
def get_value_else_default(rdict, key, def_val):
	rval = rdict.get(key, def_val)
	if not rval:
		rval = def_val
	return rval


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


def convert_to_class(myclasses_array_dict, class_name):
	if myclasses_array_dict.has_key(class_name) and len(myclasses_array_dict[class_name]) > 0:
		return myclasses_array_dict[class_name];
	else:
		raise Exception('class *{0}* not exist'.format(class_name))


