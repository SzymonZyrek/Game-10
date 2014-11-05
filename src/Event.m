#import <Foundation/Foundation.h>
#import "Event.h"
#import "EventTypes.h"

@implementation Event
//TODO: provide implementation
- (id) initWithType:(enum EventType) aType
{
    self = [super init];
    if (self) {
        _type = aType;
    }
    return self;
}
- (id) init
{
    return [self initWithType: EventType_BASE];
}
- (NSString*) description
{
    return [NSString stringWithFormat: @"Event of class %@, of type %@, id: %lu", [self class], [EventTypes eventTypeAsString: _type], [self getId]];
}
@end