#include <stdlib.h>
#include <models.h>

Coordinate *new_coordinate(uint8_t x, uint8_t y)
{
    Coordinate *c = malloc(sizeof(Coordinate));
    c->x = x;
    c->y = y;
    return c;
}