#include <stdio.h>
#include <opencv-3.3.1/modules/imgcodecs/include/opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv-3.3.1/include/opencv/highgui.h>
#include "../math/tensor.h"
#include "../math/point.h"
#include "../math/vector.h"


Tensor* readImagineToTensor( char* filename ){
    IplImage* pImg = cvLoadImage( filename, CV_LOAD_IMAGE_COLOR);
    Point point = {pImg->width, pImg->height, 3};
    Tensor* tensor = initTensor(&point);
    int col, row, colour;
    for( row = 0; row < pImg->height; row++ )
    {
        for ( col = 0; col < pImg->width; col++ )
        {
            for( colour = 0; colour < pImg->nChannels; colour++ )
            {
                point.H = row;
                point.W = col;
                point.D = colour;
                int arrind = pImg->widthStep * row + col * pImg->nChannels + colour;
                tensor->data[multiplePointParameters(&point)] = pImg->imageData[arrind];
            }
        }

    }
    cvReleaseImage(&pImg);
    return tensor;
}

Tensor* readTensorFromFile(FILE* file){
    Point point = {0, 0, 0};
    fscanf(file, "%d", &(point.H));
    fscanf(file, "%d", &(point.W));
    fscanf(file, "%d", &(point.D));

    Tensor* tensor = initTensor(&point);
    for(int i = 0; i < multiplePointParameters(&point); i++){
        fscanf(file, "%lf", &tensor->data[i]);
    }
    return tensor;
}

void writeTensorToFile(Tensor* tensor, FILE* file){
    fprintf(file, "%d %d %d ", tensor->size->H, tensor->size->W, tensor->size->D);
    for(int i = 0; i < multiplePointParameters(tensor->size); i++){
        fprintf(file, "%lf ", tensor->data[i]);
    }
}

Tensor* addDimensionsToTensor(Tensor* oldT, int n, int k){
    Point newpoint = {oldT->size->H, oldT->size->W, oldT->size->D + 2};
    Tensor* newTensor = initTensor(&newpoint);
    int mPP = multiplePointParameters(oldT->size);
    for(int i = 0; i < mPP; i++){
        newTensor->data[i] = oldT->data[i];
    }
    for(int i = mPP; i < mPP + oldT->size->H * oldT->size->W ; i++){
        newTensor->data[i] = n;
    }
    for(int i = mPP + oldT->size->H * oldT->size->W; i < mPP + 2 * oldT->size->H * oldT->size->W ; i++){
        newTensor->data[i] = k;
    }
    return newTensor;
}

Vector* createParamtersTensors(Tensor* rawImage, int n){
    Vector* vector = initVector(n);
    for(int i = 0; i < n; i++){
        pushBackVector(vector, addDimensionsToTensor(rawImage,n,i));
    }
    return vector;
}
