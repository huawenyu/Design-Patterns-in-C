# Why Bridge?

* The Bridge pattern is an application of the old advice, "prefer composition over inheritance".
* It becomes handy when you must subclass different times in ways that are orthogonal with one another, like the following:
```
When:
====
      
              A
           /     \
          Aa      Ab
         / \     /  \
       Aa1 Aa2  Ab1 Ab2

Refactor to:
============
      
           A         N
        /     \     / \
      Aa(N) Ab(N)  1   2
```

Say you must implement a hierarchy of colored shapes.  
You wouldn't subclass Shape with Rectangle and Circle and then subclass Rectangle with RedRectangle, BlueRectangle and GreenRectangle and the same for Circle, would you?  
You would prefer to say that each Shape has a Color and to implement a hierarchy of colors, and that is the Bridge Pattern.  
Well, I wouldn't implement a "hierarchy of colors", but you get the idea...  

```
When:
=====

                   ----Shape---
                  /            \
         Rectangle              Circle
        /         \            /      \
BlueRectangle  RedRectangle BlueCircle RedCircle

Refactor to:
============

          ----Shape---                        Color
         /            \                       /   \
Rectangle(Color)   Circle(Color)           Blue   Red

```

# Proxy, Decorator, Adapter, and Bridge

http://k2java.blogspot.ca/2011/09/difference-between-proxy-decorator.html
Proxy, Decorator, Adapter, and Bridge are all variations on "wrapping" a class.
```
                              Adapter/Wrapper   Decorator
-------------------------------------+--------------+----
Composes "origin" class            True           True
Modifies original interface        True           False
Modifies behavior of interface     False          True
Proxies method calls               True           True
```

## But their uses are different.

### Proxy

* Proxy could be used when you want to lazy-instantiate an object,
* or hide the fact that you're calling a remote service,
* or control access to the object.

### Decorator

* Decorator is also called "Smart Proxy."
* This is used when you want to add functionality to an object, but not by extending that object's type.
* This allows you to do so at runtime.

### Adapter

* Adapter is used when you have an abstract interface,
* and you want to map that interface to another object which has similar functional role, but a different interface.

### Bridge

* Bridge is very similar to Adapter,
* but we call it Bridge when you define both the abstract interface and the underlying implementation.
* I.e. you're not adapting to some legacy or third-party code, you're the designer of all the code but you need to be able to swap out different implementations.

### Facade

* Facade is a higher-level (read: simpler) interface to a subsystem of one or more classes.
* Think of Facade as a sort of container for other objects, as opposed to simply a wrapper.

## their structures are different.

### Proxy and Decorator

* Proxy and Decorator both have the same interface as their wrapped types,
* but the proxy creates an instance under the hood, whereas the decorator takes an instance in the constructor.

### Adapter and Facade

* Adapter and Facade both have a different interface than what they wrap.
* But the adapter derives from an existing interface, whereas the facade creates a new interface.

### Bridge and Adapter

* Bridge and Adapter both point at an existing type.
* But the bridge will point at an abstract type, and the adapter might point to a concrete type.
* The bridge will allow you to pair the implementation at runtime, whereas the adapter usually won't.

# REFS

http://sourcemaking.com/design_patterns/bridge/java/2  
http://stackoverflow.com/questions/319728/when-do-you-use-the-bridge-pattern  

