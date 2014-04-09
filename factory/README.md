They are NOT same
=================

"The static factory method is NOT the same as the Factory Method pattern" (c) Effective Java, Joshua Bloch.  
1. Factory Method: "Define an interface for creating an object, but let the classes which implement the interface decide which class to instantiate. The Factory method lets a class defer instantiation to subclasses" (c) GoF.  
2. "Static factory method is simply a static method that returns an instance of a class." (c) Effective Java, Joshua Bloch. Usually this method is inside a particular class.  

The defference:
==============

* The key idea of static factory method is to gain control over object creation and delegate it from constructor to static method. The decision of object to be created is like in Abstract Factory made ouside the method (in common case, but not allways). Example of commonly used static factory methods:
  - valueOf
  - getInstance
  - newInstance
* While the key idea of Factory Method is to delegate decision of what instance of class to create inside Factory Method. E.g. classic Singleton implementation is a special case of static factory method.
