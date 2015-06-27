//
//  CPPEventHandler.h
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__CPPEventHandler__
#define __Game10__CPPEventHandler__

#include <vector>
#include "CPPEvent.h"
#include "CPPEventType.h"
#include "CPPIdentifiable.h"
#include <memory>
#include <initializer_list>

class CPPEventHandler : public CPPIdentifiable {
public:
	CPPEventHandler(std::initializer_list<CPPEventType> &types);
    virtual ~CPPEventHandler();
    std::vector<CPPEventType> getHandledTypes() const;
    virtual void handleEvent(std::shared_ptr<CPPEvent> event) = 0;
    friend std::ostream& operator<<(std::ostream& os, const CPPEventHandler& e);
private:
    std::vector<CPPEventType> _types;
};
#endif
