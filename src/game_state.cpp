#include "game_state.h"

using namespace godot;

void GameState::_register_methods() {
	register_method("_ready", &GameState::_ready);
	register_method("collect_acorns", &GameState::collect_acorns);
	register_method("remove_acorns", &GameState::remove_acorns);
	register_method("_process", &GameState::_process);

	register_property<GameState, int>("num_acorns", &GameState::num_acorns, 25);
	register_property<GameState, Vector2>("max_acorn_bounds", &GameState::max_acorn_bounds, Vector2{10, 10});
	register_property<GameState, Vector2>("min_acorn_bounds", &GameState::min_acorn_bounds, Vector2{-10, -10});
}

GameState::GameState() {
}

GameState::~GameState() {
}

void GameState::_init() {
}

void GameState::_process(float delta) {
}

void GameState::_ready() {
	numCollected = 0;
}

void GameState::collect_acorns() {
	String gs1 = String::num_int64(numCollected);
	numCollected++;

	String gs2 = String::num_int64(numCollected);

	Label* label = (Label*) get_parent()->get_node("GUI/HSplitContainer/NinePatchRect/Label");
	if (label) {
		label->set_text(gs2);
	}

	if (numCollected >= 20) {
		Gui* gui = (Gui*) get_parent()->get_node("GUI");
		if (gui) {
			gui->_WinMenu_show();
		}
	}
}

void GameState::remove_acorns() {
	if (numCollected > 0) {
		numCollected--;
	}

	String gs1 = String::num_int64(numCollected);

	//update UI
	Label* label = (Label*) get_parent()->get_node("GUI/HSplitContainer/NinePatchRect/Label");
	if (label) {
		label->set_text(gs1);
	}
}

