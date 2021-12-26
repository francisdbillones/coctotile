#include <stdint.h>
#include <stdbool.h>
#include <models.h>
#include <board.h>

typedef struct ActionNode
{
    Board *board;
    uint64_t depth;
    Coordinate *action;
    ActionNode *parent;
    uint64_t cost;
} ActionNode;

typedef struct ActionNodeList
{
    size_t size;
    ActionNodeListNode *head;
} ActionNodeList;

typedef struct ActionNodeListNode
{
    ActionNode *node;
    ActionNodeListNode *next;
} ActionNodeListNode;

ActionNodeList *action_node_neighbours(const ActionNode *node);

ActionNodeList *action_node_path(const ActionNode *node);

ActionNode *new_action_node(const Board *board, uint64_t depth, const Coordinate *action, const ActionNode *parent);

bool is_goal_node(const ActionNode *node);

uint64_t hash_action_node(const ActionNode *node);