/*
 * bmp280.c
 *
 *  Created on: Aug 20, 2017
 *      Author: freakuency
 */

#include <stdint.h>
#include <math.h>
#include "i2c_functions.h"
#include "bmp280.h"

uint8_t  BMP280_ADDRESS;

uint16_t dig_T1;
int16_t  dig_T2;
int16_t  dig_T3;
uint16_t dig_P1;
int16_t  dig_P2;
int16_t  dig_P3;
int16_t  dig_P4;
int16_t  dig_P5;
int16_t  dig_P6;
int16_t  dig_P7;
int16_t  dig_P8;
int16_t  dig_P9;
int32_t  t_fine;

uint8_t temperature_buffer[3];
uint8_t pressure_buffer[3];
float  startup_pressure;

static void bmp280_read_compensation(void);


void bmp280_initialize(uint8_t add) {
    BMP280_ADDRESS = add;
    bmp280_read_compensation( );
    startup_pressure = bmp280_read_pressure( );
}

static void bmp280_read_compensation( ) {

    uint8_t comp_buffer[24];
    I2C_read_bytes(BMP280_ADDRESS_LOW, BMP280_DIG_T1, comp_buffer, 24);

    dig_T1 = (comp_buffer[0] << 8) + comp_buffer[1];
    dig_T2 = (comp_buffer[2] << 8) + comp_buffer[3];
    dig_T3 = (comp_buffer[4] << 8) + comp_buffer[5];
    dig_P1 = (comp_buffer[6] << 8) + comp_buffer[7];
    dig_P2 = (comp_buffer[8] << 8) + comp_buffer[9];
    dig_P3 = (comp_buffer[10] << 8) + comp_buffer[11];
    dig_P4 = (comp_buffer[12] << 8) + comp_buffer[13];
    dig_P5 = (comp_buffer[14] << 8) + comp_buffer[15];
    dig_P6 = (comp_buffer[16] << 8) + comp_buffer[17];
    dig_P7 = (comp_buffer[18] << 8) + comp_buffer[19];
    dig_P8 = (comp_buffer[20] << 8) + comp_buffer[21];
    dig_P9 = (comp_buffer[22] << 8) + comp_buffer[23];
}

float bmp280_read_temperature( ) {

    I2C_read_bytes(BMP280_ADDRESS, BMP280_TEMP, temperature_buffer, 3);

    int32_t adc_T = temperature_buffer[0];

    adc_T <<= 8;
    adc_T |=  temperature_buffer[1];
    adc_T <<= 8;
    adc_T |=  temperature_buffer[2];
    adc_T >>= 4;

    float var1, var2, T;
    var1 = (((float)adc_T)/16384.0 - ((float)dig_T1)/1024.0) * ((float)dig_T2);
    var2 = ((((float)adc_T)/131072.0 - ((float)dig_T1)/8192.0) * (((float)adc_T)/131072.0 - ((float) dig_T1)/8192.0)) * ((float)dig_T3);
    t_fine = (int32_t)(var1 + var2);
    T = (var1 + var2) / 5120.0;
    return T;
}

float bmp280_read_pressure( ) {

    bmp280_read_temperature( );

    I2C_read_bytes(BMP280_ADDRESS, BMP280_PRESS, pressure_buffer, 3);

    int32_t adc_P = pressure_buffer[0];

    adc_P <<= 8;
    adc_P |=  pressure_buffer[1];
    adc_P <<= 8;
    adc_P |=  pressure_buffer[2];
    adc_P >>= 4;

    float var1, var2, p;
    var1 = ((float)t_fine/2.0) - 64000.0;
    var2 = var1 * var1 * ((float)dig_P6) / 32768.0;
    var2 = var2 + var1 * ((float)dig_P5) * 2.0;
    var2 = (var2/4.0)+(((float)dig_P4) * 65536.0);
    var1 = (((float)dig_P3) * var1 * var1 / 524288.0 + ((float)dig_P2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0)*((float)dig_P1);
    if (var1 == 0.0) {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576.0 - (float)adc_P;
    p = (p - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((float)dig_P9) * p * p / 2147483648.0;
    var2 = p * ((float)dig_P8) / 32768.0;
    p = p + (var1 + var2 + ((float)dig_P7)) / 16.0;

    //return p;
    return bmp280_read_temperature( );
}

float bmp280_read_altitude(float ref_pressure) {


    // R is the specific gas constant = 287.053 J/(kg K).
    float R = 287.053;

    // T is the absolute temperature in Kelvin = 288.15 K at sea level.
    float T = bmp280_read_temperature( ) + 273.15;

    // g is the acceleration due to gravity = 9.80665 m/s2.
    float g = 9.80665;

    // P is the pressure at a given point at elevation z.
    float P = bmp280_read_pressure( );

    float Po; // Reference value.
    if (ref_pressure == 0){
        Po = startup_pressure;
    } else {
        Po = ref_pressure;
    }

    float elevation = -(R*T/g)*log(P/Po);

    return elevation;

}

float bmp280_read_altitude_2(float ref_hPa) {

    float altitude;

    float pressure = bmp280_read_pressure( ); // in Si units for Pascal
    pressure /= 100;

    altitude = 44330 * (1.0 - pow(pressure / ref_hPa, 0.1903));

    return altitude;
}
