#ifndef _MPU6050_REG_H_
#define _MPU6050_REG_H_

#define MPU_ADDRESS_LOW     0x68
#define MPU_ADDRESS_HIGH    0x69
#define MPU_ADDRESS_DEFAULT MPU_ADDRESS_LOW

//thanh ghi điều chỉnh tốc độ lấy mẫu (Sample rate Divider)
#define MPU_SMPLRT_DIV      0x19

//thanh ghi cấu hình (Configuration)
#define MPU_CONFIG          0x1A

//thanh ghi cấu hình con quay hồi chuyển
#define MPU_GYRO_CONFIG     0x1B

//thanh ghi cấu hình gia tốc
#define MPU_ACCEL_CONFIG    0x1C

//thanh ghi bật FIFO
#define MPU_FIFO_EN         0x23

//thanh ghi điều khiển I2C Master
#define MPU_I2C_MST_CTRL    0x24

//thanh ghi điều khiển các thiết bị slave I2C
//slave 0
#define MPU_I2C_SLV0_ADDR   0x25
#define MPU_I2C_SLV0_REG    0x26
#define MPU_II2C_SLV0_CTRL  0x27

//slave 1
#define MPU_I2C_SLV1_ADDR   0x28
#define MPU_I2C_SLV1_REG    0x29
#define MPU_II2C_SLV1_CTRL  0x2A

//slave 2
#define MPU_I2C_SLV2_ADDR   0x2B
#define MPU_I2C_SLV2_REG    0x2C
#define MPU_II2C_SLV2_CTRL  0x2D

//slave 3
#define MPU_I2C_SLV3_ADDR   0x2E
#define MPU_I2C_SLV3_REG    0x2F
#define MPU_II2C_SLV3_CTRL  0x30

//slave 4
#define MPU_I2C_SLV4_ADDR   0x31
#define MPU_I2C_SLV4_REG    0x32
#define MPU_I2C_SLV4_DO     0x33
#define MPU_I2C_SLV4_CTRL   0x34
#define MPU_I2C_SLV4_DI     0x35

//thanh ghi đo lường gia tốc
#define MPU_ACCEL_XOUT_H    0x3B
#define MPU_ACCEL_XOUT_L    0x3C
#define MPU_ACCEL_YOUT_H    0x3D
#define MPU_ACCEL_YOUT_L    0x3E
#define MPU_ACCEL_ZOUT_H    0x3F
#define MPU_ACCEL_ZOUT_L    0x40

//thanh ghi đo lường con quay hồi chuyển
#define MPU_GYRO_XOUT_H     0x43
#define MPU_GYRO_XOUT_L     0x44
#define MPU_GYRO_YOUT_H     0x45
#define MPU_GYRO_YOUT_L     0x46
#define MPU_GYRO_ZOUT_H     0x47
#define MPU_GYRO_ZOUT_L     0x48

//thanh ghi data out của Slaves
#define MPU_SLV0_DO         0x63
#define MPU_SLV1_DO         0x64
#define MPU_SLV2_DO         0x65
#define MPU_SLV3_DO         0x66

//thanh ghi power management
#define MPU_PWR_MGMT_1      0x6B
#define MPU_PWR_MGMT_2      0x6C

//thanh ghi enable FIFO
#define MPU_FIFO_EN         0x23

//thanh ghi Who Am I
#define MPU_WHO_AM_I        0x75
/////////////////////////////////////////////////////////////////////////////////////////
#define MPU_ACCEL_DLPF_260  0
#define MPU_ACCEL_DLPF_184  1
#define MPU_ACCEL_DLPF_94   2
#define MPU_ACCEL_DLPF_44   3
#define MPU_ACCEL_DLPF_21   4
#define MPU_ACCEL_DLPF_10   5
#define MPU_ACCEL_DLPF_5    6


#define MPU_GYRO_DLPF_256   0
#define MPU_GYRO_DLPF_188   1
#define MPU_GYRO_DLPF_98    2
#define MPU_GYRO_DLPF_42    3
#define MPU_GYRO_DLPF_20    4
#define MPU_GYRO_DLPF_10    5
#define MPU_GYRO_DLPF_5     6

#define MPU_GYRO_CONFIG_FS_250  0
#define MPU_GYRO_CONFIG_FS_500  1
#define MPU_GYRO_CONFIG_FS_1000 2
#define MPU_GYRO_CONFIG_FS_2000 3

#define MPU_ACCEL_CONFIG_FS_2G   0
#define MPU_ACCEL_CONFIG_FS_4G   1
#define MPU_ACCEL_CONFIG_FS_8G   2
#define MPU_ACCEL_CONFIG_FS_16G  3

#define MPU_MST_CLOCK_348        0x0
#define MPU_MST_CLOCK_333        0x1
#define MPU_MST_CLOCK_320        0x2
#define MPU_MST_CLOCK_308        0x3
#define MPU_MST_CLOCK_296        0x4
#define MPU_MST_CLOCK_286        0x5
#define MPU_MST_CLOCK_276        0x6
#define MPU_MST_CLOCK_267        0x7
#define MPU_MST_CLOCK_258        0x8
#define MPU_MST_CLOCK_500        0x9
#define MPU_MST_CLOCK_471        0xA
#define MPU_MST_CLOCK_444        0xB
#define MPU_MST_CLOCK_421        0xC
#define MPU_MST_CLOCK_400        0xD
#define MPU_MST_CLOCK_381        0xE
#define MPU_MST_CLOCK_364        0xF

#endif