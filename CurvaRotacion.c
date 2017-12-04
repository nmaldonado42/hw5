#include <stdio.h>
#include <math.h>
#define _XOPEN_SOURCE
#include <stdlib.h>

void MetHas(double r[], double v[], double p[]);

main()
{
	FILE * fc;
	fc = fopen("RadialVelocities.dat","r");

	double rad[300];
	double vel[300];
	double par[3];

	fscanf(fc, "%*[^\n]\n", NULL);

	int i = 0;
	while(fscanf(fc, "%lf %lf", &rad[i], &vel[i]) == 1)
	{
		fscanf(fc, "%lf %lf", &rad[i], &vel[i]);
		i++;
	}

	fclose(fc);

	MetHas(rad, vel, par);

	printf("%f %f %f", par[0], par[1], par[2]);
	
	return 0;
}

void MetHas(double r[], double v[], double p[])
{
	int N = 100000;
	double b = 900.0;
	double d = 900.0;
	double h = 900.0;

	double vn[300];
	int j;
	for(j = 0; j < 300; j++)
	{
		vn[j] = ((sqrt(b)*r[j])/(pow((pow(r[j],2.0) + pow(0.2497,2.0)),0.75))) + ((sqrt(d)*r[j])/(pow((pow(r[j],2.0) + pow(5.4705,2.0)),0.75))) + ((sqrt(h))/(pow((pow(r[j],2.0) + pow(64.3,2.0)),0.25)));
	}

	double chi1 = 0;
	int k;
	for(k = 0; k < 300; k++)
	{
		chi1 += pow((v[k] - vn[k]),2.0);
	}
	
	int i;
	for(i = 0; i < N; i++)
	{
		double bn = b + drand48();
		double dn = d + drand48();
		double hn = h + drand48();

		int l;
		for(l = 0; l < 300; l++)
		{
			vn[l] = ((sqrt(bn)*r[l])/(pow((pow(r[l],2.0) + pow(0.2497,2.0)),0.75))) + ((sqrt(dn)*r[l])/(pow((pow(r[l],2.0) + pow(5.4705,2.0)),0.75))) + ((sqrt(hn))/(pow((pow(r[l],2.0) + pow(64.3,2.0)),0.25)));
		}

		double chi2 = 0;
		int m;
		for(m = 0; m < 300; m++)
		{
			chi2 += pow((v[m] - vn[m]),2.0);
		}

		double rat = exp((-chi2 + chi1)/2);
		double rand = drand48();
		if(rand < rat)
		{
			b = bn;
			d = dn;
			h = hn;
			chi1 = chi2;
		}
	}

	p[0] = b;
	p[1] = d;
	p[2] = h;
}