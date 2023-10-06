unsigned int strlen(char* string){
    unsigned int cursor = 0;
    while(string[cursor] != 0){
        cursor++;
    }
    return cursor;
}

void printCharacter(char **vga_memory_pointer, char print_char, char color) {
  (*vga_memory_pointer)[0] = print_char;
  (*vga_memory_pointer)[1] = color;
  (*vga_memory_pointer) = (*vga_memory_pointer)+2;
}

void printString(char **vga_memory_pointer,char* string,char color){
    unsigned int string_length = strlen(string);
    for(unsigned int i = 0; i < string_length; i++){
        printCharacter(vga_memory_pointer,string[i],color);
    }
}


void printNumber(char **vga_memory_pointer, int number, char color) {
  if (number > 9) {
    printNumber(vga_memory_pointer, number / 10, color);
  }
  printCharacter(vga_memory_pointer,(char)('0' + number % 10),color);
}
