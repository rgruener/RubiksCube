// cube.cpp
// Robert Gruener
// 3/18/13

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "cube.h"

Cube::Cube(int num_turns /* =0 */){
    num_points = Piece::getNumVertices()*27;
    init(num_turns);
}

void Cube::init(int turns){
    reset();
    int i;
    for (i=0; i<6; i++){
        faces[i] = new Face((SIDE)i, pieces);
    }
    // perform random rotations
    srand(time(NULL));
    int turn_face,dir;
    for (i=0;i<turns;i++){
        turn_face = rand() % 6;
        dir = rand() % 2;
        rotateFace((SIDE)turn_face,dir,false);
    }
}

void Cube::reset(){
    int i,j,k,num=1;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            for (k=0;k<3;k++){
                pieces[i][j][k] = new Piece(point4(i-1,j-1,k-1,1.0), num++);
            }
        }
    }
}

extern void display(void);

bool Cube::rotateFace(SIDE face, bool dir, bool animate, bool add_move /* = true */){

    int k;
    int factor = dir? 1:-1;

    int milisec = 5; // length of time to sleep, in miliseconds
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;

    float b = 1;

    if (animate){
        for (k=0;k<30;k++){
            rotateFaceHelper(face, 3.0f*factor);
            display();
            nanosleep(&req, (struct timespec *)NULL);
        }
    } else {
        rotateFaceHelper(face, 90.f*factor);
        glutPostRedisplay();
    }

    faces[face]->rotate(dir);
    if (add_move){
        moves.push_back(CubeMove(face,dir));
    }
    glutPostRedisplay();

    return true;
}

bool Cube::rotateFaceHelper(SIDE face, float angle){

    int i,j;

    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            switch (face){
                case SIDE_FRONT:
                    pieces[i][j][0]->addRotation(RotateZ(angle));
                    break;
                case SIDE_BACK:
                    pieces[i][j][2]->addRotation(RotateZ(angle));
                    break;
                case SIDE_LEFT:
                    pieces[0][i][j]->addRotation(RotateX(angle));
                    break;
                case SIDE_RIGHT:
                    pieces[2][i][j]->addRotation(RotateX(angle));
                    break;
                case SIDE_TOP:
                    pieces[i][2][j]->addRotation(RotateY(angle*-1));
                    break;
                case SIDE_BOTTOM:
                    pieces[i][0][j]->addRotation(RotateY(angle*-1));
                    break;
            }
        }
    }
}

point4 *Cube::getPoints(){
    points = (point4 *)malloc(Piece::getNumVertices()*27*sizeof(point4));
    int i,j,k,index=0;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            for (k=0;k<3;k++){
                copy(pieces[i][j][k]->getPoints(), pieces[i][j][k]->getPoints()+Piece::getNumVertices(), points + index++*Piece::getNumVertices());
           }
        }
    }
    return points;
}

color4 *Cube::getColors(){
    colors = (color4 *)malloc(Piece::getNumVertices()*27*sizeof(color4));
    int i,j,k,index=0;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            for (k=0;k<3;k++){
                copy(pieces[i][j][k]->getColors(), pieces[i][j][k]->getColors()+Piece::getNumVertices(), colors + index++*Piece::getNumVertices());
           }
        }
    }
    return colors;
}

Piece *Cube::getPiece(int x, int y, int z){
    return pieces[x][y][z];
}

mat4 Cube::getRotation(int x, int y, int z){
    return pieces[x][y][z]->getRotation();
}

int Cube::getNumPoints(){
    return num_points;
}

bool Cube::undoLastMove(){
    if (!moves.empty()){
        CubeMove last = moves.back();
        moves.pop_back();
        rotateFace(last.face, !last.dir, true, false);
    }
}


bool Cube::saveCube(){
    ofstream outfile;
    string fname;
    cout << "Please Specify file name for cube save: ";
    cin >> fname;
    outfile.open(fname.c_str(), ios::out | ios::binary);
    
    if (outfile.is_open()){
        for (list<CubeMove>::iterator it=moves.begin(); it != moves.end(); ++it){
            outfile << (*it).face << (*it).dir;
        }
        outfile.close();
        return true;
    } else {
        cerr << "Error opening file: " << fname << endl;
        return false;
    }
}

bool Cube::loadCube(string fname){
    ifstream infile;
    infile.open(fname.c_str(), ios::in | ios::binary);

    int side;
    bool dir;
    char buf[2];

    if (infile.is_open()){
        infile.seekg(0, ios::beg);
        while (infile.read(buf,2)){
            side = buf[0] - '0';
            dir = bool(buf[1] - '0');
            rotateFace((SIDE)side, dir, false);
        }
        infile.close();
        return true;
    } else {
        cerr << "Error opening file: " << fname << endl;
        return false;
    }
}

bool Cube::checkComplete(){
    int i,j,k;
    SIDE_COLOR c;
    for (i=0;i<6;i++){
        for (j=0;j<3;j++){
            for (k=0;k<3;k++){
                if (j==0 && k==0){
                    c = (*(faces[i]->pieces[j][k]))->getSideColor(faces[i]->getSide());
                } else if ((*(faces[i]->pieces[j][k]))->getSideColor(faces[i]->getSide()) != c) {
                    return false;
                }
            }
        }
    }
    return true;
}
