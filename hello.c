#include "vga_driver.h"

int fib(int n) {
  if (n == 1 || n == 0) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}
void printFib(uint *offset, char color) {
  printString(offset,"Fibonnaci Numbers: ",color);
  goToNewLine(offset);
  for (int i = 1; i <= 15; i++) {
    printNumber(offset,i,color);
    printString(offset,":",color);
    printNumber(offset, fib(i), color);
    printString(offset," ",color);
  }
}

void test_vga_driver() {
  const char color = 0x0f;
  const char *hello = "Hello from C ";
  uint offset = 0;
  printString(&offset, (char *)hello, color);
  goToNewLine(&offset);
  printFib(&offset, color);
}

void my_main() { test_vga_driver(); }
