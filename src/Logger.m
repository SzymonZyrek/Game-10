//
//  Logger.m
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "Logger.h"
#import "EventManager.h"
#import "LoggerEvent.h"

@implementation Logger
+(void) info: (NSString*) message
{
    Event* event = [[LoggerEvent alloc] initAsInfoWithMessage:message];
    [[EventManager GlobalEventManager] registerEvent: event];
}
+(void) warn: (NSString*) message
{
    Event* event = [[LoggerEvent alloc] initAsWarningWithMessage:message];
    [[EventManager GlobalEventManager] registerEvent: event];
}
+(void) error: (NSString*) message
{
    Event* event = [[LoggerEvent alloc] initAsErrorWithMessage:message];
    [[EventManager GlobalEventManager] registerEvent: event];
}
+(void) debug: (NSString*) message
{
    Event* event = [[LoggerEvent alloc] initAsDebugWithMessage:message];
    [[EventManager GlobalEventManager] registerEvent: event];
}
@end
