SPI
===

The :class:`serbus.SPIDev` class provides an API for interfacing with standard GNU/Linux spidev devices. It is instantiated with a bus number corresponding to the `spidev` device file it will use - to communicate with devices on the SPI bus connected to `/dev/spidev0.X` you could create the instance :code:`bus = serbus.SPIDev(0)`. The read/write methods then take a chip select as their first argument, so to read a byte from a device on chip select 1 of spidev0 (`/dev/spidev0.1`) you would call :code:`bus.read(1, 1)`.

.. note::
  For more info on SPI (Serial Peripheral Interface) see https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus

API
---

.. autoclass:: serbus.SPIDev
  :members:

Clock Modes
-----------

The `clock_mode` parameter passed to :func:`~serbus.SPIDev.setClockMode` tells the SPI kernel driver how to drive the clock signal. The SPI spec allows four possible clock configurations, and the required mode for a particular device will be given in its datasheet (sometimes explicitly, but often just shown visually in an SPI timing diagram). The possible modes are:

+--------------+------------------+--------------------------------+
| `clock_mode` | clock idle state | clock edge data is captured on |
+--------------+------------------+--------------------------------+
| 0            | low              | rising edge                    |
+--------------+------------------+--------------------------------+
| 1            | low              | falling edge                   |
+--------------+------------------+--------------------------------+
| 2            | high             | falling edge                   |
+--------------+------------------+--------------------------------+
| 3            | high             | rising edge                    |
+--------------+------------------+--------------------------------+

Examples
--------

These are a few examples of using the SPIDev object. They will only work if you have the proper hardware connected to the system running them and your SPI kernel driver loaded. Depending on the system there may be additional required setup as well, such as configuring pin multiplexers on embedded GNU/Linux systems like the `BeagleBone Black`_.

Reading data
~~~~~~~~~~~~

This example shows how to read a single word from an SPI device. It is not specific to any particular device.

.. literalinclude:: ../examples/spi_read.py
  :linenos:
  :language: python
  :lines: 3-

AD7390 digital-to-analog converter
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This example shows how to control an `AD7390`_ 12-bit SPI DAC (digital-to-analog converter). 

.. literalinclude:: ../examples/spi_ad7390.py
  :linenos:
  :language: python
  :lines: 3-

The AD7390 requires an active high chip slelct signal on its LD pin, and because it uses 12-bit values its word size in larger than the default 8-bits of many SPI modules - both of these are easy set with the included methods.

.. Links:
.. _BeagleBone Black: http://beagleboard.org/BLACK
.. _AD7390: http://www.analog.com/en/products/digital-to-analog-converters/da-converters/ad7390.html