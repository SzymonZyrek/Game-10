#pragma once
#include <stdio.h>
#include "BaseRenderer.h"
#include "ModelLoader.h"
#include <memory>
#include "Camera.h"

class SimpleRenderer : public BaseRenderer
{
public:
    virtual void init();
    virtual void render();
	//TODO: move update away from here,
	//its here just as a dev toy
    virtual void update();
    void resetShift();
private:
	void draw();

	ModelLoader model;

	// uniform ids
	GLuint programID;
	GLuint mpvMatrixID;
	GLuint modelMatrixID;
	GLuint viewMatrixID;
	GLuint textureDataID;
	GLuint vertexArrayID;
	GLuint lightID;
	// buffer ids
	GLuint textureBufferID;
	GLuint vertexBufferID;
	GLuint uvBufferID;
	GLuint normalbufferID;
	
	std::shared_ptr<Camera> camera;

	glm::vec3 renderablePosition;
	glm::vec3 renderableRotation;
	float testValue = 0;
	GLuint testValueId;
};

