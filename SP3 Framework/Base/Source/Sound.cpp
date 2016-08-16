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

void Play2()
{
    if (engine->isCurrentlyPlaying("Audio/Sprint.wav"))
        return;
    engine->play2D("Audio/Sprint.wav", false);
}

void Play3()
{
    if (engine->isCurrentlyPlaying("Audio/AK.wav"))
        return;
    engine->play2D("Audio/AK.wav", false);
}


void Play4()
{
    if (engine->isCurrentlyPlaying("Audio/Jump.wav"))
        return;
    engine->play2D("Audio/Jump.wav", false);
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