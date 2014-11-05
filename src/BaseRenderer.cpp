//
//  BaseRenderer.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 05/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "BaseRenderer.h"
#include <OpenGL/gl.h>

void BaseRenderer::clear(float r, float g, float b, float a, bool depth)
{
    glClearColor(r, g, b, a);
    if (depth)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
void BaseRenderer::flush()
{
    glFlush();
}