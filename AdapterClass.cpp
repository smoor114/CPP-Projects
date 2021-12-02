//Spencer Moore
//smoor114
// figures: class adapter pattern
// Mikhail Nesterenko
// 2/16/2014

#include <iostream>

using std::cout; using std::endl;

class Figure {
public:
   virtual void draw()=0;
   virtual ~Figure(){}
};

class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, 
		   int topLeftY, 
		   int bottomRightX, 
		   int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}
   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
   {
      topLeftX_ = topLeftX;
      topLeftY_ = topLeftY;
      bottomRightX_ = bottomRightX;
      bottomRightY_ = bottomRightY;
   }
   int getTopLeftX() { return topLeftX_; }
   int getTopLeftY() { return topLeftY_; }
   int getBottomRightX() { return bottomRightX_; }
   int getBottomRightY() { return bottomRightY_; }

   void oldDraw(){
      for(int i=0; i < bottomRightY_; ++i){
	 for(int j=0; j < bottomRightX_; ++j)
	    if(i >= topLeftY_  && j >= topLeftX_ )
	       cout << '*';
	    else
	       cout << ' ';
	 cout << endl;
      }
   }
private: 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

class SquareAdapter: public Figure, private LegacyRectangle {
public:
   SquareAdapter(int size): 
      LegacyRectangle(0,0,size,size){};
   void draw() override {
      oldDraw();
   }

   int size() { return sqSize;}
   void resize(int newSize) {
      sqSize = newSize;
    move(0, 0, newSize, newSize); 
    }
private:
   int sqSize;
};


int main(){
   int enter_size;
  cout << endl;
  std::cout << "Enter size for square" << std::endl;
  std::cin >> enter_size;

  SquareAdapter* square = new SquareAdapter(enter_size);
  square->draw();

  std::cin.clear();
  std::cout << "Enter new size for square" << std::endl;
  std::cin >> enter_size;

  square->resize(enter_size);
  square->draw();
  int i = 0;
}
