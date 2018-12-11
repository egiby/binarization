#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <filesystem>

#include <opencv2/imgcodecs.hpp>
#include <vips/vips8>

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

    void WriteOneBitImage(const std::string& filename) {
        char tmpName[L_tmpnam];
        tmpnam(tmpName);
        std::string tmp = std::string(tmpName) + ".tiff";
        Write(tmp);

        vips::VImage image = vips::VImage::new_from_file(tmp.c_str());
        image.write_to_file(filename.c_str(),
                            vips::VImage::option()
                                    ->set("squash", true)
                                    ->set("compression", VIPS_FOREIGN_TIFF_COMPRESSION_DEFLATE)
        );
    }

private:
    cv::Mat image;
};
