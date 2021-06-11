#ifndef _POINT_
#define _POINT_
#include "Point.h"
#endif
#include <vector>
#include<iostream>
class Shape{
	public:
		Shape(){
			addPoint(0,0);
		}
		Shape(int x,int y){
			addPoint(x,y);
		}
		
		void addPoint(int x,int y){
			points.push_back(Point(x,y));
		}
		
		void setOffsetX(int *offset){
			x_offset = new int[offset_size];
			for(int i=0;i<offset_size;i++){
				x_offset[i] = offset[i];
			}
		}
		void setOffsetY(int *offset){
			y_offset = new int[offset_size];
			for(int i=0;i<offset_size;i++){
				y_offset[i] = offset[i];
			}
		}
		void setOffsetSize(int size){
			offset_size = size;
		}
		
		void setCurrentShape(){
			Point p = points.front();
			int x = p.getX();
			int y = p.getY();
			for(int i=0;i<offset_size;i++){
				int new_x = x+x_offset[i];
				int new_y = y+y_offset[i];
				addPoint(new_x,new_y);
			}
		}
		
		void updateCurrentShape(int x,int y){
			points.front().setXY(x,y);
			Point p = points.front();
			int nx = p.getX();
			int ny = p.getY();
			for(int i=0;i<offset_size;i++){
				int new_x = nx+x_offset[i];
				int new_y = ny+y_offset[i];
				points[i+1].setXY(new_x,new_y);
			}
		}
		
		void erase(unsigned char ***map){
			Point original = points.front();
			int ox = original.getX();
			int oy = original.getY();
			(*map)[oy][ox] = ' ';
			for(int i=0;i<offset_size;i++){
				int new_x = ox+x_offset[i];
				int new_y = oy+y_offset[i];
				(*map)[new_y][new_x] = ' ';
			}
		}
		
		void draw(unsigned char ***map){
			for(int i=0;i<points.size();i++){
				Point p = points[i];
				(*map)[p.getY()][p.getX()] = 'O';
			}
		}
		
		void swap_offset(int m_x,int m_y){
			for(int i=0;i<offset_size;i++){
				int tmp = m_x*x_offset[i];
				x_offset[i] = m_y*y_offset[i];
				y_offset[i] = tmp;
			}
		}
		
		void rotate(bool direction){
			if(direction){
				swap_offset(-1,1);
			}
			else{
				swap_offset(1,-1);
			}
			Point p = points.front();
			updateCurrentShape(p.getX(),p.getY());
		}
		
		bool touch(unsigned char ***map,int nx,int ny){
			int flag = 0;
			for(int i=0;i<points.size();i++){
				int new_x,new_y;
				if(i>0){
					new_x = nx+x_offset[i-1];
					new_y = ny+y_offset[i-1];
				}
				else{
					new_x = nx;
					new_y = ny;
				}
				if((*map)[new_y][new_x] != ' '){
					return true;
				}
				
			}
			return false;
		}
	private:
		std::vector<Point> points;
		int offset_size;
		int* x_offset;
		int* y_offset;
};
