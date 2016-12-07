#ifndef PIXEL_H_
#define PIXEL_H_
class Pixel {
	public:
		Pixel(){}
		Pixel(int x_in, int y_in){x = x_in; y = y_in;} //constructor
		bool isEqual(Pixel in);
		void trace();
		bool operator==(Pixel arg);
		bool isBound(){return is_bound;}
		void setBound(){is_bound = true;}
		int x;
		int y;
	private:
		bool is_bound;
};

#endif //PIXEL_H_

