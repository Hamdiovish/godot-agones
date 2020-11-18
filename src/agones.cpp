#include "agones.h"
#include "helpers.h"

using namespace godot;

Agones *Agones::instance = NULL;

Agones::Agones()
{
    sdk = std::make_unique<agones::SDK>();
    instance = this;
}

Agones* Agones::get_singleton(){
    if (!instance) {
        instance = new Agones();
    }
    return instance;
}

void Agones::_init() {
    godot::Godot::print(">>Pingo from init:");
}

bool Agones::Connecting()
{
    return sdk->Connect();
}

void Agones::Ready()
{
    const auto& status = sdk->Ready();
    log_error(status);
}

bool Agones::Health()
{
    return sdk->Health();
}

godot::Dictionary Agones::GameServer()
{
    sdk::GameServer gameServer;
    const auto& status = sdk->GameServer(&gameServer);
    log_error(status);
    return game_server_to_dict(gameServer);
}

void Agones::Shutdown()
{
    const auto& status = sdk->Shutdown();
    log_error(status);
}

void Agones::SetLabel(godot::String key, godot::String value)
{
    const auto& status = sdk->SetLabel(to_std(key), to_std(value));
    log_error(status);
}

void Agones::SetAnnotation(godot::String key, godot::String value)
{
    const auto& status = sdk->SetAnnotation(to_std(key), to_std(value));
    log_error(status);
}

void Agones::WatchGameServer()
{
    const auto& status = sdk->WatchGameServer([](const agones::dev::sdk::GameServer& gameserver){
        godot::Godot::print(">>GameServer Updated");

        std::cout << "GameServer Update:\n"                                 //
                << "\tname: " << gameserver.object_meta().name() << "\n"  //
                << "\tstate: " << gameserver.status().state() << "\n"
                << std::flush;
        instance->emit_signal("watch_game_server_signal");

    });
}

Agones::~Agones(){
    instance = NULL;
}

void Agones::_register_methods()
{
    register_method("connecting", &Agones::Connecting);
    register_method("ready", &Agones::Ready);
    register_method("health", &Agones::Health);
    register_method("game_server", &Agones::GameServer);
    register_method("shutdown", &Agones::Shutdown);
    register_method("set_label", &Agones::SetLabel);
    register_method("set_annotation", &Agones::SetAnnotation);
    register_method("watch_game_server", &Agones::WatchGameServer);
    register_method("get_singleton", &Agones::get_singleton);

    register_signal<Agones>("watch_game_server_signal");
}
