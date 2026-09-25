#include <stdio.h>
#include <stdlib.h>

#include "numerics.h"

int main(void)
{
    float u1 = 1.0f;
    float u2 = 0.0f;

    int n = 1000;
    int ni = 100;

    float del = 1e-6f;

    int l = 0;
    float E = 0.5f;

    float r0 = 0.001f;
    float h = (1.0f - r0) / n;

    KuttaV *Y = shooting(u1,
                         u2,
                         n,
                         del,
                         ni,
                         l,
                         E);

    if(Y == NULL){
        fprintf(stderr, "Errore nello shooting\n");
        return 1;
    }

    for(int i = 0; i <= n; i++){
        float r = r0 + h*i;

        printf("%f %f %f\n",
               r,
               Y[i].v0,
               Y[i].v1);
    }

    fprintf(stderr,
            "u(r0) = %f\nu(1) = %f\n",
            Y[0].v0,
            Y[n].v0);

    free(Y);

    return 0;
}
