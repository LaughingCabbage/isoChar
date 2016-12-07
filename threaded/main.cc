#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <pthread.h>
#include "isoChar.h"
#include "pixel.h"

using namespace std;

isoChar iso;

void *getContours(void *ptr);


int main(int argc, char **argv){
	cout << "isoChar -- by Kevin Gentile\n\n";	
	if(argc < 2){
		cout << "not enough arguments\n";
		return 1;
	}

	cout << "Starting isoChar\n";
		
	//load image
	cout << "Loading Image " << argv[1] << "...\n";	
	if(iso.load(argv[1])){
		cout << "loading fail...\n";
		return 0;
	}
	
	pthread_t traceThread, drawThread;
	int traceID;
	cout << "Begin Tracing...\n";
	traceID = pthread_create(&traceThread, NULL, &getContours, NULL);
	if(traceID){
		cout << "trace thread creation failed\n";
		return 1;
	}
	pthread_join(traceThread,NULL);	
	
	cout << "Drawing Boxes...\n";
	iso.drawBoxes();
	
	cerr << "Total Boxes Found: " << iso.contour_boxes.size() << endl;
	
	cout << "Writing to File...\n";
	iso.write(argv[1]);	
	
	cout << "done...\n";
	return 0;

}

void *getContours(void *ptr){
	cout << "enter contour thread function\n";
	while(1){
		Pixel seed(0,0);
		if(!iso.getStart(seed))
			break;
		iso.trace(seed);
	}
	
	return NULL;
}
