#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// First try on reading.... C-style!
int main(){

FILE *fp;
float * buffer; // 1d 200-element array to read file contents
float ** data; // 2d array to store contents
size_t result;

// read data C style!
fp = fopen("dataset/data", "rb");
if (fp==NULL) {fputs("file error", stderr);}

buffer = (float*) malloc(sizeof(float*)*200);
if (buffer == NULL) {fputs("Memory error", stderr);}
result = fread(buffer, 4, 200, fp);
if (result != 200) {fputs("reading error", stderr);}

data = (float **) malloc(sizeof(float *)*100);
for (int i=0; i<100; i++){
  data[i] = (float *) malloc(sizeof(float) *2);
}
// store data
for (int i=0; i<100;i++){
  for (int j=0; j<2;j++){
    data[i][j] = buffer[i*2 + j];
  }
}

std::cout << buffer[1] << std::endl;
std::cout << data[1][0] << std::endl;

fclose(fp);
free(buffer);
return 0;
}

