#!/usr/bin/python
#
# http://jinja.pocoo.org/docs/templates/
#

import os
import os.path
import jinja2
import ext_re
import re


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
	templateLoader = jinja2.FileSystemLoader(searchpath=os.path.abspath(tmpl_dir))
	templateEnv = jinja2.Environment(loader=templateLoader, extensions=["jinja2.ext.do",])
	#templateEnv.line_statement_prefix = '##'
	#templateEnv.keep_trailing_newline = True
	templateEnv.tests['re_match'] = ext_re.is_re_match
	templateEnv.tests['contain'] = ext_re.is_contain
	templateEnv.filters['re_sub'] = ext_re.filter_re_sub
	templateEnv.filters['re_escape'] = ext_re.filter_re_escape

	os.path.walk(tmpl_dir, render_one_to_file, (templateEnv,templateVars,code_style,output_dir))

