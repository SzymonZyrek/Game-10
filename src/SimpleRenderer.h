#pragma once
#include <stdio.h>
#include "BaseRenderer.h"
#include "ModelLoader.h"
#include <memory>
#include "Camera.h"
#include "RenderableComponent.h"
#include "Scene.h"

class SimpleRenderer : public BaseRenderer
{
public:
    virtual void init();
    virtual void render(Scene &scene);
	//TODO: move update away from here,
	//its here just as a dev toy
    virtual void update();
    void resetShift();
private:
	void draw(RenderableComponent &renderable);

	Scene scene;
	bool test = true;
	// uniform ids
	GLuint programID;
	GLuint mpvMatrixID;
	GLuint modelMatrixID;
	GLuint viewMatrixID;
	GLuint vertexArrayID;
	GLuint lightID;
	GLuint textureDataID;

	std::shared_ptr<Camera> camera;

	float testValue = 0;
	GLuint testValueId;
};

