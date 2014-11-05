//
//  Queue.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Queue : NSObject
@property(getter=getHead) int head;
@property(getter=getTail) int tail;
@property(getter=getSize,setter=setSize:) int size;
@property(getter=getIterator) NSMutableArray* array;
@property(getter=isEmpty) bool empty;
-(void) enqueuee: (id) object;
-(id) dequeuee;
-(id) initWithSize: (int) theSize;
@end
