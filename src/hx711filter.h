#ifndef HX711FILTER_H_
#define HX711FILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

*/

#define HX711FILTER_TAP_NUM 10

typedef struct {
  long history[HX711FILTER_TAP_NUM];
  unsigned int last_index;
} HX711Filter;

void HX711Filter_init(HX711Filter* f);
void HX711Filter_put(HX711Filter* f, long input);
long HX711Filter_get(HX711Filter* f);

#endif

