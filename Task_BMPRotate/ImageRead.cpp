// S. A. Z. P. L. E.
// A. D. III. CH. DEC. MMXII

#include "ImageRead.h"

int Jegop(int mit, int n)
{
    int output;
    
    if (n == 0)
        return output = 1;
    else if (n == 1)
        return output = mit;
    else
        return output = mit*Jegop(mit, n-1);
}

int *PointerInteger(int x)
{
    int *Output;
    Output = (int*)calloc(x, sizeof(int));
    return Output;
}

int **DoublePointerInteger(int x, int y)
{
    int **Output;
    Output = (int**)calloc(x, sizeof(int*));
    
    for (int i = 0 ; i < x; i++)
        Output[i] = (int*)calloc(y, sizeof(int));
    
    return Output;
}

double *PointerDouble(int x)
{
    double *Output;
    Output = (double*)calloc(x, sizeof(double));
    return Output;
}

double **DoublePointerDouble(int x, int y)
{
    double **Output;
    Output = (double**)calloc(x, sizeof(double*));
    
    for (int i = 0 ; i < x; i++)
        Output[i] = (double*)calloc(y, sizeof(double));
    
    return Output;
}

int *IntegerPaddingVector(int x, int number)
{
    int *output;
    output = (int*)malloc(x*sizeof(int));
    
    for (int i = 0 ; i < x; i++)
        output[i] = number;
    
    return output;
}

int **IntegerPaddingMatrix(int x, int y, int number)
{
    int **output;
    output = (int**)malloc(x*(sizeof(int*)));
    
    for (int i = 0; i < x; i++)
        output[i] = IntegerPaddingVector(y, number);
    
    return output;
}

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

void Printingimage(int **matrix, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0 ; j < y; j++)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
}

void Printingdouble(double **matrix, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0 ; j < y; j++)
            printf("%f ",matrix[i][j]);
        printf("\n");
    }
}

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

double **ConvertIntegerToDouble(int **matrix, int x, int y)
{
    double **output = DoublePointerDouble(x, y);
    
    for (int i = 0 ; i < x; i++)
        for (int j = 0 ; j < y; j++)
            output[i][j] = (double)matrix[i][j];
    
    return output;
}

int **DevideIntegerMatrix(int **matrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    int **output = DoublePointerInteger(xSize, ySize);
    
    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            output[i][j] = matrix[xStart+i][yStart+j];
    
    return output;
}

double **DevideDoubleMatrix(double **matrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    double **output = DoublePointerDouble(xSize, ySize);
    
    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            output[i][j] = matrix[xStart+i][yStart+j];
    
    return output;
}

void DistributionIntegerMatrix(int **SmallMatrix, int **BigMatrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            BigMatrix[xStart+i][yStart+j] = SmallMatrix[i][j];
}

void DistributionDoubleMatrix(double **SmallMatrix, double **BigMatrix, int xStart, int yStart, int xSize, int ySize, int x, int y)
{
    for (int i = 0 ; i < xSize; i++)
        for (int j = 0 ; j < ySize; j++)
            BigMatrix[xStart+i][yStart+j] = SmallMatrix[i][j];
}

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


