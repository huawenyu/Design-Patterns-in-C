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
		cp $(TOPDIR)tpl_top.mk topdir.mk; \
		if ! [ -a Makefile ]; then \
			cp $(TOPDIR)tpl_make.mk Makefile; \
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
OUTDIR := $(strip $(if $(PROFILEMODE),$(G_OUTDIR_PROFILE)/,\
                       $(if $(DEBUGMODE),$(G_OUTDIR_DEBUG)/,\
                            $(G_OUTDIR_RELEASE)/)))

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
LIBDIRS     := $(subst $(REPLACE_ME),$(OUTDIR),$(LIBDIRS))
LIBS        += $(EXTRA_LIBS)
CPPFLAGS    += $(EXTRA_CPPFLAGS)
LDFLAGS     += $(EXTRA_LDFLAGS)
ARFLAGS     += $(EXTRA_ARFLAGS)


# includes & macros
CPPFLAGS    := $(foreach var,$(INCS), -I$(var) ) $(CPPFLAGS)
CPPFLAGS    := $(foreach var,$(MACROS), -D $(var) ) $(CPPFLAGS)
LDFLAGS     := $(foreach var,$(LIBDIRS), -L$(var) ) $(LDFLAGS)
#_______________________________________________________________________________
#                                                             AUTO CREATE&DEFINE
# source type
C_EXT       := *.c
CPLUS_EXT   := *.C *.cc *.cpp *.CPP *.c++ *.cp *.cxx
INNER_MK    := topdir.mk config.mk base.mk tpl_make.mk tpl_top.mk
# software
CC          := gcc
CXX         := g++
GDC         := gdc
AS          := nasm
LD          := g++
AR          := ar
MAKE        := make
MKDIR       := mkdir -p
MV          := mv
RM          := rm -fr

# no-support mix c,cpp
ifneq (,$(wildcard $(C_EXT)))
    CC = gcc
    LD = gcc
endif
ifneq (,$(wildcard $(CPLUS_EXT)))
    CC = g++
    LD = g++
endif

OUTDIR := $(strip $(if $(PROFILEMODE),$(G_OUTDIR_PROFILE)/,\
               $(if $(DEBUGMODE),$(G_OUTDIR_DEBUG)/,\
                    $(G_OUTDIR_RELEASE)/)))
OUTDIR := $(subst $(TOPDIR),$(TOPDIR)$(OUTDIR),$(CURDIR))/
# create directory
$(shell $(MKDIR) $(OUTDIR))

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
    stds := $(SUBPROJS) $(INNER_MK)
    restProjs := $(filter-out $(stds),$(subprojs))

    restProjs := $(basename $(restProjs))
    SUBPROJS := $(basename $(SUBPROJS))
    SUBPROJS := $(subst <auto>,$(restProjs),$(SUBPROJS))
    ifdef VERBOSE
    $(info "Auto-SUBPROJS $(SUBPROJS)" )
    endif
endif

ifeq ($(strip $(SOURCES)),<auto>)
    SOURCES := $(wildcard $(C_EXT) $(CPLUS_EXT))
    ifdef VERBOSE
    $(info "Auto-SOURCES $(SOURCES)" )
    endif
endif

# exclude list
SOURCES := $(filter-out $(SOURCES_NOT),$(SOURCES))
SUBPROJS := $(filter-out $(SUBPROJS_NOT),$(SUBPROJS))
SUBDIRS := $(filter-out $(SUBDIRS_NOT) \
    $(G_OUTDIR_DEBUG) $(G_OUTDIR_RELEASE) $(G_OUTDIR_PROFILE) \
    ,$(SUBDIRS))

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
    haveMain := $(shell grep -s 'main\s*(.*)\s*$$' $(C_EXT) $(CPLUS_EXT))
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
#                                                                       BUILDING
# set debug mode if profiling
ifdef PROFILEMODE
export DEBUGMODE := 1
endif

# debug/profile build flags
CPPFLAGS	:= $(if $(PROFILEMODE),-pg -D PROFILE) $(if $(DEBUGMODE),\
	-g3 -O0 -D DEBUG -Wall -Wextra,-D NDEBUG -O2) $(CPPFLAGS)
CXXFLAGS	:= $(if $(DEBUGMODE),-Woverloaded-virtual -Wreorder \
	-Wctor-dtor-privacy) $(CXXFLAGS)
DFLAGS		:= $(if $(DEBUGMODE),,-frelease)
ASFLAGS		:= -f elf $(if $(DEBUGMODE),-g -dDEBUG,-dNDEBUG -O2) $(ASFLAGS)

ifeq "$(strip $(LD))" "g++"
LDFLAGS		:= $(if $(PROFILEMODE),-pg) \
	$(if $(or $(PROFILEMODE), $(DEBUGMODE)),,-Wl,-S) $(LDFLAGS)
else
LDFLAGS		:= $(if $(PROFILEMODE),-pg) \
	$(if $(or $(PROFILEMODE), $(DEBUGMODE)),,) $(LDFLAGS)
endif

# setup options for shared/static libs
CPPFLAGS	:= $(if $(or $(MKSHAREDLIB),$(MKSTATICLIB)),-fPIC) $(CPPFLAGS)
LDFLAGS		:= $(if $(LINKSTATIC),-static) $(LDFLAGS)

# add libraries for d
LIBS	:= $(LIBS) $(if $(filter %.d, $(SOURCES)), gphobos2 rt)

# build flags for libraries
LDPOSTFLAGS := $(addprefix -l,$(LIBS)) $(LDPOSTFLAGS)

# work out object and dependency files
OBJECTS     := $(addsuffix .o,  $(addprefix $(OUTDIR),$(basename $(SOURCES))))
DEPFILES    := $(addsuffix .dep,$(addprefix $(OUTDIR),$(basename $(SOURCES))))

# fixup target name
ifdef TARGET
    TARGET := $(patsubst %.so,%,$(patsubst %.a,%,$(TARGET)))
    ifneq ($(strip $(MKSHAREDLIB) $(MKSTATICLIB)),)
        TARGET := $(TARGET)$(if $(MKSHAREDLIB),.so,$(if $(MKSTATICLIB),.a))
        ifndef NOLIBPREFIX
            TARGET := lib$(patsubst lib%,%,$(TARGET))
        endif
    endif
    TARGET := $(OUTDIR)$(TARGET)
endif

# Set up dependency generation build flags
ifdef DEBUGMODE
ifndef PROFILEMODE
FIXUP_DEPENDENCY_FILES = \
	@sed 's/\#.*//;s/^[^:]*://;s/^[ \t]*//;s/ *\\$$//;/^$$/d;s/$$/:/' < \
	$(basename $<).dep > .$$$$~; cat .$$$$~ >> $(basename $<).dep; rm .$$$$~; \
	$(MV) $(basename $<).dep $(OUTDIR)$(basename $<).dep;
DEPFLAGS	= -MMD -MP -MF $(OUTDIR)$(basename $<).dep
endif
endif

# include dependencies
ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "clean_all"
-include $(DEPFILES)
endif
endif

# default rule
.DEFAULT_GOAL := all

#_______________________________________________________________________________
#                                                                          RULES

.PHONY:	all subdirs subprojs target clean clean_all run depend dep \
	$(SUBDIRS) $(SUBPROJS) $(EXTRA_PHONY)

all: subdirs subprojs target

subdirs: $(SUBDIRS)

subprojs: $(SUBPROJS)

target: $(TARGET)

clean:
ifneq ($(or $(SUBDIRS),$(SUBPROJS)),)
ifneq "$(MAKECMDGOALS)" "clean_all"
	@echo "NOT RECURSING - use 'make clean_all' to clean subdirs and " \
		"subprojs as well"
endif
endif
	rm -f $(OBJECTS) $(TARGET) $(DEPFILES) core *~

#clean_all: subdirs subprojs clean
clean_all:
	@$(RM) $(G_OUTDIR_DEBUG)
	@$(RM) $(G_OUTDIR_RELEASE)
	@$(RM) $(G_OUTDIR_PROFILE)
	@echo "Clean All OK."

run: target
	@echo "Please run: "./$(TARGET)" <OR> 'make runall'"

$(SUBDIRS) $(SUBPROJS):
	@if [ "$@" = "$(firstword $(SUBDIRS) $(SUBPROJS))" ]; then echo; fi
	@$(MAKE) $(if $(filter $@,$(SUBPROJS)), -f $@.mk, -C $@) \
		$(filter-out $(SUBDIRS) $(SUBPROJS) subdirs subprojs,$(MAKECMDGOALS))
	@echo

$(TARGET): $(OBJECTS)
ifdef MKSTATICLIB
	$(AR) rcs $(TARGET) $(OBJECTS)
else
	$(LD) $(if $(MKSHAREDLIB),-shared) -o $(TARGET) $(LDFLAGS) $(OBJECTS) $(LDPOSTFLAGS)
endif

$(OUTDIR)%.o: %.c
	$(CC) -c $(CPPFLAGS) $(DEPFLAGS) $(CFLAGS) -o $@ $<

$(OUTDIR)%.o: %.cc
	$(CXX) -c $(CPPFLAGS) $(DEPFLAGS) $(CXXFLAGS) -o $@ $<
$(OUTDIR)%.o: %.C
	$(CXX) -c $(CPPFLAGS) $(DEPFLAGS) $(CXXFLAGS) -o $@ $<
$(OUTDIR)%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) $(DEPFLAGS) $(CXXFLAGS) -o $@ $<

$(OUTDIR)%.o: %.d
	$(GDC) -c $(CPPFLAGS) $(DFLAGS) -o $@ $<

$(OUTDIR)%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<
ifdef DEBUGMODE
	$(AS) $(ASFLAGS) -M $< > $(basename $<).dep
	$(FIXUP_DEPENDENCY_FILES)
endif
$(OUTDIR)%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $<
ifdef DEBUGMODE
	$(AS) $(ASFLAGS) -M $< > $(basename $<).dep
	$(FIXUP_DEPENDENCY_FILES)
endif
$(OUTDIR)%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<
ifdef DEBUGMODE
	$(AS) $(ASFLAGS) -M $< > $(basename $<).dep
	$(FIXUP_DEPENDENCY_FILES)
endif
