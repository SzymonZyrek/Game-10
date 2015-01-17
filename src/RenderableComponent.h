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
	
	glm::vec3 position = glm::vec3(0.0,0.0,0.0);
	glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);;
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);;

	GLuint textureBufferID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalbufferID;

	unsigned int vertexCount;

	std::shared_ptr <Renderable> renderable;

	RenderableComponent();
	RenderableComponent::RenderableComponent(std::string modelName, std::string textureName);
	RenderableComponent(std::shared_ptr <Renderable> renderable);
	RenderableComponent(RenderableComponent& other);
	void setRenderable(std::shared_ptr <Renderable> renderable);
	virtual void update(double dT,
		unsigned int gameObjectId,
		std::vector<AIUpdateCommand> &aiCommands,
		std::vector<InputUpdateCommand> &inputCommands,
		std::vector<PhysicsUpdateCommand> &physicCommands,
		std::vector<RenderableUpdateCommand> &renderableCommands);
    void initWith(RenderableComponent &component);
private:
	void render();
};

#endif /* defined(__OpenGLTutorial__RenderableComponent__) */
