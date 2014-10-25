//
//  BaseRenderer.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 05/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__BaseRenderer__
#define __OpenGLTutorial__BaseRenderer__

#include <stdio.h>

class BaseRenderer
{
public:
    virtual void init() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
protected:
    void clear(float r=0,
               float g=0,
               float b=0,
               float a=0,
               bool depth=true);
    void flush();
};

#endif /* defined(__OpenGLTutorial__BaseRenderer__) */
