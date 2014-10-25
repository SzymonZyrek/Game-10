//
//  LocalisedResourceFile.h
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "ResourceFile.h"

@interface LocalisedResourceFile : ResourceFile
@property (setter=setLocale:, getter=getLocale) NSString* locale;
-(instancetype) initWithName: (NSString*) name;
+(NSString*) getLocalisedResourcesPath;
@end
