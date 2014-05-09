{%- import '_macro.jinja' as func -%}

{{ func.file_header(file_header_name,copyright,author,date,summary) }}
#include <stdio.h>
#include <stdlib.h>

#include <mycommon.h>
#include <myobj.h>
{% if trace %}#include <mytrace.h>{% endif %}
#include <test_suite.h>
{%- if includes -%}
	{%- for one_include in includes %}
#include "{{ one_include }}.h"
	{%- endfor -%}
{%- endif %}

{{ func.macro_loop_functions(trace,name,methods,'methods',mode='impl-print',qualifier='static') }}

static int test_main_entry(char *output, size_t sz)
{
	TODO(Please add our **test** code here ...)
	return 0;
}

void main_entry_test(void);
void main_entry_test(void)
{
	my_test_suite_add(test_main_entry, "Test {{ namespace }}");
}
