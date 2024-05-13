#ifndef __VIDEO_HPP__
#define __VIDEO_HPP__

#include <opencv2/opencv.hpp>
#include <vector>
#include "filter.hpp"


/**
 * \brief The video API.
 */
namespace Video {
    /** \brief A vector of frames. */
    typedef std::vector<cv::Mat> Video;

    /**
     * \brief Reads and checks a video file.
     * 
     * \param[in] filename The path to the file.
     * \param[in] apiPreference The flags to give to the cv::VideoCapture constructor.
     * 
     * \returns The read video.
     * 
     * \note Will not return a VideoCapture stream in order to loop the video.
     * 
     * \see \link cv::imread \endlink
     */
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

    /**
     * \brief Checks if a given file is a video.
     * 
     * \param[in] filename The path to the file.
     * 
     * \returns true if the file is a video.
     * 
     * \note Only file formats are mp4, avi and mkv. 
     */
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

    /**
     * \brief Displays a video in a window and apply all given filters.
     * 
     * \param[in] video The video to display.
     * \param[in] filters All filters to apply on video.
     * 
     * \note The filters are applied on the fly, so that it can change during the frame loop.
     */
    void display(Video video, std::vector<Filter::filter> filters = {}) {
        int i = 0;
        while (true) {
            cv::Mat frame;
            frame = video[i];

            for (Filter::filter filter: filters) {
                frame = filter(&frame);
            }

            cv::imshow("OpenCV", frame);

            if (cv::waitKey(25) == 27) {
                break;
            }
            
            i = (i + 1) % video.size();
        }
    }
}

#endif