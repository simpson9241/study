#include "ImageRead.h"

//Integer 포인터 변수 생성
int *PointerInteger(int x)
{
    int *Output;
    Output = (int*)calloc(x, sizeof(int));
    return Output;
}

//Integer 이중 포인터 변수 생성
int **DoublePointerInteger(int x, int y)
{
    int **Output;
    Output = (int**)calloc(x, sizeof(int*));

    for (int i = 0 ; i < x; i++)
        Output[i] = (int*)calloc(y, sizeof(int));

    return Output;
}

//Double 포인터 변수 생성
double *PointerDouble(int x)
{
    double *Output;
    Output = (double*)calloc(x, sizeof(double));
    return Output;
}

//Double 이중 포인터 변수 생성
double **DoublePointerDouble(int x, int y)
{
    double **Output;
    Output = (double**)calloc(x, sizeof(double*));

    for (int i = 0 ; i < x; i++)
        Output[i] = (double*)calloc(y, sizeof(double));

    return Output;
}

//Integer 벡터 변수 생성
int *IntegerPaddingVector(int x, int number)
{
    int *output;
    output = (int*)malloc(x*sizeof(int));

    for (int i = 0 ; i < x; i++)
        output[i] = number;

    return output;
}

//Integer 매트릭스 변수 생성
int **IntegerPaddingMatrix(int x, int y, int number)
{
    int **output;
    output = (int**)malloc(x*(sizeof(int*)));

    for (int i = 0; i < x; i++)
        output[i] = IntegerPaddingVector(y, number);

    return output;
}

//파일을 매트릭스로 변환
int **RawToMatrix(const char *FileName, int x, int y)
{
    int **matrix = DoublePointerInteger(x, y);
    BYTE temp;

    FILE *input = fopen(FileName, "rb");

    if (input == NULL)
        printf("You Failed\n");

    for (int i = 0 ; i < x; i++)
        for (int j = 0 ; j < y; j++)
        {
            fread(&temp, sizeof(BYTE), 1, input);
            matrix[i][j] = (int)temp;
        }

    fclose(input);
    return matrix;
}

//매트릭스를 파일로 변환
FILE *MatrixToRaw(const char *FileName, int **matrix, int x, int y)
{
    BYTE temp;

    FILE *output = fopen(FileName, "wb");

    for (int i  = 0 ; i < x; i++)
        for (int j = 0 ; j < y; j++)
        {
            temp = (BYTE)matrix[i][j];
            fwrite(&temp, sizeof(BYTE), 1, output);
        }

    return output;
}

//Integer 매트릭스를 파일에 입력
FILE *WritingCodexInteger(const char *FileName, int **matrix, int x, int y)
{
    FILE *output = fopen(FileName, "wb");

    for (int i = 0 ; i < x; i++)
    {
        for (int j = 0 ; j < y; j++)
            fprintf(output, "%d ",matrix[i][j]);
        fprintf(output, "\n");
    }
    return output;
}

//Double 매트릭스를 파일에 입력
FILE *WritingCodexDouble(const char *FileName, double **matrix, int x, int y)
{
    FILE *output = fopen(FileName, "wb");

    for (int i = 0 ; i < x; i++)
    {
        for (int j = 0 ; j < y; j++)
            fprintf(output, "%f ",matrix[i][j]);
        fprintf(output, "\n");
    }
    return output;
}

//RGB를 각각 분할
int **RGBdistribution(int **ColourImage, const char *sorting, int x, int y)
{
    const char *r1 = "Red"; const char *r2 = "RED"; const char *r3 = "red";
    const char *g1 = "Green"; const char *g2 = "GREEN"; const char *g3 = "green";
    const char *b1 = "Blue"; const char *b2 = "BLUE"; const char *b3 = "blue";

    int **NonColour = DoublePointerInteger(x, y);

    if (sorting == r1 || sorting == r2 || sorting == r3)
    {
        for (int i = 0 ; i < x ; i++)
            for (int j = 0 ; j < y; j++)
                NonColour[i][j] = ColourImage[i][3*j];
    }
    else if (sorting == g1 || sorting == g2 || sorting == g3)
    {
        for (int i = 0 ; i < x ; i++)
            for (int j = 0 ; j < y; j++)
                NonColour[i][j] = ColourImage[i][3*j+1];
    }
    else if (sorting == b1 || sorting == b2 || sorting == b3)
    {
        for (int i = 0 ; i < x ; i++)
            for (int j = 0 ; j < y; j++)
                NonColour[i][j] = ColourImage[i][3*j+2];
    }

    else
        printf("Error");

    return NonColour;
}

//나누어져있는 RGB를 하나로 통
int **RGBcomposition(int **Red, int **Green, int **Blue, int x, int y)
{
    int ly = 3*y;
    int **Colour = DoublePointerInteger(x, ly);

    for (int i = 0 ; i < x; i++)
        for (int j = 0 ; j < y; j++)
        {
            Colour[i][3*j] = Red[i][j];
            Colour[i][3*j+1] = Green[i][j];
            Colour[i][3*j+2] = Blue[i][j];
        }

    return Colour;
}

//Image 출력하는 함수
void Printingimage(int **matrix, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0 ; j < y; j++)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
}

//Double 매트릭스 출력하는 함수
void Printingdouble(double **matrix, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0 ; j < y; j++)
            printf("%f ",matrix[i][j]);
        printf("\n");
    }
}

//Double 매트릭스를 Integer 매트릭스로 변환
int **ConvertDoubleToInteger(double **matrix, int x, int y)
{
    int **output = DoublePointerInteger(x, y);
    int **temp1 = DoublePointerInteger(x, y);
    double **temp2 = DoublePointerDouble(x, y);

    for (int i = 0 ; i < x; i++)
        for (int j = 0 ; j < y; j++)
        {
            temp1[i][j] = (int)matrix[i][j];
            temp2[i][j] = (double)temp1[i][j];

            if (matrix[i][j] - temp2[i][j] < 0.5)
                output[i][j] = temp1[i][j];
            else
                output[i][j] = temp1[i][j] + 1;
        }

    return output;
}

//Integer 매트릭스를 Double 매트릭스로 변
double **ConvertIntegerToDouble(int **matrix, int x, int y)
{
    double **output = DoublePointerDouble(x, y);

    for (int i = 0 ; i < x; i++)
        for (int j = 0 ; j < y; j++)
            output[i][j] = (double)matrix[i][j];

    return output;
}

//Integer 매트릭스에서 특정 매트릭스 부분 추출
int **DevideIntegerMatrix(int **matrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    int **output = DoublePointerInteger(xSize, ySize);

    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            output[i][j] = matrix[xStart+i][yStart+j];

    return output;
}

//Double 매트릭스에서 특정 매트릭스 부분 추출
double **DevideDoubleMatrix(double **matrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    double **output = DoublePointerDouble(xSize, ySize);

    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            output[i][j] = matrix[xStart+i][yStart+j];

    return output;
}

//Integer 매트릭스 2개를 받아와 하나를 다른 하나에 삽입
void DistributionIntegerMatrix(int **SmallMatrix, int **BigMatrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            BigMatrix[xStart+i][yStart+j] = SmallMatrix[i][j];
}

//Double 매트릭스 2개를 받아와 하나를 다른 하나에 삽입
void DistributionDoubleMatrix(double **SmallMatrix, double **BigMatrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            BigMatrix[xStart+i][yStart+j] = SmallMatrix[i][j];
}

//Integer 매트릭스 메모리 해제
void DestroyInteger(int **matrix, int x)
{
    for (int i = 0 ; i < x; i++)
    {
        free(matrix[i]);
        //matrix[i] = NULL;
    }
    free(matrix);
    //matrix = NULL;
}

//Double 매트릭스 메모리 해제
void DestroyDouble(double **matrix, int x)
{
    for (int i = 0 ; i < x; i++)
    {
        free(matrix[i]);
        //matrix[i] = NULL;
    }
    free(matrix);
    //matrix = NULL;
}
