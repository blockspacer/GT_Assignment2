#include "squirrel_ai.h"

using namespace godot;

void WanderState::start(Node* parent) {
    Godot::print("start wandering");
    // TODO: this call is not working
    current_waypoint = Object::cast_to<SquirrelAI>(parent)->_get_closest_node();
}

void WanderState::execute(Node* parent) {
    //Godot::print("execute wandering");

    auto current = parent->get_node("/root/Game/Waypoints/" + current_waypoint);
    Godot::print(current_waypoint);

    if (current != nullptr && !current_waypoint.is_empty()) {
        Vector3 delta = Object::cast_to<Spatial>(current)->get_translation() - Object::cast_to<Spatial>(parent)->get_translation();

        if (delta.length() <= 2) {
            temp_waypoint = current_waypoint;
            current_waypoint = Object::cast_to<SquirrelAI>(parent)->_get_closest_node();
            previous_waypoint = temp_waypoint;
        }
        else {
            Object::cast_to<SquirrelAI>(parent)->_update_movement(delta.normalized() * 8);
        }
    }
}

void WanderState::end(Node* parent) {
    //Godot::print("end wander");
}

void FoundAcorn::start(Node* parent) {

}

void FoundAcorn::execute(Node* parent) {

}

void FoundAcorn::end(Node* parent) {

}

void ScareRacoon::start(Node* parent) {

}

void ScareRacoon::execute(Node* parent) {

}

void ScareRacoon::end(Node* parent) {
    
}

void SquirrelAI::_register_methods() {
	register_method("_ready", &SquirrelAI::_ready);
    register_method("_process", &SquirrelAI::_process);
    register_method("_physics_process", &SquirrelAI::_physics_process);
    register_method("_rotate_player", &SquirrelAI::_rotate_player);
    register_method("_update_movement", &SquirrelAI::_update_movement);
    register_method("_get_closest_node", &SquirrelAI::_get_closest_node);
}



SquirrelAI::SquirrelAI() {
}

SquirrelAI::~SquirrelAI() {
}

void SquirrelAI::_init() {
    
}

void SquirrelAI::_ready() {
    brain.set_state(this, &wanderState);
}

void SquirrelAI::_process(float delta) {
    brain.update(this);
}

void SquirrelAI::_physics_process(float delta) {
    move_and_slide(motion, Vector3(0, 1, 0), true, 4, 1.5);
}

void SquirrelAI::_rotate_player() {
    
}

void SquirrelAI::_update_movement(Vector3 direction) {
    direction.y = gravity;
    motion = direction;
}

NodePath SquirrelAI::_get_closest_node () {
    Godot::print("_get_closest_node: start");
    Node* waypoint_parent = get_node("/root/Game/Waypoints");
    
    // With poolStringArray, get neighbors of current_waypoint instead of get_children() if current is not null.
    Array children = waypoint_parent->get_children();
    
    Spatial* child_spatial = Object::cast_to<Spatial>(Object::___get_from_variant(children[0]));
    float min_dist = 1.0/0.0;//(this->get_translation()).distance_squared_to(child_spatial->get_translation());
    int min_index = -1;
    for (int i = 0; i < children.size(); ++i) {
        child_spatial = Object::cast_to<Spatial>(Object::___get_from_variant(children[i]));
        float new_dist = (this->get_translation()).distance_squared_to(child_spatial->get_translation());
        if (child_spatial->get_name() != wanderState.previous_waypoint && child_spatial->get_name() != wanderState.current_waypoint && new_dist < min_dist) {
            min_dist = new_dist;
            min_index = i;
        }
    }
    if (min_index == -1) {
        return "";
    }
    Godot::print(Object::cast_to<Node>(Object::___get_from_variant(children[min_index]))->get_name());
    return Object::cast_to<Node>(Object::___get_from_variant(children[min_index]))->get_name();
}





