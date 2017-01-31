#ifndef SOUND_H
#define SOUND_H

#include <irrKlang.h>
using namespace irrklang;

void Create();
/////////////////////////////////
void Play(); //Creation of sound engine
/////////////////////////////////
    
void PlayHome();
void PlayWorld();
void PlayDragon();
void StopHome();
void StopWorld();
void StopDragon();
/////////////////
void PlaySelect();
void PlayCow();
void PlayBloop();
void PlayDeath();
void StopDeath();
/////////////////
void DeleteEngine(); // Removal of sound engine
void PlayChicken();

#endif
