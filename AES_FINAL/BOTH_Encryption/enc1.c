#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>

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

//rotate array d times, length n
uint8_t* leftRotMain(uint8_t temp[], int d, int n){// d is the number of times, n is the length

  int i;
  for (i = 0; i < d; i++)
    leftRotatebyOne(temp, n);
  return temp;
}

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

int mixcoln(uint8_t S1[]){
  uint8_t S2[16];//output array
  uint8_t S_2[16];//checking output array, will be returned
  for(int i = 0 ; i <= 3; i++){
    S2[0*4+i] = ffmul(0x02,S1[0*4+i])^ffmul(0x03,S1[1*4+i])^S1[2*4+i]^S1[3*4+i];
    S2[1*4+i] = S1[0*4+i]^ffmul(0x02,S1[1*4+i])^ffmul(0x03,S1[2*4+i])^S1[3*4+i];
    S2[2*4+i] = S1[0*4+i]^S1[1*4+i]^ffmul(0x02,S1[2*4+i])^ffmul(0x03,S1[3*4+i]);
    S2[3*4+i] = ffmul(0x03,S1[0*4+i])^S1[1*4+i]^S1[2*4+i]^ffmul(0x02,S1[3*4+i]);
  }
  for(int i = 0;i < 16;i++)
    {
      S1[i] = S2[i];// I will store the final array in the initArr array itself, which is S1[] in mixcoln
      printf("%x ",S2[i]); //FINAL OUTPUT FROM MIXCOLUMNS OPERATION
      if(i==3 || i==7 || i==11 || i==15){printf("\n");}
    }
    printf("\n");
    printf(" NOW GOING FOR NEXT S_2:\n");
    S_2[0] = S2[0];   S_2[1] = S2[4];   S_2[2] = S2[8];     S_2[3] = S2[12];
    S_2[4] = S2[1];   S_2[5] = S2[5];   S_2[6] = S2[9];     S_2[7] = S2[13];
    S_2[8] = S2[2];   S_2[9] = S2[6];   S_2[10] = S2[10];   S_2[11] = S2[14];
    S_2[12] = S2[3];  S_2[13] = S2[7];  S_2[14] = S2[11];   S_2[15] = S2[15];
    for(int i = 0;i < 16;i++)
      {
        printf("%x ",S_2[i]);
      }printf("\n");
return 0;
}
//multiplication part ends here

 int main() {
//lets consider key k of 128 bits, say uint8_t k[16], Nr=10,state=4*4*8=128,Nb=4(where 4*32=128)
//uint8_t check = bsub1(0x53);//worked, 0xED returned
//000102030405060708090a0b0c0d0e0f is the key k[]
//00112233445566778899aabbccddeeff is the plaintext pt[]

uint8_t pt[16]=
{
  0x00,0x44,0x88,0xcc,
  0x11,0x55,0x99,0xdd,
  0x22,0x66,0xaa,0xee,
  0x33,0x77,0xbb,0xff
};


uint8_t k[16]=
{
  0x00,0x04,0x08,0x0c,
  0x01,0x05,0x09,0x0d,
  0x02,0x06,0x0a,0x0e,
  0x03,0x07,0x0b,0x0f
};

 /*uint8_t initArr[16] = //page40 'start' of round 1
  {
    0x00,0x40,0x80,0xC0,// reordered according to paper, page13
    0x10,0x50,0x90,0xD0,
    0x20,0x60,0xA0,0xE0,
    0x30,0x70,0xB0,0xF0
  };*/
  uint8_t initArr[16];

  for(int i = 0;i<16; i++)
    initArr[i] = pt[i] ^ k[i];

  //we do ByteSubstitution and Shift Rows at the same time
  initArr[0] = bsub1(initArr[0]);
  initArr[1] = bsub1(initArr[1]);
  initArr[2] = bsub1(initArr[2]);
  initArr[3] = bsub1(initArr[3]);
  for(int i = 4;i<=12;i = i + 4){
    if(i == 4){
      uint8_t temp[4] = {
        initArr[4],initArr[5],initArr[6],initArr[7]
      };

      uint8_t *temp2 = leftRotMain(temp,1,4);//rotate temp 1 time, length is 4, not necessary, temp[] itself will hold the changes
      initArr[4] = bsub1(*(temp2 + 0));
      initArr[5] = bsub1(*(temp2 + 1));
      initArr[6] = bsub1(*(temp2 + 2));
      initArr[7] = bsub1(*(temp2 + 3));
    }
    if(i == 8){
      uint8_t temp[4] = {
        initArr[8],initArr[9],initArr[10],initArr[11]
      };
      uint8_t *temp2 = leftRotMain(temp,2,4);//rotate temp 2 time, length is 4
      initArr[8] = bsub1(*(temp2 + 0));
      initArr[9] = bsub1(*(temp2 + 1));
      initArr[10] = bsub1(*(temp2 + 2));
      initArr[11] = bsub1(*(temp2 + 3));
    }
    if(i == 12){
      uint8_t temp[4] = {
        initArr[12],initArr[13],initArr[14],initArr[15]
      };
      uint8_t *temp2 = leftRotMain(temp,3,4);//rotate temp 3 time, length is 4
      initArr[12] = bsub1(*(temp2 + 0));
      initArr[13] = bsub1(*(temp2 + 1));
      initArr[14] = bsub1(*(temp2 + 2));
      initArr[15] = bsub1(*(temp2 + 3));
    }
  }
  mixcoln(initArr);

  //now we do AddRoundKey
return 0;
}
