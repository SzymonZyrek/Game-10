//
//  Playground.cpp
//  OpenGLTutorial
//
//  Created by Szymon Żyrek on 30/10/14.
//  Copyright (c) 2014 Szymon Żyrek. All rights reserved.
//

#include "Playground.h"
#include <stdio.h>
#include "CPPEventManager.h"
#include <iostream>
#include "GameLoop.h"

void Playground::p_main()
{
	std::cout 
		<< "----------------------\n"
		<< "|     Playground     |\n"
		<< "----------------------\n";
    printf("Hello, %s\n", "Szymon");
	GameLoop loop;
	loop.start();
}