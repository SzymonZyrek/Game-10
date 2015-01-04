//
//  GameObject.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__GameObject__
#define __OpenGLTutorial__GameObject__

#include<vector>


class Component;
class RenderableComponent;
class PhysicalComponent;
class AIComponent;
class InputComponent;
class GameObjectIds;

class GameObject {
public:
    GameObject();
	GameObject(GameObject &other);
	void setRenderableComponent(RenderableComponent* component);
    void setPhysicalComponent(PhysicalComponent* component);
    void setInputComponent(InputComponent* component);
    void setAIComponent(AIComponent* component);
    void addSpecialComponent(Component* component);

	GameObjectIds* id;

    RenderableComponent* getRenderableComponent();
    PhysicalComponent* getPhysicalComponent();
    InputComponent* getInputComponent();
    AIComponent* getAIComponent();
    std::vector<Component*> getSpecialComponents();
    
    void setActive(bool value);
    
    bool hasRenderableComponent();
    bool hasPhysicalComponent();
    bool hasInputComponent();
    bool hasAIComponent();
    bool hasSpecialComponents();
    
    bool isActive();
private:
    bool _active;

    RenderableComponent* _renderable;
    PhysicalComponent* _body;
    AIComponent* _ai;
    InputComponent* _input;
    std::vector<Component*> _specialComponents;
};

#endif /* defined(__OpenGLTutorial__GameObject__) */
