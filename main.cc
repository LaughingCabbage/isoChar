#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "isoChar.h"
#include "pixel.h"

using namespace std;

#define TOL 0.9

//pixel structure to store x and y locations of
//boundary values.

void checkLeft(move& mv, direction& dir);
void checkRight(move& mv, direction& dir);

//static string type, source;



int main(int argc, char **argv){
	cout << "isoChar -- Kevin Gentile\n\n";	
	if(argc < 2){
		cout << "not enough arguments\n";
		return 1;
	}
	cout << argc << endl;
	for(int i = 0; i < argc; ++i){
		cout << argv[i] << endl;
	}
		
	
	isoChar iso; //START
		
	//load image	
	if(iso.load(argv[1])){
		cout << "fail\n";
		return 0;
	}
	
	iso.printMatrix(); //print initial image.
	
	while(1){
		Pixel seed(0,0);
		if(!iso.getStart(seed))
			break;
		cout<<"seed x " << seed.x << " y " << seed.y << endl;
		iso.trace(seed);
	}
	
	iso.drawBoxes();
	
	
	cout << "\nsize contour_boxes: " << iso.contour_boxes.size() << endl;
	
	/*
	int timeout = iso.size_y;
	int i = 4;
	while(i > 0){	
		Pixel pixel_next(x_next,y_next);
		if(iso.getStart(pixel_next)){
			cout << " failed to get start pixel\n";
			
		}else{
			timeout = iso.size_y;
			iso.trace(pixel_next, x_next, y_next);
			cout << "x_next: " << x_next << " y_next: " << y_next << endl;
		}
		i--;
	}
	
	*/
	
	iso.printMatrix();
	
	
	
	
	

}
