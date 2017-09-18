#-- start of make_header -----------------

#====================================
#  Document FSFilter_check_install_runtime
#
#   Generated Tue Mar  8 09:47:40 2016  by lig
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_FSFilter_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_FSFilter_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_FSFilter_check_install_runtime

FSFilter_tag = $(tag)

#cmt_local_tagfile_FSFilter_check_install_runtime = $(FSFilter_tag)_FSFilter_check_install_runtime.make
cmt_local_tagfile_FSFilter_check_install_runtime = $(bin)$(FSFilter_tag)_FSFilter_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

FSFilter_tag = $(tag)

#cmt_local_tagfile_FSFilter_check_install_runtime = $(FSFilter_tag).make
cmt_local_tagfile_FSFilter_check_install_runtime = $(bin)$(FSFilter_tag).make

endif

include $(cmt_local_tagfile_FSFilter_check_install_runtime)
#-include $(cmt_local_tagfile_FSFilter_check_install_runtime)

ifdef cmt_FSFilter_check_install_runtime_has_target_tag

cmt_final_setup_FSFilter_check_install_runtime = $(bin)setup_FSFilter_check_install_runtime.make
cmt_dependencies_in_FSFilter_check_install_runtime = $(bin)dependencies_FSFilter_check_install_runtime.in
#cmt_final_setup_FSFilter_check_install_runtime = $(bin)FSFilter_FSFilter_check_install_runtimesetup.make
cmt_local_FSFilter_check_install_runtime_makefile = $(bin)FSFilter_check_install_runtime.make

else

cmt_final_setup_FSFilter_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_FSFilter_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_FSFilter_check_install_runtime = $(bin)FSFiltersetup.make
cmt_local_FSFilter_check_install_runtime_makefile = $(bin)FSFilter_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)FSFiltersetup.make

#FSFilter_check_install_runtime :: ;

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
#FSFilter_check_install_runtime::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of cmt_action_runner_header ---------------

ifdef ONCE
FSFilter_check_install_runtime_once = 1
endif

ifdef FSFilter_check_install_runtime_once

FSFilter_check_install_runtimeactionstamp = $(bin)FSFilter_check_install_runtime.actionstamp
#FSFilter_check_install_runtimeactionstamp = FSFilter_check_install_runtime.actionstamp

FSFilter_check_install_runtime :: $(FSFilter_check_install_runtimeactionstamp)
	$(echo) "FSFilter_check_install_runtime ok"
#	@echo FSFilter_check_install_runtime ok

#$(FSFilter_check_install_runtimeactionstamp) :: $(FSFilter_check_install_runtime_dependencies)
$(FSFilter_check_install_runtimeactionstamp) ::
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/7.0.0/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/lig/workarea/7.0.0/InstallArea/share
	$(silent) cat /dev/null > $(FSFilter_check_install_runtimeactionstamp)
#	@echo ok > $(FSFilter_check_install_runtimeactionstamp)

FSFilter_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(FSFilter_check_install_runtimeactionstamp)

else

#FSFilter_check_install_runtime :: $(FSFilter_check_install_runtime_dependencies)
FSFilter_check_install_runtime ::
	$(silent) /afs/ihep.ac.cn/bes3/offline/Boss/7.0.0/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs/bes/lig/workarea/7.0.0/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: FSFilter_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(FSFilter_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

FSFilter_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
