//
//  EventTypes.m
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EventTypes.h"

@implementation EventTypes
+(NSString*) eventTypeAsString: (enum EventType) aType
{
    switch (aType) {
        case EventType_BASE:
            return @"BASE EVENT";
        case EventType_SCRIPT:
            return @"SCRIPT EVENT";
        case EventType_LOGGER:
            return @"LOGGER EVENT";
        case EventType_ERROR:
            return @"ERROR";
        case EventType_WARNING:
            return @"WARNING";
        case EventType_INFO:
            return @"INFO";
        case EventType_DEBUG:
            return @"DEBUG";
        default:
            return @"Not-implemented for this type, sry";
    }
}
@end