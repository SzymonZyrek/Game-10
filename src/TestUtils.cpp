//
//  TestUtils.cpp
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestUtils.h"
#include "CPPIdentifiable.h"
#include <memory>
#include <iostream>
#include "CPPQueue.h"
#include "TestResult.h"
#include <string>
#include <sstream>
#include <set>

TestResult TestUtils::doTest(bool stopOnFailure)
{
testContext(
    runTest(testCPPIdentifiable)
    runTest(testCPPQueue)
)
};

TestResult TestUtils::testCPPIdentifiable(bool stopOnFailure){
testContext(
    std::set<unsigned long> assigned;
    for (int i = 0; i < 10; i++)
    {
        std::shared_ptr<CPPIdentifiable> identifiable = std::make_shared<CPPIdentifiable>();
        assertEquals(assigned.find(identifiable->getId()),assigned.end(),"Not unique id assigned")
        assigned.emplace(identifiable->getId());
    }
)
};
TestResult TestUtils::testCPPQueue(bool stopOnFailure){
testContext(
    CPPQueue<int> queue(4);
    assert(queue.isEmpty(),"Queue isn't \"empty\" while it should be")
    for (int i = 0; i < 4; i++)
    {
        assert(!queue.isFull(),"Queue is \"full\" while it shouldn't be")
        try {
            queue.enqueue(i);
        } catch (std::runtime_error &e) {
            assert(false, "Could not enqueue, when it should work")
        }
        assert(!queue.isEmpty(),"Queue is \"empty\" while it shouldn't be")
    }
    assert(queue.isFull(),"Queue isn't \"full\" while it should be")
    assertEquals(queue.getSize(),4,"Queue size is wrong")
    try{
        queue.enqueue(6);
        assert(false, "Queue allowed to enqueue when full")
    } catch (std::runtime_error &e) {
        // all ok, this should happen
    }
            
    for (int i = 0; i < 4; i++)
    {
        assert(!queue.isEmpty(),"Queue is \"empty\" while it shouldn't be")
        assertEquals(queue.dequeue(),i,"Queue.dequeue() returned wrong value")
        assert(!queue.isFull(),"Queue is \"full\" while it shouldn't be")
    }
    assert(queue.isEmpty(),"Queue isn't \"empty\" while it should be")
    queue.enqueue(12);
    assert(!queue.isEmpty(),"Queue is \"empty\" while it shouldn't be")
    queue.enqueue(15);
    assert(!queue.isEmpty(),"Queue is \"empty\" while it shouldn't be")
    assertEquals(queue.dequeue(),12,"Queue coherency lost after passing size")
    assertEquals(queue.dequeue(),15,"Queue coherency lost after passing size")
)
};