#define HEADER_SIZE 22

typedef struct{
  char filesignature[6];
  char fontname[8];
  char font_w;
  char font_h;
  char char_code_flg;
  char blocks;
  char start_code[2];
  char end_code[2];
} fontx2header;
