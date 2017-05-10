#ifndef BINARISATION_IMAGE_H
#define BINARISATION_IMAGE_H

#include <Magick++.h>
#include <string>
#include <iostream>

class ImageLink {
    Magick::Image image;
    Magick::PixelPacket *raw_data;
    std::string format;

    void init() {
        image.type(Magick::GrayscaleType);
        raw_data = image.getPixels(0, 0, static_cast<size_t>(width()), static_cast<size_t>(height()));
    }

public:
    explicit ImageLink(const std::string &filename, const std::string &format)
            : image(filename), format(format) {
        init();
    }

    explicit ImageLink(const std::string &filename)
            : image(filename), format("PNG") {
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
        image.magick(format);
        image.write(filename);
    }

    void display() {
        image.display();
    }
};

#endif
