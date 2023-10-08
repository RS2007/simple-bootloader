#include "vga_driver.h"

int fib(int n) {
  if (n == 1 || n == 0) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}
void printFib(uint *offset, char color) {
  printString(offset, "Fibonnaci Numbers: %n", color);
  for (int i = 1; i <= 15; i++) {
    printf(offset, color, "%d:%d ", i, fib(i));
  }
}

void test_vga_driver() {
  const char color = 0x0f;
  const char *hello = "Hello from C%n";
  uint offset = 0;
  printf(&offset, color, hello);
  printFib(&offset, color);
  printf(&offset, color, "Printing hex numbers%n");
  for (int i = 0; i <= 16; i++) {
    printf(&offset, color, "%x\n", i);
  }
}

void my_main() { test_vga_driver(); }
