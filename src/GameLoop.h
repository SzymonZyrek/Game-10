#pragma once
#include <vector>
#include <memory>
#include "SimpleRenderer.h"
#include "FXSurfaceRenderer.h"
#include "Scene.h"

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
	Scene _scene;
	std::unique_ptr<BaseRenderer> _renderer;
	float _lastTime;
	float _accumulator = 0.0;
	bool _paused;
	bool _rendererInitialized;
	void run();
};