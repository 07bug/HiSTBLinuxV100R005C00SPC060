# a silly hack that generates autoregen.sh but it's handy
# Remove the old autoregen.sh first to create a new file,
# as the current one may be being read by the shell executing
# this script.
if [ -f "autoregen.sh" ]; then
  rm autoregen.sh
fi
echo "#!/bin/sh" > autoregen.sh
echo "./autogen.sh $@ \$@" >> autoregen.sh
chmod +x autoregen.sh

# helper functions for autogen.sh

debug ()
# print out a debug message if DEBUG is a defined variable
{
  if test ! -z "$DEBUG"
  then
    echo "DEBUG: $1"
  fi
}


autogen_options ()
{
  if test "x$1" = "x"; then
    return 0
  fi

  while test "x$1" != "x" ; do
    optarg=`expr "x$1" : 'x[^=]*=\(.*\)'`
    case "$1" in
      --noconfigure)
          NOCONFIGURE=defined
	  AUTOGEN_EXT_OPT="$AUTOGEN_EXT_OPT --noconfigure"
          echo "+ configure run disabled"
          shift
          ;;
      --nocheck)
	  AUTOGEN_EXT_OPT="$AUTOGEN_EXT_OPT --nocheck"
          NOCHECK=defined
          echo "+ autotools version check disabled"
          shift
          ;;
      -d|--debug)
          DEBUG=defined
	  AUTOGEN_EXT_OPT="$AUTOGEN_EXT_OPT --debug"
          echo "+ debug output enabled"
          shift
          ;;
      -h|--help)
          echo "autogen.sh (autogen options) -- (configure options)"
          echo "autogen.sh help options: "
          echo " --noconfigure            don't run the configure script"
          echo " --nocheck                don't do version checks"
          echo " --debug                  debug the autogen process"
          echo
          echo " --with-autoconf PATH     use autoconf in PATH"
          echo " --with-automake PATH     use automake in PATH"
          echo
          echo "Any argument either not in the above list or after a '--' will be "
          echo "passed to ./configure."
	  exit 1
          ;;
      --with-automake=*)
          AUTOMAKE=$optarg
          echo "+ using alternate automake in $optarg"
	  CONFIGURE_DEF_OPT="$CONFIGURE_DEF_OPT --with-automake=$AUTOMAKE"
          shift
          ;;
      --with-autoconf=*)
          AUTOCONF=$optarg
          echo "+ using alternate autoconf in $optarg"
	  CONFIGURE_DEF_OPT="$CONFIGURE_DEF_OPT --with-autoconf=$AUTOCONF"
          shift
          ;;
      --) shift ; break ;;
      *)
          echo "+ passing argument $1 to configure"
	  CONFIGURE_EXT_OPT="$CONFIGURE_EXT_OPT $1"
          shift
          ;;
    esac
  done

  for arg do CONFIGURE_EXT_OPT="$CONFIGURE_EXT_OPT $arg"; done
  if test ! -z "$CONFIGURE_EXT_OPT"
  then
    echo "+ options passed to configure: $CONFIGURE_EXT_OPT"
  fi
}

toplevel_check ()
{
  srcfile=$1
  test -f $srcfile || {
        echo "You must run this script in the top-level $package directory"
        exit 1
  }
}

tool_run ()
{
  tool=$1
  options=$2
  run_if_fail=$3
  echo "+ running $tool $options..."
  $tool $options || {
    echo
    echo $tool failed
    eval $run_if_fail
    exit 1
  }
}

install_git_hooks ()
{
  if test -d .git; then
    # install pre-commit hook for doing clean commits
    for hook in pre-commit; do
      if test ! \( -x .git/hooks/$hook -a -L .git/hooks/$hook \); then
        echo "+ Installing git $hook hook"
        rm -f .git/hooks/$hook
        ln -s ../../common/hooks/$hook.hook .git/hooks/$hook || {
          # if we couldn't create a symbolic link, try doing a plain cp
          if cp common/hooks/pre-commit.hook .git/hooks/pre-commit; then
            chmod +x .git/hooks/pre-commit;
          else
            echo "********** Couldn't install git $hook hook **********";
          fi
        }
      fi
    done
  fi
}
