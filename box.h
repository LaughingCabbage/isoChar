#ifndef _BOX_H
#define _BOX_H

class Box{
	public:
		Box(int x_m, int x_x, int y_m, int y_x)
			{x_min = x_m; x_max = x_x; y_min = y_m; y_max = y_x;} 
			
		bool isIn(int x, int y){
			if(x >= x_min && x <= x_max && y >= y_min && y <= y_max){
				return true;
			}
			return false;
		}
		
		int width(){return x_max-x_min+1;}
			
		int x_min;
		int x_max;
		int y_min;
		int y_max;
		
	private:
	
};

#endif
