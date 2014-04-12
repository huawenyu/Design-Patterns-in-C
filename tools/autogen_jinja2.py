#!/usr/bin/python
#
# Requirement
# ===========
# > linux $ sudo pip install jinja2
# > <or>
# > linux $ sudo easy_install jinja2
#
# QuickStart
# ==========
# Run
# ---
# ./autogen_jinja2.py -i json/factory-method.json
#
# Debug
# -----
# python /usr/lib64/python2.7/pdb.py autogen_jinja2.py
# (Pdb) break            # set breakpoint
# (Pdb) run -i 'json/factory-method.json'
# (Pdb) c                # continue util breakpoint
# (Pdb) s                # step into
# (Pdb) n                # next
# (Pdb) util 112         # continue util the line number
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
import copy
import argparse
import jinja2
import pprint
import const as mysyn
from odict import odict


def enum(*sequential, **named):
	enums = dict(zip(sequential, range(len(sequential))), **named)
	reverse = dict((value, key) for key, value in enums.iteritems())
	enums['reverse_mapping'] = reverse
	return type('Enum', (), enums)


# Setup syntax constants
mysyn.classes = 'classes'  #
mysyn.members = 'members'  #
mysyn.sub_classes = 'inheritance'  #

# Must match one by one
mysyn.m_type = enum('routine', 'method', 'virtual', 'override', 'variable')
mysyn.m_set =      ['routines','methods','ops',     'ops',      'vars']
mysyn.m_str = mysyn.m_type.reverse_mapping

# cat-category
mysyn.func_mode = enum('_None', '_cat', 'cat_name', 'cat_type_name', 'cat_type_name_args')
mysyn.func =      enum('scope', 'type', 'name', 'args')


# templateVars:
# path, file,
# NAME, name, super
# members:(pre,func,post),
def render_one_to_file(templateVars):
	# Setup jinja2 render template
	templateLoader = jinja2.FileSystemLoader( searchpath="." )
	templateEnv = jinja2.Environment( loader=templateLoader )
	templ_header = templateEnv.get_template( os.path.abspath("json/c-header.jinja") )
	templ_source = templateEnv.get_template( os.path.abspath("json/c-source.jinja") )
	#outputText = template.render( templateVars ) # dictionary

	outputText = templ_header.render( templateVars )
	f = open('{0}/{1}.{2}'.format(one_class_dict['path'], one_class_dict['file'], 'h'), 'w')
	f.write(outputText)
	f.close()

	outputText = templ_source.render( templateVars )
	f = open('{0}/{1}.{2}'.format(one_class_dict['path'], one_class_dict['file'], 'c'), 'w')
	f.write(outputText)
	f.close()

def get_value_else_default(rdict, key, def_val):
	rval = rdict.get(key, def_val)
	if not rval:
		rval = def_val
	return rval

def render_tree_to_file(context_dict_tree):
	for class_name, class_detail in context_dict_tree.iteritems():
		render_one_to_file(class_detail)
		if mysyn.sub_classes in input_dict:
			render_tree_to_file(class_detail[mysyn.sub_classes])


def convert_to_myclasses(myclass_dict, input_dict, mysuper):
	for myclass_name, one_inputclass in input_dict.iteritems():
		one_myclass = odict()
		myclass_dict[myclass_name] = one_myclass
		one_myclass['path'] = get_value_else_default(mysuper, 'path', '.')
		one_myclass['namespace'] = get_value_else_default(mysuper, 'namespace', 'anonymouse')
		one_myclass['file'] = get_value_else_default(one_inputclass, 'file', myclass_name)
		one_myclass['name'] = myclass_name
		one_myclass['NAME'] = myclass_name.upper()
		one_myclass['enable_super'] = get_value_else_default(one_inputclass, 'enable_super', 'False')
		one_myclass['super'] = get_value_else_default(mysuper, 'name', '')
		#one_myclass['have_super'] = length()

		# split members into ops and vars ...
		one_myclass[mysyn.m_set[mysyn.m_type.virtual]] = []
		one_myclass[mysyn.m_set[mysyn.m_type.routine]]  = []
		one_myclass[mysyn.m_set[mysyn.m_type.method]]   = []
		one_myclass[mysyn.m_set[mysyn.m_type.variable]] = []
		if one_inputclass.has_key(mysyn.members):
			for member_input in one_inputclass[mysyn.members]:
				member_category = ''
				member_detail = ['public', '', '', '']

				member_mode = len(member_input)
				if member_mode == mysyn.func_mode.cat_name:
					member_category = member_input[0]
					member_detail[mysyn.func.name] = member_input[1]
				elif member_mode == mysyn.func_mode.cat_type_name:
					member_category = member_input[0]
					member_detail[mysyn.func.type] = member_input[1]
					member_detail[mysyn.func.name] = member_input[2]
				elif member_mode == mysyn.func_mode.cat_type_name_args:
					member_category = member_input[0]
					member_detail[mysyn.func.type] = member_input[1]
					member_detail[mysyn.func.name] = member_input[2]
					member_detail[mysyn.func.args] = member_input[3]
				else:
					raise Exception('member_input size is {0} greater than 4: {1}'.\
					format(member_input, member_mode))

				#@TODO check member_name conflict

				if   member_category == mysyn.m_str[mysyn.m_type.routine]:
					one_myclass[        mysyn.m_set[mysyn.m_type.routine]].append(member_detail)
				elif member_category == mysyn.m_str[mysyn.m_type.method]:
					one_myclass[        mysyn.m_set[mysyn.m_type.method]].append(member_detail)
				elif member_category == mysyn.m_str[mysyn.m_type.virtual]:
					one_myclass[        mysyn.m_set[mysyn.m_type.virtual]].append(member_detail)
				elif member_category == mysyn.m_str[mysyn.m_type.override]:
					ops_find = False
					for ops_member in \
					  mysuper[          mysyn.m_set[mysyn.m_type.virtual]]:
						if ops_member[mysyn.func.name] == member_detail[mysyn.func.name]:
							ops_find = True
							one_myclass[mysyn.m_set[mysyn.m_type.override]].append(ops_member)

					if not ops_find:
						raise Exception('member override, but no prototype in super: {0}'.format(member_detail))
				elif member_category == mysyn.m_str[mysyn.m_type.variable]:
					one_myclass[        mysyn.m_set[mysyn.m_type.variable]].append(member_detail)

		# recursive sub-classes
		one_myclass[mysyn.sub_classes] = odict()
		if one_inputclass.has_key(mysyn.sub_classes):
			sub_inputclass = one_inputclass[mysyn.sub_classes]
			sub_myclass = odict()
			one_myclass[mysyn.sub_classes] = sub_myclass
			convert_to_myclasses(sub_myclass, sub_inputclass, one_myclass)

	return myclass_dict


# convert config data to render data
def convert_namespace_to_tree(input_dict):
	mysuper = odict()
	context_dict_tree = odict()

	mysuper['path'] = get_value_else_default(input_dict, 'path', '.')
	mysuper['namespace'] = get_value_else_default(input_dict, 'namespace', 'anonymouse')
	if input_dict.has_key('classes'):
		convert_to_myclasses(context_dict_tree, input_dict['classes'], mysuper)

	return context_dict_tree


def render_namespace(namespace_json):
	try:
		if not os.path.isfile(namespace_json):
			raise Exception('file {0} not exists'.format(namespace_json))

		input_dict = json.load(open(namespace_json), object_pairs_hook=collections.OrderedDict)
		print 'NAMESPACE loading:',json.dumps(input_dict, sort_keys=False, indent=2)

		context_dict_tree = convert_namespace_to_tree(input_dict)
		print 'NAMESPACE generating:',json.dumps(context_dict_tree, sort_keys=False, indent=2)

		#render_tree_to_file(context_dict_tree)
	except Exception, e:
		print "Exception and exit now!", e.args
		traceback.print_exc(file=sys.stdout)
		sys.exit(0)


def test_me():
	render_namespace("json/factory-method.json")

if __name__ == '__main__':
	# arguments parser
	parser = argparse.ArgumentParser(description='Code Generater for GoF')
	parser.add_argument('-i','--input', help='Design Pattern File', required=True)
	parser.add_argument('-o','--output', help='Output Directory', required=False)
	parser.add_argument('-f','--format', help='The Code Format Choose, default=c, [c,c++,java,c#]', required=False)
	args = vars(parser.parse_args())

	render_namespace(args['input'])

