SPI
===

The :class:`serbus.SPIDev` class provides an API for interfacing with standard GNU/Linux spidev devices.

API
---

.. autoclass:: serbus.SPIDev
   :members:

Examples
--------

Reading data
~~~~~~~~~~~~

.. literalinclude:: ../examples/spi_read.py
    :linenos:
    :language: python
    :lines: 3-

AD7390 digital-to-analog converter
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: ../examples/spi_ad7390.py
    :linenos:
    :language: python
    :lines: 3-
