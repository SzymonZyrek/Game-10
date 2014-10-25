//
//  LogHandler.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//
#import "BaseEventHandler.h"

@interface LogHandler : BaseEventHandler
-(void) printInfo: (NSString*) message;
-(void) printWarning: (NSString*) message;
-(void) printError: (NSString*) message;
-(void) printDebug: (NSString*) message;
@end
