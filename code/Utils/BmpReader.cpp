/*
 * BmpReader.cpp
 *
 *  Created on: 21 Feb 2013
 *      Author: david
 */

#include "BmpReader.h"

Bmp_Reader::Bmp_Reader(std::string filename) {
    std::ifstream file(filename,std::ios::in | std::ios::binary);

    if (file) {
        file.seekg(0,std::ios::end);
        auto length = file.tellg();
        file.seekg(0,std::ios::beg);
        char * buffer = new char[length];

        file.read(buffer,length);
        file.close();

        memcpy(&fh,&buffer,sizeof(BITMAPFILEHEADER));
        memcpy(&fh,&buffer+sizeof(BITMAPFILEHEADER),sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER));
        std::cout << fh.bfType << " " << fh.bfSize << " " << fh.bfReserved1 << fh.bfReserved2 << " " << fh.bfOffBits << std::endl;
        std::cout << ih.biSize << " " << ih.biWidth << " " << ih.biHeight << " " << ih.biPlanes << " " << ih.biBitCount
        		<< " "<< ih.biCompression << " " << ih.biSizeImage << " " << ih.biXPelsPerMeter << " " << ih.biYPelsPerMeter
        		<< " " << ih.biClrUsed<< " " << ih.biClrImportant << std::endl;

        for (char *i = buffer+54;i!=buffer+length;i++) {
			RGBQUAD pixel;
        	if (ih.biBitCount==8) {
        		pixel.rgbReserved = *i;
        	}
        	else if (ih.biBitCount==24) {
        		pixel.rgbBlue = *i;
        		pixel.rgbGreen = *(i+1);
        		pixel.rgbRed = *(i+2);
        		std::advance(i,2);
        	}
        	else if(ih.biBitCount==32) {
        		pixel.rgbBlue = *i;
        		pixel.rgbGreen = *i+1;
        		pixel.rgbRed = *i+2;
        		pixel.rgbReserved = *i+3;
        		std::advance(i,3);
        	}
        	pixels.push_back(pixel);
        }
        delete [] buffer;


    }

}

unsigned int Bmp_Reader::get_height() {
	return ih.biHeight;
}

unsigned int Bmp_Reader::get_width() {
	return ih.biWidth;
}

unsigned int Bmp_Reader::get_size() {
	return ih.biSizeImage;
}

std::vector<RGBQUAD> Bmp_Reader::get_pixels() {
	return pixels;
}

Bmp_Reader::~Bmp_Reader() {}

