#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
    int fd;
    signed int buf[7];
    int accel_x_adc, accel_y_adc, accel_z_adc;
    int gyro_x_adc, gyro_y_adc, gyro_z_adc;
    int temp_adc;

    float accel_x, accel_y, accel_z;
    float gyro_x, gyro_y, gyro_z;
    float temp;

    int ret = 0;
    char* filename = "/dev/mpu6050";
    fd = open(filename,O_RDWR);
    if (fd < 0){
        printf("can't open this file!!!!");
        return -1;
    }

    while(1){
        ret = read(fd,buf,sizeof(buf));

        if(ret > 0)
        {
            gyro_x_adc = buf[3];
            gyro_y_adc = buf[4];
            gyro_z_adc = buf[5];
            accel_x_adc = buf[0];
            accel_y_adc = buf[1];
            accel_z_adc = buf[2];
            temp_adc = buf[6];

            gyro_x = (float)gyro_x_adc/16.4;
            gyro_y = (float)gyro_y_adc/16.4;
            gyro_z = (float)gyro_z_adc/16.4;

            accel_x = (float)accel_x_adc/2048;
            accel_y = (float)accel_y_adc/2048;
            accel_z = (float)accel_z_adc/1048;

            temp = (float)(temp_adc/340) + 36.5;

			printf(" gx = %.2f°/S, gy = %.2f°/S, gz = %.2f°/S\r\n", gyro_x, gyro_y, gyro_z);
			printf(" ax = %.2fg, ay = %.2fg, az = %.2fg\r\n", accel_x, accel_y, accel_z);
			printf(" temp = %.2f°C\r\n", temp);

    
        }
        usleep(5000);
    }
    close(fd);
    return 0;
}