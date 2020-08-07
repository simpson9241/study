#include "BMPreading.h"

#define WIDTHBYTES(bits) ( ( (bits)+31 )/32 * 4 )

//Image 형식 받을 변수 생성
ImageKind InitializeImageKind(void)
{
    ImageKind IK;

    IK = (struct imageKind*)malloc(sizeof(imageKind));

    IK->Height = 0;
    IK->Width = 0;
    IK->Kind = 0;

    return IK;
}

//Bitmap 형식의 파일을 Matrix 로 변환하는 함수
int **BMPtoMatrix(const char *BMP_FileName, ImageKind BMPImageKind)
{
    int **Matrix = NULL;

    BITMAP_FILEHEADER fileInformation;
    BITMAP_INFOHEADER imageInformation;
    RGB_QUAD paletteInformation[256];

    FILE *input = fopen(BMP_FileName, "rb");

    if (input == NULL)
        printf("파일 없음\n");

    fread(&fileInformation, sizeof(BITMAP_FILEHEADER), 1, input);
    fread(&imageInformation, sizeof(BITMAP_INFOHEADER), 1, input);

    // Let`s check the values of two headers
    /*printf("buffer Type : %d\n",fileInformation.bf_Type);
    printf("buffer Size : %d\n",fileInformation.bf_Type);
    printf("buffer Reserved1 : %d\n",fileInformation.bf_Reserved1);
    printf("buffer Reserved2 : %d\n",fileInformation.bf_Reserved2);
    printf("buffer OffBits : %d\n",fileInformation.bf_OffBits);

    printf("Image Size : %d\n",imageInformation.bi_Size);
    printf("Image Width : %d\n",imageInformation.bi_Width);
    printf("Image Height : %d\n",imageInformation.bi_Height);
    printf("Image Planes : %d\n",imageInformation.bi_Planes);
    printf("Image BitCount : %d\n",imageInformation.bi_BitCount);
    printf("Image Compression : %d\n",imageInformation.bi_Compression);
    printf("Image SizeImage : %d\n",imageInformation.bi_SizeImage);
    printf("Image XPelsPerMeter : %d\n",imageInformation.bi_XPelsPerMeter);
    printf("Image YPelsPerMeter : %d\n",imageInformation.bi_YPelsPerMeter);
    printf("Image ClrUsed : %d\n",imageInformation.bi_ClrUsed);
    printf("Image ClrImportant : %d\n",imageInformation.bi_ClrImportant);*/

    BMPImageKind->Width = imageInformation.bi_Width;
    BMPImageKind->Height = imageInformation.bi_Height;

    // Colour (컬러)
    //24비트 형식일 때
    if (imageInformation.bi_BitCount == 24)
    {
        printf("Colorful Image. Width : %d   Height : %d\n",imageInformation.bi_Width, imageInformation.bi_Height);

        Matrix = DoublePointerInteger(imageInformation.bi_Height, imageInformation.bi_Width*3);

        int WidthData = WIDTHBYTES(imageInformation.bi_BitCount*imageInformation.bi_Width);
        BYTE *Buffer = (BYTE*)malloc(sizeof(BYTE)*imageInformation.bi_SizeImage);

        fread(Buffer, sizeof(BYTE), imageInformation.bi_SizeImage, input);
        int BitDifference = fileInformation.bf_OffBits - 54;


        if (BitDifference > 0) // When Offset Bits of File Information is not 54.
        {
            BYTE *temp = (BYTE*)malloc(sizeof(BYTE)*BitDifference); // Position Change를 위한 코드

            for (int i = 0 ; i < imageInformation.bi_Height; i++)
            {
                for (int j = 0 ; j < BitDifference; j++)
                    temp[j] = Buffer[WidthData*i+j];
                for (int j = 0 ; j < WidthData-BitDifference; j++)
                    Buffer[WidthData*i+j] = Buffer[WidthData*i+j+BitDifference];
                for (int j = 0 ; j < BitDifference; j++)
                    Buffer[WidthData*i+(WidthData-BitDifference)+j] = temp[j];
            }

        }

        for (int i = 0 ; i < imageInformation.bi_Height; i++)
            for (int j = 0 ; j < imageInformation.bi_Width; j++)
            {
                Matrix[imageInformation.bi_Height-1-i][3*j+2] = (int)Buffer[WidthData*i+3*j];
                Matrix[imageInformation.bi_Height-1-i][3*j+1] = (int)Buffer[WidthData*i+3*j+1];
                Matrix[imageInformation.bi_Height-1-i][3*j+0] = (int)Buffer[WidthData*i+3*j+2];
            }

        BMPImageKind->Kind = Color;

        free(Buffer); Buffer = NULL;
    }

    // Monotonic (흑백)
    else if (imageInformation.bi_BitCount == 8)
    {
        fread(paletteInformation, sizeof(RGB_QUAD), 256, input);

        Matrix = DoublePointerInteger(imageInformation.bi_Height, imageInformation.bi_Width);
        printf("Monotonique Image. Width : %d   Height : %d\n",imageInformation.bi_Width, imageInformation.bi_Height);

        int WidthData = WIDTHBYTES(imageInformation.bi_BitCount*imageInformation.bi_Width);
        BYTE *Buffer = (BYTE*)malloc(sizeof(BYTE)*imageInformation.bi_SizeImage);
        fread(Buffer, sizeof(BYTE), imageInformation.bi_SizeImage, input);
        //int BitDifference = fileInformation.bf_OffBits - 54;

        for (int i = 0 ; i < imageInformation.bi_Height; i++)
        {
            /*
            for (int j = 0 ; j < BitDifference; j++)
                Matrix[imageInformation.bi_Height-1-i][imageInformation.bi_Width-BitDifference+j] = (int)Buffer[imageInformation.bi_Width*i+j];
            for (int j = 0 ; j < imageInformation.bi_Width-BitDifference; j++)
                Matrix[imageInformation.bi_Height-1-i][j] = (int)Buffer[imageInformation.bi_Width*i+j+BitDifference];
             */
            for (int j = 0 ; j < WidthData; j++)
                Matrix[imageInformation.bi_Height-1-i][j] = (int)Buffer[WidthData*i+j];
        }

        BMPImageKind->Kind = Monotonic;
        free(Buffer); Buffer = NULL;
    }
    else
        printf("Image is neither Color nor Monotonique\n");


    return Matrix;
}

FILE *MatrixtoBMP(const char *BMP_FileName, int **Matrix, ImageKind BMPImageKind)
{
    FILE *output = fopen(BMP_FileName, "wb");

    BITMAP_FILEHEADER fileInformation;
    BITMAP_INFOHEADER imageInformation;
    //RGB_QUAD *paletteInformation;

    if (BMPImageKind->Kind == Color)
    {
        fileInformation.bf_Type = 19778;
        fileInformation.bf_Size = 19778;
        fileInformation.bf_Reserved1 = 0;
        fileInformation.bf_Reserved2 = 0;
        fileInformation.bf_OffBits = 54;

        imageInformation.bi_Size = 40;
        imageInformation.bi_Width = BMPImageKind->Width;
        imageInformation.bi_Height = BMPImageKind->Height;
        imageInformation.bi_Planes = 1;
        imageInformation.bi_BitCount = 24;
        imageInformation.bi_Compression = 0;
        imageInformation.bi_SizeImage = 3*BMPImageKind->Width*BMPImageKind->Height;
        imageInformation.bi_XPelsPerMeter = 2834;
        imageInformation.bi_YPelsPerMeter = 2834;
        imageInformation.bi_ClrUsed = 0;
        imageInformation.bi_ClrImportant = 0;

        int WidthData = WIDTHBYTES(imageInformation.bi_BitCount*imageInformation.bi_Width);
        BYTE *Buffer = (BYTE*)malloc(sizeof(BYTE)*WidthData*imageInformation.bi_Height);

        for (int i = 0 ; i < imageInformation.bi_Height; i++)
            for (int j = 0 ; j < imageInformation.bi_Width; j++)
            {
                Buffer[WidthData*i+3*j+0] = (BYTE)Matrix[imageInformation.bi_Height-1-i][3*j+2];
                Buffer[WidthData*i+3*j+1] = (BYTE)Matrix[imageInformation.bi_Height-1-i][3*j+1];
                Buffer[WidthData*i+3*j+2] = (BYTE)Matrix[imageInformation.bi_Height-1-i][3*j+0];
            }

        fwrite(&fileInformation, sizeof(BYTE), sizeof(BITMAP_FILEHEADER), output);
        fwrite(&imageInformation, sizeof(BYTE), sizeof(BITMAP_INFOHEADER), output);
        fwrite(Buffer, sizeof(BYTE), WidthData*imageInformation.bi_Height, output);

        free(Buffer); Buffer = NULL;

    }

    else if (BMPImageKind->Kind == Monotonic)
    {
        RGB_QUAD paletteInformation[256]; //BYTE temp_r, temp_g, temp_b;

        for (int i = 0; i < 256; i++)
        {
            paletteInformation[i].rgb_Red = i;
            paletteInformation[i].rgb_Green = i;
            paletteInformation[i].rgb_Blue = i;
            paletteInformation[i].rgb_Reserved1 = 256;
        }

        fileInformation.bf_Type = 19778;
        fileInformation.bf_Size = 19778;
        fileInformation.bf_Reserved1 = 0;
        fileInformation.bf_Reserved2 = 0;
        fileInformation.bf_OffBits = 54;

        imageInformation.bi_Size = 40;
        imageInformation.bi_Width = BMPImageKind->Width;
        imageInformation.bi_Height = BMPImageKind->Height;
        imageInformation.bi_Planes = 1;
        imageInformation.bi_BitCount = 8;
        imageInformation.bi_Compression = 0;
        imageInformation.bi_SizeImage = BMPImageKind->Width*BMPImageKind->Height;
        imageInformation.bi_XPelsPerMeter = 2834;
        imageInformation.bi_YPelsPerMeter = 2834;
        imageInformation.bi_ClrUsed = 256;
        imageInformation.bi_ClrImportant = 0;

        int WidthData = WIDTHBYTES(imageInformation.bi_BitCount*imageInformation.bi_Width);
        BYTE *Buffer = (BYTE*)malloc(sizeof(BYTE)*WidthData*imageInformation.bi_Height);

        for (int i = 0 ; i < imageInformation.bi_Height; i++)
            for (int j = 0 ; j < imageInformation.bi_Width; j++)
                Buffer[WidthData*i+j] = (BYTE)Matrix[imageInformation.bi_Height-1-i][j];

        fwrite(&fileInformation, sizeof(BYTE), sizeof(BITMAP_FILEHEADER), output);
        fwrite(&imageInformation, sizeof(BYTE), sizeof(BITMAP_INFOHEADER), output);
        fwrite(paletteInformation, sizeof(RGB_QUAD), 256, output);
        fwrite(Buffer, sizeof(BYTE), WidthData*imageInformation.bi_Height, output);

        free(Buffer); Buffer = NULL;
    }

    return output;
}
