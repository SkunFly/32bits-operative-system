#include "screen.h"
#include "port.h"
#include "../kernel/util.h"

int print_char(char character, int row, int col, char attribute_byte);
void print_at(char* str, int row, int col);
void print(char* str);
int handle_scrolling(int cursor_offset);
int get_cursor();
void set_cursor(int offset);
int get_screen_offset(int row, int col);
int get_offset_row(int offset);
int get_offset_col(int offset);


void print_at(char* str, int row, int col){
  int offset;

  if(row >= 0 && col >= 0){
    offset = get_screen_offset(row, col);
  }
  else{
    offset = get_cursor();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  int i = 0;
  while(str[i] != 0){
    offset = print_char(str[i++], row, col, WHITE_ON_BLACK);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  set_cursor(offset);
}

void print(char* str){
  print_at(str, -1, -1);
}

void clear_screen(){
  int row, col;

  for(row = 0; row < MAX_ROWS; row++)
    for(col = 0; col < MAX_COLS; col++)
      print_char(' ', row, col, 0);

  set_cursor(get_screen_offset(0, 0));
}

/*--- PRIVATE FUNCTIONS ---*/

int print_char(char character, int row, int col, char attribute_byte){
  // Pointer to the start of video memory
  unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;

  // If attribute_byte is zero, assume default style
  if(!attribute_byte) attribute_byte = WHITE_ON_BLACK;

  /* Error control: print a red 'E' if the coords aren't right */
  if (col >= MAX_COLS || row >= MAX_ROWS) {
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
    vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
    return get_screen_offset(row, col);
  }

  int offset;
  if(col >= 0 && row >= 0){
    offset = get_screen_offset(row, col);
  }
  else{
    offset = get_cursor();
  }

  if(character == '\n'){
    row = get_offset_row(offset);
    offset = get_screen_offset(row+1, 0);
  }
  else{
    vidmem[offset] = character;
    vidmem[offset+1] = attribute_byte;
    //Update offset to the next character cell
    offset += 2;
  }

  offset = handle_scrolling(offset);

  set_cursor(offset);

  return offset;
}

int handle_scrolling(int offset){
  if(offset >= MAX_ROWS * MAX_COLS * 2 ){

    // Shuffle the rows back one
    int i;
    for(int i = 1; i < MAX_ROWS; i++){
      memory_copy((char *) get_screen_offset(i, 0) + VIDEO_ADDRESS,
                  (char *) get_screen_offset(i-1, 0) + VIDEO_ADDRESS,
                  MAX_COLS * 2
      );
    }

    char *last_line = (char *) get_screen_offset(MAX_ROWS - 1, 0) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

    offset -= 2 * MAX_COLS;
  }
  return offset;
}

// REG_SCREEN_CTRL (0x3D4) -> port that map the screen cursor position
// REG_SCREEN_DATA 0x3D5   -> port where the query result is stored
// value 14 -> request the cursor position high byte
// value 15 -> request the cursor position low byte
int get_cursor(){
  port_byte_out(REG_SCREEN_CTRL, 14); // queries port about high byte position
  int offset = port_byte_in(REG_SCREEN_DATA) << 8; // shift-left 8 bits (low byte is missing)
  port_byte_out(REG_SCREEN_CTRL, 15); // queries port about low byte position
  offset += port_byte_in(REG_SCREEN_DATA); // sum the result of the query with the high byte

  // Since the cursor offset reported by the VGA hardware is the number of
  // characters, we multiplu by two to convert it to a character cell offset
  return offset*2;
}

void set_cursor(int offset){
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xff)); // we just want the low part
}

int get_screen_offset(int row, int col){ return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
