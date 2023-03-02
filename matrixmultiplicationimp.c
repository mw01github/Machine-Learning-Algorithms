#include <stdio.h>

static void *bruteForceImplementation(double *outputArray, double *inputArrayX, double *inputArrayY, long *XDims, long *YDims) {
    for (int i = 0; i < XDims[0]; i++) {
        for (int j = 0; j < YDims[1]; j++) {
            for (int k = 0; k < XDims[1]; k++) {
                outputArray[i * XDims[1] + j] += inputArrayX[i * XDims[1] + k] * inputArrayY[k * XDims[0] + j];
            }
        }
    }
}

static void *divideImplementation(double *outputArray, double *inputArrayX, double *inputArrayY, long size) {
    if (size <= 2) {
        long Dims[2] = {size, size};
        bruteForceImplementation(outputArray, inputArrayX, inputArrayY, Dims, Dims);
        return NULL;
    }

    double *Xsplits[4], *Ysplits[4];
    for (int i = 0; i < 4; i++) {
        Xsplits[i] = inputArrayX + i * size * sizeof(double);
        Ysplits[i] = inputArrayY + i * size * sizeof(double);
    }

    divideImplementation(outputArray, Xsplits[1], Ysplits[1], size / 2);
    divideImplementation(outputArray, Xsplits[2], Ysplits[3], size / 2);
    divideImplementation(outputArray, Xsplits[1], Ysplits[2], size / 2);
    divideImplementation(outputArray, Xsplits[2], Ysplits[4], size / 2);
    divideImplementation(outputArray, Xsplits[3], Ysplits[1], size / 2);
    divideImplementation(outputArray, Xsplits[4], Ysplits[3], size / 2);
    divideImplementation(outputArray, Xsplits[3], Ysplits[2], size / 2);
    divideImplementation(outputArray, Xsplits[4], Ysplits[4], size / 2);
}