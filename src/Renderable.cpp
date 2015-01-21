#include "Renderable.h"
#include <map>
#include <glm/glm.hpp>

struct triplet {
	glm::vec3 first;
	glm::vec3 second;
	glm::vec2 third;
	bool operator()(triplet const& lhs, triplet const& rhs) const
	{
		if (lhs.first == rhs.first&&lhs.second == lhs.second&&rhs.third == lhs.third);
	}
	bool operator== (triplet const & that) const {
		return first == that.first && second == that.second;
	}
	bool operator< (triplet const & that) const {
		return first == that.first && second == that.second;
	}
};

Renderable::Renderable(std::string modelName, std::string textureName){
	this->modelName = modelName;
	this->textureName = textureName;
}
void Renderable::index(){
	std::map<triplet, unsigned int> inserted;
	unsigned int insertedCount = 0;
	for (unsigned int i = 0; i < meshVertices.size(); i++){
		triplet key;
		key.first = meshVertices[i];
		key.second = meshNormals[i];
		key.third = meshUvs[i];
		if (inserted.count(key)==0){
			indexedVertices[insertedCount] = key.first;
			indexedNormals[insertedCount] = key.second;
			indexedUvs[insertedCount] = key.third;
			insertedCount++;
		}
		indices[indexCount++] = inserted[key];
	}
}