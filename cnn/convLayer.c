#include <time.h>
#include "convLayer.h"
#include "../math/vector.h"
#include "testCase.h"
#include "../math/point.h"
#include "grad.h"

ConvLayer * initConvLayer(int stride, int spatialExtent, int padding, int filtersNumber, Point *inSize){
    debugAssert(inSize != NULL);
    debugAssert((inSize->H - spatialExtent + 2*padding) % stride == 0);
    debugAssert((inSize->W - spatialExtent + 2*padding) % stride == 0);
    int w = (inSize->W - spatialExtent + 2*padding)/stride + 1;
    int h = (inSize->H - spatialExtent + 2*padding)/stride + 1;
    Point outSize = {w,h,filtersNumber};
    ConvLayer* convLayer = malloc(sizeof(convLayer));
    convLayer->type = conv;
    convLayer->in = NULL;
    convLayer->back = initTensor(inSize);
    convLayer->out = initTensor(&outSize);
    convLayer->stride = stride;
    convLayer->spatialExtent = spatialExtent;
    convLayer->padding = padding;
    convLayer->filters = initVector(0);
    convLayer->filtersOldGrad = initVector(0);
    convLayer->filtersGrad = initVector(0);
    srand((unsigned int) time(NULL));
    for(int i = 0; i < filtersNumber; i++){
        Point filterSize = {spatialExtent,spatialExtent,inSize->D};
        Tensor* filter = initTensor(&filterSize);
        Tensor* filterGrad = initTensor(&filterSize);
        Tensor* filterOldGrad = initTensor(&filterSize);
        int max = multiplePointParameters(&filterSize);
        for(int index = 0; index < max;index++){
            *getFasterTensorField(filter,index) = 1/(double)max * rand() / (double)(RAND_MAX);
            *getFasterTensorField(filterGrad,index) = 0;
            *getFasterTensorField(filterOldGrad,index) = 0;
        }
        pushBackVector(convLayer->filters,filter);
        pushBackVector(convLayer->filtersOldGrad,filterOldGrad);
        pushBackVector(convLayer->filtersGrad,filterGrad);
    }
    return convLayer;
}


int checkIndex(Point point, int padding, Point max){
    if(point.H < padding || max.H + padding <= point.H) return 0;
    if(point.W < padding || max.W + padding <= point.W) return 0;
    return 1;
}

void activateConvLayer(ConvLayer* convLayer, Tensor* in){
    convLayer->in = in;
    for(int f_i = 0; f_i < convLayer->filters->size; f_i++){
        Tensor* filter = getVectorField(convLayer->filters,f_i);
        for(int i = 0; i < convLayer->out->size->H; i++){
            for(int j = 0; j< convLayer->out->size->W; j++){
                double sum = 0;
                for(int x = 0; x < convLayer->spatialExtent; x++){
                    for(int y = 0; y < convLayer->spatialExtent; y++){
                        for(int z = 0; z < in->size->D; z++){
                            double weight = *getTensorField(filter,(Point){x,y,z});
                            Point index = {x+i*convLayer->stride,y+j*convLayer->stride,z};
                            double val = 0;
                            if(checkIndex(index,convLayer->padding,*in->size)){
                                val = *getTensorField(in,index);
                            }
                            sum += val * weight;
                        }
                    }
                }
                *getTensorField(convLayer->out,(Point){i,j,f_i}) = sum;
            }
        }
    }
}


void backPropConvLayer(ConvLayer* convLayer, Tensor* nextLayerBack){

    int spatialExtent = convLayer->spatialExtent;
    double stride = convLayer->stride;
    Point inSize = *convLayer->back->size;
    Point outSize = *convLayer->out->size;
    int padding = convLayer->padding;
    for(int f_i = 0; f_i <convLayer->filtersGrad->size; f_i++){
        Tensor * filterGrad = getVectorField(convLayer->filtersGrad,f_i);
        for(int i = 0; i < spatialExtent; i++){
            for(int j = 0; j < spatialExtent;j++){
                for(int k = 0; k < inSize.D; k++){
                    *getTensorField(filterGrad,(Point){i,j,k}) = 0;
                }
            }
        }
    }

    for(int i = 0; i < inSize.H; i++){
        for(int j = 0; j< inSize.W; j++){
            for(int k = 0; inSize.D; k++){
                int x_min = normalizeValue((i+padding-spatialExtent+1)/stride,outSize.H-1,1);
                int x_max = normalizeValue((i+padding)/stride,outSize.H-1,0);
                int y_min = normalizeValue((j+padding-spatialExtent+1)/stride,outSize.W-1,1);
                int y_max = normalizeValue((j+padding)/stride,outSize.W-1,0);
                Point inIndex = {i,j,k};
                double sum = 0;
                for(int x = x_min; x<= x_max; x++){
                    for(int y = y_min; y <= y_max; y++){
                        for(int z = 0; z < convLayer->filters->size; z++){
                            Tensor * filter = getVectorField(convLayer->filters,z);
                            Tensor * filterGrad = getVectorField(convLayer->filtersGrad,z);
                            Point outIndex = {x,y,z};
                            Point filterIndex = {i+padding-x_min,j+padding-y_min,k};
                            double filter_value = *getTensorField(filter,filterIndex);
                            double back_value = *getTensorField(nextLayerBack,outIndex);
                            double in_val = *getTensorField(convLayer->in,inIndex);
                            sum += filter_value * back_value;
                            *getTensorField(filterGrad,filterIndex) += in_val * back_value;
                        }
                    }
                }
                *getTensorField(convLayer->back,inIndex) = sum;
            }
        }
    }

    for(int f_i = 0; f_i <convLayer->filtersGrad->size; f_i++){
        Tensor * filter = getVectorField(convLayer->filters,f_i);
        Tensor * filterOldGrad = getVectorField(convLayer->filtersOldGrad,f_i);
        Tensor * filterGrad = getVectorField(convLayer->filtersGrad,f_i);
        for(int i = 0; i < spatialExtent; i++){
            for(int j = 0; j < spatialExtent;j++){
                for(int k = 0; k < inSize.D; k++){
                    Point index = {i,j,k};
                    double weight = *getTensorField(filter, index);
                    double grad = *getTensorField(filterGrad, index);
                    double oldGrad = *getTensorField(filterOldGrad, index);
                    *getTensorField(filter, index) = updateWeight(weight, grad, oldGrad, 1);
                    *getTensorField(filterOldGrad, index) = updateGradient(grad, oldGrad);
                }
            }
        }
    }


}
void freeConvLayer(ConvLayer* convLayer){
    debugAssert(convLayer != NULL);
    freeTensor(convLayer->back);
    freeTensor(convLayer->out);
    for(int i = 0; i < convLayer->filters->size; i++){
        freeTensor(getVectorField(convLayer->filters,i));
        freeTensor(getVectorField(convLayer->filtersGrad,i));
        freeTensor(getVectorField(convLayer->filtersOldGrad,i));
    }
    freeVector(convLayer->filters);
    freeVector(convLayer->filtersGrad);
    freeVector(convLayer->filtersOldGrad);
    free(convLayer);
}

