#include "pixel.h"

bool Pixel::isEqual(Pixel in){
	if(x == in.x && y == in.y)
		return true;
	return false;
}
