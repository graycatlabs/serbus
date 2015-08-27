from setuptools import setup, Extension

extensions = [
  Extension("serbus.spidev",
            ["serbus/pyspidev.c",
             "src/spidriver.c"],
            include_dirs=["include"]),

  Extension("serbus.i2cdev",
            ["serbus/pyi2cdev.c",
             "src/i2cdriver.c"],
            include_dirs=["include"]),
  ]

setup(name="pyserbus",
      version="1.0",
      description="A Python package for I2C and SPI serial bus communication on GNU/Linux systems.",
      long_description=open("README.md").read(),
      author="Alexander Hiam",
      author_email="alex@graycat.io",
      license="MIT License",
      url="https://github.com/graycatlabs/serbus",
      download_url="",
      keywords=["I2C", "SPI", "serial", "Linux"],
      packages=["serbus"],
      ext_modules=extensions, 
      classifiers=[
        "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX :: Linux",
        "Topic :: Software Development :: Embedded Systems",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: System :: Hardware"
      ])
