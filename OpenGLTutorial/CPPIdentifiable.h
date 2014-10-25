//
//  CPPIdentifiable.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__CPPIdentifiable__
#define __OpenGLTutorial__CPPIdentifiable__
class CPPIdentifiable {
public:
    CPPIdentifiable();
    virtual ~CPPIdentifiable();
    unsigned long getId() const;
private:
    unsigned long _id;
};

#endif /* defined(__OpenGLTutorial__CPPIdentifiable__) */
