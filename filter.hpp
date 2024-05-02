#ifndef __FILTER_HPP__
#define __FILTER_HPP__

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Filter {
    typedef cv::Mat (*filter)(cv::Mat);

    cv::Mat grayscale(cv::Mat image) {
        cv::Mat greyMat;
        cv::cvtColor(image, greyMat, cv::COLOR_BGR2GRAY);
        return greyMat;
    }

    cv::Mat edgeDetection(cv::Mat image) {
        cv::Mat blurred, edges;
        cv::blur(image, blurred, cv::Size(3, 3));
        cv::Canny(blurred, edges, 0, 300);
        return edges;
    }
}

#endif