#!/bin/bash

DEPOT="`dirname \"$0\"`" 
DEPOT="`( cd \"$DEPOT\" && cd .. && pwd )`"  # absolutized and normalized
if [ -z "$DEPOT" ] ; then
  # error; for some reason, the path is not accessible
  # to the script (e.g. permissions re-evaled after suid)
  echo "ERROR: cannot determine the location of the DEPOT path."
  exit 1  # fail
fi

export DEPOT

echo "Using DEPOT=$DEPOT"

PC="-DCMAKE_TOOLCHAIN_FILE=$DEPOT/config/Platform_PC.cmake"

PLATFORM=PC
if [ "$1" != "" ]; then
	TOOL=$1
fi

if [ "$2" != "" ]; then
	PLATFORM=$2
fi

eval TOOLCHAIN=\$$PLATFORM
#echo Toolchain: $TOOLCHAIN

function buildModule()
{
	prefix=$1
	module=$2
	echo Building $module...
	mkdir $module
	cd $module
	cmake $TOOLCHAIN $DEPOT/$prefix/$module 
	if [ $? -ne 0  ]
		then exit 1
	fi 
	make $MAKE_OPTS install 
	if [ $? -ne 0  ] 
		then exit 1
	fi
	cd ..
}

MODULES=build.conf
cat $DEPOT/tool/$TOOL/$MODULES | while read lib;
	do buildModule "lib" $lib
done
if [ $? -ne 0  ] 
	then exit 1
fi
buildModule "tool" $TOOL

