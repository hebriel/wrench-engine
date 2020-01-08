//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <string>
#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <core/error.h>

#include "mesh.h"

namespace wrench {

	template <class VAOImpl, class VBOImpl, class IBOImpl>
	class ResourceLoader
	{
	public:
		ResourceLoader() = default;

		void load_mesh(const char* name, const std::string& file)
		{
			const aiScene* scene = m_importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes);

			if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				wrench::Error err;
				err.err = true;
				err.msg = std::string("Error (Assimp): ") + std::string(m_importer.GetErrorString());
				inform_on_fail(err);
				return;
			}

			m_meshes[name] = std::make_unique<std::vector<Mesh>>();
			process_node(name, scene->mRootNode, scene);

			for (Mesh& mesh : *m_meshes[name])
			{
				mesh.setup_mesh<VAOImpl,VBOImpl, IBOImpl>();
			}
		}

		std::vector<Mesh>& get_mesh(const char* name)
		{
			return *m_meshes[name].get();
		}

	private:

		void process_node(const char* name, aiNode* node, const aiScene* scene)
		{
			for(unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
				m_meshes[name]->emplace_back(process_mesh(mesh, scene));
			}
			for(unsigned int i = 0; i < node->mNumChildren; i++)
			{
				process_node(name, node->mChildren[i], scene);
			}
		}

		Mesh process_mesh(aiMesh *mesh, const aiScene *scene)
		{
			Mesh f_mesh;

			for(unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				f_mesh.vertices.emplace_back(mesh->mVertices[i].x);
				f_mesh.vertices.emplace_back(mesh->mVertices[i].y);
				f_mesh.vertices.emplace_back(mesh->mVertices[i].z);

				f_mesh.vertices.emplace_back(mesh->mNormals[i].x);
				f_mesh.vertices.emplace_back(mesh->mNormals[i].y);
				f_mesh.vertices.emplace_back(mesh->mNormals[i].z);

				glm::vec2 texCoord = glm::vec2(0.0f, 0.0f);

				if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					texCoord.x = mesh->mTextureCoords[0][i].x;
					texCoord.y = mesh->mTextureCoords[0][i].y;
				}

				f_mesh.vertices.emplace_back(texCoord.x);
				f_mesh.vertices.emplace_back(texCoord.y);
			}

			for(unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for(unsigned int j = 0; j < face.mNumIndices; j++)
					f_mesh.indices.push_back(face.mIndices[j]);
			}

			if(mesh->mMaterialIndex >= 0)
			{
				//todo:
			}

			return f_mesh;
		}

		Assimp::Importer m_importer;
		std::unordered_map<std::string, std::unique_ptr<std::vector<Mesh>>> m_meshes;
	};
}
