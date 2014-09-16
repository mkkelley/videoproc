Videoproc
=========
This project is a library and example application for accessing webcam
information and processing that data. The eventual goal is to reconstruct video
depth and create a 3d model of the scene from a fixed-camera perspective, but
the only thing it currently does is calculation and display of keypoint
information.

Library
-------
The library is the solid part of the application (everything under src/, not its subdirectories, and include/).

Dependencies
------------
+ CMake
+ QT4
+ OpenCV2 (with V4L1/2, ffmpeg at least)
