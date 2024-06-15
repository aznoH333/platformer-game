#ifndef ENTITIES
#define ENTITIES 

#include <stdlib.h>
#include "gutil.c"

struct EntityMarker{
    int x;
    int y;
    int id;
};

typedef struct EntityMarker EntityMarker;

EntityMarker* initEntityMarker(char* levelData, int markerIndex){
    EntityMarker* out = malloc(sizeof(EntityMarker));
    
    
    char x[2] = {levelData[markerIndex], levelData[markerIndex + 1]};
    out->x = parseStrToInt(x, 2);
    char y[2] = {levelData[markerIndex + 2], levelData[markerIndex + 3]};
    out->y = parseStrToInt(y, 2);
    char id[2] = {levelData[markerIndex + 4], levelData[markerIndex + 5]};
    out->id = parseStrToInt(id, 2);

    return out;
}

void saveEntityMarker(EntityMarker* marker, char* fileData, int markerIndex){
    writeIntAsChar(fileData, marker->x, 2, markerIndex);
    writeIntAsChar(fileData, marker->y, 2, markerIndex + 2);
    writeIntAsChar(fileData, marker->id, 2, markerIndex + 4);
}

void disposeEntityMarker(EntityMarker* marker){
    free(marker);
}




#endif