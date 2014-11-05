//
//  OGLDemoView.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 05/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "Tut01Renderer.h"

@interface OGLDemoView : NSOpenGLView
@property(getter=getRenderTimer,setter=setRenderTimer:) NSTimer* renderTimer;
@property(getter=getRenderer,setter=setRenderer:) Tut01Renderer renderer;
-(void) drawRect: (NSRect)bounds;
-(void) resetShift;
@end

