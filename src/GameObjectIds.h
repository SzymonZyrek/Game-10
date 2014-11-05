//
//  GameObject.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__GameObjectIds__
#define __OpenGLTutorial__GameObjectIds__

#include<vector>
#include "CPPIdentifiable.h"

// As GameObject, but different approach- component array indexes instead of pointers
class GameObjectIds : public CPPIdentifiable {
public:
    GameObjectIds();
    void setRenderableComponent(int component);
    void setPhysicalComponent(int component);
    void setInputComponent(int component);
    void setAIComponent(int component);
    void addSpecialComponent(int component);
    
    void setActive(bool value);
    
    bool hasRenderableComponent();
    bool hasPhysicalComponent();
    bool hasInputComponent();
    bool hasAIComponent();
    bool hasSpecialComponents();
    
    bool isActive();
private:
    bool _active;
    
    int _renderableIndex;
    int _bodyIndex;
    int _aiIndex;
    int _inputIndex;
    std::vector<int> _specialComponentIndices;
};

#endif /* defined(__OpenGLTutorial__GameObjectIds__) */
