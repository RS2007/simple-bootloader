#include "vga_driver.h"
#include <stdarg.h>

unsigned int strlen(char *string) {
  unsigned int cursor = 0;
  while (string[cursor] != 0) {
    cursor++;
  }
  return cursor;
}

unsigned int printf(uint *offset, char color, const char *format_string, ...) {
  va_list ptr;
  uint initial_offset = *offset;
  va_start(ptr, format_string);
  for (int i = 0; i < strlen((char *)format_string); i++) {
    char current_char = format_string[i];
    if (current_char == '%') {
      i++;
      current_char = format_string[i];
      switch (current_char) {
      case 'd': {
        int number = va_arg(ptr, int);
        printNumber(offset, number, color);
        continue;
      }
      case 's': {
        char *string = va_arg(ptr, char *);
        printString(offset, string, color);
        continue;
      }
      case 'x': {
        int number = va_arg(ptr, int);
        char buffer[8];
        int j = 0;
        while (number != 0) {
          int remainder = number % 16;
          if (remainder < 10)
            buffer[j] = remainder + '0';
          else
            buffer[j] = remainder - 10 + 'a';
          number = number / 16;
          j++;
        }
        for (j = j - 1; j >= 0; j--) {
          printCharacter(offset, buffer[j], color);
        }
        continue;
      }
      case 'n': {
        goToNewLine(offset);
        continue;
      }
      default:
        return 0;
      }
    }
    printCharacter(offset, current_char, color);
  }
  uint final_offset = *offset;
  return final_offset - initial_offset;
}

void goToNewLine(uint *offset) { (*offset) = 160 * (((*offset) / 160) + 1); }

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
