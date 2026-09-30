//
//  RunPlayground.cpp
//  Game10
//
//  Created by Szymon Żyrek on 30/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "RunPlayground.h"
#include <stdio.h>
#include "CPPEventManager.h"
#include <iostream>
#include "GameLoop.h"
#include "CPPLogger.h"

void RunPlayground::p_main()
{
	std::cout 
		<< "----------------------\n"
		<< "|     RunPlayground     |\n"
		<< "----------------------\n";
    printf("Hello, %s\n", "Szymon");
	GameLoop loop;
	loop.start();
}