//
//  Configuration.h
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Configuration : NSObject
@property (setter=setProperties:, getter=getProperties) NSMutableDictionary* properties;
-(instancetype) init;
-(id) getPropertyByName: (NSString*) name;
-(void) printProps;
@end
