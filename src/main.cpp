#include "main.hpp"

#include "scotland2/shared/modloader.h"
#include "GlobalNamespace/BTSCharacterSpawnController.hpp"
#include "GlobalNamespace/BTSCharacterSpawnAnimationController.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(BTSCharacterSpawnAnimationController_PlayAnimation, &BTSCharacterSpawnAnimationController::PlayAnimation, void, BTSCharacterSpawnAnimationController* self) {
  BTSCharacterSpawnAnimationController_PlayAnimation(self);
  self->StopAnimation();
  PaperLogger.info("BTS character was detected and stopped.");
}

MAKE_HOOK_MATCH(BTSCharacterSpawnAnimationController_ResumeAnimation, &BTSCharacterSpawnAnimationController::ResumeAnimation, void, BTSCharacterSpawnAnimationController* self) {
  BTSCharacterSpawnAnimationController_ResumeAnimation(self);
  self->StopAnimation();
  PaperLogger.info("BTS character was detected and stopped.");
}

/**
 * Stores the ID and version of our mod, and is sent to the modloader upon startup
 */
static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};


/**
 * Called at the early stages of game loading
 */
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
  *info = modInfo.to_c();

  // File logging
  Paper::Logger::RegisterFileContextId(PaperLogger.tag);

  PaperLogger.info("Completed setup!");
}

/**
 * Called later on in the game loading - a good time to install function hooks
 */
MOD_EXTERN_FUNC void late_load() noexcept {
  il2cpp_functions::Init();

  PaperLogger.info("Installing hooks...");
  INSTALL_HOOK(PaperLogger, BTSCharacterSpawnAnimationController_PlayAnimation);
  INSTALL_HOOK(PaperLogger, BTSCharacterSpawnAnimationController_ResumeAnimation);
  PaperLogger.info("Installed all hooks!");
}
