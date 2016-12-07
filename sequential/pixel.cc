#include "pixel.h"

bool Pixel::isEqual(Pixel in){
	if(x == in.x && y == in.y)
		return true;
	return false;
}

bool Pixel::operator==(Pixel arg){
	if(x == arg.x && y == arg.y)
		return true;
	return false;
}
