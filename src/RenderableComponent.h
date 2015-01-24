//
//  RenderableComponent.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "Renderable.h"
#include <memory>
#include "RenderableUpdateCommand.h"

class GameObjectIds;

class RenderableComponent : public Component{
public:
	// transformation data
	glm::vec3 position = glm::vec3(0.0,0.0,0.0);
	glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);;
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);;
	// buffer ids
	GLuint textureBufferID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalbufferID;
	GLuint indexBufferId;
	// shader id
	GLuint programID;
	// how much stuff we've got
	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;

	bool indexed = false;

	RenderableComponent();
	RenderableComponent::RenderableComponent(std::string modelName, std::string textureName, bool indexed);
	RenderableComponent(std::shared_ptr <Renderable> renderable);
	RenderableComponent(RenderableComponent& other);
	void setRenderable(std::shared_ptr <Renderable> renderable);
	std::shared_ptr<Renderable> RenderableComponent::getRenderable();
	virtual void update(double dT, std::vector<RenderableUpdateCommand> &commands);
    void initWith(RenderableComponent &component);

private:
	// pointer to my daddy, who has the actual data, so that
	// i can call him when the shit gets real
	// dont call daddy too often- he will beat up the cache bad
	std::shared_ptr <Renderable> renderable;
	void refreshFromRenderable();
	void initRenderable();
};

std::ostream& operator<<(std::ostream &strm, RenderableComponent &a);