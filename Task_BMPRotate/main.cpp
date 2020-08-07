#include <iostream>
#include <math.h>
#include "ImageRead.h"
#include "BMPreading.h"

#define pi 3.141592653589793238462643383279
#define W_FullHD 1920
#define H_FullHD 1080

void rotation(int **InputImage,int **OutputImage, double Degree, int Width, int Height){
  int x,y;
  int original_x,original_y;
  int pixel;
  double radian = Degree*pi/180.0;
  double cc=cos(radian),ss=sin(-radian);
  double xcenter=(double)Width/2.0,ycenter=(double)Height/2.0;

  for(y=0;y<Height;y++){
    for(x=0;x<Width;x++){
      original_x=(int)(xcenter+((double)y-ycenter)*ss+((double)x-xcenter)*cc);
      original_y=(int)(ycenter+((double)y-ycenter)*cc-((double)x-xcenter)*ss);
      pixel=0;//빈 공간은 검정으로 채움

      if((original_y>=0&&original_y<Height)&&(original_x>=0&&original_x<Width))
        pixel=InputImage[original_y][original_x];
      OutputImage[y][x]=pixel;

    }
  }

}

int main()
{
    // 컬러
    ImageKind ImageCharacteristic1 = InitializeImageKind();//이미지 형식에 관한 정보를 받을 변수 생성
    // ImageKind ImageCharacteristic2 = InitializeImageKind();

    int **Image = BMPtoMatrix("Annick.bmp", ImageCharacteristic1);//Input
    // int **Image2 = BMPtoMatrix("Annick.bmp", ImageCharacteristic1);

    //받아온 이미지를 RGB 각각으로 나누는 작업
    int **Image_R=DoublePointerInteger(ImageCharacteristic1->Height,ImageCharacteristic1->Width);
    int **Image_G=DoublePointerInteger(ImageCharacteristic1->Height,ImageCharacteristic1->Width);
    int **Image_B=DoublePointerInteger(ImageCharacteristic1->Height,ImageCharacteristic1->Width);
    int i,j;
    for(i=0;i<ImageCharacteristic1->Height;i++){
      for(j=0;j<ImageCharacteristic1->Width*3;j++){
        if(j%3==0){
          Image_R[i][j/3]=Image[i][j];
        }else if(j%3==1){
          Image_G[i][j/3]=Image[i][j];
        }else{
          Image_B[i][j/3]=Image[i][j];
        }
      }
    }


    //Output 생성
    int **Image2= DoublePointerInteger(ImageCharacteristic1->Height,ImageCharacteristic1->Width*3);

    int **Image2_R=DoublePointerInteger(ImageCharacteristic1->Height,ImageCharacteristic1->Width);
    int **Image2_G=DoublePointerInteger(ImageCharacteristic1->Height,ImageCharacteristic1->Width);
    int **Image2_B=DoublePointerInteger(ImageCharacteristic1->Height,ImageCharacteristic1->Width);

    //RGB 각각 Rotation 함수 적용
    rotation(Image_R,Image2_R,270,ImageCharacteristic1->Width,ImageCharacteristic1->Height);
    rotation(Image_G,Image2_G,270,ImageCharacteristic1->Width,ImageCharacteristic1->Height);
    rotation(Image_B,Image2_B,270,ImageCharacteristic1->Width,ImageCharacteristic1->Height);

    //RGB 합치는 작업
    for(i=0;i<ImageCharacteristic1->Height;i++){
      for(j=0;j<ImageCharacteristic1->Width*3;j++){
        if(j%3==0){
          Image2[i][j]=Image2_R[i][j/3];
        }else if(j%3==1){
          Image2[i][j]=Image2_G[i][j/3];
        }else{
          Image2[i][j]=Image2_B[i][j/3];
        }
      }
    }

    // rotation(Image,Image2,90,ImageCharacteristic1->Width*3,ImageCharacteristic1->Height);
    // int **Image_Monotonic = DoublePointerInteger(ImageCharacteristic1->Height, ImageCharacteristic1->Width);

    // 컬러 이미지 -> 흑백 이미지 만들기
    // for (int i = 0; i < ImageCharacteristic1->Height; i++)
    //     for (int j = 0; j < ImageCharacteristic1->Width; j++)
    //         Image_Monotonic[i][j] = (Image[i][3*j] + Image[i][j*3+1] + Image[i][3*j+2])/3;

    // 흑백 이미지 프로파일 만들기
    // ImageCharacteristic2->Width = ImageCharacteristic1->Width;
    // ImageCharacteristic2->Height = ImageCharacteristic1->Height;
    // ImageCharacteristic2->Kind = Monotonic;
    // 컬러저장
    FILE *output1 = MatrixtoBMP("Annick_result.bmp", Image2, ImageCharacteristic1); fclose(output1);//Output
    // 흑백저장
    // FILE *output2 = MatrixtoBMP("Annick_monotonic.bmp", Image_Monotonic, ImageCharacteristic2); fclose(output2);
}
