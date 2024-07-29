#ifndef SPRITE_DATA
#define SPRITE_DATA

// player
#define SPRITE_START_PLAYER 0
#define SPRITE_END_PLAYER 6
// misc gui stuff
#define CURSOR_SPRITE SPRITE_END_PLAYER + 1
#define NEW_BOUNDS_SPRITE SPRITE_END_PLAYER + 2
#define OUT_OF_BOUNDS_SPRITE SPRITE_END_PLAYER + 3
#define TILE_CURSOR SPRITE_END_PLAYER + 4
#define SPRITE_VIS_TOGGLE TILE_CURSOR + 1

// tiles
#define SPRITE_START_TILES SPRITE_VIS_TOGGLE + 2
#define SPRITE_COUNT_TILES 120
// water
#define SPRITE_START_WATER SPRITE_START_TILES + SPRITE_COUNT_TILES + 1
#define SPRITE_COUNT_WATER 2
// entities
#define SPRITE_START_ENTITIES SPRITE_START_WATER + SPRITE_COUNT_WATER + 1
#define SPRITE_COUNT_ENTITIES 54

// effects
#define SPRITE_START_EFFECTS SPRITE_START_ENTITIES + SPRITE_COUNT_ENTITIES + 1
#define SPRITE_COUNT_EFFECTS 34


// markers
#define SPRITE_START_MARKERS SPRITE_START_EFFECTS + SPRITE_COUNT_EFFECTS + 1
#define SPRITE_COUNT_MARKERS 38

#endif