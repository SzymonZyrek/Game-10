//
//  SimpleTextResourceFile.m
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "SimpleTextResourceFile.h"
#import "GameFile.h"

@implementation SimpleTextResourceFile

-(instancetype) initWithName: (NSString*) name
{
    self = [super initWithName: name];
    if(self)
    {
        [self setExtension: @".txt"];
        [self setFilePath: [[self getFilePath] stringByAppendingString: [self getExtension]]];
    }
    return self;
}
-(NSString*) getDataAsString
{
    return [[NSString alloc] initWithData: [self getRawData]
                                 encoding:NSUTF8StringEncoding];
}
+(void) initialize
{
    NSLog(@"SimpleTextResourceFile initialize");
}
@end
