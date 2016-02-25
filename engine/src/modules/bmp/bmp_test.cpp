#include "bmp.h"

#include <cassert>

void test_size()
{
  assert(sizeof(bmp_magic) == 2);
  assert(sizeof(bmp_header) == 12);
  assert(sizeof(bmp_info) == 40);
}

int main()
{
  test_size();
  return 0;
}
