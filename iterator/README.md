# Iterator design pattern

Take traversal-of-a-collection functionality out of the collection and promote it to "full object status". This simplifies the collection, allows many traversals to be active simultaneously, and decouples collection algo- rithms from collection data structures.

"Every 'container-like' class must have an iterator." It may seem like a violation of encapsulation for a Stack class to allow its users to access its contents directly, but John Lakos' argument is that the designer of a class inevitably leaves something out. Later, when users need addi- tional functionality, if an iterator was originally provided, they can add functionality with "open for extension, closed for modification". Without an iterator, their only recourse is to invasively customize production code. Below, the orginal Stack class did not include an equality operator, but it did include an iterator. As a result, the equality operator could be readily retrofitted.

- Design an "iterator" class for the "container" class
- Add a createIterator() member to the container class
- Clients ask the container object to create an iterator object
- Clients use the first(), isDone(), next(), and currentItem() protocol

