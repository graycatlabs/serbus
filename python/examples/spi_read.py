# spi_read.py 
# Example of reading SPI data
import serbus

# The chip select connected to the slave device:
cs = 0

# Create a SPIDev instance for interfacing to /dev/spidev0.x devices:
bus = serbus.SPIDev(0)
bus.open()

# Set bus configuration:
bus.setMaxFrequency(cs, 1000000)
bus.setBitsPerWord(cs, 8)
bus.setClockMode(cs, 0)
bus.setCSActiveLow(cs)
bus.setMSBFirst(cs)

# Read a single 8-bit word from the device:
data = bus.read(cs, 1)
print "word received: {:x}".format(data[0])

bus.close()