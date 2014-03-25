// rubiks.h
// Robert Gruener
// 3/18/13

#include "Angel.h"
#include "cube.h"
#include <string>
#include <cstring>
#include <unistd.h>

point4 *points;
color4 *colors;

Cube *myCube;

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };
GLuint  model_view;  // The location of the "model_view" shader uniform variable
GLuint face_rotations;
GLuint buffer;
GLuint indexBuffer;
GLuint vaoObject[27];

double camera_angle_h = 0;
double camera_angle_v = 0;

int drag_x_origin;
int drag_y_origin;
int dragging = 0;

bool animate = true;
int initial_turns=0;
int load_cube=0;
string save_file_name;

void* glutFonts[7] = {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_8_BY_13,
    GLUT_BITMAP_TIMES_ROMAN_10,
    GLUT_BITMAP_TIMES_ROMAN_24,
    GLUT_BITMAP_HELVETICA_10,
    GLUT_BITMAP_HELVETICA_12,
    GLUT_BITMAP_HELVETICA_18
};

//----------------------------------------------------------------------------

void glutPrint(float x, float y, void* font, string text, float r, float g, float b, float a){
    if(!text.length()) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(r,g,b,a);
    glRasterPos2f(x,y);
    for (int i=0;i<text.length();i++) {
        glutBitmapCharacter(font, text[i]);
    }
    if(!blending) glDisable(GL_BLEND);
}

//----------------------------------------------------------------------------

// OpenGL initialization
void init(){
    myCube = new Cube(initial_turns);
    if (load_cube){
        myCube->loadCube(save_file_name);
    }
    points = myCube->getPoints();
    colors = myCube->getColors();

    int num_points = myCube->getNumPoints();
    int i,j,k,index=0;
    int cur_num_points;

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, num_points*(sizeof(point4) + sizeof(color4)),
		  NULL, GL_STREAM_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*num_points, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*num_points, sizeof(color4)*num_points, colors );

    //Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    //set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
               BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
               BUFFER_OFFSET(sizeof(point4)*num_points) );


    model_view = glGetUniformLocation( program, "model_view" );
    face_rotations = glGetUniformLocation( program, "face_rotations" );

    glEnable( GL_DEPTH_TEST );
    glClearColor( .5, .5, .5, 1.0 );
}

//----------------------------------------------------------------------------

void display( void ){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    mat4 mv = RotateY(Theta[Yaxis]) * RotateX(Theta[Xaxis]);
    mat4 rot;

    glUniformMatrix4fv( model_view, 1, GL_TRUE, mv );

    int i,j,k;
    int offset_points=0;
    int offset_bytes=0;

    int num_points = myCube->getNumPoints();

    points = myCube->getPoints();
    colors = myCube->getColors();

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*num_points, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*num_points, sizeof(color4)*num_points, colors );

    bool complete = myCube->checkComplete();

    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            for (k=0;k<3;k++){
                rot = myCube->getRotation(i,j,k);
                glUniformMatrix4fv( face_rotations, 1, GL_TRUE, rot);
                glDrawArrays( GL_TRIANGLES, offset_points, num_points/27 );
                offset_bytes += sizeof(point4) * num_points/27;
                offset_points += num_points/27;
            }
        }
    }
    if (complete){
        glutPrint(-0.55f, 0.65f, glutFonts[6], "Congratulations! The Cube is Complete", 0.0f, 0.0f, 0.0f, 1.0f);
    }

    glutPrint(-0.8f, -0.5f, glutFonts[5], "Directions", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.55f, glutFonts[5], "Rotate Face With Red Center: <a>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.60f, glutFonts[5], "Rotate Face With Yellow Center: <z>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.65f, glutFonts[5], "Rotate Face With Blue Center: <s>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.70f, glutFonts[5], "Rotate Face With White Center: <x>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.75f, glutFonts[5], "Rotate Face With Green Center: <d>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.80f, glutFonts[5], "Rotate Face With Orange Center: <c>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.85f, glutFonts[5], "Undo Last Move: <u>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.90f, glutFonts[5], "Save Cube: <w> followed by command line input", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.9f, -0.95f, glutFonts[5], "Exit Program: <esc>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.1f, -0.60f, glutFonts[5], "Note: Perform opposite rotation with <shift><rotation key>", 0.0f, 0.0f, 0.0f, 1.0f);
    glutPrint(-0.1f, -0.65f, glutFonts[5], "Rotate entire cube with left click and drag or arrow keys", 0.0f, 0.0f, 0.0f, 1.0f);

    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y ){
    bool save_success;
    switch( key ) {
        case 033:  // Escape key
            exit( EXIT_SUCCESS );
            break;
        case 'a':
            myCube->rotateFace(SIDE_FRONT, true, animate);
            break;
        case 'A':
            myCube->rotateFace(SIDE_FRONT, false, animate);
            break;
        case 'z':
            myCube->rotateFace(SIDE_BACK, true, animate);
            break;
        case 'Z':
            myCube->rotateFace(SIDE_BACK, false, animate);
            break;
        case 's':
            myCube->rotateFace(SIDE_LEFT, true, animate);
            break;
        case 'S':
            myCube->rotateFace(SIDE_LEFT, false, animate);
            break;
        case 'x':
            myCube->rotateFace(SIDE_RIGHT, true, animate);
            break;
        case 'X':
            myCube->rotateFace(SIDE_RIGHT, false, animate);
            break;
        case 'd':
            myCube->rotateFace(SIDE_TOP, true, animate);
            break;
        case 'D':
            myCube->rotateFace(SIDE_TOP, false, animate);
            break;
        case 'c':
            myCube->rotateFace(SIDE_BOTTOM, true, animate);
            break;
        case 'C':
            myCube->rotateFace(SIDE_BOTTOM, false, animate);
            break;
        case 'w': case 'W':
            save_success = myCube->saveCube();
            if (save_success){
                cout << "Successfully Saved Cube!" << endl;
            } else {
                cerr << "Error while saving cube" << endl;
            }
            break;
        case 'u': case 'U':
            myCube->undoLastMove();
            break;
    }
}

//----------------------------------------------------------------------------

void special_keyboard( int key, int x, int y ){
    int angle_factor = 4;
    switch( key ) {
        case GLUT_KEY_LEFT:
            Theta[Yaxis] += angle_factor;
            break;
        case GLUT_KEY_RIGHT:
            Theta[Yaxis] -= angle_factor;
            break;
        case GLUT_KEY_UP:
            Theta[Xaxis] += angle_factor;
            break;
        case GLUT_KEY_DOWN:
            Theta[Xaxis] -= angle_factor;
            break;
    }
    if (Theta[Xaxis] > 360.0)
        Theta[Xaxis] -= 360.0;
    if (Theta[Yaxis] > 360.0)
        Theta[Yaxis] -= 360.0;
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void mouse( int button, int state, int x, int y ){
    switch (button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
                dragging = 1;
                drag_x_origin = x;
                drag_y_origin = y;
            }
            else
                dragging = 0;
            break;
    }
}

//----------------------------------------------------------------------------

void mouse_move(int x, int y){
    if(dragging) {
        Theta[Xaxis] += (y - drag_y_origin)*0.3;
        Theta[Yaxis] += (x - drag_x_origin)*0.3;
        drag_x_origin = x;
        drag_y_origin = y;
        glutPostRedisplay();
    }
}

//----------------------------------------------------------------------------

int main( int argc, char **argv ){

    string input;
    cout << "Would you like to load a previous cube? (y/n)" << endl;
    cin >> input;
    while (input != "y" && input != "n"){
        cout << "Please enter \'y\' or \'n\'" << endl;
        cin >> input;
    }
    if (input == "y"){
        cout << "Enter the name of your save file: ";
        cin >> save_file_name;
        load_cube = 1;
    } else {
        cout << "How many random turns would you like to start off you cube with? : ";
        cin >> initial_turns;
    }

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 600, 600 );
    glutCreateWindow( "Rubiks Cube" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( special_keyboard );
    glutMouseFunc( mouse );
    glutMotionFunc( mouse_move);
    //glutIdleFunc( idle );

    glutMainLoop();
    return 0;
}
