#ORB_SLAM_iOS

This is iOS port of [ORB_SLAM](https://github.com/raulmur/ORB_SLAM) with modified dependency for iOS.

Various IO options and utility are provided to test ORB_SLAM, including:

1. Metal for AR testing
2. SceneKit for realtime trajectory viewing
3. AVFoudnation for live RGB stream
4. OpenCV utilities for record data and stream from files
5. StrctureSensor(optional) for scale calibrated tracking and map reconstruction

This code has been tested on Xcode 7 with iPhone 6 plus (iOS9)

USAGE:

1. Download https://drive.google.com/open?id=0B1nzrhyFOuT3SXE1UHplLWFwOGs and unzip it to root folder. This contains compiled ARM64 libs g2o/boost which is too large for github.
2. Either download vocabulary from https://drive.google.com/open?id=0B1nzrhyFOuT3am5JeDZDRjJGNkU or orginal author's page and unzip it to SLAM/ORB_SLAM/Data
