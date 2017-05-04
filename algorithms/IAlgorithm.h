#ifndef BINARISATION_IALGORITHM_H
#define BINARISATION_IALGORITHM_H

#include "../image/Image.h"

class IBinarisationAlgorithm {
public:
    virtual void run(ImageLink &image) = 0;
};

#endif
