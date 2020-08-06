// A. D. VIII EID. IAN.
// S. A. Z. P. L. E.

#include <iostream>
#include "ImageRead.h"
#include "BMPreading.h"

#define W_FullHD 1920
#define H_FullHD 1080

int main()
{
    // 컬러
    ImageKind ImageCharacteristic1 = InitializeImageKind();
    ImageKind ImageCharacteristic2 = InitializeImageKind();

    int **Image = BMPtoMatrix("Annick.bmp", ImageCharacteristic1);
    int **Image_Monotonic = DoublePointerInteger(ImageCharacteristic1->Height, ImageCharacteristic1->Width);

    // 컬러 이미지 -> 흑백 이미지 만들기
    for (int i = 0; i < ImageCharacteristic1->Height; i++)
        for (int j = 0; j < ImageCharacteristic1->Width; j++)
            Image_Monotonic[i][j] = (Image[i][3*j] + Image[i][j*3+1] + Image[i][3*j+2])/3;

    // 흑백 이미지 프로파일 만들기
    ImageCharacteristic2->Width = ImageCharacteristic1->Width;
    ImageCharacteristic2->Height = ImageCharacteristic1->Height;
    ImageCharacteristic2->Kind = Monotonic;
    // 컬러저장
    FILE *output1 = MatrixtoBMP("Annick_color.bmp", Image, ImageCharacteristic1); fclose(output1);
    // 흑백저장
    FILE *output2 = MatrixtoBMP("Annick_monotonic.bmp", Image_Monotonic, ImageCharacteristic2); fclose(output2);
}
