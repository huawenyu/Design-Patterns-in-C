# Problem

When we implement oop using c, there have so many repeated code temple,  
Maybe the frame code can be autogen. Ok, This is the one.  

# Solution

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

## Using Json describe pattern

### JSON Comment
A wrapper to JSON parsers allowing comments, multiline strings and trailing commas  
https://pypi.python.org/pypi/jsoncomment/0.2.3  
- Single and Multi line comments
- Multi line data strings
- Trailing comma in objects and arrays

#### Comments

- # and ; are for single line comments
- /* and */ enclose multiline comments
- Inline comments are not supported

#### Multiline strings

Any string can be multiline, even object keys.

- Multiline strings start and end with """, like in python
- The preprocessor merges all lines to a single standard string
- A single trailing space is kept, if present
- New line is not kept. To hard code new lines in the string, use \\n

```
$ cd tools  
$ cat json/decorator/pizza.json  

{
"add_file_header":"True",
"namespace":      "decorator_pizza",
"path":           "decorator_pizza",
"trace":          "True",
"comment":        "Consider a case of a pizza shop.",

"classes": {
	"pizza":{
		# this is abstract class
		"type":"abstract",
		"members": [
			["pure_virtual", "price", "int"],
			["var",   "_pizza_price", "int", "", "private"],
		],

		"inheritance": {
			"margherita_pizza, gourmet_pizza":{
				"members": [ ["override",  "<ALL>"],
					["init","init", "void", "int pizza_price"],
				]
			},
			"toppings_decorator":{
				"type":"abstract",
				"enable_super":"True",
				"members": [ ["override",  "<ALL>"],
					["init","init", "void", "struct pizza *inner, int topping_price"],
					["var", "_inner",  "struct pizza *", "", "private"],
					["var", "_topping_price",  "int", "", "private"]
				 ],
				"inheritance": {
					"extra_cheese_topping, jalapeno_topping, mushroom_topping":{
						"members": [ ["override",  "<ALL>"],
							["init","init", "void", "struct pizza *inner, int topping_price"]
						 ]
					}
				}
			}
		}
	},

	"test":{
		"includes":["margherita_pizza", "gourmet_pizza", "extra_cheese_topping", "jalapeno_topping", "mushroom_topping"],
		"templates":["_test"]
	}
}
}

```

## Create template code using jinja2 Template Engine

```
$ tree tmpl       
tmpl
`-- c
    |-- _source.jinja
    |-- c.jinja
    |-- _header.jinja
    `-- h.jinja
```

## Using jinja2 replace&combine the json-define-class-info and the Template

```
$ ./autogen_jinja2.py --file json/factory-method.json 
```

## Check Result

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

# QuickStart

## Run

```
$ cd tools  
$ ./autogen_jinja2.py --file json/factory-method.json  
```

## Debug

```
python /usr/lib64/python2.7/pdb.py autogen_jinja2.py  
(Pdb) break            # set breakpoint  
(Pdb) run -i 'json/factory-method.json'  
(Pdb) c                # continue util breakpoint  
(Pdb) s                # step into  
(Pdb) n                # next  
(Pdb) util 112         # continue util the line number  
```

# Requirement

```
$ sudo pip install jinja2  
$ sudo pip install jsoncomment
<or>
$ sudo easy_install jinja2
$ sudo easy_install jsoncomment
```

# Vim Plugin

https://github.com/Glench/Vim-Jinja2-Syntax.git  
https://github.com/elzr/vim-json.git  

# Refs

http://kagerato.net/articles/software/libraries/jinja-quickstart.html  
http://jinja.pocoo.org/docs/templates/  
http://jinja.pocoo.org/docs/templates/#whitespace-control  
http://www.dotnetperls.com/dictionary-python  
http://pymotw.com/2/json/  
http://pagekite.net/wiki/Floss/PyBreeder/  
