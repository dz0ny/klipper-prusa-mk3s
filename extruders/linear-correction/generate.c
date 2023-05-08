// Code based on prusa mk3s+ firmware
// https://github.com/prusa3d/Prusa-Firmware/blob/8d1abf772dd930c3cfa8e5021d18c4d414359b04/Firmware/tmc2130.cpp#L838
// File shared under GPL-3.0 license.

#include <stdio.h>
#include "constants.h"
#include <math.h>


void generate(unsigned int amp, unsigned int fac1000) {
  FILE * fptr;

  char path[28];
  snprintf(path, 28, "./linear-correction-%d.cfg", fac1000);
  printf("%s\n", path);

  fptr = fopen(path, "w");

  if (fptr == NULL) {
    printf("unable to write file!");
    return;
  }

  // TMC2130 wave compression algorithm
  // optimized for minimal memory requirements
  // printf_P(PSTR("tmc2130_set_wave %d %d\n"), axis, fac1000);
  if (fac1000 < TMC2130_WAVE_FAC1000_MIN) fac1000 = 0;
  if (fac1000 > TMC2130_WAVE_FAC1000_MAX) fac1000 = TMC2130_WAVE_FAC1000_MAX;
  float fac = 0;
  if (fac1000) fac = ((float)((long unsigned int) fac1000 + 1000) / 1000); //correction factor
  //	printf_P(PSTR(" factor: %s\n"), ftostr43(fac));
  unsigned int vA = 0; //value of currentA
  unsigned int va = 0; //previous vA
  int d0 = 0; //delta0
  int d1 = 1; //delta1
  unsigned int w[4] = {
    1,
    1,
    1,
    1
  }; //W bits (MSLUTSEL)
  unsigned int x[3] = {
    255,
    255,
    255
  }; //X segment bounds (MSLUTSEL)
  unsigned int s = 0; //current segment
  int b; //encoded bit value
  int dA; //delta value
  unsigned int i = 0; //microstep index
  unsigned long int reg = 0; //tmc2130 register
  // tmc2130_wr_MSLUTSTART(axis, 0, amp);
  fprintf(fptr, "[tmc2130 extruder]\n");
  fprintf(fptr, "driver_START_SIN: %d \n", 0);
  fprintf(fptr, "driver_START_SIN90: %d\n", amp);

  do {
    if ((i & 0x1f) == 0)
      reg = 0;
    // calculate value
    if (fac == 0) // default TMC wave
      vA = (unsigned int)((amp + 1) * sin((2 * M_PI * i + M_PI) / 1024) + 0.5) - 1;
    else // corrected wave
      vA = (unsigned int)(amp * pow(sin(2 * M_PI * i / 1024), fac) + 0.5);
    dA = vA - va; // calculate delta
    va = vA;
    b = -1;
    if (dA == d0) b = 0; //delta == delta0 => bit=0
    else if (dA == d1) b = 1; //delta == delta1 => bit=1
    else {
      if (dA < d0) // delta < delta0 => switch wbit down
      {
        //printf("dn\n");
        b = 0;
        switch (dA) {
        case -1:
          d0 = -1;
          d1 = 0;
          w[s + 1] = 0;
          break;
        case 0:
          d0 = 0;
          d1 = 1;
          w[s + 1] = 1;
          break;
        case 1:
          d0 = 1;
          d1 = 2;
          w[s + 1] = 2;
          break;
        default:
          b = -1;
          break;
        }
        if (b >= 0) {
          x[s] = i;
          s++;
        }
      } else if (dA > d1) // delta > delta0 => switch wbit up
      {
        //printf("up\n");
        b = 1;
        switch (dA) {
        case 1:
          d0 = 0;
          d1 = 1;
          w[s + 1] = 1;
          break;
        case 2:
          d0 = 1;
          d1 = 2;
          w[s + 1] = 2;
          break;
        case 3:
          d0 = 2;
          d1 = 3;
          w[s + 1] = 3;
          break;
        default:
          b = -1;
          break;
        }
        if (b >= 0) {
          x[s] = i;
          s++;
        }
      }
    }
    if (b < 0) break; // delta out of range (<-1 or >3)
    if (s > 3) break; // segment out of range (> 3)
    //printf("%d\n", vA);
    if (b == 1) reg |= 0x80000000;
    if ((i & 31) == 31)
      // tmc2130_wr_MSLUT(axis, (unsigned int)(i >> 5), reg);
      fprintf(fptr, "driver_MSLUT%d: %ld \n", (unsigned int)(i >> 5), reg);
    else
      reg >>= 1;
    // 		printf("%3d\t%3d\t%2d\t%2d\t%2d\t%2d    %08x\n", i, vA, dA, b, w[s], s, reg);
  } while (i++ != 255);
  // 	tmc2130_wr_MSLUTSEL(axis, x[0], x[1], x[2], w[0], w[1], w[2], w[3]);
  fprintf(fptr, "driver_X1: %3d\n", x[0]);
  fprintf(fptr, "driver_X2: %3d\n", x[1]);
  fprintf(fptr, "driver_X3: %3d\n", x[2]);
  fprintf(fptr, "driver_W0: %3d\n", w[0]);
  fprintf(fptr, "driver_W1: %3d\n", w[1]);
  fprintf(fptr, "driver_W2: %3d\n", w[2]);
  fprintf(fptr, "driver_W3: %3d\n", w[3]);
  //printf("tmc2130_wr_MSLUTSEL %3d\t%3d\t%2d\t%2d\t%2d\t%2d    %08x\n", x[0], x[1], x[2], w[0], w[1], w[2], w[3]);
  fclose(fptr);
}

int main() {
  // int_t axis, int_t amp, int_t fac1000
  int amp = 247;
  generate(amp, 0);
  for (int i = TMC2130_WAVE_FAC1000_MIN; i <= TMC2130_WAVE_FAC1000_MAX; i += TMC2130_WAVE_FAC1000_STEP) {
    printf("step: %d\n", i);
    generate(amp, i);
  }

  return 0;
}