Problem
=======

Assume we have some class Service, that has two dependencies: an IDatabaseAccessHandler and an IFileAccessHandler which can be disiced at first.  
Now this class Service also has other dependencies, such as functional dependencies like an IDomain which be decised at runtime.  
* I'd also need to pass a IDomain object in the constructor.
* How to instantiating the class Service in a elegant way?

