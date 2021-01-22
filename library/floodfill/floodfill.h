#include "coord.h"
#include "entry.h"
#include "StackList.h"


const byte headings[] = { 1, 2, 4, 8 };

const byte NORTH=0;
const byte SOUTH=1;
const byte EAST=2;
const byte WEST =3;

#define X 8
#define Y 8

entry maze[X][Y];

byte globalHeading = NORTH;

coord globalCoord = { 0,Y-1 };

coord globalEnd = { 0,0 };


byte calcCenter(byte posx, byte posy, byte dim);

byte calcDist(byte posx, byte posy, byte desireX, byte desireY);

void instantiateReflood();

void instantiate();

void resetToCoord(  coord desiredCoord);

bool checkBounds(coord Coord);

coord bearingCoord(coord currCoord, byte heading);

byte orient(coord currCoord, byte heading);

byte checkNeighs(coord Coord);

bool isDead(coord coord);

bool isEnd(coord Coord, coord DesiredArray[]);

void coordUpdate(coord coordinate, byte wallDir);

byte readCurrent(coord currCord);

void updateWall(coord currCoord);

void floodFillUpdate(coord currCoord, coord desired[], bool isMoving);

void floodFill(coord desired[], coord current, bool isMoving);

void createSpeedQueue();

void updateWallinCenter(coord current,coord desired[]);

