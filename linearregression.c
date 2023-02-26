#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct arrayInfoStruct {
    int nDimensions;
    long *dimensions;
    double *arrayData;
} arrayInfo;
*/

/*
arrayInfo linearregression(arrayInfo inputArrayInfo) {
  arrayInfo outputArrayInfo;

  outputArrayInfo.nDimensions = 2;
  long dimensions[] = {3, 3};
  double temp1[] = {7, 4, 5, 6, 1, 3, 8, 0, 111};

  outputArrayInfo.dimensions = (long *)calloc(outputArrayInfo.nDimensions, sizeof(long));
  memcpy(outputArrayInfo.dimensions, dimensions, sizeof(long) * outputArrayInfo.nDimensions);

  int outputArrayLength = 1;
  for (int i = 0; i < outputArrayInfo.nDimensions; i++) {
    outputArrayLength *= (int)outputArrayInfo.dimensions[i];
  }
  outputArrayInfo.arrayData = (double *)calloc(outputArrayLength, sizeof(double));
  memcpy(outputArrayInfo.arrayData, temp1, sizeof(double) * outputArrayLength);

  return outputArrayInfo;
}
*/

int LRSize(int inputNdArrayNDimensions, long *inputNdArrayDimensions, long *outputNdArrayDimensions) {
    long dtemp[] = {3, 3};
    memcpy(outputNdArrayDimensions, dtemp, sizeof(long) * outputArrayInfo.nDimensions);
    return 1;
}