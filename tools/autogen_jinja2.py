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
mysyn.auto_comn_tmpl_file = 'autogen_.jinja'
mysyn.classes = 'classes'  #
mysyn.members = 'members'  #
mysyn.sub_classes = 'inheritance'  #

# Must match one by one
mysyn.m_dict = {\
'routine' :'routines',\
'method'  :'methods',\
'virtual' :'virtuals',\
'override':'overrides',\
'variable':'vars'}

# cat-category
mysyn.func_mode = enum('_None', '_cat', '_cat_name', 'cat_type_name', 'cat_type_name_args')
mysyn.func =      enum('scope', 'type', 'name', 'args')


def render_one_to_file(x, dir_name, files):
	templateEnv,templateVars,output_dir = x

	for one_file in files :
		if not one_file.startswith('_') and one_file.endswith('jinja'):
			templ_file = templateEnv.get_template(one_file)
			output_text = templ_file.render( templateVars )

			# open file
			ext = os.path.splitext(one_file)[0] # use filename as output file extension
			output_abs_file = os.path.abspath('{0}/{1}/{2}.{3}'.format(output_dir, templateVars['path'], templateVars['file'], ext))
			output_abs_dir = os.path.dirname(output_abs_file)
			if not os.path.exists(output_abs_dir):
				os.makedirs(output_abs_dir)

			f = open(output_abs_file, 'w')
			f.write(output_text)
			f.close()


def render_class_to_file(templateVars, code_style, output_dir):
	tmpl_dir = ''
	if code_style == 'c':
		tmpl_dir = 'tmpl/c/'
	elif code_style == 'cplus':
		tmpl_dir = 'tmpl/cplus/'
	elif code_style == 'java':
		tmpl_dir = 'tmpl/java/'
	elif code_style == 'csharp':
		tmpl_dir = 'tmpl/csharp/'

	# Setup jinja2 render template
	templateLoader = jinja2.FileSystemLoader( searchpath=os.path.abspath(tmpl_dir) )
	templateEnv = jinja2.Environment( loader=templateLoader )
	templateEnv.line_statement_prefix = '##'
	os.path.walk(tmpl_dir, render_one_to_file, (templateEnv,templateVars,output_dir))


def get_value_else_default(rdict, key, def_val):
	rval = rdict.get(key, def_val)
	if not rval:
		rval = def_val
	return rval


def render_array_to_file(myclasses_array_dict, code_style, output_dir):
	for class_name, class_detail in myclasses_array_dict.iteritems():
		render_class_to_file(class_detail, code_style, output_dir)


def flush_unused_and_makeup(myclasses_array_dict):
	for class_name, class_detail in myclasses_array_dict.iteritems():
		# make dummy for jinja
		class_detail['x'] = ''

		if class_detail.has_key(mysyn.sub_classes):
			class_detail.pop(mysyn.sub_classes, None)
		if class_detail.has_key(mysyn.m_dict['override']):
			class_detail.pop(mysyn.m_dict['override'], None)
		if class_detail.has_key('supers') and len(class_detail['supers']) == 0:
			class_detail.pop('supers', None)
		for members in mysyn.m_dict.values(): # avoid None Error
			if class_detail.has_key(members):
				if len(class_detail[members]) > 0:
					members_tuple = []
					for one_member in class_detail[members]:
						members_tuple.append(tuple(one_member))
					class_detail[members] = members_tuple
				elif len(class_detail[members]) == 0:
					class_detail.pop(members, None)


def convert_to_class(myclasses_array_dict, class_name):
	if myclasses_array_dict.has_key(class_name) and len(myclasses_array_dict[class_name]) > 0:
		return myclasses_array_dict[class_name];
	else:
		raise Exception('class *{0}* not exist'.format(class_name))


# find function's protocol from super's vtable
# @find_my_supers begin search from this class's supers
# @is_a_class come from override's type field, means the vtable should search first from is_a_class
# @my_direct_parent must be contain in this_class's supers
def find_vtable_entry_by_function(my_class, func_name, myclasses_array_dict, find_the_supers, is_a_class, my_direct_parents):
	one_class = convert_to_class(myclasses_array_dict, find_the_supers)
	for super_name in one_class['supers'].keys():
		my_direct_parents.append(super_name)
		one_super = convert_to_class(myclasses_array_dict, super_name)

		# find vtable protocol, copy info into our processing class
		my_supers = my_class['supers']
		#function = ['public', 'void', 'do_something', '']
		for one_virtual in one_super[mysyn.m_dict['virtual']]:
			if func_name == one_virtual[mysyn.func.name] and len(my_direct_parents) > 0:
				# use direct parent as key
				if not my_supers.has_key(my_direct_parents[0]):
					my_supers[my_direct_parents[0]] = odict()

				# the value is function's array
				if not my_supers[my_direct_parents[0]].has_key(one_super['name']):
					my_supers[my_direct_parents[0]][one_super['name']] = odict()

				my_supers[my_direct_parents[0]][one_super['name']]['detail'] = '.'.join(my_direct_parents)
				my_supers[my_direct_parents[0]][one_super['name']][mysyn.m_dict['virtual']] = []
				my_supers[my_direct_parents[0]][one_super['name']][mysyn.m_dict['virtual']].append(one_virtual)

				return True

		if find_vtable_entry_by_function(my_class, func_name, myclasses_array_dict, super_name, is_a_class, my_direct_parents):
			return True
		my_direct_parents.pop()
	return False


def parse_override_function(myclasses_array_dict):
	for class_name, class_detail in myclasses_array_dict.iteritems():
		#override = ['public', 'base_class', 'do_something', '']
		for override in class_detail[mysyn.m_dict['override']]:
			if not find_vtable_entry_by_function(class_detail, \
			  override[mysyn.func.name], myclasses_array_dict, \
			  class_detail['name'], override[mysyn.func.type], []):
				raise Exception('class *{0}* override function *{1}* not exist in *{2}* and the supers'.\
					format(class_detail['name'], override[mysyn.func.name], override[mysyn.func.type]))


def convert_to_array_dict(myclasses_array_dict, context_dict_tree):
	for class_name, class_detail in context_dict_tree.iteritems():
		myclasses_array_dict[class_name] = class_detail
		if class_detail.has_key(mysyn.sub_classes):
			convert_to_array_dict(myclasses_array_dict, class_detail[mysyn.sub_classes])


def convert_to_myclasses(myclass_dict, input_dict, mysuper):
	for myclass_name, one_inputclass in input_dict.iteritems():
		one_myclass = odict()
		myclass_dict[myclass_name] = one_myclass
		one_myclass['path'] = get_value_else_default(mysuper, 'path', '.')
		one_myclass['namespace'] = get_value_else_default(mysuper, 'namespace', 'anonymouse')
		one_myclass['file'] = get_value_else_default(one_inputclass, 'file', myclass_name)
		one_myclass['name'] = myclass_name
		one_myclass['NAME'] = myclass_name.upper()

		supers = odict()
		one_myclass['supers'] = supers
		if mysuper.has_key('name'):
			supers[mysuper['name']] = odict()
		if one_inputclass.has_key('supers'):
			for super_name in one_inputclass['supers']:
				supers[super_name] = odict()

		for members in mysyn.m_dict.values(): # avoid None Error
			one_myclass[members]  = []

		# split members into functions and vars ...
		if one_inputclass.has_key(mysyn.members):
			for member_input in one_inputclass[mysyn.members]:
				member_category = ''
				member_detail = ['public', '', '', '']

				member_mode = len(member_input)
				if member_mode == mysyn.func_mode.cat_type_name:
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
				if one_myclass.has_key(mysyn.m_dict[member_category]):
					one_myclass[mysyn.m_dict[member_category]].append(member_detail)
				else:
					raise Exception('members of category *{0}* not exist'.\
						format(mysyn.m_dict[member_category]))

		''' **Just needed by C code.**
		1. "enable_super" come from config
		2. "_have_super_ref" is auto-gen field used to control code-gen
		   If "_have_super_ref" is "True", means the implement support super call:
		    * As base class, who have no super at all
			  - can be control by **config**
			  - must have virtual-function,
			  - must already config as 'enable_super'
			  - The generated code should append super pointer in vtable
		    * As derive class,
			  - just control by super, **config have no use at all**.
			  - must exist super to sure self is really 'derive' class
			  - the parent must have enable_super already
			  - The generated code should init with super
		'''
		one_myclass['_have_super_ref'] = False
		if one_myclass['supers']: # As derive class
			if mysuper.has_key('_have_super_ref') and mysuper['_have_super_ref'] == True: # if parent support super, child should be init with super
				one_myclass['_have_super_ref'] = True
		else: # As base class
			if len(one_myclass[mysyn.m_dict['virtual']]) > 0:
				enable_super = get_value_else_default(one_inputclass, 'enable_super', 'False')
				if enable_super.lower() == 'true':
					one_myclass['_have_super_ref'] = True
		
		'''
		"_have_vtable_new" is auto-gen field used to control code-gen
		    - means the class add new virtual function for itself and it's derive classes
		    - The generated code should have a new vtable (for C code)
		'''
		one_myclass['_have_vtable_new'] = False
		if len(one_myclass[mysyn.m_dict['virtual']]) > 0:
			one_myclass['_have_vtable_new'] = True

		# recursive sub-classes
		one_myclass[mysyn.sub_classes] = odict()
		if one_inputclass.has_key(mysyn.sub_classes):
			sub_inputclass = one_inputclass[mysyn.sub_classes]
			sub_myclass = odict()
			one_myclass[mysyn.sub_classes] = sub_myclass
			convert_to_myclasses(sub_myclass, sub_inputclass, one_myclass)

	return myclass_dict


# convert config data to render data
def convert_namespace_to_tree(def_path, input_dict):
	mysuper = odict()
	context_dict_tree = odict()

	mysuper['path'] = get_value_else_default(input_dict, 'path', def_path)
	mysuper['namespace'] = get_value_else_default(input_dict, 'namespace', def_path)
	mysuper['enable_super'] = 'False'
	mysuper['supers'] = []
	if input_dict.has_key('classes'):
		convert_to_myclasses(context_dict_tree, input_dict['classes'], mysuper)

	return context_dict_tree


def render_namespace(input_file, code_style, output_dir):
	try:
		if not os.path.isfile(input_file):
			raise Exception('file *{0}* not exists'.format(input_file))

		input_dict = json.load(open(input_file), object_pairs_hook=collections.OrderedDict)
		#print 'NAMESPACE loading:',json.dumps(input_dict, sort_keys=False, indent=2)

		context_dict_tree = convert_namespace_to_tree(\
		  os.path.splitext(os.path.basename(input_file))[0], input_dict)
		#print json.dumps(context_dict_tree, sort_keys=False, indent=2)

		myclasses_array_dict = odict()
		convert_to_array_dict(myclasses_array_dict, context_dict_tree)
		parse_override_function(myclasses_array_dict)
		flush_unused_and_makeup(myclasses_array_dict)
		print json.dumps(myclasses_array_dict, sort_keys=False, indent=3)

		render_array_to_file(myclasses_array_dict, code_style, output_dir)
	except Exception, e:
		print "Exception and exit now!", e.args
		traceback.print_exc(file=sys.stdout)
		sys.exit(0)


def test_me():
	render_namespace("json/factory-method.json")

if __name__ == '__main__':
	# arguments parser
	parser = argparse.ArgumentParser(description='Code Generater for GoF')
	parser.add_argument('--file', metavar='input file', help='Input Design Pattern File', required=True)
	parser.add_argument('--dir', metavar='output dir', help='Output Directory', required=False, default='code')
	parser.add_argument('--code', metavar='code type', help='Language Choose', choices=['c','cplus','java','csharp'], required=False, default='c')
	args = vars(parser.parse_args())

	render_namespace(args['file'], args['code'], args['dir'])

