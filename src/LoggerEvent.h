//
//  LoggerEvent.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "Event.h"

@interface LoggerEvent : Event
@property(getter=getMessage,setter=setMessage:) NSString* message;
- (id) init;
- (id) initWithMessage:(NSString*) message;
-(id) initAsWarningWithMessage: (NSString*) message;
-(id) initAsErrorWithMessage: (NSString*) message;
-(id) initAsInfoWithMessage: (NSString*) message;
-(id) initAsDebugWithMessage: (NSString*) message;
@end
