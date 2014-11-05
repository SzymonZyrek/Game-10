//
//  Queue.m
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "Queue.h"

@implementation Queue
@synthesize size = _size;
-(void) enqueuee: (id) object
{
    [_array insertObject:object atIndex: _tail];
    _empty = NO;
    _tail = (_tail+1)%_size;
    if (_tail == _head)
    {
        [NSException raise:@"Tail reached head!" format:@"on queuee: %@", self];
    }
}
-(id) dequeuee
{
    if (_empty)
    {
        return nil;
    }
    id result = [_array objectAtIndex: _head];
    _head = (_head + 1)%_size;
    if (_head == _tail)
    {
        _empty = YES;
    }
    return result;
}
-(void) setSize: (int) size
{
    NSMutableArray* newArray = [NSMutableArray arrayWithCapacity:size];
    [newArray addObjectsFromArray: _array];
    _array = newArray;
}
-(int) getSize
{
    return _size;
}
-(id) initWithSize: (int) size
{
    self = [super init];
    if (self)
    {
        _array = [NSMutableArray arrayWithCapacity: size];
        _size = size;
        _head = 0;
        _tail = 0;
        _empty = YES;
    }
    return self;
}
@end
