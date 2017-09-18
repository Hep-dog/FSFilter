# echo "setup FSFilter FSFilter-00-00-09 in /workfs/bes/lig/workarea/7.0.0"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtFSFiltertempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtFSFiltertempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=FSFilter -version=FSFilter-00-00-09 -path=/workfs/bes/lig/workarea/7.0.0  -no_cleanup $* >${cmtFSFiltertempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=FSFilter -version=FSFilter-00-00-09 -path=/workfs/bes/lig/workarea/7.0.0  -no_cleanup $* >${cmtFSFiltertempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtFSFiltertempfile}
  unset cmtFSFiltertempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtFSFiltertempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtFSFiltertempfile}
unset cmtFSFiltertempfile
return $cmtsetupstatus

