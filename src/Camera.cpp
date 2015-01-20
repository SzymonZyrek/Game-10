#include "Camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <sstream>
#include "CPPLogger.h"

Camera::Camera(GLFWwindow* window){
	this->window = window;
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	resolutionX = mode->width;
	resolutionY = mode->height;
	// Initial position : on +Z
	position = glm::vec3(0, 0, 0);
	// Initial horizontal angle : toward -Z
	horizontalAngle = 3.14f;
	// Initial vertical angle : none
	verticalAngle = 0.0f;
	speed = 8.0f; // 3 units / second
	mouseSpeed = 0.005f;
	camLogPeriodicKey = Log::getInstance()->getLogPeriodicKey(3.0);
	dalogger = Logger(camLogPeriodicKey, DebugKey::CAMERA);
}
Camera::~Camera(){}

glm::vec3 Camera::getPosition(){
	return this->position;
}
void Camera::setPosition(glm::vec3 position){
	this->position = position;
}

glm::vec3 Camera::getDirection(){
	return this->direction;
}
void Camera::setDirection(glm::vec3 direction){
	this->direction = direction;
}

glm::vec3 Camera::getVelocity(){
	return this->velocity;
}
void Camera::setVelocity(glm::vec3 velocity){
	this->velocity = velocity;
}

void Camera::moveForward(float step) {
	this->setPosition(this->getPosition() + (direction * (float)step * (float)speed));
}
void Camera::moveBackwards(float step) {
	this->setPosition(this->getPosition() - (direction * (float)step * (float)speed));
}
void Camera::moveLeft(float step) {
	this->setPosition(this->getPosition() - (right * (float)step * (float)speed));
}
void Camera::moveRight(float step) {
	this->setPosition(this->getPosition() + (right * (float)step * (float)speed));
}
void Camera::moveUpwards(float step) {
	this->setPosition(this->getPosition() + (up * (float)step * (float)speed));
}
void Camera::moveDownwards(float step) {
	this->setPosition(this->getPosition() - (up * (float)step * (float)speed));
}


void Camera::updateLookAtPoint(float deltaTime, float xpos, float ypos){
	horizontalAngle += mouseSpeed * float(resolutionX / 2 - xpos);
	verticalAngle += mouseSpeed * float(resolutionY / 2 - ypos);

	// direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);
	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);
	up = glm::cross(right, direction);
}

void Camera::applyCameraToMatrices(float deltaTime, glm::mat4 *ViewMatrix, glm::mat4 *ProjectionMatrix){
	glm::mat4 viewMatrix = *ViewMatrix;
	glm::mat4 projectionMatrix = *ProjectionMatrix;
	// update gaze direction
	updateLookAtPoint(deltaTime, resolutionX / 2, resolutionY / 2);
	
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 600 units
	projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 600.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	std::stringstream ss;
	ss << "Camera direction: " << direction.x << "," << direction.y << "," << direction.z <<
		", up: " << up.x << "," << up.y << "," << up.z <<
		", right: " << right.x << "," << right.y << "," << right.z << std::endl;
	dalogger << ss;
	// For the next frame, the "last time" will be "now"
	*ViewMatrix = viewMatrix;
	*ProjectionMatrix = projectionMatrix;
}

