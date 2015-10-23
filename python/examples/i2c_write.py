# i2c_read.py
# Example of reading I2C data
import serbus

# Create an I2CDev instance for interfacing to /dev/i2c-1:
bus = serbus.I2CDev(1)
bus.open()

# Write a couple bytes to the slave device with address 0x50:
bus.write(0x50, [0x00, 0x01])

bus.close()