# https://groups.google.com/forum/#!topic/pocoo-libs/3yZl8vHJ9fI
#
# {% set svc_list = [] %}
# {% set if_list = [] %}
# {% set ip_list = [] %}
# 
# {% for c in cf %}
# {% if c is re_match("^service_", "i") %}
# {% set svcname = c | re_sub("^service_", "", "i", 1) %}
# {% set svc_list = svc_list + [svcname] %}
# {% endif %}
# {% if c is re_match("^net_iface_") %}
# {% set ifname = c | re_sub("^net_iface_", "") %}
# {% set if_list = if_list + [ifname] %}
# {% endif %}
# {% if c is re_match("^ipv4_") %}
# {% set ipname = c | re_sub("^ipv4_(.*)", "ip4-\\1") | re_sub("_", ".")
# %}
# {% set ip_list = ip_list + [ipname] %}
# {% endif %}
# {% endfor %}
# 
# Enabled services:
# {% for s in svc_list %}
# SVC({{loop.index0}})={{s}}
# {% endfor %}
# 
# Interfaces:
# {% for s in if_list %}
# IF({{loop.index0}})={{s}}
# {% endfor %}
# 
# IP addresses:
# {% for s in ip_list %}
# IP({{loop.index0}})={{s}}
# {% endfor %}

import re

def get_re_flags(flagstr):
    reflags = 0
    if flagstr:
        if flagstr.find("i") > -1: reflags |= re.IGNORECASE
        if flagstr.find("l") > -1: reflags |= re.LOCALE
        if flagstr.find("m") > -1: reflags |= re.MULTILINE
        if flagstr.find("s") > -1: reflags |= re.DOTALL
        if flagstr.find("u") > -1: reflags |= re.UNICODE
        if flagstr.find("x") > -1: reflags |= re.VERBOSE
    return reflags

def is_contain(s, sub_str):
    if sub_str in s:
        return True
    else:
        return False

def is_re_match(s, rs, flagstr=None):
    reflags = get_re_flags(flagstr)
    if re.search(rs, s, reflags):
        return True
    else:
        return False

def filter_re_sub(s, rs, repl, flagstr=None, count=0):
    reflags = get_re_flags(flagstr)
    myre = re.compile(rs, reflags)
    return re.sub(myre, repl, s, count)

def filter_re_escape(s):
    return re.escape(s)

