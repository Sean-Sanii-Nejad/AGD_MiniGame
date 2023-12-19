#include <memory>
#include "../../include/utils/AudioManager.h"

class ServiceLocator {

public:
    ServiceLocator();
    ~ServiceLocator();

    static std::shared_ptr<AudioManager> getAudioManager();

private:
    static std::shared_ptr<AudioManager> audioManagerService;
};