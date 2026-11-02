#ifndef WEATHER_H
#define WEATHER_H

#include "shared.h"

typedef struct Weather {
    Color current_weather;
    Color expected_weather;
    unsigned int time_passed;
} Weather_t;

Weather_t *init_weather();
void weather_update(Weather_t *weather);
void weather_render(Weather_t *weather);
void weather_destroy(Weather_t *weather);

#endif /* WEATHER_H */
