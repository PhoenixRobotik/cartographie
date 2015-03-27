// Convertir les milliradians en degrés pour l'affichage
#define MRAD2DEGRES 0.0572957795131
// Dimensions
// Le facteur de zoom (mm par pixel)
#define ZOOM_FACTOR 5

#define HEIGHT 2000
#define WIDTH 3000

#define POINT_SIZE 40

void dessine_fond();

void set_position(int x, int y, int alpha);
void add_passage_point(int x, int y, int type);
int sdl_manage_events();
int init_sdl_screen();
int quit_sdl_screen();

