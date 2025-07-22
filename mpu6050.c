#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include "mpu6050.h"


#define MPU6050_NAME    "mpu6050"
#define MPU6050_COUNT   1

 typedef struct{
    dev_t devid;
    struct cdev cdev;
    struct class* class;
    struct device* device;
    void* private_data;
    int major;
    int accel_x_adc;
    int accel_y_adc;
    int accel_z_adc;
    int gyro_x_adc;
    int gyro_y_adc;
    int gyro_z_adc;
    int temp_adc;
}mpu6050_dev;

static mpu6050_dev mpu6050dev;



static s32 mpu_write_regs(mpu6050_dev* dev, u8 *buffer, u8 reg, u8 len)
{
    u8 b[256];
    struct i2c_client *client = (struct i2c_client*)dev->private_data;
    struct i2c_msg msg;
    // gộp data vào 1 buffer 
    b[0] = reg;
    memcpy(&b[1], buffer, len);

    msg.addr = client->addr;
    msg.flags = 0;
    msg.buf = b;
    msg.len = len + 1;


    return i2c_transfer(client->adapter,&msg,1);

}

static void mpu_write_onereg(mpu6050_dev* dev,u8 reg, u8 data)
{
    u8 buffer = 0;
    buffer = data;
    mpu_write_regs(dev,&buffer,reg,1);
}

static int mpu_read_regs(mpu6050_dev* dev, u8 reg, void *val, int len)
{
    int ret;
    struct i2c_client* client = (struct i2c_client*)dev->private_data;
    struct i2c_msg msg[2];

    //write register
    msg[0].addr = client->addr;
    msg[0].flags = 0;
    msg[0].buf = &reg;
    msg[0].len = 1;

    //read data from register
    msg[1].addr = client->addr;
    msg[1].flags = I2C_M_RD;
    msg[1].buf  = val;
    msg[1].len  = len;

    ret = i2c_transfer(client->adapter,msg,2);

    return ret;
}

static u8 mpu_read_onereg(mpu6050_dev* dev, uint8_t reg)
{
    uint8_t data =0;
    mpu_read_regs(dev,reg,&data,1);
    return data;
}

void mpu6050_data_read(mpu6050_dev *dev)
{
    uint8_t data[14];
    mpu_read_regs(dev,MPU_ACCEL_XOUT_H,data,14);

    dev->accel_x_adc = (s16)((data[0] << 8)|data[1]);
    dev->accel_y_adc = (s16)((data[2] << 8)|data[3]);
    dev->accel_z_adc = (s16)((data[4] << 8)|data[5]);
    dev->temp_adc   = (s16)((data[6] << 8) | data[7]);
    dev->gyro_x_adc = (s16)((data[8] << 8)|data[9]);
    dev->gyro_y_adc = (s16)((data[10] << 8)|data[11]);
    dev->gyro_z_adc = (s16)((data[12] << 8)|data[13]);
   
}

void mpu_init(void)
{
    uint8_t ret = 0;
    // Reset MPU6050
    mpu_write_onereg(&mpu6050dev,MPU_PWR_MGMT_1,0x80);
    msleep(100);

    // Bỏ sleep mode, chọn nguồn xung nội
    mpu_write_onereg(&mpu6050dev, MPU_PWR_MGMT_1, 0x00);
    msleep(10);

    ret = mpu_read_onereg(&mpu6050dev,MPU_WHO_AM_I);
    printk("mpu6050 ID = 0x%02x\n",ret);
    
    // Sample rate = Gyro output rate / (1 + SMPLRT_DIV)
    mpu_write_onereg(&mpu6050dev,MPU_SMPLRT_DIV,0x00);
    // DLPF 44Hz
    mpu_write_onereg(&mpu6050dev,MPU_CONFIG,0x03);
    // Gyro full scale ±2000°/s
    mpu_write_onereg(&mpu6050dev,MPU_GYRO_CONFIG,0x18);//full scale range 2000
    // Accel full scale ±16g
    mpu_write_onereg(&mpu6050dev,MPU_ACCEL_CONFIG,0x18);//full scale range 16g
    // Bật tất cả cảm biến (gyro + accel)
    mpu_write_onereg(&mpu6050dev,MPU_PWR_MGMT_2,0x00);
    // Tạm thời tắt FIFO
    mpu_write_onereg(&mpu6050dev,MPU_FIFO_EN,0x00);
}

static int mpu6050_open(struct inode *inode, struct file *file)
{
    file->private_data = &mpu6050dev;
    return 0;
}

static ssize_t mpu6050_read(struct file *file, char __user *user_buf,
                            size_t count, loff_t *ppos)
{
    mpu6050_dev *dev = (mpu6050_dev*)file->private_data;
    signed int data[7];
    size_t datalen = sizeof(data);
    signed int ret;

    mpu6050_data_read(dev);

    data[0] = dev->accel_x_adc;
    data[1] = dev->accel_y_adc;
    data[2] = dev->accel_z_adc;

    data[3] = dev->gyro_x_adc;
    data[4] = dev->gyro_y_adc;
    data[5] = dev->gyro_z_adc;

    data[6] = dev->temp_adc;

    ret = copy_to_user(user_buf,data,sizeof(data));

    if (ret != 0){
        return -EFAULT;
    }
    *ppos += datalen;  // cập nhật offset để đọc 1 lần

    return datalen;

}

static int mpu6050_release(struct inode *inode, struct file *file)
{
    return 0;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = mpu6050_open,
    .read = mpu6050_read,
    .release = mpu6050_release,
};

static int mpu6050_probe (struct i2c_client* client, const struct i2c_device_id *id)
{
    int ret;

    printk("init module: entry!!!\n");

    if(mpu6050dev.major)
    {
        mpu6050dev.devid = MKDEV(mpu6050dev.major,0);
        ret = register_chrdev_region(mpu6050dev.devid,MPU6050_COUNT,MPU6050_NAME);
    }
    else
    {
        ret = alloc_chrdev_region(&mpu6050dev.devid,0,MPU6050_COUNT,MPU6050_NAME);
        mpu6050dev.major = MAJOR(mpu6050dev.devid);
    }

    if (ret < 0)
    {
        pr_err("Failed to allocate chrdev region !!!!\n");
        return ret;
    }


    cdev_init(&mpu6050dev.cdev,&fops);
    cdev_add(&mpu6050dev.cdev,mpu6050dev.devid,MPU6050_COUNT);

    mpu6050dev.class = class_create(THIS_MODULE,MPU6050_NAME);
    mpu6050dev.device = device_create(mpu6050dev.class,NULL,mpu6050dev.devid,NULL,MPU6050_NAME);

    mpu6050dev.private_data = client;

    printk("init module: exit!!\n");
    mpu_init();
    return 0;
}

static int mpu6050_remove(struct i2c_client *client)
{
    printk("exit module: entry!!");
    device_destroy(mpu6050dev.class, mpu6050dev.devid);
    class_destroy(mpu6050dev.class);
    unregister_chrdev_region(mpu6050dev.devid,MPU6050_COUNT);
    cdev_del(&mpu6050dev.cdev);
    printk("exit module: exit!!");
    return 0;
}

static const struct i2c_device_id mpu6050_id[] = {
    {"invense,mpu6050",0},
    {}
};
MODULE_DEVICE_TABLE(i2c, mpu6050_id);


static const struct of_device_id mpu6050_of_match[] = {
    {.compatible = "invense,mpu6050"},
    {}
};
MODULE_DEVICE_TABLE(of, mpu6050_of_match);

static struct i2c_driver mpu6050_driver = 
{
    .probe = mpu6050_probe,
    .remove = mpu6050_remove,
    .driver = {
        .owner = THIS_MODULE,
        .name = MPU6050_NAME,
        .of_match_table = mpu6050_of_match,
    },
    .id_table = mpu6050_id,
};

static int __init mpu6050_init(void)
{
    int ret = 0;
    ret = i2c_add_driver(&mpu6050_driver);
    return ret;
}

static void __exit mpu6050_exit(void)
{
    i2c_del_driver(&mpu6050_driver);
}

module_init(mpu6050_init);
module_exit(mpu6050_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edogawa Conam");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");
