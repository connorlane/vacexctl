#include "voltagefilter.h"
//DEBUG
#include <printf.h>

static int filter_taps[VOLTAGEFILTER_TAP_NUM] = {
  84,
  70,
  67,
  31,
  -48,
  -168,
  -316,
  -464,
  -571,
  -590,
  -476,
  -194,
  267,
  893,
  1639,
  2431,
  3184,
  3804,
  4213,
  4356,
  4213,
  3804,
  3184,
  2431,
  1639,
  893,
  267,
  -194,
  -476,
  -590,
  -571,
  -464,
  -316,
  -168,
  -48,
  31,
  67,
  70,
  84
};

void VoltageFilter_Init(VoltageFilter* f) {
  int i;
  for(i = 0; i < VOLTAGEFILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void VoltageFilter_Put(VoltageFilter* f, int input) {
  f->history[f->last_index++] = input;
  if(f->last_index == VOLTAGEFILTER_TAP_NUM)
    f->last_index = 0;
}

int VoltageFilter_Get(VoltageFilter* f) {
  long acc = 0;
  long product = 0;
  int index = f->last_index, i;
  for(i = 0; i < VOLTAGEFILTER_TAP_NUM; ++i) {
    index = index != 0 ? index-1 : VOLTAGEFILTER_TAP_NUM-1;
    product = (long)f->history[index] * filter_taps[i];
    acc = acc + product;
  };

  return acc >> 15;
}

