#include <image/Image.h>
#include <algorithms/BradleyAlgorithm.h>

#include <iostream>

#include <unistd.h>

#include <vips/vips8>

using std::cout;

void Binarize(Image* image, int invWindowSize, double threshold) {
    BradleyAlgorithm algorithm;
    algorithm.Run(*image, invWindowSize, threshold);
}

struct Params {
    std::string InputFile;
    std::string OutputFile;

    int InvWindowSize = 128;
    double Threshold = 0.12;

    bool Verbose = false;
    bool HasHelp = false;
    bool OneBitImage = false;
};

void PrintHelp() {
    std::cout << "Usage: \n"
                 "binarization -i=<input file> [-o[=<output file>]]\n"
                 "\t[-d=<relative inverted window size>] [-t=<threshold>]\n"
                 "\t[-v] [-h] [-c] or \n"
                 "\tbinarization <input file>" << std::endl;

    std::cout << "\nDefaults:\n"
                 "\t-o=\"result.tiff\"\n"
                 "\t-d=128\n"
                 "\t-t=0.12\n"
                 "" << std::endl;

    std::exit(0);
}

Params ParseCommandLine(int argc, char* argv[]) {
    Params params;
    params.OutputFile = "result.tiff";


    const char options[] = "i:o:d:t:hvc";
    int opt(-1);
    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
            case 'i': {
                params.InputFile = optarg;
                break;
            }
            case 'o': {
                params.OutputFile = optarg;
                break;
            }
            case 'd': {
                params.InvWindowSize = atoi(optarg);
                break;
            }
            case 't': {
                params.Threshold = atof(optarg);
                break;
            }
            case 'h': {
                params.HasHelp = true;
                break;
            }
            case 'v': {
                params.Verbose = true;
                break;
            }
            case 'c': {
                params.OneBitImage = true;
                break;
            }
            default: {
                PrintHelp();
            }
        }
    }

    if (params.HasHelp || (params.InputFile.empty() && argc != 2)) {
        PrintHelp();
    } else if (params.InputFile.empty() && argc == 2) {
        params.InputFile = argv[1];
    }

    return params;
}

int main(int argc, char* argv[]) {
    if (VIPS_INIT(argv[0]))
        vips_error_exit(nullptr);

    Params params = ParseCommandLine(argc, argv);

    Image image(params.InputFile);
    auto start = std::chrono::system_clock::now();
    Binarize(&image, params.InvWindowSize, params.Threshold);
    auto end = std::chrono::system_clock::now();

    if (params.OneBitImage) {
        image.WriteOneBitImage(params.OutputFile);
    } else {
        image.Write(params.OutputFile);
    }

    if (params.Verbose) {
        int size = image.Height() * image.Width();

        auto duration = std::chrono::duration<double>(end - start).count();
        cout << duration << "s" << std::endl;
        cout << "Speed: " << size / duration / 1e6 << " MPix/s" << std::endl;
    }

    return 0;
}