# Design-Patterns-in-C

**Practical Design Patterns in C**  

This will be a repository of
* Implement the Design Patterns of **GoF**(Gang of Four) in C.  
* Provide script to auto generate Design Patterns into different code style: C, C++, Java, C#, python-uml

## C oop implement:

```

====================================================
                   private protected public  static
---------------------------+---------+------+-------
method
  virtual                              +
  routine             +                +       +
variable
  member              -                +       +
====================================================
+ have implemented
- can implemented with body-handle pattern, but ...

```

## Quick Start:

```
Make a pattern
--------------

$ vi test_suite.c  <<< comment the others, for example, pattern 'prototype'

	void my_test_suite_open()
	{
		my_test_suite_init(&my_test_suite);

		/*
		extern void inheritance_test(void); inheritance_test();
		extern void builder_test(void); builder_test();
		......
		*/
		extern void prototype_test(void); prototype_test();
	}

$ make target=prototype  <<< build one pattern
$ ./Debug/main	         <<< if Makefile set Debug=y, run this
$ ./Release/main         <<< else run this
$ make clean

Auto Generate class
-------------------

$ cd tools
$ ./autogen_jinja2.py --file json/prototype.json    <<< the generated code in dir ./tools/code/c/prototype

```

## OOP basic:

The oop come from myobj.h:
* each class have it's special v-table, here is the struct ops
* the derive class should also have it's v-table instance, but same type with it's parent
* the derive class's v-table instance should initial with merge with it's parent

### Code Sample Tree

```
$ cd patterns
$ ls
$ tree oop
oop
|-- diagram               <<< the uml class diagram
|   |-- inheritance.py
|   `-- mult_inherit.py
|-- inheritance           <<< sample of inheritance
|   |-- child.c
|   |-- child.h
|   |-- grandgirl.c       <<< grandgirl_init() give the myobj.h MACRO expand code for our review reading
|   |-- grandgirl.h
|   |-- grandson.c
|   |-- grandson.h
|   |-- parent.c
|   |-- parent.h
|   `-- test.c
|-- mult_inherit
|   |-- employee.c
|   |-- employee.h
|   |-- person.c
|   |-- person.h
|   |-- teacher.c
|   |-- teacher.h
|   `-- test.c
`-- README.md

```

## Design Patterns:

* Using patterns can keep our code **loose coupling, cohesive code, and encapsulation**.
* Then we can write maintainable code with a high degree of **Orthogonality**.

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

[PyNSource - UML tool for Python](http://www.andypatterns.com/index.php/products/pynsource/)
[Design Patterns Explained Simply](http://sourcemaking.com/design_patterns)  
[.NET Design Patterns](http://www.dofactory.com/Patterns/Patterns.aspx)  
[Software design pattern](http://en.wikipedia.org/wiki/Design_pattern_%28computer_science%29)  
[Computer Science Design Patterns](http://en.wikibooks.org/wiki/Computer_Science_Design_Patterns)  

## TODOS

oop:
http://www.apwebco.com/gofpatterns/creational/Prototype.html
http://www.codeproject.com/Articles/22769/Introduction-to-Object-Oriented-Programming-Concep
http://www.tutorialspoint.com/cplusplus/cpp_object_oriented.htm
http://oopsconcepts.blogspot.ca/

* myobj.h copy_ops_offset to exclude static, let client initial it's static
* python uml object support
* manual about oop's basic principle
* manual about oop C's implement:
```
scope           catergory
-------------------------------------------------------------------
class           virtual         if-protected -> no candy inline
*object
private         method
protected
*public         routine
                static(class+public)
                var             if-private -> body_impl

ops -> vtable
caps -> DI (construct)
client -> DI (argument)

enable_super
enable_free

```
* move 'static ops' into init-function
* move class from top to bottom where just before the function declare
* framework-lib cooperate with client:
  - caps: template drive
    + can be simple interface which implement by client and used by class, is callback-functions
    + can be simple factory which implement by client and used by class to create itself, such as client's memory implements
  - DI: dependence on abstract interface
  - derive (instance embed): inheritance as-A
  - client-ops: AI (argument injection)
  - call-ops: smaller client-ops
