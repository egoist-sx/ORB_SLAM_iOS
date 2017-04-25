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

1. Download zip file from [Baidu Drive](https://pan.baidu.com/s/1bYkyHS)(I switched to Baidu Drive due to Google Drive's payment issue) and unzip it to root folder. This contains compiled ARM64 libs g2o/boost which is too large for github.
2. Download vocabulary from orginal author's [page](https://github.com/raulmur/ORB_SLAM/blob/master/Data/ORBvoc.txt.tar.gz) and unzip it to SLAM/ORB_SLAM/Data
