// piece.cpp
// Robert Gruener
// 3/18/13

#include <iostream>
#include "piece.h"

int piece_point_index = 0;

void Piece::quad(point4 a, point4 b, point4 c, point4 d, SIDE side){
    colors[piece_point_index] = side_colors_rgb[piece_side_colors[side]];
    points[piece_point_index++] = a;
    colors[piece_point_index] = side_colors_rgb[piece_side_colors[side]];
    points[piece_point_index++] = b;
    colors[piece_point_index] = side_colors_rgb[piece_side_colors[side]];
    points[piece_point_index++] = c;
    colors[piece_point_index] = side_colors_rgb[piece_side_colors[side]];
    points[piece_point_index++] = a;
    colors[piece_point_index] = side_colors_rgb[piece_side_colors[side]];
    points[piece_point_index++] = c;
    colors[piece_point_index] = side_colors_rgb[piece_side_colors[side]];
    points[piece_point_index++] = d;
}

Piece::Piece(point4 pos, int piece_number){
    piece_num = piece_number;
    reset(pos);
}

void Piece::reset(point4 pos){
    rotation = Translate(0,0,0);
    piece_side_colors[SIDE_RIGHT]  = pos.x== 1 ? WHITE  : BLACK;
    piece_side_colors[SIDE_LEFT]   = pos.x==-1 ? BLUE   : BLACK;
    piece_side_colors[SIDE_TOP]    = pos.y== 1 ? GREEN  : BLACK;
    piece_side_colors[SIDE_BOTTOM] = pos.y==-1 ? ORANGE : BLACK;
    piece_side_colors[SIDE_FRONT]  = pos.z== 1 ? BLACK    : RED;
    piece_side_colors[SIDE_BACK]   = pos.z==-1 ? BLACK : YELLOW;
    if (pos.z == 0){
        piece_side_colors[SIDE_FRONT] = piece_side_colors[SIDE_BACK] = BLACK;
    }
    float factor = .25; // size factor
    float gap = 0.2; // gap factor independent of size factor
    gap*=factor;

    // determine cube points, based on fact cube positions for x,y,z will be -1,0,or 1
    point4 front_top_left = pos*factor + point4(-.66*factor+gap, .66*factor-gap, -.66*factor+gap, 1-factor);
    point4 front_top_right = pos*factor + point4(.66*factor-gap, .66*factor-gap, -.66*factor+gap, 1-factor);
    point4 front_bottom_left = pos*factor + point4(-.66*factor+gap, -.66*factor+gap, -.66*factor+gap, 1-factor);
    point4 front_bottom_right = pos*factor + point4(.66*factor-gap, -.66*factor+gap, -.66*factor+gap, 1-factor);
    point4 back_top_left = pos*factor + point4(-.66*factor+gap, .66*factor-gap, .66*factor-gap, 1-factor);
    point4 back_top_right = pos*factor + point4(.66*factor-gap, .66*factor-gap, .66*factor-gap, 1-factor);
    point4 back_bottom_left = pos*factor + point4(-.66*factor+gap, -.66*factor+gap, .66*factor-gap, 1-factor);
    point4 back_bottom_right = pos*factor + point4(.66*factor-gap, -.66*factor+gap, .66*factor-gap, 1-factor);

    piece_point_index=0;
    quad(back_top_left, back_bottom_left, back_bottom_right, back_top_right, SIDE_BACK);
    quad(front_top_left, front_bottom_left, back_bottom_left, back_top_left, SIDE_LEFT);
    quad(front_top_right, front_bottom_right, back_bottom_right, back_top_right, SIDE_RIGHT);
    quad(front_top_left, front_top_right, back_top_right, back_top_left, SIDE_TOP);
    quad(front_bottom_left, front_bottom_right, back_bottom_right, back_bottom_left, SIDE_BOTTOM);
    quad(front_top_left, front_bottom_left, front_bottom_right, front_top_right, SIDE_FRONT);
}

point4 *Piece::getPoints(){
    return this->points;
}

color4 *Piece::getColors(){
    return this->colors;
}

mat4 Piece::getRotation(){
    return rotation;
}

void Piece::addRotation(mat4 rot){
    rotation = rot * rotation;
}

int Piece::getNumVertices(){
    return Num_Vertices;
}

SIDE_COLOR Piece::getSideColor(SIDE s){
    return piece_side_colors[(int)s];
}
