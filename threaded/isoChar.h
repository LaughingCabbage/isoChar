#ifndef ISOCHAR_H_

#include <vector>
#include <fstream>
#include <string>
#include "pixel.h"
#include "box.h"

enum move {Up, Right, Left, Down};
enum direction {North, East, South, West};
class isoChar {
	public:
		isoChar();
		bool load(char *file_name);
		void write(char *file_name);
		void trace(Pixel& start);
		void drawBoxes();
		int getStart(Pixel& start);
		void printMatrix();
		int inBoxes(int x, int y);
		
		
		int size_x; //global availability of image matrix size
		int size_y;
		std::vector<Box> contour_boxes;
	private:
		std::vector< std::vector<char> > img_matrix;
		std::string type;
		std::string source;
		std::vector<Pixel> box_pixels;
		

};
#endif
