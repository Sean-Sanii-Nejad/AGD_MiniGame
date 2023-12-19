#include <string>
#include <SFML/Audio.hpp>

class AudioManager 
{
public:
    void playSound(const std::string& soundID);
    void stopSound();

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
};