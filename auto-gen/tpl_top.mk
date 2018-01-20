#include ../topdir.mk
#_______________________________________________________________________________
#                               READONLY FILE
# Using file 'config.mk' as upward search sanity file to detect $(TOPDIR)
#_______________________________________________________________________________
REPLACE_ME= XXXXXX
OUTDIR    = $(REPLACE_ME)

ifndef TOPDIR
empty:=
space:= $(empty) $(empty)
tmpdir := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
tmpdir := $(subst /,$(space),$(tmpdir))
number := $(words $(tmpdir))

topdir := $(shell \
	tmpdir="." ; number=$(number) ; \
	while [[ $$number -gt 1 ]] ; do \
		if [ -a "$${tmpdir}/config.mk" ]; then echo $$tmpdir; break; fi; \
		tmpdir="$${tmpdir}/.." ; \
		((number = number - 1)) ; \
	done ; \
	)
TOPDIR := $(realpath $(topdir))/
include $(TOPDIR)topdir.mk
endif
#_______________________________________________________________________________
