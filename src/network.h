#ifndef NETWORK_H
#define NETWORK_H

#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <SceneTree.hpp>
#include <NetworkedMultiplayerENet.hpp>
#include <ResourceLoader.hpp>
#include <vector>
#include "basic_movement.h"


namespace godot {

class Network : public Node {
    GODOT_CLASS(Network, Node)

private:
    
public:
    static void _register_methods();

    Network();
    ~Network();

    void _init();
    void _ready();

    void create_server(String playerNickname);
    void connect_to_server(String playerNickname);
    void _connected_to_server();
    void _on_player_disconnected(int64_t id);
    void _on_player_connected(int64_t connectedPlayerId);
    void _request_player_info(int64_t requestFromId, int64_t playerId);
    void _request_players(int64_t requestFromId);
    void _send_player_info(int64_t id, Dictionary info);
    void update_position(int64_t id, Vector3 position);

private:
    Ref<PackedScene> player_scene;
    const String SERVER_IP = "127.0.0.1";
    const int64_t SERVER_PORT = 31400;
    const int64_t MAX_PLAYERS = 2;
    Dictionary self_data;
    Dictionary players;
    std::vector<Vector3> init_positions;
};

}

#endif