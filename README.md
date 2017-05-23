# QECommon

It is the common library for **QE Framework**.

1. [Installation](#Installation)
1. [Versioning](#Versioning)
1. [Content](#content)
1. [License](#License)

## Installation

The easiest way to use this library in your code is by [Conan Package Manager](https://www.conan.io).
Please use the project setup that you can find in [QECommon/1.0.0 Conan](https://www.conan.io/source/QECommon/0.1.0/fmiguelgarcia/stable).

## Versioning

This library uses [Semantic Versioning](htpp://semver.org) and internal private implementation to provide a long-term, stable, and reusable binaries.

## Content

These are the most important tools that are provided by this library.

### Class qe::common::Future

This class is a mixture of std::shared_future, std::promise and QFuture. Briefly, it supports:

 - It shares implicitly the future value and promise (like std::shared_future).
 - You can set the value (like a std::promise).
 - You can connect using Qt signal/slot mechanism.  

### Class qe::common::Exception

It is the base class for QE Framework exception. It is able to clone and raise itself, and it is useful to clone exceptions between several thread context.

## License 

This license follows the dual-license pattern that Qt is currently using. A [LGPL 3.0 license](https://www.gnu.org/licenses/lgpl-3.0-standalone.html) for projects that do not need commercial support, and another one, **Commercial license** in other case.

You can find a brief comparison between both licenses in the below table:

 License types                 | LGPLv3 | Commercial 
-------------------------------|--------|------------
 Community Support             | Yes    | Yes
 Official Support Helpdesk     | No     | Yes
 Keep your application private | No     | Yes
 Possible to keep your application private with dynamic linking | Yes | Yes
 No need to provide a relinking mechanism for QE Framework <br> (can always use static linking)  | No | Yes
 No need to provide a copy of license and explicitly<br> acknowledge the use of QE | No | Yes
 No need to make copy of the QE Framework source code <br> available for customers | No | Yes
 Full rights to proprietary QE source code modifications | No | Yes
 Enforce DRM                   | [See LGPLv3 FAQ](https://www.gnu.org/licenses/gpl-faq.html#DRMProhibited) | Yes
 Enforce software patents      | [See LGPLv3 FAQ](https://www.gnu.org/licenses/gpl-faq.html#DRMProhibited) | Yes



