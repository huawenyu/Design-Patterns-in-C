<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [Design-Patterns-in-C](#design-patterns-in-c)
  - [C oop implement:](#c-oop-implement)
- [](#)
- [  member           -                +       +](#member-----------------------------------)
  - [Quick Start:](#quick-start)
  - [Make a pattern](#make-a-pattern)
  - [Auto Generate class](#auto-generate-class)
  - [OOP basic:](#oop-basic)
    - [Object](#object)
    - [Class](#class)
    - [Data Abstraction & Encapsulation](#data-abstraction-&-encapsulation)
    - [Inheritance](#inheritance)
    - [Polymorphism](#polymorphism)
  - [Design Patterns:](#design-patterns)
  - [Contribute](#contribute)
  - [License](#license)
  - [See also & References](#see-also-&-references)
  - [TODOS](#todos)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Design-Patterns-in-C

**Practical Design Patterns in C**  

This will be a repository of
* Implement the Design Patterns of **GoF**(Gang of Four) in C.  
* (Version 1) Provide script to auto generate Design Patterns into different code style: C, pyNSource(ascii-UML), ... [C++, Java, C#]
* (Version 2) Reference from [Design Patterns in PHP](https://github.com/kamranahmedse/design-patterns-for-humans)

## C oop implement:

```python

======================================================
                private protected public  static  pure
-------------------+--------+-------+--------+-----+--
constructor        +                +       +
destructor
  virtual                           +
methods
  virtual                           +              +
  routine          +                +       +
variables
  member           -                +       +
=================================================
+ have implemented
- can implemented with the "handle/body" idiom, but ...

```

## Quick Start:

```sh
Make a pattern
--------------

$ cd auto-gen
$ make
$ make runall
$ make clean_all

Auto Generate class
-------------------

$ cd tools
$ python gencode.py --file json/prototype.json > log   <<< the generated code in dir ./tools/code/c/prototype

```

## OOP basic:

The oop come from myobj.h:
* each class have it's special v-table, here is the struct ops
* the derive class should also have it's v-table instance, but same type with it's parent
* the derive class's v-table instance should initial with merge with it's parent

### Object
```c
struct shape_rectangle *rect;

rect = malloc(sizeof(*rect));
if (!rect) return -1;
shape_rectangle_init(rect);
shape_draw(&rect->shape);
shape_free(&rect->shape);
```

### Class

```c
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

```c
struct shape_rectangle *rect;

shape_rectangle_init(rect);
shape_draw(&rect->shape);
shape_free(&rect->shape);
```

### Inheritance

```c
struct shape_rectangle {
	struct shape shape;
};

void shape_rectangle_init(struct shape_rectangle *);
```

### Polymorphism

```c
struct shape_rectangle *rect;
struct shape_circle *circle;

shape_draw(&rect->shape);
shape_draw(&circle->shape);
```
## Another OOP style (OOC by A.T. Schreiner)

```c
// file: OOC.h
struct Class {
    size_t size;
    void *(* ctor) (void *self, va_list *app);
};

void *new(const void *_class, ...) {
    const struct Class *class = _class;     // assign the address of `struct String` class
    void *p = calloc(1, class->size);       // allocate the sizeof(struct String);

    assert(p);
    *(const struct Class **)p = class;      // Force the conversion of p and set the argument `class` as the value of this pointer.
    if(class->ctor) {
        va_list ap;
        va_start(ap, _class);
        p = class->ctor(p, &ap);        // Now what is `p` here, a `struct String` or `struct Class`.
                                        // and if it is `struct Class` then how it convert to `struct String` in `String_ctor` function 
                                        // given below.
        va_end(ap);
    }
    return p;
}


// file: mystring.h

#include "OOC.h"

struct String {
    const void *class;  // must be first
    char *text;
};

static void *String_ctor(void *_self, va_list *app) {
    struct String *self = _self;        
    const char *text = va_arg(*app, const char *);

    self->text = malloc(strlen(text) + 1);
    assert(self->text);
    strcpy(self->text, text);
    return self;
}

// Initialization
static const struct Class _String  = {
    sizeof(struct String),
    String_ctor
};

const void *String = &_String;



// file: main.c

#include "mystring.h"

int main(void)
{
    void *a = new(String, "some text");
}
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
  * Handle Body Idiom
  * Proxy
  * MVC
3. Behavioral patterns
  * Chain of Responsibility
  * Command
  * Interpreter
  * Iterator
  * Mediator
  * Observer
  * State
  * Strategy
  * Template Method
  * Visitor

The repository contains a folder by each design pattern.

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
  t_ops -> half class level vtable
caps -> DI - callback (construct)
cbs -> DI - client/request callback (argument)

```

* [The SOLID principles of object-oriented programming](https://en.wikipedia.org/wiki/SOLID)
  - DIP: Dependence Inversion Principle, dependence on abstract interface
    - DI: [Dependency Injection](https://en.wikipedia.org/wiki/Dependency_injection)
    - AI: argument injection
    - IoC: Inversion of Control
      + Interface injection
      + Constructor injection
      + Setter injection
      + Method injection
  - LSP: Liskov Substitution Principle
  - SRP: Single Responsibility Principle
  - OCP: Open Close Principle
  - ISP: Interface Segregation Principle
  - LoD: Least Knowledge Principle

* framework-lib cooperate with client:
  - caps: template drive
    + can be simple interface which implement by client and used by class, is callback-functions
    + can be simple factory which implement by client and used by class to create itself, such as client's memory implements
  - derive (instance embed): LSP, inheritance as-A
  - client/request-cbs: AI,MI, one kind of client/request ops, 
  - call-ops: smaller client-ops
 

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
