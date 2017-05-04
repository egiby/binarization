#ifndef BINARISATION_IMAGE_H
#define BINARISATION_IMAGE_H

#include <Magick++.h>
#include <string>
#include <iostream>

class ImageLink {
    Magick::Image image;
    Magick::PixelPacket* raw_data;

    void init() {
        image.type(Magick::GrayscaleType);
        raw_data = image.getPixels(0, 0, width(), height());
    }

public:
    explicit ImageLink(const std::string &filename)
    : image(filename) {
        init();
    }

    explicit ImageLink(Magick::Image image)
            : image(image) {
        init();
    }

    int height() const {
        return (int) image.size().height();
    }

    int width() const {
        return (int) image.size().width();
    }

    Magick::PixelPacket *operator[](const size_t n) {
        return raw_data + n * width();
    }

    MagickCore::Quantum get_intensity(int h, int w) const {
        return (raw_data + h * width() + w)->green; // they all the same
    }

    void sync() {
        image.syncPixels();
    }

    void write(const std::string &filename) {
        image.write(filename);
    }
};

#endif
