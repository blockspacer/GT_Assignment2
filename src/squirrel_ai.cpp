#include "squirrel_ai.h"

using namespace godot;

void WanderState::start(Node* parent) {
    Godot::print("start wandering");
    current_waypoint = Object::cast_to<SquirrelAI>(parent)->_get_closest_node();
}

void WanderState::execute(Node* parent, float dt) {
    //Godot::print("execute wandering");

    auto current = parent->get_node("/root/Game/Waypoints/" + current_waypoint);
    //Godot::print(current_waypoint);

    if (current != nullptr && !current_waypoint.is_empty()) {
        Vector3 delta = Object::cast_to<Spatial>(current)->get_translation() - Object::cast_to<Spatial>(parent)->get_translation();

        if (delta.length() <= 2) {
            // find a new waypoint to move to
            temp_waypoint = current_waypoint;
            current_waypoint = Object::cast_to<SquirrelAI>(parent)->_get_closest_node();
            previous_waypoint = temp_waypoint;
        } else {
            // move squirrel towards current waypoint
            Object::cast_to<SquirrelAI>(parent)->_update_movement(delta.normalized() * 6);
            Object::cast_to<SquirrelAI>(parent)->_turn_to_face(Object::cast_to<Spatial>(current)->get_translation());
        }
    }
}

void WanderState::end(Node* parent) {
    //Godot::print("end wander");
}

void FoundAcorn::start(Node* parent) {
    Godot::print("FoundAcorn: start");
}

void FoundAcorn::execute(Node* parent, float dt) {
    auto current = parent->get_node(current_acorn);

    if (current != nullptr) {
        // move squirrel towards current acorn
        Vector3 delta = Object::cast_to<Spatial>(current)->get_translation() - Object::cast_to<Spatial>(parent)->get_translation();
        delta.y = 0;

        float len = delta.length();
        Vector3 normalized_delta = delta * 6 / len;
        if (len < 1)
            normalized_delta = delta * 6;        

        Object::cast_to<SquirrelAI>(parent)->_update_movement(normalized_delta);
        Object::cast_to<SquirrelAI>(parent)->_turn_to_face(Object::cast_to<Spatial>(current)->get_translation());
    } else {
        // switch back to wanderState
         Object::cast_to<SquirrelAI>(parent)->brain.set_state(parent, &(Object::cast_to<SquirrelAI>(parent)->wanderState));
    }
}

void FoundAcorn::end(Node* parent) {

}

void ScareRacoon::start(Node* parent) {

}

void ScareRacoon::execute(Node* parent, float dt) {

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
    register_method("_on_area_entered", &SquirrelAI::_on_area_entered);
}



SquirrelAI::SquirrelAI() {
}

SquirrelAI::~SquirrelAI() {
}

void SquirrelAI::_init() {
    
}

void SquirrelAI::_ready() {
    brain.set_state(this, &wanderState);

    get_node("SquirrelVision")->connect("area_entered", this, "_on_area_entered");
}

void SquirrelAI::_process(float delta) {
    brain.update(this, delta);
}

void SquirrelAI::_physics_process(float delta) {
    move_and_slide(motion, Vector3(0, 1, 0), true, 4, 1.5);
}

void SquirrelAI::_rotate_player() {
    
}

void SquirrelAI::_on_area_entered (Area* area) {
    Node* areaNode = (Node*)area;
	String name = areaNode->get_name();
    
    if (areaNode->get_name() == "AcornArea" && brain.state == &wanderState) {
        Godot::print("area_entered signal: found acorn");
        // change state to FoundAcorn if not already in FoundAcorn
        foundAcorn.current_acorn = areaNode->get_parent()->get_path();
        Godot::print(foundAcorn.current_acorn);
        brain.set_state(this, &foundAcorn);
    }
}

void SquirrelAI::_update_movement(Vector3 direction) {
    direction.y = gravity;
    motion = direction;
}

void SquirrelAI::_turn_to_face(Vector3 target) {
    Vector3 up = Vector3(0, 1, 0);
    target.y = get_translation().y;
    look_at(target, up);
}

NodePath SquirrelAI::_get_closest_node () {
    //Godot::print("_get_closest_node: start");
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
    //Godot::print(Object::cast_to<Node>(Object::___get_from_variant(children[min_index]))->get_name());
    return Object::cast_to<Node>(Object::___get_from_variant(children[min_index]))->get_name();
}





