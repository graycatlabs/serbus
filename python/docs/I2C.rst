I2C
===

The :class:`serbus.I2CDev` class provides an API for interfacing with standard GNU/Linux spidev devices.

API
---

.. autoclass:: serbus.I2CDev
    :members:

Examples
--------

Reading data
~~~~~~~~~~~~

.. literalinclude:: ../examples/i2c_read.py
    :linenos:
    :language: python
    :lines: 3-

EEPROM memory
~~~~~~~~~~~~~

.. literalinclude:: ../examples/i2c_eeprom.py
    :linenos:
    :language: python
    :lines: 3-


HTU21D humidity sensor
~~~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: ../examples/i2c_htu21d.py
    :linenos:
    :language: python
    :lines: 3-
