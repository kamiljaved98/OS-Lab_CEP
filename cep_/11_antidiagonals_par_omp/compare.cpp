#include <CImg.h>
#include <iostream>
#include <cstdlib>

using cimg_library::CImg;
using std::cout;
using std::cerr;
using std::endl;

const unsigned int THRESHOLD = 16;


int main(int argc, char *argv[]) {
	long long unsigned int pixelsAboveThreshold = 0;
	
	if ( argc != 3 ) {
		cerr << "Usage: " << argv[0] << " <image1> <image2>" << endl;
		return 1;
	}

	CImg< unsigned char > imageOne = CImg< unsigned char >(argv[1]);
	CImg< unsigned char > imageTwo = CImg< unsigned char >(argv[2]);

	if ( imageOne.width() != imageTwo.width() ) {
		cerr << "The two images have different width." << endl;
		return 1;
	}
	if ( imageOne.height() != imageTwo.height() ) {
		cerr << "The two images have different height." << endl;
		return 1;
	}
	if ( imageOne.spectrum() != imageTwo.spectrum() ) {
		cerr << "The two images have different spectrum." << endl;
		return 1;
	}

	CImg< unsigned char > differenceImage = CImg< unsigned char >(imageOne.width(), imageOne.height(), 1, imageOne.spectrum());

	for ( int y = 0; y < differenceImage.height(); y++ ) {
		for ( int x = 0; x < differenceImage.width(); x++ ) {
			for ( int c = 0; c < differenceImage.spectrum(); c++ ) {
				differenceImage(x, y, 0, c) = abs(imageOne(x, y, 0, c) - imageTwo(x, y, 0, c));
				
				// cout << abs(imageOne(x, y, 0, c) - imageTwo(x, y, 0, c)) << endl;

				if ( differenceImage(x, y, 0, c) > THRESHOLD ) {
					pixelsAboveThreshold++;
				}
			}
		}
	}

	differenceImage.save("./diff.bmp");

	cout << "Pixels above threshold: " << pixelsAboveThreshold << " (" << static_cast< int >((100.0f * pixelsAboveThreshold) / differenceImage.size()) << "\%)." << endl;

	return 0;
}

