#define tablesize 92
#define HEADER_SIZE 18
#define LETTER_AMOUNT 6962 //該当FONTX2ファイル内のフォント数。美咲の場合この数

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

int block_size[tablesize];

void print_font(font_data data);
void printbincharpad(char c);
void get_font_date(char lette_code[2],font_data *dist);

//global data
font_data data[LETTER_AMOUNT];
fontx2header header;
