#include "Renderable.h"
#include <set>
#include <hash_map>
#include <map>
#include <unordered_map>
#include <glm/glm.hpp>
#define EPSILON 0.01

struct triplet {
	glm::vec3 first;
	glm::vec3 second;
	glm::vec2 third;
	int operator==(const triplet &q) const
	{
		return isEqualish(first, q.first) &&
			isEqualish(second, q.second) &&
			isEqualish(third, q.third);
	}
	bool operator<(const triplet &q) const
	{
		return memcmp((void*)this, (void*)&q, sizeof(triplet))>0;
	}
	bool operator!=(const triplet &q) const
	{
		return !(isEqualish(first, q.first) &&
			isEqualish(second, q.second) &&
			isEqualish(third, q.third));
	}
	bool isEqualish(glm::vec2 A, glm::vec2 B) const
	{
		return isEqualish(A.x, B.x, 1) &&
			isEqualish(A.y, B.y, 1);
	}
	bool isEqualish(glm::vec3 A, glm::vec3 B) const
	{
		return isEqualish(A.x, B.x, 1) &&
			isEqualish(A.y, B.y, 1) &&
			isEqualish(A.z, B.z, 1);
	}
	bool isEqualish(float A, float B, int maxUlps) const
	{
		int aInt = *(int*)&A;
		if (aInt < 0)
			aInt = 0x80000000 - aInt;
		int bInt = *(int*)&B;
		if (bInt < 0)
			bInt = 0x80000000 - bInt;
		int intDiff = abs(aInt - bInt);
		if (intDiff <= maxUlps)
			return true;
		return false;
	}
};

namespace std {
	unsigned int hash_the_float(float f)
	{
		unsigned int ui;
		memcpy(&ui, &f, sizeof(float));
		return ui & 0xfffffff8;
	}
	template <>
	struct hash<triplet>
	{
		std::size_t operator()(const triplet& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return ((hash<float>()(k.first.x)
				^ (hash<float>()(k.first.y) << 1)
				^ (hash<float>()(k.first.z) << 1)
				^ (hash<float>()(k.second.x) << 1)
				^ (hash<float>()(k.second.y) << 1)
				^ (hash<float>()(k.second.z) << 1)
				^ (hash<float>()(k.third.x) << 1)
				^ (hash<float>()(k.third.y) << 1)>>7));
		}
	};

}

Renderable::Renderable(std::string modelName,
	std::string textureName,
	std::string vertexShaderName,
	std::string fragmentShaderName) {

	this->modelName = modelName;
	this->textureName = textureName;
	this->vertexShaderName = vertexShaderName;
	this->fragmentShaderName = fragmentShaderName;
}
Renderable::Renderable(std::string modelName,
	std::string textureName) {
	modelName = modelName;
	textureName = textureName;
	vertexShaderName = Config::getStringProperty(DEFAULT_VERTEX_SHADER_FILE_NAME);
	fragmentShaderName = Config::getStringProperty(DEFAULT_FRAGMENT_SHADER_FILE_NAME);
}
void Renderable::index(){
	std::map<triplet, unsigned int> inserted;
	unsigned int insertedCount = 0;
	indexCount = 0;
	for (unsigned int i = 0; i < meshVertices.size(); i++){
		triplet key;
		key.first = meshVertices[i];
		key.second = meshNormals[i];
		key.third = meshUvs[i];
		// check if we already have that vertex
		std::map<triplet, unsigned int>::iterator it = inserted.find(key);
		if (it == inserted.end()){
			// if no, add it
			indexedVertices.push_back(key.first);
			indexedNormals.push_back(key.second);
			indexedUvs.push_back(key.third);
			inserted[key] = insertedCount;
			insertedCount++;
		}
		// return index of the vertex
		indices.push_back(inserted[key]);
		indexCount++;
	}
	this->indexed = true;
}

std::ostream& operator<<(std::ostream &strm, Renderable &a) {
	return strm
		<< "Renderable:[" << std::endl
		<< "\tmodelName: " << a.modelName <<std::endl
		<< "\ttextureName: " << a.textureName << std::endl
		<< "\tvertexShaderName: " << a.vertexShaderName << std::endl
		<< "\tfragmentShaderName: " << a.fragmentShaderName << std::endl
		<< "\tmodelLoaded: " << (a.modelLoaded ? "true" : "false") << std::endl
		<< "\ttextureLoaded: " << (a.textureLoaded ? "true" : "false") << std::endl
		<< "\tshadersLoaded: " << (a.shadersLoaded ? "true" : "false") << std::endl
		<< "\tmodelInitialized: " << (a.modelInitialized ? "true" : "false") << std::endl
		<< "\tindexed: " << (a.indexed ? "true" : "false") << std::endl
		<< "\tvertices: " << a.vertexCount << std::endl
		<< "\tindices: " << a.indexCount << std::endl
		<< "]" << std::endl;
}