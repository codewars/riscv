#ifndef __PRELOADED_H
#define __PRELOADED_H

int factorial(int n) {
  return n <= 0 ? 1 : n * factorial(n - 1);
}

#endif
