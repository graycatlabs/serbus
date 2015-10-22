/*******************************************************************************
 * Copyright (c) 2015 - Gray Cat Labs - https://graycat.io
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/**
 * @file spidriver.h
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief A basic driver for controlling Linux spidev interfaces.
 * 
 * Requires an SPI Kernel driver be loaded to expose /dev/spidevX.Y interfaces 
 * which provide the standard Linux SPI ioctls. This driver is really just an 
 * ioctl wrapper.
 */

#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include <stdint.h>
#include <linux/spi/spidev.h>

/**
 * @brief Opens the /dev/spidev[bus].[cs] interface.
 *
 * @param bus SPI bus number
 * @param cs chip select number
 * @return Returns the file descriptor for the spidev interface.
 */
int SPI_open(uint8_t bus, uint8_t cs);

/**
 * @brief Closes the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 */
void SPI_close(int spidev_fd);

/**
 * @brief Reads from the given spidev interface.
 *
 * Reads \p n_words from the given spidev interface and puts them into the 
 * given buffer.
 *
 * @param spidev_fd spidev file descriptor
 * @param rx_buffer pointer to an array, already initialized to the required 
 *        size
 * @param n_words the number of words to read into tx_buffer
 *
 * @return Returns the number of bytes read, or -1 if unable to read from 
 *         interface 
 */
int SPI_read(int spidev_fd, void *rx_buffer, int n_words);

/**
 * @brief Writes to the given spidev interface.
 *
 * Writes \p n_words from the given buffer to the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 * @param tx_buffer pointer to an array containing the words to be transmitted
 * @param n_words the number of words to be transmitted from tx_buffer
 *
 * @return Returns the number of bytes written, or -1 if unable to write 
 *         interface 
 */
int SPI_write(int spidev_fd, void *tx_buffer, int n_words);

/**
 * @brief Writes to and reads from the given spidev interface simultaneously.
 *
 * Writes n_words from the given tx buffer to the given spidev interface, while 
 * simultaneously reading words into the given rx buffer.
 *
 * @param spidev_fd spidev file descriptor
 * @param tx_buffer pointer to an array containing the words to be transmitted
 * @param rx_buffer pointer to an array, already initialized to the required 
 *        size
 * @param n_words the number of words to be transferred
 *
 * @return Returns the number of bytes transferred, or -1 if unable to write 
 *         interface 
 */
int SPI_transfer(int spidev_fd, void *tx_buffer, void *rx_buffer, int n_words);

/**
 * Passed to #SPI_setBitOrder to specify the bit order to use for subsequent
 * SPI transfers.
 */
typedef enum { 
  SPI_MSBFIRST, ///< Most significant bit first
  SPI_LSBFIRST  ///< Least significant bit first
} SPI_bit_order;

/**
 * @brief Sets the bit order of the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 * @param bit_order one of SPI_MSBFIRST or SPI_LSBFIRST
 *
 * @return Returns 0 if successful, or -1 if error
 */
 int SPI_setBitOrder(int spidev_fd, SPI_bit_order bit_order);

/**
 * @brief Sets the number of bits per word for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 * @param bits_per_word number of bits per word
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_setBitsPerWord(int spidev_fd, uint8_t bits_per_word);

/**
 * @brief Gets the number of bits per word for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns bits per word, or -1 if error
 */
int SPI_getBitsPerWord(int spidev_fd);

/**
 * @brief Sets the maximum clock frequency for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 * @param frequency maximum clock frequency
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_setMaxFrequency(int spidev_fd, uint32_t frequency);

/**
 * @brief Gets the maximum clock frequency for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns the frequency, or -1 if error
 */
int SPI_getMaxFrequency(int spidev_fd);

/**
 * @brief Sets the clock mode for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 * @param clock_mode one of SPI_MODE_0, SPI_MODE_1, SPI_MODE_2 or SPI_MODE_3
 *
 * @return Returns 0 if successful, -1 if error
 */
int SPI_setClockMode(int spidev_fd, uint8_t clock_mode);

/**
 * @brief Gets the clock mode for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns  the clock mode, or -1 if error
 */
int SPI_getClockMode(int spidev_fd);

/**
 * @brief Sets the given spidev interface's cs signal to be active low.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_setCSActiveLow(int spidev_fd);

/**
 * @brief Sets the given spidev interface's cs signal to be active high.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_setCSActiveHigh(int spidev_fd);

/**
 * @brief Enables the given spidev interface's cs output.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_enableCS(int spidev_fd);

/**
 * @brief Disables the given spidev interface's cs output.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_disableCS(int spidev_fd);

/**
 * @brief Puts the given spidev interface in loopback mode.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_enableLoopback(int spidev_fd);

/**
 * @brief Disables loopback mode for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_disableLoopback(int spidev_fd);

/**
 * @brief Enables 3-wire SPI mode for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_enable3Wire(int spidev_fd);

/**
 * @brief Enables 4-wire SPI mode for the given spidev interface.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_disable3Wire(int spidev_fd);

/**
 * @brief Sets the full SPI mode byte for the given spidev interface.
 * 
 * Used to set things like the clock mode, SC active state, etc., and shouldn't
 * typically need to be called directly.
 *
 * @param spidev_fd spidev file descriptor
 * @param mode SPI mode byte
 *
 * @return Returns 0 if successful, or -1 if error
 */
int SPI_setMode(int spidev_fd, uint8_t mode);

/**
 * @brief Gets and returns the full SPI mode byte for the given spidev 
 *        interface.
 *
 * Encodes current settings like the clock mode, SC active state, etc., and 
 * shouldn't typically need to be called directly.
 *
 * @param spidev_fd spidev file descriptor
 *
 * @return Returns SPI mode if successful, or -1 if error
 */
int SPI_getMode(int spidev_fd);

#endif // _SPI_DRIVER_H_