ifndef TOPDIR
TOPDIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
$(info make help		View help info)
#$(info TOPDIR $(TOPDIR))
endif
export TOPDIR
