#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Use more libraries as necessary

char ** ReadAndParseFile(FILE *fp, int numberOfRows, char ** inputBuffer);
double * valuesSplit(char ** inputBuffer, int numberOfValues, int numRows);
int main (int argc, char *argv[])
{
    if( argc != 7)
    {
        printf("USE LIKE THIS: serial_mult_mat_vec file_1.csv n_row_1 n_col_1 file_2.csv n_row_2 outputfile.csv \n");
        return EXIT_FAILURE;
    }

    // This code can help you to read the csv input files
    // and other parameters

    FILE *inputFile1;
    FILE *inputFile2;

    char* p1;
    char* p2;

    inputFile1 = fopen(argv[1], "r");
    // the number of rows of the input matrix
    int n_row1 = strtol(argv[2], &p1, 10 );
    // the number of cols of the input matrix
    int n_col1 = strtol(argv[3], &p2, 10 );
    // the vector file that we will multiply against the input matrix
    inputFile2 = fopen(argv[4], "r");

    char* p3;
    int n_row2 = strtol(argv[5], &p3, 10 );


    FILE *outputFile;
    outputFile = fopen(argv[6], "w");


    // Code for allocation of Matrix
    // This reference may be useful
	// We suggest using data type double
    // https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

    // TODO:
    // Code for processing csv files
    // Perform matrix vector multiplication
    // and write to csv file 
    char  ** bufInput1;
    char ** bufInput2;
    double * valuesBuffer1;
    double * valuesBuffer2;
    char * endPtr;
    double value;
    int postionInBuf1 = 0;
    int postionInBuf2 = 0;
    int postionOutputBuf = 0;
    double * outputBuf;
    int nextLocation = 0 ;
    //allocate memory for data structure that will be holding each line of the file seperatley
    bufInput1 = (char **) malloc(n_row1 * sizeof(char *));
    bufInput2 = (char  **) malloc(n_row2 * sizeof(char *)); 
    // this data structure will hold all the values formmated post splliting the array of strings read in.
    valuesBuffer1 = (double * ) malloc(n_row1 * sizeof(double));
    valuesBuffer2 = (double *) malloc(n_row2 * sizeof(double));
    outputBuf = (double *) malloc(n_row2 * sizeof(double));
    // error checks if memory not allocated
    if(bufInput1 == NULL)
    {   printf("Memory not allocated.\n");
        return EXIT_FAILURE;
    }
    if(bufInput2 == NULL)
    {
        printf("Memory not allocated.\n");  
        return EXIT_FAILURE;
    }
    if(valuesBuffer1 == NULL)
    {  
        printf("Memory not allocated.\n"); 
        return EXIT_FAILURE;
    }
    if(valuesBuffer2== NULL)
    {
        printf("Memory not allocated.\n"); 
        return EXIT_FAILURE;
    } 

   // Here we will both files, store them line by line then call a function to handle splitting up the values into an array of doubles for further computation. 
   bufInput1 = ReadAndParseFile(inputFile1, n_row1, bufInput1);
   bufInput2 = ReadAndParseFile(inputFile2, n_row2, bufInput2);
   valuesBuffer1 = valuesSplit(bufInput1, n_row1 * n_col1, n_row1);
   valuesBuffer2 = valuesSplit(bufInput2, n_row2, n_row2);

   while(postionInBuf1 != (n_row1 * n_col1)){
       double initalResult =  valuesBuffer1[postionInBuf1] *  valuesBuffer2[postionInBuf2]; 
       value += initalResult;
      // printf("The inital result: of %f * %f = %f\n", valuesBuffer1[postionInBuf1],valuesBuffer2[postionInBuf2],initalResult);
       ++postionInBuf1;
       ++postionInBuf2;
       if(postionInBuf2 == n_row2){
         postionInBuf2 = 0;
         ++postionOutputBuf;
         printf("The result is: %f\n", value);
         outputBuf[nextLocation] = value;
         ++nextLocation;
         value = 0.0;
       }
   }

for(int i = 0; i < n_row2; ++i){
    fprintf(outputFile, "%f\n", outputBuf[i]);

}
    free(bufInput1);
    free(bufInput2);
    free(valuesBuffer1);
    free(valuesBuffer2);
    fclose (inputFile1);
    fclose (inputFile2);
    fclose (outputFile);
    return 0;
}


char ** ReadAndParseFile(FILE *fp, int numberOfRows, char ** inputBuffer ){
    char buf[50000];
    int i = 0;
    // read in the first input file and store each line into its own char array. 
    while(fgets(buf, 50000, fp)){
        // Remove new line
        buf[strlen(buf) + 1] = '\0';
        // Get length of buffer
        int len = strlen(buf);
        // allocate space for the string
        char *str = (char*) malloc((len + 1) * sizeof(char));
        // copy string from buf to str
        strcpy(str, buf);
        //printf("the value is: %s\n", str);
        // store the elements from buffer one into here. 
        inputBuffer[i] = str;
        i++;
    } 
    return inputBuffer;
}

double  * valuesSplit(char ** inputBuffer, int numberOfValues, int numRows){
    double * valueArray = (double *) malloc(numberOfValues * sizeof(double));
    int position = 0;
    double value = 0.0;
    char * endPtr;
    for(int i =0; i < numRows; ++i){
        char * token = strtok(inputBuffer[i], ",");
        while((token != NULL)){
            value = strtod(token, &endPtr);
            //printf("Converted Value and Element place into array = %f\n", value);
            valueArray[position] = value;
            ++position;
            token = strtok(NULL, ",");
        }
    }
    return valueArray;
}