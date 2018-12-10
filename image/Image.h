#pragma once

#include <opencv2/imgcodecs.hpp>
#include <string>
#include <iostream>

class Image {
public:
    explicit Image(const std::string &filename) {
        image = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    }

    int Height() const {
        return image.size().height;
    }

    int Width() const {
        return image.size().width;
    }

    int GetIntensity(int h, int w) const {
        return image.at<uchar>(h, w);
    }

    void SetIntensity(int value, int h, int w) {
        image.at<uchar>(h, w) = static_cast<uchar>(value);
    }

    void Write(const std::string& filename) {
        cv::imwrite(filename, image);
    }

private:
    cv::Mat image;
};
