# Makefile for serbus example programs
#
# Run:
#  $ make
# to build all the example programs.
#
# The examples can also be built individually, e.g.:
#  $ make i2c_htu21d

CC         = gcc
CFLAGS     = -Wall -g
INCLUDES   = -I../include/
I2C_DRIVER = ../src/i2cdriver.c
SPI_DRIVER = ../src/spidriver.c
BIN_DIR    = bin

all: i2c_htu21d spi_ad7390

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

i2cdriver.o: $(I2CDRIVER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(I2C_DRIVER) 

spidriver.o: $(I2CDRIVER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SPI_DRIVER) 

i2c_htu21d: i2c_htu21d.o i2cdriver.o
	$(CC) -o $(BIN_DIR)/i2c_htu21d $^ 

spi_ad7390: spi_ad7390.o spidriver.o
	$(CC) -o $(BIN_DIR)/spi_ad7390 $^ 

clean:
	rm -f *.o bin/*