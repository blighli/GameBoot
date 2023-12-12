//
// Created by bligh on 2023/11/28.
//

#include "Geometry.h"
#include <iostream>
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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

    char imageName[256];
    if(fscanf(file, "%s", imageName) != EOF){
        //printf("%s\n", imageName);
        const char* pch = strrchr(fileName, '/');
        if(pch != nullptr){
            //printf("%s\n",pch);
            //append image name to mesh path
            size_t imageNameLen = strlen(imageName);
            size_t filePathLen = pch - fileName + 1;
            memcpy(imageName + filePathLen, imageName, imageNameLen + 1);
            memcpy(imageName, fileName, filePathLen);
            printf("%s\n", imageName);
            unsigned char *img = stbi_load(imageName, &mImageWidth, &mImageHeight, nullptr, 0);
            printf("width=%d,height=%d\n", mImageWidth, mImageHeight);

        }
    } else{
        printf("No Image File\n");
    }

    fclose(file);
}

Geometry::Geometry() {
    mVertexCount = 0;
    mVertexBuffer = nullptr;
    mIndexCount = 0;
    mIndexBuffer = nullptr;

    mImageBuffer = nullptr;
    mImageWidth = 0;
    mImageHeight = 0;
}

Geometry::~Geometry() {
    delete[] mVertexBuffer;
    delete[] mIndexBuffer;
    delete[] mImageBuffer;
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
