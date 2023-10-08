#include "vga_driver.h"

int fib(int n) {
  if (n == 1 || n == 0) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}
void printFib(uint *offset, char color) {
  printf(offset, color, "Fibonnaci Numbers:%n");
  for (int i = 1; i <= 15; i++) {
    if (i == 15) {
      printf(offset, color, "%d:%d", i, fib(i));
      continue;
    }
    printf(offset, color, "%d:%d ", i, fib(i));
  }
}

void test_vga_driver() {
  const char color = 0x0f;
  const char *hello = "Hello from C %n";
  uint offset = 0;
  printf(&offset, color, hello);
  printFib(&offset, color);
  printf(&offset, color, "Printing hex numbers%n");
  for (int i = 0; i <= 40; i++) {
    if (i == 40) {
      printf(&offset, color, "%x", i);
      continue;
    }
    printf(&offset, color, "%x ", i);
  }
}

void my_main() { test_vga_driver(); }
