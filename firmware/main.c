#include "ch.h"
#include "hal.h"

#include "usbcfg.h"
#include "string.h"
#include "shell.h"
#include "chprintf.h"
#include <stdbool.h>
//#include "math.h"

#include "data_types.h"
#include "i2c_functions.h"
#include "usb_functions.h"
#include "buffer.h"
#include "rx_requests.h"
#include "hw_setup.h"
#include "ssd1331.h"

// Sensor headers.
#include "bmp280.h"
#include "mpu6050.h"
#include "ISL29125.h"
#include "VEML6070.h"
#include "TCS3472.h"
#include "mpu9250.h"


int16_t XaccelRaw, YaccelRaw, ZaccelRaw;
int16_t XgyroRaw, YgyroRaw, ZgyroRaw;
double XaccelAngle, YaccelAngle;

static bool initSensors();
static bool start_MPU9250();

// LED blinker thread, times are in milliseconds.
static THD_WORKING_AREA(blinker_thread_wa, 128);
static THD_FUNCTION(blinker_thread, arg) {

  (void)arg;
  chRegSetThreadName("blinker_thread");

  while (true) {
    systime_t time;
    time = serusbcfg.usbp->state == USB_ACTIVE ? 250 : 500;
    palClearLine(LINE_LED6);
    chThdSleepMilliseconds(time);
    palSetLine(LINE_LED6);
    chThdSleepMilliseconds(time);
  }
}


// Application entry point.
int main() {

  // System initializations.
  // - HAL initialization, this also initializes the configured device drivers
  //   and performs the board-specific initializations.
  // - Kernel initialization, the main() function becomes a thread and the
  //   RTOS is active.
  halInit();
  chSysInit();

  hw_initialization( );   // USB, SPI, GPIO
  i2c_initialization( );  // I2C, contains functions for sensors.


  // Sensor initializations.
  bmp280_initialize(BMP280_ADDRESS_LOW);  // Pressure     0x76
  //initSensors( );                       // MPU6050      0x68
  //palSetLine(LINE_LED3);
  ssd1331_initialize( );                  // OLED
  //ISL29125_initialize( );               // RGB          0x44
  //palSetLine(LINE_LED4);
  //VEML6070_initialize(3);               // UV           0x38, 0x39
  //TCS3472_initialize( );                // RGB          0x29


  // MPU9250
  uint8_t I_am = 0;
  I2C_read_byte(MPU9250_ADDRESS, WHO_AM_I_MPU9250, &I_am);
  if (I_am == 0x71){
    palSetLine(LINE_LED6);
  }

  I2C_read_byte(AK8963_ADDRESS, WHO_AM_I_AK8963, &I_am);
  if (I_am == 0x48){
    palSetLine(LINE_LED5);
  }

  for (int j = 0; j < 10; j++){
    palToggleLine(LINE_LED3);
    chThdSleepMilliseconds(100);
  }
  palClearLine(LINE_LED3);
  palClearLine(LINE_LED4);


  start_MPU9250( );
  for (int j = 0; j < 50; j++){
    palToggleLine(LINE_LED6);
    chThdSleepMilliseconds(100);
  }

  I2C_read_byte(MPU9250_ADDRESS, WHO_AM_I_MPU9250, &I_am);
  if (I_am == 0x71){
    palSetLine(LINE_LED3);
  }

  I2C_read_byte(AK8963_ADDRESS, WHO_AM_I_AK8963, &I_am);
  if (I_am == 0x48){
    palSetLine(LINE_LED4);
  }

  for (int j = 0; j < 10; j++){
    palToggleLine(LINE_LED6);
    chThdSleepMilliseconds(100);
  }

  palClearLine(LINE_LED3);
  palClearLine(LINE_LED4);

  // Creates the blinker thread
  chThdCreateStatic(blinker_thread_wa, sizeof(blinker_thread_wa), NORMALPRIO + 1, blinker_thread, NULL);

  // Shell manager initialization
  //shellInit();

  unsigned char tx_buffer[64];
  unsigned char i2c_buffer[64];
  // unsigned char g[2];
  // unsigned char r[2];
  // unsigned char b[2];
  int32_t tx_length;

  tx_buffer[0] = START_BYTE;
  tx_buffer[1] = COM_PACKAGE_IMU;
  tx_buffer[2] = 0;

  float pressure;

  int16_t mpu9250_buf[10];

  while (TRUE){

    // MPU6250
    //  tx_buffer[1] = COM_PACKAGE_IMU;
    //  tx_length = 3;
    //
    //  get_data_IMU(tx_buffer, &tx_length);
    //  tx_buffer[2] = (unsigned char)tx_length-3;
    //  streamWrite(&SDU1, tx_buffer, tx_length);
    //
    //  chThdSleepMilliseconds(20);


    // BMP
    //  tx_buffer[1] = COM_PACKAGE_BAROMETER_BMP280;
    //  tx_length = 3;
    //  pressure = bmp280_read_pressure( );
    //  buffer_append_float32(tx_buffer, pressure, 1, &tx_length);
    //  tx_buffer[2] = 4;
    //  streamWrite(&SDU1, tx_buffer, tx_length);
    //
    //  chThdSleepMilliseconds(20);


    // ISL29125
    //  tx_buffer[1] = COM_PACKAGE_ISL29125;
    //  tx_length = 3;
    //  //ISL29125_get_GRB();
    //
    //  if(I2C_read_bytes(ISL29125_ADDR, ISL29125_GREEN_L, i2c_buffer, 6)){
    //      //palSetLine(LINE_LED4);
    //  } else {
    //      //palSetLine(LINE_LED5);
    //  }
    //
    //  buffer_append_int16(tx_buffer, i2c_buffer[0], &tx_length);
    //  buffer_append_int16(tx_buffer, i2c_buffer[2], &tx_length);
    //  buffer_append_int16(tx_buffer, i2c_buffer[4], &tx_length);
    //  tx_buffer[2] = 6;
    //
    //  streamWrite(&SDU1, tx_buffer, tx_length);
    //
    //  chThdSleepMilliseconds(20);


    // MPU9250
    tx_buffer[1] = COM_PACKAGE_MPU9250;
    tx_length = 3;
    if(get_accelerometer_data(&mpu9250_buf[0])){
        palToggleLine(LINE_LED3);
    }

    if(get_gyroscope_data(&mpu9250_buf[3])){
        palToggleLine(LINE_LED4);
    }

    if(get_magnetometer_data(&mpu9250_buf[6])){
        palToggleLine(LINE_LED5);
    }

    //get_temperature_data(&mpu9250_buf[9]);

    buffer_append_int16(tx_buffer, mpu9250_buf[0], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[1], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[2], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[3], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[4], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[5], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[6], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[7], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[8], &tx_length);
    buffer_append_int16(tx_buffer, mpu9250_buf[9], &tx_length);
    tx_buffer[2] = 20;

    streamWrite(&SDU1, tx_buffer, tx_length);
    chThdSleepMilliseconds(50);


    // I2CdevreadBytes(ISL29125_ADDR, ISL29125_RED_L, 2, &r, 0);
    // I2CdevreadBytes(ISL29125_ADDR, ISL29125_GREEN_L, 2, &g, 0);
    // I2CdevreadBytes(ISL29125_ADDR, ISL29125_BLUE_L, 2, &b, 0);

    // I2CdevreadByte(devAddr, regAddr, data, timeout)
    // I2CdevreadBytes(devAddr, regAddr, 6, data, timeout);
  }
}


// Removing the MPU6050 later
static bool initSensors(){

  bool sts = 0;

  // MPU6050, AD0 is connected to VCC
  MPU6050(MPU6050_ADDRESS_AD0_LOW);

  // Test connection
  sts = MPUtestConnection();
  if (!sts) return FALSE;

  MPUreset();
  MPUresetSensors();
  chThdSleepMilliseconds(100);
  MPUinitialize();
  chThdSleepMilliseconds(100);

  // chprintf((BaseSequentialStream *)&SDU1, "A: X-axis: %d mg\r\n", XaccelRaw);
  // chprintf((BaseSequentialStream *)&SDU1, "G: X-axis: %d mg\r\n", XgyroRaw);

  return TRUE;
}



static bool start_MPU9250(){

  float gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0};
  float mpu_deviation[6];


  MPU9250_self_test(&mpu_deviation[0]);
  MPU9250_calibrate(&gyroBias[0], &accelBias[0]);
  init_MPU9250( );

  // if(init_MPU9250( )){
  //   palSetLine(LINE_LED5);
  // }

  // Factory mag calibration and mag bias
  float magCalibration[3] = {0, 0, 0}; //, magbias[3] = {0, 0, 0};
  init_AK8963(&magCalibration[0]);

  return true;
}
