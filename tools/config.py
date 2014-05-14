import const as const
from enum import *
from odict import odict

# Setup syntax constants
const.auto_comn_tmpl_file = 'autogen_.jinja'
const.classes             = 'classes'
const.sub_classes         = 'inheritances'
## member var and method
const.members             = 'members'
const.override_all        = '<ALL>'
const.textwrap            =['note', 'comment', 'copyright']

const.m_dict              = odict([\
                            ('init'         ,'inits'), \
                            ('init_setter'  ,'inits_setter'), \
                            \
                            ('var'          ,'vars'), \
                            ('static_var'   ,'vars'),\
                            \
                            ('property'     ,'methods'),\
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
# grahic: node&edge
const.graphic             = 'graphic'
const.templ_graphic       = '_graphic'
const.graphic_node        = odict([('type','node'), ('id','name'), ('attrs',''), ('meths',''), ('x',1), ('y',1), ('width',1), ('height',1)])
const.graphic_edge        = odict([('type','edge'), ('id','name'), ('source','src'), ('target','dst'), ('uml_edge_type','generalisation')])

