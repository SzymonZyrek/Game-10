//
//  Tut01Renderer.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 05/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__Tut01Renderer__
#define __OpenGLTutorial__Tut01Renderer__

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

#endif /* defined(__OpenGLTutorial__Tut01Renderer__) */
