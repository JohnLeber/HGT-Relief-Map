# HGT-Relief-Map

Sample C++ Windows application that creates relief map images from high resolution 1 arc-second HGT files. The application was used to create the relief maps in my [New Zealand Digital Elevation Model project](https://github.com/nodecomplete/NZDEM-HGT-30/tree/master/Images). 

The application expects a high resolution HGT file ( 1 arc-second ). These files are 3601 by 3601 and contain the height in meters stored as a 16 bit value.
The output file is a 1200 by 1200 bitmap/jpg file containing the relief map. Relief maps allow the HGT to be visualized more easily. For more information about HGT files see my other [project](https://github.com/nodecomplete/NZDEM-HGT-30). 

**Building the application**

The project was written using Visual Studio 2019 (make sure the desktop C++ and MFC options are installed).

![alt text](https://github.com/nodecomplete/HGT-Relief-Map/blob/master/ScreenShot.jpg)

**Credits**

1) The Vector SIMD code was copied from [here](https://github.com/pelletier/vector3).
2) the colour map was inpsired from 3dem application that apparently is no longer supported but an old version can be downloaded from here http://www.visualizationsoftware.com/3dem.

 
 

The image below shows a relief map of the [S44E170.hgt](https://github.com/nodecomplete/NZDEM-HGT-30/blob/master/HGT/S44E170.zip) file (West Coast/Southern Alps of New Zealand).

![alt text](https://github.com/nodecomplete/HGT-Relief-Map/blob/master/ReliefMap.jpg)

More samples, in this case Tongariro National Park [S40E175.hgt](https://github.com/nodecomplete/NZDEM-HGT-30/blob/master/HGT/S40E175.zip) and Otage/Southland.

![alt text](https://github.com/nodecomplete/HGT-Relief-Map/blob/master/ReliefMap2.jpg)

![alt text](https://github.com/nodecomplete/HGT-Relief-Map/blob/master/ReliefMap3.jpg)

