#include "../../include/utils/Locator.h"
#include <iostream>

std::shared_ptr<AudioManager> ServiceLocator::audioManagerService = nullptr;
ServiceLocator::ServiceLocator()
{
	if (!audioManagerService)
	{
		audioManagerService = std::make_shared<AudioManager>();
	}
}

ServiceLocator::~ServiceLocator()
{

}

std::shared_ptr<AudioManager> ServiceLocator::getAudioManager() 
{
    return audioManagerService;
}