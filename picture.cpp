#include "picture.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

Picture::Picture(){
    width = 0;
    height = 0;
    maxIntensity = 0;
}

// This function inverts the colors of the picture, changing the current
// intensity of each pixel by subtracting it from the max intensity.
void Picture::invert(){
    for (unsigned long i = 0; i < pixels.size(); i++){
        pixels[i].red = maxIntensity-pixels[i].red;
        pixels[i].green = maxIntensity-pixels[i].green;
        pixels[i].blu = maxIntensity-pixels[i].blu;
    }
}

// This function flips the picture over the y-axis, it does this by setting
// the position of one pixel to its mirror on the y-axis and vice-versa.
void Picture::flipY(){
    for (size_t i = 0; i < (width/2); i++){

        for (size_t j = 0; j < height; j++){
            Pixel pix;
            pix = getPixel(j, width -(1+i));

            setPixel(j, width- (1 + i), getPixel(j, i));
            setPixel(j, i, pix);

        }
    }
}
// This function flips the picture over the x-axis through the same mechanism
// as flipY.
void Picture::flipX(){
    for (size_t i = 0; i < (height/2); i++){
        for (size_t j = 0; j < width; j++){
            Pixel pix;
            pix = getPixel(height -(1+i),j);
            setPixel(height - (1 + i), j, getPixel(i, j));
            setPixel(i, j, pix);
        }
    }
}

// This returns the index of pixel with the given coordinates.
const Pixel& Picture::getPixel(const size_t row, const size_t column) const{
    int index = (row * width) + column;
    return pixels[index];

}

// This does the same except allows the pixel to be modified.
Pixel& Picture::getPixel(const size_t row, const size_t column){
    int index = (row * width) + column;
    return pixels[index];
}

// This sets a pixel at the given coordinates.
void Picture::setPixel(const size_t row, const size_t column, const Pixel &pixel){
    getPixel(row, column) = pixel;
}
// This outputs the vector of pixels as its RGB components.
void Picture::writeOutput(ostream &out){
    out << "P3" << endl << width << " " << height << endl << maxIntensity << endl;
    for (unsigned long i = 0; i < pixels.size(); i++){
        out << pixels[i].red << " ";
        out << pixels[i].green << " ";
        out << pixels[i].blu << endl;
    }
}

// This function takes the input and creates a vector of pixels with it.
bool Picture::readInput(istream &in) {
    string line;
    stringstream in_without_comments;
    in >> line;
    // This if statements checks if the required P3 header is there.
    if (line != "P3"){
        cerr << "Error: invalid header" << endl;
        exit(1);
    }

    // This while loop and if statement removes any non-pixel input such as comments.
    while(getline(in, line)){
        if (line[0] != '#'){
            in_without_comments << line << "\n";
        }
    }

    // This takes the inital settings for the picture from the input and
    // resizes the vector.
    in_without_comments >> width >> height >> maxIntensity;
    unsigned long num = width * height;
    pixels.resize(num);

    // This for loop takes the RGB values for each pixel and makes a pixel
    // object and adds it to the vector.
    for (unsigned long i = 0; i < num; i++){
        unsigned int r;
        unsigned int g;
        unsigned int b;
        in_without_comments >> r >> g >> b;

        // The "Overdrive" bool lets the code know if the given value is greater than
        // the given max intensity and then sets the value to the max intensity.
        bool redOverdrive = (r > maxIntensity);
        bool greenOverdrive = (g > maxIntensity);
        bool blueOverdrive = (b > maxIntensity);
        if(redOverdrive){
            cerr << "Warning: red channel " << r <<" exceeded max intensity " << maxIntensity << endl;
            r = maxIntensity;
        }
        if(greenOverdrive){
            cerr << "Warning: green channel " << g <<" exceeded max intensity " << maxIntensity << endl;
            g = maxIntensity;
        }
        if(blueOverdrive){
            cerr << "Warning: blue channel " << b <<" exceeded max intensity " << maxIntensity << endl;
            b = maxIntensity;
        }
        Pixel px = Pixel();
        px.red = r;
        px.green = g;
        px.blu = b;
        pixels[i] = px;

    }

    return true;
}
