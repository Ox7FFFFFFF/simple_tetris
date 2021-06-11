#ifndef _SHAPE_
#define _SHAPE_
#include "Shape.h"
#endif
class Square : public Shape{
	public:
		Square(int x,int y):Shape(x,y){
			int x_offset[3] = {1,0,1};
			int y_offset[3] = {0,1,1};
			setOffsetSize(3);
			setOffsetX(x_offset);
			setOffsetY(y_offset);
			setCurrentShape();
		}


};
