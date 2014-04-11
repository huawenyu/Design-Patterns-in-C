#!/usr/bin/python
#
# Quick:
# ======
# > linux $ sudo pip install jinja2
# > <or>
# > linux $ sudo easy_install jinja2
#
# Refs:
# =====
# http://jinja.pocoo.org/docs/templates/
# http://jinja.pocoo.org/docs/templates/#whitespace-control
# http://www.dotnetperls.com/dictionary-python
# http://pymotw.com/2/json/
#

import os
import json
import collections
import sys, traceback
from jinja2 import Environment

def load_from_file(filepath):
	class_inst = None
	expected_class = 'MyClass'

	mod_name,file_ext = os.path.splitext(os.path.split(filepath)[-1])

	if file_ext.lower() == '.py':
		py_mod = imp.load_source(mod_name, filepath)

	elif file_ext.lower() == '.pyc':
		py_mod = imp.load_compiled(mod_name, filepath)

	if hasattr(py_mod, expected_class):
		class_inst = getattr(py_mod, expected_name)()

	return class_inst
 
c_template = """
#ifndef {{ NAME }}_H_
#define {{ NAME }}_H_

struct {{ name }}_ops;
struct {{ name }} {
	struct {{ name }}_ops *ops;
};

struct pizza_ops {
{%- for func_rtn, func, func_params in members -%}
	{%- if func_params %}
	{{ func_rtn }} (*{{ func }})(struct {{ name }} *, {{ func_params }});
	{%- else %}
	{{ func_rtn }} (*{{ func }})(struct {{ name }} *);
	{%- endif -%}
{%- endfor -%}

{% if enable_super %}
	struct {{ name }}_ops *super;
{%- endif %}
};

void {{ name }}_init(struct {{ name }} *);
{% for func_rtn, func, func_params in members %}
static inline
{%- if func_params %}
{{ func_rtn }} {{ name }}_{{ func }}(struct {{ name }} *{{ name }}, {{ func_params }})
{
	{{ name }}->ops->{{ func }}({{ name }}, {{ func_params }});
}
{%- else %}
{{ func_rtn }} {{ name }}_{{ func }}(struct {{ name }} *{{ name }})
{
	{{ name }}->ops->{{ func }}({{ name }});
}
{% endif %}
{% endfor %}
#endif /* {{ NAME }}_H_ */

"""
 
def render_to_file(context_dict):
	tokenvals = None
	tokendict = {}
	output = Environment().from_string(c_template).render(context_dict)
	#print(output)
	f = open('{0}.{1}'.format(context_dict['file'], 'h'), 'w')
	f.write(output) # python will convert \n to os.linesep
	f.close() # you can omit in most cases as the destructor will call if


if __name__ == '__main__':
	try:
		#data = [ { 'a':'A', 'b':(2, 4), 'c':3.0 } ]
		#print 'INDENT:',json.dumps(data, sort_keys=True, indent=2)

		#print random.choice(class_inst.verb_list)
		#json.dumps(['foo', {'bar': ('baz', None, 1.0, 2)}])

		#print json.dumps(['foo', {'bar': ('baz', None, 1.0, 2)}])
		#JSON_Datalist = '{"id":"XXXX", "name": "xyz", "user" : { "id": "XXXX", "username":"XYZ", "group":{"id": "XXXX"}}}'

		JSON_Datalist = '{"name":"pizza", "member": ["prepare", "bake"], \
			"user" : { "id": "XXXX", "username":"XYZ", "group":{"id": "XXXX"}}}'
		input_dict = json.loads(JSON_Datalist, object_pairs_hook=collections.OrderedDict)
		print 'INDENT:',json.dumps(input_dict, sort_keys=False, indent=2)

		print input_dict
		print '-------'
		print 'name:{0}'.format(input_dict['name'])
		print str(input_dict['member'])
		for item in input_dict['member'] :
			print item
		#print json.dumps([{"KEY1":{"NAME":"XXXXXX","VALUE":100},"KEY2":{"NAME":"YYYYYYY","VALUE":200},"KEY3":{{"NAME":"ZZZZZZZ","VALUE":500}}])

		# formalize data
		context_dict = {}
		name = "";
		if "name" in input_dict:
			name = input_dict['name']
			context_dict['name'] = name
			context_dict['NAME'] = name.upper()
		else:
			raise Exception("class's name is empty")

		if "file" in input_dict:
			context_dict['file'] = input_dict['file']
		else:
			context_dict['file'] = name

		context_dict['members'] = [('void', 'prepare', 'int a, int b'), \
			('void', 'bake', 'int a, int b'),\
			('void', 'cut', 'int a, int b'),]
		context_dict['enable_super'] = True

		render_to_file(context_dict)

		for index, item in enumerate(sys.argv):
			print "argument {0} {1}".format(index, str(item))
			if index > 0 :
				print 'class_inst'
	except Exception, e:
		print "Exception and exit now!", e.args
		traceback.print_exc(file=sys.stdout)
		sys.exit(0)

