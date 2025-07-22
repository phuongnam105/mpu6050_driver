# MPU6050 Linux Kernel Driver

This project implements a Linux kernel module (device driver) for the MPU6050 IMU sensor, along with a user-space application to test the data acquisition via `/dev/mpu6050`.

## 📌 Features

- Communicates with MPU6050 via I2C on Raspberry Pi 3
- Supports reading accelerometer, gyroscope, and temperature data
- Exposes sensor data via character device `/dev/mpu6050`
- User-space C program provided for real-time testing

This is a node for mpu6050, you must insert into i2c parent node in Device Tree (.dts). To create struct client for mpu node

mpu6050@68 {
    compatible = "invense,mpu6050";
    reg = <0x68>;
    status = "okay";
};

## Noted
You must change a status for i2c bus to "okay", which bus you want to use for your sensor (example : i2c_1, i2c_2,..)

Thank you for reading !!!!!!!
