I2C
===

The :class:`serbus.I2CDev` class provides an API for interfacing with standard GNU/Linux spidev devices. It is instantiated with a bus number corresponding to the I2C bus device file it will use - to communicate with devices on the I2C bus connected to `/dev/i2c-0` you could create the instance :code:`bus = serbus.I2CDev(0)`. 

.. note::
  For more info on I2C (Inter-Integrated Circuit) see https://en.wikipedia.org/wiki/I%C2%B2C


API
---

.. autoclass:: serbus.I2CDev
  :members:

Examples
--------

These are a few examples of using the I2CDev object. They will only work if you have the proper hardware connected to the system running them and your I2C kernel driver loaded. Depending on the system there may be additional required setup as well, such as configuring pin multiplexers on embedded GNU/Linux systems like the `BeagleBone Black`_. 

Reading data
~~~~~~~~~~~~

This example shows how to read a single byte from an I2C device. It is not specific to any particular device.

.. literalinclude:: ../examples/i2c_read.py
  :linenos:
  :language: python
  :lines: 3-

EEPROM memory
~~~~~~~~~~~~~

In this example, a sequence of bytes are written to a `24LC256`_ (or equivalent) I2C EEPROM, then reading them back to verify they have been written.

.. literalinclude:: ../examples/i2c_eeprom.py
  :linenos:
  :language: python
  :lines: 3-

For this to work, the EEPROM's *WP* (write protect) pin must be pulled down to GND to allow writing.

HTU21D humidity sensor
~~~~~~~~~~~~~~~~~~~~~~

This example shows how the `I2CDev` class can be used to measure relative humidity and temperature from the `HTU21D`_ I2C humidity sensor.

.. literalinclude:: ../examples/i2c_htu21d.py
  :linenos:
  :language: python
  :lines: 3-

.. Links:
.. _BeagleBone Black: http://beagleboard.org/BLACK
.. _24LC256: http://www.microchip.com/wwwproducts/Devices.aspx?product=24LC256
.. _HTU21D: http://www.meas-spec.com/product/humidity/HTU21D.aspx