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
import copy
import jinja2
#import const as syntax
from odict import odict

# Setup syntax constants
#syntax.classes = 'classes'  # the namespace's sub-classes

# Setup jinja2 render template
templateLoader = jinja2.FileSystemLoader( searchpath="." )
templateEnv = jinja2.Environment( loader=templateLoader )
templ_header = templateEnv.get_template( "header.jinja" )
templ_source = templateEnv.get_template( "source.jinja" )
#outputText = template.render( templateVars ) # dictionary


# templateVars:
# path, file,
# NAME, name, super
# members:(pre,func,post),
def render_one_to_file(templateVars):
	outputText = templ_header.render( templateVars )
	f = open('{0}/{1}.{2}'.format(one_class_dict['path'], one_class_dict['file'], 'h'), 'w')
	f.write(outputText)
	f.close()

	outputText = templ_source.render( templateVars )
	f = open('{0}/{1}.{2}'.format(one_class_dict['path'], one_class_dict['file'], 'c'), 'w')
	f.write(outputText)
	f.close()


def render_tree_to_file(context_dict_tree):
	for class_name, class_detail in context_dict_tree.iteritems():
		render_one_to_file(class_detail)
		if 'inheritance' in input_dict:
			render_tree_to_file(class_detail['inheritance'])


def convert_to_myclasses(myclass_dict, input_dict, mysuper):
	for myclass_name, one_inputclass in input_dict.iteritems():
		one_myclass = odict()
		myclass_dict[myclass_name] = one_myclass
		one_myclass['path'] = mysuper.get('path', '.')
		one_myclass['file'] = one_inputclass.get('file', myclass_name)
		one_myclass['name'] = myclass_name
		one_myclass['NAME'] = myclass_name.upper()
		one_myclass['enable_super'] = one_inputclass.get('enable_super', False)
		one_myclass['super'] = mysuper.get('name', '')
		#one_myclass['have_super'] = length()

		# split members into ops and vars ...
		one_myclass['ops'] = odict()
		one_myclass['routines'] = odict()
		one_myclass['methods'] = odict()
		one_myclass['vars'] = odict()
		if one_inputclass.has_key('members'):
			for member_name, member_detail in one_inputclass['members'].iteritems():
				for cell_type, cell_val in member_detail.iteritems():
					if cell_type == 'type':
						member_type = cell_val
					elif cell_type == 'pre':
						member_pre = cell_val
					elif cell_type == 'post':
						member_post = cell_val
					else:
						raise Exception('unkown member subcell\'s type {0}'.format(cell_type))

				#@TODO check member_name conflict

				if mysuper.has_key('ops'):
					one_myclass['ops'] = copy.deepcopy(mysuper['ops'])
					for ops_member_name, ops_member_detail in one_myclass['ops'].iteritems():
						ops_member_detail[0] = 'False'

				if member_type == 'routine': # global function
					one_myclass['routines'][member_name] = ['True', member_pre, member_name, member_post]
				elif member_type == 'method': # private function
					one_myclass['methods'][member_name] = ['True', member_pre, member_name, member_post]
				elif member_type == 'virtual': # implement as ops function pointer
					one_myclass['ops'][member_name] = ['True', member_pre, member_name, member_post]
				elif member_type == 'override': # copy function protocol from super class
					if one_myclass['ops'].has_key(member_name):
						one_myclass['ops'][member_name][0] = 'True'
				elif member_type == 'variable':
					one_myclass['vars'][member_name] = ['True', member_pre, member_name, member_post]

		# recursive sub-classes
		one_myclass['inheritance'] = odict()
		if one_inputclass.has_key('inheritance'):
			for subclass_name, subclass_detail in one_inputclass['inheritance'].iteritems():
				sub_one_myclass = odict()
				one_myclass['inheritance'][subclass_name] = sub_one_myclass
				convert_to_myclasses(sub_one_myclass, subclass_detail, one_myclass)

	return myclass_dict


# convert config data to render data
def convert_namespace_to_tree(input_dict):
	mysuper = odict()
	context_dict_tree = odict()

	mysuper['path'] = input_dict.get('path', '.')
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

if __name__ == '__main__':
	for index, item in enumerate(sys.argv):
		if index > 0 :
			print "{0}. generate {1}".format(index, str(item))
			render_namespace(item)

