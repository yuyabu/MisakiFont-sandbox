
typedef struct{
  char filesignature[6];
  char fontname[8];
  char font_w;
  char font_h;
  char char_code_flg;
  char blocks;
} fontx2header;

typedef struct{
  char start_code[2];
  char end_code[2];
}bloack_table_entry;

typedef char font_data[8];

void print_font(font_data data);
void printbincharpad(char c);
