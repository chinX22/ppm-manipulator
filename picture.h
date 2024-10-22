#ifndef PICTURE_H
#define PICTURE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Pixel {
    unsigned int red;
    unsigned int green;
    unsigned int blu;
};

class Picture {
    private:
        size_t width;
        size_t height;
        unsigned int maxIntensity;
        vector<Pixel> pixels;

    public:
        Picture();

        const Pixel &getPixel(const size_t, const size_t) const;
        Pixel &getPixel(const size_t, const size_t);
        void setPixel(const size_t, const size_t, const Pixel&);

        void invert();
        void flipY();
        void flipX();
        bool readInput(istream&);
        void writeOutput(ostream&);
};

#endif
