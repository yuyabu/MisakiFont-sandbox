#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "font.h"

typedef enum _boolean { FALSE, TRUE } boolean;
int count_letters_untill_block(int block[tablesize],int block_index);
void confirm_files_sandbox(fontx2header header,FILE *fp);
void toggle_endian(char v[2]);
int block_potition(bloack_table_entry* table,char letter[2]);
boolean comp_letter(char v1[2],char v2[2]);
int char_2B_hex_minus(char minuend[2],char subtrahend[2]);

int main(){
  FILE *fp;
  char *filename = "MISAKI.FNT";

  /*fnt file open*/
  if((fp = fopen(filename,"r"))==NULL){
    fprintf(stderr,"%s open faild.\n",filename);
    exit(EXIT_FAILURE);
  };

  fontx2header header;
  fread(&header,HEADER_SIZE,1,fp);

  int block_amount = (int)header.blocks;
  header.block = malloc(sizeof(bloack_table_entry) * block_amount);

  fread(header.block,sizeof(bloack_table_entry)* block_amount,1,fp);
  for(int i=0;i<block_amount;i++){
    toggle_endian(header.block[i].start_code);
    toggle_endian(header.block[i].end_code);

    //ブロック保持する文字コード数のサイズは可変なので各テーブルで
    //何文字分のデータを管理しているか把握しておく必要がある
    block_size[i]=char_2B_hex_minus(header.block[i].end_code,
         header.block[i].start_code)+1;
    //データ確認用
    // printf("%3d:",i);
    // printf("start=0x%2x%2x "
    //  ,(unsigned char)header.block[i].start_code[0]
    //  ,(unsigned char)header.block[i].start_code[1]
    // );
    //
    // printf("end  =0x%2x%2x "
    //   ,(unsigned char)header.block[i].end_code[0]
    //   ,(unsigned char)header.block[i].end_code[1]
    // );
    //
    // printf(" block size is %d\n",
    //   char_2B_hex_minus(header.block[i].end_code,
    //     header.block[i].start_code)+1);
    //

  }


  char test_letter[2] = {0x97,0x44};
  int block_index= block_potition(header.block,test_letter);
  //文字が存在しているブロックの先頭まで、何文字あったか確認する
  int base = count_letters_untill_block(block_size,block_index);

  //ブロックの先頭から何番目めに文字があるのか確認する
  int offset = char_2B_hex_minus(test_letter,header.block[block_index].start_code);

  int  tmp =HEADER_SIZE + tablesize * (sizeof(bloack_table_entry))
              + (base+offset) * (sizeof(font_data));

  printf("tmp is %d\n",tmp);
  fclose(fp);





// 憂憂    憂
// 憂憂  憂憂憂
// 憂  憂憂憂憂憂
// 憂憂  憂  憂
// 憂憂憂    憂憂
// 憂      憂
// 憂  憂憂憂憂憂


//   鬱  鬱  鬱
// 鬱鬱鬱  鬱鬱鬱
//   鬱鬱鬱鬱鬱
// 鬱鬱鬱鬱鬱  鬱
// 鬱鬱鬱鬱  鬱
//   鬱        鬱
//   鬱鬱鬱  鬱


//       犬  犬
//       犬
// 犬犬犬犬犬犬犬
//       犬
//       犬
//     犬  犬
// 犬犬      犬犬
//







}
int count_letters_untill_block(int block[tablesize],int block_index){
  int letter_amount=0;
  for(int i=0;i<block_index;i++){
    letter_amount+= block[i];
  }
  return letter_amount;
}

/**
 * ブロックテーブル内のどの位置に引数の文字が存在しているか調べる
 * @param  table  検索対象ブロックテーブル
 * @param  letter 検索対象文字
 * @return        テーブルにない時:-1,テーブルに存在した時:テーブルのindex
 */
int block_potition(bloack_table_entry* table,char letter[2]){
  for(int i=0;i<tablesize;i++){
    int smallest = comp_letter(letter,table[i].start_code);
    int biggest   = comp_letter(letter,table[i].end_code);
    if(smallest == TRUE && biggest == FALSE) return i;
  }
  return -1;
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

void char2Print(char v[2]){
  printf("%x%x\n",(unsigned char)v[0],(unsigned char)v[1]);

}
/**
 * 文字(2Byete=長さ2のchar配列の比較)
 * @param  v1 比較対象1
 * @param  v2 比較対象2
 * @return v1>v2のときtrue。それ以外false
 */
boolean comp_letter(char v1[2],char v2[2]){
  if(v1[0]>v2[0]){
    return TRUE;
  }else if(v1[0]==v2[0]){
    if(v1[1]>v2[1]){
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * char[2]のデータを16進数２桁とみなして減算をし、結果を10進数で返す
 *
 * minuend - subtrahend
 *
 * @param  minuend 被減数
 * @param  subtrahend 減数
 * @return difference 差分(減算結果)10進数
 */
int char_2B_hex_minus(char minuend[2],char subtrahend[2]){
  /**
   * 注意
   * char[2]は
   * char[0]=256の位
   * char[1]=1の位
   * として計算することに注意
   */
  return (((int)minuend[0])*256 + (int)minuend[1]) -
    (((int)subtrahend[0])*256 + (int)subtrahend[1]);
}
