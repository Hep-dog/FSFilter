#-- start of make_header -----------------

#====================================
#  Library FSFilter
#
#   Generated Sat Dec 27 19:01:30 2014  by lig
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

ifdef READONLY
cmt_local_tagfile_FSFilter = /tmp/CMT_$(FSFilter_tag)_FSFilter.make$(cmt_lock_pid)
else
#cmt_local_tagfile_FSFilter = $(FSFilter_tag)_FSFilter.make
cmt_local_tagfile_FSFilter = $(bin)$(FSFilter_tag)_FSFilter.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

FSFilter_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_FSFilter = /tmp/CMT_$(FSFilter_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_FSFilter = $(FSFilter_tag).make
cmt_local_tagfile_FSFilter = $(bin)$(FSFilter_tag).make
endif

endif

-include $(cmt_local_tagfile_FSFilter)

ifdef cmt_FSFilter_has_target_tag

ifdef READONLY
cmt_final_setup_FSFilter = /tmp/CMT_FSFilter_FSFiltersetup.make
cmt_local_FSFilter_makefile = /tmp/CMT_FSFilter$(cmt_lock_pid).make
else
cmt_final_setup_FSFilter = $(bin)FSFilter_FSFiltersetup.make
cmt_local_FSFilter_makefile = $(bin)FSFilter.make
endif

else

ifdef READONLY
cmt_final_setup_FSFilter = /tmp/CMT_FSFiltersetup.make
cmt_local_FSFilter_makefile = /tmp/CMT_FSFilter$(cmt_lock_pid).make
else
cmt_final_setup_FSFilter = $(bin)FSFiltersetup.make
cmt_local_FSFilter_makefile = $(bin)FSFilter.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_FSFiltersetup.make
else
cmt_final_setup = $(bin)FSFiltersetup.make
endif

FSFilter ::


ifdef READONLY
FSFilter ::
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
	$(echo) 'FSFilter'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = FSFilter/
FSFilter::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
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

$(FSFilterlib) :: $(bin)FSFilter.o $(bin)FSHelper.o $(bin)MCTruthHelper.o $(bin)NTupleHelper.o $(bin)YUPING.o $(bin)DTagName.o $(bin)Utility.o $(bin)RscanDQ.o $(bin)FSFilter_entries.o $(bin)FSFilter_load.o
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
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)FSFilter.o $(bin)FSHelper.o $(bin)MCTruthHelper.o $(bin)NTupleHelper.o $(bin)YUPING.o $(bin)DTagName.o $(bin)Utility.o $(bin)RscanDQ.o $(bin)FSFilter_entries.o $(bin)FSFilter_load.o

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




#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),FSFilterclean)

#$(bin)FSFilter_dependencies.make :: dirs

ifndef QUICK
$(bin)FSFilter_dependencies.make : ../src/FSFilter.cxx ../src/FSHelper.cxx ../src/MCTruthHelper.cxx ../src/NTupleHelper.cxx ../src/YUPING.cxx ../src/DTagName.cxx ../src/Utility.cxx ../src/RscanDQ.cxx ../src/components/FSFilter_entries.cxx ../src/components/FSFilter_load.cxx $(use_requirements) $(cmt_final_setup_FSFilter)
	$(echo) "(FSFilter.make) Rebuilding $@"; \
	  $(build_dependencies) FSFilter -all_sources -out=$@ ../src/FSFilter.cxx ../src/FSHelper.cxx ../src/MCTruthHelper.cxx ../src/NTupleHelper.cxx ../src/YUPING.cxx ../src/DTagName.cxx ../src/Utility.cxx ../src/RscanDQ.cxx ../src/components/FSFilter_entries.cxx ../src/components/FSFilter_load.cxx
endif

#$(FSFilter_dependencies)

-include $(bin)FSFilter_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(FSFilter_cxx_dependencies)

$(bin)$(binobj)FSFilter.o : $(FSFilter_cxx_dependencies)
	$(cpp_echo) $(src)FSFilter.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_cppflags) $(FSFilter_cxx_cppflags)  $(src)FSFilter.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(FSHelper_cxx_dependencies)

$(bin)$(binobj)FSHelper.o : $(FSHelper_cxx_dependencies)
	$(cpp_echo) $(src)FSHelper.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSHelper_cppflags) $(FSHelper_cxx_cppflags)  $(src)FSHelper.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(MCTruthHelper_cxx_dependencies)

$(bin)$(binobj)MCTruthHelper.o : $(MCTruthHelper_cxx_dependencies)
	$(cpp_echo) $(src)MCTruthHelper.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(MCTruthHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(MCTruthHelper_cppflags) $(MCTruthHelper_cxx_cppflags)  $(src)MCTruthHelper.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(NTupleHelper_cxx_dependencies)

$(bin)$(binobj)NTupleHelper.o : $(NTupleHelper_cxx_dependencies)
	$(cpp_echo) $(src)NTupleHelper.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(NTupleHelper_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(NTupleHelper_cppflags) $(NTupleHelper_cxx_cppflags)  $(src)NTupleHelper.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(YUPING_cxx_dependencies)

$(bin)$(binobj)YUPING.o : $(YUPING_cxx_dependencies)
	$(cpp_echo) $(src)YUPING.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(YUPING_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(YUPING_cppflags) $(YUPING_cxx_cppflags)  $(src)YUPING.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(DTagName_cxx_dependencies)

$(bin)$(binobj)DTagName.o : $(DTagName_cxx_dependencies)
	$(cpp_echo) $(src)DTagName.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(DTagName_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(DTagName_cppflags) $(DTagName_cxx_cppflags)  $(src)DTagName.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(Utility_cxx_dependencies)

$(bin)$(binobj)Utility.o : $(Utility_cxx_dependencies)
	$(cpp_echo) $(src)Utility.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(Utility_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(Utility_cppflags) $(Utility_cxx_cppflags)  $(src)Utility.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(RscanDQ_cxx_dependencies)

$(bin)$(binobj)RscanDQ.o : $(RscanDQ_cxx_dependencies)
	$(cpp_echo) $(src)RscanDQ.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(RscanDQ_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(RscanDQ_cppflags) $(RscanDQ_cxx_cppflags)  $(src)RscanDQ.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(FSFilter_entries_cxx_dependencies)

$(bin)$(binobj)FSFilter_entries.o : $(FSFilter_entries_cxx_dependencies)
	$(cpp_echo) $(src)components/FSFilter_entries.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_entries_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_entries_cppflags) $(FSFilter_entries_cxx_cppflags) -I../src/components $(src)components/FSFilter_entries.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)FSFilter_dependencies.make : $(FSFilter_load_cxx_dependencies)

$(bin)$(binobj)FSFilter_load.o : $(FSFilter_load_cxx_dependencies)
	$(cpp_echo) $(src)components/FSFilter_load.cxx
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(FSFilter_pp_cppflags) $(lib_FSFilter_pp_cppflags) $(FSFilter_load_pp_cppflags) $(use_cppflags) $(FSFilter_cppflags) $(lib_FSFilter_cppflags) $(FSFilter_load_cppflags) $(FSFilter_load_cxx_cppflags) -I../src/components $(src)components/FSFilter_load.cxx

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: FSFilterclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(FSFilter.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(FSFilter.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_FSFilter)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FSFilter.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FSFilter.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(FSFilter.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

FSFilterclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)FSFilter$(library_suffix).a $(binobj)$(library_prefix)FSFilter$(library_suffix).s? $(binobj)FSFilter.stamp $(binobj)FSFilter.shstamp
#-- end of cleanup_library ---------------

