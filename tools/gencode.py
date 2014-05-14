#!/usr/bin/python
#
# Requirement
# ===========
# $ sudo pip install jinja2
# $ sudo pip install jsoncomment
#
# QuickStart
# ==========
# ./gencode.py --file json/factory-method.json
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
import jinja
import re
from odict import odict
from time import gmtime, strftime
from config import *
from graphic import *
from comn import *


def render_array_to_file(myclasses_array_dict, code_style, output_dir):
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		jinja.render_class_to_file(one_myclass, code_style, output_dir)


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


def parse_override_function(myclasses_array_dict):
	while True:
		should_be_continue = False
		for class_name, one_myclass in myclasses_array_dict.iteritems():
			my_supers = one_myclass[const.m_dict['super']]

			override_set = set()
			if not one_myclass.has_key(const.override_all):
				one_myclass[const.override_all] = False
				for over_function in one_myclass[const.m_dict['override']]:
					if over_function[const.func.name] == const.override_all:
						one_myclass[const.override_all] = True
						break
					override_set.add(over_function[const.func.name])

			for super_name in my_supers.keys():
				super_class = convert_to_class(myclasses_array_dict, super_name)
				# create new inherit-vtable
				if (not my_supers[super_name].has_key(super_name)) \
					and super_class[const.m_dict['virtual']]:
					should_be_continue = True
					my_supers[super_name][super_name] = odict()
					my_supers[super_name][super_name]['path'] = super_name
					my_supers[super_name][super_name][const.control_super] = False
					v_func_list = []
					if not my_supers[super_name][super_name].has_key(const.m_dict['virtual']):
						my_supers[super_name][super_name][const.m_dict['virtual']] = v_func_list

					# check override function
					for v_function in super_class[const.m_dict['virtual']]:
						if one_myclass[const.override_all] \
							or v_function[const.func.name] in override_set:
							v_func_list.append(v_function)

				# clone inherit-vtable from supers
				super2_supers = super_class[const.m_dict['super']]
				for super2_name, super2_class in super2_supers.iteritems():
					for super2_vtable_name, super2_vtable in super2_class.iteritems():
						if not my_supers[super_name].has_key(super2_vtable_name):
							should_be_continue = True
							vtable_class = convert_to_class(myclasses_array_dict, super2_vtable_name)
							my_supers[super_name][super2_vtable_name] = odict()
							my_supers[super_name][super2_vtable_name]['path'] = super_name + '.' + super2_vtable['path']
							my_supers[super_name][super2_vtable_name][const.control_super] = False
							v_func_list = []
							if not my_supers[super_name][super2_vtable_name].has_key(const.m_dict['virtual']):
								my_supers[super_name][super2_vtable_name][const.m_dict['virtual']] = v_func_list

							# check override function
							for v_function in vtable_class[const.m_dict['virtual']]:
								if v_function[const.func.name] in override_set:
									v_func_list.push(v_function)

		if not should_be_continue:
			break


def parse_helper_flag(myclasses_array_dict):
	#1. const.control_vtable
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		'''
		it's auto-gen field used to control code-gen
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

	#1. const.control_super
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

			# parse 1-times for self's control_super
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

		# parse 2-times for supers's control_super
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
						vtable[const.control_super] = vtable_class[const.control_super]

		if not should_be_continue:
			break


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

			one_myclass['name']      = myclass_name
			one_myclass['file']      = get_value_else_default(one_inputclass, 'file',      myclass_name)
			one_myclass['path']      = get_value_else_default(one_inputclass, 'path',      get_value_else_default(mysuper, 'path',      '.'))
			one_myclass['namespace'] = get_value_else_default(one_inputclass, 'namespace', get_value_else_default(mysuper, 'namespace', ''))
			one_myclass['file_note'] = get_value_else_default(one_inputclass, 'file_note', get_value_else_default(mysuper, 'file_note', False))
			one_myclass['trace']     = get_value_else_default(one_inputclass, 'trace',     get_value_else_default(mysuper, 'trace',     False))
			one_myclass['copyright'] = get_value_else_default(one_inputclass, 'copyright', get_value_else_default(mysuper, 'copyright', []))
			one_myclass['author']    = get_value_else_default(one_inputclass, 'author',    get_value_else_default(mysuper, 'author',    [])) # author with email
			one_myclass['date']      = get_value_else_default(one_inputclass, 'date',      get_value_else_default(mysuper, 'date',      ''))
			one_myclass['summary']   = get_value_else_default(one_inputclass, 'summary',   get_value_else_default(mysuper, 'summary',   []))
			one_myclass['note']      = get_value_else_default(one_inputclass, 'note',      get_value_else_default(mysuper, 'note',      ''))
			one_myclass['comment']   = get_value_else_default(one_inputclass, 'comment',   get_value_else_default(mysuper, 'comment',   ''))
			one_myclass['message']   = get_value_else_default(one_inputclass, 'message',   get_value_else_default(mysuper, 'message',   ''))
			one_myclass['error']     = get_value_else_default(one_inputclass, 'error',     get_value_else_default(mysuper, 'error',     ''))

			one_myclass['templates'] = get_value_else_default(one_inputclass, 'templates', [])
			one_myclass['includes']  = get_value_else_default(one_inputclass, 'includes',  [])
			one_myclass['type']      = get_value_else_default(one_inputclass, 'type',      'class')

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

					if one_myclass.has_key(const.m_dict[member_category]):
						if member_category == 'static_method' \
							or member_category == 'static_var':
							member_detail[const.func.static] = 'True'
							one_myclass[const.m_dict[member_category]].append(member_detail)
						elif member_category == 'pure_virtual':
							member_detail[const.func.pure] = 'True'
							one_myclass[const.m_dict[member_category]].append(member_detail)
						elif member_category == 'property':
							property_name = member_detail[const.func.name]
							member_var = copy.deepcopy(member_detail)
							member_set = copy.deepcopy(member_detail)
							member_get = copy.deepcopy(member_detail)
							one_myclass[const.m_dict['var']].append(member_var)
							one_myclass[const.m_dict['method']].append(member_set)
							one_myclass[const.m_dict['method']].append(member_get)

							member_var[const.func.name] = '_' + property_name
							member_var[const.func.scope] = 'private'

							member_set[const.func.name] = 'set_' + property_name
							member_set[const.func.type] = 'void'
							member_set[const.func.params] = ''
							if member_detail[const.func.params]: # is array
								member_set[const.func.params] = member_detail[const.func.type] + ' *' + property_name + ', int ' + property_name + '_sz'
							else:
								member_set[const.func.params] = member_detail[const.func.type] + ' ' + property_name
							params,args = parse_parameters(member_set[const.func.params])
							member_set[const.func.args] = ', '.join(args)

							member_get[const.func.name] = 'get_' + property_name
							if member_detail[const.func.params]: # is array
								member_get[const.func.type] = member_detail[const.func.type] + ' *'
							else:
								member_get[const.func.type] = member_detail[const.func.type]
							member_get[const.func.params] = ''
							member_get[const.func.args] = ''
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
	mysuper['file_note'] = get_value_else_default(input_dict, 'file_note', False)
	mysuper['trace']     = get_value_else_default(input_dict, 'trace',     False)
	mysuper['copyright'] = get_value_else_default(input_dict, 'copyright', [])
	mysuper['author']    = get_value_else_default(input_dict, 'author',    []) # author with email
	mysuper['date']      = get_value_else_default(input_dict, 'date',      strftime("%Y-%m-%d", gmtime()))
	mysuper['summary']   = get_value_else_default(input_dict, 'summary',   [])
	mysuper['note']      = get_value_else_default(input_dict, 'note',      [])
	mysuper['comment']   = get_value_else_default(input_dict, 'comment',   [])
	mysuper['message']   = get_value_else_default(input_dict, 'message',   '')
	mysuper['error']     = get_value_else_default(input_dict, 'error',     '')

	# generate path
	mysuper['path']      = get_value_else_default(input_dict, 'path',      def_path)
	mysuper['namespace'] = get_value_else_default(input_dict, 'namespace', def_path)

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

		json_file = open(input_file).read()
		#input_dict = json.loads(json_file.replace('\t', '    '), object_pairs_hook=collections.OrderedDict)
		input_dict = JsonComment(json).loads(json_file.replace('\t', '    '), object_pairs_hook=collections.OrderedDict)
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
	parser.add_argument('--dir', metavar='output dir', help='Output Directory', required=False, default='_code')
	parser.add_argument('--code', metavar='code type', help='Language Choose', choices=['c','cplus','java','csharp','python'], required=False, default='c')
	args = vars(parser.parse_args())

	render_namespace(args['file'], args['code'], args['dir'])

