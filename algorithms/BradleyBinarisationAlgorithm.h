#ifndef BINARISATION_BRADLEYBINARISATIONALGORITHM_H
#define BINARISATION_BRADLEYBINARISATIONALGORITHM_H

#include <thread>
#include <vector>

#include "IAlgorithm.h"

using std::vector;

class BradleyBinarisationAlgorithm : public IBinarisationAlgorithm {
    int get_num_threads() const {
#ifndef _DEBUG
        auto number_threads = std::thread::hardware_concurrency() + 1;
#else
        ui32 number_threads = 1; // debug mode
#endif
        return number_threads;
    }

    vector<vector<long long> > part_sums;

    void calc_part_sums(const ImageLink &image) {
        part_sums.clear();
        part_sums.resize(image.height() + 1, vector<long long>(image.width() + 1));

        for (uint32_t h = 1; h < part_sums.size(); ++h) {
            for (uint32_t w = 1; w < part_sums[h].size(); ++w) {
                part_sums[h][w] = (long long) image.get_intensity(h - 1, w - 1) + part_sums[h - 1][w] + part_sums[h][w - 1]
                                  - part_sums[h - 1][w - 1];
            }
        }
    }

    long long get_sum(int h_l, int w_l, int h_r, int w_r) const {
        return part_sums[h_r][w_r] - part_sums[h_l][w_r] - part_sums[h_r][w_l] + part_sums[h_l][w_l];
    }

public:
    void run(ImageLink &image) {
        run(image, 16, 0.15);
    }

    void run(ImageLink &image, int d_coef_i, double t_coef) {
        calc_part_sums(image);
        int d = image.width() / d_coef_i;

    #pragma omp parallel num_threads(get_num_threads())
        for (int h = 0; h < image.height(); ++h) {
            for (int w = 0; w < image.width(); ++w) {
                int h_l = h - d >= 0 ? h - d : 0;
                int h_r = h + d <= image.height() ? h + d : image.height();

                int w_l = w - d >= 0 ? w - d : 0;
                int w_r = w + d <= image.width() ? w + d : image.width();

                long long count = (h_r - h_l) * (w_r - w_l);

                long long border = (long long)(get_sum(h_l, w_l, h_r, w_r) * (1 - t_coef));

                if (image.get_intensity(h, w) * count < border) {
                    image[h][w] = Magick::ColorGray("black");
                } else {
                    image[h][w] = Magick::ColorGray("white");
                }
            }
        }
    }
};

#endif //BINARISATION_BRADLEYBINARISATIONALGORITHM_H
