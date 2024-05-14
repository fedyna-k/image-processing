#ifndef __HISTOGRAM_HPP__
#define __HISTOGRAM_HPP__

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


/**
 * \brief The image histogram API.
 */
namespace Histogram {
    /**
     * \brief Create a grayscale profile histogram.
     * 
     * \param[in] event The mouse event ID.
     * \param[in] x The x coordinate of the mouse.
     * \param[in] y The y coordinate of the mouse.
     * \param[in] flags Is there a modifier on the event?
     * \param[in] userdata The data given (should be the image to process).
     */
    void grayscaleLineCallback(int event, int x, int y, int flags, void *userdata) {
        // On click
        if (event == cv::EVENT_LBUTTONDOWN) {
            // Get the image data
            cv::Mat image = *reinterpret_cast<cv::Mat *>(userdata);
            int imageWidth = image.size().width;

            // Create profile
            cv::Mat Profile = cv::Mat(256, imageWidth, CV_8U, cv::Scalar(255));

            int valueBefore = image.at<uchar>(y, 0);
            int valueAfter = image.at<uchar>(y, 0);
            cv::line(Profile, {0, 256 - valueBefore}, {0, 256 - valueAfter}, 0);

            for (int i = 1 ; i < imageWidth ; i++) {
                valueBefore = image.at<uchar>(y, i - 1);
                valueAfter = image.at<uchar>(y, i);
                cv::line(Profile, {i, 256 - valueBefore}, {i, 256 - valueAfter}, 0);
            }
            cv::imshow("Profile", Profile);

            // Draw red line on image
            cv::Mat cloned = image.clone();
            cv::cvtColor(cloned, cloned, cv::COLOR_GRAY2BGR);
            cv::line(cloned, {0, y}, {imageWidth, y}, cv::Scalar(0, 0, 255));
            cv::imshow("OpenCV", cloned);
        }
    }

    /**
     * \brief Create a grayscale histogram of all pixels.
     * 
     * \param[in] name The created window name.
     * \param[in] image The image to get the histogram from (must be grayscaled).
     */
    void createGrayscale(const char *name, cv::Mat image) {
        // Compute histogram values
        cv::Mat histData;
        int channels[] = {0};
        int histSize[] = {256};
        float range[] = {0, 256};
        const float* ranges[] = {range};

        cv::calcHist(&image, 1, channels, cv::Mat(), histData, 1, histSize, ranges);

        // Normalize it
        cv::normalize(histData, histData, 0, 256, cv::NORM_MINMAX);

        // Create the histogram
        cv::Mat hist = cv::Mat(256, 256, CV_8U, 0xffffff);
        for (int i = 0 ; i < 256 ; i++) {
            cv::line(hist, {i, 256}, {i, 255 - (uchar)histData.at<float>(i)}, 0);
        }

        // Display it
        cv::imshow(name, hist);
    }
}

#endif