#ifndef __FILTER_HPP__
#define __FILTER_HPP__

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "histogram.hpp"

/**
 * \brief The image processing API.
 */
namespace Filter {
    /** \brief Typedef for filter function */
    typedef cv::Mat (*filter)(cv::Mat *);

    /**
     * \brief Apply grayscale on image.
     * 
     * \param[in] image The image to process.
     * 
     * \returns A grayscaled version of the image.
     */
    cv::Mat grayscale(cv::Mat *image) {
        cv::Mat greyMat;
        cv::cvtColor(*image, greyMat, cv::COLOR_BGR2GRAY);
        return greyMat;
    }

    /**
     * \brief Apply edge detection on image.
     * 
     * \param[in] image The image to process.
     * 
     * \returns The edges of the image.
     */
    cv::Mat edgeDetection(cv::Mat *image) {
        cv::Mat blurred, edges;
        cv::blur(*image, blurred, cv::Size(3, 3));
        cv::Canny(blurred, edges, 0, 300);
        return edges;
    }

    /**
     * \brief Create an histogram for a grayscale image of the values on a line.
     * 
     * \param[in] image The image to process.
     * 
     * \returns The image as it is.
     */
    cv::Mat grayscaleLine(cv::Mat *image) {
        *image = grayscale(image);
        
        cv::setMouseCallback("OpenCV", Histogram::grayscaleLineCallback, image);

        return *image;
    }

    /**
     * \brief Create an histogram for a grayscale image of the values on a line.
     * 
     * \param[in] image The image to process.
     * 
     * \returns The image as it is.
     */
    cv::Mat grayscaleExpansion(cv::Mat *image) {
        *image = grayscale(image);
        cv::Mat expanded = image->clone();
        
        // Search the minimum and maximum
        int min = 0;
        int max = 0;
        for (int y = 0 ; y < expanded.rows ; y++) {
            for (int x = 0 ; x < expanded.cols ; x++) {
                int coef = expanded.at<uchar>(y, x);
                min = min > coef ? coef : min;
                max = max < coef ? coef : max;
            }
        }

        // Apply range expansion (I like to expand).
        for (int y = 0 ; y < expanded.rows ; y++) {
            for (int x = 0 ; x < expanded.cols ; x++) {
                int coef = expanded.at<uchar>(y, x);
                expanded.at<uchar>(y, x) = (uchar)(255 * (coef - min) / (1. * (max - min)));
            }
        }

        cv::imshow("Expanded", expanded);
        Histogram::createGrayscale("Original Histogram", *image);
        Histogram::createGrayscale("Expanded Histogram", expanded);

        return *image;
    }
}

#endif