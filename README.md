# Design-Patterns-in-C

**Practical Design Patterns in C**  

This will be a repository of
* Implement the Design Patterns of **GoF**(Gang of Four) in C.  
* Provide script to auto generate Design Patterns into different code style: C, pyNSource(ascii-UML), ... [C++, Java, C#]

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
- can implemented with the "handle/body" idiom, but ...

```

## Quick Start:

```
Make a pattern
--------------

$ make target=prototype     <<< build one pattern
<OR>
$ make target=bridge/shape  <<< build one pattern
$ ./Debug/main              <<< if Makefile set Debug=y, run this, if json.trace=True, output pretty with indent

	=TESTSUITE=BEGIN[Design Pattern TestSuite] total 1 fail 0 at 0
	         test_main_entry
	            color_blue_init()
	            shape_rectangle_init()
	               shape_rectangle::draw()
	                  shape::draw()
	                        color_blue::render()
	                     shape_rectangle::_destructor()
	                        shape::_destructor()
	               shape_rectangle::free()
	=TESTSUITE= [ OK ] 0    Test bridge_shape

	=TESTSUITE= END [Design Pattern TestSuite] total 1 fail 0 at 1

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

### Object
```
struct shape_rectangle *rect;

rect = malloc(sizeof(*rect));
if (!rect) return -1;
shape_rectangle_init(rect);
shape_draw(&rect->shape);
shape_free(&rect->shape);
```

### Class

```
struct shape_ops;
struct shape {
	struct shape_ops *ops;
	struct color * _color;
};
struct shape_ops {
	void (*_destructor)(struct shape *);
	void (*free)(struct shape *);
	void (*draw)(struct shape *);
	struct shape_ops *__super;
};
void shape_init(struct shape *);
```

### Data Abstraction & Encapsulation

```
struct shape_rectangle *rect;

shape_rectangle_init(rect);
shape_draw(&rect->shape);
shape_free(&rect->shape);
```

### Inheritance

```
struct shape_rectangle {
	struct shape shape;
};

void shape_rectangle_init(struct shape_rectangle *);
```

### Polymorphism

```
struct shape_rectangle *rect;
struct shape_circle *circle;

shape_draw(&rect->shape);
shape_draw(&circle->shape);
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
http://www.codeproject.com/Articles/22769/Introduction-to-Object-Oriented-Programming-Concep
http://www.tutorialspoint.com/cplusplus/cpp_object_oriented.htm
http://oopsconcepts.blogspot.ca/

* python uml object support
* manual about oop's basic principle
* manual about oop C's implement:
```
ops -> vtable
caps -> DI (construct)
client -> DI (argument)

```
* framework-lib cooperate with client:
  - caps: template drive
    + can be simple interface which implement by client and used by class, is callback-functions
    + can be simple factory which implement by client and used by class to create itself, such as client's memory implements
  - DI: dependence on abstract interface
  - derive (instance embed): inheritance as-A
  - client-ops: AI (argument injection)
  - call-ops: smaller client-ops
