#!/usr/bin/python
#
# Requirement
# ===========
# > linux $ sudo pip install jinja2
# > <or>
# > linux $ sudo easy_install jinja2
#
# Refs
# ====
# http://jinja.pocoo.org/docs/templates/
# http://jinja.pocoo.org/docs/templates/#whitespace-control
# http://www.dotnetperls.com/dictionary-python
# http://pymotw.com/2/json/
#

import os
import os.path
import json
import collections
import sys, traceback
import jinja2


templateLoader = jinja2.FileSystemLoader( searchpath="." )
templateEnv = jinja2.Environment( loader=templateLoader )
templ_header = templateEnv.get_template( "header.jinja" )
templ_source = templateEnv.get_template( "source.jinja" )
#outputText = template.render( templateVars ) # dictionary

# template var: NAME, name, members:(pre,func,post), enable_super
def render_one_to_file(one_class_dict):
	outputText = templ_header.render( context_dict )
	f = open('{0}/{1}.{2}'.format(one_class_dict['path'], one_class_dict['file'], 'h'), 'w')
	f.write(outputText)
	f.close()

	outputText = templ_source.render( context_dict )
	f = open('{0}/{1}.{2}'.format(one_class_dict['path'], one_class_dict['file'], 'c'), 'w')
	f.write(outputText)
	f.close()

def get_default_value(input_dict, key, default):
	rval = ''
	if key in input_dict:
		rval = input_dict[key]
		if not rval:
			rval = default
	else:
		rval = default

	return rval


# convert config data to render data
def formalize_namespace(input_dict):
	context_dict = {}
	one_class_dict = None

	for class_name, class_detail in input_dict['classes'].iteritems():
		if not class_name:
			raise Exception("class's name is empty")

		context_dict[class_name] = {}
		one_class_dict = context_dict[class_name]
		
		one_class_dict['name'] = class_name
		one_class_dict['NAME'] = class_name.upper()
		one_class_dict['path'] = get_default_value(input_dict, 'path', '.')
		one_class_dict['file'] = get_default_value(input_dict, 'file', class_name)
		one_class_dict['enable_super'] = get_default_value(input_dict, 'enable_super', 'False')


	if "file" in input_dict:
		file = input_dict['file']
		if not file:
			file = name
		context_dict['file'] = file
	else:
		file = name
		context_dict['file'] = file

	context_dict['members'] = [('void', 'prepare', 'int a, int b'), \
		('void', 'bake', 'int a, int b'),\
		('void', 'cut', 'int a, int b'),]
	context_dict['enable_super'] = True

	return context_dict


def load_namespace(namespace_json):
	try:
		if not os.path.isfile(namespace_json):
			raise Exception('file {0} not exists'.format(namespace_json))

		input_dict = json.loads(open(namespace_json), object_pairs_hook=collections.OrderedDict)
		# format and output
		print 'NAMESPACE generating:',json.dumps(input_dict, sort_keys=False, indent=2)

		context_dict = formalize_namespace(input_dict)
		for class_name, class_detail in context_dict['classes'].iteritems():
			render_one_to_file(class_detail)

	except Exception, e:
		print "Exception and exit now!", e.args
		traceback.print_exc(file=sys.stdout)
		sys.exit(0)

if __name__ == '__main__':
	for index, item in enumerate(sys.argv):
		print "{0}. generate {1}".format(index, str(item))
		if index > 0 :
			load_namespace(item)

