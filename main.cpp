#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "picture.h"

using namespace std;

int main(int argc, char **argv) {

	// Error checks user arguments.
	if (argc < 3 || argc > 4){
		cerr << "Usage: ./ppm <input file> <output file> [i|x|y]" << endl;
		return 1;
	}

	Picture pic;

	// Checks whether or not to read a command input or file input.
	if (argv[1][0] == '-'){
		pic.readInput(cin);
	} else {
		ifstream fin(argv[1]);
		if(!fin.is_open()){
			cerr << "Unable to open " << argv[1] << "." << endl;
			return 1;
		}
		pic.readInput(fin);
		fin.close();
	}

	// Error checks the output file.
	ofstream fout(argv[2]);
	if(!fout.is_open()){
		cerr << "Unable to open " << argv[2] << "." << endl;
		return 1;
	}

	// Checks if given an acceptable operation.
	if (argc == 4){	
		switch (argv[3][0]){
			case 'i':
				pic.invert();
				break;
			case 'x':
				pic.flipX();
				break;
			case 'y':
				pic.flipY();
				break;
			default:
				cerr << "Unknown operation: " << argv[3][0] << endl;
				return 1;

		}
	}

	if (argv[1][0] == '-'){
		pic.writeOutput(cout);

	} else {
		pic.writeOutput(fout);
	}
	fout.close();
	return 0;
}
