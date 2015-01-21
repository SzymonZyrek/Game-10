#include "RenderDataLoader.h"

RenderDataLoader::RenderDataLoader(){

}

void RenderDataLoader::loadPlainData(Renderable &renderable){
	
	renderable.index();

	glGenBuffers(1, &renderable.indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable.indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderable.indexCount * sizeof(unsigned int), &renderable.indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &renderable.vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, (renderable.meshVertices.size() * sizeof(glm::vec3)), &renderable.meshVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &renderable.uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.meshUvs.size() * sizeof(glm::vec2), &renderable.meshUvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &renderable.normalbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.normalbufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.meshNormals.size() * sizeof(glm::vec3), &renderable.meshNormals[0], GL_STATIC_DRAW);

	renderable.modelInitialized = true;
}

void RenderDataLoader::loadIndexedData(Renderable &renderable){

	glGenBuffers(1, &renderable.vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, (renderable.meshVertices.size() * sizeof(glm::vec3)), &renderable.meshVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &renderable.uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.meshUvs.size() * sizeof(glm::vec2), &renderable.meshUvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &renderable.normalbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, renderable.normalbufferID);
	glBufferData(GL_ARRAY_BUFFER, renderable.meshNormals.size() * sizeof(glm::vec3), &renderable.meshNormals[0], GL_STATIC_DRAW);

	renderable.modelInitialized = true;
}