#include <stdint.h>

typedef struct Board
{
    size_t height;
    size_t width;
    uint64_t *cells;
    Coordinate *blank;
} Board;

uint64_t manhattan_distance(const Board *board);

CoordinateList *board_actions(const Board *b);

const Board *resulting_board(const Board *b, const Coordinate *action);

uint64_t *cell_at(const Board *b, uint64_t i, uint64_t j);

uint64_t hash_board(const Board *b);