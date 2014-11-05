//
//  GameFile.m
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 27/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "GameFile.h"
#import <Foundation/Foundation.h>

@implementation GameFile
-(instancetype) init
{
    return [self initWithExtension: @""];
}
-(instancetype) initWithExtension:(NSString *) extension
{
    return [self initWithExtension: extension andCategory: GENERIC];
}
-(instancetype) initWithExtension:(NSString *)extension
                      andCategory:(GameFileCategory) category
{
    self = [super init];
    if (self)
    {
        [self setExtension: extension];
        [self setCategory: category];
    }
    return self;
}
-(instancetype) initWithFilePath: (NSString*) path
{
    return [self initWithFilePath: path andCategory: GENERIC];
}
-(instancetype) initWithFilePath: (NSString*) path
                     andCategory:(GameFileCategory) category
{
    self = [self initWithExtension: [path pathExtension] andCategory: category];
    if(self)
    {
        [self setFilePath:path];
    }
    return self;
}

-(NSData*) getRawData
{
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath: [self getFilePath]]==YES)
    {
        return [fileManager contentsAtPath: [self getFilePath]];
    }
    else
    {
        NSLog(@"No file at %@", [self getFilePath]);
        return nil;
    }
}
@end
