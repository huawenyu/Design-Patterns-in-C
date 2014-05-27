# If only use a proj's define: define it in the proj's Makefile
# If add more option: define EXTRA_* in the proj's Makefile which will be merged with this global one
#_______________________________________________________________________________
#                                                         PROJECTS GLOBAL CONFIG
# 1, enable, otherwise comment it
#VERBOSE   = 1
DEBUGMODE = 1

G_MACROS  =
G_INCS    = $(TOPDIR)util .
G_LIBDIRS = $(TOPDIR)util
G_LIBS    = util
G_CPPFLAGS= -Wall -Werror -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wunused-value -Wno-unused-parameter -Wformat \
  -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wredundant-decls
G_LDFLAGS =
G_ARFLAGS = -cr

#_______________________________________________________________________________
#                                                                   IGNORE BELOW
include $(TOPDIR)config_ext.mk
