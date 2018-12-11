#include "BradleyAlgorithm.h"

#include <image/Image.h>


void BradleyAlgorithm::Run(Image& image, int invWindowSize, double threshold) {
    computeIntegralImage(image);
    int windowSize = std::min(image.Width(), image.Height()) / invWindowSize;

    for (int h = 0; h < image.Height(); ++h) {
        for (int w = 0; w < image.Width(); ++w) {
            int hBegin = h - windowSize >= 0 ? h - windowSize : 0;
            int hEnd = h + windowSize <= image.Height() ? h + windowSize : image.Height();

            int wBegin = w - windowSize >= 0 ? w - windowSize : 0;
            int wEnd = w + windowSize <= image.Width() ? w + windowSize : image.Width();

            int64_t count = (hEnd - hBegin) * (wEnd - wBegin);

            auto border = static_cast<int64_t>(getSum(hBegin, wBegin, hEnd, wEnd) *
                                               (1 - threshold));

            if (image.GetIntensity(h, w) * count < border) {
                image.SetIntensity(0, h, w);
            } else {
                image.SetIntensity(255, h, w);
            }
        }
    }
}

void BradleyAlgorithm::computeIntegralImage(const Image& image) {
    integralImage = {static_cast<size_t>(image.Height()) + 1,
                     std::vector<int64_t>(image.Width() + 1)};

    for (size_t h = 1; h < integralImage.size(); ++h) {
        for (size_t w = 1; w < integralImage[h].size(); ++w) {
            integralImage[h][w] = static_cast<int64_t>(image.GetIntensity(h - 1, w - 1)) +
                                  integralImage[h - 1][w] + integralImage[h][w - 1]
                                  - integralImage[h - 1][w - 1];
        }
    }
}

int64_t BradleyAlgorithm::getSum(int hBegin, int wBegin, int hEnd, int wEnd) const {
    return integralImage[hEnd][wEnd] - integralImage[hBegin][wEnd] -
           integralImage[hEnd][wBegin] + integralImage[hBegin][wBegin];
}
