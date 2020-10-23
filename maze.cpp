#include <iostream>
#include <chrono>
#include <queue>
#include <stack>
#include <malloc.h>
#include <cmath>
#include <vector>
#include <set>

using namespace std::chrono;


#define MAX_ROW 8
#define MAX_COL 8

typedef struct {
    int row, col;
}Point;
typedef struct State {
    int maze[MAX_ROW][MAX_COL]{};
    Point start{};
    Point end{};
    bool visited[MAX_ROW][MAX_COL]{};
}State;
typedef struct Node{
    State maze;
    struct Node* parent{};
    int no_function{};
    double f{}, g{}, h{};
}Node;
//struct node_cmp{
//    bool operator()(Node *a, Node *b)
//    {
//        return a->f < b->f;
//    }
//};
void init(State &state)
{
    state.maze[state.start.row][state.start.col] = 2;

    state.maze[state.end.row][state.end.col] = 3;
    for(int i = 0; i < MAX_ROW; i++)
    {
        for(int j = 0; j < MAX_COL; j++)
        {
            state.visited[i][j] = false;
        }
    }
    state.visited[state.start.row][state.start.col] = true;
}
bool isGoal(State state)
{
    if((state.start.row == state.end.row) && (state.start.col == state.end.col))
        return true;
    return false;
}
bool isSafe(int x, int y, State state)
{
    return ((x >= 0 && x < MAX_ROW && y >= 0 && y < MAX_COL && state.maze[x][y] != 1) && !state.visited[x][y]);
}
bool move(int action, State state, State &result)
{

    int row[] = { 1, 0, -1, 0 };
    int col[] = { 0, -1, 0, 1 };
    if( isSafe(state.start.row+row[action], state.start.col+col[action], state) )
    {

        result = state;
        result.maze[state.start.row+row[action]][state.start.col+col[action]] = 2;
        result.start.row = state.start.row+row[action];
        result.start.col = state.start.col+col[action];
        result.visited[state.start.row+row[action]][state.start.col+col[action]] = true;
        return true;
    }
    return false;

}
void printMaze(State state)
{
    for(int i = 0; i < MAX_ROW; i++)
    {
        for(int j = 0; j < MAX_COL; j++)
        {
            std::cout << state.maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
double calculate(State state)
{
    return std::sqrt(std::pow((state.end.row - state.start.row), 2) + std::pow((state.end.col - state.start.col), 2)) ;
}
Node *solveDFS(State cur_state)
{
    std::stack<Node*> openStack;
    std::stack<Node*> closeStack;
    Node *root = (Node*)malloc(sizeof(Node));
    root->maze = cur_state;
    root->parent = nullptr;
    root->no_function = 0;
    openStack.push(root);
    while(!openStack.empty())
    {
        Node *node = openStack.top();
        openStack.pop();
        closeStack.push(node);
        if(isGoal(node->maze))
        {
            return node;
        }
        std::cout << "---------------" << std::endl;
        for(int i = 0; i < 4; i++)
        {
            State newState;
            if(move(i, node->maze, newState))
            {
                printMaze(newState);
                Node * newNode =(Node*)malloc(sizeof(Node));
                newNode->maze = newState;
                newNode->parent = node;
                newNode->no_function = i;
                openStack.push(newNode);
            }
        }
        std::cout << "---------------" << std::endl;
    }
    return nullptr;
}
Node *solveBFS(State cur_state)
{
    std::queue<Node*> openStack;
    std::queue<Node*> closeStack;
    Node *root = (Node*)malloc(sizeof(Node));
    root->maze = cur_state;
    root->parent = nullptr;
    root->no_function = 0;
    openStack.push(root);
    while(!openStack.empty())
    {
        Node *node = openStack.front();
        openStack.pop();
        closeStack.push(node);
        if(isGoal(node->maze))
        {
            return node;
        }
        std::cout << "---------------" << std::endl;
        for(int i = 0; i < 4; i++)
        {
            State newState;
            if(move(i, node->maze, newState))
            {
                printMaze(newState);
                Node * newNode =(Node*)malloc(sizeof(Node));
                newNode->maze = newState;
                newNode->parent = node;
                newNode->no_function = i;
                openStack.push(newNode);
            }
        }
        std::cout << "---------------" << std::endl;
    }
    return nullptr;
}
//bool same_state(State s1, State s2)
//{
//    for(int i = 0; i < MAX_ROW; i++)
//    {
//        for(int j = 0; j < MAX_COL; j++)
//        {
//            if()
//        }
//    }
//}
//bool find_state(State state, std::vector<State> *explored )
//{
//    for(State c1: *explored)
//    {
//
//    }
//}
//Node *A_Star(State cur_state, std::vector<State> &explored)
//{
//    Node *root = (Node*)malloc(sizeof(Node));
//    root->maze = cur_state;
//    root->parent = nullptr;
//    root->no_function = 0;
//    root->g = 0;
//    root->h = calculate(cur_state);
//    root->f = root->g + root->h;
//    std::multiset<Node*, node_cmp> frontiers;
//    frontiers.insert(root);
//    while(!frontiers.empty())
//    {
//        Node *node = *frontiers.begin();
//        frontiers.erase(frontiers.begin());
//        if(isGoal(node->maze))
//        {
//            return node;
//        }
//
//    }
//}
int main() {
    State cur_state = {
        {
    {1, 0, 1, 0, 0, 0, 1, 3},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 1},
    {0, 1, 1, 0, 0, 1, 0, 1},
    {0, 1, 1, 1, 0, 1, 0, 1},
    {0, 0, 1, 1, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {2, 0, 1, 1, 1, 0, 0, 0}
        }
    },result;

    cur_state.start = {7, 0};
    cur_state.end   = {0, 7};
    init(cur_state);
//
//
//
    Node *p = solveBFS(cur_state);

//    std::stack<Node*> stackPrint;

//    while(p->parent != nullptr)
//    {
//        stackPrint.push(p);
//        p = p->parent;
//    }
//    stackPrint.push(p);
//    int no_action = 0;
//    while(!stackPrint.empty())
//    {
//        printMaze(stackPrint.top()->maze);
//        stackPrint.pop();
//        std::cout << "--------------" << std::endl;
//    }

//    std::vector<State> explored;
//    std::cout << calculate(cur_state);

    return 0;
}
