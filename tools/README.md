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

class describe
--------------

```
If no the node, process as default value

"product":{"file":"", "super":""	<<< file default="" auto same as class's name. super default="" auto is parent if have
	"members": {		<<< list members and methods
		"do_it":{"type":"method",	<<< type=(method|virtual|override|routine) | variable. virtual used by base class just have prototype but no implement, override used by sub-class copying protocol from super, method is just routine
			"pre":"void",			<<< function's return type, or variable's type
			"post":"int a, int b"	<<< default="". if have, function's parameters, or variable's array;
		},
		"name":{"type":"variable",	<<< type=variable
			"pre":"char",
			"post":"[32]",
		},
	},
	"enable_super":"True",			<<< default="False". append ops super to implement call-super

	"inheritance": {},				<<< the sub derive classes
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
