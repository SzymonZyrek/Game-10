//
//  LogHandler.m
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "LogHandler.h"
#import "LoggerEvent.h"

static const NSString* INFO_FORMAT = @"INFO: %@";
static const NSString* DEBUG_FORMAT = @"DEBUG: %@";
static const NSString* WARNING_FORMAT = @"WARNING: %@";
static const NSString* ERROR_FORMAT = @"ERROR: %@";

@implementation LogHandler
- (void) handleEvent:(Event*) event
{
    if (! [[event class] isSubclassOfClass: [LoggerEvent class]])
    {
        [self printError: @"Log handler only services events that derive from LoggerEvent class!"];
    }
    LoggerEvent* castEvent = (LoggerEvent*) event;
    NSString* message = [castEvent getMessage];
    switch([event getType])
    {
        case EventType_ERROR:
            [self printError: message];
            break;
        case EventType_WARNING:
            [self printWarning: message];
            break;
        case EventType_INFO:
            [self printInfo: message];
            break;
        case EventType_DEBUG:
            [self printDebug: message];
            break;
        default: break;

    }
}
-(void) printInfo: (NSString*) message
{
    NSLog(INFO_FORMAT,message);
}
-(void) printWarning: (NSString*) message
{
    NSLog(WARNING_FORMAT,message);
}
-(void) printError: (NSString*) message
{
    NSLog(ERROR_FORMAT,message);
}
-(void) printDebug: (NSString*) message
{
    NSLog(DEBUG_FORMAT,message);
}

@end
