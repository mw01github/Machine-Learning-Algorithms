#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arrayInfo {
  int nDimensions;
  long *dimensions;
  double *arrayData;
};

struct arrayInfo linearregression(struct arrayInfo inputArrayInfo) {
  struct arrayInfo outputArrayInfo;

  outputArrayInfo.nDimensions = 2;
  long dimensions[] = {3, 3};
  double temp1[] = {7, 4, 5, 6, 1, 3, 8, 0, 9};

  outputArrayInfo.dimensions =
      (long *)calloc(outputArrayInfo.nDimensions, sizeof(long));
  memcpy(outputArrayInfo.dimensions, dimensions,
         sizeof(long) * outputArrayInfo.nDimensions);

  int outputArrayLength = 1;
  for (int i = 0; i < outputArrayInfo.nDimensions; i++) {
    outputArrayLength *= (int)outputArrayInfo.dimensions[i];
  }
  outputArrayInfo.arrayData =
      (double *)calloc(outputArrayLength, sizeof(double));
  memcpy(outputArrayInfo.arrayData, temp1, sizeof(double) * outputArrayLength);

  return outputArrayInfo;
}