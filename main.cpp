#include <iostream>
#include <Magick++.h>

#include "image/Image.h"
#include "algorithms/BradleyBinarisationAlgorithm.h"

using std::cout;

int main(int argc, char * argv[]) {
    Magick::InitializeMagick(*argv);

    auto image = ImageLink("data/05.JPG");

    BradleyBinarisationAlgorithm algo = BradleyBinarisationAlgorithm();

    algo.run(image);

    image.write("result.jpg");

    return 0;
}