void my_main() {
  const short color = 0x0100;
  const char *hello = "Hello from C";
  char *vga_start_address_skipping_older_string =
      (char *)0xb8000 + 90; // Length of the earlier string has to be skipped
  int i = 0;
  while (i < 12) {
    *(vga_start_address_skipping_older_string) = color | *(hello + i);
    vga_start_address_skipping_older_string += 2;
    i++;
  }
}
