#ifndef SCHRODINGER
#define SCHRODINGER

#define NX 20000
#define M 10
#define NI 10
#define X1 1e-4
#define X2 50.0

#include <math.h>
#include <stdlib.h>

int wave(double energy,
	 double m,
	 int l);



const double *get_u(void);


/*
 * Cerca lo zero di f(E) in [Ea,Eb]: scan a passi uguali per trovare il primo
 * passaggio da + a - (i poli di f vanno da - a +, quindi non vengono scambiati
 * per zeri), poi bisezione fino a precisione del.
 * Ritorna NAN se non trova nulla.
 */
double find_root(double Ea,
		 double Eb,
		 double del,
		 double m,
		 int l);

#endif
