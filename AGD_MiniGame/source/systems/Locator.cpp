#include "../../include/utils/Locator.h"
#include "../../include/utils/AudioManager.h"

ServiceLocator::ServiceLocator()
{
    audioManagerService = std::make_shared<AudioManager>();
}

ServiceLocator::~ServiceLocator()
{

}

std::shared_ptr<AudioManager> ServiceLocator::getAudioManager() {
    return audioManagerService;
}