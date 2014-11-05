//
//  Logger.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Logger : NSObject
+(void) info: (NSString*) message;
+(void) warn: (NSString*) message;
+(void) error: (NSString*) message;
+(void) debug: (NSString*) message;
@end
