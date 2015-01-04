#pragma once
#include <stdio.h>
#include "BaseRenderer.h"

class Tut01Renderer : public BaseRenderer
{
public:
    virtual void init();
    virtual void render();
    virtual void update();
    void resetShift();
private:
    float shitf;
    float shitfDirection;
    void drawTriangles();
};

