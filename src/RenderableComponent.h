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
#include <glm/glm.hpp>
#include "Renderable.h"
#include <memory>

class GameObjectIds;

class RenderableComponent : public Component{
public:
	
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	GLuint textureBufferID;
	GLuint textureDataID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalbufferID;

	std::shared_ptr <Renderable> renderable;

	operator bool() const;
	RenderableComponent();
	RenderableComponent(std::shared_ptr <Renderable> renderable);
	RenderableComponent(RenderableComponent& other);
	void setRenderable(std::shared_ptr <Renderable> renderable);
    virtual void update(double dT);
    void initWith(RenderableComponent &component);
private:
	void render();
	bool _isNullComponent = false;
};

#endif /* defined(__OpenGLTutorial__RenderableComponent__) */
