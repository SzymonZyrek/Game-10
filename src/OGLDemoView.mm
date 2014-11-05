//
//  OGLDemoView.m
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 05/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import "OGLDemoView.h"
#import <OpenGL/gl.h>
#import "Configuration.h"
#import "LocalisedResourceFile.h"
#import "LoggerEvent.h"
#import "EventManager.h"
#import "LogHandler.h"
#import "Logger.h"

static double TIME_INTERVAL = 0.01;

@implementation OGLDemoView
- (id)initWithFrame:(NSRect)frame
{
  self = [super initWithFrame:frame];
  // set best avaiable resolution
  if (self) {  
   [self wantsBestResolutionOpenGLSurface];
}
  return self;
}
- (void)prepareOpenGL
{
  // v-sync
  GLint swapInt = 1;
  [[self openGLContext]
         setValues:&swapInt
         forParameter:NSOpenGLCPSwapInterval];
  _renderer.init();
}
-(void)awakeFromNib
{
// render each TIME_INTERVAL

    //Configuration* config = [[Configuration alloc] init];
    //[config printProps];
    //ResourceFile* file = [[LocalisedResourceFile alloc] initWithName:@"strings.txt"];
    //NSString* fileDataAsString = [[NSString alloc] initWithData: [file getRawData]
    //                                               encoding:NSUTF8StringEncoding];
    //NSLog(@"Data:\n%@",fileDataAsString);
    //[OGLDemoView gay_kinda_main_for_quick_testing_and_prototyping_in_objc];
    [self runRendererLoop];
}
- (void) runRendererLoop
{
    _renderTimer = [NSTimer timerWithTimeInterval:TIME_INTERVAL
                                           target:self
                                         selector:@selector(nextFrame:)
                                         userInfo:nil
                                          repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:_renderTimer
                                 forMode:NSDefaultRunLoopMode];
    //Ensure timer fires during resize
    [[NSRunLoop currentRunLoop]
     addTimer:_renderTimer
     forMode:NSEventTrackingRunLoopMode];
}
// NSRunLoop renderer update callback
- (void)nextFrame:(id)sender
{
    // update renderer
    _renderer.update();
    // trigger redraw
    [self setNeedsDisplay:YES];
}
// NSRunLoop renderer render callback
- (void)drawRect:(NSRect)bounds
{
    NSRect backingBounds = [self convertRectToBacking:[self bounds]];
    glViewport(0,0, backingBounds.size.width, backingBounds.size.height);
    _renderer.render();
}
+(void) gay_kinda_main_for_quick_testing_and_prototyping_in_objc
{
    id<EventHandler> handler = [[LogHandler alloc] initWithHandledTypes: @[
                                                                                 [NSNumber numberWithInt: EventType_ERROR],
                                                                                 [NSNumber numberWithInt: EventType_WARNING],
                                                                                 [NSNumber numberWithInt: EventType_INFO]
                                                                                 ]
                                ];
    [[EventManager GlobalEventManager] registerEventHandler: handler];
    [Logger info: @"Logger initialized"];
    [Logger info: @"GlobalEventManager initialized"];
    [Logger debug: @"aaaaaah fuck this"];
    [[EventManager GlobalEventManager] handleEvents];
}
-(void) resetShift
{
    _renderer.resetShift();
}
@end
