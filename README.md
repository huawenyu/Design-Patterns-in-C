Design-Patterns-in-C
====================

Practical Design Patterns in C  
This will be a repository of implement the Design Patterns from **GoF**(Gang of Four) in C.  
* Using patterns can keep our code **loose coupling, cohesive code, and encapsulation**.  
* Then we can write maintainable code with a high degree of **Orthogonality**.  

## Quick Start:

> Make
> > linux $ make			<<< build project  
> > linux $ ./Debug/main	<<< if Makefile set Debug=y, run this  

> Clean
> > linux $ make clean

> Debug
> > linux $ gdb ./Debug/main	<<< Makefile set Debug=y

> Auto Generate class source/header
> > linux $ autogen_jinja2.py

## Update:

Apr 6, 2014: Add init version

## Design Patterns:

1. Creational patterns
  * Factory
    - Static Factory
    - Simple Factory
    - Factory Method
      + GoF
      + two stage
    - Abstract Factory
      + GoF family objects
      + two dimension
      + three dimension
  * Builder
  * Object Pool
  * Prototype
  * Singleton
2. Structural patterns
  * Adapter
  * Bridge
  * Composite
  * Decorator
  * Facade
  * Flyweight
  * Private Class Data
  * Proxy
  * MVC
3. Behavioral patterns
  * Chain of Responsibility
  * Command
  * Interpreter
  * Iterator
  * Mediator
  * Memento
  * Null Object
  * Observer
  * State
  * Strategy
  * Template Method
  * Visitor

The repository contains a folder by each design pattern.

## Contribute

All constructive comments are welcome.
Please feel free to fork and extend existing or add your own examples and send a pull request with your changes!

## License

The MIT License (MIT)

Copyright (c) 2014 Wilson Huawen Yu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## See also & References

[Design Patterns Explained Simply](http://sourcemaking.com/design_patterns)  
[.NET Design Patterns](http://www.dofactory.com/Patterns/Patterns.aspx)  
[Software design pattern](http://en.wikipedia.org/wiki/Design_pattern_%28computer_science%29)  
[Computer Science Design Patterns](http://en.wikibooks.org/wiki/Computer_Science_Design_Patterns)  
