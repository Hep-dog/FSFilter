#-- start of make_header -----------------

#====================================
#  Library FSFilter
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

cmt_FSFilter_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_FSFilter_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_FSFilter

FSFilter_tag = $(tag)

#cmt_local_tagfile_FSFilter = $(FSFilter_tag)_FSFilter.make
cmt_local_tagfile_FSFilter = $(bin)$(FSFilter_tag)_FSFilter.make

else

tags      = $(tag),$(CMTEXTRATAGS)

FSFilter_tag = $(tag)

#cmt_local_tagfile_FSFilter = $(FSFilter_tag).make
cmt_local_tagfile_FSFilter = $(bin)$(FSFilter_tag).make

endif

include $(cmt_local_tagfile_FSFilter)
#-include $(cmt_local_tagfile_FSFilter)

ifdef cmt_FSFilter_has_target_tag

cmt_final_setup_FSFilter = $(bin)setup_FSFilter.make
cmt_dependencies_in_FSFilter = $(bin)dependencies_FSFilter.in
#cmt_final_setup_FSFilter = $(bin)FSFilter_FSFiltersetup.make
cmt_local_FSFilter_makefile = $(bin)FSFilter.make

else

cmt_final_setup_FSFilter = $(bin)setup.make
cmt_dependencies_in_FSFilter = $(bin)dependencies.in
#cmt_final_setup_FSFilter = $(bin)FSFiltersetup.make
cmt_local_FSFilter_makefile = $(bin)FSFilter.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)FSFiltersetup.make

#FSFilter :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'FSFilter'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = FSFilter/
#FSFilter::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

FSFilterlibname   = $(bin)$(library_prefix)FSFilter$(library_suffix)
FSFilterlib       = $(FSFilterlibname).a
FSFilterstamp     = $(bin)FSFilter.stamp
FSFiltershstamp   = $(bin)FSFilter.shstamp

FSFilter :: dirs  FSFilterLIB
	$(echo) "FSFilter ok"

#-- end of libary_header ----------------

FSFilterLIB :: $(FSFilterlib) $(FSFiltershstamp)
	@/bin/echo "------> FSFilter : library ok"

$(FSFilterlib) :: $(bin)YUPING.o $(bin)RscanDQ.o $(bin)Utility.o $(bin)MCTruthHelper.o $(bin)DTagName.o $(bin)FSHelper.o $(bin)FSFilter.o $(bin)NTupleHelper.o $(bin)FSFilter_entries.o $(bin)FSFilter_load.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(FSFilterlib) $?
	$(lib_silent) $(ranlib) $(FSFilterlib)
	$(lib_silent) cat /dev/null >$(FSFilterstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(FSFilterlibname).$(shlibsuffix) :: $(FSFilterlib) $(FSFilterstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" FSFilter $(FSFilter_shlibflags)

$(FSFiltershstamp) :: $(FSFilterlibname).$(shlibsuffix)
	@if test -f $(FSFilterlibname).$(shlibsuffix) ; then cat /dev/null >$(FSFiltershstamp) ; fi

FSFilterclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)YUPING.o $(bin)RscanDQ.o $(bin)Utility.o $(bin)MCTruthHelper.o $(bin)DTagName.o $(bin)FSHelper.o $(bin)FSFilter.o $(bin)NTupleHelper.o $(bin)FSFilter_entries.o $(bin)FSFilter_load.o

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/${CMTCONFIG}/lib
FSFilterinstallname = $(library_prefix)FSFilter$(library_suffix).$(shlibsuffix)

FSFilter :: FSFilterinstall

install :: FSFilterinstall

FSFilterinstall :: $(install_dir)/$(FSFilterinstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(FSFilterinstallname) :: $(bin)$(FSFilterinstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(FSFilterinstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(FSFilterinstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(FSFilterinstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(FSFilterinstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(FSFilterinstallname) $(install_dir)/$(FSFilterinstallname); \
	      echo `pwd`/$(FSFilterinstallname) >$(install_dir)/$(FSFilterinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(FSFilterinstallname), no installation directory specified"; \
	  fi; \
	fi

FSFilterclean :: FSFilteruninstall

uninstall :: FSFilteruninstall

FSFilteruninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(FSFilterinstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(FSFilterinstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(FSFilterinstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(FSFilterinstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)YUPING.d

$(bin)$(binobj)YUPING.d :

$(bin)$(binobj)YUPING.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)YUPING.o : $(src)YUPING.cxx
	$(cpp_echo) $(src)YUPING.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(YUPING_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(YUPING_cppflags) $(YUPING_cxx_cppflags)  $(src)YUPING.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(YUPING_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)YUPING.cxx

$(bin)$(binobj)YUPING.o : $(YUPING_cxx_dependencies)
	$(cpp_echo) $(src)YUPING.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(YUPING_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(YUPING_cppflags) $(YUPING_cxx_cppflags)  $(src)YUPING.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)RscanDQ.d

$(bin)$(binobj)RscanDQ.d :

$(bin)$(binobj)RscanDQ.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)RscanDQ.o : $(src)RscanDQ.cxx
	$(cpp_echo) $(src)RscanDQ.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(RscanDQ_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(RscanDQ_cppflags) $(RscanDQ_cxx_cppflags)  $(src)RscanDQ.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(RscanDQ_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)RscanDQ.cxx

$(bin)$(binobj)RscanDQ.o : $(RscanDQ_cxx_dependencies)
	$(cpp_echo) $(src)RscanDQ.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(RscanDQ_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(RscanDQ_cppflags) $(RscanDQ_cxx_cppflags)  $(src)RscanDQ.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Utility.d

$(bin)$(binobj)Utility.d :

$(bin)$(binobj)Utility.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)Utility.o : $(src)Utility.cxx
	$(cpp_echo) $(src)Utility.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(Utility_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(Utility_cppflags) $(Utility_cxx_cppflags)  $(src)Utility.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(Utility_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)Utility.cxx

$(bin)$(binobj)Utility.o : $(Utility_cxx_dependencies)
	$(cpp_echo) $(src)Utility.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(Utility_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(Utility_cppflags) $(Utility_cxx_cppflags)  $(src)Utility.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)MCTruthHelper.d

$(bin)$(binobj)MCTruthHelper.d :

$(bin)$(binobj)MCTruthHelper.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)MCTruthHelper.o : $(src)MCTruthHelper.cxx
	$(cpp_echo) $(src)MCTruthHelper.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(MCTruthHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(MCTruthHelper_cppflags) $(MCTruthHelper_cxx_cppflags)  $(src)MCTruthHelper.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(MCTruthHelper_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)MCTruthHelper.cxx

$(bin)$(binobj)MCTruthHelper.o : $(MCTruthHelper_cxx_dependencies)
	$(cpp_echo) $(src)MCTruthHelper.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(MCTruthHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(MCTruthHelper_cppflags) $(MCTruthHelper_cxx_cppflags)  $(src)MCTruthHelper.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)DTagName.d

$(bin)$(binobj)DTagName.d :

$(bin)$(binobj)DTagName.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)DTagName.o : $(src)DTagName.cxx
	$(cpp_echo) $(src)DTagName.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(DTagName_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(DTagName_cppflags) $(DTagName_cxx_cppflags)  $(src)DTagName.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(DTagName_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)DTagName.cxx

$(bin)$(binobj)DTagName.o : $(DTagName_cxx_dependencies)
	$(cpp_echo) $(src)DTagName.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(DTagName_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(DTagName_cppflags) $(DTagName_cxx_cppflags)  $(src)DTagName.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)FSHelper.d

$(bin)$(binobj)FSHelper.d :

$(bin)$(binobj)FSHelper.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)FSHelper.o : $(src)FSHelper.cxx
	$(cpp_echo) $(src)FSHelper.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSHelper_cppflags) $(FSHelper_cxx_cppflags)  $(src)FSHelper.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(FSHelper_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)FSHelper.cxx

$(bin)$(binobj)FSHelper.o : $(FSHelper_cxx_dependencies)
	$(cpp_echo) $(src)FSHelper.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSHelper_cppflags) $(FSHelper_cxx_cppflags)  $(src)FSHelper.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)FSFilter.d

$(bin)$(binobj)FSFilter.d :

$(bin)$(binobj)FSFilter.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)FSFilter.o : $(src)FSFilter.cxx
	$(cpp_echo) $(src)FSFilter.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_cppflags) $(FSFilter_cxx_cppflags)  $(src)FSFilter.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(FSFilter_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)FSFilter.cxx

$(bin)$(binobj)FSFilter.o : $(FSFilter_cxx_dependencies)
	$(cpp_echo) $(src)FSFilter.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_cppflags) $(FSFilter_cxx_cppflags)  $(src)FSFilter.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)NTupleHelper.d

$(bin)$(binobj)NTupleHelper.d :

$(bin)$(binobj)NTupleHelper.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)NTupleHelper.o : $(src)NTupleHelper.cxx
	$(cpp_echo) $(src)NTupleHelper.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(NTupleHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(NTupleHelper_cppflags) $(NTupleHelper_cxx_cppflags)  $(src)NTupleHelper.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(NTupleHelper_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)NTupleHelper.cxx

$(bin)$(binobj)NTupleHelper.o : $(NTupleHelper_cxx_dependencies)
	$(cpp_echo) $(src)NTupleHelper.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(NTupleHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(NTupleHelper_cppflags) $(NTupleHelper_cxx_cppflags)  $(src)NTupleHelper.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)FSFilter_entries.d

$(bin)$(binobj)FSFilter_entries.d :

$(bin)$(binobj)FSFilter_entries.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)FSFilter_entries.o : $(src)components/FSFilter_entries.cxx
	$(cpp_echo) $(src)components/FSFilter_entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_entries_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_entries_cppflags) $(FSFilter_entries_cxx_cppflags) -I../src/components $(src)components/FSFilter_entries.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(FSFilter_entries_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)components/FSFilter_entries.cxx

$(bin)$(binobj)FSFilter_entries.o : $(FSFilter_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/FSFilter_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_entries_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_entries_cppflags) $(FSFilter_entries_cxx_cppflags) -I../src/components $(src)components/FSFilter_entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),FSFilterclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)FSFilter_load.d

$(bin)$(binobj)FSFilter_load.d :

$(bin)$(binobj)FSFilter_load.o : $(cmt_final_setup_FSFilter)

$(bin)$(binobj)FSFilter_load.o : $(src)components/FSFilter_load.cxx
	$(cpp_echo) $(src)components/FSFilter_load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_load_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_load_cppflags) $(FSFilter_load_cxx_cppflags) -I../src/components $(src)components/FSFilter_load.cxx
endif
endif

else
$(bin)FSFilter_dependencies.make : $(FSFilter_load_cxx_dependencies)

$(bin)FSFilter_dependencies.make : $(src)components/FSFilter_load.cxx

$(bin)$(binobj)FSFilter_load.o : $(FSFilter_load_cxx_dependencies)
	$(cpp_echo) $(src)components/FSFilter_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_load_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_load_cppflags) $(FSFilter_load_cxx_cppflags) -I../src/components $(src)components/FSFilter_load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: FSFilterclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(FSFilter.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

FSFilterclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library FSFilter
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)FSFilter$(library_suffix).a $(library_prefix)FSFilter$(library_suffix).s? FSFilter.stamp FSFilter.shstamp
#-- end of cleanup_library ---------------
