// S. A. Z. P. L. E.
// A. D. III. CH. DEC. MMXII

#ifndef DitheringProjectus_ImageRead_h
#define DitheringProjectus_ImageRead_h



#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE unsigned char

int Jegop(int mit, int n);

int *PointerInteger(int x);
int **DoublePointerInteger(int x, int y);
double *PointerDouble(int x);
double **DoublePointerDouble(int x, int y);

int *IntegerPaddingVector(int x, int number);
int **IntegerPaddingMatrix(int x, int y, int number);

int **RawToMatrix(const char *FileName, int x, int y);
FILE *MatrixToRaw(const char *FileName, int **matrix, int x, int y);
FILE *WritingCodexInteger(const char *FileName, int **matrix, int x, int y);
FILE *WritingCodexDouble(const char *FileName, double **matrix, int x, int y);

int **RGBdistribution(int **ColourImage, const char *sorting, int x, int y);
int **RGBcomposition(int **Red, int **Green, int **Blue, int x, int y);

void Printingimage(int **matrix, int x, int y);
void Printingdouble(double **matrix, int x, int y);

int **ConvertDoubleToInteger(double **matrix, int x, int y);
double **ConvertIntegerToDouble(int **matrix, int x, int y);

int **DevideIntegerMatrix(int **matrix, int xStart, int yStart, int xSize, int ySize, int x, int y);
double **DevideDoubleMatrix(double **matrix, int xStart, int yStart, int xSize, int ySize, int x, int y);
void DistributionIntegerMatrix(int **SmallMatrix, int **BigMatrix, int xStart, int yStart, int xSize, int ySize, int x, int y);
void DistributionDoubleMatrix(double **SmallMatrix, double **BigMatrix, int xStart, int yStart, int xSize, int ySize, int x, int y);

void DestroyInteger(int **matrix, int x);
void DestroyDouble(double **matrix, int x);