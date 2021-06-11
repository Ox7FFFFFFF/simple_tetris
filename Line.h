#ifndef _SHAPE_
#define _SHAPE_
#include "Shape.h"
#endif
class Line : public Shape{
	public:
		Line(int x,int y):Shape(x,y){
			int x_offset[3] = {1,2,3};
			int y_offset[3] = {0,0,0};
			setOffsetSize(3);
			setOffsetX(x_offset);
			setOffsetY(y_offset);
			setCurrentShape();
		}
		

};
