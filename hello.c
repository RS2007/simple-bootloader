#include "vga_driver.h"

int fib(int n) {
  if (n == 1 || n == 0) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

void test_vga_driver() {
  const char color = 0x0f;
  const char *hello = "Hello from C ";
  char *vga_start_address_skipping_older_string =
      (char *)0xb8000 + 80; // Length of the earlier string has to be skipped
  printString(&vga_start_address_skipping_older_string, (char *)hello, color);
  printString(&vga_start_address_skipping_older_string,
              "10th Fibonacci numbers ", color);
  printNumber(&vga_start_address_skipping_older_string, fib(10), color);
}

void my_main() { test_vga_driver(); }
