#include <iostream>

#include "Registry.h"

struct Pos {

};

struct Vel {
	int a, b;
};

int main(int, char**) {
	Registry *registry = Registry::sharedInstance();

	registry->Register<Vel>();
	registry->Register<Pos>();

	Entity player0 = registry->CreateEntity<Pos, Vel>();
	Entity player1 = registry->CreateEntity<Vel>();
	Entity player2 = registry->CreateEntity();

	// registry->AddComponent(player0, Vel{1000, 0});

	// std::cout << registry->GetComponent<Vel>(player0).a << std::endl;
	registry->AddComponent(player1, Vel{2100, 0});

	// std::cout << registry->GetComponent<Vel>(player1).a << std::endl;
	// registry->AddComponent(player2, Vel{1030, 0});
	
	// // registry->RemoveComponent<Vel>(player0);
	// // registry->RemoveComponent<Vel>(player1);
	// // registry->DestroyEntity(player0);
	// // registry->DestroyEntity(player1);

	// std::cout << registry->GetComponent<Vel>(player2).a << std::endl;
	// std::cout << registry->GetComponent<Vel>(player0).a << std::endl;

	std::cout << "entity" << std::endl;

	const auto& entities = registry->View<Vel>();
	for (const auto& entity: entities) {
		std::cout << entity << std::endl;
	}

	registry->RemoveComponent<Vel>(player1);

	for (const auto& entity: entities) {
		std::cout << entity << std::endl;
	}
}