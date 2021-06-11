#ifndef _SHAPE_
#define _SHAPE_
#include "Shape.h"
#endif

class LRShape : public Shape{
	public:
		LRShape(int x,int y):Shape(x,y){
			int x_offset[3] = {0,0,-1};
			int y_offset[3] = {1,2,2};
			setOffsetSize(3);
			setOffsetX(x_offset);
			setOffsetY(y_offset);
			setCurrentShape();
		}

};
