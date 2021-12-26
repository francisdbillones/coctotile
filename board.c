#include <stdlib.h>
#include <string.h>
#include <models.h>
#include <board.h>

const int8_t MOVES[4][2] = {
    {-1, 0},
    {0, -1},
    {0, 1},
    {1, 0},
};

const int8_t MOVE_COUNT = 4;

Board *new_board(uint8_t width, uint8_t height)
{
    Board *board = malloc(sizeof(Board));
    board->width = width;
    board->height = height;
    board->cells = malloc(sizeof(uint64_t) * width * height);
    memset(board->cells, 0, sizeof(uint64_t) * width * height);
    return board;
}

size_t manhattan_distance(const Board *board)
{
    size_t manhattan_distance = 0;
    for (size_t i = 0; i < (board->height * board->width); ++i)
    {
        manhattan_distance += manhattan_distance_at(board, i);
    }
    return manhattan_distance;
}

uint64_t manhattan_distance_at(const Board *b, const uint64_t i)
{
    uint64_t i_cor, j_cor;
    uint64_t goal_i_cor, goal_j_cor;

    i_cor = i / b->width;
    j_cor = i % b->width;

    if (b->cells[i] == 0)
    {
        goal_i_cor = b->height - 1;
        goal_j_cor = b->width - 1;
    }
    else
    {
        goal_i_cor = (b->cells[i] - 1) / b->width;
        goal_j_cor = (b->cells[i] - 1) % b->width;
    }

    return abs(goal_i_cor - i_cor) + abs(goal_j_cor - j_cor);
}

CoordinateList *board_actions(const Board *b)
{
    CoordinateList *actions = malloc(sizeof(CoordinateList));
    actions->size = 0;

    CoordinateListNode *cursor = actions->head;

    for (size_t i = 0; i < MOVE_COUNT; ++i)
    {
        const int move[2] = MOVES[i];
        if (is_valid_move(b, move))
        {
            cursor->coordinate->x = move[0];
            cursor->coordinate->y = move[1];
            cursor->next = malloc(sizeof(CoordinateListNode));
            cursor = cursor->next;
        }
    }

    return actions;
}

const Board *resulting_board(const Board *b, const Coordinate *action)
{
    Board *result = copy_board(b);

    Coordinate new_blank = {
        .x = b->blank->x + action->x,
        .y = b->blank->y + action->y,
    };

    swap_cells(result, b->blank, &new_blank);

    *result->blank = new_blank;

    return result;
}

void swap_cells(Board *b, const Coordinate *old, const Coordinate *new)
{
    uint64_t temp = *cell_at(b, old->x, old->y);
    *cell_at(b, old->x, old->y) = *cell_at(b, new->x, new->y);
    *cell_at(b, new->x, new->y) = temp;
}

Board *copy_board(const Board *b)
{
    Board *copied_board = new_board(b->width, b->height);
    memcpy(copied_board->cells, b->cells, sizeof(uint64_t) * b->width * b->height);
    copied_board->blank = new_coordinate(b->blank->x, b->blank->y);
    return copied_board;
}

uint64_t *cell_at(const Board *b, uint64_t i, uint64_t j)
{
    return &(b->cells[i * b->width + j]);
}