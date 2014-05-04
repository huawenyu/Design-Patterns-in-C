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
import re
import const as const
from odict import odict
from time import gmtime, strftime

def enum(*sequential, **named):
	enums = dict(zip(sequential, range(len(sequential))), **named)
	reverse = dict((value, key) for key, value in enums.iteritems())
	enums['reverse_mapping'] = reverse
	return type('Enum', (), enums)


# Setup syntax constants
const.auto_comn_tmpl_file = 'autogen_.jinja'
const.classes             = 'classes'        #
const.sub_classes         = 'inheritance'    #
## member var and method
const.members             = 'members'        #
const.override_all        = '<ALL>'          #
const.m_dict              ={ \
                            'virtual'      :'virtuals', \
                            'method'       :'methods',  \
                            'static_method':'methods',  \
                            'override'     :'overrides',\
                            'var'          :'vars', \
                            'static_var'   :'vars'}

## auto add function:       'static', 'scope', 'type', 'name', 'params', 'args', 'comment'
const.member_destructor   =['False', 'private', 'void', '_destructor', '', '', \
                            'called by free(): put resources, forward to super.']
const.member_free         =['False', 'public', 'void', 'free', '', '', \
                            'free memory after call destructor().']
## Flags
const.config_destructor   = 'enable_destructor'
const.config_super        = 'enable_super'
const.control_super       = '_have_super_ref'
const.control_vtable      = '_have_vtable_new'
const.control_static_var  = '_have_static_var'
## cat-category
const.func                = enum('static', 'scope', 'type', 'name', 'params', 'args', 'comment')
const.func_mode           = enum('_None', '_cat', 'cat_name', 'cat_name_type', 'cat_name_type_args', 'cat_name_type_args_scope', 'cat_name_type_args_scope_comment')


def render_one_to_file(x, dir_name, files):
	templateEnv,templateVars,code_style,output_dir = x

	# if class have assign special templates, just apply them
	if templateVars.has_key('templates') and len(templateVars['templates']) > 0:
		for one_file in files :
			filename = os.path.splitext(one_file)[0] # use filename as output file extension
			ext = os.path.splitext(one_file)[1] # use filename as output file extension
			for tmpl in templateVars['templates']:
				if filename == tmpl or one_file == tmpl:
					# open file
					output_abs_file = os.path.abspath(\
					  '{0}/{1}/{2}/{3}{4}'.format(\
					  output_dir, code_style, templateVars['path'], \
					  templateVars['file'], ext))
					file_header_name = '{0}{1}'.format(templateVars['file'], ext)
					output_abs_dir = os.path.dirname(output_abs_file)
					if not os.path.exists(output_abs_dir):
						os.makedirs(output_abs_dir)

					templateVars['file_header_name'] = file_header_name
					templ_file = templateEnv.get_template(one_file)
					output_text = templ_file.render( templateVars )
					output_text = re.sub('([ \t]*\n){3,}', '\n\n', output_text.strip())
					f = open(output_abs_file, 'w')
					f.write(output_text)
					f.close()
	else:
		for one_file in files :
			if not one_file.startswith('_') and one_file.endswith('jinja'):
				# open file
				ext = os.path.splitext(one_file)[0] # use filename as output file extension
				output_abs_file = os.path.abspath(\
				  '{0}/{1}/{2}/{3}.{4}'.format(\
				  output_dir, code_style, templateVars['path'], \
				  templateVars['file'], ext))
				file_header_name = '{0}.{1}'.format(templateVars['file'], ext)
				output_abs_dir = os.path.dirname(output_abs_file)
				if not os.path.exists(output_abs_dir):
					os.makedirs(output_abs_dir)

				templateVars['file_header_name'] = file_header_name
				templ_file = templateEnv.get_template(one_file)
				output_text = templ_file.render( templateVars )
				output_text = re.sub('([ \t]*\n){3,}', '\n\n', output_text.strip())
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
	elif code_style == 'python':
		tmpl_dir = 'tmpl/python/'

	# Setup jinja2 render template
	templateLoader = jinja2.FileSystemLoader( searchpath=os.path.abspath(tmpl_dir) )
	templateEnv = jinja2.Environment( loader=templateLoader, extensions=["jinja2.ext.do",] )
	templateEnv.line_statement_prefix = '##'
	os.path.walk(tmpl_dir, render_one_to_file, (templateEnv,templateVars,code_style,output_dir))


def get_value_else_default(rdict, key, def_val):
	rval = rdict.get(key, def_val)
	if not rval:
		rval = def_val
	return rval


def render_array_to_file(myclasses_array_dict, code_style, output_dir):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		render_class_to_file(one_myclass, code_style, output_dir)


# if language already support oop, continue makeup
def makeeasy_for_oop_language(myclasses_array_dict):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		if one_myclass.has_key(const.control_super):
			one_myclass.pop(const.control_super, None)
		if one_myclass.has_key(const.control_vtable):
			one_myclass.pop(const.control_vtable, None)

		supers = one_myclass['supers']
		one_myclass['supers'] = []
		overrides = []
		one_myclass[const.m_dict['override']] = overrides
		for super_name,super_detail in supers.iteritems():
			one_myclass['supers'].append(super_name)
			for vtable_name,vtable_detail in super_detail.iteritems():
				if vtable_detail.has_key(const.m_dict['virtual']):
					overrides += vtable_detail[const.m_dict['virtual']]
		one_myclass[const.m_dict['override']] = overrides


def flush_unused_and_makeup(myclasses_array_dict):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		if one_myclass.has_key(const.config_destructor):
			one_myclass.pop(const.config_destructor, None)
		if one_myclass.has_key(const.config_super):
			one_myclass.pop(const.config_super, None)
		if one_myclass.has_key(const.sub_classes):
			one_myclass.pop(const.sub_classes, None)
		if one_myclass.has_key(const.m_dict['override']):
			one_myclass.pop(const.m_dict['override'], None)
		for members in const.m_dict.values(): # avoid None Error
			if one_myclass.has_key(members):
				if len(one_myclass[members]) > 0:
					members_tuple = []
					for one_member in one_myclass[members]:
						members_tuple.append(tuple(one_member))
					one_myclass[members] = members_tuple
				elif len(one_myclass[members]) == 0:
					one_myclass.pop(members, None)


def convert_to_class(myclasses_array_dict, class_name):
	if myclasses_array_dict.has_key(class_name) and len(myclasses_array_dict[class_name]) > 0:
		return myclasses_array_dict[class_name];
	else:
		raise Exception('class *{0}* not exist'.format(class_name))


# find function's protocol from super's vtable
# @find_the_supers begin search from this class's supers
# @is_a_class come from override's type field, means the vtable should search first from is_a_class
# @my_direct_parents must be contain in this_class's supers
def find_virtual_prototype_by_name(my_class, func_name, myclasses_array_dict, find_the_supers, is_a_class, my_direct_parents):
	one_class = convert_to_class(myclasses_array_dict, find_the_supers)
	for super_name in one_class['supers'].keys():
		my_direct_parents.append(super_name)
		one_super = convert_to_class(myclasses_array_dict, super_name)

		# find vtable protocol in my supers, copy info into my class
		my_supers = my_class['supers']
		#function = ['public', 'void', 'do_something', '']
		for one_virtual in one_super[const.m_dict['virtual']]:
			#   * if name matched, copy
			#   * if my function name is <ALL>, copy all vtable
			#   * if vtable function name is 'destructor & free', copy
			if (func_name == const.override_all \
			    or func_name == one_virtual[const.func.name] \
			    or const.member_destructor[const.func.name] == one_virtual[const.func.name] \
			    or const.member_free[const.func.name] == one_virtual[const.func.name] \
			   ) \
			   and len(my_direct_parents) > 0:
				# use direct parent as key
				if not my_supers.has_key(my_direct_parents[0]):
					my_supers[my_direct_parents[0]] = odict()

				# the value is function's array
				if not my_supers[my_direct_parents[0]].has_key(one_super['name']):
					my_supers[my_direct_parents[0]][one_super['name']] = odict()

				my_supers[my_direct_parents[0]][one_super['name']]['path'] = '.'.join(my_direct_parents)
				if not my_supers[my_direct_parents[0]][one_super['name']].has_key(const.m_dict['virtual']):
					my_supers[my_direct_parents[0]][one_super['name']][const.m_dict['virtual']] = []
				my_supers[my_direct_parents[0]][one_super['name']][const.m_dict['virtual']].append(one_virtual)

				if (func_name == one_virtual[const.func.name]):
					return True

		if find_virtual_prototype_by_name(my_class, func_name, myclasses_array_dict, super_name, is_a_class, my_direct_parents):
			return True
		my_direct_parents.pop()
	return False


def parse_override_function(myclasses_array_dict):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		# if override_all, flush the others
		for override in one_myclass[const.m_dict['override']]:
			if override[const.func.name] == const.override_all:
				one_myclass[const.m_dict['override']] = []
				one_myclass[const.m_dict['override']].append(override)

		# find override functions prototype
		for override in one_myclass[const.m_dict['override']]:
			if not find_virtual_prototype_by_name(one_myclass, \
			  override[const.func.name], myclasses_array_dict, \
			  one_myclass['name'], override[const.func.type], []):
				if override[const.func.name] != const.override_all:
					raise Exception('class *{0}* override function *{1}* not exist in *{2}* and the supers'.\
						format(one_myclass['name'], override[const.func.name], override[const.func.type]))


def parse_support_flag_and_auto_function(myclasses_array_dict):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		# control flags
		one_myclass[const.control_super] = False  # config: enable_super
		one_myclass[const.control_vtable] = False # config: virtual
		one_myclass[const.control_static_var] = '' # config: static var

		'''
		"_have_vtable_new" is auto-gen field used to control code-gen
		    - means the class add new virtual function or static-member-variable itself
		    - The generated code should have a new vtable (for C code)
		'''
		if len(one_myclass[const.m_dict['virtual']]) > 0:
			one_myclass[const.control_vtable] = True

		# if static var, enable have_vtable_new
		for variable in one_myclass[const.m_dict['var']]:
			if variable[const.func.static] == 'True':
				one_myclass[const.control_vtable] = True
				one_myclass[const.control_static_var] = 'True'
				one_myclass[const.control_super] = True
				break

		''' **Just needed by C code.**
		1. "enable_super" come from config
		2. "_have_super_ref" is auto-gen field used to control code-gen
		   If "_have_super_ref" is "True", means the implement support super call:
		    * As base class, provide *super* support member,
			  - control by **config**: must config as 'enable_super'
			  - must have virtual-function,
			  - The generated code should append super pointer in vtable
		    * As derive class, initial suitable super,
			  - just control by super-class, **config have no use at all**.
			  - must have super-class which must have enable_super already
			  - The generated code should init with super
		'''
		if one_myclass['supers']: # As derive class
			for super_name in one_myclass['supers'].keys():
				one_super = convert_to_class(myclasses_array_dict, super_name)
				if one_super.has_key(const.config_super) \
				   and one_super[const.config_super].lower() == 'true':
					one_myclass[const.control_super] = True
					break # exit innner supers
		else: # As base class
			if len(one_myclass[const.m_dict['virtual']]) > 0:
				if one_myclass[const.config_super].lower() == 'true':
					one_myclass[const.control_super] = True

	# parse 2-times for supers's flags control_super
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		if one_myclass['supers']: # As derive class
			for super_name,super_class in one_myclass['supers'].iteritems():
				for vtable_name, vtable in super_class.iteritems():
					vtable_class = convert_to_class(myclasses_array_dict, vtable_name)
					if vtable_class[const.control_super]:
						vtable[const.control_super] = True
					if vtable_class[const.control_static_var]:
						for variable in vtable_class[const.m_dict['var']]:
							if variable[const.func.static] == 'True':
								vtable[const.control_static_var] = variable[const.func.name]
								break # exit find first static var


def convert_to_array_dict(myclasses_array_dict, context_dict_tree):
	for class_name, one_myclass in context_dict_tree.iteritems():
		myclasses_array_dict[class_name] = one_myclass
		if one_myclass.has_key(const.sub_classes):
			convert_to_array_dict(myclasses_array_dict, one_myclass[const.sub_classes])


def convert_to_myclasses(myclass_dict, input_dict, mysuper):
	for myclass_name, one_inputclass in input_dict.iteritems():
		one_myclass = odict()
		myclass_dict[myclass_name] = one_myclass

		one_myclass['templates'] = get_value_else_default(one_inputclass, 'templates', [])
		one_myclass['add_file_header'] = get_value_else_default(mysuper, 'add_file_header', False)
		one_myclass['trace']     = get_value_else_default(mysuper, 'trace', False)
		one_myclass['copyright'] = get_value_else_default(mysuper, 'copyright', [])
		one_myclass['author']    = get_value_else_default(mysuper, 'author', []) # author with email
		one_myclass['date']      = get_value_else_default(mysuper, 'date', '')
		one_myclass['summary']   = get_value_else_default(mysuper, 'summary', [])

		one_myclass['path']      = get_value_else_default(mysuper, 'path', '.')
		one_myclass['namespace'] = get_value_else_default(mysuper, 'namespace', '')
		one_myclass['file']      = get_value_else_default(one_inputclass, 'file', myclass_name)
		one_myclass['name']      = myclass_name
		one_myclass['includes']  = get_value_else_default(one_inputclass, 'includes', [])
		one_myclass['comment']   = get_value_else_default(one_inputclass, 'comment', '')

		# used as C generate helper
		# config flags
		one_myclass[const.config_destructor] = get_value_else_default(one_inputclass, const.config_destructor, 'False')
		one_myclass[const.config_super] = get_value_else_default(one_inputclass, const.config_super, 'False')
		if one_myclass[const.config_destructor].lower() == 'true':
			one_myclass[const.config_super] = 'True'

		supers = odict()
		one_myclass['supers'] = supers
		if mysuper.has_key('name'):
			supers[mysuper['name']] = odict()
		if one_inputclass.has_key('supers'):
			for super_name in one_inputclass['supers']:
				supers[super_name] = odict()

		for members in const.m_dict.values(): # avoid None Error
			one_myclass[members]  = []

		if one_myclass[const.config_destructor].lower() == 'true':
			one_myclass[const.m_dict['virtual']].append(const.member_destructor);
			one_myclass[const.m_dict['virtual']].append(const.member_free);

		# split members into functions and vars ...
		if one_inputclass.has_key(const.members):
			for member_input in one_inputclass[const.members]:
				member_category = ''
				member_detail = ['False', 'public', '', '', '', '','']

				member_mode = len(member_input)
				if  member_mode == const.func_mode.cat_name:
					member_category = member_input[0]
					member_detail[const.func.name] = member_input[1]
				elif member_mode == const.func_mode.cat_name_type:
					member_category = member_input[0]
					member_detail[const.func.name] = member_input[1]
					member_detail[const.func.type] = member_input[2]
				elif member_mode == const.func_mode.cat_name_type_args or \
					 member_mode == const.func_mode.cat_name_type_args_scope or \
					 member_mode == cat_name_type_args_scope_comment:
					member_category = member_input[0]
					member_detail[const.func.name]  = member_input[1]
					member_detail[const.func.type]  = member_input[2]
					member_detail[const.func.params]= member_input[3]

					# scope and comment
					if member_mode == const.func_mode.cat_name_type_args_scope or \
					   member_mode == const.func_mode.cat_name_type_args_scope_comment:
						if member_input[4]:
							member_detail[const.func.scope] = member_input[4]
						if member_mode == const.func_mode.cat_name_type_args_scope_comment:
							if member_input[5]:
								member_detail[const.func.comment] = member_input[5]

					if member_input[3] and member_category != 'var':
						params_str = member_input[3]
						params = params_str.split(',')
						args = []
						for one_param in params:
							find = False
							for idx in range(len(one_param)-1, 0, -1):
								one_char = one_param[idx]
								if one_char >= 'a' and one_char <= 'z' or \
								   one_char >= 'A' and one_char <= 'Z' or \
								   one_char >= '0' and one_char <= '9' or \
								   one_char == '_':
									pass
								else:
									find = True
									args.append(one_param[(idx+1):])
									args.append(', ')
									break

							if not find:
								raise Exception('class {0} member {1} params \'{2}\' error: no type or name'.\
								  format(myclass_name, member_input, params_str))

						args.pop() # remove the last comma
						member_detail[const.func.args] = ''.join(args)
				else:
					raise Exception('class {0} member_input size is {1} greater than 4: {2}'.\
					  format(myclass_name, member_input, member_mode))

				#@TODO warning member_name conflict
				if one_myclass.has_key(const.m_dict[member_category]):
					one_myclass[const.m_dict[member_category]].append(member_detail)
					if member_category == 'static_method' or member_category == 'static_var':
						member_detail[const.func.static] = 'True'
				else:
					raise Exception('class {0} members of category *{1}* not exist'.\
					  format(myclass_name, const.m_dict[member_category]))

		# recursive sub-classes
		one_myclass[const.sub_classes] = odict()
		if one_inputclass.has_key(const.sub_classes):
			sub_inputclass = one_inputclass[const.sub_classes]
			sub_myclass = odict()
			one_myclass[const.sub_classes] = sub_myclass
			convert_to_myclasses(sub_myclass, sub_inputclass, one_myclass)

	return myclass_dict


# convert config data to render data
def convert_namespace_to_tree(def_path, input_dict):
	mysuper = odict()
	context_dict_tree = odict()

	# file header or comments
	mysuper['add_file_header']  = get_value_else_default(input_dict, 'add_file_header', False)
	mysuper['trace']            = get_value_else_default(input_dict, 'trace', False)
	mysuper['copyright']        = get_value_else_default(input_dict, 'copyright', [])
	mysuper['author']           = get_value_else_default(input_dict, 'author', []) # author with email
	mysuper['date']             = get_value_else_default(input_dict, 'date', strftime("%Y-%m-%d", gmtime()))
	mysuper['summary']          = get_value_else_default(input_dict, 'summary', [])

	# generate path
	mysuper['path']             = get_value_else_default(input_dict, 'path', def_path)
	mysuper['namespace']        = get_value_else_default(input_dict, 'namespace', def_path)
	mysuper[const.config_super] = 'False'
	mysuper[const.config_destructor] = 'False'
	mysuper['supers']           = []
	if input_dict.has_key('classes'):
		convert_to_myclasses(context_dict_tree, input_dict['classes'], mysuper)

	return context_dict_tree


def render_namespace(input_file, code_style, output_dir):
	try:
		if not os.path.isfile(input_file):
			raise Exception('file *{0}* not exists'.format(input_file))

		input_dict = json.load(open(input_file), strict=False, object_pairs_hook=collections.OrderedDict)
		#print 'LOADING:',json.dumps(input_dict, sort_keys=False, indent=3)

		context_dict_tree = convert_namespace_to_tree(\
		  os.path.splitext(os.path.basename(input_file))[0], input_dict)
		#print 'JSON CONVERT TO TREE:',json.dumps(context_dict_tree, sort_keys=False, indent=3)

		myclasses_array_dict = odict()
		convert_to_array_dict(myclasses_array_dict, context_dict_tree)
		#print 'JSON CONVERT TO ARRAY:',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)
		parse_override_function(myclasses_array_dict)
		#print 'JSON PARSE OVERRIDE:',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)
		parse_support_flag_and_auto_function(myclasses_array_dict)
		#print 'JSON PARSE SUPPORT FLAGS:',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)
		flush_unused_and_makeup(myclasses_array_dict)

		if code_style == 'c':  # language not support oop
			print 'JSON FINAL:',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)
		elif code_style == 'cplus' or \
		     code_style == 'java' or \
		     code_style == 'csharp' or \
			 code_style == 'python' :
			makeeasy_for_oop_language(myclasses_array_dict)
			print 'JSON FINAL:',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)

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
	parser.add_argument('--code', metavar='code type', help='Language Choose', choices=['c','cplus','java','csharp','python'], required=False, default='c')
	args = vars(parser.parse_args())

	render_namespace(args['file'], args['code'], args['dir'])

