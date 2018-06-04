#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>

//mutliplication code
int print_array_int(int *array, int length)
{
  for (int i = 0; i < length/2; i++) {
    int temp=array[7-i];
    array[7-i]=array[i];
    array[i]=temp;
  }
  return 0;
}

uint8_t ffmul(uint8_t ax, uint8_t bx){
  uint8_t i=0x01;
  uint8_t mx = (uint8_t)0x1B;//this is the polynomial
  int i1=1,not_zero=0;
  int chk[8];// stores the bitwise values in an integer array format
  uint8_t val[8];
  uint8_t res=0x00;//stores the result of the final computation
  while(i1<=8){
    chk[i1-1]=(bx&i)>>(i1-1);
    //initialize val[] by 0x0
    val[i1-1]=0x0;
    i=i<<1;
    i1++;
  }
  print_array_int(chk,8);

  while(chk[not_zero]!=1)
    not_zero++;
  //printf(" Not Zero:%d\n",not_zero);

uint8_t ax2=ax;
  for (int i = 1; i < (8-not_zero); i++) {
    //implementing finite field multiplication algorithm
    if((ax2>>7)==0x00){
      ax2=ax2<<1;
      val[7-i]=ax2;
    }
    else{
      ax2=ax2<<1;
      ax2=ax2^mx;
      val[7-i]=ax2;
    }
  }
val[7]=ax;
//now finally if there's a 1 in chk[index], if true we XOR it with
//the corresponding value at val[index], starting from 7 to not_zero
for(int i=not_zero;i<=7;i++){
  if(chk[i]==1){
    //printf("i=%d\n",i);
    res=res^val[i];
  }
}
  return (res);
}
//multiplication part ends here

//printing any uint8_t array
int print_array_uint8(uint8_t *array, int length)
{
  //printf("\nPrinting array val:");
  for (int i = 0; i < length;i++){
    printf("%x ",array[i]);
  }
  //printf("\n");
  return 0;
}
//printing finished

//performs table lookup for ByteSubstitution
uint8_t bsub1(uint8_t val){
  uint8_t s[256] =
 {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
 };

 return s[val];
}

//rotate array once
void leftRotatebyOne(uint8_t temp[], int n)//n is the length of arr[]
{
  int i;
  uint8_t swap;
  swap = temp[0];
  for (i = 0; i < n-1; i++)
     temp[i] = temp[i+1];
  temp[i] = swap;
}

uint8_t* leftRotMain(uint8_t temp[], int d, int n){// d is the number of times, n is the length

  int i;
  for (i = 0; i < d; i++)
    leftRotatebyOne(temp, n);
  return temp;
}
//rotation finished
//copy array from right to left array
void copyArr(uint8_t l[], uint8_t r[]){
  for(int i = 0; i<4; i++)
    l[i] = r[i];
}
//copying finished
//XOR array i.e right array to left array and store in left array
void XORArr(uint8_t l[], uint8_t r[]){
  for(int i = 0; i<4; i++)
    l[i] = r[i] ^ l[i];
}
//XORing finished
//word generation starts here---------------------------------------------------
int word_gen(uint8_t w_i0[],uint8_t w_i1[],uint8_t w_i2[],uint8_t w_i3[], int round,uint8_t RC[]){
  //uint8_t temp_wi0[4];
  uint8_t temp_G_wi3[4];
  uint8_t w_i4[4];
  //int round hasnt been used yet
  //uint8_t w_i5[4];
  //uint8_t w_i6[4];
  //uint8_t w_i7[4];
  //now we rotate w_i3 and store along with ByteSubstitution
  //first assign w_i3 to temp_G_wi3 and do ByteSubstitution
  //now rotate temp_G_wi3 once, from left
  for(int i = 0;i<4;i++){
    temp_G_wi3[i] = w_i3[i];//change of PLANS, first store value, then rotate, then ByteSubstitution
  }
  uint8_t *temp2 = leftRotMain(temp_G_wi3,1,4);//rotate temp_G_wi3 array 1 time, of 4 length
  for(int i = 0;i<4;i++){
    temp_G_wi3[i] = *(temp2 + i);
  }
//leftRotatebyOne(temp_G_wi3,4);
for(int i = 0; i<4; i++){
  temp_G_wi3[i] = bsub1(temp_G_wi3[i]);
}
//now XOR temp_G_wi3 bytes with corresponding RCON_temp bytes and store in former
//for(int i = 0;i<4;i++){
  //temp_G_wi3[i] = *(temp2 + i);
  //temp_G_wi3[i] = temp_G_wi3[i] ^ RCON_temp[i];//can be substituted with XORArr()
  temp_G_wi3[0] = temp_G_wi3[0] ^ RC[round];
//}
//g(Wi+3) is ready, now calculate Wi+4
XORArr(temp_G_wi3,w_i0);
copyArr(w_i4,temp_G_wi3);//w_i4 is generated and stored, will be stored in w_i0 in the end
//now calculate w_i5
XORArr(w_i1,w_i4);//w_i5 is generated and stored, will be stored in w_i1 in the end
XORArr(w_i2,w_i1);//w_i6 is generated and stored, will be stored in w_i2 in the end
XORArr(w_i3,w_i2);//w_i7 is generated and stored, will be stored in w_i3 in the end
copyArr(w_i0,w_i4);
return 0;
}

//word generation ends here-----------------------------------------------------
//copy the words to the final[] array
int copy_final(uint8_t final[][16],uint8_t w_i0[],uint8_t w_i1[],uint8_t w_i2[],uint8_t w_i3[],int rown){
int j=0;
for(int i = 0; i<4;i++)
  final[rown][j++] = w_i0[i];
for(int i = 0; i<4;i++)
  final[rown][j++] = w_i1[i];
for(int i = 0; i<4;i++)
  final[rown][j++] = w_i2[i];
for(int i = 0; i<4;i++)
  final[rown][j++] = w_i3[i];

  return 0;
}

//copying ends

//printing final[][]for debugging and checking
void print_final(uint8_t final[11][16]){
  printf("CHECK!!\n");
  for(int i = 0;i<11;i++){
    for(int j = 0;j<16;j++){
      printf("%x ",final[i][j]);
    }
    printf("\n");
  }
}
 int main() {
  uint8_t k[16] =
  {
    0x00,0x04,0x08,0x0c,
    0x01,0x05,0x09,0x0d,
    0x02,0x06,0x0a,0x0e,
    0x03,0x07,0x0b,0x0f
  };

  uint8_t RCON[4][11];//stores the RCON for every round
  uint8_t w_i0[4] = {0x00,0x01,0x02,0x03};
  uint8_t w_i1[4] = {0x04,0x05,0x06,0x07};
  uint8_t w_i2[4] = {0x08,0x09,0x0a,0x0b};
  uint8_t w_i3[4] = {0x0c,0x0d,0x0e,0x0f};//stores the first 4 words

  uint8_t final[11][16];
  copy_final(final,w_i0,w_i1,w_i2,w_i3,0);//this function copies the 4 words to the final array,0 is the row number
  int j = 2;
  uint8_t RC[11];
  RC[0] = 0x00;//ignore this one, start from RC[1]
  RC[1] = 0x01;
  while(j <= 10){
    RC[j] = ffmul(0x02,RC[j-1]);
     j++;//increment j for next RC index
  }
//printing RC[] to check if algorithm is working, checked fine, so should be RCON[][]
print_array_uint8(RC,11);
//now creat RCON[]
RCON[0][0] = 0x01;
RCON[1][0] = 0x00;
RCON[2][0] = 0x00;
RCON[3][0] = 0x00;
for(int i = 1;i<=10;i++){
  RCON[0][i] = RC[i];
  RCON[1][i] = 0x00;
  RCON[2][i] = 0x00;
  RCON[3][i] = 0x00;
}

//for every round we expand the key every time, we start off with the key k for round 0, then from Round1 to  Round10
printf("\nROUND0 key:\n");
print_array_uint8(w_i0,4);
print_array_uint8(w_i1,4);
print_array_uint8(w_i2,4);
print_array_uint8(w_i3,4);
printf("\n");//start printing the next round keys
for(int i = 1;i<=10;i++){

  //uint8_t RCON_temp[4] ={ RCON[0][i-1],RCON[1][i-1],RCON[2][i-1],RCON[3][i-1]};
  //send this array for processing next word
  //word_gen(w_i0,w_i1,w_i2,w_i3,i,RCON_temp);
  word_gen(w_i0,w_i1,w_i2,w_i3,i,RC);
  printf("ROUND%d key:\n",i);

  print_array_uint8(w_i0,4);
  print_array_uint8(w_i1,4);
  print_array_uint8(w_i2,4);
  print_array_uint8(w_i3,4);

  copy_final(final,w_i0,w_i1,w_i2,w_i3,i);

  printf("\n");
}
print_final(final);
//store the final array
  return 0;
}
