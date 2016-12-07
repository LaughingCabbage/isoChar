#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "pixel.h"
#include "isoChar.h"

#define PADDING 2 //padding of pixel box.

using namespace std;

isoChar::isoChar(){
	size_x = 0;
	size_y = 0;
}
 
void isoChar::drawBoxes(){
	if(contour_boxes.empty())
		return;
	
	for(int z = 0; z < contour_boxes.size(); z++){	
		//draw top of box
		for(int i = contour_boxes[z].x_min; i <= contour_boxes[z].x_max; i++){
			img_matrix[contour_boxes[z].y_min][i] = '1';
		} 
	
		//draw bottom of box
		for(int i = contour_boxes[z].x_min; i <= contour_boxes[z].x_max; i++){
			img_matrix[contour_boxes[z].y_max][i] = '1';
		}
	
		//draw left of box
		for(int i = contour_boxes[z].y_min; i <= contour_boxes[z].y_max; i++){
			img_matrix[i][contour_boxes[z].x_min] = '1';
		}
	
		//draw right of box
		for(int i = contour_boxes[z].y_min; i <= contour_boxes[z].y_max; i++){
			img_matrix[i][contour_boxes[z].x_max] = '1';
		}
	
	}

}

bool isoChar::load(char *file_name){
		//lets try to oepn the test file
	ifstream ifs(file_name);
	if(ifs.fail()){
		cout << "open file failed\n";
		return 1;
	}
	
	getline(ifs, type);
	getline(ifs,source);
	ifs >> size_x >> size_y;

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

void isoChar::write(char *file_name){
	
	//lets make output file names different.
	string file = file_name;
	string outType = "_iso";
	int i = 0;
	for(; i < file.length(); i++){ //find period
		if(file[i] == '.')
			break;
	}
	file.insert(i,outType);	
	
	ofstream ofs(file.c_str());
	if(ofs.fail()){
		cout << "output fial stream fail\n";
	}
	
	ofs << type << endl << source << endl << size_x << " " << size_y << endl;
	
	//read in matrix
	for(int i = size_y-1; i >= 0; i--){
		for(int j = size_x-1; j >= 0; j--){
			ofs << img_matrix[i][j];
		}
		ofs << endl;
	}
	
	ofs.close();
}

void isoChar::trace(Pixel& start){
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
	}//END WHILE	
	
	
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
	
	y_min = y_min - PADDING; //box recatangle padding.
	x_min = x_min - PADDING;
	y_max = y_max + PADDING;
	x_max = x_max + PADDING;
	
	Box contour_box(x_min, x_max, y_min, y_max);
	contour_boxes.push_back(contour_box); //add contour box
	
}

int isoChar::getStart(Pixel& start){
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			if(img_matrix[i][j] == '1'){
				int index = inBoxes(j,i);
			 	if(index != -1){ //pixel is in a box. skip over it
					j = j + contour_boxes[index].width();
				}else{
					start.x = j;
					start.y = i;
					return 1;	
				}
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

int isoChar::inBoxes(int x, int y){ //return index to box
	if(contour_boxes.empty()){
		return -1;
	}

	for(int i = 0; i < contour_boxes.size(); i++){
		if(contour_boxes[i].isIn(x,y)){
			return i;
		}
	}
	
	return -1;
}







