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
		"do_it":{"type":"method",	<<< type=(method|virtual|override) | variable. virtual used by base class just have protocol but no implement, override used by sub-class copying protocol from super, method is just routine
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

Vim Plugin
==========

https://github.com/Glench/Vim-Jinja2-Syntax.git

Refs
====

http://kagerato.net/articles/software/libraries/jinja-quickstart.html
