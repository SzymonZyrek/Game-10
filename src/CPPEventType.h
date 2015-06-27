//
//  CPPEventType.h
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__CPPEventType__
#define __Game10__CPPEventType__
enum CPPEventType{Events_LOGGER, Events_SCRIPT, Events_BASE, Events_WARNING, Events_INFO, Events_ERROR, Events_DEBUG, Events_TEST};
#include <string>
class CPPEventUtil {
public:
    static std::string eventTypeAsString(CPPEventType aType);
};
#endif /* defined(__Game10__CPPEventType__) */
