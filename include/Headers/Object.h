#pragma once

#include <vector>
#include <map>
#include <string>
#include "Material.h"
#include "Mesh.h"

class Object {


private : 

	glm::mat4 m_ModelMatrix;
	std::string m_TextureDirectory = "";
	
	/*glm::mat4 m_Translation;
	glm::mat4 m_Rotation;
	glm::mat4 m_Scale;*/

	std::string GetFileName(FILE * f);
	

protected : 

	Mesh<Vertexun> * m_Mesh;
	std::vector<Material*> m_Materials;
	std::map<unsigned int, unsigned int> * m_ListMat;

public :
	Object();
	Object(Mesh<Vertexun> * m);
	Object(Mesh<Vertexun> * m, Material * mat);
	Object(Mesh<Vertexun> * m, std::vector<Material*> mat);
	Object(Mesh<Vertexun> * m, std::string shaderPath);
	Object(std::string pathObj, std::string pathMtl, bool reverse = false, int renderType = GL_TRIANGLES);
	Object(std::string pathObj, bool reverse = false);

	void LoadObject(std::string pathObj, bool reverse);
	void LoadMaterials(std::string path, std::vector<Material*> & materials);
	void LoadTexturesMap();
	void LoadTexturesMap(std::string path);
	int contains(glm::vec3 v, glm::vec2 vt, glm::vec3 vn);
	bool hasMaterial(Material* mat);
	unsigned int GetMaterialId(std::string nameMat);

	void CreateShaders(std::string shadersPath, std::string genShaderPath);
	void Init(unsigned int renderType, std::string shaderPath);
	void Bind();
	void Unbind();
	
	void Translate(float x, float y, float z);
	void Translate(glm::vec3 axis);
	void RotationRad(float angle, float x, float y, float z);
	void RotationRad(float angle, glm::vec3 axis);
	void RotationDeg(float angle, float x, float y, float z);
	void RotationDeg(float angle, glm::vec3 axis);
	void Scale(float x, float y, float z);
	void Scale(glm::vec3 axis);

	//getters
	inline std::vector<Material*> GetMaterials() { return m_Materials; }
	inline Mesh<Vertexun> * GetMesh() { return m_Mesh; }
	inline glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }
	inline std::map<unsigned int, unsigned int> * GetListMat() { return m_ListMat; }
	inline std::string GetTextureDirectory() const { return m_TextureDirectory; }

	//setters
	inline void SetTextureDirectory(std::string path) { m_TextureDirectory = path; }
};