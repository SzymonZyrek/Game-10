#include "RenderDataLoader.h"

RenderDataLoader::RenderDataLoader(){

}

void RenderDataLoader::loadIndexedData(Renderable &renderable){

	glGenBuffers(1, &renderable.vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, (renderable.indexedVertices.size() * sizeof(glm::vec3)), &renderable.indexedVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &renderable.uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.indexedUv.size() * sizeof(glm::vec2), &renderable.indexedUv[0], GL_STATIC_DRAW);

	glGenBuffers(1, &renderable.normalbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.normalbufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.indexedNormals.size() * sizeof(glm::vec3), &renderable.indexedNormals[0], GL_STATIC_DRAW);

	renderable.modelInitialized = true;
}