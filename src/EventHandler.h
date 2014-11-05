#import <Foundation/Foundation.h>
#import "Identifiable.h"

@class Event;

@protocol EventHandler <NSObject>
@property(getter=getHandledTypes,setter=setHandledTypes:) NSArray* handledTypes;
- (void) handleEvent:(Event*) event;
- (unsigned long)getId;
@end