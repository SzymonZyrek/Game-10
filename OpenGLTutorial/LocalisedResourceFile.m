//
//  LocalisedResourceFile.m
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "LocalisedResourceFile.h"

static NSString* DEFAULT_LOCALE = @"PL";

@implementation LocalisedResourceFile

-(instancetype) initWithName: (NSString*) name
{
    self = [super initWithName: name];
    if(self)
    {
        [self setLocale: DEFAULT_LOCALE];
        [self setFilePath: [[[LocalisedResourceFile getLocalisedResourcesPath]
                             stringByAppendingPathComponent: [self getName]]
                            stringByAppendingString: [self getExtension]]];
    }
    return self;
}
+(void) initialize
{
    NSLog(@"LocalisedResourceFile initialize");
}
+(NSString*) getLocalisedResourcesPath
{
    return [[NSString stringWithString: [self getResourcesPath]] stringByAppendingPathComponent: DEFAULT_LOCALE];
}

@end
