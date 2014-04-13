Problem
=======

When we implement oop using c, there have so many repeated code temple,
Maybe the frame code can be autogen. Ok, This is the one.

Solution
========

1. Using json to describe our class
2. Loading json file into python's Dictionary
3. Create template code using jinja2 Template Engine
4. Using jinja2 replace&combine the json-define-class-info and the Template

Syntax: Json describe pattern
=============================

class describe using Json
-------------------------

```
If no the node, process as default value

{
"namespace":"factory_method",
"path":"factory_method",
"classes": {
	"product":{"file":"", "super":"",
		"members": [
			["virtual",  "void", "do_it", "int a, int b"],
			["variable", "char", "name", "[32]"]
		],
		"enable_super":"True",

		"inheritance": {
			"concrete_product_1":{
				"members": [
					["override", "do_it"]
				]
			},
			"concrete_product_2":{
				"members": [
					["override", "do_it"]
				]
			}
		}
	},

	"product_factory":{
		"members": [
			["virtual", "struct product*", "create"],
			["method",  "void", "do_it"]
		],

		"inheritance": {
			"product_factory_1":{
				"members": [
					["override", "create"]
				]
			},
			"product_factory_2":{
				"members": [
					["override", "create"]
				]
			}
		}
	}
}
}
```
Requirement
===========
> linux $ sudo pip install jinja2
> <or>
> linux $ sudo easy_install jinja2

QuickStart
==========
Run
---
./autogen_jinja2.py -i json/factory-method.json

Debug
-----
python /usr/lib64/python2.7/pdb.py autogen_jinja2.py
(Pdb) break            # set breakpoint
(Pdb) run -i 'json/factory-method.json'
(Pdb) c                # continue util breakpoint
(Pdb) s                # step into
(Pdb) n                # next
(Pdb) util 112         # continue util the line number

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
