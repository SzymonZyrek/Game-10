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
    virtual void update();
    void resetShift();
private:
    float shitf;
    float shitfDirection;
	void draw();
	void drawTraingle();
    void drawTriangles();
	void drawModel();

	ModelLoader model;

	GLuint programID;			//shader id
	GLuint matrixID;			//MVP matrix id
	GLuint textureDataID;
	GLuint vertexArrayID;		//vertex array id

	glm::mat4 viewMatrix;		//view matrix
	glm::mat4 projectionMatrix; //projection matrix

	GLuint textureBuffer;		//texture buffer id
	GLuint vertexBuffer;		//vertex buffer id
	GLuint uvBuffer;			//normals buffer id

	/*std::vector<glm::vec3> vertices = model.indexedVertices;
	std::vector<glm::vec2> uvs = model.indexedUv;*/
	
	std::shared_ptr<Camera> camera;
	glm::vec3 renderablePosition;
	glm::vec3 renderableRotation;
};

