//
//  GameObject.h
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__GameObject__
#define __Game10__GameObject__

#include<vector>
#include<memory>

class Component;
class RenderableComponent;
class PhysicalComponent;
class AIComponent;
class InputComponent;
class GameObjectIds;

class GameObject {
public:
	unsigned int gameObjectId = 0;
    GameObject();
	GameObject(GameObject &other);
	void setRenderableComponent(std::shared_ptr<RenderableComponent> component);
	void setPhysicalComponent(std::shared_ptr<PhysicalComponent> component);
	void setInputComponent(std::shared_ptr<InputComponent> component);
	void setAIComponent(std::shared_ptr<AIComponent> component);
	void addSpecialComponent(std::shared_ptr<Component> component);

	std::shared_ptr<RenderableComponent> getRenderableComponent();
	std::shared_ptr<PhysicalComponent> getPhysicalComponent();
	std::shared_ptr<InputComponent> getInputComponent();
	std::shared_ptr<AIComponent> getAIComponent();
	std::vector<std::shared_ptr<Component>> getSpecialComponents();
    
    void setActive(bool value);
    
    bool hasRenderableComponent();
    bool hasPhysicalComponent();
    bool hasInputComponent();
    bool hasAIComponent();
    bool hasSpecialComponents();
    
    bool isActive();
private:
    bool _active;

	std::shared_ptr<RenderableComponent> _renderable;
	std::shared_ptr<PhysicalComponent> _body;
	std::shared_ptr<AIComponent> _ai;
	std::shared_ptr< InputComponent> _input;
	std::vector<std::shared_ptr<Component>> _specialComponents;
};

#endif /* defined(__Game10__GameObject__) */
