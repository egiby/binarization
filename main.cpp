#include <iostream>
#include <Magick++.h>

#include <unistd.h>

#include "image/Image.h"
#include "algorithms/BradleyBinarisationAlgorithm.h"

using std::cout;

int binarize(const std::string &infile, const std::string &outfile, const std::string &format) {
    auto image = ImageLink(infile, format);

    BradleyBinarisationAlgorithm algo = BradleyBinarisationAlgorithm();

    algo.run(image);

    image.write(outfile);
    return image.width() * image.height();
}

void help() {
    std::cout << "Usage: \n"
            "binarization -i=<input file> [-o[=<output file>]] "
            "[-v] [-f=<output image format>] [-h] [-v] or \n"
            "binarization <input file>" << std::endl;

    std::cout << "\nDefaults:\n"
            "-f=PNG\n"
            "-o=\"result.png\"\n"
            "" << std::endl;
}

int main(int argc, char * argv[]) {
    Magick::InitializeMagick(*argv);

    const char options[] = "i:o:f:j:hv";
    int opt(-1);

    std::string infile, outfile, format;
    bool has_help(false), verbose(false);

    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
            case 'i': {
                infile = optarg;
                break;
            }
            case 'o': {
                outfile = optarg;
                break;
            }
            case 'h': {
                has_help = true;
                break;
            }
            case 'f': {
                format = optarg;
                break;
            }
            case 'v': {
                verbose = true;
                break;
            }
            default: {
                help();
                return 0;
            }
        }
    }

    if (has_help || (infile.empty() && argc != 2)) {
        help();
        return 0;
    } else if (infile.empty() && argc == 2) {
        infile = argv[1];
    }

    if (outfile.empty()) {
        outfile = "result.png";
    }

    if (format.empty()) {
        format = "PNG";
    }

    auto start = std::chrono::system_clock::now();
    auto size = binarize(infile, outfile, format);
    auto end = std::chrono::system_clock::now();

    if (verbose) {
        auto duration = std::chrono::duration<double>(end - start).count();
        cout << duration << "s" << std::endl;
        cout << "Speed: " << size / duration / 1e6 << " MPix/s" << std::endl;
    }

    return 0;
}