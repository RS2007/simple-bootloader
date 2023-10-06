#define ROW_LENGTH 80
#define VGA_BASE 0xb8000
#define uint unsigned int

void printCharacter(uint *, char, char);
void printString(uint *, char *, char);
void printNumber(uint *, int, char);
void goToNewLine(uint *);
