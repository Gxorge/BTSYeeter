#include "main.hpp"

#include "GlobalNamespace/BTSCharacterSpawnController.hpp"
#include "GlobalNamespace/BTSCharacterSpawnAnimationController.hpp"
using namespace GlobalNamespace;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// When the characters spawn, just stop their animiation and they go away!
MAKE_HOOK_OFFSETLESS(PlayAni, void, BTSCharacterSpawnAnimationController* self) {
    PlayAni(self);
    self->StopAnimation();
    getLogger().info("BTS character was detected and stopped.");
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(getLogger(), PlayAni, il2cpp_utils::FindMethodUnsafe("", "BTSCharacterSpawnAnimationController", "PlayAnimation", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), PlayAni, il2cpp_utils::FindMethodUnsafe("", "BTSCharacterSpawnAnimationController", "ResumeAnimation", 0));
    getLogger().info("Installed all hooks!");
}