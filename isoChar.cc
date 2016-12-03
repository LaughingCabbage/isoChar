#include <iostream>
#include <fstream>
#include <vector>
#include "pixel.h"
#include "isoChar.h"

using namespace std;

isoChar::isoChar(){
	size_x = 0;
	size_y = 0;
}
 
void isoChar::drawBox(vector<vector<char> >& img_matrix,
				 int x_min, int y_min, int x_max, int y_max){
	
	y_min--; //avoid writing on characters
	x_min--;
	y_max++;
	x_max++;
	
	//draw top of box
	for(int i = x_min; i <= x_max; i++){
		img_matrix[y_min][i] = '1';
	} 
	
	//draw bottom of box
	for(int i = x_min; i <= x_max; i++){
		img_matrix[y_max][i] = '1';
	}
	
	//draw left of box
	for(int i = y_min; i <= y_max; i++){
		img_matrix[i][x_min] = '1';
	}
	
	//draw right of box
	for(int i = y_min; i <= y_max; i++){
		img_matrix[i][x_max] = '1';
	}

}

bool isoChar::load(char *file_name){
		//lets try to oepn the test file
	ifstream ifs(file_name);
	if(ifs.fail()){
		cout << "failed to open test file...\n";
		return 1;
	}
	
	getline(ifs, type);
	cout << "file type: " << type << endl;
	getline(ifs,source);
	cout <<"file source: " << source << endl;
	ifs >> size_x >> size_y;
	cout << "size_x: " << size_x << "\nsize_y: " << size_y << endl;
	
	//cout<<"making matrix\n";
	//need to create image matrix.
	img_matrix.resize(size_y);
	for(int i = 0; i < size_y; i++){
		img_matrix[i].resize(size_x);
	}
	
	//read in matrix
	for(int i = size_y-1; i >= 0; i--){
		for(int j = size_x-1; j >= 0; j--){
			ifs >> img_matrix[i][j];
		}
	
	}
	ifs.close(); //close image stream
	
	return 0;

}

void isoChar::trace(Pixel& start, int& x_next, int& y_next){

	
	//create a vector to store boundary pixels
	vector<Pixel> boundary;
	
	 
	//need to begin tracing boundary
	int x = start.x-1;
	int y = start.y;
	//start by checking next column for black pixel
	direction current_direction = East;
	bool done = false;
	while(!done){
		switch(current_direction){
			case East:
				if(x < size_x){ //check boundary
					x = x+1; //visit pixel
					if(img_matrix[y][x] == '1'){
						current_direction = North;
						Pixel temp(x,y);
						boundary.push_back(temp);
					}else{
						current_direction = South;
					}
				}
			break;
			
			case North:
				if(y > 0){//check boundary
					y = y-1;
					if(img_matrix[y][x] == '1'){
						current_direction = West;
						Pixel temp(x,y);
						boundary.push_back(temp);
					}else{
						current_direction = East;
					}
				}
						
			break;
			
			case West:
				if(x > 0){
					x = x-1;
					if(img_matrix[y][x] == '1'){
						current_direction = South;
						Pixel temp(x,y);
						boundary.push_back(temp);
					}else{
						current_direction = North;
					}
				}
			break;
			
			case South:
				if(y < size_y){
					y = y+1;
					if(img_matrix[y][x] == '1'){
						current_direction = East;
						Pixel temp(x,y);
						boundary.push_back(temp);
					}else{
						current_direction = West;
					}
				}
			break;
		}
		if(boundary.size() > 1){ //check if pixel is equal to start pixel. 
			if(start.isEqual(boundary[boundary.size()-1])){
				done = true;
			}
		}
	}
	
	letter_contours.push_back(boundary); //add to boundary vectors
	
	
	// find box edges.
	int x_min = size_x;
	int x_max = 0;
	int y_min = size_y;
	int y_max = 0;
	
	for(int i = 0; i < boundary.size();i++){
		if(boundary[i].x < x_min){
			x_min = boundary[i].x;
		}
		if(boundary[i].y < y_min){
			y_min = boundary[i].y;
		}
		if(boundary[i].x > x_max){
			x_max = boundary[i].x;
		}
		if(boundary[i].y > y_max){
			y_max = boundary[i].y;
		}
	}
	
	cout <<"xmin: " << x_min << " ymin: " << y_min
		<<" x_max: " << x_max << " y_max " << y_max << endl;
		
	//begin drawing box.
	drawBox(img_matrix, x_min, y_min, x_max, y_max);
	
	x_next = x_max+2;
	y_next = y_min + (y_max-y_min)/2;
	
	//give tracer next location to start.
	
}

int isoChar::getStart(Pixel& start){
	if((size_x == 0 ) || (start.x > size_x) || (size_y == 0) || start.y > size_y){
				cout << "get start error\n";
				return 1;
			}
		
		bool found = 0;
		for(int i = start.y; i < size_y && !found; i++){
			for(int j = start.x; j < size_x && !found; j++){
				if(i == size_y-1){
					start.x = 0;
					start.y = 
				}
				if(img_matrix[i][j] == '1'){
					start.x = j;
					start.y = i;
					found = true;
					cout << "start pixel found at x: "
						 << start.x << " y: " << start.y << endl;
				}
			}
		}
	return 0;
}

void isoChar::printMatrix(){
	//printing the matrix
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			cout << img_matrix[i][j];
		}
		cout << endl;
	}
}







