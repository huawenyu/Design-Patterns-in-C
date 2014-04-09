Factory Method and Abstract Factory
===================================

1. Background worker diff
  - AbstractFactory pattern uses composition to delegate responsibility of creating object to another class
  - while Factory design pattern uses inheritance and relies on derived class or sub class to create object.

2. Factory's produce diff
  - With the Factory pattern, you produce implementations (Apple, Banana, Cherry, etc.) of a particular interface -- say, IFruit.
  - With the Abstract Factory pattern, you produce implementations of a particular Factory interface -- e.g., IFruitFactory. Each of those knows how to create different kinds of fruit.

3. Factory's produce diff
  - Factory pattern: The factory produces IProduct-implementations
  - Abstract Factory Pattern: A factory-factory produces IFactories, which in turn produces IProducts :)

Mark Seemann Suggests
=====================

The person who is the author of book "Dependency injection in .net".
* http://stackoverflow.com/questions/1943576/is-there-a-pattern-for-initializing-objects-created-wth-a-di-container/1945023#1945023
* http://stackoverflow.com/questions/1926826/cant-combine-factory-di/1927167#1927167
* http://stackoverflow.com/questions/2168704/wcf-dependency-injection-and-abstract-factory/2168882#2168882
* http://stackoverflow.com/questions/1890341/how-to-set-up-ioc-when-a-key-class-needs-session-or-other-context-specific-varia/1890463#1890463
* http://stackoverflow.com/questions/2180276/how-to-resolve-type-based-on-end-user-configuration-value/2182775#2182775
* http://stackoverflow.com/questions/1706056/strategy-pattern-and-dependency-injection-using-unity/1706352#1706352
* http://stackoverflow.com/questions/1993397/abstract-factory-pattern-on-top-of-ioc/1994455#1994455
* http://stackoverflow.com/questions/1892532/is-this-the-correct-way-to-use-and-test-a-class-that-makes-use-of-the-factory-pat/1892636#1892636
* http://stackoverflow.com/questions/2194629/ddd-book-eric-evans-please-explain-what-is-meant-by-the-factory-should-be-abst/2198504#2198504
* http://stackoverflow.com/questions/2060767/di-container-factory-or-new-for-ephemeral-objects/2060840#2060840
* http://stackoverflow.com/questions/1900358/how-to-unit-test-instance-creation/1900446#1900446
* http://stackoverflow.com/questions/1682925/what-is-the-best-strategy-for-dependency-injection-of-user-input/1686403#1686403
