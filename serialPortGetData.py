# NASA Spase Apps challenge 2018
# Command: Interstellar Dolphin
# Challange: Make Sense out of Mars
# v0.1

# Read some rows of data from Serial port and calculate physical
# sensors data.  

import serial

def parse_serial(rew_serial_data):
    data_set = list()
    for row in rew_serial_data:
        data_list = row[:-1].split(" ")
        data_list_int = list()
        for serial_str in data_list:
            serial_int = int(serial_str)
            data_list_int.append(serial_int)
            
        data_set.append(data_list_int)
    return data_set

def analyze_HC_data(hc_rew_data):
    c = 343.21 # Speed of sound
    hc_calc_data = list()
    for rew_data_time in hc_rew_data:
        dist = c*rew_data_time/1000000.0 # m
        hc_calc_data.append(dist)
    return hc_calc_data

def analyze_gyroscope_data(gyro_rew_data):
    gyro_calc_data = list()
    gyroMPUconst = 131.0 # MPU constatnt. CHECK WHEN USE! LSB/deg
    gyro_data_set = [0, 0, 0]
    for gyro_data in gyro_rew_data:
        gyro_data_set[0] = gyro_data[0]/gyroMPUconst
        gyro_data_set[1] = gyro_data[1]/gyroMPUconst
        gyro_data_set[2] = gyro_data[2]/gyroMPUconst

        gyro_calc_data.append(gyro_data_set)
    return gyro_calc_data

def analyze_accelerometer_data(accel_rew_data):
    acc_calc_data = list()
    accMPUconst = 16384.0 #  MPU constatnt. CHECK WHEN USE! LSB/g
    acc_data_set = [0, 0, 0]
    for acc_data in accel_rew_data:
        acc_data_set[0] = acc_data[0]/accMPUconst
        acc_data_set[1] = acc_data[1]/accMPUconst
        acc_data_set[2] = acc_data[2]/accMPUconst

        acc_calc_data.append(acc_data_set)
    return acc_calc_data

serial_dataset = serial.Serial('COM18', 9600)
serial_data = list()

for i in range(1, 10):
    #print(i)
    serial_bytes = serial_dataset.readline()
    serial_bytes_dec = serial_bytes.decode('utf-8')
    serial_data.append(serial_bytes_dec)

# Parsed serial 
# [0] - duration of ultra sound sensor 1
# [1] - duration of ultra sound sensor 2

# MPU 01
# [2] - acceselerometer X
# [3] - acceselerometer Y
# [4] - acceselerometer Z
# [5] - Gyroscope X
# [6] - Gyroscope Y
# [7] - Gyroscope Z

# MPU 02
# [8] - acceselerometer X
# [9] - acceselerometer Y
# [10] - acceselerometer Z
# [11] - Gyroscope X
# [12] - Gyroscope Y
# [13] - Gyroscope Z

parsed_serial = parse_serial(serial_data)

# print(parsed_serial)

# Reorganize data
durationHC1 = list()
durationHC2 = list()

accelerometerMPU1 = list()
accelerometerMPU2 = list()

gyroscopeMPU1 = list()
gyroscopeMPU2 = list()

for parsed_row in parsed_serial:
    durationHC1.append(parsed_row[0])
    durationHC2.append(parsed_row[1])
    accelerometerMPU1.append(parsed_row[2:5])
    gyroscopeMPU1.append(parsed_row[5:8])
    accelerometerMPU2.append(parsed_row[8:11])
    gyroscopeMPU2.append(parsed_row[11:])

#print(durationHC1)
#print(durationHC2)
#print(accelerometerMPU1)

hc1_dist = analyze_HC_data(durationHC1)
hc2_dist = analyze_HC_data(durationHC2)

MPU1_gyro_data = analyze_gyroscope_data(gyroscopeMPU1)
MPU2_gyro_data = analyze_gyroscope_data(gyroscopeMPU2)

MPU1_accel_data = analyze_accelerometer_data(gyroscopeMPU1)
MPU2_accel_data = analyze_accelerometer_data(gyroscopeMPU2)

print(hc1_dist)
print(hc2_dist)
print(MPU1_gyro_data)
print(MPU2_gyro_data)
print(MPU1_accel_data)
print(MPU2_accel_data)

# Further it is needed compute coordinates of 3D scanner and
# form the point cloud for building
    
