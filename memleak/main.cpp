#include <memory>
#include <iostream>

class testObject {
private:
  int _val = 0;
public:
  testObject(int val): _val(val) {};
  void showVal() {
    std::cout << _val << std::endl;
  };
};

void f(void)
{
  int* x = new int[10]; 
  x[10] = 0;        // problem 1: heap block overrun
}                    // problem 2: memory leak -- x not freed

void g(void)
{
  // mem leak here, y is not deallocated
  testObject *y = new testObject(20);
  y->showVal();
}

void h(void)
{
  // no leaks here because the object is deleted using the unique pointer
  std::unique_ptr<testObject> z(new testObject(30));
  z->showVal();
}

int main(void)
{
  f(); // core dump because of f
  g();
  h();
  return 0;
}
