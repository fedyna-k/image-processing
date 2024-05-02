#include <opencv2/opencv.hpp>
#include <iostream>

#include "image.hpp"
#include "video.hpp"
#include "filter.hpp"

int main(int argc, char** argv) {
    // Get file

    if (argc != 2) {
        std::printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    if (Image::isImage(argv[1])) {
        cv::Mat image = Image::read(argv[1]);
        Image::display(image, {Filter::grayscale});
    } else if (Video::isVideo(argv[1])) {
        Video::Video video = Video::read(argv[1]);
        Video::display(video, {Filter::grayscale});
    } else {
        std::cerr << "Unsupported file format." << std::endl;
        return -1;
    }

    return 0;
}