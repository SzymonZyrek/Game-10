#pragma once
#include <vector>
#include <memory>
#include "Tut01Renderer.h"

class GameLoop
{
public:
	static float frameTime;
	static float deltaTime;
	static float fps;
	GameLoop();
	~GameLoop();
	void start();
	void pause();
private:
	Tut01Renderer _renderer;
	float _lastTime;
	float _accumulator = 0.0;
	bool _paused;
	bool _rendererInitialized;
	void run();
};