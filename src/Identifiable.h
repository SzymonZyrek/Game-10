//
//  Identifiable.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Identifiable : NSObject
@property(getter=getId,setter=setId:) long itsId;
-(id)init;
@end
