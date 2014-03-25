// piece.h
// Robert Gruener
// 3/18/13

#ifndef _PIECE_H
#define _PIECE_H

#include "Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

using namespace std;

const int Num_Vertices = 36;

typedef enum {
    SIDE_RIGHT,
    SIDE_LEFT,
    SIDE_TOP,
    SIDE_BOTTOM,
    SIDE_FRONT,
    SIDE_BACK,
} SIDE;

typedef enum {
    BLACK,
    RED,
    YELLOW,
    GREEN,
    BLUE,
    ORANGE,
    WHITE,
} SIDE_COLOR;

// RGBA colors
const color4 side_colors_rgb[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    color4( 1.0, 0.5, 0.0, 1.0 ),  // orange
    color4( 1.0, 1.0, 1.0, 1.0 ),  // white
};

class Piece {

    private:

        SIDE_COLOR piece_side_colors[6];
        point4 position;
        point4 points[Num_Vertices];
        color4 colors[Num_Vertices];
        int piece_num;
        mat4 rotation;

        void quad(point4 a, point4 b, point4 c, point4 d, SIDE side);

    public:

        Piece(point4 pos, int piece_number);
        void reset(point4 pos);
        point4 *getPoints();
        color4 *getColors();
        int getPieceNum();
        mat4 getRotation();
        void addRotation(mat4 rot);
        static int getNumVertices();
        SIDE_COLOR getSideColor(SIDE s);
};


#endif
