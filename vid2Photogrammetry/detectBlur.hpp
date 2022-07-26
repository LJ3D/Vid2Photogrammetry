#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

#include "commonFunctions.hpp"

// Quantifies the bluriness of an image
float quantifyBlur(const cv::Mat& img){
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY); // Convert to gray
    cv::resize(grayImg, grayImg, cv::Size(512, 512)); // Resize to fixed size
    cv::Mat laplaceImage;
    cv::Laplacian(grayImg, laplaceImage, CV_64F); // Calc laplace filter
    cv::Scalar mean, stddev;
    cv::meanStdDev(laplaceImage, mean, stddev, cv::Mat()); // Get stddev of laplace
    return stddev.val[0]*stddev.val[0]; // Return variance of laplace (variance = stddev^2)
}

void removeBlurryFrames(std::string framesFolder, int threshold){
    std::cout << "==================================================" << std::endl;
    std::cout << "Removing blurry frames...." << std::endl;
    std::cout << "Performing validation..." << std::endl;
    // Check framesFolder exists
    if(!folderExists(framesFolder)){return;}

    // Get the list of files in the framesFolder
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);
    
    // Run blur detection
    std::cout << "Performing blurry frame removal..." << std::endl;
    int removed = 0;
    for(auto fp : files){
        float frameBlur = quantifyBlur(cv::imread(fp)); // Get the blur value of the frame (lower is blurrier)
        if(frameBlur < threshold){ // If blur is below threshold, delete it
            std::filesystem::remove(fp);
            std::cout << "Deleted file " << fp << " | Blur value: " << frameBlur << " | Threshold: " << threshold << std::endl;
            removed++;
        }
    }
    std::cout << "Blurry frame removal complete (" << removed << " deleted)" << std::endl;
}
