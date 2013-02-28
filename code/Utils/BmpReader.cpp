/*
 * BmpReader.cpp
 *
 *  Created on: 21 Feb 2013
 *      Author: david
 */

#include "BmpReader.h"

Bmp_Reader::Bmp_Reader(std::string filename) {
	FILE* file = fopen(filename.c_str(), "rb");

	if(file != NULL) {
		fread(&fh, sizeof(BITMAPFILEHEADER), 1, file);
		fread(&ih, sizeof(BITMAPINFOHEADER), 1, file);
		pixels = new RGBQUAD[ih.biSizeImage];
		fread(pixels,sizeof(RGBQUAD),ih.biSizeImage,file);
		fclose(file);
	}

}

unsigned int Bmp_Reader::get_height() {
	return ih.biHeight;
}

unsigned int Bmp_Reader::get_width() {
	return ih.biWidth;
}

RGBQUAD *Bmp_Reader::get_pixels() {
	return pixels;
}

unsigned int Bmp_Reader::get_size() {
	return ih.biSizeImage;
}

Bmp_Reader::~Bmp_Reader() {}

