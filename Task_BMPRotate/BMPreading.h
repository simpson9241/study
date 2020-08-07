#include <stdio.h>
#include <stdlib.h>
#include "ImageRead.h"

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD int
#define LONG unsigned int

#define Color 1
#define Monotonic 2

#pragma pack(push, 1)

typedef struct
{
	WORD  bf_Type;
	DWORD bf_Size;
	WORD  bf_Reserved1;
	WORD  bf_Reserved2;
	DWORD bf_OffBits;
} BITMAP_FILEHEADER;

typedef struct
{
   	DWORD bi_Size;
   	LONG  bi_Width;
   	LONG  bi_Height;
    WORD  bi_Planes;
    WORD  bi_BitCount;
  	DWORD bi_Compression;
  	DWORD bi_SizeImage;
  	LONG  bi_XPelsPerMeter;
  	LONG  bi_YPelsPerMeter;
   	DWORD bi_ClrUsed;
   	DWORD bi_ClrImportant;
} BITMAP_INFOHEADER;

typedef struct
{
	BYTE rgb_Blue;
	BYTE rgb_Green;
	BYTE rgb_Red;
	BYTE rgb_Reserved1;
} RGB_QUAD;

#pragma pack(pop)

typedef struct imageKind *ImageKind;

struct imageKind
{
    int Height;
    int Width;
    int Kind; // Sort = Color or Monotonic
};

ImageKind InitializeImageKind(void);

// BMP 이미지 -> Matrix
int **BMPtoMatrix(const char *BMP_FileName, ImageKind BMPImageKind);

// Matrix -> BMP 이미지
FILE *MatrixtoBMP(const char *BMP_FileName, int **Matrix, ImageKind BMPImageKind);
