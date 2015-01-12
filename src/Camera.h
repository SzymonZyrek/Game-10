#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "CPPLogger.h"
class Camera {
public: 
	void applyCameraToMatrices(float deltaTime, glm::mat4 *ViewMatrix, glm::mat4 *ProjectionMatrix);
	Camera(GLFWwindow* window);
	~Camera();
	//------------------------------------------
	// Window this camera is servicing:
	//------------------------------------------
	GLFWwindow* window;
	//------------------------------------------
	// Basic camera data:
	//------------------------------------------
	glm::vec3 position;			//position of the camera
	glm::vec3 direction;		//direction camera is 
								//			   facing
	glm::vec3 velocity;			//velocity of camera move

	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);

	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);

	glm::vec3 getVelocity();
	void setVelocity(glm::vec3 velocity);

	//------------------------------- MOVABLE INTERFACE PART -------------------------------
	void moveForward(float step);
	void moveBackwards(float step);
	void moveLeft(float step);
	void moveRight(float step);
	void moveUpwards(float step);
	void moveDownwards(float step);

	void updateLookAtPoint(float deltaTime, float xpos, float ypos);
	//------------------------------- ILookAround INTERFACE PART -------------------------------

	glm::vec3 right;
	glm::vec3 up;

	float horizontalAngle;
	float verticalAngle;

	float initialFoV;
	float speed;
	float mouseSpeed;
private:
	unsigned int camLogPeriodicKey;
	Logger dalogger;
};