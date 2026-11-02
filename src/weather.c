#include "weather.h"

#include <stdlib.h>

#define SUN CLITERAL(Color){255, 230, 64, 255};      // YELLOW
#define CLOUDS CLITERAL(Color){219, 219, 219, 255};  // GREY
#define RAIN CLITERAL(Color){83, 157, 252, 255};     // BLUE
#define STORM CLITERAL(Color){252, 83, 176, 255};    // RED
#define SNOW CLITERAL(Color){255, 255, 255, 255};    // WHITE

Weather_t *init_weather()
{
    Weather_t *weather = (Weather_t *)malloc(sizeof(Weather_t));
    if (!weather) return NULL;

    weather->current_weather = SUN;
    weather->expected_weather = RAIN;
    weather->time_passed = 0;

    return weather;
}

void weather_update(Weather_t *weather)
{
    weather->time_passed++;

    if (weather->time_passed % 200 == 0) {
        weather->current_weather = weather->expected_weather;
        int rnd_weather = GetRandomValue(1, 5);

        switch (rnd_weather) {
            case 1:
                weather->expected_weather = SUN;
                break;
            case 2:
                weather->expected_weather = CLOUDS;
                break;
            case 3:
                weather->expected_weather = RAIN;
                break;
            case 4:
                weather->expected_weather = STORM;
                break;
            case 5:
                weather->expected_weather = SNOW;
                break;
        }
    }
}

void weather_render(Weather_t *weather)
{
    DrawRectangle(400, 100, 20, 20, weather->current_weather);
    DrawRectangle(430, 100, 20, 20, weather->expected_weather);
}

void weather_destroy(Weather_t *weather) { free(weather); }
