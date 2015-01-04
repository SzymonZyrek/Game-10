//
//  GameObject.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "GameObject.h"
#include "AIComponent.h"
#include "RenderableComponent.h"
#include "InputComponent.h"
#include "PhysicalComponent.h"
#include "CPPLogger.h"

GameObject::GameObject()
{
    this->_active = false;
	Log::debug("GameObject constrcuted with default constructor\n", DebugKey::OBJECT_CREATION);
}
GameObject::GameObject(GameObject &other)
{
	//reset id, will be re-assigned on registration
	this->id = nullptr;
	if (other.hasAIComponent())
		this->_ai = new AIComponent(*other.getAIComponent());
	if (other.hasInputComponent())
		this->_input = new InputComponent(*other.getInputComponent());
	if (other.hasPhysicalComponent())
		this->_body = new PhysicalComponent(*other.getPhysicalComponent());
	if (other.hasRenderableComponent())
		this->_renderable = new RenderableComponent(*other.getRenderableComponent());
	Log::debug("GameObject constrcuted with ref copy construcor\n", DebugKey::OBJECT_CREATION);
}
void GameObject::setRenderableComponent(RenderableComponent* component)
{
    this->_renderable = component;
}
void GameObject::setPhysicalComponent(PhysicalComponent* component)
{
    this->_body = component;
}
void GameObject::setInputComponent(InputComponent* component)
{
    this->_input = component;
}
void GameObject::setAIComponent(AIComponent* component)
{
    this->_ai = component;
}
void GameObject::addSpecialComponent(Component* component)
{
    this->_specialComponents.push_back(component);
}

RenderableComponent* GameObject::getRenderableComponent(){return _renderable;}
PhysicalComponent* GameObject::getPhysicalComponent(){return _body;}
InputComponent* GameObject::getInputComponent(){return _input;}
AIComponent* GameObject::getAIComponent(){return _ai;}
std::vector<Component*> GameObject::getSpecialComponents(){return _specialComponents;}

bool GameObject::hasRenderableComponent()
{
    return (_renderable!=NULL);
}
bool GameObject::hasPhysicalComponent()
{
	return (_body != NULL);
}
bool GameObject::hasInputComponent()
{
	return (_input != NULL);
}
bool GameObject::hasAIComponent()
{
	return (_ai != NULL);
}
bool GameObject::hasSpecialComponents()
{
    return (_specialComponents.size() > 0);
}
bool GameObject::isActive()
{
    return _active;
}
void GameObject::setActive(bool value)
{
    this->_active = value;
}
