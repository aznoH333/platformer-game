#ifndef LEVEL 
#define LEVEL 

#include "gfiles.c"
#include "glog.c"
#include "gframework.c"
#include "gutil.c"
#include "gvector.c"
#include "entities.c"


struct Level {
    char** tiles;
    int width;
    int height;
    File* levelFile;
    Vector entityeMarkers;

};
typedef struct Level Level;

#define MIN_LEVEL_FILE_SIZE 4
#define LEVEL_DATA_START 4

Level* loadLevel(const char* levePath){
    File* f = initFile(levePath);

    if (f->contentsLength < MIN_LEVEL_FILE_SIZE){
        gLog(LOG_ERROR, "Invalid file : %s", levePath);
    }

    Level* out = malloc(sizeof(Level));
    out->levelFile = f;
    // read level header
    {
        char w[4] = {f->contents[0], f->contents[1]};
        out->width = parseStrToInt(w, 2);
        char h[4] = {f->contents[2], f->contents[3]};
        out->height = parseStrToInt(h, 2);
    }

    
    if (f->contentsLength < MIN_LEVEL_FILE_SIZE + out->width + out->height){
        gLog(LOG_ERROR, "Level data corrupted %s", levePath);
    }
    
    
    // read tile data
    {
        out->tiles = malloc(sizeof(char*) * out->width);

        for (int x = 0; x < out->width; x++){
            out->tiles[x] = malloc(sizeof(char) * out->height);
            for (int y = 0; y < out->height; y++){
                out->tiles[x][y] = f->contents[(x * out->height) + y + LEVEL_DATA_START];
            }
        }
    }

    int markersStart = out->width * out->height + LEVEL_DATA_START;
    {
        out->entityeMarkers = initVector();
        
        // read markers
        for (int i = markersStart; i < f->contentsLength; i+=6){
            vectorPush(&out->entityeMarkers, initEntityMarker(f->contents, i));
        }
    }

    return out;
}

void saveLevel(Level* lvl){
    gLog(LOG_INFO, "Saving level to file %s", lvl->levelFile->filePath);

    // construct file contents
    char newContents[MAX_FILE_SIZE];
    int contentsIndex = 0;

    {
        // write header
        writeIntAsChar(newContents, lvl->width, 2, 0);
        writeIntAsChar(newContents, lvl->height, 2, 2);
        contentsIndex = LEVEL_DATA_START;
    }

    {
        // write tiles
        for (int x = 0; x < lvl->width; x++){
            for (int y = 0; y < lvl->height; y++){
                newContents[LEVEL_DATA_START + y + (x * lvl->height)] = lvl->tiles[x][y];
            }
        }
        contentsIndex = LEVEL_DATA_START + (lvl->width * lvl->height);
    }

    {
        // save markers
        for (int i = 0; i < lvl->entityeMarkers.elementCount; i++){
            saveEntityMarker(vectorGet(&lvl->entityeMarkers, i), newContents, contentsIndex);
            contentsIndex += 6;
        }
    }

    {
        // set file contents
        char* contetns = malloc(sizeof(char) * contentsIndex);
        // copy contents
        for (int i = 0; i < contentsIndex; i++){
            contetns[i] = newContents[i];
        }
        setFileContents(lvl->levelFile, contetns, contentsIndex);
    }

    

    saveFile(lvl->levelFile);
}

void unloadLevel(Level* level){
    unloadFile(level->levelFile);
    for (int i = 0; i < level->width;i++){
        free(level->tiles[i]);
    }

    for (int i = 0; i < level->entityeMarkers.elementCount; i++){
        disposeEntityMarker(vectorGet(&level->entityeMarkers, i));
    }

    free(level->tiles);
    free(level);
}


void resizeLevel(Level* level, int newWidth, int newHeight){
    if(newWidth < 1 || newHeight < 1){
        return;
    }

    // init new contents    
    char** newLevelContent = malloc(sizeof(char*) * newWidth);
    for (int i = 0; i < newWidth; i++){
        newLevelContent[i] = malloc(sizeof(char*) * newHeight);
    }
    // copy old contents
    for (int x = 0; x < newWidth; x++){
        for (int y = 0; y < newHeight; y++){
            if (x < level->width && y < level->height){
                newLevelContent[x][y] = level->tiles[x][y];
            }else {
                // else fill with air
                newLevelContent[x][y] = 0;
            }
        }
    }

    // free old contents
    for (int i = 0; i < level->width;i++){
        free(level->tiles[i]);
    }
    free(level->tiles);


    // set new contents
    level->tiles = newLevelContent;
    level->width = newWidth;
    level->height = newHeight;
}



#define TILE_SPRITE_START 7
void drawLevel(Level* lvl){
    for (int x = 0; x < lvl->width; x++){
        for (int y = 0; y < lvl->height; y++){
            if (lvl->tiles[x][y] != 0){
                draw(TILE_SPRITE_START + lvl->tiles[x][y], x * 32, y * 32, LAYER_WORLD);
            }
        }
    }
}


#define MARKER_SPRITE_START 7
const Color MARKER_COLOR = {255, 255, 255, 100};
void drawEntityMarkers(Level* lvl){
    for (int i = 0; i < lvl->entityeMarkers.elementCount; i++){
        EntityMarker* marker = vectorGet(&lvl->entityeMarkers, i);
        drawC(MARKER_SPRITE_START + marker->id, marker->x * 32, marker->y * 32, MARKER_COLOR, LAYER_OBJECTS);
    }
}



#endif