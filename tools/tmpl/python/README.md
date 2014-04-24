Problem
=======

When we implement oop using c, there have so many repeated code temple,  
Maybe the frame code can be autogen. Ok, This is the one.  

Solution
========

1. Using json to describe our class
2. Create template code using jinja2 Template Engine
3. Using jinja2 replace&combine the json-define-class-info and the Template
4. Check Result

QuickStart
==========
Run
---

```
$ cd tools  
$ ./autogen_jinja2.py --file json/factory-method.json  
```

Refs
====

http://www.tutorialspoint.com/python/python_classes_objects.htm  
