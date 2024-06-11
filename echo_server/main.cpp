#include <iostream>

#include <zlib.h>

int main()
{
  try
  {
    std::cout << "First line" << std::endl;
    std::cout << "Second line" << std::endl;
  }
  catch (std::exception& e)
  {
    std::printf("Exception: %s\n", e.what());
    return -1;
  }

  return 0;
}