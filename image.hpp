#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <opencv2/opencv.hpp>
#include <vector>
#include "filter.hpp"

namespace Image {
    /**
     * \brief Reads and checks an image file.
     * 
     * \param[in] filename The path to the file.
     * \param[in] flags The flags to give to the cv::imread function.
     * 
     * \returns The read image.
     * 
     * \see \link cv::imread \endlink
     */
    cv::Mat read(const cv::String &filename, const int flags = 1) {
        // Load image
        cv::Mat image = cv::imread(filename, flags);
        
        // Check if image is loaded
        if (!image.data) {
            throw "No image data.";
        }

        // Return the image
        return image;
    }

    bool isImage(const cv::String &filename) {
        std::size_t lastDotIndex = filename.find_last_of(".");
        
        // If no dot is found
        if (lastDotIndex == cv::String::npos) {
            return false;
        }

        // Get substring and check for extension
        cv::String extension = filename.substr(lastDotIndex + 1);

        return extension == "png" || extension == "jpeg" || extension == "jpg";
    }

    void display(cv::Mat image, std::vector<Filter::filter> filters = {}) {
        for (Filter::filter filter: filters) {
            image = filter(image);
        }

        while (true) {
            cv::imshow("Display Image", image);
            
            if (cv::waitKey(25) == 27) {
                break;
            }
        }
    }
}

#endif