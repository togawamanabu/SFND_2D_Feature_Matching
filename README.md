# SFND 2D Feature Tracking

<img src="images/keypoints.png" width="820" height="248" />

The idea of the camera course is to build a collision detection system - that's the overall goal for the Final Project. As a preparation for this, you will now build the feature tracking part and test various detector / descriptor combinations to see which ones perform best. This mid-term project consists of four parts:

* First, you will focus on loading images, setting up data structures and putting everything into a ring buffer to optimize memory load. 
* Then, you will integrate several keypoint detectors such as HARRIS, FAST, BRISK and SIFT and compare them with regard to number of keypoints and speed. 
* In the next part, you will then focus on descriptor extraction and matching using brute force and also the FLANN approach we discussed in the previous lesson. 
* In the last part, once the code framework is complete, you will test the various algorithms in different combinations and compare them with regard to some performance measures. 

See the classroom instruction and code comments for more details on each of these parts. Once you are finished with this project, the keypoint matching part will be set up and you can proceed to the next lesson, where the focus is on integrating Lidar points and on object detection using deep-learning. 

## MP.1 -  #MP6

written in src code.

## MP.7

Harris keypoins are small. another methods are keypoints and distribution looks good. FAST method is fastest.

## SHITOMASI
Shi-Tomasi detection with n=1370 keypoints in 11.1862 ms
Shi-Tomasi detection with n=1301 keypoints in 8.96171 ms
Shi-Tomasi detection with n=1361 keypoints in 8.90161 ms
Shi-Tomasi detection with n=1358 keypoints in 9.5165 ms
Shi-Tomasi detection with n=1333 keypoints in 9.18037 ms
Shi-Tomasi detection with n=1284 keypoints in 9.2532 ms
Shi-Tomasi detection with n=1322 keypoints in 7.15887 ms
Shi-Tomasi detection with n=1366 keypoints in 8.03797 ms
Shi-Tomasi detection with n=1389 keypoints in 8.01015 ms
Shi-Tomasi detection with n=1339 keypoints in 9.14601 ms

## HARIS
Harris detection with n=115 keypoints in 2.39259 ms
Harris detection with n=98 keypoints in 2.2978 ms
Harris detection with n=113 keypoints in 2.4815 ms
Harris detection with n=121 keypoints in 2.4545 ms
Harris detection with n=160 keypoints in 3.01616 ms
Harris detection with n=383 keypoints in 12.5885 ms
Harris detection with n=85 keypoints in 2.02637 ms
Harris detection with n=210 keypoints in 3.79322 ms
Harris detection with n=171 keypoints in 3.42694 ms
Harris detection with n=281 keypoints in 7.54068 ms

## FAST
FAST detection with n=1824 keypoints in 0.490677 ms
FAST detection with n=1832 keypoints in 0.603235 ms
FAST detection with n=1810 keypoints in 0.570256 ms
FAST detection with n=1817 keypoints in 0.576214 ms
FAST detection with n=1793 keypoints in 0.569704 ms
FAST detection with n=1796 keypoints in 0.565513 ms
FAST detection with n=1788 keypoints in 0.567789 ms
FAST detection with n=1695 keypoints in 0.56379 ms
FAST detection with n=1749 keypoints in 0.584792 ms
FAST detection with n=1770 keypoints in 0.590117 ms

## BRISK
BRISK detection with n=2757 keypoints in 129.371 ms
BRISK detection with n=2777 keypoints in 130.424 ms
BRISK detection with n=2741 keypoints in 128.533 ms
BRISK detection with n=2735 keypoints in 120.556 ms
BRISK detection with n=2757 keypoints in 124.441 ms
BRISK detection with n=2695 keypoints in 120.197 ms
BRISK detection with n=2715 keypoints in 120.656 ms
BRISK detection with n=2628 keypoints in 119.734 ms
BRISK detection with n=2639 keypoints in 121.536 ms
BRISK detection with n=2672 keypoints in 128.696 ms

## ORB
ORB detection with n=500 keypoints in 4.61816 ms
ORB detection with n=500 keypoints in 6.35503 ms
ORB detection with n=500 keypoints in 5.03546 ms
ORB detection with n=500 keypoints in 5.10438 ms
ORB detection with n=500 keypoints in 5.00492 ms
ORB detection with n=500 keypoints in 4.959 ms
ORB detection with n=500 keypoints in 5.0276 ms
ORB detection with n=500 keypoints in 5.24325 ms
ORB detection with n=500 keypoints in 8.45907 ms
ORB detection with n=500 keypoints in 5.26828 ms

## AKAZE
AKAZE detection with n=1351 keypoints in 50.5951 ms
AKAZE detection with n=1327 keypoints in 48.3692 ms
AKAZE detection with n=1311 keypoints in 53.2049 ms
AKAZE detection with n=1351 keypoints in 47.5184 ms
AKAZE detection with n=1360 keypoints in 47.1737 ms
AKAZE detection with n=1347 keypoints in 47.5129 ms
AKAZE detection with n=1363 keypoints in 46.556 ms
AKAZE detection with n=1331 keypoints in 48.217 ms
AKAZE detection with n=1358 keypoints in 48.996 ms
AKAZE detection with n=1331 keypoints in 48.6685 ms

## SIFT
SIFT detection with n=1438 keypoints in 67.2726 ms
SIFT detection with n=1371 keypoints in 63.1852 ms
SIFT detection with n=1380 keypoints in 69.1296 ms
SIFT detection with n=1335 keypoints in 66.1743 ms
SIFT detection with n=1305 keypoints in 61.1564 ms
SIFT detection with n=1369 keypoints in 70.2995 ms
SIFT detection with n=1396 keypoints in 71.4924 ms
SIFT detection with n=1382 keypoints in 67.8223 ms
SIFT detection with n=1463 keypoints in 70.2025 ms
SIFT detection with n=1422 keypoints in 60.0226 ms


# MP.8 #MP.9

Top3  
1. FAST-BRIEF (Fast and accuracy)
2. FAST-ORB (Fast less accuracy)
3. BRISK-BRIEF(High accuracy but slower)

Match count:
  BRISK-BRIEF: 1704
  BRISK-BRISK: 1570
  BRISK-FREAK: 1526
  BRISK-ORB: 1510
  AKAZE-BRIEF: 1266
  AKAZE-AKAZE: 1259
  AKAZE-BRISK: 1215
  AKAZE-FREAK: 1188
  AKAZE-ORB: 1186
  FAST-BRIEF: 1099
  FAST-ORB: 1081
  SHITOMASI-BRIEF: 944
  SHITOMASI-ORB: 907
  FAST-BRISK: 899
  FAST-FREAK: 881
  SHITOMASI-BRISK: 767
  SHITOMASI-FREAK: 766
  ORB-ORB: 761
  ORB-BRISK: 751
  SIFT-BRIEF: 702
  SIFT-FREAK: 596
  SIFT-BRISK: 592
  ORB-BRIEF: 545
  ORB-FREAK: 421
  HARRIS-BRIEF: 173
  HARRIS-ORB: 160
  HARRIS-FREAK: 146
  HARRIS-BRISK: 142
  SIFT-SIFT: 0
  ORB-SIFT: 0
  FAST-SIFT: 0
  SHITOMASI-SIFT: 0
  BRISK-SIFT: 0
  HARRIS-SIFT: 0

Average processing time:
  FAST-BRIEF: 0.00155867
  FAST-ORB: 0.0026358
  ORB-BRIEF: 0.00673004
  SHITOMASI-BRIEF: 0.00808094
  SHITOMASI-ORB: 0.00904844
  HARRIS-BRIEF: 0.0116728
  ORB-ORB: 0.0127611
  HARRIS-ORB: 0.0131477
  FAST-SIFT: 0.0154173
  FAST-FREAK: 0.0164499
  SHITOMASI-SIFT: 0.0207983
  SHITOMASI-FREAK: 0.0219713
  ORB-FREAK: 0.0234423
  HARRIS-SIFT: 0.0262416
  HARRIS-FREAK: 0.0284254
  ORB-SIFT: 0.0286491
  AKAZE-BRIEF: 0.0504173
  AKAZE-ORB: 0.0545691
  AKAZE-FREAK: 0.0688749
  SIFT-BRIEF: 0.0737017
  SIFT-FREAK: 0.0936889
  FAST-BRISK: 0.0941404
  AKAZE-AKAZE: 0.0973922
  ORB-BRISK: 0.100836
  HARRIS-BRISK: 0.104332
  SHITOMASI-BRISK: 0.104603
  BRISK-BRIEF: 0.119125
  BRISK-ORB: 0.124056
  BRISK-FREAK: 0.132872
  SIFT-SIFT: 0.134851
  BRISK-SIFT: 0.145648
  AKAZE-BRISK: 0.153272
  SIFT-BRISK: 0.17982
  BRISK-BRISK: 0.217778
