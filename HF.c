#include "graphics/graphics.h"
#include "numerics/schrodinger.h"

#include <math.h>
#include <complex.h>

static double h = (X2-X1)/NX;

static double radial(double r, const double *R)
{
  if (r < X1 || r > X2)
    return 0.0;

  double p = (r - X1)/h;
  int i = (int)p;

  if (i >= NX)
    return R[NX];

  double t = p - i;

  return (1.0-t)*R[i] + t*R[i+1];
}

static double psi_dz2(double x,
                      double y,
                      double z,
                      const double *R)
{
  double r = sqrt(x*x + y*y + z*z);

  if (r < X1)
    return 0.0;

  double angular =
    (2.0*z*z - x*x - y*y)/(r*r);

  return radial(r, R)*angular;
}

static double factorial(int n)
{
    return tgamma((double)n + 1.0);
}

// Allora ci sta una formula bruta per Ylm(x,y,z)
// Sinceramente mi sono fatto generare sta formula perchè
// non sono masuchista
double complex psi_lm(double x,
                      double y,
                      double z,
                      int l,
                      int m,
                      const double *R)
{
    double r = sqrt(x*x + y*y + z*z);

    if (r == 0.0)
        return 0.0 + 0.0*I;

    /* Gestisco prima m < 0 usando
       Y_l^{-m} = (-1)^m (Y_l^m)^*
    */
    if (m < 0) {
        int mp = -m;

        double complex yp = psi_lm(x, y, z, l, mp, R);

        if (mp % 2)
            return -conj(yp);

        return conj(yp);
    }

    if (m > l)
        return 0.0 + 0.0*I;

    /* Normalizzazione */
    double norm =
        sqrt(
            ((2.0*l + 1.0)/(4.0*M_PI)) *
            (factorial(l - m) / factorial(l + m))
        );

    double complex xy = x + I*y;

    double complex prefactor =
        pow(-1.0, m)
        * norm
        * cpow(xy, m)
        / pow(2.0, l);

    /* Somma */
    double complex sum = 0.0 + 0.0*I;

    int kmax = (l - m)/2;

    for (int k = 0; k <= kmax; k++) {

        double coeff =
            pow(-1.0, k)
            * factorial(2*l - 2*k)
            /
            (
                factorial(k)
                * factorial(l - k)
                * factorial(l - m - 2*k)
            );

        double spatial =
            pow(z, l - m - 2*k)
            /
            pow(r, l - 2*k);

        sum += coeff * spatial;
    }

    double complex Ylm = prefactor * sum;

    return radial(r, R) * Ylm;
}

int main(int argc, char **argv){

  int n = atoi(argv[1]);
  int l = atoi(argv[2]);
  int m = atoi(argv[3]);

  double En = -1.0/(2.0*n*n);
  double E = find_root(En - 0.01,En + 0.01,1e-8,1.0,l);
  wave(E,1.0,l);

  double *u = get_u();
  double R[NX+1];

  
  for (int i = 0; i <= NX; i++) {
    double r = X1 + i*h;
    R[i] = u[i] / r;
  }

  double L = 15.0;
  double step = 0.5;

  double iso = 0.005;
  double eps = 0.002;

  for (double x = -L; x <= L; x += step) {
    for (double y = -L; y <= L; y += step) {
      for (double z = -L; z <= L; z += step) {

	double complex pc = psi_lm(x, y, z,l,m,R);
	double p = creal(pc);

	if (fabs(fabs(p) - iso) < eps) {

	  if (p > 0.0) {
	    add_sphere(x, y, z,
		       1.0, 0.2, 0.2);
	  }
	  else {
	    add_sphere(x, y, z,
		       0.2, 0.2, 1.0);
	  }
	}
      }
    }
  }

  start_opengl(argc,argv);
}
