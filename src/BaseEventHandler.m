//
//  BaseEventHandler.m
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 24/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "BaseEventHandler.h"
#import "EventTypes.h"

@implementation BaseEventHandler
@synthesize handledTypes;
- (void) handleEvent:(Event*) event
{
    [NSException raise:@"Attepted to call handleEvent on abstract BaseEventHandler: " format: @"%@", event];
}
- (id) initWithHandledTypes: (NSArray*) theTypes
{
    if (self= [super init])
    {
        [self setHandledTypes: theTypes];
    }
    return self;
}
- (NSString*) description
{
    NSString* types = @"";
    for (id type in [self getHandledTypes])
    {
        types = [[types stringByAppendingString: [EventTypes eventTypeAsString: [type intValue]]] stringByAppendingString:@","];
    }
    // Remove last ","
    if ([types length]>0)
    {
        types = [types substringToIndex: [types length]-1];
    }
    return [NSString stringWithFormat: @"#%lu:EventHandler of class %@, for types: [%@]",[self getId], [self class], types];
}
@end
