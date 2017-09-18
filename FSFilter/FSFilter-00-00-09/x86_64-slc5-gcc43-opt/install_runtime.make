#-- start of make_header -----------------

#====================================
#  Document install_runtime
#
#   Generated Sat Dec 27 19:02:00 2014  by lig
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_install_runtime

FSFilter_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_install_runtime = /tmp/CMT_$(FSFilter_tag)_install_runtime.make$(cmt_lock_pid)
else
#cmt_local_tagfile_install_runtime = $(FSFilter_tag)_install_runtime.make
cmt_local_tagfile_install_runtime = $(bin)$(FSFilter_tag)_install_runtime.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

FSFilter_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_install_runtime = /tmp/CMT_$(FSFilter_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_install_runtime = $(FSFilter_tag).make
cmt_local_tagfile_install_runtime = $(bin)$(FSFilter_tag).make
endif

endif

-include $(cmt_local_tagfile_install_runtime)

ifdef cmt_install_runtime_has_target_tag

ifdef READONLY
cmt_final_setup_install_runtime = /tmp/CMT_FSFilter_install_runtimesetup.make
cmt_local_install_runtime_makefile = /tmp/CMT_install_runtime$(cmt_lock_pid).make
else
cmt_final_setup_install_runtime = $(bin)FSFilter_install_runtimesetup.make
cmt_local_install_runtime_makefile = $(bin)install_runtime.make
endif

else

ifdef READONLY
cmt_final_setup_install_runtime = /tmp/CMT_FSFiltersetup.make
cmt_local_install_runtime_makefile = /tmp/CMT_install_runtime$(cmt_lock_pid).make
else
cmt_final_setup_install_runtime = $(bin)FSFiltersetup.make
cmt_local_install_runtime_makefile = $(bin)install_runtime.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_FSFiltersetup.make
else
cmt_final_setup = $(bin)FSFiltersetup.make
endif

install_runtime ::


ifdef READONLY
install_runtime ::
	@echo tags=$(tags)
	@echo cmt_local_tagfile=$(cmt_local_tagfile)
endif


dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = install_runtime/
install_runtime::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------



ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/share

install_runtime :: install_runtimeinstall

install :: install_runtimeinstall

install_runtimeclean :: install_runtimeuninstall

uninstall :: install_runtimeuninstall



jobOptions_FSFilter_txt_dependencies = ../share/jobOptions_FSFilter.txt


install_runtimeinstall :: ${install_dir}/jobOptions_FSFilter.txt
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

${install_dir}/jobOptions_FSFilter.txt :: ../share/jobOptions_FSFilter.txt
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/jobOptions_FSFilter.txt`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_install_action) "$${d}" "jobOptions_FSFilter.txt" "$(install_dir)" "cp -R" ; \
	fi

install_runtimeuninstall ::
	@if test ! "${installarea}" = ""; then \
	  d=`dirname ../share/jobOptions_FSFilter.txt`; \
	  d=`(cd $${d}; pwd)`; \
	  CMTINSTALLAREA=${CMTINSTALLAREA}; export CMTINSTALLAREA; \
	  $(cmt_uninstall_action) "$${d}" "jobOptions_FSFilter.txt" "$(install_dir)" "cp -R" ; \
	fi
#-- start of cleanup_header --------------

clean :: install_runtimeclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(install_runtime.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(install_runtime.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_install_runtime)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(install_runtime.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(install_runtime.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(install_runtime.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

install_runtimeclean ::
#-- end of cleanup_header ---------------
