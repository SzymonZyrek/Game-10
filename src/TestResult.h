//
//  TestResult.h
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#ifndef __Game10__CPPResult__
#define __Game10__CPPResult__

#include <string>
#include <vector>
class TestResult {
public:
    void print();
    void print(std::string prefix);
    operator bool() const;
    TestResult & operator+=(const TestResult &other);
    TestResult();
    TestResult(std::string errorMessage);
    void addError(std::string error);
    std::vector<std::string> getErrors() const;
private:
    std::vector<std::string> errors;
};
#endif
