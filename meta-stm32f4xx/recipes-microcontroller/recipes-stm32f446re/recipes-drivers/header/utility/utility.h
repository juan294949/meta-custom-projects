#ifndef UTILITY_H
  #define UTILITY_H

  #include <stdint.h>
  #include <stdio.h>
  #include <stdarg.h>
  #include "usart.h"
  #include "systick.h"
  
  /* Function prototypes */
  void initUtilities();
  void print(const char* msg, ...);
  void blockMilliseconds(uint32_t delay);

#endif
