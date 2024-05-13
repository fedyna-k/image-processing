#include <opencv2/opencv.hpp>
#include <iostream>

#include "image.hpp"
#include "video.hpp"
#include "filter.hpp"
#include "cli.hpp"

int main(int argc, char** argv) {
    // Get file and arguments
    CLI::OptionMap options = CLI::processOptions(argc, argv);
    CLI::Args args = CLI::getArgs(argc, argv);

    if (args.size() != 1) {
        std::cout << CLI::help_message << std::endl;
        return -1;
    }

    // Get all the filters according to the arguments
    std::vector<Filter::filter> filters = std::vector<Filter::filter>();
    for (auto option: options) {
        if (option.second) {
            if (option.first.compare("-gs") == 0) {
                filters.push_back(Filter::grayscale);
            }
            if (option.first.compare("-gsl") == 0) {
                filters.push_back(Filter::grayscaleLine);
            }
            if (option.first.compare("-gse") == 0) {
                filters.push_back(Filter::grayscaleExpansion);
            }
            if (option.first.compare("-ed") == 0) {
                filters.push_back(Filter::edgeDetection);
            }
        }
    }

    // Create a new window
    cv::namedWindow("OpenCV");

    // Display the right type of data with the filters
    if (Image::isImage(args[0])) {
        cv::Mat image = Image::read(args[0]);
        Image::display(image, filters);
    } else if (Video::isVideo(args[0])) {
        Video::Video video = Video::read(args[0]);
        Video::display(video, filters);
    } else {
        std::cerr << "Unsupported file format." << std::endl;
        return -1;
    }

    return 0;
}