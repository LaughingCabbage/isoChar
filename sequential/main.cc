#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "isoChar.h"
#include "pixel.h"

using namespace std;


int main(int argc, char **argv){
	cout << "isoChar -- by Kevin Gentile\n\n";	
	if(argc < 2){
		cout << "not enough arguments\n";
		return 1;
	}

	cout << "Starting isoChar\n";
	isoChar iso; //START
		
	//load image
	cout << "Loading Image " << argv[1] << "...\n";	
	if(iso.load(argv[1])){
		cout << "loading fail...\n";
		return 0;
	}
	
	cout << "Begin Tracing...\n";
	while(1){
		Pixel seed(0,0);
		if(!iso.getStart(seed))
			break;
		iso.trace(seed);
	}
	
	cout << "Drawing Boxes...\n";
	iso.drawBoxes();
	
	cerr << "Total Boxes Found: " << iso.contour_boxes.size() << endl;
	
	cout << "Writing to File...\n";
	iso.write(argv[1]);	
	
	cout << "done...\n";
	return 0;

}
