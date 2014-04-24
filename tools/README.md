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

The files like following:
```
➜  Design-Patterns-in-C git:(master) tree tools
tools
|-- autogen_jinja2.py   <<< the entry script
|-- const.py            <<<    implement const
|-- odict.py            <<<    implement order diction
|-- json                <<< the pattern describe files using json
|   `-- factory-method.json
|-- README.md
`-- tmpl                <<< the templates using jinja2
    `-- c               <<< used for generate C code
        |-- c.jinja     <<<      for code {class-name}.c
        |-- _header.jinja <      beginwith "_" means no-render, normal used by other template or as super template
        `-- h.jinja     <<<      for code {class-name}.h
```

1. Using Json describe pattern
------------------------------

```
$ cd tools  
$ cat json/factory-method.json  

1.	{
2.	"classes": {
3.		"product":{
4.			"members": [
5.				["virtual", "do_it","void", "int a, int b"],
6.				["var",     "name", "char", "[32]"]
7.			],
8.			"enable_super":"False",
9.	
10.			"inheritance": {
11.				"concrete_product_1":{
12.					"members": [ ["override", "<ALL>"] ]
13.				},
14.				"concrete_product_2":{
15.					"members": [ ["override", "<ALL>"] ]
16.				}
17.			}
18.		},
19.	
20.		"product_factory":{
21.			"members": [
22.				["virtual", "create", "struct product*"],
23.				["routine", "do_it", "void" ]
24.			],
25.	
26.			"inheritance": {
27.				"product_factory_1":{
28.					"members": [ ["override", "<ALL>"] ]
29.				},
30.				"product_factory_2":{
31.					"members": [ ["override", "<ALL>"] ]
32.				}
33.			}
34.		}
35.	}
36.	}

```

2. Create template code using jinja2 Template Engine
----------------------------------------------------

```
$ tree tmpl       
tmpl
`-- c
    |-- _source.jinja
    |-- c.jinja
    |-- _header.jinja
    `-- h.jinja
```

3. Using jinja2 replace&combine the json-define-class-info and the Template
---------------------------------------------------------------------------

```
$ ./autogen_jinja2.py --file json/factory-method.json 
```

4. Check Result
---------------

```
$ tree autogen_code 
autogen_code
`-- factory_method
    |-- concrete_product_1.c
    |-- concrete_product_1.h
    |-- concrete_product_2.c
    |-- concrete_product_2.h
    |-- product.c
    |-- product_factory_1.c
    |-- product_factory_1.h
    |-- product_factory_2.c
    |-- product_factory_2.h
    |-- product_factory.c
    |-- product_factory.h
    `-- product.h
```

QuickStart
==========
Run
---

```
$ cd tools  
$ ./autogen_jinja2.py --file json/factory-method.json  
```

Debug
-----
```
python /usr/lib64/python2.7/pdb.py autogen_jinja2.py  
(Pdb) break            # set breakpoint  
(Pdb) run -i 'json/factory-method.json'  
(Pdb) c                # continue util breakpoint  
(Pdb) s                # step into  
(Pdb) n                # next  
(Pdb) util 112         # continue util the line number  
```

Requirement
===========

```
$ sudo pip install jinja2  
<or>
$ sudo easy_install jinja2
```

Vim Plugin
==========

https://github.com/Glench/Vim-Jinja2-Syntax.git  
https://github.com/elzr/vim-json.git  

Refs
====

http://kagerato.net/articles/software/libraries/jinja-quickstart.html  
http://jinja.pocoo.org/docs/templates/  
http://jinja.pocoo.org/docs/templates/#whitespace-control  
http://www.dotnetperls.com/dictionary-python  
http://pymotw.com/2/json/  
