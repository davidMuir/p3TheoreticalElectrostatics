/*
 * BmpReader.cpp
 *
 *  Created on: 21 Feb 2013
 *      Author: david
 */

#include "BmpReader.h"

Bmp_Reader::Bmp_Reader(std::string filename) {
	FILE *file = fopen(filename.c_str(),"rb");
    if (file) {
    	fread(&fh,sizeof(BITMAPFILEHEADER),1,file);
    	fread(&ih,sizeof(BITMAPINFOHEADER),1,file);
    	fseek(file,fh.bfOffBits,SEEK_SET);
        std::cout << fh.bfType << " " << fh.bfSize << " " << fh.bfReserved1 << fh.bfReserved2 << " " << fh.bfOffBits << std::endl;
        std::cout << ih.biSize << " " << ih.biWidth << " " << ih.biHeight << " " << ih.biPlanes << " " << ih.biBitCount
        		<< " "<< ih.biCompression << " " << ih.biSizeImage << " " << ih.biXPelsPerMeter << " " << ih.biYPelsPerMeter
        		<< " " << ih.biClrUsed<< " " << ih.biClrImportant << std::endl;
        pixels = new RGBQUAD[ih.biWidth*ih.biHeight];
        for (RGBQUAD * i = pixels; i!=pixels+ih.biWidth*ih.biHeight;++i) {
        	if (ih.biBitCount==8) {
        		fread( &(*i).rgbReserved, 1, 1, file );
        	}
        	else if (ih.biBitCount==24) {
        		fread( &(*i), 3, 1, file );
        	}
        	else if(ih.biBitCount==32) {
        		fread( &(*i),4, 1, file );
        	}
        }
        fclose(file);
    }
}

unsigned int Bmp_Reader::get_height() {
	return ih.biHeight;
}

unsigned int Bmp_Reader::get_width() {
	return ih.biWidth;
}

unsigned int Bmp_Reader::get_size() {
	return ih.biWidth*ih.biHeight;
}

RGBQUAD * Bmp_Reader::get_pixels() {
	return pixels;
}

Bmp_Reader::~Bmp_Reader() {
	delete [] pixels;
}

