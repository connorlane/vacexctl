#ifndef VOLTAGEFILTER_H_
#define VOLTAGEFILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 250 Hz

*/

#define VOLTAGEFILTER_TAP_NUM 39

typedef struct {
  int history[VOLTAGEFILTER_TAP_NUM];
  unsigned int last_index;
} VoltageFilter;

void VoltageFilter_Init(VoltageFilter* f);
void VoltageFilter_Put(VoltageFilter* f, int input);
int VoltageFilter_Get(VoltageFilter* f);

#endif

