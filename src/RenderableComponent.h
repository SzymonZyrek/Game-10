//
//  RenderableComponent.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__RenderableComponent__
#define __OpenGLTutorial__RenderableComponent__

#include "Component.h"

class GameObjectIds;

class RenderableComponent : public Component{
public:
	RenderableComponent();
	RenderableComponent(RenderableComponent& other);
    virtual void update(double dT);
	void render();
    void initWith(RenderableComponent &component);
};

#endif /* defined(__OpenGLTutorial__RenderableComponent__) */
