/**
 * @file i2c_htu21d.c
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief Uses serbus to get RH and temperature data from an HTU21D. 
 * 
 * Requires an I2C Kernel driver be loaded to expose a /dev/i2c-N interface
 * and an HTU21D be connected on the I2C bus.
 */

#include "i2cdriver.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define HTU21D_BUS      1    // Connected to /dev/i2c-1
#define HTU21D_ADDR     0x40 // HTU21D slave address
#define HTU21D_CMD_TEMP 0xe3 // Command to read temperature
#define HTU21D_CMD_RH   0xe5 // Command to read relative humidity

/**
 * @brief Reads and returns the current temperature from the HUT21D
 *
 * @param i2c_fd I2C bus file descriptor
 *
 * @return the current temperature in Celsius
 */
float getTemp(int i2c_fd) {
  uint8_t rx_buffer[3];
  int raw_value;
  // Set the slave address:
  if (I2C_setSlaveAddress(i2c_fd, HTU21D_ADDR) < 0) {
    printf("*Could set slave address to %d\n", HTU21D_ADDR);
    exit(0);
  }
  // Read the 3 bytes of data:
  I2C_readTransaction(i2c_fd, HTU21D_CMD_TEMP, (void*) rx_buffer, 3);
  // The crc (cyclic redundancy check) can be used to verify the data was 
  // received without error - ignore it here
  // Combine the high and low bytes:
  raw_value = (rx_buffer[0]<<8) | rx_buffer[1];
  // Clear the two status bits (see datasheet):
  raw_value &= ~0b11;
  // Convert to Celsius and return (conversion from datasheet):
  return -46.85 + 175.72 * (((float)raw_value)/65536.0);
}

/**
 * @brief Reads and returns the current humidity from the HUT21D
 *
 * @param i2c_fd I2C bus file descriptor
 *
 * @return the current temperature in Celsius
 */
float getRH(int i2c_fd) {
  uint8_t rx_buffer[3];
  int raw_value;
  if (I2C_setSlaveAddress(i2c_fd, HTU21D_ADDR) < 0) {
    printf("*Could set slave address to %d\n", HTU21D_ADDR);
    exit(0);
  }
  I2C_readTransaction(i2c_fd, HTU21D_CMD_RH, (void*) rx_buffer, 3);
  raw_value = (rx_buffer[0]<<8) | rx_buffer[1];
  raw_value &= ~0b11;
  // Convert to %RH and return (conversion from datasheet):
  return -6.0 + 125.0 * (raw_value/65536.0);
}

int main() {
  int i2c_fd;
  float temp, rh;
  // Open the I2C device file:
  i2c_fd = I2C_open(HTU21D_BUS);
  if (i2c_fd < 0) {
    printf("*Could not open I2C bus %d\n", HTU21D_BUS);
    exit(0);
  }
  // Read and print the current temp and rh:
  temp = getTemp(i2c_fd);
  rh = getRH(i2c_fd);
  printf("Temp : %5.2fC\n", temp);
  printf("RH   : %5.2f%%\n", rh);
  // Close the I2C file descriptor:
  I2C_close(i2c_fd);
  return 0;
}
