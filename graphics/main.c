#include "graphics.h"

int main(int argc , char **argv){
  /* Nucleo */
add_sphere( 0.0,  0.0,  0.0, 1.0, 0.2, 0.2);
add_sphere( 1.5,  0.5,  0.0, 1.0, 0.6, 0.0);
add_sphere(-1.5, -0.5,  0.5, 1.0, 0.0, 0.8);
add_sphere( 0.0,  1.5, -0.5, 0.2, 0.8, 1.0);
add_sphere( 0.0, -1.5,  0.5, 1.0, 1.0, 0.0);

/* Orbita 1 - piano XZ */
add_sphere( 8.0,  0.0,  0.0, 1.0, 0.0, 0.0);
add_sphere( 6.0,  0.0,  5.0, 1.0, 0.3, 0.0);
add_sphere( 2.0,  0.0,  8.0, 1.0, 0.7, 0.0);
add_sphere(-3.0,  0.0,  7.5, 0.8, 1.0, 0.0);
add_sphere(-7.0,  0.0,  4.0, 0.0, 1.0, 0.4);
add_sphere(-8.0,  0.0, -1.0, 0.0, 1.0, 1.0);
add_sphere(-5.0,  0.0, -6.0, 0.0, 0.4, 1.0);
add_sphere( 0.0,  0.0, -8.0, 0.4, 0.0, 1.0);
add_sphere( 5.0,  0.0, -6.0, 1.0, 0.0, 0.7);

/* Orbita 2 - inclinata */
add_sphere( 0.0,  8.0,  0.0, 1.0, 0.0, 1.0);
add_sphere( 4.0,  6.0,  3.0, 0.7, 0.0, 1.0);
add_sphere( 7.0,  2.0,  4.0, 0.2, 0.0, 1.0);
add_sphere( 6.0, -3.0,  5.0, 0.0, 0.5, 1.0);
add_sphere( 2.0, -7.0,  3.0, 0.0, 1.0, 1.0);
add_sphere(-3.0, -7.0, -2.0, 0.0, 1.0, 0.3);
add_sphere(-7.0, -3.0, -4.0, 0.5, 1.0, 0.0);
add_sphere(-6.0,  3.0, -5.0, 1.0, 0.5, 0.0);
add_sphere(-2.0,  7.0, -3.0, 1.0, 0.0, 0.0);

/* Orbita 3 - inclinazione opposta */
add_sphere( 0.0,  7.0,  4.0, 1.0, 0.2, 0.6);
add_sphere( 5.0,  4.0,  5.0, 1.0, 0.0, 0.8);
add_sphere( 8.0,  0.0,  2.0, 0.3, 0.0, 1.0);
add_sphere( 6.0, -5.0, -2.0, 0.0, 0.5, 1.0);
add_sphere( 1.0, -8.0, -3.0, 0.0, 1.0, 0.8);
add_sphere(-4.0, -6.0,  0.0, 0.0, 1.0, 0.2);
add_sphere(-7.0, -2.0,  4.0, 0.7, 1.0, 0.0);
add_sphere(-6.0,  4.0,  5.0, 1.0, 0.4, 0.0);
add_sphere(-2.0,  7.0,  3.0, 1.0, 0.0, 0.3);
  start_opengl(argc,
	       argv);
}
