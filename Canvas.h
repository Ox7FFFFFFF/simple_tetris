
class Canvas{
	public:
		static Canvas& getInstance(){
			static Canvas canvas;
			return canvas;
		}
		
		Canvas(int width,int height){
			map = new char*[height+1];
			for(int i=0;i<=height;i++){
				map[i] = new char[width+1];
				for(int j=0;j<=width;j++){
					if(i==0 || i == height || j==0 || j == width) map[i][j] = '+';
					else map[i][j] = ' ';
				}
			}
		}
		
		char** getMap(){
			return map;
		}
		
	private:
		char** map;
};
