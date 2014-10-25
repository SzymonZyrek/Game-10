//
//  AppDelegate.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 05/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "OGLDemoView.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
- (IBAction)resetButtonClicked:(id)sender;
@property (weak) IBOutlet OGLDemoView *glView;


@end

