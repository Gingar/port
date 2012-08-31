#!/bin/bash

DEPOT="`dirname \"$0\"`" 
DEPOT="`( cd \"$DEPOT\" && pwd )`"  # absolutized and normalized
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
echo "Toolchain: $TOOLCHAIN"

function addPackage()
{
  DEB_PAKAGES="${DEB_PAKAGES} ${1}${DEB_ARCH}.deb"
}

DEB_FTP=http://ftp.us.debian.org/debian/pool/main/
DEB_ARCH=i386
DEB_PAKAGES=
addPackage b/boost1.42/libboost1.42-dev_1.42.0-4_
addPackage b/boost1.42/libboost-thread1.42.0_1.42.0-4_
addPackage b/boost1.42/libboost-thread1.42-dev_1.42.0-4_
addPackage b/boost1.42/libboost-filesystem1.42.0_1.42.0-4_
addPackage b/boost1.42/libboost-filesystem1.42-dev_1.42.0-4_
addPackage b/boost1.42/libboost-system1.42.0_1.42.0-4_
addPackage b/boost1.42/libboost-system1.42-dev_1.42.0-4_
addPackage b/boost1.42/libboost-regex1.42.0_1.42.0-4_
addPackage b/boost1.42/libboost-regex1.42-dev_1.42.0-4_
addPackage g/gtest/libgtest0_1.5.0-1_
addPackage g/gtest/libgtest-dev_1.5.0-1_

export PREFIX=$DEPOT/DEPLOY/usr
mkdir -p $PREFIX
cd $DEPOT/DEPLOY
#local debpackage
for deburl in ${DEB_PAKAGES}; do
  deburl=${DEB_FTP}${deburl}
  echo "Downloading $deburl..."
  wget -nc -nv ${deburl}
  if [ $? -ne 0  ]
    then exit 1
  fi
done

for debfile in *; do
  debtemplate="\.deb$"
  if [[ ${debfile} =~ ${debtemplate} ]]; then
    echo "Unpacking ${debfile}..."
    dpkg -x ${debfile} .
    if [ $? -ne 0  ]
      then exit 1
    fi
  fi
done

function buildModule()
{
  module=$1
  echo "====================================================================="
  echo "Building $module..."
  echo " "
  mkdir -p $DEPOT/BUILD/$module
  cd $DEPOT/BUILD/$module
  cmake $TOOLCHAIN $DEPOT/$module
  if [ $? -ne 0  ]
    then exit 1
  fi

echo "MAKE_OPTS=$MAKE_OPTS"
  make $MAKE_OPTS install
  if [ $? -ne 0  ]
    then exit 1
  fi
  cd $DEPOT
}

MODULES=build.conf
cat $DEPOT/ginga/$MODULES | while read lib;
  do buildModule $lib
done
if [ $? -ne 0  ] 
  then exit 1
fi
buildModule ginga

