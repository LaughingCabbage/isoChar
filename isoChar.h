#ifndef PIXEL_H_
#define PIXEL_H_

class Pixel {
	public:
		Pixel(){}
		Pixel(int x_in, int y_in){x = x_in; y = y_in;} //constructor
		bool isEqual(Pixel in);
		
		int x;
		int y;
	private:
		
};



#endif
