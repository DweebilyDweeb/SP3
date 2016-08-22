#include "Sound.h"

ISoundEngine* engine;

void Create()
{
    engine = createIrrKlangDevice();
}

void Play()
{
	if (engine->isCurrentlyPlaying("Audio/BGM/BGM.mp3"))
		return;
	engine->play2D("Audio/BGM/BGM.mp3", true);
}

void PlayHome()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/Home.mp3"))
        return;
    engine->play2D("Audio/BGM/Home.mp3", true);
}

void StopHome()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/Home.mp3"))
    engine->removeSoundSource("Audio/BGM/Home.mp3");
}

void PlayWorld()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/World.mp3"))
        return;
    engine->play2D("Audio/BGM/World.mp3", true);
}

void StopWorld()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/World.mp3"))
        engine->removeSoundSource("Audio/BGM/World.mp3");
}

void PlayDragon()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/Dragon.mp3"))
        return;
    engine->play2D("Audio/BGM/Dragon.mp3", true);
}

void StopDragon()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/Dragon.mp3"))
        engine->removeSoundSource("Audio/BGM/Dragon.mp3");
}
void Play5()
{
    if (engine->isCurrentlyPlaying("Audio/Reload.wav"))
        return;
    engine->play2D("Audio/Reload.wav", false);
}

void Play6()
{
    if (engine->isCurrentlyPlaying("Audio/Empty.wav"))
        return;
    engine->play2D("Audio/Empty.wav", false);
}

void Play7()
{
    if (engine->isCurrentlyPlaying("Audio/M4.wav"))
        return;
    engine->play2D("Audio/M4.wav", false);
}


void DeleteEngine()
{
    engine->drop();
}