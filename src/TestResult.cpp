//
//  TestResult.cpp
//  Game10
//
//  Created by Szymon Żyrek on 25/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "TestResult.h"
#include <iostream>
#include <sstream>
TestResult::TestResult()
{
    
}
TestResult::TestResult(std::string errorMessage)
{
    errors.push_back(errorMessage);
}
void TestResult::addError(std::string errorMessage)
{
    errors.push_back(errorMessage);
}
TestResult::operator bool() const {
    return errors.size()==0;
}
TestResult & TestResult::operator+=(const TestResult &other){
    for (std::string error : other.getErrors()){
        this->addError(error);
    }
    return *this;
}

std::vector<std::string> TestResult::getErrors() const {
    return this->errors;
}
void TestResult::print(std::string prefix)
{
    std::cout << "- " << prefix << ":";
    print();
}
void TestResult::print()
{
    std::stringstream ss;
    if (errors.size()==0){
        ss << " OK";
    }else{
        ss << "ERRORS:" << std::endl;
        for (std::string str : errors){
            ss << str << std::endl;
        }
    }
	ss << std::endl;
	std::cout << ss.str();
}