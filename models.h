#include <stdlib.h>
#include <stdint.h>

typedef struct Coordinate
{
    uint64_t x;
    uint64_t y;
} Coordinate;

typedef struct CoordinateArray
{
    size_t size;
    Coordinate *coordinates;
} CoordinateArray;

typedef struct CoordinateList
{
    size_t size;
    CoordinateListNode *head;
} CoordinateList;

typedef struct CoordinateListNode
{
    Coordinate *coordinate;
    CoordinateListNode *next;
} CoordinateListNode;

Coordinate *new_coordinate(uint64_t x, uint64_t y);