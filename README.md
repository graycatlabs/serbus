# Serbus

Copyright (c) 2015 - Gray Cat Labs - https://graycat.io

Serbus provides basic C APIs for the I2C and SPI serial bus protocols on 
GNU/Linux based systems, as well as a Python package built on top of them. 

It's really just a wrapper for the ioctl commands provided by the standard Linux 
I2C and SPI drivers, so it should be pretty universal. That said, I've currently
only tested it extensively on the BeagleBone Black, so use it at your own risk! 
(And let me know if it's working for you on another system)

* Source code: https://github.com/graycatlabs/serbus/
* C API documentation: https://graycat.io/docs/serbus/

## Contributing

Have something to contribute? Great! This project follows the Contributor 
Covenant Code of Conduct, so be sure to read `code_of_conduct.md`.

## License

Released under the MIT license.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.