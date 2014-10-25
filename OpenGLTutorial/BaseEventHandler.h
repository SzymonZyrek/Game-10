//
//  BaseEventHandler.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "Identifiable.h"
#import "EventHandler.h"

@interface BaseEventHandler : Identifiable <EventHandler>
- (id) initWithHandledTypes: (NSArray*) types;
@end
