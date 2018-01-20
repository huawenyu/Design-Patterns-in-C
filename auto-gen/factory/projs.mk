include topdir.mk
#_______________________________________________________________________________
#                                                                   IGNORE ABOVE
# if = <auto>: auto assign value
#
# target: foo, foo.a, foo.so
TARGET         = #<auto>
SOURCES        = #<auto>
SUBPROJS       = #<auto>
SUBDIRS        = #<auto>

# add more to global config
EXTRA_MACROS   =
EXTRA_INCS     = #$(TOPDIR)include
EXTRA_LIBDIRS  = #$(TOPDIR)lib
EXTRA_LIBS     =
EXTRA_CPPFLAGS =
EXTRA_LDFLAGS  =
EXTRA_ARFLAGS  =

# this proj donnot use global config
#MACROS        =
#INCS          =
#LIBDIRS       =
#LIBS          =
#CPPFLAGS      =
#LDFLAGS       =
#ARFLAGS       =

#_______________________________________________________________________________
#                                                                   IGNORE BELOW
include $(TOPDIR)config.mk
