# i2c_htu21d.py 
# Example of reading data from the HTU21D I2C temp/humidity sensor
import serbus, time

htu21d_bus      = 1    # Connected to /dev/i2c-1
htu21d_addr     = 0x40 # HTU21D slave address
htu21d_cmd_temp = 0xe3 # Command to read temperature
htu21d_cmd_rh   = 0xe5 # Command to read relative humidity

bus = serbus.I2CDev(1)
bus.open()

def getTemp():
  # Read the 3 bytes of data:
  msb, lsb, crc = bus.readTransaction(htu21d_addr, htu21d_cmd_temp, 3)
  # The crc (cyclic redundancy check) can be used to verify the data was 
  # received without error - ignore it here
  # Combine the high and low bytes:
  raw_value = (msb<<8) | lsb
  # Clear the two status bits (see datasheet):
  raw_value &= ~0b11
  # Convert to Celsius and return (conversion from datasheet):
  return -46.85 + 175.72 * (raw_value/65536.0)

def getRH():
  msb, lsb, crc = bus.readTransaction(htu21d_addr, htu21d_cmd_rh, 3)
  raw_value = (msb<<8) | lsb
  raw_value &= ~0b11
  # Convert to %RH and return (conversion from datasheet):
  return -6.0 + 125.0 * (raw_value/65536.0)

try:
  while True:
    print
    print "Temperature:       {:0.2f}C".format(getTemp())
    print "Relative humidity: {:0.2f}%".format(getRH())
    time.sleep(1)

except KeyboardInterrupt:
  bus.close()