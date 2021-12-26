#include <stdlib.h>
#include <models.h>
#include <board.h>
#include <action_node.h>

ActionNode *new_action_node(const Board *board, const uint64_t depth, const Coordinate *action, const ActionNode *parent)
{
    ActionNode *node = malloc(sizeof(ActionNode));
    node->board = board;
    node->depth = depth;
    node->action = action;
    node->parent = parent;
    node->cost = depth + manhattan_distance(board);

    return node;
}

Coordinate *inverse_action(const Coordinate *action)
{
    Coordinate *inverse = malloc(sizeof(Coordinate));
    inverse->x = -action->x;
    inverse->y = -action->y;
    return inverse;
}

ActionNodeList *action_node_neighbours(const ActionNode *node)
{
    ActionNodeList *neighbours = malloc(sizeof(ActionNodeList));
    const CoordinateList *actions = board_actions(node->board);

    CoordinateListNode *current_action = actions->head;
    ActionNodeListNode *current_neighbour = neighbours->head;

    while (current_action != NULL)
    {
        if (current_action->coordinate != NULL)
        {
            Coordinate *inverse = inverse_action(current_action->coordinate);
            if (current_action->coordinate->x == inverse->x && current_action->coordinate->y == inverse->y)
            {
                free(inverse);
                continue;
            }
            else
                free(inverse);
        }

        const Board *new_board = resulting_board(node->board, current_action->coordinate);
        const ActionNode *neighbour = new_action_node(new_board, node->depth + 1, current_action->coordinate, node);
        current_neighbour->node = neighbour;
        current_neighbour->next = malloc(sizeof(ActionNodeListNode));
        current_neighbour = current_neighbour->next;

        current_action = current_action->next;
    }

    free(actions);

    return neighbours;
}

CoordinateList *action_path(const ActionNode *node)
{
    CoordinateList *path = malloc(sizeof(CoordinateList));
    path->size = 0;

    CoordinateListNode *cursor = path->head;

    while (node != NULL)
    {
        // prepend to the list, because we're going backwards in the action node graph
        cursor->coordinate = node->action;

        CoordinateListNode *new_head = malloc(sizeof(CoordinateListNode));
        new_head->next = cursor;
        cursor = new_head;

        path->size++;
        node = node->parent;
    }

    return path;
}

uint64_t hash_action_node(const ActionNode *node)
{
    return hash_board(node->board);
}