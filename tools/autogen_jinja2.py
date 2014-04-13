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
mysyn.m_type = enum('routine', 'method', 'virtual', 'override', 'variable')
mysyn.m_set =      ['routines','methods','virtuals','overrides','vars']
mysyn.m_str = mysyn.m_type.reverse_mapping

# cat-category
mysyn.func_mode = enum('_None', '_cat', 'cat_name', 'cat_type_name', 'cat_type_name_args')
mysyn.func =      enum('scope', 'type', 'name', 'args')


def render_one_to_file(x, dir_name, files):
	templateEnv,templateVars,output_dir = x

	for one_file in files :
		if not one_file.startswith('_'):
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
	os.path.walk(tmpl_dir, render_one_to_file, (templateEnv,templateVars,output_dir))


def get_value_else_default(rdict, key, def_val):
	rval = rdict.get(key, def_val)
	if not rval:
		rval = def_val
	return rval

def render_tree_to_file(context_dict_tree, code_style, output_dir):
	for class_name, class_detail in context_dict_tree.iteritems():
		render_class_to_file(class_detail, code_style, output_dir)
		if mysyn.sub_classes in class_detail:
			render_tree_to_file(class_detail[mysyn.sub_classes], code_style, output_dir)


def convert_to_myclasses(myclass_dict, input_dict, mysuper):
	for myclass_name, one_inputclass in input_dict.iteritems():
		one_myclass = odict()
		myclass_dict[myclass_name] = one_myclass
		one_myclass['path'] = get_value_else_default(mysuper, 'path', '.')
		one_myclass['namespace'] = get_value_else_default(mysuper, 'namespace', 'anonymouse')
		one_myclass['file'] = get_value_else_default(one_inputclass, 'file', myclass_name)
		one_myclass['name'] = myclass_name
		one_myclass['NAME'] = myclass_name.upper()
		one_myclass['super'] = get_value_else_default(mysuper, 'name', '')

		# split members into functions and vars ...
		one_myclass[mysyn.m_set[mysyn.m_type.routine]]  = []
		one_myclass[mysyn.m_set[mysyn.m_type.method]]   = []
		one_myclass[mysyn.m_set[mysyn.m_type.virtual]]  = []
		one_myclass[mysyn.m_set[mysyn.m_type.override]] = []
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
					virtual_find = False
					for virtual_member in \
					  mysuper[          mysyn.m_set[mysyn.m_type.virtual]]:
						if virtual_member[mysyn.func.name] == member_detail[mysyn.func.name]:
							virtual_find = True
							one_myclass[mysyn.m_set[mysyn.m_type.override]].append(virtual_member)

					if not virtual_find:
						raise Exception('member override, but no prototype in super: {0}'.format(member_detail))
				elif member_category == mysyn.m_str[mysyn.m_type.variable]:
					one_myclass[        mysyn.m_set[mysyn.m_type.variable]].append(member_detail)

		''' **Just needed by C code.**
		1. "enable_super" come from config
		2. "_enable_super" is auto-gen field used to control code-gen
		   If "_enable_super" is "True", means should support super call:
		    * As base class, who have no super at all
			  - can be control by **config**
			  - must have virtual-function,
			  - must user requie (config) 'enable_super'
			  - when implement, must append super pointer in ops
		    * As derive class,
			  - just control by super, **config have no use at all**.
			  - must exist super to sure self is really 'derive' class
			  - the parent must have enable_super already
			  - when implement, must init with super
		'''
		one_myclass['_enable_super'] = False
		if one_myclass['super']: # As derive class
			if mysuper['_enable_super'] == True: # if parent support super, child should be init with super
				one_myclass['_enable_super'] = True
		else: # As base class
			if len(one_myclass[mysyn.m_set[mysyn.m_type.virtual]]) > 0:
				enable_super = get_value_else_default(one_inputclass, 'enable_super', 'False')
				if enable_super.lower() == 'true':
					one_myclass['_enable_super'] = True
		
		'''
		"_enable_virtual" is auto-gen field used to control code-gen
		    - must be basic class who have no super
		    - must have virtual function
		    - when implement, must have ops (for C code) or "virtual" keyword (for others) keyword
		        + so as derive class, auto have virtual but this flag is false, that's OK.
		'''
		one_myclass['_enable_virtual'] = False
		if not one_myclass['super'] and len(one_myclass[mysyn.m_set[mysyn.m_type.virtual]]) > 0: # As basic class
			one_myclass['_enable_virtual'] = True


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
	mysuper['enable_super'] = 'False'
	mysuper['super'] = ''
	if input_dict.has_key('classes'):
		convert_to_myclasses(context_dict_tree, input_dict['classes'], mysuper)

	return context_dict_tree


def render_namespace(input_file, code_style, output_dir):
	try:
		if not os.path.isfile(input_file):
			raise Exception('file {0} not exists'.format(input_file))

		input_dict = json.load(open(input_file), object_pairs_hook=collections.OrderedDict)
		#print 'NAMESPACE loading:',json.dumps(input_dict, sort_keys=False, indent=2)

		context_dict_tree = convert_namespace_to_tree(input_dict)
		print json.dumps(context_dict_tree, sort_keys=False, indent=2)

		render_tree_to_file(context_dict_tree, code_style, output_dir)
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
	parser.add_argument('--dir', metavar='output dir', help='Output Directory', required=False, default='autogen_code')
	parser.add_argument('--code', metavar='code type', help='Language Choose', choices=['c','cplus','java','csharp'], required=False, default='c')
	args = vars(parser.parse_args())

	render_namespace(args['file'], args['code'], args['dir'])

