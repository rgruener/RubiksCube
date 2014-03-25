// cube.h
// Robert Gruener
// 3/17/13

#ifndef _CUBE_H
#define _CUBE_H

#include <iostream>
#include <list>
#include <ctime>
#include <string>
#include "piece.h"
#include "face.h"
#include "cubemove.h"
#include "Angel.h"

using namespace std;

class Cube {

    private:
        Piece *pieces[3][3][3];
        Face *faces[6];
        point4 *points;
        color4 *colors;
        int num_points;
        list<CubeMove> moves;
        bool rotateFaceHelper(SIDE face, float angle);

    public:

        Cube(int num_turns = 0);
        void init(int turns);
        void reset();
        Piece *getPiece(int x, int y, int z);
        point4 *getPoints();
        color4 *getColors();
        mat4 getRotation(int x, int y, int z);
        int getNumPoints();
        bool rotateFace(SIDE face, bool dir, bool animate, bool add_move = true);
        bool undoLastMove();
        bool saveCube();
        bool loadCube(string fname);
        bool checkComplete();

};

#endif
