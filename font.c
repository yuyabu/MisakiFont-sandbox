#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "font.h"


int main(){
  FILE *fp;
  char *filename = "MISAKI.FNT";

  /*fnt file open*/
  if((fp = fopen(filename,"r"))==NULL){
    fprintf(stderr,"%s open faild.\n",filename);
    exit(EXIT_FAILURE);
  };
 fontx2header header;
 printf("hdader size is %lu\n",sizeof(header));
 fread(&header,sizeof(header),1,fp);
 // typedef struct{
 //   char filesignature[6];
 //   char fontname[8];
 //   char font_w;
 //   char font_h;
 //   char char_code_flg;
 //   char blocks;
 //   char start_code[2];
 //   char end_code[2];
 // } fontx2header;

 //この書き方はできないみたい。filesignatureの開始アドレスからnull文字までが全部出てしまう。
 //printf("filesignature is %s",header.filesignature);

 char temp[100];
 strncpy(temp,header.filesignature,6);

 printf("filesignature is %s\n" ,temp                );

 strncpy(temp,header.fontname,7);

 printf("fontname is %s\n"      ,temp                );
 printf("width is %x\n"         ,header.font_w       );
 printf("hight is %x\n"         ,header.font_h       );
 printf("char code flg is %x\n" ,header.char_code_flg);
 printf("blocks is %x\n"        ,header.blocks       );

 //char型のblock数をint型に変換
 //charとintでバイト数違うけどこんな型変換ができていいのかw
 int block_amount = (int)header.blocks;

 bloack_table_entry entry[block_amount];

 //ブロックテーブルの読み取り
 fread(&entry,sizeof(entry),1,fp);
 for(int i=0;i<block_amount;i++){
   //この方法でなぜかダンプできない
   printf("%3d blocks start code is 0x%2x%2x\n",i
     ,(unsigned char)entry[i].start_code[0]
     ,(unsigned char)entry[i].start_code[1]

   );
   printf("%3d blocks end   code is 0x%2x%2x\n",i
   ,(unsigned char)entry[i].end_code[0]
   ,(unsigned char)entry[i].end_code[1]
  );
}

font_data data[10];
fread(&data,sizeof(data),1,fp);

 for(int i=0;i<10;i++){
   print_font(data[i]);
 }



 //配列をそのまま１６進数で表示する方法がわからないのでかなり頭の悪いやり方でやってる
 //printf("start_code is %x%x\n"   ,(unsigned char)header.start_code[0] ,(unsigned char)header.start_code[1]);
 //printf("end_code is %02x%02x\n" ,(unsigned char)header.end_code[0]   ,(unsigned char)header.end_code[1]  );

  fclose(fp);
}
void print_font(font_data data){
  for(int i=0;i<8;i++){
    printbincharpad(data[i]);
  }
  puts("\n");
}
void printbincharpad(char c){
  for (int i = 7; i >= 0; --i){
    putchar( (c & (1 << i)) ? '1' : '0' );
  }
  putchar('\n');
}
