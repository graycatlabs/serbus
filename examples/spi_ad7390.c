/**
 * @file spi_ad7390.c
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief Uses serbus to control an AD7390 DAC.
 * 
 * Requires an SPI Kernel driver be loaded to expose a /dev/spidevX.Y 
 * interface and an AD7390 be connected on the SPI bus.
 */

#include "spidriver.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

#define AD7390_BUS       1        // Connected to /dev/spidev1.X bus
#define AD7390_CS        0        // Using chip select 0 (/dev/spidev1.0)
#define AD7390_FREQ      1000000  // SPI clock frequency in Hz
#define AD7390_BITS      16       // SPI bits per word
#define AD7390_CLOCKMODE 3        // SPI clock mode

static uint8_t running;

/**
 * @brief Sets the given SPI bus per the AD7390's required configuration
 *
 * @param spi_fd SPI bus file descriptor
 */
void AD7390_SPIConfig(int spi_fd) {
  SPI_setMaxFrequency(spi_fd, AD7390_FREQ);
  SPI_setBitsPerWord(spi_fd, AD7390_BITS);
  SPI_setClockMode(spi_fd, AD7390_CLOCKMODE);
  SPI_setCSActiveHigh(spi_fd);
  SPI_setBitOrder(spi_fd, SPI_MSBFIRST);
}

/**
 * @brief Sets the output of the AD7390 in the range 0-4095
 *
 * @param spi_fd SPI bus file descriptor
 * @param value DAC value in range 0-4095
 */
void AD7390_setValue(int spi_fd, uint16_t value) {
  SPI_write(spi_fd, (void*) &value, 1);
}


/**
 * @brief Called when Ctrl+C is pressed - triggers the program to stop.
 */
void stopHandler(int sig) {
  running = 0;
}

int main() {
  int spi_fd, value;
  // Open the SPI device file:
  spi_fd = SPI_open(AD7390_BUS, AD7390_CS);
  if (spi_fd < 0) {
    printf("*Could not open SPI bus %d\n", AD7390_BUS);
    exit(0);
  }
  // Configure the SPI bus:
  AD7390_SPIConfig(spi_fd);

  // Loop until Ctrl+C pressed:
  running = 1;
  signal(SIGINT, stopHandler);
  while(running) {
  // Ramp up from 0V to full-scale:
    for (value=0; value<4095; value++) {
      AD7390_setValue(spi_fd, value);
    }
    // Ramp down from full-scale to 0V:
    for (value=4096; value>0; value--) {
      AD7390_setValue(spi_fd, value);
    }
  }
  // Set DAC output to 0 and close the SPI file descriptor:
  AD7390_setValue(spi_fd, 0);
  SPI_close(spi_fd);
  return 0;
}

