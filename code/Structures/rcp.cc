#include <iostream>
#include <stdlib.h>   
#include <iomanip>
#include <math.h>    // for sin() and cos()


	///Regular Convex Polygon
	case RCP:{ 
		int xc=x; //x centre point
        	int yc=y; // y centre point
        	double R=r;// Radius(of verices)
        	int N=z;//number of side/vertices.
       		double pi = 3.14159265;

        	if (x - r < 0 || x + r > values.size() - 1 || y - r < 0
		|| y + r > values[0].size() - 1)
		cout << "Out of range." << endl;
		else {
			double phi= pi*(1-2/N)/2; // This an angle in a triangle that is formed that scans out theta=0 to theta= 360/N
			for (int xs = x - r; xs <= x + r; xs++) { // ie from 1 vertice to another.
				for (int ys = y - r; ys <= y + r; ys++) {
				if (xs==xc && ys<=yc){ // for cases where gradient becomes infinite (ie atan(double (ys-yc)/(xs-xc)) is 
					double actualtheta=pi/2;// undefined because xs=xc. In this case i just set theta to pi/2 
					double correctedtheta=actualtheta;// or 3*pi/2 depending on wherether ys-yc is positive or not.
					while (correctedtheta >= 2*pi/N){
						correctedtheta=correctedtheta-2*pi/N; // This is used to make angle scanned out begin 
					}		// at 0 when we start at a new vertice.
					double a=fabs(R*sin(phi)/sin(double (pi-correctedtheta-phi)));
					if (sqrt((xs-xc)^2+(ys-yc)^2) < a) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}}
				if (xs==xc && ys>yc){
					double actualtheta=3*pi/2;
					double correctedtheta=actualtheta;
					while (correctedtheta >= 2*pi/N){
						correctedtheta=correctedtheta-2*pi/N;
					}		
					double a=fabs(R*sin(phi)/sin(double (pi-correctedtheta-phi)));
					if (sqrt((xs-xc)^2+(ys-yc)^2) < a) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;	
					}}
				if (xs !=xc) {// for cases where xs isnt equal arctan can be used to find angle.
                        		double actualtheta= atan(double (ys-yc)/(xs-xc));
					double correctedtheta=actualtheta;
					while (correctedtheta >= 2*pi/N){
						correctedtheta=correctedtheta-2*pi/N;
					}		
					double a=fabs(R*sin(phi)/sin(double (pi-correctedtheta-phi)));
					if (sqrt((xs-xc)^2+(ys-yc)^2) < a) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}}
				}
			}
		}
		break;
	}

	///Regular Convex Polygon
	case RCP:{ 
		int xc=x1;
        	int yc=y1;
        	double R=r;
        	int N=x2;
       		double pi = 3.14159265;

        	if (x1 - r < 0 || x1 + r > values.size() - 1 || y1 - r < 0
		|| y1 + r > values[0].size() - 1)
		cout << "Out of range." << endl;
		else {
			double phi= pi*(1-2/N)/2;
			for (int xs = x1 - r; xs <= x1 + r; xs++) {
				for (int ys = y1 - r; ys <= y1 + r; ys++) {
				if (xs==xc && ys<=yc){
					double actualtheta=pi/2;
					double correctedtheta=actualtheta;
					while (correctedtheta >= 2*pi/N){
						correctedtheta=correctedtheta-2*pi/N;
					}		
					double a=fabs(R*sin(phi)/sin(double (pi-correctedtheta-phi)));
					if (sqrt((xs-xc)^2+(ys-yc)^2) < a) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}}
				if (xs==xc && ys>yc){
					double actualtheta=3*pi/2;
					double correctedtheta=actualtheta;
					while (correctedtheta >= 2*pi/N){
						correctedtheta=correctedtheta-2*pi/N;
					}		
					double a=fabs(R*sin(phi)/sin(double (pi-correctedtheta-phi)));
					if (sqrt((xs-xc)^2+(ys-yc)^2) < a) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;	
					}}
				if (xs !=xc) {
                        		double actualtheta= atan(double (ys-yc)/(xs-xc));
					double correctedtheta=actualtheta;
					while (correctedtheta >= 2*pi/N){
						correctedtheta=correctedtheta-2*pi/N;
					}		
					double a=fabs(R*sin(phi)/sin(double (pi-correctedtheta-phi)));
					if (sqrt((xs-xc)^2+(ys-yc)^2) < a) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}}
				}
			}
		}
		break;
	}
