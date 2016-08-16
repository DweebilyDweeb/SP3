#ifndef TILE_INDEX_H
#define TILE_INDEX_H

enum TILE_TYPE {
	TILE_EMPTY = 0,
	TILE_DIRT,
	TILE_GRASS,
	TILE_PORTAL,
    TILE_FENCE,
    TILE_WATER,
 
    TILE_CHICKEN = 10,
    TILE_COW,

	TILE_DAUGHTER = 20,
	TILE_MOTHER,
	TILE_SON,

	TILE_SPAWNPOINT = 99,

	NUM_TILE,
};

#endif