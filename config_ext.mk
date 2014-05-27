#_______________________________________________________________________________
#                                                               HELP&EXTRA_PHONY
EXTRA_PHONY := help auto clean_auto runall run_all

help:
#	@echo "____________________________________________________________"
	@echo "make			Build All"
	@echo "make target=debug|release|sample|test	Assign target"
#	@echo "____________________________________________________________"
	@echo "make auto		Auto gen-raw Makefile (skip top-Makefile and the exist)"
	@echo "make clean_auto		Clear all auto-gen Makefile"
#	@echo "____________________________________________________________"
	@echo "make run		Run the file"
	@echo "make runall		Run all executable file"

auto:
#	find * -type d -exec sh -c '(cd {} && ls)' \;
	@find * -type d -exec sh -c '(\
		cd {} && \
		if ! [ -a Makefile ]; then \
			cp $(TOPDIR)tpl_make.mk Makefile && \
			cp $(TOPDIR)tpl_top.mk topdir.mk; \
		fi; \
		)' \;
	@echo "Auto add Makefile finished"

clean_auto:
	-@find * -name topdir.mk | grep / | xargs -r -n1 rm
	-@find * -name Makefile  | grep / | xargs -r -n1 rm
	@echo "Clear all auto-gen Makefile finished"

SplitLine := '=========================================='
AllRunners := $(shell find * -executable -type f)
runall run_all:
	@echo $(SplitLine)
	@$(foreach var,$(AllRunners),\
		./$(var);\
		echo $(SplitLine);\
	)

#_______________________________________________________________________________
#                                                             FLAGS DEFINE&MERGE
# macros, -D
ifndef MACROS
MACROS    = $(G_MACROS)
endif

# include path, -I
ifndef INCS
INCS      = $(G_INCS)
endif

# library path, -L, no-prefix 'lib'
ifndef LIBDIRS
LIBDIRS   = $(G_LIBDIRS)
endif

# library, -l
ifndef LIBS
LIBS = $(G_LIBS)
endif

ifndef CPPFLAGS
CPPFLAGS  = $(G_CPPFLAGS)
ifdef VERBOSE
$(info "Using Common-CPPFLAGS $(CPPFLAGS)" )
endif
endif

ifndef LDFLAGS
LDFLAGS   = $(G_LDFLAGS)
ifdef VERBOSE
$(info "Using Common-LDFLAGS $(LDFLAGS)" )
endif
endif

ifndef ARFLAGS
ARFLAGS   = $(G_ARFLAGS)
ifdef VERBOSE
$(info "Using Common-ARFLAGS $(ARFLAGS)" )
endif
endif

# append extra config
MACROS      += $(EXTRA_MACROS)
INCS        += $(EXTRA_INCS)
LIBDIRS     += $(EXTRA_LIBDIRS)
LIBS        += $(EXTRA_LIBS)
CPPFLAGS    += $(EXTRA_CPPFLAGS)
LDFLAGS     += $(EXTRA_LDFLAGS)
ARFLAGS     += $(EXTRA_ARFLAGS)

# includes
CFLAGS      := $(foreach var,$(INCS), -I$(var) ) $(CFLAGS)
CPPFLAGS    := $(foreach var,$(INCS), -I$(var) ) $(CPPFLAGS)
CXXFLAGS    := $(foreach var,$(INCS), -I$(var) ) $(CXXFLAGS)
# macros
CFLAGS      := $(foreach var,$(MACROS), -D $(var) ) $(CFLAGS)
CPPFLAGS    := $(foreach var,$(MACROS), -D $(var) ) $(CPPFLAGS)
CXXFLAGS    := $(foreach var,$(MACROS), -D $(var) ) $(CXXFLAGS)
#
LDFLAGS     := $(foreach var,$(LIBDIRS), -L$(var) ) $(LDFLAGS)
LIBRARIES   += $(LIBS)

#_______________________________________________________________________________
#                                                             AUTO CREATE&DEFINE
# software
CC          := gcc
CXX         := g++
GDC         := gdc
AS          := nasm
LD          := g++
AR          := ar
MAKE        := make
# no-support mix c,cpp
ifneq (,$(wildcard *.c))
    CC = gcc
    LD = gcc
endif
ifneq (,$(wildcard *.C *.cc *.cpp *.CPP *.c++ *.cp *.cxx))
    CC = g++
    LD = g++
endif

ifneq (,$(findstring <auto>,$(SUBDIRS)))
    subdirs := $(shell find * -maxdepth 0 -type d)
    restDir := $(filter-out $(SUBDIRS),$(subdirs))
    SUBDIRS := $(subst <auto>,$(restDir),$(SUBDIRS))
    ifdef VERBOSE
    $(info "Auto-SUBDIRS $(SUBDIRS)" )
    endif
endif

ifneq (,$(findstring <auto>,$(SUBPROJS)))
    SUBPROJS := $(addsuffix .mk,$(SUBPROJS))
    subprojs := $(wildcard *.mk)
    stds := $(SUBPROJS) topdir.mk edam.mk config.mk config_ext.mk tpl_make.mk tpl_top.mk
    restProjs := $(filter-out $(stds),$(subprojs))

    restProjs := $(basename $(restProjs))
    SUBPROJS := $(basename $(SUBPROJS))
    SUBPROJS := $(subst <auto>,$(restProjs),$(SUBPROJS))
    ifdef VERBOSE
    $(info "Auto-SUBPROJS $(SUBPROJS)" )
    endif
endif

ifeq ($(strip $(SOURCES)),<auto>)
    SOURCES := $(wildcard *.c)
    ifdef VERBOSE
    $(info "Auto-SOURCES $(SOURCES)" )
    endif
endif

# target should have source files
ifeq ($(strip $(SOURCES)),)
undefine TARGET
endif

# if no-main function, build as static library
empty:=
space:= $(empty) $(empty)
ifeq ($(strip $(TARGET)),<auto>)
    tmp:= $(subst /,$(space),$(CURDIR))
    TARGET := $(word $(words $(tmp)),$(tmp))
    haveMain := $(shell grep -s 'main\s*(.*)\s*$$' *.c)
    ifeq (,$(findstring main,$(haveMain)))
        TARGET := $(addsuffix .a,$(TARGET))
    endif
    ifdef VERBOSE
    $(info "Auto-TARGET $(TARGET)" )
    endif
endif

undefine MKSTATICLIB
undefine MKSHAREDLIB
ifneq ($(strip $(TARGET)),)
    # auto define MKSTATICLIB ...
    tmpext := $(strip $(suffix $(firstword $(TARGET))))
    ifeq ($(tmpext),)
    else ifeq ($(tmpext),.a)
        MKSTATICLIB = 1
    else ifeq ($(tmpext),.so)
        MKSHAREDLIB = 1
    endif
endif

#_______________________________________________________________________________
#                                                                   IGNORE BELOW
include $(TOPDIR)edam.mk
