#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "font.h"

typedef enum _boolean { FALSE, TRUE } boolean;

void confirm_files_sandbox(fontx2header header,FILE *fp);
void toggle_endian(char v[2]);
boolean comp_letter(char v1[2],char v2[2]);
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
 fread(&header,HEADER_SIZE,1,fp);

 //動作確認用。
 //confirm_files_sandbox(header,fp);

 //bloack_table_entry entry[block_amount];
 //header.block = malloc(sizeof(bloack_table_entry) * block_amount);
 printf("hdader size is %lu\n",sizeof(header));
 printf("table entry pointer size is %2lu\n",sizeof(bloack_table_entry*));
 printf("table entry  size is        %2lu\n",sizeof(bloack_table_entry));

 printf("new hader size is           %2lu\n",sizeof(fontx2header));
 printf("old header size is          %2lu\n",sizeof(fontx2header_before));

 printf("size of hader instance      %2lu\n",sizeof(header.block));

 printf("addr of header          %p\n",&header);
 printf("addr of header.block    %p\n",&header.block);
 printf("addr of header.block[0] %p\n",&header.block[1]);
 printf("addr of header.block[1] %p\n",&header.block[1]);




 int block_amount = (int)header.blocks;
 header.block = malloc(sizeof(bloack_table_entry) * block_amount);

 fread(header.block,sizeof(bloack_table_entry)* block_amount,1,fp);
 for(int i=0;i<block_amount;i++){
   toggle_endian(header.block[i].start_code);
   toggle_endian(header.block[i].end_code);


   printf("%3d blocks start code is 0x%2x%2x\n",i
     ,(unsigned char)header.block[i].start_code[0]
     ,(unsigned char)header.block[i].start_code[1]
   );
   printf("%3d blocks end   code is 0x%2x%2x\n",i
    ,(unsigned char)header.block[i].end_code[0]
    ,(unsigned char)header.block[i].end_code[1]
    );
  }

  fclose(fp);



}

/**
 * 8バイトの配列(美咲フォントのデータ実態)を１文字分printする
 * @param c [description]
 */
void print_font(font_data data){
  for(int i=0;i<8;i++){
    printbincharpad(data[i]);
  }
  puts("\n");
}

/**
 * 美咲フォント
 * @param c [description]
 */
 void printbincharpad(char c){
  for (int i = 7; i >= 0; --i){
    putchar( (c & (1 << i)) ? '1' : '0' );
  }
  putchar('\n');
}
int block_potition(){
  return -1;
}

/**
 * 長さ2の配列のエンディアンを入れ替える
 * @param v      [処理対象の配列]
 * @param length [配列の長さ]
 */
void toggle_endian(char v[2]){
  char tmp=v[0];
  v[0]= v[1];
  v[1] = tmp;
}

/**
 * 文字(2Byete=長さ2のchar配列の比較)
 * @param  v1 比較対象1
 * @param  v2 比較対象2
 * @return v1>v2のときtrue。それ以外false
 */
boolean comp_letter(char v1[2],char v2[2]){
  if(v1[0]>v2[1]){
    return TRUE;
  }else if(v1[0]==v2[0]){
    if(v1[1]>v2[1]){
      return TRUE;
    }
  }
  return FALSE;
}
