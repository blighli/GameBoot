//
// Created by bligh on 2023/11/28.
//

#ifndef GAMEBOOT_GEOMETRY_H
#define GAMEBOOT_GEOMETRY_H


class Geometry {
public:
    Geometry();
    virtual ~Geometry();
    void loadGeomeryFromFile(const char* fileName);
    int getVertexCount() const;
    float *getVertexBuffer() const;
    int getIndexCount() const;
    int *getIndexBuffer() const;
private:
    int mVertexCount;
    float* mVertexBuffer;
    int mIndexCount;
    int* mIndexBuffer;
    char* mImageBuffer;
    int mImageWidth;
    int mImageHeight;
};


#endif //GAMEBOOT_GEOMETRY_H
