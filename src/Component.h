//
//  Component.h
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 31/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __OpenGLTutorial__Component__
#define __OpenGLTutorial__Component__

#include <iostream>

class Component {
public:
    Component();
    void setDaddyId(int daddy);
    int getDaddyId();
	bool isActive();
	void setActive(bool active);
    virtual void update(double dT) = 0;
	operator bool() const;
protected:
    int _daddyId = -1;
	bool _active = false;
	bool _isNullComponent;
protected:
	unsigned int _logPeriodicKey;
};

#endif /* defined(__OpenGLTutorial__Component__) */
