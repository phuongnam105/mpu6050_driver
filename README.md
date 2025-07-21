# MPU6050 Linux Kernel Driver

This project implements a Linux kernel module (device driver) for the MPU6050 IMU sensor, along with a user-space application to test the data acquisition via `/dev/mpu6050`.

## 📌 Features

- Communicates with MPU6050 via I2C on Raspberry Pi 3
- Supports reading accelerometer, gyroscope, and temperature data
- Exposes sensor data via character device `/dev/mpu6050`
- User-space C program provided for real-time testing
