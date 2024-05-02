#ifndef __VIDEO_HPP__
#define __VIDEO_HPP__

#include <opencv2/opencv.hpp>
#include <vector>
#include "filter.hpp"

namespace Video {
    typedef std::vector<cv::Mat> Video;

    Video read(const cv::String &filename, int apiPreference = 0) {
        // Load image
        cv::VideoCapture capture = cv::VideoCapture(filename, apiPreference);
        Video video = Video();
        
        // Check if image is loaded
        if (!capture.isOpened()) {
            throw "No video data.";
        }

        while (true) {
            cv::Mat frame;
            capture >> frame;

            if (frame.empty()) {
                break;
            }

            video.push_back(frame);            
        }        

        // Return the image
        return video;
    }

    bool isVideo(const cv::String &filename) {
        std::size_t lastDotIndex = filename.find_last_of(".");
        
        // If no dot is found
        if (lastDotIndex == cv::String::npos) {
            return false;
        }

        // Get substring and check for extension
        cv::String extension = filename.substr(lastDotIndex + 1);

        return extension == "mp4" || extension == "avi" || extension == "mkv";
    }

    void display(Video video, std::vector<Filter::filter> filters = {}) {
        int i = 0;
        while (true) {
            cv::Mat frame;
            frame = video[i];

            for (Filter::filter filter: filters) {
                frame = filter(frame);
            }

            cv::imshow("Video", frame);

            if (cv::waitKey(25) == 27) {
                break;
            }
            
            i = (i + 1) % video.size();
        }
    }
}

#endif