#define tablesize 92
#define HEADER_SIZE 18

typedef struct{
  char start_code[2];
  char end_code[2];
}bloack_table_entry;

typedef struct{
  char filesignature[6];
  char fontname[8];
  char font_w;
  char font_h;
  char char_code_flg;
  char blocks;
  bloack_table_entry *block;
}fontx2header;

typedef struct{
  char filesignature[6];
  char fontname[8];
  char font_w;
  char font_h;
  char char_code_flg;
  char blocks;
  //  bloack_table_entry *block;
}fontx2header_before;

typedef bloack_table_entry test_table[];

typedef char font_data[8];

void print_font(font_data data);
void printbincharpad(char c);
