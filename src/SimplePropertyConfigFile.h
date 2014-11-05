//
//  SimplePropertyConfigFile.h
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "ConfigFile.h"

@interface SimplePropertyConfigFile : ConfigFile
@property (setter=setName:, getter=getName) NSString* name;
-(instancetype) initWithName: (NSString*) name;
+(void)initialize;
@end
