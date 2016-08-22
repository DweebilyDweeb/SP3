#ifndef TILE_INDEX_H
#define TILE_INDEX_H

enum TILE_TYPE {
	TILE_EMPTY = 0,
	TILE_DIRT,
	TILE_GRASS,
	TILE_PORTAL,
    TILE_FENCE,
    TILE_WATER,
    TILE_BUSH,
    TILE_PLATFORM,
    TILE_TRIGGER,
    TILE_PORTAL2,
    TILE_CHICKEN = 10,
    TILE_COW,
	TILE_CABBAGE = 15,
	TILE_CARROT,
	TILE_POTATO,
	TILE_WHEAT,
	TILE_CORN,

	TILE_DAUGHTER = 20,
	TILE_MOTHER,
	TILE_SON,


    TILE_CENTRE = 88,

	TILE_SPAWNPOINT = 99,
    TILE_SPAWNPOINT2,
	NUM_TILE,
};

#endif