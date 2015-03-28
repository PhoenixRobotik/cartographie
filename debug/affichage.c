#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "affichage.h"

#define AFFICHAGE_DEBUG 0

SDL_Event evenements;
GLuint texturePlateau;

SDL_Rect position_robot;

float plateau_width, plateau_height;

int souris_x, souris_y;

void dessine_fond() {
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glColor3ub(255,255,255);
        glTexCoord2d (0, 0); glVertex2d(0,              0);
        glTexCoord2d (0, 1); glVertex2d(0,              plateau_height);
        glTexCoord2d (1, 1); glVertex2d(plateau_width,  plateau_height);
        glTexCoord2d (1, 0); glVertex2d(plateau_width,  0);
    glEnd();
    SDL_GL_SwapBuffers(); // Mise à jour de l'écran
}
void add_trait(int x1, int y1,int x2, int y2) {
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    glColor3ub(255,0,0);

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();

    glFlush();
    SDL_GL_SwapBuffers(); // Mise à jour de l'écran

}
void add_circle(float cx, float cy, float r, int num_segments)
{
    num_segments = 100;
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    float theta = 2 * 3.1415926 / (float)(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = r;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    int ii;
    for( ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();

    glFlush();
    SDL_GL_SwapBuffers(); // Mise à jour de l'écran
}
void add_passage_point(int x, int y, int type) {
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glTranslated(x, y, 0);

    switch (type) {
        case 0:
            glColor3ub(128,128,128);
            break;
        case 1:
            glColor3ub(0,255,0);
            break;
        case 2:
            glColor3ub(255,0,0);
            break;
        default:
            glColor3ub(0,0,0);
    }


    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glVertex2d(-POINT_SIZE/2, -POINT_SIZE/2);
        glVertex2d(-POINT_SIZE/2, +POINT_SIZE/2);
        glVertex2d(+POINT_SIZE/2, +POINT_SIZE/2);
        glVertex2d(+POINT_SIZE/2, -POINT_SIZE/2);
    glEnd();

    glFlush();
    SDL_GL_SwapBuffers(); // Mise à jour de l'écran
}


int sdl_manage_events() {
    SDL_PollEvent(&evenements);
    switch(evenements.type) {
        case SDL_QUIT:
            return 1;
        case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEMOTION: // Clic de la souris
                return 0;
            break;
        default:
            return 0;
    }

    return 0;
}

int init_sdl_screen() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return quit_sdl_screen(1);

    SDL_WM_SetCaption("SDL : Une p'tite gestion de l'asservissement", NULL);

    if (SDL_SetVideoMode(WIDTH/ZOOM_FACTOR+1, HEIGHT/ZOOM_FACTOR+1, 32, SDL_OPENGL) == 0)
        return quit_sdl_screen(1);

    // Changer de repère : repère orthogonal avec origine bas-gauche
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0,WIDTH,0,HEIGHT);

    // Texture : plateau de jeu
    texturePlateau = SOIL_load_OGL_texture("debug/plateau.png",
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (AFFICHAGE_DEBUG == 1 || texturePlateau == 0)
        printf("SOIL messages : '%s' (plateau.png)\n", SOIL_last_result());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, texturePlateau);

    // Calcul des dimensions
    plateau_width = WIDTH ;
    plateau_height= HEIGHT;

    return 0;
}

int quit_sdl_screen(int erreur) {
    if (erreur != 0)
        printf("Erreur lors de la creation de la fenetre : ,%s",SDL_GetError());

    SDL_Quit();
    return -1;
}
