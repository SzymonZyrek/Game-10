//
//  SimplePropertyConfigFile.m
//  ConsoleApp01
//
//  Created by Szymon Żyrek on 28/09/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "SimplePropertyConfigFile.h"


@implementation SimplePropertyConfigFile
-(instancetype) initWithName: (NSString*) name
{
    self = [self initWithExtension:  @".conf" andCategory: CONFIGURATION];
    if(self)
    {
        [self setName: name];
        [self setFilePath: [[[[self class] getConfigPath] stringByAppendingPathComponent: [self getName]]
                           stringByAppendingString: [self getExtension]]];
        NSMutableDictionary *props = [NSMutableDictionary dictionary];
        NSString* dataAsString = [[NSString alloc] initWithData: [self getRawData]
                                                       encoding:NSUTF8StringEncoding];
        NSArray *dataSplitByLines = [dataAsString componentsSeparatedByCharactersInSet: [NSCharacterSet newlineCharacterSet]];
        for (int i = 0; i < [dataSplitByLines count]; i++)
        {
            NSString* line = [dataSplitByLines objectAtIndex: i];
            if([line isEqualToString: @""])
            {
                break;
            }
            NSArray *keyValuePair = [line componentsSeparatedByString: @"="];
            if ([keyValuePair count]==2)
            {
                NSString* key = [keyValuePair objectAtIndex: 0];
                NSString* value = [keyValuePair objectAtIndex: 1];
                [props setValue: value forKey: key];
            }
            else
            {
                NSLog(@"Unsupported entry: \"%@\" in SimplePropertyConfigFile %@", line, [self getFilePath]);
            }
        }
        [self setProperties: props];
    }
    return self;
}
+(void)initialize
{
    NSLog(@"SimplePropertyConfigFile initialize");
}
@end
