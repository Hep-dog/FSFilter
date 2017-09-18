#-- start of make_header -----------------

#====================================
#  Document FSFilter_check_install_runtime
#
#   Generated Sat Dec 27 19:01:59 2014  by lig
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_FSFilter_check_install_runtime_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_FSFilter_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_FSFilter_check_install_runtime

FSFilter_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_FSFilter_check_install_runtime = /tmp/CMT_$(FSFilter_tag)_FSFilter_check_install_runtime.make$(cmt_lock_pid)
else
#cmt_local_tagfile_FSFilter_check_install_runtime = $(FSFilter_tag)_FSFilter_check_install_runtime.make
cmt_local_tagfile_FSFilter_check_install_runtime = $(bin)$(FSFilter_tag)_FSFilter_check_install_runtime.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

FSFilter_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_FSFilter_check_install_runtime = /tmp/CMT_$(FSFilter_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_FSFilter_check_install_runtime = $(FSFilter_tag).make
cmt_local_tagfile_FSFilter_check_install_runtime = $(bin)$(FSFilter_tag).make
endif

endif

-include $(cmt_local_tagfile_FSFilter_check_install_runtime)

ifdef cmt_FSFilter_check_install_runtime_has_target_tag

ifdef READONLY
cmt_final_setup_FSFilter_check_install_runtime = /tmp/CMT_FSFilter_FSFilter_check_install_runtimesetup.make
cmt_local_FSFilter_check_install_runtime_makefile = /tmp/CMT_FSFilter_check_install_runtime$(cmt_lock_pid).make
else
cmt_final_setup_FSFilter_check_install_runtime = $(bin)FSFilter_FSFilter_check_install_runtimesetup.make
cmt_local_FSFilter_check_install_runtime_makefile = $(bin)FSFilter_check_install_runtime.make
endif

else

ifdef READONLY
cmt_final_setup_FSFilter_check_install_runtime = /tmp/CMT_FSFiltersetup.make
cmt_local_FSFilter_check_install_runtime_makefile = /tmp/CMT_FSFilter_check_install_runtime$(cmt_lock_pid).make
else
cmt_final_setup_FSFilter_check_install_runtime = $(bin)FSFiltersetup.make
cmt_local_FSFilter_check_install_runtime_makefile = $(bin)FSFilter_check_install_runtime.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_FSFiltersetup.make
else
cmt_final_setup = $(bin)FSFiltersetup.make
endif

FSFilter_check_install_runtime ::


ifdef READONLY
FSFilter_check_install_runtime ::
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
	$(echo) 'FSFilter_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = FSFilter_check_install_runtime/
FSFilter_check_install_runtime::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of cmt_action_runner_header ---------------

ifdef ONCE
FSFilter_check_install_runtime_once = 1
endif

ifdef FSFilter_check_install_runtime_once

FSFilter_check_install_runtimeactionstamp = FSFilter_check_install_runtime.actionstamp

FSFilter_check_install_runtime :: $(FSFilter_check_install_runtimeactionstamp)
	@echo FSFilter_check_install_runtime ok

$(FSFilter_check_install_runtimeactionstamp) :: $(FSFilter_check_install_runtime_dependencies)
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/6.6.4.p03/BesPolicy/BesPolicy-01-05-03/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/lig/workarea/6.6.4.p03/InstallArea/share
	@echo ok > $(FSFilter_check_install_runtimeactionstamp)

FSFilter_check_install_runtimeclean ::
	@/bin/rm -f $(FSFilter_check_install_runtimeactionstamp)

else

FSFilter_check_install_runtime :: $(FSFilter_check_install_runtime_dependencies)
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/6.6.4.p03/BesPolicy/BesPolicy-01-05-03/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/lig/workarea/6.6.4.p03/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: FSFilter_check_install_runtimeclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(FSFilter_check_install_runtime.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(FSFilter_check_install_runtime.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_FSFilter_check_install_runtime)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FSFilter_check_install_runtime.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FSFilter_check_install_runtime.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FSFilter_check_install_runtime.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

FSFilter_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
