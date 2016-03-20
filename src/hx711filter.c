#include "hx711filter.h"

static long filter_taps[HX711FILTER_TAP_NUM] = {
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM,
  16777216 / HX711FILTER_TAP_NUM
};

void HX711Filter_init(HX711Filter* f) {
  int i;
  for(i = 0; i < HX711FILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void HX711Filter_put(HX711Filter* f, long input) {
  f->history[f->last_index++] = input;
  if(f->last_index == HX711FILTER_TAP_NUM)
    f->last_index = 0;
}

long HX711Filter_get(HX711Filter* f) {
  long long acc = 0;
  int index = f->last_index, i;
  for(i = 0; i < HX711FILTER_TAP_NUM; ++i) {
    index = index != 0 ? index-1 : HX711FILTER_TAP_NUM-1;
    acc += (long long)f->history[index] * filter_taps[i];
  };
  return acc >> 24;
}

