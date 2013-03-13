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
        pixels = new RGBQUAD[ih.biWidth*ih.biHeight];
        int pad = ih.biWidth%4;
        char * dump[pad*ih.biHeight];
        for (RGBQUAD * h = pixels;h!=pixels+ih.biWidth*ih.biHeight;h+=(ih.biWidth)) {
        	for (RGBQUAD * i = h; i!=h+(ih.biWidth);++i) {
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
        	fread(&dump,pad,1,file);
        }
        fclose(file);
    }
}


Grid Bmp_Reader::get_grid(Boundary b,double l,double r, double vals) {
	grid = Grid(ih.biWidth-1,ih.biHeight-1);
	grid.set_flow(l,r);
	matrix g = grid.get_values();
	matrix mat;
	Value boundaryVal,val;
	val.value = 0;
	val.accessible = true;
	val.boundary = false;
	val.flag = 0;
	boundaryVal.boundary = true;
    if (b!=accessible) {boundaryVal.accessible = true;}
    else {boundaryVal.accessible = false;}
	if (b==conductor){ boundaryVal.flag = 1; }
	else {boundaryVal.flag = 0;}
	std::vector<Value> row;
	for (RGBQUAD * h = pixels;h!=pixels+ih.biWidth*ih.biHeight;h+=(ih.biWidth)) {
		row.clear();
		for (RGBQUAD * i = h; i!=h+(ih.biWidth);++i) {
			if ( (ih.biBitCount>8 && ((*i).rgbBlue < 0xee || (*i).rgbGreen < 0xee || (*i).rgbBlue < 0xee || (ih.biBitCount==32 && (*i).rgbReserved < 0xee)))
					|| (ih.biBitCount==8 && (*i).rgbReserved < 0xee) ) {
				row.push_back(boundaryVal);
			}
			else {
				row.push_back(val);
			}
		}
		mat.push_back(row);
	}
	//std::cout << mat.size() << " " << mat[0].size() << " now grid " << g.size() <<  "    " << g[0].size() << std::endl;

	for (int x = 1; x < g.size()-1; x++) {
		for (int y = 1; y < g[0].size()-1; y++) {
			if (mat[x][y].boundary==true) {
				g[x][y].boundary = true;
				if(b!=conductor)g[x][y].value = vals;
			}
            if (mat[x][y].flag==1) {
                g[x][y].flag = 1;
            }
            if (mat[x][y].accessible==false) {
                g[x][y].accessible = false;
            }
        }
    }
    //int check = 0;
	if (b==conductor) {
        double avvalue = grid.get_average_value_safe(g);
        //std::cout << avvalue << std::endl;
        for (int x = 1; x < g.size()-1; x++) {
            for (int y = 1; y < g[0].size()-1; y++) {
                if(g[x][y].flag == 1){
                    //std::cout << check << std::endl;
                    //check++;
                    g[x][y].value = avvalue;
                    g[x][y].flag = 0;
                }
            }
        }
	}


	grid.set_values(g);
//	grid.recalculate_matrices(ih.biWidth,ih.biHeight);
	return grid;
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

