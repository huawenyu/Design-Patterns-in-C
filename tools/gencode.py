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
import textwrap
import json
#import simplejson as json
#import yaml as json
from jsoncomment import JsonComment
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
const.textwrap            =['note', 'comment', 'copyright']
const.graphic             = 'graphic'
const.templ_graphic       = '_graphic'

const.m_dict              = odict([\
                            ('init'         ,'inits'), \
                            ('init_setter'  ,'inits_setter'), \
                            \
                            ('var'          ,'vars'), \
                            ('static_var'   ,'vars'),\
                            \
                            ('method'       ,'methods'),  \
                            ('static_method','methods'),  \
                            \
                            ('virtual'      ,'virtuals'), \
                            ('pure_virtual' ,'virtuals'), \
                            ('override'     ,'overrides'),\
                            \
                            ('super'        ,'supers'),\
                            ('super_setter' ,'supers_setter')\
                            \
                            ])

## auto add function:       'pure', 'static', 'scope', 'type', 'name', 'params', 'args', 'comment'
const.constructor_comment = 'constructor().'
const.member_default      =['False', 'False', 'public', '', '', '', '','','']
const.member_init         =['False', 'False', 'public', 'void', 'init', '', '', \
                            const.constructor_comment, '']
const.member_destructor   =['False', 'False', 'private', 'void', '_destructor', '', '', \
                            'called by free(): put resources, forward to super.', '']
const.member_free         =['False', 'False', 'public', 'void', 'free', '', '', \
                            'free memory after call destructor().', '']
## Flags
const.config_destructor   = 'enable_destructor' # add free() to self and all derived-class, auto enable-super
const.config_super        = 'enable_super'      # add member 'super' to vtable
const.control_super       = '_have_super_ref'
const.control_vtable      = '_have_vtable_new'
const.control_static_var  = '_have_static_var'  # '' <OR> store first static var's name for init
## cat-category
const.func                = enum('pure', 'static', 'scope', 'type', 'name', 'params', 'args', 'comment', 'pseudocode')
const.func_mode           = enum('_None', '_cat', 'cat_name', 'cat_name_type', 'cat_name_type_args', \
                                 'cat_name_type_args_scope', 'cat_name_type_args_scope_comment', \
                                 'cat_name_type_args_scope_comment_pseudocode', \
                                )


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
					file_name = templateVars['file']
					if "." not in file_name:
						file_name = '{0}{1}'.format(file_name, ext)
					output_abs_file = os.path.abspath(\
					  '{0}/{1}/{2}/{3}'.format(\
					  output_dir, code_style, templateVars['path'], file_name))
					output_abs_dir = os.path.dirname(output_abs_file)
					if not os.path.exists(output_abs_dir):
						os.makedirs(output_abs_dir)

					templateVars['file_name'] = file_name
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
				file_name = templateVars['file']
				if "." not in file_name:
					file_name = '{0}.{1}'.format(file_name, ext)
				output_abs_file = os.path.abspath(\
				  '{0}/{1}/{2}/{3}'.format(\
				  output_dir, code_style, templateVars['path'], file_name))
				output_abs_dir = os.path.dirname(output_abs_file)
				if not os.path.exists(output_abs_dir):
					os.makedirs(output_abs_dir)

				templateVars['file_name'] = file_name
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
	#templateEnv.line_statement_prefix = '##'
	#templateEnv.keep_trailing_newline = True
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


def textwrap_me(text):
	#textwrap.fill(text, width=80, initial_indent=' * ', subsequent_indent='    ')
	return textwrap.fill(text, width=79, initial_indent='    ', subsequent_indent='    ')

def textwrap_with_code(text):
	spec = '<br>'
	new_text = text.replace('<br>','<br>@')
	lines = new_text.split(spec)
	new_lines = []
	for line in lines:
		if line.startswith('@'):
			new_lines.append('\n' + line.strip('@'))
		else:
			new_lines.append('\n' + textwrap_me(line))

	return ''.join(new_lines).strip()


def flush_unused_and_makeup(myclasses_array_dict):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		if class_name == const.graphic:
			continue;

		if one_myclass.has_key(const.config_destructor):
			one_myclass.pop(const.config_destructor, None)
		if one_myclass.has_key(const.config_super):
			one_myclass.pop(const.config_super, None)
		if one_myclass.has_key(const.sub_classes):
			one_myclass.pop(const.sub_classes, None)

		# remove empty
		for members in const.m_dict.values():
			if one_myclass.has_key(members) and len(one_myclass[members]) == 0:
				one_myclass.pop(members, None)
		if one_myclass.has_key(const.m_dict['override']):
			one_myclass.pop(const.m_dict['override'], None)

		# wrap text
		for need_wrap in const.textwrap:
			if one_myclass.has_key(need_wrap) and isinstance(one_myclass[need_wrap], basestring):
				one_myclass[need_wrap] = textwrap_with_code(one_myclass[need_wrap])


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
	for super_name in one_class[const.m_dict['super']].keys():
		my_direct_parents.append(super_name)
		one_super = convert_to_class(myclasses_array_dict, super_name)

		# find vtable protocol in my supers, copy info into my class
		my_supers = my_class[const.m_dict['super']]
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
				my_supers[my_direct_parents[0]][one_super['name']][const.control_super] = False
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


def parse_helper_flag(myclasses_array_dict):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
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
				one_myclass[const.control_super] = True  # now if enable static_var, should be after member.super, so enable_super
				break

		# if static_var, remember the first static variable for initial code
		for class_name, one_myclass in myclasses_array_dict.iteritems():
			if one_myclass[const.m_dict['super']]: # As derive class
				for super_name,super_class in one_myclass[const.m_dict['super']].iteritems():
					for vtable_name, vtable in super_class.iteritems():
						vtable_class = convert_to_class(myclasses_array_dict, vtable_name)
						if vtable_class[const.control_static_var]:
							for variable in vtable_class[const.m_dict['var']]:
								if variable[const.func.static] == 'True':
									vtable[const.control_static_var] = variable[const.func.name]
									break # exit find first static var

	# const.control_super
	while True:
		should_be_continue = False
		for class_name, one_myclass in myclasses_array_dict.iteritems():
			''' **Just needed by C code.**
			1. "enable_super" come from config
			2. "_have_super_ref" is auto-gen field used to control code-gen
				* As base class, provide *super* support member,
				  - The generated code should append super pointer in vtable
				* As derive class, initial suitable super,
				  - The generated code should init with super

			# parse 1-times:
				* As base class, provide *super* support member,
				  - control by **config**: must config as 'enable_super'
				  - must have virtual-function,
				* As derive class, initial suitable super,
				  - just control by super-class, **config have no use at all**.
				  - must have super-class which must have enable_super already

			# parse 2-times for supers's flags control_super:
				* if one class config_super, change it's super all have super
			'''

			# parse 1-times for control_super
			if not one_myclass[const.control_super]:
				if one_myclass[const.m_dict['super']]: # As derive class
					for super_name in one_myclass[const.m_dict['super']].keys():
						one_super = convert_to_class(myclasses_array_dict, super_name)
						if one_super[const.control_super] \
							or (one_super.has_key(const.config_super) \
								and one_super[const.config_super].lower() == 'true'):
							one_myclass[const.control_super] = True
							should_be_continue = True
							break # exit innner supers
				else: # As base class
					if len(one_myclass[const.m_dict['virtual']]) > 0:
						if one_myclass[const.config_super].lower() == 'true':
							one_myclass[const.control_super] = True
							should_be_continue = True

		# parse 2-times for control_super: some flags should re-scan after 1-times
		for class_name, one_myclass in myclasses_array_dict.iteritems():
			if one_myclass[const.m_dict['super']]: # As derive class
				for super_name,super_class in one_myclass[const.m_dict['super']].iteritems():
					for vtable_name, vtable in super_class.iteritems():
						vtable_class = convert_to_class(myclasses_array_dict, vtable_name)

						# if one class config_super, change it's super all have super
						if not vtable_class[const.control_super]:
							if one_myclass[const.control_super] \
								or one_myclass[const.config_super].lower() == 'true':
								vtable_class[const.control_super] = True
								should_be_continue = True

							# sync vtable's flag
							if vtable_class[const.control_super]:
								vtable[const.control_super] = True

		if not should_be_continue:
			break



def gen_pynsource_graphic_nodes(myclasses_array_dict):
	nodes = []
	edges = []
	node = odict([('type','node'), ('id','name'), ('attrs',''), ('meths',''), ('x',1), ('y',1), ('width',1), ('height',1)])
	edge = odict([('type','edge'), ('id','name'), ('source','src'), ('target','dst'), ('uml_edge_type','generalisation')])

	_path = ''
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		if class_name == 'test':
			continue

		_path = get_value_else_default(one_myclass, 'path', '.')
		one_node = copy.deepcopy(node)
		one_node['id'] = class_name
		if one_myclass['type'] and one_myclass['type'] != 'class':
			one_node['id'] = '<' + one_myclass['type'] + '>' + class_name

		node_attrs = []
		node_meths = []

		# 'static', 'scope', 'type', 'name', 'params', 'args', 'comment')
		for variable in one_myclass[const.m_dict['var']]:
			attrs_str = ''
			if variable[const.func.scope] == 'public':
				attrs_str = '+'
			elif variable[const.func.scope] == 'protected':
				attrs_str = '#'
			elif variable[const.func.scope] == 'private':
				attrs_str = '-'
			elif variable[const.func.static] == 'True':
				attrs_str = '@'
			else:
				attrs_str = ' '

			attrs_str += ' '
			attrs_str += variable[const.func.name] #+ ' : ' + variable[const.func.type]
			node_attrs.append(attrs_str)

			if variable[const.func.type].startswith('struct '):
				var_type = variable[const.func.type].split(' ')
				if len(var_type) > 1:
					one_edge = copy.deepcopy(edge)
					one_edge['id'] = class_name + '_to_' + var_type[1]
					one_edge['source'] = class_name
					one_edge['target'] = var_type[1]
					one_edge['uml_edge_type'] = 'composition'
					edges.append(one_edge)

		for method in one_myclass[const.m_dict['method']]:
			meths_str = ''
			if method[const.func.scope] == 'public':
				meths_str = '+'
			elif method[const.func.scope] == 'protected':
				meths_str = '#'
			elif method[const.func.scope] == 'private':
				meths_str = '-'
			else:
				meths_str = ' '

			meths_str += ' '
			meths_str += method[const.func.name]  + '()'
			node_meths.append(meths_str)

		for method in one_myclass[const.m_dict['init']]:
			meths_str = ''
			if method[const.func.scope] == 'public':
				meths_str = '+'
			elif method[const.func.scope] == 'protected':
				meths_str = '#'
			elif method[const.func.scope] == 'private':
				meths_str = '-'
			else:
				meths_str = ' '

			meths_str += ' '
			meths_str += method[const.func.name]  + '()'
			if method[const.func.pure] == 'True':
				meths_str = '=0'
			node_meths.append(meths_str)

		for method in one_myclass[const.m_dict['virtual']]:
			meths_str = '~'
			meths_str += ' '
			meths_str += method[const.func.name] + '()'
			if method[const.func.pure] == 'True':
				meths_str = '=0'
			node_meths.append(meths_str)

		for super_name,super_class in one_myclass[const.m_dict['super']].iteritems():
			one_edge = copy.deepcopy(edge)
			one_edge['id'] = class_name + '_to_' + super_name
			one_edge['source'] = class_name
			one_edge['target'] = super_name
			edges.append(one_edge)

			for vtable_name, vtable in super_class.iteritems():
				vtable_class = convert_to_class(myclasses_array_dict, vtable_name)
				for method in vtable[const.m_dict['virtual']]:
					meths_str = '~'
					meths_str += ' '
					meths_str += method[const.func.name] + '(' + vtable_name + ')'
					node_meths.append(meths_str)

		one_node['attrs'] = '|'.join(node_attrs)
		one_node['meths'] = '|'.join(node_meths)
		nodes.append(one_node)

	# append graphic to classes
	myclasses_array_dict[const.graphic] = odict()
	myclasses_array_dict[const.graphic]['templates']       = [const.templ_graphic]
	myclasses_array_dict[const.graphic]['add_file_header'] = False
	myclasses_array_dict[const.graphic]['file']            = const.graphic
	myclasses_array_dict[const.graphic]['path']            = _path
	myclasses_array_dict[const.graphic]['nodes']           = nodes
	myclasses_array_dict[const.graphic]['edges']           = edges


def parse_parameters(params_str):
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
				break
	return params,args


def parse_init_constructor(myclasses_array_dict):
	# parse 1-times, process self
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		'''
		  - if no init, append one
		  - if mult-init, rename as: init, init2, init3, ...
		  - re-construct init as dict: "init":{ "scope":"public", "paremeter":"", "argument":{"para1":"arg1","para2":"arg2"}
		  - Also append this info into vtable of supers for init
		'''
		if len(one_myclass[const.m_dict['init']]) == 0:
			member_init = copy.deepcopy(const.member_init)
			member_init[const.func.name] = class_name
			one_myclass[const.m_dict['init']].append(member_init)

		for method in one_myclass[const.m_dict['init']]:
			method_setter = odict([('scope', method[const.func.scope]), \
				('name', method[const.func.name]), \
				('params', method[const.func.params]), \
				('args', method[const.func.args]), \
				('setters', odict())])
			one_myclass[const.m_dict['init_setter']].append(method_setter)

			# if have params, try match with vars (no-static)
			if method[const.func.params]:
				params,args = parse_parameters(method[const.func.params])
				for arg in args:
					for variable in one_myclass[const.m_dict['var']]:
						if variable[const.func.static] != 'True' \
							and (variable[const.func.name].lower() == arg \
								or variable[const.func.name].lower() == '_' + arg \
								or variable[const.func.name].lower() == arg + '_'):
							method_setter['setters'][variable[const.func.name]] = arg
							break # exit find first var
			
	# parse 2-times, process supers
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		super_setter = one_myclass[const.m_dict['super_setter']]
		for super_name,superclass in one_myclass[const.m_dict['super']].iteritems():
			super_class = convert_to_class(myclasses_array_dict, super_name)
			super_setter[super_name] = super_class[const.m_dict['init_setter']]


def convert_to_array_dict(myclasses_array_dict, context_dict_tree):
	for class_name, one_myclass in context_dict_tree.iteritems():
		myclasses_array_dict[class_name] = one_myclass
		if one_myclass.has_key(const.sub_classes):
			convert_to_array_dict(myclasses_array_dict, one_myclass[const.sub_classes])


def convert_to_myclasses(myclass_dict, input_dict, mysuper):
	for myclass_name, one_inputclass in input_dict.iteritems():
		names = myclass_name.replace(';',' ').replace(',',' ').split()
		for myclass_name in names:
			one_myclass = odict()
			myclass_dict[myclass_name] = one_myclass

			one_myclass['templates'] = get_value_else_default(one_inputclass, 'templates', [])
			one_myclass['add_file_header'] = get_value_else_default(mysuper, 'add_file_header', False)
			one_myclass['trace']     = get_value_else_default(mysuper, 'trace', False)
			one_myclass['copyright'] = get_value_else_default(mysuper, 'copyright', [])
			one_myclass['author']    = get_value_else_default(mysuper, 'author', []) # author with email
			one_myclass['date']      = get_value_else_default(mysuper, 'date', '')
			one_myclass['summary']   = get_value_else_default(mysuper, 'summary', [])
			one_myclass['note']      = get_value_else_default(one_inputclass, 'note', get_value_else_default(mysuper, 'note', []))

			one_myclass['path']      = get_value_else_default(mysuper, 'path', '.')
			one_myclass['namespace'] = get_value_else_default(mysuper, 'namespace', '')
			one_myclass['file']      = get_value_else_default(one_inputclass, 'file', myclass_name)
			one_myclass['name']      = myclass_name
			one_myclass['includes']  = get_value_else_default(one_inputclass, 'includes', [])
			one_myclass['comment']   = get_value_else_default(one_inputclass, 'comment', '')
			one_myclass['type']      = get_value_else_default(one_inputclass, 'type', 'class')

			# control flags
			one_myclass[const.control_super] = False  # config: enable_super
			one_myclass[const.control_vtable] = False # config: virtual
			# if static_var, remember the first static variable for initial code
			one_myclass[const.control_static_var] = '' # config: static var

			# used as C generate helper
			# config flags
			one_myclass[const.config_destructor] = get_value_else_default(one_inputclass, const.config_destructor, 'False')
			one_myclass[const.config_super] = get_value_else_default(one_inputclass, const.config_super, 'False')
			if one_myclass[const.config_destructor].lower() == 'true':
				one_myclass[const.config_super] = 'True'

			# create members
			for members in const.m_dict.values(): # avoid None Error
				if not members.startswith('supers'):
					one_myclass[members] = []

			# create supers
			supers = odict()
			one_myclass[const.m_dict['super']] = supers
			supers_setter = odict()
			one_myclass[const.m_dict['super_setter']] = supers_setter
			# append super to supers
			if mysuper.has_key('name'):
				supers[mysuper['name']] = odict()
			if one_inputclass.has_key(const.m_dict['super']):
				for super_name in one_inputclass[const.m_dict['super']]:
					supers[super_name] = odict()

			if one_myclass[const.config_destructor].lower() == 'true':
				one_myclass[const.m_dict['virtual']].append(const.member_destructor);
				one_myclass[const.m_dict['virtual']].append(const.member_free);

			# split members into functions and vars ...
			if one_inputclass.has_key(const.members):
				for member_input in one_inputclass[const.members]:
					member_category = ''
					member_detail = copy.deepcopy(const.member_default)

					member_mode = len(member_input)
					if  member_mode == const.func_mode.cat_name:
						member_category = member_input[0]
						member_detail[const.func.name] = member_input[1]
					elif member_mode == const.func_mode.cat_name_type:
						member_category = member_input[0]
						member_detail[const.func.name] = member_input[1]
						member_detail[const.func.type] = member_input[2]
					elif member_mode >= const.func_mode.cat_name_type_args:
						member_category = member_input[0]
						member_detail[const.func.name]  = member_input[1]
						member_detail[const.func.type]  = member_input[2]
						member_detail[const.func.params]= member_input[3]

						# scope and comment
						if member_mode >= const.func_mode.cat_name_type_args_scope:
							if member_input[4]:
								member_detail[const.func.scope] = member_input[4]
							if member_mode >= const.func_mode.cat_name_type_args_scope_comment:
								if member_input[5]:
									member_detail[const.func.comment] = textwrap_with_code(member_input[5])
								if member_mode >= const.func_mode.cat_name_type_args_scope_comment_pseudocode:
									if member_input[6]:
										member_detail[const.func.pseudocode] = textwrap_with_code(member_input[6])

						if member_input[3] and member_category != 'var':
							params,args = parse_parameters(member_input[3])
							member_detail[const.func.args] = ', '.join(args)
					else:
						raise Exception('class {0} member_input size is {1} greater than 4: {2}'.\
						  format(myclass_name, member_input, member_mode))

					# Check if constructor: change category
					if member_detail[const.func.name] == myclass_name \
						or member_detail[const.func.name] == 'constructor' \
						or member_detail[const.func.name] == 'new' \
						or member_detail[const.func.name] == 'init':
						member_category = 'init'

					#@TODO warning member_name conflict
					if one_myclass.has_key(const.m_dict[member_category]):
						# static=True:
						#   - when methods|vars, means it's static
						if member_category == 'static_method' \
							or member_category == 'static_var':
							member_detail[const.func.static] = 'True'
						elif member_category == 'pure_virtual':
							member_detail[const.func.pure] = 'True'
						elif member_category == 'init':
							member_detail[const.func.static] = 'False'
							member_detail[const.func.comment] = const.constructor_comment
							# Rename:
							# '' -> classname
							for one_member in one_myclass[const.m_dict['init']]:
								if member_detail[const.func.name] == one_member[const.func.name]:
									member_detail[const.func.name] = myclass_name
									break

						one_myclass[const.m_dict[member_category]].append(member_detail)
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
	mysuper['note']             = get_value_else_default(input_dict, 'note', get_value_else_default(input_dict, 'comment', []))

	# generate path
	mysuper['path']             = get_value_else_default(input_dict, 'path', def_path)
	mysuper['namespace']        = get_value_else_default(input_dict, 'namespace', def_path)

	mysuper[const.config_super] = 'False'
	mysuper[const.config_destructor] = 'False'
	mysuper[const.m_dict['super']]   = []
	if input_dict.has_key('classes'):
		convert_to_myclasses(context_dict_tree, input_dict['classes'], mysuper)

	return context_dict_tree


def render_namespace(input_file, code_style, output_dir):
	try:
		if not os.path.isfile(input_file):
			raise Exception('file *{0}* not exists'.format(input_file))

		#input_dict = json.load(open(input_file), object_pairs_hook=collections.OrderedDict)
		input_dict = JsonComment(json).load(open(input_file), object_pairs_hook=collections.OrderedDict)
		#print '"LOADING":\n',json.dumps(input_dict, sort_keys=False, indent=3)

		context_dict_tree = convert_namespace_to_tree(\
		  os.path.splitext(os.path.basename(input_file))[0], input_dict)
		#print '"JSON CONVERT TO TREE":\n',json.dumps(context_dict_tree, sort_keys=False, indent=3)

		myclasses_array_dict = odict()
		convert_to_array_dict(myclasses_array_dict, context_dict_tree)
		#print '"JSON CONVERT TO ARRAY":\n',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)

		parse_override_function(myclasses_array_dict)
		#print '"JSON PARSE OVERRIDE":\n',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)

		parse_helper_flag(myclasses_array_dict)
		#print '"JSON PARSE SUPPORT FLAGS":\n',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)

		parse_init_constructor(myclasses_array_dict)
		#print '"JSON INIT-CONSTRUCTOR":\n',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)

		gen_pynsource_graphic_nodes(myclasses_array_dict)
		#print '"JSON GRAPHIC":\n',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)

		flush_unused_and_makeup(myclasses_array_dict)
		if code_style == 'c':  # language not support oop
			print '"JSON FINAL":\n',json.dumps(myclasses_array_dict, sort_keys=False, indent=3)
			#print '"YAML FINAL":\n',json.dump(myclasses_array_dict, default_flow_style=False, indent=3)
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

