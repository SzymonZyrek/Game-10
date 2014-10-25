#import <Foundation/Foundation.h>
#import "Identifiable.h"
#import "EventTypes.h"

@interface Event : Identifiable
@property(getter=getType,setter=setType:) enum EventType type;
- (id) initWithType:(enum EventType) aType;
- (id) init;
@end