#include "vga_driver.h"

unsigned int strlen(char *string) {
  unsigned int cursor = 0;
  while (string[cursor] != 0) {
    cursor++;
  }
  return cursor;
}

void goToNewLine(uint *offset) {
  (*offset) = (((*offset) / 80) + 2) * ROW_LENGTH;
}

void printCharacter(uint *offset, char print_char, char color) {
  char *vga_mem = (char *)VGA_BASE + *offset;

  vga_mem[0] = print_char;
  vga_mem[1] = color;
  (*offset) = (*offset) + 2;
}

void printString(uint *offset, char *string, char color) {
  unsigned int string_length = strlen(string);
  for (unsigned int i = 0; i < string_length; i++) {
    printCharacter(offset, string[i], color);
  }
}

void printNumber(uint *offset, int number, char color) {
  if (number > 9) {
    printNumber(offset, number / 10, color);
  }
  printCharacter(offset, (char)('0' + number % 10), color);
}
