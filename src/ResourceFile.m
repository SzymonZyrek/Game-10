//
//  ResourceFile.m
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "ResourceFile.h"

@implementation ResourceFile
+(void) initialize
{
    NSLog(@"ResourceFile initialize");
}
-(instancetype) initWithName: (NSString*) name
{
    self = [self initWithExtension:  @"" andCategory: RESOURCE];
    if(self)
    {
        [self setName: name];
        [self setFilePath: [[[ResourceFile getResourcesPath] stringByAppendingPathComponent: [self getName]]
                            stringByAppendingString: [self getExtension]]];
    }
    return self;
}

+(NSString*) getResourcesPath
{
    return [[NSString stringWithString: GAME_FILES_ROOT] stringByAppendingPathComponent: @"resources"];
}
@end
