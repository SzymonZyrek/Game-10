//
//  ConfigFile.h
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "GameFile.h"

@interface ConfigFile : GameFile
@property (setter=setProperties:, getter=getProperties) NSDictionary* properties;
@property (readonly, getter=isInitialized) BOOL initialized;
+(void)initialize;
+(NSString*)getConfigPath;
@end
