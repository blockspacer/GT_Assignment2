#ifndef PLAYER_HANDLER_H
#define PLAYER_HANDLER_H

#include <Godot.hpp>
#include <Node.hpp>
#include <Ref.hpp>
#include <PackedScene.hpp>
#include "collectable.h"
#include <vector>

namespace godot {

	class PlayerHandler : public Node {
		GODOT_CLASS(PlayerHandler, Node)

	private:
		Ref<PackedScene> PlayerScene;

		std::vector<Collectable> acorn_positions;

	public:
		static void _register_methods();

		PlayerHandler();
		~PlayerHandler();

		void _init();
		void _ready();
		void _create_player();
		void _process(float delta);
	};
}

#endif