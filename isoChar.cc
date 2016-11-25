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

	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			cout << img_matrix[i][j];
		}
		cout << endl;
	}
	

	//create a vector to store boundary pixels
	vector<pixel> boundary;
	
	//need to find starting pixel.
	pixel start;
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
	bool done = 0;
	
	int x = start.x;
	int y = start.y;
	pixel temp;
	enum move {Up, Right, Left, Down};
	//start by checking next column for black pixel
	move current_move = Right;
	while(!done){
		//check if next pixel in row is black, add if it is.
		switch(current_move){
			case Up:
				if(y > 0 && img_matrix[y-1][x]){
					temp.x = x;
					temp.y = y;
					boundary.push_back(temp);
					cout << "\nx: " << x << " y: " << y << endl;
					y = y-1;
				}else{
					current_move = Right;
				}
			break;
			
			case Right:
				cout<<"right case\n";
				if( x < size_x && img_matrix[y][x+1] == '1'){
					temp.x = x;
					temp.y = y;
					boundary.push_back(temp);
					cout << "\nx: " << x << " y: " << y << endl;
					x = x+1;
				}else{
					current_move = Up;
				}
			break;
			
			default:
				cout<< "default...\n";
		}
	} 
	
	
	return 0;
}




