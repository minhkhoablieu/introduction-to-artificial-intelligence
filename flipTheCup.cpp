#include <iostream>
#include <chrono>
#include <queue>
#include <stack>
#include <malloc.h>
using namespace std::chrono;

#define MAX_CUP 6

typedef struct {
    int cup[MAX_CUP];
}State;

typedef struct Node{
    State state;
    struct Node* parent;
    int no_function;
}Node;

void makeNullState(State &state)
{
    for(int i = 0; i < MAX_CUP; i++)
    {
        state.cup[i] = 0;
    }
}
int flipTheCup(int action, State cur_state, State &result)
{
    result = cur_state;
    for(int i = action; i < action + 3; i++)
    {
        result.cup[i] = !cur_state.cup[i];
    }
    return 1;
}
void printState(State state)
{
    std::cout << "{ ";
    for(int i = 0; i < MAX_CUP; i++)
    {
        std::cout << state.cup[i] << ", ";
    }
    std::cout << "}" << std::endl;
}
bool goal(State state)
{
    for(int i : state.cup)
    {
        if(i != 1)
        {
            return false;
        }
    }
    return true;
}
int compareState(State stateOne, State stateTwo)
{
    for(int i = 0; i < MAX_CUP; i++)
    {
        if(stateOne.cup[i] != stateTwo.cup[i])
        {
            return 0;
        }
    }
    return 1;
}
int findStateDFS(State state, std::stack<Node*> s)
{
    while(!s.empty())
    {
        if(compareState(state, s.top()->state))
        {
            return 1;
        }
        s.pop();
    }
    return 0;
}
int findStateBFS(State state, std::queue<Node*> s)
{
    while(!s.empty())
    {
        if(compareState(state, s.front()->state))
        {
            return 1;
        }
        s.pop();
    }
    return 0;
}
Node *solveDFS(State state)
{

    std::stack<Node*> stackOpen;
    std::stack<Node*> stackClose;
    Node *root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;

    stackOpen.push(root);

    while(!stackOpen.empty())
    {
        Node *node = stackOpen.top();
        stackOpen.pop();
        stackClose.push(node);
        if(goal(node->state))
        {
            return node;
        }
        else
        {
            for(int action = 0 ; action < 4; action++)
            {
                State newState;
                makeNullState(newState);
                flipTheCup(action, node->state, newState);
                if(findStateDFS(newState, stackOpen) || findStateDFS(newState, stackClose))
                    continue;
                Node *newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = node;
                newNode->no_function = action;
                stackOpen.push(newNode);
            }
        }
    }



    return NULL;
}
Node *solveBFS(State state)
{

    std::queue<Node*> queueOpen;
    std::queue<Node*> queueClose;
    Node *root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_function = 0;

    queueOpen.push(root);

    while(!queueOpen.empty())
    {
        Node *node = queueOpen.front();
        queueOpen.pop();
        if(goal(node->state))
        {
            return node;
        }
        else
        {
            for(int action = 0 ; action < 4; action++)
            {
                State newState;
                makeNullState(newState);
                flipTheCup(action, node->state, newState);
                if(findStateBFS(newState, queueOpen) || findStateBFS(newState, queueClose))
                    continue;
                Node *newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = node;
                newNode->no_function = action;
                queueOpen.push(newNode);
            }
        }
    }
    return NULL;
}

int main() {


    State cur_state = {1,0,1,0,1,0}, result;


    auto start = high_resolution_clock::now();
    Node *p = solveDFS(cur_state);

    std::stack<Node*> stackPrint;

    while(p->parent != nullptr)
    {
        stackPrint.push(p);
        p = p->parent;
    }
    stackPrint.push(p);
    int no_action = 0;
    while(!stackPrint.empty())
    {
        printState(stackPrint.top()->state);
        stackPrint.pop();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << std::endl << ": "
         << duration.count() << " microseconds" << std::endl;
    return 0;
}
