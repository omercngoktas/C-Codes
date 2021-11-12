#include <stdio.h>


void out_float(float f)
{
  size_t size = sizeof(f);
  unsigned char * p = (unsigned char *) &f;
  p += size-1;
  while (size--)
  {
    int n;
    for (n=0; n<8; n++)
    {
      putchar('0' + (*p & 128 ? 1 : 0));
      *p <<= 1;
    }
    p--;
  }
}


int main()
{
  float f = 29.109375f;

  out_float(f);
  putchar('\n');
  return 0;
}