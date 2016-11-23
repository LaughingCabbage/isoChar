#include <iostream>
#include <fstream>
#include <vector>


using namespace std;



//pixel structure to store x and y locations of
//boundary values.
typedef struct{
	int x,y;
} pixel;

static string type, source;
int size_x = 0;
int size_y = 0;

template< typename T, size_t N, size_t M >
void printImage( T(&img_matrix)[N][M]){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			cout << img_matrix[i][j];
		}
		cout << endl;
	}
}


int main(int argc, char **argv){
	
	if(argc < 2){
		cout << "not enough arguments\n";
		exit(1);
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
		exit(1);
	}
	
	getline(ifs, type);
	cout << "file type: " << type << endl;
	getline(ifs,source);
	cout <<"file source: " << source << endl;
	ifs >> size_x >> size_y;
	cout << "size_x: " << size_x << "\nsize_y: " << size_y << endl;
	
	
	//need to create image matrix.
	char img_matrix[size_x][size_y];
	
	/*vector<vector<char> > img_matrix;
	//adjust size
	img_matrix.resize(size_y);
	for(int i = 0; i < size_y; ++i){
		img_matrix[i].resize(size_x);
	}
	*/
	
	//read in matrix
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			ifs >> img_matrix[i][j];
		}
	
	}
	
	printImage(img_matrix);

	/*
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			cout << img_matrix[i][j];
		}
		cout << endl;
	}
	*/
	printImage(img_matrix);
	//create a vector to store boundary pixels
	vector<pixel> boundary;
	
	//need to find starting pixel.
	
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			
		}
	}
	
	
	return 0;
}




