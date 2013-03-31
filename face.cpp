// face.cpp
// Robert Gruener
// 3/18/13

#include "face.h"


Face::Face(SIDE s, Piece *cube[3][3][3]){
    reset(s, cube);
}

void Face::reset(SIDE s, Piece *cube[3][3][3]){
    side = s;
    int i,j;
    switch(s){
        case SIDE_BACK:
            for (i=0; i<3; i++){
                for (j=0; j<3; j++){
                    pieces[i][j] = &cube[i][j][2];
                }
            }
            break;
        case SIDE_LEFT:
            for (i=0; i<3; i++){
                for (j=0; j<3; j++){
                    pieces[i][j] = &cube[0][i][j];
                }
            }
            break;
        case SIDE_RIGHT:
            for (i=0; i<3; i++){
                for (j=0; j<3; j++){
                    pieces[i][j] = &cube[2][i][j];
                }
            }
            break;
        case SIDE_TOP:
            for (i=0; i<3; i++){
                for (j=0; j<3; j++){
                    pieces[i][j] = &cube[i][2][j];
                }
            }
            break;
        case SIDE_BOTTOM:
            for (i=0; i<3; i++){
                for (j=0; j<3; j++){
                    pieces[i][j] = &cube[i][0][j];
                }
            }
            break;
        case SIDE_FRONT:
            for (i=0; i<3; i++){
                for (j=0; j<3; j++){
                    pieces[i][j] = &cube[i][j][0];
                }
            }
            break;
    }
}

void Face::rotate(bool dir){
    if (dir){
        Piece *tmp_point = *(pieces[0][0]);
        *(pieces[0][0]) = *(pieces[0][2]);
        *(pieces[0][2]) = *(pieces[2][2]);
        *(pieces[2][2]) = *(pieces[2][0]);
        *(pieces[2][0]) = tmp_point;
        tmp_point = *(pieces[1][0]);
        *(pieces[1][0]) = *(pieces[0][1]);
        *(pieces[0][1]) = *(pieces[1][2]);
        *(pieces[1][2]) = *(pieces[2][1]);
        *(pieces[2][1]) = tmp_point;
    } else {
        Piece *tmp_point = *(pieces[0][0]);
        *(pieces[0][0]) = *(pieces[2][0]);
        *(pieces[2][0]) = *(pieces[2][2]);
        *(pieces[2][2]) = *(pieces[0][2]);
        *(pieces[0][2]) = tmp_point;
        tmp_point = *(pieces[1][0]);
        *(pieces[1][0]) = *(pieces[2][1]);
        *(pieces[2][1]) = *(pieces[1][2]);
        *(pieces[1][2]) = *(pieces[0][1]);
        *(pieces[0][1]) = tmp_point;
    }
}

SIDE Face::getSide(){
    return side;
}
