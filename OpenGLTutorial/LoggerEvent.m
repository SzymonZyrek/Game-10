//
//  LoggerEvent.m
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "LoggerEvent.h"

@implementation LoggerEvent
- (id) init
{
    self = [super initWithType: EventType_LOGGER];
    return self;
}
- (id) initWithMessage:(NSString *)message
{
    self = [super initWithType: EventType_LOGGER];
    if(self)
    {
        _message = message;
    }
    return self;
}

-(id) initAsWarningWithMessage: (NSString*) message
{
    self = [super initWithType: EventType_WARNING];
    if(self)
    {
        _message = message;
    }
    return self;
}

-(id) initAsInfoWithMessage: (NSString*) message
{
    self = [super initWithType: EventType_INFO];
    if(self)
    {
        _message = message;
    }
    return self;
}

-(id) initAsErrorWithMessage: (NSString*) message
{
    self = [super initWithType: EventType_ERROR];
    if(self)
    {
        _message = message;
    }
    return self;
}

-(id) initAsDebugWithMessage: (NSString*) message
{
    self = [super initWithType: EventType_DEBUG];
    if(self)
    {
        _message = message;
    }
    return self;
}

- (NSString*) description
{
    return [NSString stringWithFormat: @"#%lu:Log(%@):%@",[self getId], [EventTypes eventTypeAsString: [self getType]], _message];
}
@end
