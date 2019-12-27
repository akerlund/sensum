EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:w_freaquency
LIBS:w_microcontrollers
LIBS:crf_1
LIBS:w_analog
LIBS:w_logic
LIBS:w_opto
LIBS:w_connectors
LIBS:w_device
LIBS:w_transistor
LIBS:w_rtx
LIBS:w_relay
LIBS:w_memory
LIBS:sensor_pcb-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L HEADER_4 J101
U 1 1 59D7DD7E
P 1300 1100
F 0 "J101" H 1300 1350 60  0000 C CNN
F 1 "VL53L0X" V 1500 1100 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_4" H 1300 1100 60  0001 C CNN
F 3 "" H 1300 1100 60  0000 C CNN
	1    1300 1100
	1    0    0    -1  
$EndComp
$Comp
L HEADER_5 J110
U 1 1 59D7DDBF
P 9600 2750
F 0 "J110" H 9600 3050 60  0000 C CNN
F 1 "NEO6M" V 9800 2750 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_5" H 9600 2750 60  0001 C CNN
F 3 "" H 9600 2750 60  0000 C CNN
	1    9600 2750
	1    0    0    -1  
$EndComp
$Comp
L HEADER_7 J103
U 1 1 59D7DE1D
P 9600 1250
F 0 "J103" H 9600 1650 60  0000 C CNN
F 1 "SSD1331" V 9800 1250 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_7" H 9600 1250 60  0001 C CNN
F 3 "" H 9600 1250 60  0000 C CNN
	1    9600 1250
	1    0    0    -1  
$EndComp
$Comp
L HEADER_4 J105
U 1 1 59D7DEDD
P 1300 1700
F 0 "J105" H 1300 1950 60  0000 C CNN
F 1 "BMP180" V 1500 1700 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_4" H 1300 1700 60  0001 C CNN
F 3 "" H 1300 1700 60  0000 C CNN
	1    1300 1700
	1    0    0    -1  
$EndComp
$Comp
L HEADER_4 J111
U 1 1 59D7DF18
P 1300 3100
F 0 "J111" H 1300 3350 60  0000 C CNN
F 1 "Si7021" V 1500 3100 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_4" H 1300 3100 60  0001 C CNN
F 3 "" H 1300 3100 60  0000 C CNN
	1    1300 3100
	1    0    0    -1  
$EndComp
$Comp
L HEADER_5 J102
U 1 1 59D7DFE5
P 3800 1150
F 0 "J102" H 3800 1450 60  0000 C CNN
F 1 "ISL29125" V 4000 1150 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_5" H 3800 1150 60  0001 C CNN
F 3 "" H 3800 1150 60  0000 C CNN
	1    3800 1150
	1    0    0    -1  
$EndComp
$Comp
L HEADER_5 J106
U 1 1 59D7E029
P 3800 1850
F 0 "J106" H 3800 2150 60  0000 C CNN
F 1 "VEML6070" V 4000 1850 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_5" H 3800 1850 60  0001 C CNN
F 3 "" H 3800 1850 60  0000 C CNN
	1    3800 1850
	1    0    0    -1  
$EndComp
$Comp
L HEADER_6 J114
U 1 1 59D7E10F
P 1300 4400
F 0 "J114" H 1300 4750 60  0000 C CNN
F 1 "OPT3001" V 1500 4400 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_6" H 1300 4400 60  0001 C CNN
F 3 "" H 1300 4400 60  0000 C CNN
	1    1300 4400
	1    0    0    -1  
$EndComp
$Comp
L HEADER_7 J112
U 1 1 59D7E1BE
P 3800 3650
F 0 "J112" H 3800 4050 60  0000 C CNN
F 1 "TCS34725" V 4000 3650 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_7" H 3800 3650 60  0001 C CNN
F 3 "" H 3800 3650 60  0000 C CNN
	1    3800 3650
	1    0    0    -1  
$EndComp
$Comp
L HEADER_10 J104
U 1 1 59D7E272
P 6400 1400
F 0 "J104" H 6400 1950 60  0000 C CNN
F 1 "MPU9250" V 6600 1400 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_10" H 6400 1400 60  0001 C CNN
F 3 "" H 6400 1400 60  0000 C CNN
	1    6400 1400
	1    0    0    -1  
$EndComp
Text Label 1200 950  2    60   ~ 0
3V3
Text Label 1200 1050 2    60   ~ 0
GND
Text Label 1200 1150 2    60   ~ 0
SCL
Text Label 1200 1250 2    60   ~ 0
SDA
Text Label 1200 1550 2    60   ~ 0
3V3
Text Label 1200 1650 2    60   ~ 0
GND
Text Label 1200 1750 2    60   ~ 0
SCL
Text Label 1200 1850 2    60   ~ 0
SDA
Text Label 1200 2950 2    60   ~ 0
3V3
Text Label 1200 3050 2    60   ~ 0
GND
Text Label 1200 3150 2    60   ~ 0
SCL
Text Label 1200 3250 2    60   ~ 0
SDA
Text Notes 9950 2050 1    60   ~ 0
UVB
Text Label 9500 2100 2    60   ~ 0
3V3
Text Label 9500 2000 2    60   ~ 0
GND
Text Label 9500 1900 2    60   ~ 0
ML8511_OUT
Text Label 9500 2550 2    60   ~ 0
NEO6M_PPS
Text Label 9500 2650 2    60   ~ 0
NEO6M_RXD
Text Label 9500 2750 2    60   ~ 0
NEO6M_TXD
Text Label 9500 2850 2    60   ~ 0
GND
Text Label 9500 2950 2    60   ~ 0
3V3
Text Label 1200 2150 2    60   ~ 0
3V3
Text Label 1200 2250 2    60   ~ 0
GND
Text Label 1200 2350 2    60   ~ 0
SCL
Text Label 1200 2450 2    60   ~ 0
SDA
$Comp
L HEADER_4 J113
U 1 1 59D7F011
P 1300 3700
F 0 "J113" H 1300 3950 60  0000 C CNN
F 1 "MAX44009" V 1500 3700 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_4" H 1300 3700 60  0001 C CNN
F 3 "" H 1300 3700 60  0000 C CNN
	1    1300 3700
	1    0    0    -1  
$EndComp
Text Label 1200 3850 2    60   ~ 0
3V3
Text Label 1200 3750 2    60   ~ 0
GND
Text Label 1200 3650 2    60   ~ 0
SCL
Text Label 1200 3550 2    60   ~ 0
SDA
Text Notes 1650 4000 1    60   ~ 0
Ambient Light
Text Notes 1650 3300 1    60   ~ 0
Humidity
Text Label 3700 950  2    60   ~ 0
GND
Text Label 3700 1050 2    60   ~ 0
3V3
Text Label 3700 1150 2    60   ~ 0
SDA
Text Label 3700 1250 2    60   ~ 0
SCL
Text Label 3700 1350 2    60   ~ 0
ISL29125_INT
Text Notes 9950 2800 1    60   ~ 0
GPS
Text Notes 4150 1200 1    60   ~ 0
RGB
Text Notes 4150 1900 1    60   ~ 0
UV
Text Label 3700 2050 2    60   ~ 0
3V3
Text Label 3700 1950 2    60   ~ 0
GND
Text Label 3700 1850 2    60   ~ 0
SCL
Text Label 3700 1750 2    60   ~ 0
SDA
Text Label 3700 1650 2    60   ~ 0
VEML6070_ACK
Text Notes 4150 2850 1    60   ~ 0
Current
Text Label 3700 2350 2    60   ~ 0
3V3
Text Label 3700 2450 2    60   ~ 0
GND
Text Label 3700 2550 2    60   ~ 0
SCL
Text Label 3700 2650 2    60   ~ 0
SDA
Text Notes 1650 4700 1    60   ~ 0
Ambient Light
Text Label 1200 4650 2    60   ~ 0
3V3
Text Label 1200 4550 2    60   ~ 0
GND
Text Label 1200 4450 2    60   ~ 0
SCL
Text Label 1200 4350 2    60   ~ 0
SDA
Text Label 1200 4250 2    60   ~ 0
OPT3001_INT
Text Label 1200 4150 2    60   ~ 0
OPT3001_ADD
Text Notes 9950 1350 1    60   ~ 0
OLED
Text Label 9500 950  2    60   ~ 0
SSD1331_CS
Text Label 9500 1050 2    60   ~ 0
SSD1331_DC
Text Label 9500 1150 2    60   ~ 0
SSD1331_RES
Text Label 9500 1450 2    60   ~ 0
5V
Text Label 9500 1550 2    60   ~ 0
GND
Text Label 3700 3350 2    60   ~ 0
TCS34725_LED
Text Label 3700 3450 2    60   ~ 0
TCS34725_INT
Text Label 3700 3750 2    60   ~ 0
3V3
Text Label 3700 3850 2    60   ~ 0
GND
Text Label 3700 3650 2    60   ~ 0
SCL
Text Label 3700 3550 2    60   ~ 0
SDA
NoConn ~ 3700 3950
Text Label 3700 4250 2    60   ~ 0
3V3
Text Label 3700 4350 2    60   ~ 0
GND
Text Label 3700 4450 2    60   ~ 0
SCL
Text Label 3700 4550 2    60   ~ 0
SDA
Text Label 3600 4650 2    60   ~ 0
MS5611_CSB
Text Label 3600 4750 2    60   ~ 0
MS5611_SDO
Text Notes 1650 2500 1    60   ~ 0
Pressure
Text Notes 1650 1900 1    60   ~ 0
Pressure
Text Notes 4150 4700 1    60   ~ 0
Pressure
Text Notes 4250 4750 1    60   ~ 0
GY-63 $7
Text Label 6300 950  2    60   ~ 0
3V3
Text Label 6300 1050 2    60   ~ 0
GND
Text Label 6300 1150 2    60   ~ 0
SCL
Text Label 6300 1250 2    60   ~ 0
SDA
Text Label 6200 1350 2    60   ~ 0
MPU9250_EDA
Text Label 6200 1450 2    60   ~ 0
MPU9250_ECL
Text Label 6400 2100 2    60   ~ 0
MPU9250_ADD
Text Label 6300 1650 2    60   ~ 0
MPU9250_INT
Text Label 6200 1750 2    60   ~ 0
MPU9250_NCS
Text Label 6300 1850 2    60   ~ 0
MPU9250_FSYNC
Text Label 8000 4050 2    60   ~ 0
GND
Text Label 8000 5250 2    60   ~ 0
SCL
Text Label 8000 5350 2    60   ~ 0
SDA
Text Label 8000 4450 2    60   ~ 0
ML8511_OUT
Text Label 9850 3950 0    60   ~ 0
NEO6M_PPS
Text Label 8000 5050 2    60   ~ 0
NEO6M_RXD
Text Label 8000 5150 2    60   ~ 0
NEO6M_TXD
Text Label 9850 4050 0    60   ~ 0
ISL29125_INT
Text Label 9850 4150 0    60   ~ 0
VEML6070_ACK
Text Label 9850 4250 0    60   ~ 0
OPT3001_INT
Text Label 9850 4350 0    60   ~ 0
SSD1331_CS
Text Label 9850 4450 0    60   ~ 0
SSD1331_DC
Text Label 9850 4550 0    60   ~ 0
SSD1331_RES
Text Label 9850 4650 0    60   ~ 0
TCS34725_LED
Text Label 9850 4750 0    60   ~ 0
TCS34725_INT
Text Label 3400 4850 2    60   ~ 0
MS5611_PS
Text Label 9850 4850 0    60   ~ 0
MPU9250_INT
Text Label 9850 4950 0    60   ~ 0
MPU9250_FSYNC
Text Label 9500 1800 2    60   ~ 0
3V3
Text Notes 8500 2550 0    60   ~ 0
Timepulse
NoConn ~ 3700 2750
NoConn ~ 3700 2850
Text Notes 1800 4700 0    60   ~ 0
I2C\nAD0=0: 1000100 0x44\nAD0=1: 1000101 0x45
Text Notes 4400 2900 0    60   ~ 0
I2C\n00: 1000000  0x40\n01: 1000001  0x41\n10: 1000100  0x44\n11: 1000101  0x45
Text Notes 4400 2100 0    60   ~ 0
I2C\n0x38 & 0x39
Text Notes 3300 5200 0    60   ~ 0
Protocol Select\n0: SPI\n1: I2C
Text Label 3600 4850 2    60   ~ 0
3V3
Wire Wire Line
	3400 4850 3700 4850
NoConn ~ 3700 4650
NoConn ~ 3700 4750
Text Notes 4400 4900 0    60   ~ 0
I2C\n111011Cx, where C is\nthe complementary\nvalue of the pin CSB.
NoConn ~ 6300 1350
NoConn ~ 6300 1450
NoConn ~ 6300 1750
Text Label 6300 1550 2    60   ~ 0
MPU9250_ADD
Wire Wire Line
	6400 2100 6500 2100
Text Notes 5600 1250 0    60   ~ 0
External
Text Notes 7000 1500 0    60   ~ 0
I2C\n110100X
Text Label 6500 2100 0    60   ~ 0
GND
Text Label 1300 4900 2    60   ~ 0
OPT3001_ADD
Text Label 8000 4150 2    60   ~ 0
5V
Wire Wire Line
	1300 4900 1400 4900
Text Label 1400 4900 0    60   ~ 0
GND
Text Notes 1800 1300 0    60   ~ 0
I2C\n1001001x\n0x52
Text Notes 1800 1900 0    60   ~ 0
I2C\n1110111x\n0xEE
Text Notes 1800 3300 0    60   ~ 0
I2C\n1000000x\n0x40
Text Notes 1650 1200 1    60   ~ 0
Laser
Text Notes 1800 2500 0    60   ~ 0
I2C (LOW/HIGH)\n1110110x / 1110111x\n0x76 / 0x77
Text Notes 1800 3900 0    60   ~ 0
I2C (LOW/HIGH)\n1001010x / 1001011x\n0x4A / 0x4B
Text Notes 4400 1400 0    60   ~ 0
I2C\n1000100x\n0x44
Text Notes 4150 3750 1    60   ~ 0
RGB
Text Notes 4400 4000 0    60   ~ 0
I2C\n0101001x\n0x29
Text Notes 7000 1900 0    60   ~ 0
I2C\nAD0=0: 1101000 0x68\nAD0=1: 1101001 0x69
Text Notes 6750 1500 1    60   ~ 0
IMU
Text Label 6300 1850 2    60   ~ 0
MPU9250_FSYNC
$Comp
L HEADER_5 J107
U 1 1 59FB8871
P 9600 2000
F 0 "J107" H 9600 2300 60  0000 C CNN
F 1 "ML8511" V 9800 2000 60  0000 C CNN
F 2 "w_pin_strip:pin_strip_5" H 9600 2000 60  0001 C CNN
F 3 "" H 9600 2000 60  0000 C CNN
	1    9600 2000
	1    0    0    -1  
$EndComp
$Comp
L HEADER_8 J109
U 1 1 59FB8E82
P 3800 2700
F 0 "J109" H 3800 3150 60  0000 C CNN
F 1 "INA226" V 4000 2700 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_8" H 3800 2700 60  0001 C CNN
F 3 "" H 3800 2700 60  0000 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
$Comp
L HEADER_4 J122
U 1 1 59FB9182
P 6400 2550
F 0 "J122" H 6400 2800 60  0000 C CNN
F 1 "NFC" V 6600 2550 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_4" H 6400 2550 60  0001 C CNN
F 3 "" H 6400 2550 60  0000 C CNN
	1    6400 2550
	1    0    0    -1  
$EndComp
Text Label 6300 2500 2    60   ~ 0
3V3
Text Label 6300 2400 2    60   ~ 0
GND
Text Label 6300 2700 2    60   ~ 0
SCL
Text Label 6300 2600 2    60   ~ 0
SDA
$Comp
L HEADER_8 J123
U 1 1 59FB95BA
P 6400 3500
F 0 "J123" H 6400 3950 60  0000 C CNN
F 1 "nRF24L01" V 6600 3500 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_4x2" H 6400 3500 60  0001 C CNN
F 3 "" H 6400 3500 60  0000 C CNN
	1    6400 3500
	1    0    0    -1  
$EndComp
Text Label 6300 3150 2    60   ~ 0
GND
Text Label 6300 3250 2    60   ~ 0
3V3
Text Label 6300 3350 2    60   ~ 0
nRF42L01_CE
Text Label 6300 3450 2    60   ~ 0
nRF42L01_CSN
Text Label 6300 4200 2    60   ~ 0
nRF42L01_SCK
Text Label 6300 4300 2    60   ~ 0
nRF42L01_MOSI
Text Label 6300 4400 2    60   ~ 0
nRF42L01_MISO
Text Label 6300 3850 2    60   ~ 0
nRF42L01_IRQ
$Comp
L HEADER_6 J108
U 1 1 59FBA013
P 1300 2400
F 0 "J108" H 1300 2750 60  0000 C CNN
F 1 "BMP280" V 1500 2400 60  0000 C CNN
F 2 "w_pin_strip:pin_strip_6" H 1300 2400 60  0001 C CNN
F 3 "" H 1300 2400 60  0000 C CNN
	1    1300 2400
	1    0    0    -1  
$EndComp
NoConn ~ 1200 2550
NoConn ~ 1200 2650
Text Label 8000 5550 2    60   ~ 0
STM_MOSI
Text Label 8000 5650 2    60   ~ 0
STM_MISO
Text Label 9850 5050 0    60   ~ 0
nRF42L01_CSN
Text Label 6300 3550 2    60   ~ 0
nRF42L01_SCK
Text Label 6300 3650 2    60   ~ 0
nRF42L01_MOSI
Text Label 6300 3750 2    60   ~ 0
nRF42L01_MISO
Text Label 6400 4300 0    60   ~ 0
STM_MOSI
Text Label 6400 4400 0    60   ~ 0
STM_MISO
Text Label 6400 4200 0    60   ~ 0
STM_SCK
Wire Wire Line
	6300 4200 6400 4200
Wire Wire Line
	6400 4300 6300 4300
Wire Wire Line
	6300 4400 6400 4400
Text Label 9500 1250 2    60   ~ 0
STM_MOSI
Text Label 9500 1350 2    60   ~ 0
STM_SCK
$Sheet
S 8000 3850 1850 1950
U 59FBD089
F0 "STM32F405" 60
F1 "STM32F405.sch" 60
F2 "GND" I L 8000 4050 60 
F3 "VDD" I L 8000 3950 60 
F4 "ADC0" I L 8000 4450 60 
F5 "ADC1" I L 8000 4550 60 
F6 "USART1_TX" I L 8000 5050 60 
F7 "USART1_RX" I L 8000 5150 60 
F8 "I2C_SCL" I L 8000 5250 60 
F9 "I2C_SDA" I L 8000 5350 60 
F10 "5V_USB" I L 8000 4150 60 
F11 "NEO6M_PPS" I R 9850 3950 60 
F12 "ISL29125_INT" I R 9850 4050 60 
F13 "VEML6070_ACK" I R 9850 4150 60 
F14 "OPT3001_INT" I R 9850 4250 60 
F15 "SSD1331_CS" I R 9850 4350 60 
F16 "SSD1331_DS" I R 9850 4450 60 
F17 "SSD1331_RES" I R 9850 4550 60 
F18 "TCS34725_LED" I R 9850 4650 60 
F19 "TCS34725_INT" I R 9850 4750 60 
F20 "MPU9250_INT" I R 9850 4850 60 
F21 "MPU9250_FSYNC" I R 9850 4950 60 
F22 "nRF42L01_CSN" I R 9850 5050 60 
F23 "SPI2_MISO" I L 8000 5550 60 
F24 "SPI2_MOSI" I L 8000 5650 60 
F25 "SPI2_SCK" I L 8000 5450 60 
F26 "nRF42L01_IRQ" I R 9850 5150 60 
F27 "nRF42L01_CE" I R 9850 5250 60 
$EndSheet
Text Label 8000 3950 2    60   ~ 0
3V3
Text Label 8000 5450 2    60   ~ 0
STM_SCK
Text Notes 1750 3850 1    60   ~ 0
GY-49
Text Notes 1750 4550 1    60   ~ 0
CJMCU
$Comp
L drill U101
U 1 1 59FD8AB9
P 1150 6950
F 0 "U101" H 1150 7050 60  0000 C CNN
F 1 "drill" H 1150 6850 60  0000 C CNN
F 2 "freaquency:drill_2.0mm" H 1150 6950 60  0001 C CNN
F 3 "" H 1150 6950 60  0000 C CNN
	1    1150 6950
	1    0    0    -1  
$EndComp
$Comp
L drill U102
U 1 1 59FD922C
P 1350 6950
F 0 "U102" H 1350 7050 60  0000 C CNN
F 1 "drill" H 1350 6850 60  0000 C CNN
F 2 "freaquency:drill_2.0mm" H 1350 6950 60  0001 C CNN
F 3 "" H 1350 6950 60  0000 C CNN
	1    1350 6950
	1    0    0    -1  
$EndComp
$Comp
L drill U103
U 1 1 59FD9410
P 1550 6950
F 0 "U103" H 1550 7050 60  0000 C CNN
F 1 "drill" H 1550 6850 60  0000 C CNN
F 2 "freaquency:drill_2.0mm" H 1550 6950 60  0001 C CNN
F 3 "" H 1550 6950 60  0000 C CNN
	1    1550 6950
	1    0    0    -1  
$EndComp
$Comp
L drill U104
U 1 1 59FD9416
P 1750 6950
F 0 "U104" H 1750 7050 60  0000 C CNN
F 1 "drill" H 1750 6850 60  0000 C CNN
F 2 "freaquency:drill_2.0mm" H 1750 6950 60  0001 C CNN
F 3 "" H 1750 6950 60  0000 C CNN
	1    1750 6950
	1    0    0    -1  
$EndComp
Text Label 9850 5150 0    60   ~ 0
nRF42L01_IRQ
Text Label 7250 5250 2    60   ~ 0
I2C+
Text Label 7250 5350 2    60   ~ 0
I2C-
Wire Wire Line
	8000 5250 7250 5250
Wire Wire Line
	7250 5350 8000 5350
$Comp
L HEADER_7 J115
U 1 1 59FF44AD
P 3800 4550
F 0 "J115" H 3800 4950 60  0000 C CNN
F 1 "MS5611" V 3950 4550 60  0000 C CNN
F 2 "w_pin_strip:pin_socket_7" H 3800 4550 60  0001 C CNN
F 3 "" H 3800 4550 60  0000 C CNN
	1    3800 4550
	1    0    0    -1  
$EndComp
NoConn ~ 3700 2950
NoConn ~ 3700 3050
NoConn ~ 9500 2200
Text Label 9850 5250 0    60   ~ 0
nRF42L01_CE
NoConn ~ 8000 4550
$EndSCHEMATC
