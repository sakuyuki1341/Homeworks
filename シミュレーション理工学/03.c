#include <stdio.h>
#include <math.h>

#define _USE_MATH_DEFINES

void initial(double *t, double pos[2], double vel[2], double *GM,
double *dt, double *tmax) {
	pos[0] = 1;
	pos[1] = 0;
	vel[0] = 0;
	vel[1] = 2*M_PI;
	*t = 0.0;
	*GM = 4.0*M_PI*M_PI;
	scanf("%lf", dt);
	*tmax = 10;
	return;
}

void euler(double pos[2], double vel[2], double *t, double GM, double dt) {
	double accel[2], r2, r3, posm[2], velm[2], accelm[2], r2m, r3m;

	r2 = pos[0]*pos[0] + pos[1]*pos[1];
	r3 = pow(r2, 1.5);

	accel[0] = -GM * pos[0] / r3;
	accel[1] = -GM * pos[1] / r3;
	velm[0] = vel[0] + accel[0]*dt / 2;
	velm[1] = vel[1] + accel[1]*dt / 2;
	posm[0] = pos[0] + vel[0]*dt / 2;
	posm[1] = pos[1] + vel[1]*dt / 2;

	r2m = posm[0]*posm[0] + posm[1]*posm[1];
	r3m = pow(r2m, 1.5);
	accelm[0] = -GM * posm[0] / r3m;
	accelm[1] = -GM * posm[1] / r3m;
	vel[0] = vel[0] + accelm[0] * dt;
	vel[1] = vel[1] + accelm[1] * dt;
	pos[0] = pos[0] + velm[0] * dt;
	pos[1] = pos[1] + velm[1] * dt;

	*t += dt;
	return;
}

void main() {
	double t, pos[2], vel[2], GM, dt, tmax, r;

	initial(&t, pos, vel, &GM, &dt, &tmax);

	FILE *fp;
	fp = fopen("result.plt", "w");

	r = sqrt(pos[0]*pos[0] + pos[1]*pos[1]);
	fprintf(fp, "%6.3f %6.3f %6.3f %6.3f %6.3f\n", pos[0], pos[1], t, r, (vel[0]*vel[0] + vel[1]*vel[1])/2 - GM / r);
	while (t <= tmax) {
		euler(pos, vel, &t, GM, dt);
		r = sqrt(pos[0]*pos[0] + pos[1]*pos[1]);
		fprintf(fp, "%6.3f %6.3f %6.3f %6.3f %6.3f\n", pos[0], pos[1], t, r, (vel[0]*vel[0] + vel[1]*vel[1])/2 - GM / r);
	}
}