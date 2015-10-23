# spi_ad7390.py 
# Example of controlling an AD7390 DAC
import serbus, time

# The SPI bus and chip select the AD7390 is connected to:
spi_bus = 1
cs      = 0
# /dev/spidev1.0

bus = serbus.SPIDev(spi_bus)
bus.open()

# Set bus configuration, as described in the AD7390 datasheet:
bus.setMaxFrequency(cs, 1000000)
bus.setBitsPerWord(cs, 16)
bus.setClockMode(cs, 3)
bus.setCSActiveHigh(cs)
bus.setMSBFirst(cs)

try:
  while True:
    # Ramp up from 0V to full-scale:
    for i in range(0, 2**12, 100):
      bus.write(cs, [i])
      time.sleep(0.01)

    # Ramp down from full-scale to 0V:
    for i in range(2**12-1, 0, -100):
      bus.write(cs, [i])
      time.sleep(0.01)

except KeyboardInterrupt:
  bus.close()