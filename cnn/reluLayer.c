#include <malloc.h>
#include "reluLayer.h"

ReluLayer* initReluLayer(Point* inSize){
    ReluLayer* reluLayer = malloc(sizeof(ReluLayer));
    reluLayer->type = relu;
    reluLayer->in = NULL;
    reluLayer->back = initTensor(inSize);
    reluLayer->out = initTensor(inSize);
}

void activateReluLayer(ReluLayer* reluLayer, Tensor* in){
    reluLayer->in = in;
    for(int i = 0; i < reluLayer->in->size->H; i++){
        for(int j = 0; j< reluLayer->in->size->W; j++){
            for(int k = 0; reluLayer->in->size->D; k++){
                double x = *getTensorField(in,{i,j,k});
                if(x < 0) x = 0;
                *getTensorField(reluLayer->out,{i,j,k}) = x;
            }
        }
    }
}

void backPropReluLayer(ReluLayer* reluLayer, Tensor* nextLayerBack){
    for(int i = 0; i < reluLayer->in->size->H; i++){
        for(int j = 0; j< reluLayer->in->size->W; j++){
            for(int k = 0; reluLayer->in->size->D; k++){
                double x = *getTensorField(reluLayer->in,{i,j,k});
                if(x < 0) x = 0;
                else x = *getTensorField(nextLayerBack,{i,j,k});
                *getTensorField(reluLayer->back,{i,j,k}) = x;
            }
        }
    }
}

void freeReluLayer(ReluLayer* reluLayer){
    freeTensor(reluLayer->back);
    freeTensor(reluLayer->out);
    free(reluLayer);
}


