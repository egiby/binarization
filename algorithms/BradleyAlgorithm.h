#pragma once

#include <image/Image.h>

#include <thread>
#include <vector>

class Image;

class BradleyAlgorithm {
public:
    void Run(Image& image, int invWindowSize = DefaultInvWindowSize,
            double threshold = DefaultThreshold);

    static constexpr int DefaultInvWindowSize = 16;
    static constexpr double DefaultThreshold = 0.15;

private:
    std::vector<std::vector<int64_t>> integralImage;

    void computeIntegralImage(const Image& image);
    int64_t getSum(int hBegin, int wBegin, int hEnd, int wEnd) const;
};
