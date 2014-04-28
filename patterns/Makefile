###########################################################
# MAKEFILE FOR C PROJECT
# make target=sample    # here sample must be a complete dir's name which will used by grep
# Auto include sub dir
# Auto exclude dir or file begin with underscore
# 32bit: "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
###########################################################

.PHONY: all clean
all: 

# annotation when release version
TARGET_PROG := main
DEBUG       := y #y
INC_DIR     := #$(DIR1) $(DIR2) ...
MACROS      := 
CFLAGS      := -m32 -Wall -Werror -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wunused-value -Wno-unused-parameter -Wformat \
  -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wredundant-decls
LDFLAGS     := -m32

# project directory	
DEBUG_DIR   := ./Debug
RELEASE_DIR := ./Release
BIN_DIR     := $(if $(DEBUG), $(DEBUG_DIR), $(RELEASE_DIR))

# shell command
CC    := gcc
RM    := rm -rf
MKDIR := mkdir -p
SED   := sed
MV    := mv

# init includes & sources & objects & depends
INC_PARAMS  := $(foreach d, $(INC_DIR), -I$d)
MACRO_PARAMS:= $(foreach d, $(MACROS), -D$d)
ifndef $(target)
  sources_all := $(shell find . -maxdepth 1 -name "*.c" -o -name "*.cpp" -o -name "*.h")
  sources_all += $(shell find . -name "*.c" -o -name "*.cpp" -o -name "*.h" | grep -v "/_" | grep "/$(target)/")
else
  sources_all := $(shell find . -name "*.c" -o -name "*.cpp" -o -name "*.h" | grep -v "/_")
endif
sources_c   := $(filter %.c, $(sources_all))
sources_cpp := $(filter %.cpp, $(sources_all))
sources_h   := $(filter %.h, $(sources_all))
objs        := $(addprefix $(BIN_DIR)/,$(strip $(sources_cpp:.cpp=.o) $(sources_c:.c=.o)))
deps        := $(addprefix $(BIN_DIR)/,$(strip $(sources_cpp:.cpp=.d) $(sources_c:.c=.d)))

# create directory
$(foreach dirname,$(sort $(dir $(sources_c) $(sources_cpp))),\
  $(shell $(MKDIR) $(BIN_DIR)/$(dirname)))

# complie & link variable
CFLAGS     += $(if $(DEBUG),-g -O0, -O3)
CFLAGS     += $(addprefix -I ,$(sort $(dir $(sources_h))))
CFLAGS     += $(INC_PARAMS)
LOADLIBES  += #-L/usr/include/mysql
LDLIBS     += #-lpthread -lmysqlclient

# add vpath
vpath %.h $(sort $(dir $(sources_h)))
vpath %.c $(sort $(dir $(sources_c)))
vpath %.cpp $(sort $(dir $(sources_cpp)))

# generate depend files
# actually generate after object generated, because it only used when next make:)
ifneq "$(MAKECMDGOALS)" "clean"
sinclude $(deps)
endif

# make-depend(depend-file,source-file,object-file,cc)
define make-depend
  $(RM) $1;                                     \
  $4 $(CFLAGS) -MM $2 |                         \
  $(SED) 's,\($(notdir $3)\): ,$3: ,' > $1.tmp; \
  $(SED) -e 's/#.*//'                           \
         -e 's/^[^:]*: *//'                     \
         -e 's/ *\\$$//'                        \
         -e '/^$$/ d'                           \
         -e 's/$$/ :/' < $1.tmp >> $1.tmp;      \
  $(MV) $1.tmp $1;
endef

# rules to generate objects file
$(BIN_DIR)/%.o: %.c
	@$(call make-depend,$(patsubst %.o,%.d,$@),$<,$@,$(CC))
	$(CC) $(CFLAGS) -o $@ -c $<

# add-target(target,objs,cc)
define add-target
  REAL_TARGET += $(BIN_DIR)/$1
  $(BIN_DIR)/$1: $2
	$3 $(LDFLAGS) $$^ $(LOADLIBES) $(LDLIBS) -o $$@
endef

# call add-target
$(foreach targ,$(TARGET_PROG),$(eval $(call add-target,$(targ),$(objs),$(CC))))

all: $(REAL_TARGET) $(TARGET_LIBS)

clean: 
	@$(RM) $(BIN_DIR)
	@$(RM) $(DEBUG_DIR)
	@$(RM) $(RELEASE_DIR)
