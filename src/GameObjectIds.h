//
//  GameObject.h
//  Game10
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__GameObjectIds__
#define __Game10__GameObjectIds__

#include<vector>
#include "CPPIdentifiable.h"

static unsigned int __lastGameObjectId = 0;

// As GameObject, but different approach- component array indexes instead of pointers
class GameObjectIds : public CPPIdentifiable {
public:
	unsigned int gameObjectId = ++__lastGameObjectId;
    GameObjectIds();
	void setRenderableComponent(unsigned int component);
	void setPhysicalComponent(unsigned int component);
	void setInputComponent(unsigned int component);
	void setAIComponent(unsigned int component);
	void addSpecialComponent(unsigned int component);

	unsigned int getRenderableComponent();
	unsigned int getPhysicalComponent();
	unsigned int getInputComponent();
	unsigned int getAIComponent();

    void setActive(bool value);
    
    bool hasRenderableComponent();
    bool hasPhysicalComponent();
    bool hasInputComponent();
    bool hasAIComponent();
    bool hasSpecialComponents();
	void initWith(GameObjectIds &other);
    bool isActive();
	void clear();
private:
    bool _active;
    
    int _renderableIndex;
    int _bodyIndex;
    int _aiIndex;
    int _inputIndex;
    std::vector<int> _specialComponentIndices;
};

#endif /* defined(__Game10__GameObjectIds__) */
