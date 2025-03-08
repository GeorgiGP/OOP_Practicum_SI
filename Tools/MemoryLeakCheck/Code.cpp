#include <iostream>
#include <cstdlib>
#include <crtdbg.h>
//include those 2 libs

//IMPORTANT: only works when debugging
int main() //so set break point for debugging here. Debug and then step out (arrow up) to exit the program 
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //...
  //someLogic("crit1.txt", "crit2.txt", "res.txt"); The function has no memory leak
  int* a = new int(3);
  //...
}
