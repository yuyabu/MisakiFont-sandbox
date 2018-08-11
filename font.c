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
 // char filesignature[6];
 // char fontname[8];
 // char font_w;
 // char font_h;
 // char char_code_flg;
 // char blocks;
 // char start_code[2];
 // char end_code[2];

 //この書き方はできないみたい。filesignatureの開始アドレスからnull文字までが全部出てしまう。
 //printf("filesignature is %s",header.filesignature);
 char temp[100];
 strncpy(temp,header.filesignature,5);
 printf("filesignature is %s\n",temp);
 strncpy(temp,header.fontname,7);
 printf("fontname is %s\n",temp);
 printf("width is %x\n",header.font_w);
 printf("hight is %x\n",header.font_h);
 printf("char code flg is %x\n",header.char_code_flg);
 printf("blocks is %x\n",header.blocks);

 //配列をそのまま１６進数で表示する方法がわからないのでかなり頭の悪いやり方でやってる
 printf("start_code is %x%x\n",(unsigned char)header.start_code[0],(unsigned char)header.start_code[1]);
 printf("end_code is %02x%02x\n",(unsigned char)header.end_code[0],(unsigned char)header.end_code[1]);

  fclose(fp);
}
