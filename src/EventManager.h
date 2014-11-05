#import <Foundation/Foundation.h>
#import "Identifiable.h"
#import "EventTypes.h"
#import "EventHandler.h"
#import "Queue.h"

@class Event;
@class EventHandler;

@interface EventManager : Identifiable
@property(getter=getEventQueue,setter=setEventQueue:) Queue* eventQueue;
@property(getter=getHandlersById,setter=setHandlersById:) NSMutableDictionary* handlersById;
@property(getter=getHandlersIdsByType,setter=setHandlersIdsByType:) NSMutableDictionary* handlersIdsByType;
+(EventManager*)GlobalEventManager;
- (void) registerEvent: (Event*) event;
- (void) notify: (EventHandler*) handler withEvent:(Event*) Event;
- (void) registerEventHandler:(id<EventHandler>) handler;
- (id) init;
- (void) handleEvents;
@end