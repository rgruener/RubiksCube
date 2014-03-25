// face.h
// Robert Gruener
// 3/18/13

#ifndef _FACE_H
#define _FACE_H

#include "Angel.h"
#include "piece.h"

class Face {

    private:

        SIDE side;

    public:

        Piece **pieces[3][3];
        Face(SIDE s, Piece *cube[3][3][3]);
        void reset(SIDE s, Piece *cube[3][3][3]);
        void rotate(bool dir);
        SIDE getSide();
};


#endif
