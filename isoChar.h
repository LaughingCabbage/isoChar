#ifndef ISOCHAR_H_

#include <vector>
#include <fstream>
#include <string>
#include "pixel.h"

enum move {Up, Right, Left, Down};
enum direction {North, East, South, West};
class isoChar {
	public:
		isoChar();
		bool load(char *file_name);
		void trace(Pixel& start, int& x_next, int& y_next);
		void drawBox(std::vector<std::vector<char> >& img_matrix,
				 int x_min, int y_min, int x_max, int y_max);
		int getStart(Pixel& start);
		void printMatrix();
		
		
		int size_x;
		int size_y;
	private:
		std::vector< std::vector<char> > img_matrix;
		std::string type;
		std::string source;
		std::vector<std::vector<Pixel> > letter_contours;

};
#endif
