// cubemove.h
// Robert Gruener
// 3/18/13

#ifndef _CUBEMOVE_H
#define _CUBEMOVE_H

#include "piece.h"

class CubeMove {
    
    public:

        SIDE face;
        bool dir;
        CubeMove(SIDE s, bool d):face(s),dir(d){}
};

#endif
