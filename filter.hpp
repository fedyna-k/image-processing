#ifndef __FILTER_HPP__
#define __FILTER_HPP__

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


/**
 * \brief The image processing API.
 */
namespace Filter {
    /** \brief Typedef for filter function */
    typedef cv::Mat (*filter)(cv::Mat);

    /**
     * \brief Apply grayscale on image.
     * 
     * \param[in] image The image to process.
     * 
     * \returns A grayscaled version of the image.
     */
    cv::Mat grayscale(cv::Mat image) {
        cv::Mat greyMat;
        cv::cvtColor(image, greyMat, cv::COLOR_BGR2GRAY);
        return greyMat;
    }

    /**
     * \brief Apply edge detection on image.
     * 
     * \param[in] image The image to process.
     * 
     * \returns The edges of the image.
     */
    cv::Mat edgeDetection(cv::Mat image) {
        cv::Mat blurred, edges;
        cv::blur(image, blurred, cv::Size(3, 3));
        cv::Canny(blurred, edges, 0, 300);
        return edges;
    }
}

#endif