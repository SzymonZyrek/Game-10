#include "GameLoop.h"
#include <GLFW\glfw3.h>
#include "CPPLogger.h"
#include <sstream>
#include <regex>
#include "Tut01Renderer.h"
#define STEP 1/60

float GameLoop::frameTime;
float GameLoop::deltaTime;
float GameLoop::fps;

unsigned int accumulatorLogKey = Log::getInstance()->getLogPeriodicKey(5.0);

GameLoop::GameLoop()
{
	frameTime = (float)glfwGetTime();
	deltaTime = 0;
	fps = 0;
	_paused = true;
	_rendererInitialized = false;
	_accumulator = 0;
	_lastTime = frameTime;
}
GameLoop::~GameLoop()
{

}
void GameLoop::start()
{
	_paused = false;
	if (!_rendererInitialized)
	{
		_renderer.init();
		_rendererInitialized = true;
	}
	while (!_paused)
	{
		run();
	}
}
void GameLoop::pause()
{
	_paused = true;
}


void GameLoop::run()
{
	frameTime = (float)glfwGetTime();
	deltaTime = float(frameTime - _lastTime);
	_accumulator += deltaTime;
	fps = 1 / deltaTime;

	if (_accumulator >= STEP)
	{
		std::stringstream ss;
		std::stringstream paramstream;
		paramstream << _accumulator - STEP;
		std::string param = AGGREGATION_PARAM(paramstream.str());
		ss << "Accumulator overflow: Min: " << param << " Max: " << param << " Avg: " << param;
		Log::periodicAggregate(ss.str(), accumulatorLogKey, { MIN_DOUBLE, MAX_DOUBLE, AVERAGE_DOUBLE});
		_renderer.update();
		_renderer.render();
		_accumulator = 0;
	}

	_lastTime = frameTime;
}