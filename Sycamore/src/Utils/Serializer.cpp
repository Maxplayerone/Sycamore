#include"Serializer.h"

#include"yaml-cpp/yaml.h"

#include"../ECS/GameObject.h"
#include"../ECS/Transform.h"
#include"../ECS/SpriteRenderer.h"

#include"DataTypes.h"
#include"Logger.h"
#include"ObjectPool.h"

#include"../../Math/SM_math.h"

#include"../SceneManagment/LevelEditorScene.h"

#include<xhash>

namespace YAML {

	template<>
	struct convert<SM_math::vec2>
	{
		static Node encode(const SM_math::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, SM_math::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<SM_math::vec3>
	{
		static Node encode(const SM_math::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, SM_math::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<color4>
	{
		static Node encode(const color4& rhs)
		{
			Node node;
			node.push_back(rhs.r);
			node.push_back(rhs.g);
			node.push_back(rhs.b);
			node.push_back(rhs.a);
			return node;
		}

		static bool decode(const Node& node, color4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.r = node[0].as<float>();
			rhs.g = node[1].as<float>();
			rhs.b = node[2].as<float>();
			rhs.a = node[3].as<float>();
			return true;
		}
	};

}

std::vector<GameObject> entities;

void SerializeEntity(YAML::Emitter & out, GameObject go);

YAML::Emitter& operator<<(YAML::Emitter& out, const SM_math::vec2& vector) {
	out << YAML::Flow;
	out << YAML::BeginSeq << vector.x << vector.y << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const SM_math::vec3& vector) {
	out << YAML::Flow;
	out << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const color4& color) {
	out << YAML::Flow;
	out << YAML::BeginSeq << color.r << color.g << color.b << color.a << YAML::EndSeq;
	return out;
}


void SM_Serializer::Serialize() {
	
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Scene";
	out << YAML::Value << "Title of the scene";
	out << YAML::Key << "Entities";
	out << YAML::Value << YAML::BeginSeq;
	
	for (int i = 0; i < entities.size(); i++) {
		SerializeEntity(out, entities[i]);
	}

	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::ofstream file;
	file.open("src/Assets/scenes/Example.txt");
	file << out.c_str();
	file.close();
}

bool SM_Serializer::Deserialize(LevelEditorScene* scene) {
	std::ifstream stream("src/Assets/scenes/Example.txt");
	std::stringstream ss;
	ss << stream.rdbuf();

	YAML::Node data = YAML::Load(ss.str());
	if (!data["Scene"])
		return false;

	std::string sceneName = data["Scene"].as<std::string>();
	LOGGER_INFO("Deserializing scene");
	
	auto entities = data["Entities"];
	
	if (entities) {
		for (auto entity : entities) {
			uint64_t uuid = entity["Entity"].as<uint64_t>();
			std::string name = entity["Entity name"].as<std::string>();
			
			GameObject tmpGo(name, uuid);
			
			auto transNode = entity["Transform component"];
			if (transNode) {
				SM_math::vec2 pos = transNode["Position"].as<SM_math::vec2>();
				SM_math::vec2 scale = transNode["Scale"].as<SM_math::vec2>();
				tmpGo.AddComponent( new Transform(pos, scale) );
			}
			
			auto rendNode = entity["Sprite renderer component"];
			bool hasTexture = false;
			
			if (rendNode) {
				color4 color = rendNode["Color"].as<color4>();
				uint texIndex = rendNode["Texture index"].as<uint>();

				//texture thingy
				//used to get a texture at a specific index in a spritesheet
				auto sprIndexNode = rendNode["spritesheet index"];
				int sprIndex = -1;
				if (sprIndexNode) {
					sprIndex = sprIndexNode.as<int>();
				}

				auto texFilepathNode = rendNode["Texture file name"];
				std::string filepath = "";
				if (texFilepathNode) {
					filepath = texFilepathNode.as<std::string>();
					hasTexture = true;
				}

				if (!hasTexture)
					tmpGo.AddComponent(new SpriteRenderer(color));
				else if (hasTexture && sprIndex == -1) {
					Texture* tex = SM_Pool::GetTexture(filepath);
					tmpGo.AddComponent(new SpriteRenderer(Sprite(tex)));
				}
				else {
					SpriteSheet* sheet = SM_Pool::GetSpriteSheet(filepath, 16, 81);
					tmpGo.AddComponent( new SpriteRenderer( sheet->GetSprite(sprIndex) ) );
				}
			}
			
			scene->AddGameObjectToScene(tmpGo);
		}
		
	}
	LOGGER_INFO("Deserialization finished successfully");
	return true;
}

void SM_Serializer::Push(GameObject go) {
	entities.push_back(go);
}

void SerializeEntity(YAML::Emitter& out, GameObject go) {
	out << YAML::BeginMap;

	out << YAML::Key << "Entity";
	out << YAML::Value << go.GetID();

	out << YAML::Key << "Entity name";
	out << YAML::Value << go.GetName();
	

	if (Transform* trans = go.GetComponent<Transform>()) {
		out << YAML::Key << "Transform component";
		out << YAML::BeginMap;

		out << YAML::Key << "Position";
		out << YAML::Value << trans->GetPos();

		out << YAML::Key << "Scale";
		out << YAML::Value << trans->GetScale();

		out << YAML::EndMap;
	}

	if (SpriteRenderer* rend = go.GetComponent<SpriteRenderer>()) {
		out << YAML::Key << "Sprite renderer component";
		out << YAML::BeginMap;

		out << YAML::Key << "Color";
		out << YAML::Value << rend->GetColor4();

		out << YAML::Key << "Texture index";
		out << YAML::Value << rend->GetSprite().GetTexSlot();

		if (rend->HasTexture()) {
			out << YAML::Key << "Texture file name";
			out << YAML::Value << rend->GetSprite().GetTexture()->GetTextureFilepath();

			out << YAML::Key << "spritesheet index";
			out << YAML::Value << rend->GetSprite().GetSpritesheetIndex();
		}

		out << YAML::EndMap;
	}

	out << YAML::EndMap;
}
