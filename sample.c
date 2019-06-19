#include<stdio.h>
#include "font.h"
int main(){


  init_font();

  //char test_letter0[2] = {0x90,0xcc};

  char test_letters[12][2] ={
	  {0x94,0xfc},//美
	  {0x82,0xb5},//し
	  {0x82,0xa2},//い
	  {0x94,0xfc},//美 
	  {0x8d,0xe7},//咲
	  {0x83,0x74},//フ
	  {0x83,0x48},//ォ
	  {0x83,0x93},//ン
	  {0x83,0x67},//ト 
	  {0x82,0xcc},//の 
	  {0x90,0xa2},//世 
	  {0x8a,0x45} //界
  };
  for(int i=0;i<(int)sizeof(test_letters)/2;i++){
    char test_letter0[2];
    test_letter0[0] =  test_letters[i][0];
    test_letter0[1] =  test_letters[i][1];
    font_data print_test;
    get_font_data(test_letter0,&print_test);
    print_font(print_test);
  }
} 
