//
//  Configuration.m
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "Configuration.h"
#import "ConfigFile.h"
#import "SimplePropertyConfigFile.h"

@implementation Configuration
-(instancetype) init
{
    self = [super init];
    if(self)
    {
        [self setProperties: [NSMutableDictionary dictionary]];
        NSArray* configFiles = @[@"test1", @"test2", @"test3"];
        for (id file in configFiles)
        {
            ConfigFile* cFile = [[SimplePropertyConfigFile alloc] initWithName: file];
            [self addProperties: [cFile getProperties]];
        }
    }
    return self;

}
-(void) addProperties: (NSDictionary*) props{
    [[self getProperties] addEntriesFromDictionary: props];
}
-(id) getPropertyByName: (NSString*) name
{
    return [[self getProperties] objectForKey: name];
}
-(void) printProps
{
    for(id key in [self getProperties])
    {
        NSLog(@"%@ -> %@", key, [[self getProperties] objectForKey: key]);
    }
}
@end
