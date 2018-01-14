/*
  Reed Solomon encode/decode test program
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "rs.h"

#define RS_CODE 255
#define RS_MESG 239
#define RS_PARI (RS_CODE - RS_MESG)

#define ERR_RATE 1000 /* error rate is 1/ERR_RATE */
#define LOOP_COUNT 10000

int main(void)
{
  int i, j, k, m;
  unsigned char code1[RS_CODE], code2[RS_CODE], code3[RS_CODE];

  /* initialize RS library by rs_init(n, k) */
  if (rs_init(RS_CODE, RS_MESG)) {
    fprintf(stderr, "rs_init() return error\n");
    exit(1);
  }

  /* make original message */
  for (i = 0; i < RS_MESG; i++) 
    code1[i] = rand() & 0xff;

  /* generate Reed-Solomon parity */
  if (rs_encode(code1)) {
    fprintf(stderr, "rs_encode() return error\n");
    exit(1);
  }

  /* copy RS code */
  for (i = 0; i < RS_CODE; i ++) {
    code2[i] = code1[i];
  }

  /* add errors */
  for (i = 0; i < RS_PARI / 2; i++) {
    j = rand() % RS_CODE; /* index */
    k = rand() & 0xff; /* error value */

    code2[j] = k; /* error */
  }

  /* copy error code */
  for (i = 0; i < RS_CODE; i++) {
    code3[i] = code2[i];
  }

  /* error correction */
  m = rs_decode(code3);
  if (m < 0) {
    fprintf(stderr, "rs_decode() can not correct error\n");
    exit(1);
  }

  printf("%d errors corrected\n", m);

  /* print codes */
  printf("[index], original, with error, corrected\n");
  for (i = 0; i < RS_CODE; i++) {
    
    printf("[%d], %02x, %02x, %02x %c\n", i, code1[i], code2[i], code3[i],
	   (code2[i] != code3[i]) ? '*' : ' ');
  }

  return 0;
}
