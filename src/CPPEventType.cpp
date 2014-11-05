//
//  CPPEventType.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "CPPEventType.h"
std::string CPPEventUtil::eventTypeAsString(CPPEventType type) {
    switch (type) {
        case Events_BASE:
            return "BASE EVENT";
        case Events_SCRIPT:
            return "SCRIPT EVENT";
        case Events_LOGGER:
            return "LOGGER EVENT";
        case Events_ERROR:
            return "ERROR";
        case Events_WARNING:
            return "WARNING";
        case Events_INFO:
            return "INFO";
        case Events_DEBUG:
            return "DEBUG";
        case Events_TEST:
            return "TEST EVENT";
        default:
            return "Not-implemented for this type, sry";
    }
};