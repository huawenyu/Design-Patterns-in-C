import copy
from config import *
from comn import *

def gen_edge_from_type_string(one_myclass, type_str, edges):
	if type_str.startswith('struct '):
		var_type = type_str.split(' ')
		if len(var_type) > 1:
			one_edge = copy.deepcopy(const.graphic_edge)
			one_edge['id'] = one_myclass['name'] + '_to_' + var_type[1]
			one_edge['source'] = one_myclass['name']
			one_edge['target'] = var_type[1]
			one_edge['uml_edge_type'] = 'composition'
			edges.append(one_edge)


def gen_edge_from_function(one_myclass, method, edges):
	gen_edge_from_type_string(one_myclass, method[const.func.type], edges)
	if method[const.func.params]:
		params,args = parse_parameters(method[const.func.params])
		for param in params:
			gen_edge_from_type_string(one_myclass, param, edges)


def gen_pynsource_graphic_nodes(myclasses_array_dict):
	nodes = []
	edges = []

	_path = ''
	for class_name, one_myclass in myclasses_array_dict.iteritems():
		if class_name == 'test':
			continue

		_path = get_value_else_default(one_myclass, 'path', '.')
		one_node = copy.deepcopy(const.graphic_node)
		one_node['id'] = class_name
		## if change id, the edge also should changed
		#if one_myclass['type'] and one_myclass['type'] != 'class':
		#	one_node['id'] = '<' + one_myclass['type'] + '>' + class_name

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
			gen_edge_from_type_string(one_myclass, variable[const.func.type], edges)

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

			gen_edge_from_function(one_myclass, method, edges)

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

			gen_edge_from_function(one_myclass, method, edges)

		for method in one_myclass[const.m_dict['virtual']]:
			meths_str = '~'
			meths_str += ' '
			meths_str += method[const.func.name] + '()'
			if method[const.func.pure] == 'True':
				meths_str = '=0'
			node_meths.append(meths_str)

			gen_edge_from_function(one_myclass, method, edges)

		for super_name,super_class in one_myclass[const.m_dict['super']].iteritems():
			one_edge = copy.deepcopy(const.graphic_edge)
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

					# avoid more edge, leave this to super-self
					#gen_edge_from_function(one_myclass, method, edges)

		one_node['attrs'] = '|'.join(node_attrs)
		one_node['meths'] = '|'.join(node_meths)
		nodes.append(one_node)

	offset = 60
	for idx, one_node in enumerate(nodes):
		one_node['x'] += offset*idx;
		one_node['y'] += offset*idx;

	# append graphic to classes
	myclasses_array_dict[const.graphic] = odict()
	myclasses_array_dict[const.graphic]['templates']       = [const.templ_graphic]
	myclasses_array_dict[const.graphic]['file_note']       = False
	myclasses_array_dict[const.graphic]['file']            = const.graphic
	myclasses_array_dict[const.graphic]['path']            = _path
	myclasses_array_dict[const.graphic]['nodes']           = nodes
	myclasses_array_dict[const.graphic]['edges']           = edges

