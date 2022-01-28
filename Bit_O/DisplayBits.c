#include <stdio.h>
#include <stdlib.h>
void displayBits (unsigned value);

int main(void)
{
unsigned int x;
printf( "Enter an unsigned integer: " );
scanf( "%u", &x );
displayBits(x);

  return 0;
}
/* display bits of an unsigned integer value */
void displayBits (unsigned int value)
{

  unsigned int mask= (1<<31);/*// generate bitmask for the integr 1 is left shift by 31*/
  /* loop for n bits */
  unsigned int c ; /*counter*/
  for(c=1;c<=32;c++)
  {
  putchar( value & mask ? '1' : '0' );
  /* shift the value by 1 or divide by 2 each time */
  value = value << 1;
  /* output space after 8 bits */
  if (c%8==0)
  {
    putchar(' ');
  } /* end for if */
}/*end for loop*/
  putchar('\n');

} /* end of the function displaybit */
