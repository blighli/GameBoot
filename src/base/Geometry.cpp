//
// Created by bligh on 2023/11/28.
//

#include "Geometry.h"
#include <iostream>

void Geometry::loadGeomeryFromFile(const char *fileName) {
    FILE* file =  fopen(fileName, "r");
    if (!file)
    {
        std::cerr<<"Load geometry from " << fileName << " failed!"<<std::endl;
        return;
    }

    fscanf(file, "%d", &mVertexCount);

    int vertexBufferSize = mVertexCount * 6;
    mVertexBuffer = new float[vertexBufferSize];
    for(int i=0; i < vertexBufferSize; i++){
        fscanf(file, "%f", &mVertexBuffer[i]);
    }

    fscanf(file, "%d", &mIndexCount);
    if(mIndexCount > 0)
    {
        mIndexBuffer = new int[mIndexCount];
        for(int i=0; i < mIndexCount; i++){
            fscanf(file, "%d", &mIndexBuffer[i]);
        }
    }

    fclose(file);
}

Geometry::Geometry() {
    mVertexCount = 0;
    mVertexBuffer = nullptr;
    mIndexCount = 0;
    mIndexBuffer = nullptr;
}

Geometry::~Geometry() {
    delete[] mVertexBuffer;
    delete[] mIndexBuffer;
}

int Geometry::getVertexCount() const {
    return mVertexCount;
}

float *Geometry::getVertexBuffer() const {
    return mVertexBuffer;
}

int Geometry::getIndexCount() const {
    return mIndexCount;
}

int *Geometry::getIndexBuffer() const {
    return mIndexBuffer;
}
