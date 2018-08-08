#include<stdio.h>
#include<stdlib.h>
#include "font.h"

int main(){
  FILE *fp;
  char *filename = "MISAKI.FNT";

  /*fnt file open*/
  if((fp = fopen(filename,"r"))==NULL){
    fprintf(stderr,"%s open faild.\n",filename);
    exit(EXIT_FAILURE);
  }
  char c;
  for(int i=0;i<12;i++){
    c = fgetc(fp);
    printf("%c\n",c);
  }
  fclose(fp);
}
