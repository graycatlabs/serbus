# i2c_read.py
# Example of reading I2C data
import serbus

# Create an I2CDev instance for interfacing to /dev/i2c-1:
bus = serbus.I2CDev(1)
bus.open()

# Read a single byte from the slave device with address 0x50:
data = bus.read(0x50, 1)
print "byte received: {:x}".format(data[0])

bus.close()