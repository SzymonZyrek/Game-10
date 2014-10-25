//
//  CPPEvent.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__CPPEvent__
#define __OpenGLTutorial__CPPEvent__

#include <stdio.h>
#include "CPPIdentifiable.h"
#include "CPPEventType.h"
#include <iostream>
class CPPEvent : public CPPIdentifiable
{
public:
    CPPEvent(CPPEventType type);
    CPPEventType getType();
    friend std::ostream& operator<<(std::ostream& os, const CPPEvent& e);
private:
    CPPEventType _type;
};
#endif /* defined(__OpenGLTutorial__CPPEvent__) */
