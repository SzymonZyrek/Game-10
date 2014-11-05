//
//  SimpleTextResourceFile.h
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameFile.h"
#import "LocalisedResourceFile.h"

@interface SimpleTextResourceFile : LocalisedResourceFile
-(NSString*) getDataAsString;
-(instancetype) initWithName:(NSString *)name;
+(void) initialize;
@end
