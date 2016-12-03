#include <iostream>
#include <fstream>
#include <vector>
#include "isoChar.h"
#include "pixel.h"

using namespace std;



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
		
	
	isoChar iso;
		
	//load image	
	if(iso.load(argv[1])){
		cout << "fail\n";
		return 0;
	}
	
	iso.printMatrix();
	
	int x_next = 0;
	int y_next = 0;

	int i = 4;
	while(i > 0){	
		Pixel pixel_next(x_next,y_next);
	
		if(iso.getStart(pixel_next)){
			cout << " failed to get start pixel\n";
			break;
		}


		iso.trace(pixel_next, x_next, y_next);
		i--;
		cout << "x_next: " << x_next << " y_next: " << y_next << endl;
	}
	
	iso.printMatrix();
	
	
	
	
	

}
