class Point{
	public:
		Point(){
			Point(0,0);
		}
		Point(int x,int y){
			_x = x;
			_y = y;
		}
		int getX(){
			return _x;
		}
		int getY(){
			return _y; 
		}
		void setXY(int x,int y){
			setX(x);
			setY(y);
		}
		void setX(int x){
			_x = x;
		}
		void setY(int y){
			_y = y;
		}
		void increaseX(){
			_x += 1;
		}
		void decreaseX(){
			_x -= 1;
		}
		void increaseY(int step){
			_y += step;
		}
	private:
		int _x;
		int _y;
};
