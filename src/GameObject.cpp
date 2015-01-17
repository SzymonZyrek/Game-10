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
#include <memory>

GameObject::GameObject()
{
    this->_active = false;
	Log::debug("GameObject constrcuted with default constructor\n", DebugKey::OBJECT_CREATION);
}
GameObject::GameObject(GameObject &other)
{
	//reset id, will be re-assigned on registration
	this->gameObjectId= 0;
	if (other.hasAIComponent())
		this->_ai = std::make_shared<AIComponent>(*other.getAIComponent());
	if (other.hasInputComponent())
		this->_input = std::make_shared<InputComponent>(*other.getInputComponent());
	if (other.hasPhysicalComponent())
		this->_body = std::make_shared<PhysicalComponent>(*other.getPhysicalComponent());
	if (other.hasRenderableComponent())
		this->_renderable = std::make_shared<RenderableComponent>(*other.getRenderableComponent());
	Log::debug("GameObject constrcuted with ref copy construcor\n", DebugKey::OBJECT_CREATION);
}
void GameObject::setRenderableComponent(std::shared_ptr<RenderableComponent> component)
{
    this->_renderable = component;
}
void GameObject::setPhysicalComponent(std::shared_ptr<PhysicalComponent> component)
{
    this->_body = component;
}
void GameObject::setInputComponent(std::shared_ptr<InputComponent> component)
{
    this->_input = component;
}
void GameObject::setAIComponent(std::shared_ptr<AIComponent> component)
{
    this->_ai = component;
}
void GameObject::addSpecialComponent(std::shared_ptr<Component> component)
{
    this->_specialComponents.push_back(component);
}

std::shared_ptr<RenderableComponent> GameObject::getRenderableComponent(){ return _renderable; }
std::shared_ptr<PhysicalComponent> GameObject::getPhysicalComponent(){ return _body; }
std::shared_ptr<InputComponent> GameObject::getInputComponent(){ return _input; }
std::shared_ptr<AIComponent> GameObject::getAIComponent(){ return _ai; }
std::vector<std::shared_ptr<Component>> GameObject::getSpecialComponents(){ return _specialComponents; }

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
