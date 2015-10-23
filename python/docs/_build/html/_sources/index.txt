.. PySerbus documentation master file

PySerbus
======================

The `serbus` Python package provides slim APIs for communicating with I2C and SPI devices on GNU/Linux systems. It interfaces with the `/dev/i2c-N` and `/dev/spidevX.Y` device files provided by standard Linux I2C and SPI drivers.

Why?
====

The serbus library was developed as part of `PyBBIO`_, a Python library for hardware IO support on the `BeagleBone Black`_. There are already some Python packages for SPI and I2C communication, like `spidev`_ and `smbus`_, but neither have very friendly APIs, and they both have some limitations. The `serbus` library was written from scratch for PyBBIO, to provide clean and simple APIs in both `C`_ and Python. 


Contents
========

.. toctree::
  :maxdepth: 2

  install
  I2C
  SPI

* :ref:`genindex`
* :ref:`search`


.. note::
  `PySerbus` requires the `/dev/i2c-N` and `/dev/spidevX.Y` device files be present, and therefore relies on there being I2C and SPI drivers present and loaded. 

  I2C and SPI device files typically require root privileges to access, and therefore any programs using the `serbus` package will need to be run with root permissions.

.. warning::
  Because PySerbus provides direct access to the SPI and I2C buses you could certainly cause some damage with it, e.g. putting an on-board device into a bad or unknown state - use at your own risk!


.. Links:
.. _PyBBIO: https://github.com/graycatlabs/PyBBIO
.. _BeagleBone Black: http://beagleboard.org/BLACK
.. _smbus: https://pypi.python.org/pypi/smbus-cffi
.. _spidev: https://pypi.python.org/pypi/spidev
.. _C: https://graycat.io/docs/serbus