//
//  Tut01Renderer.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 05/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Tut01Renderer.h"
#include <OpenGl/gl.h>
#include <iostream>
#include "CPPIdentifiable.h"
#include <memory>
#include "Testing.h"
#include "TestResult.h"

static void another_silly_a_la_main_for_prototyping()
{
    Testing::performTests(false);
}

void Tut01Renderer::init()
{
    shitfDirection = 1;
    shitf = 0.0f;
    another_silly_a_la_main_for_prototyping();
}

void Tut01Renderer::update()
{
#define SHIFT_MOVE 0.005f
    if (shitfDirection==1)
    {
        shitf += SHIFT_MOVE;
    }
    else
    {
        shitf -= SHIFT_MOVE;
        if (shitf <= 0.0)
        {
            shitfDirection = 1;
        }
    }
}

void Tut01Renderer::render()
{
    clear();
    drawTriangles();
    flush();
}

void Tut01Renderer::drawTriangles()
{
    glColor3f(1.0, 0.85, 0.35);
    
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(-1.0+shitf, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    
        glColor3f(1.0f, 0.0f, 0.35f);
    
        glVertex3f(1.0-shitf, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    }
    glEnd();
    
}

void Tut01Renderer::resetShift()
{
    this->shitf = 0.0;
}