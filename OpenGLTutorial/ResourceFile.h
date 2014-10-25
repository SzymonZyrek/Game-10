//
//  ResourceFile.h
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "GameFile.h"

static NSString* RESOURCES_PATH;

@interface ResourceFile : GameFile
@property (setter=setName:, getter=getName) NSString* name;
-(instancetype) initWithName: (NSString*) name;
+(NSString*) getResourcesPath;
@end
