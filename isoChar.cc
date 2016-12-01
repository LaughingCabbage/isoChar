#include <iostream>
#include <fstream>
#include <vector>
#include "Pixel.h"

using namespace std;



//pixel structure to store x and y locations of
//boundary values.


static string type, source;
int size_x = 0;
int size_y = 0;


int main(int argc, char **argv){
	
	if(argc < 2){
		cout << "not enough arguments\n";
		return 1;
	}
	cout << argc << endl;
	for(int i = 0; i < argc; ++i){
		cout << argv[i] << endl;
	}
	
	cout << "isoChar -- Kevin Gentile\n\n";
	//lets try to oepn the test file
	ifstream ifs(argv[1]);
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
	
	
	//need to create image matrix.
	char img_matrix[size_x][size_y];
	
	
	//read in matrix
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			ifs >> img_matrix[i][j];
		}
	
	}

	ifs.close(); //close image stream

	//printing the matrix
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			cout << img_matrix[i][j];
		}
		cout << endl;
	}
	

	//create a vector to store boundary pixels
	vector<Pixel> boundary;
	
	//need to find starting pixel.
	Pixel start;
	bool found = 0;
	for(int i = 0; i < size_y && !found; i++){
		for(int j = 0; j < size_x && !found; j++){
			if(img_matrix[i][j] == '1'){
				start.x = j;
				start.y = i;
				boundary.push_back(start);
			}
		}
	}
	
	//need to begin tracing boundary
	
	int x = start.x;
	int y = start.y;
	enum move {Up, Right, Left, Down};
	//start by checking next column for black pixel
	move current_move = Right;
	bool done = 0;
	while(!done){
		//check if next pixel in row is black, add if it is.
		switch(current_move){
			
			case Right: //check right pixel
				cout<<"right case\n";
				if(x < size_x && img_matrix[y][x+1] == '1'){ //found black
					Pixel temp(x,y);
					boundary.push_back(temp); //add pixel to list
					cout << "\nx: " << x << " y: " << y << endl;
					x = x+1; //continue right
				}else{
					current_move = Down; // found white, switch to down.
				}

			break;	//END RIGHT

			case Down: //check down pixel
				cout <<"down case\n";
				if(y < sixe_y && img_matrix[y+1][x] == '1'){ //found black
					Pixel temp(x,y);
					boundary.push_back(temp); //add pixel to list
					y = y+1; //continue down
				}else{
					current_move = Left;
				}
			break; //END DOWN
			
			case Left: //check left pixel
				cout <<"left case\n"l;
				if(x > 0 && img_matrix[x-1][y] == '1'){ //found black
					Pixel temp(x,y);
					boundary.push_back(temp);
					x = x-1;
				}else{
					current_move = Up;
				}
				
			break; //END LEFT
			
			case Up:
				if(y > 0 && img_matrix[y-1][x] == '1'){ //found black
					Pixel temp(x,y);
					boundary.push_back(temp);
					cout << "\nx: " << x << " y: " << y << endl;
					y = y-1; //continue up
				}else{
					current_move = Right;
				}
			break; // END UP
			
			
			default:
				cout<< "default...\n";
		}
		
	} 
	
	
	return 0;
}




