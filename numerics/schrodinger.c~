// Sto traducendo da java un codice che sta sul Pang.
// Chiaramente il codice è per un problema senza simmetrie 1D.
// L'autore scrive codice come un deficente, però sta qui e commetterò le stesse
// cose da deficiente per accorciare i tempi sinceramente.
// (Mi chiedo se l'autore del libro si sia turovato in una condizione simile a suo tempo).

/*
  Ora, il problema sula pang tiene conto di un problema 1D senza  simmetrice, in simmetria
   radilae abbiamo da risolvere:
   u''(r) + q(r)u(r) = 0
   con
   q(r) = 2m(E-V(r)) - l(l+1)/r^2
*/ 

#include "schrodinger.h"
#include "numerics.h"

// Allora, ripeto che così si fa nel Pang,
// le variabili globali in generale non credo che debbano più
// essere un taboo, sì che però per mia esperienza rendono il
// codice molto più illeggibile.
static double h = (X2-X1)/NX;
static int nr,nl;
static double ql[NX+1];
static double qr[NX+1];
static double s[NX+1];
static double u[NX+1];

double ul[NX+1];
double ur[NX+1];


static double v(double x)
{
  return -1.0/x;
}


/*
 * Integra numericamente un'equazione differenziale del tipo
 *
 *     u''(x) + q(x)u(x) = s(x)
 *
 * tramite il metodo di Numerov.
 *
 * Parametri:
 *
 *   m   : numero di punti della griglia da utilizzare;
 *
 *   h   : passo della griglia;
 *
 *   u0  : valore iniziale della soluzione, u(x_0);
 *
 *   u1  : valore della soluzione al punto successivo, u(x_0 + h);
 *
 *   q   : array contenente i valori q(x_i) sui punti della griglia;
 *
 *   s   : array contenente il termine sorgente s(x_i).
 *         Nel caso dell'equazione di Schrödinger omogenea,
 *         normalmente s(x) = 0;
 *
 *   u   : array in cui vengono salvati i valori della soluzione
 *         calcolati con Numerov. Deve avere spazio per almeno m elementi.
 */
static void numerov(int m,
		      double h,
		      double u0,
		      double u1,
		      double *q,
		      double *s,
		      double *u){
  u[0] = u0;
  u[1] = u1;
  double g = h*h/12.0;
  for(int i = 1 ; i < m-1; i++){
    double c0 = 1+g*q[i-1];
    double c1 = 2-10*g*q[i];
    double c2 = 1+g*q[i+1];
    double d = g*(s[i+1]+s[i-1]+10*s[i]);
    u[i + 1] = (c1*u[i]-c0*u[i-1]+d)/c2;
  }
}



/* Ritorna 0 se tutto ok, -1 se l'energia non è valida o non c'è turning point.
   In caso di errore ul, ur, nl, nr, u NON vengono aggiornati. */
int wave(double energy,double m, int l){
  double y[NX+1];

  /* controllo sull'energia spostato in cima: prima di usare sqrt(-2me) */
  if (!(energy < 0.0) || !isfinite(energy)) {
    fprintf(stderr,
            "Energia non valida per uno stato legato: %g\n",
            energy);
    return -1;
  }

  for(int i = 0; i <= NX; i++){
    double x = X1+i*h;
    ql[i] = 2.0*m*(energy - v(x)) - l*(l+1)/(x*x);
    qr[NX-i] = ql[i];
  }

  // TROVO IL PUNTO DI MATCHING
  int im = -1;
  for(int i = 0; i < NX; i++){
    if((ql[i]*ql[i+1] < 0) && (ql[i] > 0)){
      im = i;
    }
  }

  
  if (im < 1) {
    fprintf(stderr,
            "ERRORE: turning point non trovato: E=%g, im=%d\n",
            energy, im);
    return -1;
  }


  /* Qua dobbiamo fa attenzione:
     venendo da sinistra effeettamivazione per uno stato legato è r^(l+1)
     , venendo da destra invece è e^-kr con k = sqrt(-2me)
  */
  nl = im+2;
  nr = NX - im +2;
  double ul1 = 1.0;
  double ul0 = pow(X1/(X1+h), l+1);
  double kappa = sqrt(-2.0*m*energy);

  double ur0 = 1.0;
  double ur1 = exp(kappa*h);

  numerov(nl, h, ul0, ul1, ql, s, ul);
  numerov(nr, h, ur0, ur1, qr, s, ur);

  // TROVO LA FUNZIONE DONDA SULLA SINISTRA
  double ratio = ur[nr-2]/ul[im];

  for(int i = 0; i <= im; i++){
    u[i] = ratio*ul[i];
    y[i] = u[i]*u[i];
  }

  // Trovo quella sulla destra
  for(int i = 0; i < (nr-1); i++){
    u[i+im] = ur[nr-i-2];
    y[i+im] = u[i+im]*u[i+im];
  }

  // Normalizazzione
  double sum = simpson(y,NX+1,h);
  sum = sqrt(sum);
  for(int i = 0; i <= NX; i++){
    u[i] /= sum;
  }

  return 0;
}

static double f(double energy, double m, int l)
{
    if (wave(energy, m, l) != 0)
        return NAN;

    int im = nl - 2;
    int j  = nr - 2;

    if (fabs(ul[im]) < 1e-20 ||
        fabs(ur[j])  < 1e-20) {
        fprintf(stderr,
                "MATCHING: denominatore quasi nullo "
                "E=%g ul=%e ur=%e\n",
                energy, ul[im], ur[j]);
        return NAN;
    }

    double left =
        (ul[im+1] - ul[im-1])
        / (2.0*h*ul[im]);

    double right =
        (ur[j-1] - ur[j+1])
        / (2.0*h*ur[j]);

    double result = left-right;

    fprintf(stderr,
            "E=% .8f im=%d left=% .8e right=% .8e F=% .8e\n",
            energy, im, left, right, result);

    return result;
}

double find_root(double Ea,
                        double Eb,
                        double del,
                        double m,
                        int l){
  int nscan = 200;
  if (!(Eb > Ea)) return NAN;

  double dE = (Eb - Ea) / nscan;
  double Elo = NAN, Ehi = NAN;

  double fa = f(Ea, m, l);
  for(int k = 1; k <= nscan; k++){
    double E  = Ea + k*dE;
    double fb = f(E, m, l);
    if (isfinite(fa) && isfinite(fb) && fa > 0 && fb < 0) {
      Elo = E - dE;
      Ehi = E;
      break;
    }
    fa = fb;
  }
  if (isnan(Elo)) {
    printf("Nessun cambio di segno trovato in [%g, %g] per l=%d\n", Ea, Eb, l);
    return NAN;
  }

  while(Ehi - Elo > del){
    double Em = 0.5*(Elo + Ehi);
    double fm = f(Em, m, l);
    if (!isfinite(fm)) return NAN;
    if (fm > 0) Elo = Em; else Ehi = Em;
  }

  return 0.5*(Elo + Ehi);
}


const double *get_u(void){
  return u;
}


/*
  CODICE GENERATO DA CHATGPT per testare le funzioni
  dovrebbe mandare in output le prime 4 autofunzioni del atomo di idrogeno
  e poi le puoi disegna con gnuplot
*/

/* #include <stdio.h> */
/* #include <math.h> */

/* #define LMAX 3   /\* calcolo l = 0,1,2,3 *\/ */

/* int main(void) */
/* { */
/*     double del  = 1e-6; */
/*     double mass = 1.0; */

/*     FILE *gp = fopen("plot_radial.gp", "w"); */
/*     if (gp == NULL) { */
/*         fprintf(stderr, "Errore: non riesco ad aprire plot_radial.gp\n"); */
/*         return 1; */
/*     } */

/*     fprintf(gp, "set grid\n"); */
/*     fprintf(gp, "set xlabel 'r'\n"); */
/*     fprintf(gp, "set ylabel 'u(r)'\n"); */
/*     fprintf(gp, "set title 'Autofunzioni radiali ridotte dell''idrogeno'\n"); */
/*     fprintf(gp, "plot \\\n"); */

/*     for (int l = 0; l <= LMAX; l++) { */

/*         /\* per l'idrogeno lo stato più basso con dato l ha n = l+1 *\/ */
/*         int n = l + 1; */

/* 	double e_guess = -1.0 / (2.0 * n * n); */

/* 	/\* intervallo di ricerca: */
/* 	   sotto Ea non c'è zona classicamente permessa (minimo di V_eff), */
/* 	   sopra Eb il turning point esterno (~1/|E|) esce dalla scatola *\/ */
/* 	double Ea = (l > 0) ? -0.999*mass/(2.0*l*(l+1)) : -1.0; */
/* 	double Eb = -1.0/(0.8*X2); */

/*         double e = find_root(Ea, Eb, del, mass, l); */

/*         if (!isfinite(e)) { */
/*             fprintf(stderr, */
/*                     "Errore: energia non finita per l=%d\n", l); */
/*             fclose(gp); */
/*             return 1; */
/*         } */

/*         fprintf(stderr, */
/*                 "l = %d   n = %d   E = %.8f   (guess %.8f)\n", */
/*                 l, n, e, e_guess); */

/*         wave(e, mass, l); */

/*         char filename[64]; */
/*         snprintf(filename, sizeof(filename), "radial_l%d.dat", l); */

/*         FILE *fp = fopen(filename, "w"); */
/*         if (fp == NULL) { */
/*             fprintf(stderr, "Errore: non riesco ad aprire %s\n", filename); */
/*             fclose(gp); */
/*             return 1; */
/*         } */

/*         fprintf(fp, "# l = %d\n", l); */
/*         fprintf(fp, "# n = %d\n", n); */
/*         fprintf(fp, "# E = %.8f\n", e); */
/*         fprintf(fp, "# r\tu(r)\tR(r)\tV(r)\n"); */

/*         for (int i = 0; i <= NX; i++) { */
/*             double r = X1 + i*h; */
/*             double R = u[i] / r;   /\* R(r) = u(r)/r *\/ */

/*             fprintf(fp, "%.8f\t%.8f\t%.8f\t%.8f\n", */
/*                     r, u[i], R, v(r)); */
/*         } */

/*         fclose(fp); */

/*         /\* aggiungo la curva al file gnuplot *\/ */
/*         fprintf(gp, */
/*                 "'radial_l%d.dat' using 1:2 with lines lw 2 title 'l=%d'", */
/*                 l, l); */

/*         if (l < LMAX) */
/*             fprintf(gp, ", \\\n"); */
/*         else */
/*             fprintf(gp, "\n"); */
/*     } */

/*     fclose(gp); */

/*     printf("Ho generato i file:\n"); */
/*     for (int l = 0; l <= LMAX; l++) { */
/*         printf("  radial_l%d.dat\n", l); */
/*     } */
/*     printf("e lo script gnuplot:\n"); */
/*     printf("  plot_radial.gp\n"); */
/*     printf("\nPer disegnare:\n"); */
/*     printf("  gnuplot -persist plot_radial.gp\n"); */

/*     return 0; */
/* } */

