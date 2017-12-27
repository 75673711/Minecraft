#ifndef CUBEMODEL_H
#define CUBEMODEL_H

#include "BaseModel.h"

class CubeModel : public BaseModel
{
public:
    CubeModel();

    virtual void Draw() const override;
    virtual CGLuint getIndicesCount() const override;
};

#endif // CUBEMODEL_H
