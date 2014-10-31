//
//  GameObject.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject()
{
    this->_active = false;
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
    return _renderable;
}
bool GameObject::hasPhysicalComponent()
{
    return _body;
}
bool GameObject::hasInputComponent()
{
    return _input;
}
bool GameObject::hasAIComponent()
{
    return _ai;
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
