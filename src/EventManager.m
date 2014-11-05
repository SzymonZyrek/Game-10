#import <Foundation/Foundation.h>
#import "EventManager.h"
#import "EventHandler.h"
#import "Event.h"
static EventManager* _globalEventManager;
@implementation EventManager


+(EventManager*)GlobalEventManager
{
    if (_globalEventManager==nil)
    {
        _globalEventManager = [[EventManager alloc] init];
    }
    return _globalEventManager;
}
- (void) registerEvent:(Event*) event
{
    [_eventQueue enqueuee: event];
#ifdef __DEBUG_EVENTS
    NSLog(@"%@ queueed:    %@", self, event);
#endif
}
//TODO: provide implementation
- (void) notify:(EventHandler*) handler withEvent:(Event*) event
{
    //NSLog(@"%@ notifying:  %@ with %@", self, handler, event);
#ifdef __DEBUG_EVENTS
    NSLog(@"Not implemented:\n EventManager::-(void)notify:(EventHandler*)handler withEvent:(Event*)event");
#endif
}

- (void) registerEventHandler:(id<EventHandler>) handler
{
    NSNumber* handlerId = [NSNumber numberWithUnsignedLong:[handler getId]];
    
    for (NSNumber* val in [handler getHandledTypes])
    {
        if ([_handlersIdsByType objectForKey: val]==nil)
        {
#ifdef __DEBUG_EVENTS
            NSLog(@"%@ new event array for type: %@", self, [EventTypes eventTypeAsString: [val intValue]]);
#endif
            [_handlersIdsByType setObject: [[NSMutableArray alloc]init] forKey: val];
        }
        [[_handlersIdsByType objectForKey: val] addObject: handlerId];
    }
    [_handlersById setObject: handler forKey: handlerId];
#ifdef __DEBUG_EVENTS
    NSLog(@"%@ registered: %@", self, handler);
#endif
}

- (id) init
{
    self = [super init];
    if (self)
    {
        _eventQueue = [[Queue alloc] initWithSize: 20];
        _handlersById = [[NSMutableDictionary alloc] init];
        _handlersIdsByType = [[NSMutableDictionary alloc] init];
    }
    return self;
}

-(id) getEvent
{
    return [_eventQueue dequeuee];
}

- (void) processEvent: (Event*) event
{
    NSNumber* typeNum = [NSNumber numberWithInt: [event getType]];
    if ([_handlersIdsByType objectForKey: typeNum]==nil)
    {
        return;
    }
    else
    {
        for (NSNumber* handlerId in [_handlersIdsByType objectForKey: typeNum])
        {
            [[_handlersById objectForKey: handlerId] handleEvent: event];
        }
    }
}

- (void) handleEvents
{
#ifdef __DEBUG_EVENTS
    NSLog(@"%@ handling events:",self);
#endif
    while (![_eventQueue isEmpty])
    {
        Event* nextEvent = [_eventQueue dequeuee];
#ifdef __DEBUG_EVENTS
        NSLog(@"%@ proccesing: %@",self, nextEvent);
#endif
        [self processEvent: nextEvent];
    }
#ifdef __DEBUG_EVENTS
    NSLog(@"%@ finished handling events",self);
#endif
}
- (NSString*) description
{
    return [NSString stringWithFormat: @"#%lu:EventManager", [self getId]];
}
@end