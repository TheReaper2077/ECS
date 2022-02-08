#pragma once

#include "Types.h"
#include "EntityManager.h"
#include "ComponentManager.h"


class SystemManager {
private:
	std::vector<std::set<Entity>> system_array;
	std::map<ID, unsigned int> system_index_map;
	unsigned int next_index = 0;

	SystemManager() {}
	ComponentManager *component_manager = ComponentManager::sharedInstance();
	EntityManager *entity_manager = EntityManager::sharedInstance();

public:
	static SystemManager *sharedInstance() {
		static SystemManager instance;
		return &instance;
	}

	template <typename T>
	void EntityIDChanged(const Entity &entity) {
		const auto& entity_id = entity_manager->GetEntityID(entity);
		const auto& component_id = 1 << component_manager->GetComponentType<T>();

		for (const auto& pair: system_index_map) {
			if (pair.first & component_id) {
				if (entity_id & pair.first) {
					system_array[pair.second].insert(entity);
				} else {
					system_array[pair.second].erase(entity);
				}
			}
		}
	}

	void EntityIDChanged(const Entity &entity) {
		const auto& entity_id = entity_manager->GetEntityID(entity);

		for (const auto& pair: system_index_map) {
			if (entity_id & pair.first) {
				system_array[pair.second].insert(entity);
			} else {
				system_array[pair.second].erase(entity);
			}
		}
	}

	template <typename ...T>
	std::set<Entity>& CreateView() {
		ID temp_id = 0;
		for (const auto& component_name: {typeid(T).name()...}) {
			temp_id |= 1 << component_manager->GetComponentType(component_name);
		}

		if (system_index_map.find(temp_id) == system_index_map.end()) {
			system_index_map[temp_id] = next_index++;
			
			std::set<Entity> temp_set;

			for (const auto& pair: entity_manager->GetEntityIDArray()) {
				if (temp_id & pair.second) {
					temp_set.insert(pair.first);
				}
			}

			system_array.push_back(temp_set);
		}

		return system_array[system_index_map[temp_id]];
	}
};
