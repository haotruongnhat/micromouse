

byte calcCenter(byte posx, byte posy, byte dim) {
  byte center = dim / 2;
  byte dist = 0;

  if (posy < center) {
    if (posx < center) {
      //You're in the top left of the maze
      dist = calcDist(posx, posy, (center - 1), (center - 1));
    }
    else {
      //You're in the top right of the maze
      dist = calcDist(posx, posy, center, (center - 1));
    }
  }
  else {
    if (posx >= center) {
      //You're in the bottom right of the maze
      dist = calcDist(posx, posy, center, center);
    }
    else {
      //You're in the bottom left of the maze
      dist = calcDist(posx, posy, (center - 1), center);
    }
  }
  return dist;

}

byte calcDist(byte posx, byte posy, byte desireX, byte desireY) {
  byte dist = (byte)(abs(desireY - posy) + abs(desireX - posx));
  return dist;
}

void instantiateReflood() {
  for (byte j = 0; j < Y; j++) {
    for (byte i = 0; i < X; i++) {
      maze[j][i].distance = calcCenter(i, j, X);
    }
  }
}

void instantiate() {
  for (byte j = 0; j < Y; j++) {
    for (byte i = 0; i < X; i++) {
      maze[j][i].distance = calcCenter(i, j, X);
      maze[j][i].walls = 15;
      //If this is the left column (0,x)
      if (i == 0) {
        maze[j][i].walls = 7;
      }
      //if this is the top row
      if (j == 0) {
        maze[j][i].walls = 14;
      }
      //if this is the bottom row
      if (j == (Y - 1)) {
        maze[j][i].walls = 13;
      }
      //If this is the righ column
      if (i == (X - 1)) {
        maze[j][i].walls = 11;
      }
      maze[0][0].walls = 6;
      maze[Y - 1][0].walls = 5;
      maze[0][X - 1].walls = 10;
      maze[X - 1][Y - 1].walls = 9;
    }
  }

}

void resetToCoord(coord desiredCoord) {
  for (byte j = 0; j < Y; j++) {
    for (byte i = 0; i < X; i++) {
      maze[j][i].distance = calcDist(i, j, desiredCoord.x, desiredCoord.y);
    }
  }
}

bool checkBounds(coord Coord) {
  if ((Coord.x >= X) || (Coord.y >= Y) || (Coord.x < 0) || (Coord.y < 0)) {
    return false;
  }
  else {
    return true;
  }
}

coord bearingCoord(coord currCoord, byte heading) {
  coord nextCoord = { 0, 0 };
  switch (heading) {
    case 1:
      //code
      nextCoord.x = currCoord.x;
      nextCoord.y = currCoord.y - 1;
      break;
    case 2:
      nextCoord.x = currCoord.x;
      nextCoord.y = currCoord.y + 1;
      break;
    case 4:
      nextCoord.x = currCoord.x + 1;
      nextCoord.y = currCoord.y;
      break;
    case 8:
      nextCoord.x = currCoord.x - 1;
      nextCoord.y = currCoord.y;
      break;
  }
  return nextCoord;
}

byte orient(coord currCoord, byte heading) {
  coord leastNext = { 0, 0 };
  //This is the absolute largest value possible (dimension of maze squared)
  int leastNextVal = X * X;
  byte leastDir = heading;

  //If there is a bitwise equivalence between the current heading and the cell's value, then the next cell is accessible
  if ((maze[currCoord.y][currCoord.x].walls & heading) != 0) {
    //Define a coordinate for the next cell based onthis heading and set the leastNextVal t its value
    coord leastnextTemp = bearingCoord(currCoord, heading);

    if (checkBounds(leastnextTemp)) {
      leastNext = leastnextTemp;
      leastNextVal = maze[leastNext.y][leastNext.x].distance;
    }
  }

  for (byte i = 0; i < 4; i++) {
    byte dir = headings[i];
    //if this dir is accessible
    if ((maze[currCoord.y][currCoord.x].walls & dir) != 0) {
      //define the coordiante for this dir
      coord dirCoord = bearingCoord(currCoord, dir);

      if (checkBounds(dirCoord)) {
        //if this dir is more optimal than continuing straight
        if (maze[dirCoord.y][dirCoord.x].distance < leastNextVal) {
          //update teh value of leastNextVal
          leastNextVal = maze[dirCoord.y][dirCoord.x].distance;
          //update the value of leastnext to this dir
          leastNext = dirCoord;
          leastDir = dir;
        }
      }
    }
  }
  return leastDir;
}

byte checkNeighs(coord Coord) {
  int minVal = X * X;
  for (byte i = 0; i < 4; i++) {
    byte dir = headings[i];
    //if this dir is accessible
    if ((maze[Coord.y][Coord.x].walls & dir) != 0) {
      //Get the coordinate of the accessible neighbor
      coord neighCoord = bearingCoord(Coord, dir);
      //Check the value of the accessible neighbor
      if (checkBounds(neighCoord)) {
        //if the neighbore is less than the current recording minimum value, update the minimum value
        //If minVal is null, set it right away, otherwise test
        if (maze[neighCoord.y][neighCoord.x].distance < minVal) {
          minVal = maze[neighCoord.y][neighCoord.x].distance;
        }
      }
    }
  }
  return minVal;
}

bool isDead(coord coord) {
  bool deadEnd = false;
  if (checkBounds(coord)) {
    byte bounds = maze[coord.y][coord.x].walls;
    //bounds is the integer from the exploratory maze that represents the known walls of the coordinate
    if ((bounds == 1) || (bounds == 2) || (bounds == 4) || (bounds == 8)) {
      deadEnd = true;
    }
  }
  return deadEnd;
}

bool isEnd(coord Coord, coord DesiredArray[]) {
  bool End = false;
  for (byte i = 0; i < numDesiredArray; i++) {
    coord Desired = DesiredArray[i];
    if (checkBounds(Coord)) {
      if ((Coord.x == Desired.x) && (Coord.y == Desired.y)) {
        End = true;
      }
    }
  }
  return End;
}

void coordUpdate(coord coordinate, byte wallDir) {
  if (checkBounds(coordinate)) {
    if ((maze[coordinate.y][coordinate.x].walls & wallDir) != 0) {
      maze[coordinate.y][coordinate.x].walls = maze[coordinate.y][coordinate.x].walls - wallDir;
    }
  }
}

byte readCurrent(coord currCord) {
  // need to code
  //return mazetemp[currCord.y][currCord.x].walls;
}

void updateWall(coord currCoord) {
  for (byte i = 0; i<4; i++) {
    byte dir = headings[i];

    //updatewall
    //If there's a wall in this dir
    if ((maze[currCoord.y][currCoord.x].walls & dir) == 0) {
      //create a temporary working coordinate
      coord workingCoord = { currCoord.x,currCoord.y };
      switch (dir) {
      case 1:
        workingCoord.y = workingCoord.y - 1;
        coordUpdate(workingCoord, 2);
        break;
      case 2:
        workingCoord.y = workingCoord.y + 1;
        coordUpdate(workingCoord, 1);
        break;
      case 4:
        workingCoord.x = workingCoord.x + 1;
        coordUpdate(workingCoord, 8);
        break;
      case 8:
        workingCoord.x = workingCoord.x - 1;
        coordUpdate(workingCoord, 4);
        break;
      }
      //If the workingEntry is a valid entry and not a finish, push it onto the stack
      //if (checkBounds(workingCoord) && (!isEnd(workingCoord, desired))) {
      //  entries.push_back(workingCoord);
      //}
    }
  }
}

void floodFillUpdate(coord currCoord, coord desired[], bool isMoving) {
  StackList<coord> entries;
  
//  if(isMoving)
//    maze[currCoord.y][currCoord.x].walls = readCurrent(currCoord);
  
  entries.push(currCoord);
  updateWall(currCoord);

  //While the entries stack isn't empty
  while (!entries.isEmpty()) {
    //Pop an entry from the stack
    coord workingEntry = entries.pop();
    byte neighCheck = checkNeighs(workingEntry);
    //If the least neighbor of the working entry is not one less than the value of the working entry
    if (neighCheck + 1 != maze[workingEntry.y][workingEntry.x].distance) {
      maze[workingEntry.y][workingEntry.x].distance = neighCheck + 1;
      for (byte i = 0; i<4; i++) {
        byte dir = headings[i];
        if ((maze[workingEntry.y][workingEntry.x].walls & dir) != 0) {
          coord nextCoord = bearingCoord(workingEntry, dir);
          if (checkBounds(nextCoord)) {
            if (!isEnd(nextCoord, desired)) {
              entries.push(nextCoord);
            }
          }
        }
      }
    }
  }
}

void floodFill(coord desired[], coord current, bool isMoving) {
  coord currCoord = current;
  byte heading = globalHeading;
  /*Integer representation of heading
  * 1 = N
  * 4 = E
  * 2 = S
  * 8 = W
  */
  while (maze[currCoord.y][currCoord.x].distance != 0) {
    floodFillUpdate(currCoord, desired,isMoving);
    byte nextHeading = orient(currCoord, heading);
    coord nextCoord = bearingCoord(currCoord, nextHeading);

    if (isMoving) {
      moveInstruction(globalHeading,nextHeading);
      
      
      //Call createInstruction to push a new instruction to the stack
      //instructions.push(createInstruction(currCoord, nextCoord, nextHeading));

      //Pop the next instruction from the instructions queue and execute it
      //executeInstruction(instructions.pop());
    }

    //After exectuing the instruction update the values of the local and global variables
    currCoord = nextCoord;
    heading = nextHeading;
    
    //If the robot has actually moved, update the global position variabless
    if (isMoving) {
      globalHeading = heading;
      globalCoord = currCoord;
    }
  }
  //Set the global end as the current coordinate.
  globalEnd = currCoord;
}

void createSpeedQueue();

void updateWallinCenter(coord current, coord desired[]) {
  byte walltemp[4] = { 6, 5, 10, 9 };
  for (byte i = 0; i < 4; i++) {
    if ((desired[i].x != current.x) || (desired[i].y != current.y)) {
      maze[desired[i].y][desired[i].x].walls = walltemp[i];
      updateWall(desired[i]);
    }
  }
}

