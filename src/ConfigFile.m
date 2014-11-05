//
//  ConfigFile.m
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "ConfigFile.h"

@implementation ConfigFile
+(void) initialize
{
    NSLog(@"ConfigFile initialize");
}
+(NSString*) getConfigPath
{
    return [[NSString stringWithString: GAME_FILES_ROOT ] stringByAppendingString: @"/config"];
}
@end
