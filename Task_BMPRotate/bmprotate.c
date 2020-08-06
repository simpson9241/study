#include <stdio.h>

typedef struct tagBitMapFileHeader{
  WORD bfType;//"BM"이라는 글자가 설정됨
  DWORD bfSize;//비트맵 파일의 전체 크기
  WORD bfReserved1;//예약변수
  WORD bfReserved2;//예약변수
  DWORD bfOffBits;//파일에서 비트맵 데이터가 있는 위치
}bitmapfileheader;

typedef struct tagBitMapInfoHeader{
  DWORD bitSize; //구조체의 크기
  LONG bitWidth;//비트맵의 가로 길이
  LONG bitHeight;//비트맵의 세로 길이
  WORD bitPlanes;//plane 수(1로 설정)
  WORD bitCount;//한 픽셀당 비트수
  DWORD bitCompression;// 압축 유무 플래그
  DWORD bitSizeImage;//그림 데이터의 크기
  LONG bitXPixPerMeter;//한 픽셀당 가로 미터
  LONG bitYPixPerMeter;//한 픽셀당 세로 미터
  DWORD bitColorUsed;//그림에서 실제 사용되는 컬러 수
  DWORD bitColorImportant;//중요하게 사용되는 컬러
}bitmapinfoheader;

typedef struct tagRGBQUAD{
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
}rgb;

int main(){
  FILE *file;
  file=open("sample.bmp",0_RDONLY);
  if(file=NULL){
    printf("No Image File");
    return;
  }
  //BMP Header Info

}
