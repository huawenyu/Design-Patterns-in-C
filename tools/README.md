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
|-- gencode.py          <<< the entry script
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

### Trips

- Support comment which start with #, but Inline comments are not supported
- Support multiline-strings with """ enclose, with prefix ```<br>``` to show newline, but the content cannot contain any double-quote symbol like ["], or [\], if needed, please prefix with escape [\], for example:
```
Sample 1:
---------

"comment"        :"""Composite better than inheritance,
<br> When:
<br> =====
<br> 
<br>                    ----Shape---
<br>                   /            \\
<br>          Rectangle              Circle
<br>         /        \\            /      \\
<br> BlueRectangle  RedRectangle BlueCircle RedCircle
<br> 
<br> Refactor to:
<br> ============
<br> 
<br>           ----Shape---                        Color
<br>          /           \\                      /    \\
<br> Rectangle(Color)   Circle(Color)           Blue   Red
""",

Sample 2:
---------

			["static_method", "test_me", "int", "", "private","","""
				<br>void color_init(struct color *color)
				<br>{
				<br>	printf(\"color_init\\n\");
				<br>	memset(color, sizeof(*color), 0);
				<br>	color->ops = &color_ops;
				<br>}
			"""],
```
- Support trailing commas, but donnot append any space after commas, Error sample:
```
> "members": [ ["override",  "<ALL>"], ],
Should change to:
> "members": [ ["override",  "<ALL>"],],
Or change to:
> "members": [ ["override",  "<ALL>"],
> ],
```
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
$ python gencode.py --file json/factory-method.json 
```

## Check Result

```
$ tree _code 
_code
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
$ python gencode.py --file json/factory-method.json  
```

## Debug

```
python -m pdb gencode.py --file json/command.json
(Pdb) break            # set breakpoint  
(Pdb) c                # continue util breakpoint  
(Pdb) s                # step into  
(Pdb) n                # next  
(Pdb) util 112         # continue util the line number  

(Pdb) run --file 'json/factory-method.json'    <<< if want to debug another input file  
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

1. Syntax.Jinja
https://github.com/Glench/Vim-Jinja2-Syntax.git  

2. Syntax.json  because this is more-json, so we can use javascript-syntax to show json,
Maybe it's better choice when we embedd 'pseudocode' in our json file.
Add the following line to .vimrc:
> autocmd BufNewFile,BufRead *.json set ft=javascript

# Refs

http://kagerato.net/articles/software/libraries/jinja-quickstart.html  
http://jinja.pocoo.org/docs/templates/  
http://jinja.pocoo.org/docs/templates/#whitespace-control  
http://www.dotnetperls.com/dictionary-python  
http://pymotw.com/2/json/  
http://pagekite.net/wiki/Floss/PyBreeder/  
