#pragma once
#include "Renderable.h"

class RenderDataLoader {
public:
	RenderDataLoader();
	void loadPlainData(Renderable &renderable);
	void loadIndexedData(Renderable &renderable);
};