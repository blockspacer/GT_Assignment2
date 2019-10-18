#include "gui.h"

using namespace godot;

void Gui::_register_methods() {
    register_method("_on_MenuButton_pressed", &Gui::_on_MenuButton_pressed);
	register_method("_on_ExitButton_pressed", &Gui::_on_ExitButton_pressed);
	register_method("_on_SFX_pressed", &Gui::_on_SFX_pressed);
	register_method("_on_BackgroundSound_pressed", &Gui::_on_BackgroundSound_pressed);
	register_method("_on_RotateStrafe_pressed", &Gui::_on_RotateStrafe_pressed);
	register_method("_on_PlayAgain_pressed", &Gui::_on_PlayAgain_pressed);
	register_method("_on_QuitButton_pressed", &Gui::_on_QuitButton_pressed);
	register_method("_on_VolumeSlider_changed", &Gui::_on_VolumeSlider_changed);
	register_method("_update_acorn_count", &Gui::_update_acorn_count);

	register_method("_on_PlayMain_pressed", &Gui::_on_PlayMain_pressed);
	register_method("_on_CreateMain_pressed", &Gui::_on_CreateMain_pressed);
	register_method("_on_JoinMain_pressed", &Gui::_on_JoinMain_pressed);
	register_method("_on_JoinIPMain_pressed", &Gui::_on_JoinIPMain_pressed);

    register_method("_ready", &Gui::_ready);
    register_method("_process", &Gui::_process);
    register_method("_WinMenu_show", &Gui::_WinMenu_show);
}

Gui::Gui() {

}
Gui::~Gui() {

}

void Gui::_init() {
    bool soundEffect = true;
    bool backgroundSound = true;
}

void Gui::_ready() {
	Control* main_menu = Object::cast_to<Control>(get_parent()->get_node("MainMenu"));
    if (main_menu) {
    	main_menu->show();
		get_tree()->set_pause(true);
    }

    Node* button = get_node("HSplitContainer/MenuButton");
	if (button) {
		button->connect("pressed", this, "_on_MenuButton_pressed");
	}
	Node* exitButton = get_parent()->get_node("PopupMenu/ExitButton");
	if (exitButton) {
		exitButton->connect("pressed", this, "_on_ExitButton_pressed");
	}
	Node* SFXButton = get_parent()->get_node("PopupMenu/HBoxContainer/SFX");
	if (SFXButton) {
		SFXButton->connect("pressed", this, "_on_SFX_pressed");
	}
	Node* BackgroundButton = get_parent()->get_node("PopupMenu/HBoxContainer2/BackgroundSound");
	if (BackgroundButton) {
		BackgroundButton->connect("pressed", this, "_on_BackgroundSound_pressed");
	}
	Node* RotateToggle = get_parent()->get_node("PopupMenu/HBoxContainer3/RotateStrafe");
	if (RotateToggle) {
		RotateToggle->connect("pressed", this, "_on_RotateStrafe_pressed");
	}

	Node* play_again_button = get_parent()->get_node("WinMenu/PlayAgain");
	if (play_again_button) {
		play_again_button->connect("pressed", this, "_on_PlayAgain_pressed");
	}

	Node* quit_button = get_parent()->get_node("WinMenu/QuitButton");
	if (quit_button) {
		quit_button->connect("pressed", this, "_on_QuitButton_pressed");
	}

	Node* play_main = get_parent()->get_node("MainMenu/PlayMain");
	if (play_main) {
		play_main->connect("pressed", this, "_on_PlayMain_pressed");
	}

	Node* create_main = get_parent()->get_node("MainMenu/CreateServerMain");
	if (create_main) {
		create_main->connect("pressed", this, "_on_CreateMain_pressed");
	}

	Node* join_main = get_parent()->get_node("MainMenu/JoinServerMain");
	if (join_main) {
		join_main->connect("pressed", this, "_on_JoinMain_pressed");
	}

	Node* join_ip_main = get_parent()->get_node("MainMenu/JoinMain");
	if (join_ip_main) {
		join_ip_main->connect("pressed", this, "_on_JoinIPMain_pressed");
	}

	Node* quit_main = get_parent()->get_node("MainMenu/QuitMain");
	if (quit_main) {
		quit_main->connect("pressed", this, "_on_QuitButton_pressed");
	}

	Node* quit_pause = get_parent()->get_node("PopupMenu/PauseQuit");
	if (quit_pause) {
		quit_pause->connect("pressed", this, "_on_QuitButton_pressed");
	}

	Node* volume_slider = get_parent()->get_node("PopupMenu/HSlider");
	if (volume_slider) {
		volume_slider->connect("value_changed", this, "_on_VolumeSlider_changed");
	}
}

void Gui::_process() {
	Input* i = Input::get_singleton();
	if (i->is_action_pressed("ui_cancel")) {
		Control* menu = Object::cast_to<Control>(get_parent()->get_node("PopupMenu"));
		if (menu) {
			if (menu->is_visible_in_tree()) 
				_on_ExitButton_pressed();
			else
				_on_MenuButton_pressed();
		}
	}
}

void Gui::_on_MenuButton_pressed() {
	Control* menu = Object::cast_to<Control>(get_parent()->get_node("PopupMenu"));
	if (menu) {
		menu->show();
		get_tree()->set_pause(true);
	}
}

void Gui::_on_ExitButton_pressed() {
	Control* menu = Object::cast_to<Control>(get_parent()->get_node("PopupMenu"));
	if (menu) {
		menu->hide();
		get_tree()->set_pause(false);
	}
}

void Gui::_on_SFX_pressed() {
	AudioStreamPlayer3D *a1 = Object::cast_to<AudioStreamPlayer3D>(get_node("/root/Spatial/Player/AcornSound"));
	AudioStreamPlayer3D *a2 = Object::cast_to<AudioStreamPlayer3D>(get_node("/root/Spatial/Player/TrapSound"));
	if (soundEffect) {
		a1->set_unit_db(-80);
		a2->set_unit_db(-80);
		soundEffect = false;
	} else {
		a1->set_unit_db(10);
		a2->set_unit_db(10);
		soundEffect = true;
	}
}

void Gui::_on_BackgroundSound_pressed() {
	AudioStreamPlayer3D *a1 = Object::cast_to<AudioStreamPlayer3D>(get_node("/root/Spatial/Player/BackgroundMusic"));
	if(a1->is_playing())
		a1->stop();
	else 
		a1->play();
}

void Gui::_on_RotateStrafe_pressed() {
	BasicMovement* player = Object::cast_to<BasicMovement>(get_parent()->get_node("Player"));
	if (player) {
		player->toggle_AD_rotate();
	}
}

void Gui::_on_PlayAgain_pressed() {
	get_tree()->reload_current_scene();

	Control* menu = Object::cast_to<Control>(get_parent()->get_node("WinMenu"));
	if (menu) {
		menu->hide();
		get_tree()->set_pause(false);
	}
}

void Gui::_on_QuitButton_pressed() {
	get_tree()->quit();
}

void Gui::_on_PlayMain_pressed() {
	Control* main_menu2 = Object::cast_to<Control>(get_parent()->get_node("MainMenu"));
    if (main_menu2) {
    	main_menu2->hide();
		get_tree()->set_pause(false);
    }

	get_node("/root/Game")->call("_create_player");	
}

void Gui::_on_CreateMain_pressed () {
	 get_node("/root/network")->call("create_server", "player");
    //_load_game();

	Control* main_menu2 = Object::cast_to<Control>(get_parent()->get_node("MainMenu"));
    if (main_menu2) {
    	main_menu2->hide();
		get_tree()->set_pause(false);
    }

	get_node("/root/Game")->call("_create_player");	
}
    
	
void Gui::_on_JoinMain_pressed () {
	Control* play_main = Object::cast_to<Control>(get_parent()->get_node("MainMenu/PlayMain"));
	play_main->hide();

	Control* join_main = Object::cast_to<Control>(get_parent()->get_node("MainMenu/JoinServerMain"));
	join_main->hide();

	Control* create_main = Object::cast_to<Control>(get_parent()->get_node("MainMenu/CreateServerMain"));
	create_main->hide();

	Control* join_ip_main = Object::cast_to<Control>(get_parent()->get_node("MainMenu/JoinMain"));
	join_ip_main->show();

	Control* ip_main = Object::cast_to<Control>(get_parent()->get_node("MainMenu/IPField"));
	ip_main->show();

}

void Gui::_on_JoinIPMain_pressed () {
	LineEdit* ip_field = Object::cast_to<LineEdit>(get_node("../MainMenu/IPField"));
	get_node("/root/network")->call("connect_to_server", "player2", ip_field->get_text());

	Control* main_menu2 = Object::cast_to<Control>(get_parent()->get_node("MainMenu"));
    if (main_menu2) {
    	main_menu2->hide();
		get_tree()->set_pause(false);
    }

	get_node("/root/Game")->call("_create_player");	

}

void Gui::_WinMenu_show() {
	Control* win_menu = Object::cast_to<Control>(get_parent()->get_node("WinMenu"));
	if (win_menu) {
		win_menu->show();
		//get_tree()->set_pause(true);
	}
}

void Gui::_on_VolumeSlider_changed(float value) {
	AudioStreamPlayer3D *a1 = Object::cast_to<AudioStreamPlayer3D>(get_node("/root/Spatial/Player/BackgroundMusic"));
	a1->set_unit_db(value);
}

// Called when acorn count is incremented or decremented
void Gui::_update_acorn_count (String count) {
	Label* label = (Label*) get_parent()->get_node("GUI/HSplitContainer/NinePatchRect/AcornCounter/NumAcorns");
	if (label) {
		label->set_text(count);
	}
}

