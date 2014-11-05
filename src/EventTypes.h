//
//  EventTypes.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//
#import<Foundation/Foundation.h>
#ifndef OpenGLTutorial_EventTypes_h
#define OpenGLTutorial_EventTypes_h
enum EventType{EventType_LOGGER, EventType_SCRIPT, EventType_BASE, EventType_WARNING, EventType_INFO, EventType_ERROR, EventType_DEBUG, EventType_TEST};
#endif
@interface EventTypes : NSObject
+(NSString*) eventTypeAsString:(enum EventType) aType;
@end

