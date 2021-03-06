/*
 * Author:      Eric van der Woude
 * Description: UART library by David Welch, modified to work
 *              with FreeRTOS on the Raspberry Pi B+.
 */

#include "uart.h"


void uart_init()
{
  unsigned int ra;

  PUT32(AUX_ENABLES,1);
  PUT32(AUX_MU_IER_REG,0);
  PUT32(AUX_MU_CNTL_REG,0);
  PUT32(AUX_MU_LCR_REG,3);
  PUT32(AUX_MU_MCR_REG,0);
  PUT32(AUX_MU_IER_REG,0);
  PUT32(AUX_MU_IIR_REG,0xC6);
  PUT32(AUX_MU_BAUD_REG,270);

  ra=GET32(GPFSEL1);
  ra&=~(7<<12);       // gpio14
  ra|=2<<12;          // alt5
  ra&=~(7<<15);       // gpio15
  ra|=2<<15;          // alt5
  PUT32(GPFSEL1, ra);

  PUT32(GPPUD,0);
  for(ra=0;ra<150;ra++) dummy(ra);
  PUT32(GPPUDCLK0,(1<<14)|(1<<15));
  for(ra=0;ra<150;ra++) dummy(ra);
  PUT32(GPPUDCLK0,0);

  PUT32(AUX_MU_CNTL_REG,3);
}

void uart_send(unsigned int c)
{
  for (;;)
  {
    if(GET32(AUX_MU_LSR_REG) & 0x20) break;
  }

  PUT32(AUX_MU_IO_REG , c);
}

void uart_print(char *s)
{
    while (*s != 0)
    {
        uart_send((unsigned int) *s);
        s++;
    }

    uart_send(0x0A);
}

/*
 * Prints run time statistics for a task. It prints the following format:
 * <task name> <elapsed time> <appointed time>
 */
void uart_print_stats(char *name, unsigned int i, unsigned int j)
{
  char *buffer = "";

  uart_print(name);

  _int_to_string(buffer, i);
  uart_print(buffer);

  _int_to_string(buffer, j);
  uart_print(buffer);

  uart_print("\n");
}

/* Converts a given integer n to string and
 * stores the result in a given string.
 *
 * Code obtained from:
 * https://www.go4expert.com/articles/converting-integer-string-c-sprintf-t28037/
 */
int _int_to_string(char *s, unsigned int n)
{
  unsigned int i = 1000000000;

  if (((signed) n) < 0 ) {
    *s++ = '-';
    n = -n;
  }

  while(i > n) i /= 10;

  do {
    *s++ = '0' + (n - n % i) / i % 10;
  } while(i /= 10);

  *s = 0;

  return n;
}

//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
