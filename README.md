# Reed-Solomon

#include "rs.h"

main()
{
  int i;
  char code[255];

  rs_init(255, 239);

  for (i = 0; i < 239; i++) code[i] = data(i);

  rs_encode(code);

  code[100] = 200; /* eroor */

  rs_decode(code);
} 
