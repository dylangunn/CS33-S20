//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Dylan Gunn
 * UCLA ID : 805112866
 * Email : dylankgunn@gmail.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u, v, w;
  int ton = 0;
  long compute_it, moving_average;
  double pi, pi2, x , y, sum, step = 0.0;
  long dot_product=0;
  long nCirc=0;
  long aggregate=1.0;
  double r=1.0;
  int was_smart = 16;
  int DIMm = DIM-1;

  long temp1,temp2;
  for(i=0; i<DIMm;i++)
  {
    temp1 = simple[i];
    super[i] += temp1;
  }

  moving_average = 0;
  for(i=0; i<DIMm;i++)
  {
    dot_product += super[i]*simple[i];
  }

  int a_secret = 5;
  fibonacci[0] = 1;
  fibonacci[1] = 1;
  fibonacci[2] = 2;
  fibonacci[3] = 3;
  i = 3;
  printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));
  int last_val = 3;
  int last_last = 2;
  int DIMf=DIM-10;
  int pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
  
  for(i=4; i<DIMf;i+=10)
  {
    pos0 = last_val + last_last;
    pos1 = pos0 + last_val;
    pos2 = pos1 + pos0;
    pos3 = pos2 + pos1;
    pos4 = pos3 + pos2;
    pos5 = pos4 + pos3;
    pos6 = pos5 + pos4;
    pos7 = pos6 + pos5;
    pos8 = pos7 + pos6;
    pos9 = pos8 + pos7;

    fibonacci[i] = pos0;
    fibonacci[i+1] = pos1;
    fibonacci[i+2] = pos2;
    fibonacci[i+3] = pos3;
    fibonacci[i+4] = pos4;
    fibonacci[i+5] = pos5;
    fibonacci[i+6] = pos6;
    fibonacci[i+7] = pos7;
    fibonacci[i+8] = last_last = pos8;
    fibonacci[i+9] = last_val = pos9;
  }
  while(i<DIMm)
  {
      fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
      i++;
  }
  
  double hstep;
  step = 1.0 / NUM_STEPS;
  hstep = 0.5*step;
  for (i=0;i<NUM_STEPS; i++)
  {
    x = hstep + i*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 
  
  for(i=0;i<NUM_TRIALS; i++)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    if (( x*x + y*y) <= 1) { //SAME r? was r*r
      nCirc++;
    }
  } 
  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 

  int DIMsq = DIM*DIM;
  int iDIMsq, jDIM, iDIMsqjDIM, iDIMsqjDIMk, iuDIMsq, jvDIM;
  long we_need = we_need_the_func();
  long gimmie = gimmie_the_func();

  //GOOD
#pragma omp parallel for private(j,k,iDIMsq,iDIMsqjDIM,compute_it) reduction(+:aggregate)
  for (i=1; i<DIMm; i++) {
      iDIMsq = i*DIMsq;
    for (j=1; j<DIMm; j++) {
        iDIMsqjDIM = iDIMsq+j*DIM;
      for (k=1; k<DIMm; k++) {
        compute_it = old[iDIMsqjDIM+k] * we_need;
        aggregate += compute_it / gimmie;
      }
    }
  }

  printf("AGGR:%ld\n",aggregate);

  // GOOD
  int iDIMsqn,iDIMsqp,jDIMn,jDIMp,kn,kp;
  long templ;
#pragma omp parallel for private(j,k,iDIMsq,jDIM,iDIMsqjDIM,iDIMsqjDIMk,iDIMsqn,iDIMsqp,jDIMn,jDIMp,kn,kp,templ)
  for (i=1; i<DIMm; i++) {
      iDIMsq = i*DIMsq;
      iDIMsqn = iDIMsq-DIMsq;
      iDIMsqp = iDIMsq+DIMsq;
    for (j=1; j<DIMm; j++) {
        jDIM = j*DIM;
        jDIMn = jDIM-DIM;
        jDIMp = jDIM+DIM;
        iDIMsqjDIM = iDIMsq+j*DIM;
      for (k=1; k<DIMm; k++) {
          iDIMsqjDIMk = iDIMsqjDIM+k;
          kn=k-1;
          kp=k+1;
          templ=0;
          templ+=old[iDIMsqn+jDIMn+kn];
          templ+=old[iDIMsqn+jDIMn+k];
          templ+=old[iDIMsqn+jDIMn+kp];
          templ+=old[iDIMsqn+jDIM+kn];
          templ+=old[iDIMsqn+jDIM+k];
          templ+=old[iDIMsqn+jDIM+kp];
          templ+=old[iDIMsqn+jDIMp+kn];
          templ+=old[iDIMsqn+jDIMp+k];
          templ+=old[iDIMsqn+jDIMp+kp];
          templ+=old[iDIMsq+jDIMn+kn];
          templ+=old[iDIMsq+jDIMn+k];
          templ+=old[iDIMsq+jDIMn+kp];
          templ+=old[iDIMsq+jDIM+kn];
          templ+=old[iDIMsq+jDIM+k];
          templ+=old[iDIMsq+jDIM+kp];
          templ+=old[iDIMsq+jDIMp+kn];
          templ+=old[iDIMsq+jDIMp+k];
          templ+=old[iDIMsq+jDIMp+kp];
          templ+=old[iDIMsqp+jDIMn+kn];
          templ+=old[iDIMsqp+jDIMn+k];
          templ+=old[iDIMsqp+jDIMn+kp];
          templ+=old[iDIMsqp+jDIM+kn];
          templ+=old[iDIMsqp+jDIM+k];
          templ+=old[iDIMsqp+jDIM+kp];
          templ+=old[iDIMsqp+jDIMp+kn];
          templ+=old[iDIMsqp+jDIMp+k];
          templ+=old[iDIMsqp+jDIMp+kp];
          templ/=27;
          new[iDIMsqjDIMk] = templ;
      }
    }
  }
  int DIM5=DIM-5;
  for (i=1; i<DIMm; i++) {
      iDIMsq = i*DIMsq;
    for (j=1; j<DIMm; j++) {
        iDIMsqjDIM = iDIMsq+j*DIM;
      for (k=1; k<DIM5; k+=5) {
        iDIMsqjDIMk = iDIMsqjDIM+k;
        u=(new[iDIMsqjDIMk]);
        if (u<=99) u=0;
        else if (u>=900) u=9;
        else u /= 100;
        histogrammy[u]++;
        u=(new[iDIMsqjDIMk+1]);
        if (u<=99) u=0;
        else if (u>=900) u=9;
        else u /= 100;
        histogrammy[u]++;
        u=(new[iDIMsqjDIMk+2]);
        if (u<=99) u=0;
        else if (u>=900) u=9;
        else u /= 100;
        histogrammy[u]++;
        u=(new[iDIMsqjDIMk+3]);
        if (u<=99) u=0;
        else if (u>=900) u=9;
        else u /= 100;
        histogrammy[u]++;
        u=(new[iDIMsqjDIMk+4]);
        if (u<=99) u=0;
        else if (u>=900) u=9;
        else u /= 100;
        histogrammy[u]++;
      }
      while(k<DIMm)
      {
        u=(new[iDIMsqjDIM+k]);
        if (u<=99) u=0;
        else if (u>=900) u=9;
        else u /= 100;
        histogrammy[u]++;
        k++;
      }
    }
  }
  return (double) (dot_product+moving_average+pi+pi2);
}
