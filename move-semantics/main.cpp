#include <string>
#include <utility>

class moveFrom {
private:
  int a = 10;

public:
  std::string _str = "Default String\n";

  moveFrom(std::string str) : _str(str) {};
  ~moveFrom() {};

  void printString() {
    printf("%s", _str.c_str());
  };

  void printVal() {
    printf("%d\n", a);
  }
};

class secondMoveFrom {
  int _a;
public:
  secondMoveFrom(int a) : _a(a) {};
  ~secondMoveFrom() {};

  std::string _str = "Second Move From\n";
};

class thirdMoveFrom {
public:
  thirdMoveFrom() {};
  ~thirdMoveFrom() {};

  std::string _str = "Third Move From\n";
};

class moveTo {
private:
  std::string _str = "";

public:
  // rvalue reference 
  // also a universal reference (T&&) thus reference collapsing applies
  template <typename T>
  moveTo(T&& w) noexcept
    : _str( std::move(w)._str) 
    {}; 
  ~moveTo() {};

  void printString() {
    printf("%s", _str.c_str());
  };
};

int main() {
  // create an object with a string array
  moveFrom m1( "Hello World\n" );
 
  // here's the string
  m1.printString();

  // here's the value in movedFrom
  m1.printVal();

  // we can move moveFrom using an lvalue reference
  moveTo t1( std::move(m1) );
  // or an rvalue reference moveFrom is a temporary object
  moveTo t2( moveFrom("New World\n") );
  // it is only possible to pass both lvalue and rvalue here due ro the universal reference
  // we can also pass dfferent types
  moveTo t3( secondMoveFrom(13) );
  // but this doesnt work because of parsing issues
  // moveTo t4( thirdMoveFrom() );
  moveTo t4{ thirdMoveFrom() };

  // here's the string in moveTo
  t1.printString();
  // t2 is also valud
  t2.printString();
  // t3 is valid
  t3.printString();

  // but c++ doesnt use a destructive move 
  // so the object still exists
  // in a moved-from state
  // hence this compiles
  // but it doesnt print anything because _str contains nothign
  m1.printString();
  m1.printVal(); 
};
