#include <stdio.h>
#include <math.h>

static void copyArray(double* source, double* dest, long length) {
    for (int i = 0; i < length; i++) {
        dest[i] = source[i];
    }
}

static void addArray(double* source, double* dest, long length) {
    for (int i = 0; i < length; i++) {
        dest[i] += source[i];
    }
}

static void add_Array(double* X, double* Y, double* dest, long length) {
    for (int i = 0; i < length; i++) {
        dest[i] = X[i] + Y[i];
    }
}

static void subArray(double* source, double* dest, long length) {
    for (int i = 0; i < length; i++) {
        dest[i] -= source[i];
    }
}

static void sub_Array(double* X, double* Y, double* dest, long length) {
    for (int i = 0; i < length; i++) {
        dest[i] = X[i] - Y[i];
    }
}


static void *bruteForceImplementation(double *outputArray, double *inputArrayX, double *inputArrayY, long *XDims, long *YDims) {
    for (int i = 0; i < XDims[0]; i++) {
        for (int j = 0; j < YDims[1]; j++) {
            for (int k = 0; k < XDims[1]; k++) {
                outputArray[i * XDims[1] + j] += inputArrayX[i * XDims[1] + k] * inputArrayY[k * XDims[0] + j];
            }
        }
    }
}

static void *reArange(double *inputArray, long width, int revert) {
    double outputArray[width * width];
    double *splitPtr;
    int m = 0;

    for (int i = 0; i < 4; i++) {
        if (revert == 0) splitPtr = inputArray;
        else splitPtr = outputArray;
        if (i == 1) splitPtr += (width / 2);
        if (i == 2) splitPtr += ((width / 2) * width);
        if (i == 3) splitPtr += (width / 2) + ((width / 2) * width);
        for(int j = 0; j < (width / 2); j++) { //row
            for(int k = 0; k < (width / 2); k++) { //col
                if (revert == 0) outputArray[m] = *splitPtr;
                if (revert == 1) *splitPtr = inputArray[m];
                splitPtr += 1;
                m++;
            }
            splitPtr += (width / 2);
        }
    }
    copyArray(outputArray, inputArray, width * width);
}

static void *divideImplementation(double *outputArray, double *inputArrayX, double *inputArrayY, long width) {
    if (width == 1) {
        *outputArray += *inputArrayX * *inputArrayY;
        return NULL;
    }
    long length = width * width;
    long quarter = length / 4;

    double iX[length]; double iY[length];
    copyArray(inputArrayX, iX, length); copyArray(inputArrayY, iY, length);
    reArange(iX, width, 0); reArange(iY, width, 0);

    int oDest[] = {0, 0, 1, 1, 2, 2, 3, 3};
    int XDest[] = {0, 1, 0, 1, 2, 3, 2, 3};
    int YDest[] = {0, 2, 1, 3, 0, 2, 1, 3};
    double tempOutput[length / 4];

    for (int i = 0; i < 8 ; i++) {
        memset(tempOutput, (double)0, (length / 4)*sizeof(double));
        divideImplementation(tempOutput, &iX[quarter * XDest[i]], &iY[quarter * YDest[i]], width / 2);
        addArray(tempOutput, &outputArray[quarter * oDest[i]], length / 4);
    }
    reArange(outputArray, width, 1);
}

static void *strassenImplementation(double *outputArray, double *inputArrayX, double *inputArrayY, long width) {
    if (width == 1) {
        *outputArray += *inputArrayX * *inputArrayY;
        return NULL;
    }
    long length = width * width;

    double iX[length]; double iY[length];
    copyArray(inputArrayX, iX, length); copyArray(inputArrayY, iY, length);
    reArange(iX, width, 0); reArange(iY, width, 0);

    long quarter = length / 4;
    long a = 0, b = quarter, c = quarter * 2, d = quarter * 3;
    double tempOutput[length / 4];

    memset(tempOutput, (double)0, (length / 4)*sizeof(double));
    double XaPXd[length / 4]; add_Array(&iX[a], &iX[d], XaPXd, length / 4);
    double YaPYd[length / 4]; add_Array(&iY[a], &iY[d], YaPYd, length / 4);
    strassenImplementation(tempOutput, XaPXd, YaPYd, width / 2);
    addArray(tempOutput, &outputArray[a], length / 4);
    addArray(tempOutput, &outputArray[d], length / 4);

    memset(tempOutput, (double)0, (length / 4)*sizeof(double));
    double YcMYa[length / 4]; sub_Array(&iY[c], &iY[a], YcMYa, length / 4);
    strassenImplementation(tempOutput, &iX[d], YcMYa, width / 2);
    addArray(tempOutput, &outputArray[a], length / 4);
    addArray(tempOutput, &outputArray[c], length / 4);

    memset(tempOutput, (double)0, (length / 4)*sizeof(double));
    double XaPXb[length / 4]; add_Array(&iX[a], &iX[b], XaPXb, length / 4);
    strassenImplementation(tempOutput, XaPXb, &iY[d], width / 2);
    subArray(tempOutput, &outputArray[a], length / 4);
    addArray(tempOutput, &outputArray[b], length / 4);

    memset(tempOutput, (double)0, (length / 4)*sizeof(double));
    double XbMXd[length / 4]; sub_Array(&iX[b], &iX[d], XbMXd, length / 4);
    double YcPYd[length / 4]; add_Array(&iY[c], &iY[d], YcPYd, length / 4);
    strassenImplementation(tempOutput, XbMXd, YcPYd, width / 2);
    addArray(tempOutput, &outputArray[a], length / 4);

    memset(tempOutput, (double)0, (length / 4)*sizeof(double));
    double YbMYd[length / 4]; sub_Array(&iY[b], &iY[d], YbMYd, length / 4);
    strassenImplementation(tempOutput, &iX[a], YbMYd, width / 2);
    addArray(tempOutput, &outputArray[b], length / 4);
    addArray(tempOutput, &outputArray[d], length / 4);

    memset(tempOutput, (double)0, (length / 4)*sizeof(double));
    double XcPXd[length / 4]; add_Array(&iX[c], &iX[d], XcPXd, length / 4);
    strassenImplementation(tempOutput, XcPXd, &iY[a], width / 2);
    addArray(tempOutput, &outputArray[c], length / 4);
    subArray(tempOutput, &outputArray[d], length / 4);

    memset(tempOutput, (double)0, (length / 4)*sizeof(double));
    double XaMXc[length / 4]; sub_Array(&iX[a], &iX[c], XaMXc, length / 4);
    double YaPYb[length / 4]; add_Array(&iY[a], &iY[b], YaPYb, length / 4);
    strassenImplementation(tempOutput, XaMXc, YaPYb, width / 2);
    subArray(tempOutput, &outputArray[d], length / 4);

    reArange(outputArray, width, 1);
}