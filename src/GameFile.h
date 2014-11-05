//
//  GameFile.h
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 27/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString* GAME_FILES_ROOT = @"/Users/szymonzyrek/Documents/GAME_FILES";

typedef NS_ENUM(NSUInteger, GameFileCategory) {
    TEXTURE,
    MESH,
    CONFIGURATION,
    SCRIPT,
    RESOURCE,
    GENERIC
};

@interface GameFile : NSObject
    @property (getter=getFilePath, setter=setFilePath:) NSString* filePath;
    @property (getter=getExtension, setter=setExtension:) NSString* extension;
    @property (getter=getCategory, setter=setCategory:) GameFileCategory category;
    @property (getter=getName, setter=setName:) NSString* name;
    -(instancetype) init;
    -(instancetype) initWithFilePath: (NSString*) path;
    -(instancetype) initWithExtension: (NSString*) extension;

    -(instancetype) initWithFilePath: (NSString*) path andCategory:(GameFileCategory) category;
    -(instancetype) initWithExtension:(NSString *)extension
                          andCategory:(GameFileCategory) category;
    -(NSData*) getRawData;
@end
