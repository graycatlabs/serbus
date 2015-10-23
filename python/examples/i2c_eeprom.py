# i2c_read.py
# Write data to an I2C EEPROM (e.g. 24LC256) then reading it back
import serbus, time

eeprom_addr = 0x50 # I2C slave address of EEPROM
start_msb   = 0x00 # High byte of location in EEPROM to write/read
start_lsb   = 0x00 # Low byte of location in EEPROM to write/read

data_to_write = range(10)

# Create an I2CDev instance for interfacing to /dev/i2c-2:
bus = serbus.I2CDev(2)
bus.open()

print "Writing data: {}".format(data_to_write)
# Write the data to the EEPROM:
bus.write(eeprom_addr, [start_msb, start_lsb] + data_to_write)
# The I2C write is asynchronous - give it a bit of time to complete:
time.sleep(0.01) # 10ms should be more than enough

# Read the data from the EEPROM:
bus.write(eeprom_addr, [start_msb, start_lsb])
read_data = bus.read(0x50, len(data_to_write))
print "Data read: {}".format(read_data)

if read_data == data_to_write:
  print "EEPROM write successful!"
else:
  print "EEPROM write failed, is WP enabled?"

bus.close()