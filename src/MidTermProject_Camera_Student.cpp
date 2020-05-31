/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <unordered_map>
#include <map>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

using namespace std;

struct MatchStat
{
    size_t totalMatches = 0;
    double totalProcessingTime = 0.0;
    size_t matchedFramesCount = 0;
}; 

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{

    /* INIT VARIABLES AND DATA STRUCTURES */

    // data location
    string dataPath = "../";

    // camera
    string imgBasePath = dataPath + "images/";
    string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
    string imgFileType = ".png";
    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
    int imgEndIndex = 9;   // last file index to load
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

    // misc
    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
    vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
    bool bVis = false;            // visualize results

    /* MAIN LOOP OVER ALL IMAGES */

    unordered_map<string, MatchStat> matchStat;

    vector<string> detectorTypes = { "SHITOMASI", "HARRIS", "FAST", "BRISK", "ORB", "AKAZE", "SIFT" };
    vector<string> descriptorTypes  = { "BRISK", "BRIEF", "ORB", "FREAK", "AKAZE", "SIFT" };
    
    for (const string & detectorType : detectorTypes)
    {
        for (const string & descriptorType : descriptorTypes)
        {
            cout << "---------- START " << detectorType << ", " << descriptorType << endl;
            for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
            {
                /* LOAD IMAGE INTO BUFFER */

                // assemble filenames for current index
                ostringstream imgNumber;
                imgNumber << setfill('0') << setw(imgFillWidth) << imgStartIndex + imgIndex;
                string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

                // load image from file and convert to grayscale
                cv::Mat img, imgGray;
                img = cv::imread(imgFullFilename);
                cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

                //// STUDENT ASSIGNMENT
                //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

                // push image into data frame buffer
                DataFrame frame;
                frame.cameraImg = imgGray;
                dataBuffer.push_back(frame);

                if(dataBufferSize < dataBuffer.size() ) {
                    dataBuffer.erase(dataBuffer.begin());
                }

                //// EOF STUDENT ASSIGNMENT
                // cout << "#1 : LOAD IMAGE INTO BUFFER done" << endl;

                double totalProcessingTime = (double)cv::getTickCount();

                /* DETECT IMAGE KEYPOINTS */

                // extract 2D keypoints from current image
                vector<cv::KeyPoint> keypoints; // create empty feature list for current image
                // string detectorType = "SHITOMASI";
                // string detectorType = "HARRIS";
                // string detectorType = "FAST";
                // string detectorType = "BRISK";
                // string detectorType = "ORB";
                // string detectorType = "AKAZE";
                // string detectorType = "SIFT";

                //// STUDENT ASSIGNMENT
                //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
                //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT

                if (detectorType.compare("SHITOMASI") == 0)
                {
                    detKeypointsShiTomasi(keypoints, imgGray, false);
                }
                else if (detectorType.compare("HARRIS") == 0)
                {
                    detKeypointsHarris(keypoints, imgGray, false);
                }
                else {
                    detKeypointsModern(keypoints, imgGray, detectorType, false);
                }
                //// EOF STUDENT ASSIGNMENT

                //// STUDENT ASSIGNMENT
                //// TASK MP.3 -> only keep keypoints on the preceding vehicle

                // only keep keypoints on the preceding vehicle
                bool bFocusOnVehicle = true;
                cv::Rect vehicleRect(535, 180, 180, 150);
                vector<cv::KeyPoint> filteredPoints;
                if (bFocusOnVehicle)
                {
                    for (auto keypt:keypoints) {
                        if(vehicleRect.contains(keypt.pt)) 
                        {
                            filteredPoints.push_back(keypt);
                        }
                    }
                    keypoints = filteredPoints;
                }
                            

                //// EOF STUDENT ASSIGNMENT

                // optional : limit number of keypoints (helpful for debugging and learning)
                bool bLimitKpts = false;
                if (bLimitKpts)
                {
                    int maxKeypoints = 50;

                    if (detectorType.compare("SHITOMASI") == 0)
                    { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                        keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
                    }
                    cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
                    cout << " NOTE: Keypoints have been limited!" << endl;
                }

                // push keypoints and descriptor for current frame to end of data buffer
                (dataBuffer.end() - 1)->keypoints = keypoints;
                // cout << "#2 : DETECT KEYPOINTS done" << endl;

                /* EXTRACT KEYPOINT DESCRIPTORS */

                //// STUDENT ASSIGNMENT
                //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
                //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

                cv::Mat descriptors;
                // string descriptorType = "BRIEF"; // BRIEF, ORB, FREAK, AKAZE, SIFT
                // string descriptorType = "ORB"; // BRIEF, ORB, FREAK, AKAZE, SIFT
                // string descriptorType = "FREAK"; // BRIEF, ORB, FREAK, AKAZE, SIFT
                // string descriptorType = "AKAZE"; // BRIEF, ORB, FREAK, AKAZE, SIFT
                // string descriptorType = "SIFT"; // BRIEF, ORB, FREAK, AKAZE, SIFT

                try 
                {
                    descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType);
                }
                catch (cv::Exception & ex)
                {
                    cout << detectorType << " is error with " << descriptorType << endl;
                    continue;
                }

                //// EOF STUDENT ASSIGNMENT

                // push descriptors for current frame to end of data buffer
                (dataBuffer.end() - 1)->descriptors = descriptors;

                // cout << "#3 : EXTRACT DESCRIPTORS done" << endl;

                if (dataBuffer.size() > 1) // wait until at least two images have been processed
                {

                    /* MATCH KEYPOINT DESCRIPTORS */

                    vector<cv::DMatch> matches;
                    string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN
                    //string descriptorType = "DES_BINARY"; // DES_BINARY, DES_HOG
                    // string selectorType = "SEL_NN";       // SEL_NN, SEL_KNN
                    string selectorType = "SEL_KNN";       // SEL_NN, SEL_KNN

                    //// STUDENT ASSIGNMENT
                    //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
                    //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp

                    try
                    {
                        matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                                    (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                                    matches, descriptorType, matcherType, selectorType);
                    }
                    catch (cv::Exception & ex)
                    {
                        cout << detectorType << "is error with " << descriptorType << endl;
                        continue;
                    }

                    totalProcessingTime = ((double)cv::getTickCount() - totalProcessingTime) / cv::getTickFrequency();
                    
                    auto & stat = matchStat[detectorType + "-" + descriptorType];
                    stat.totalMatches += matches.size();
                    stat.totalProcessingTime += totalProcessingTime;
                    stat.matchedFramesCount += 1;

                    //// EOF STUDENT ASSIGNMENT

                    // store matches in current data frame
                    (dataBuffer.end() - 1)->kptMatches = matches;

                    // cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << endl;

                    // visualize matches between current and previous image
                    bVis = true;
                    if (bVis)
                    {
                        cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                        cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                        (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                        matches, matchImg,
                                        cv::Scalar::all(-1), cv::Scalar::all(-1),
                                        vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                        string windowName = "Matching keypoints between two camera images";
                        cv::namedWindow(windowName, 7);
                        cv::imshow(windowName, matchImg);

                        // cout << "Press key to continue to next image" << endl;
                        // cv::waitKey(0); // wait for key to be pressed
                    }
                    bVis = false;
                }

            } // eof loop over all images
        }
    }

    cout  << "-----" << endl;

    multimap<size_t, string, std::greater<size_t>> matchCountToAlg;
    multimap<double, string> averageProcessingTimeToAlg;
    
    for (const auto & pair : matchStat)
    {
        matchCountToAlg.emplace(pair.second.totalMatches, pair.first);
        averageProcessingTimeToAlg.emplace(1.0 * pair.second.totalProcessingTime / pair.second.matchedFramesCount, pair.first);
    }

    cout << "Match count:\n";
    for (const auto & pair : matchCountToAlg)
        cout << "  " << pair.second << ": " << pair.first << endl;

    cout << "Average processing time:\n";
    for (const auto & pair : averageProcessingTimeToAlg)
        cout << "  " << pair.second << ": " << pair.first << endl;

    return 0;
}
