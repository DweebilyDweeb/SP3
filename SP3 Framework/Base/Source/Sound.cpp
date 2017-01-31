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

void PlaySelect()
{
    if (engine->isCurrentlyPlaying("Audio/Sound_Effects/select.wav"))
        return;
    engine->play2D("Audio/Sound_Effects/select.wav", false);
}

void PlayCow()
{
    if (engine->isCurrentlyPlaying("Audio/Sound_Effects/cow.wav"))
        return;
    engine->play2D("Audio/Sound_Effects/cow.wav", false);
}

void PlayBloop()
{
    engine->play2D("Audio/Sound_Effects/bloop.wav", false);
}

void PlayDeath()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/Death.mp3"))
        return;
    engine->play2D("Audio/BGM/Death.mp3", true);
}

void StopDeath()
{
    if (engine->isCurrentlyPlaying("Audio/BGM/Death.mp3"))
        engine->removeSoundSource("Audio/BGM/Death.mp3");
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


void PlayChicken()
{
    engine->play2D("Audio/Sound_Effects/chicken.mp3", false);
}

void DeleteEngine()
{
    engine->drop();
}
