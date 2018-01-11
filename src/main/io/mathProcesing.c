#include "mathProcesing.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../3rdParty/stb_image.h"


Tensor *readImagineToTensor(char *filename) {
    int width, height, nChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nChannels, 0);
    Point point = {width, height, nChannels};
    Tensor *tensor = initTensor(&point);
    int col, row, colour;
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            for (colour = 0; colour < nChannels; colour++) {
                point.height = row;
                point.width = col;
                point.depth = colour;
                int dataIndex = colour + col * nChannels + row * width * nChannels;
                tensor->data[multiplePointParameters(&point)] = data[dataIndex] / 255;
            }
        }

    }
    stbi_image_free(data);
    return tensor;
}

Tensor *readTensorFromFile(FILE *file) {
    Point point = readPointFile(file);
    Tensor *tensor = initTensor(&point);
    for (int i = 0; i < multiplePointParameters(&point); i++) {
        fscanf(file, "%le", &tensor->data[i]);
    }
    return tensor;
}

void writeTensorToFile(Tensor *tensor, FILE *file) {
    savePointFile(file, *tensor->size);
    for (int i = 0; i < multiplePointParameters(tensor->size); i++) {
        fprintf(file, "%le\n", tensor->data[i]);
    }
}

Tensor *addDimensionsToTensor(Tensor *oldT, int n, int k) {
    Point newpoint = {oldT->size->height, oldT->size->width, oldT->size->depth + 2};
    Tensor *newTensor = initTensor(&newpoint);
    int mPP = multiplePointParameters(oldT->size);
    for (int i = 0; i < mPP; i++) {
        newTensor->data[i] = oldT->data[i];
    }
    for (int i = mPP; i < mPP + oldT->size->height * oldT->size->width; i++) {
        newTensor->data[i] = n;
    }
    for (int i = mPP + oldT->size->height * oldT->size->width; i < mPP + 2 * oldT->size->height * oldT->size->width; i++) {
        newTensor->data[i] = k;
    }
    return newTensor;
}

Vector *createParamtersTensors(Tensor *rawImage, int n) {
    Vector *vector = initVector(n);
    for (int i = 0; i < n; i++) {
        pushBackVector(vector, addDimensionsToTensor(rawImage, n, i));
    }
    return vector;
}

Tensor *returnOutputTensor(int n, int k) {
    Point point = {n, 1, 1};
    Tensor *tensor = initTensor(&point);
    for (int i = 0; i < multiplePointParameters(&point); i++) {
        *getFasterTensorField(tensor, i) = 0;
    }
    *getFasterTensorField(tensor, k) = 1;
    return tensor;
}

Point readPointFile(FILE *file) {
    Point point = {0, 0, 0};
    fscanf(file, "%d %d %d", &(point.height), &(point.width), &(point.depth));
    return point;
}

void savePointFile(FILE *file, Point point) {
    fprintf(file, "%d %d %d\n", (point.height), (point.width), (point.depth));
}
