# MetOceanViewer
Multipurpose tool for viewing hydrodynamic model data, such as ADCIRC, with a gui interface. The code is written in Qt C++ and is designed to run on Windows, Mac OSX, and Linux systems.

# Feature List
- [x] Access and view NOAA station data
- [x] Access and view USGS station data
- [x] Read ADCIRC fort.61 files (when accompanied by station file)
- [x] Read ADCIRC netCDF formatted files
- [x] Read/write IMEDS formatted data
- [x] Read HWM comparisons, plot to map, and calculate statistics

# Planned Upgrades
- [ ] Read Delft3D native formatted NEFIS files
- [x] Allow download of longer periods of data from NOAA interface
- [x] Remove restriction on files having same locations
- [ ] Add interface to NOAA Currents stations
- [ ] Add data to session files upon request of user

# Screenshots
![Screenshot 1](https://github.com/zcobell/MetOceanViewer/blob/master/screenshots/mov_ss1.JPG)
![Screenshot 2](https://github.com/zcobell/MetOceanViewer/blob/master/screenshots/mov_ss2.JPG)
![Screenshot 3](https://github.com/zcobell/MetOceanViewer/blob/master/screenshots/mov_ss3.JPG)

# Compiling
To compile this program, please use the Qt suite of tools. The MetOceanViewer.pro file has been tested using QtCreator and Qt version 5.5.0 on Windows, Mac OSX, and Linux.

##QtCharts
This program requires the non-standard QtCharts library. This is packaged as part of the windows DLLs provided here, however, to compile this code for yourself you will need to manually generate this Qt module. The QtCharts module can be obtained [here](https://code.qt.io/cgit/qt/qtcharts.git). This module has taken over for the HighCharts plotting routines which, while extremely powerful, are not ideal for being embedded in a Qt C++ application with large amounts of data.

##QtWebEngine
This program requires a version of Qt with QtWebEngine available. The Qt development team has decided that it will discontinue support for QtWebKit in favor of QtWebEngine. This project has followed their lead in order to maintain access to updates and bug fixes. 

# Credits
The following external libraries/APIs are used in this software
- NOAA CO-OPS API (http://tidesandcurrents.noaa.gov)
- USGS Waterdata API (http://waterdata.usgs.gov)
- Google Maps v3.x API (http://maps.google.com)
- Google Fusion Tables API (http://tables.googlelabs.com)
- netCDF v4.3.3 (http://www.unidata.ucar.edu/software/netcdf)
- HDF5 v1.8.14 (http://www.hdfgroup.org/HDF5)
- Curl v7.35.0 (http://curl.haxx.se)
- zlib v1.2.8 (http://www.zlib.net)
- OpenSSL v1.0.2d (https://www.openssl.org/)

# License
This program conforms to the GNU GPL, Version 3, with the caveat that the name MetOcean Viewer is specific to this project and derivative works should be named differently.
