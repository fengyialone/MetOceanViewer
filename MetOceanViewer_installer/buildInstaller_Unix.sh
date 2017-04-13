#!/bin/bash

QtHome=/opt/Qt
QtLibDir=/opt/Qt/5.8/gcc_64/lib
executable=../../build-MetOceanViewer-Desktop_Qt_5_8_0_GCC_64bit-Release/MetOceanViewer_GUI/MetOceanViewer
webenginelib=/opt/Qt/5.8/gcc_64/lib/libQt5WebEngineCore.so.5
proj4lib=../../build-MetOceanViewer-Desktop_Qt_5_8_0_GCC_64bit-Release/libraries/libproj4/libmovProj4.so.1
xtide=../MetOceanViewer_GUI/mov_libs/bin/tide
harmonics=../MetOceanViewer_GUI/mov_libs/bin/harmonics.tcd
version=$(git describe --always --tags --dirty)


if [ ! -s $executable ] ; then
    echo "ERROR: executable not found."
    exit 1
fi

if [ ! -s $xtide ] ; then
    echo "ERROR: XTide executable not found."
    exit 1
fi

if [ ! -s $harmonics ] ; then
    echo "ERROR: Tidal database not found."
    exit 1
fi

if [ ! -s $QtHome/Tools/QtInstallerFramework/2.0/bin/binarycreator ] ; then
    echo "ERROR: Qt Installer Framework not found"
    exit 1
fi

echo "Gathering libraries..."
ldd $executable    > liblist.txt
ldd $webenginelib >> liblist.txt

mkdir -p ./packages_unix/com.zachcobell.metoceanviewer/data
mkdir -p ./packages_unix/com.qt.qtsharedlibraries/data
mkdir -p ./packages_unix/com.unidata.netcdf/data 

cp $executable ./packages_unix/com.zachcobell.metoceanviewer/data/.
cp $proj4lib ./packages_unix/com.zachcobell.metoceanviewer/data/.
cp $xtide ./packages_unix/com.zachcobell.metoceanviewer/data/.
cp $harmonics ./packages_unix/com.zachcobell.metoceanviewer/data/.

while read LIB
do

    NAME=$(echo $LIB | cut -d= -f1)
    SHORTNAME=$(echo $LIB | cut -d= -f1 | cut -c1-5)
    SHORTNAME2=$(echo $LIB | cut -d= -f1 | cut -c1-9)
    SHORTNAME3=$(echo $LIB | cut -d= -f1 | cut -c1-7)
    LOCATION=$(echo $LIB | cut -d">" -f2 | cut -d"(" -f1)
    LIBDIR=$(dirname $LOCATION 2>/dev/null)
    
    if [ "x$LIBDIR" == "x$QtLibDir" ] ; then
        cp $LOCATION ./packages_unix/com.qt.qtsharedlibraries/data/.
    elif [ $SHORTNAME2 == "libnetcdf" ] ; then
        cp $LOCATION ./packages_unix/com.unidata.netcdf/data/.
    elif [ $SHORTNAME3 == "libhdf5" ] ; then
        cp $LOCATION ./packages_unix/com.unidata.netcdf/data/.
    fi

done < liblist.txt

rm liblist.txt

echo "Building Installer..."
$QtHome/Tools/QtInstallerFramework/2.0/bin/binarycreator -c config/config.xml -p packages_unix MetOceanViewer_Unix_Installer_$version.bin
