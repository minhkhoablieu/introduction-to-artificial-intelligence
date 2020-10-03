/*
 * Phùng Sơn Minh Khoa
 * B1812275
 * https://github.com/minhkhoa2000/AI_LAB
 *
 */
#include <iostream>
#include <queue>
#include <stack>
#include <malloc.h>



#define MAX_GHOST 3
#define MAX_PEOPLE 3
#define POSITION_A 1
#define POSITION_B 0

using namespace std;

typedef struct{
    int people;
    int ghost;
    int boat_location;
}State;

typedef struct Node{
    State state;
    struct Node* Parent;
    int no_function;
}Node;

void makeNullState(State *state)
{
    state->ghost = 0;
    state->people = 0;
    state->boat_location = 0;
}
int isWin(State state)
{
    return ( (state.people == 0) && (state.ghost == 0 ) && (state.boat_location == POSITION_B) );
}
int oneGhost(State currentState, State *result)
{
    if(currentState.boat_location == POSITION_A && currentState.ghost > 0 )
    {
        result->ghost = currentState.ghost - 1;
        result->people = currentState.people;
        result->boat_location = POSITION_B;
        return 1;
    }else if(currentState.boat_location == POSITION_B && currentState.ghost < 3 ){
        result->ghost = currentState.ghost + 1;
        result->people = currentState.people;
        result->boat_location = POSITION_A;
        return 1;
    }
    return 0;
} // 011
int twoGhost(State currentState, State *result)
{
    if(currentState.boat_location == POSITION_A && currentState.ghost > 1 )
    {
        result->ghost = currentState.ghost - 2;
        result->people = currentState.people;
        result->boat_location = POSITION_B;
        return 1;
    }else if(currentState.boat_location == POSITION_B && currentState.ghost < 2 ){
        result->ghost = currentState.ghost + 2;
        result->people = currentState.people;
        result->boat_location = POSITION_A;
        return 1;
    }
    return 0;
} // 021
int onePeople(State currentState, State *result)
{
    if(currentState.boat_location == POSITION_A && currentState.people > 0 )
    {
        result->people = currentState.people - 1;
        result->ghost = currentState.ghost;
        result->boat_location = POSITION_B;
        return 1;
    }else if(currentState.boat_location == POSITION_B && currentState.people < 3 ){
        result->people = currentState.people + 1;
        result->ghost = currentState.ghost;
        result->boat_location = POSITION_A;
        return 1;
    }
    return 0;
} // 101
int onePeopleOneGhost(State currentState, State *result)
{
    if((currentState.boat_location == POSITION_A) && (currentState.ghost > 0) && (currentState.people > 0))
    {
        result->people = currentState.people - 1;
        result->ghost = currentState.ghost -1;
        result->boat_location = POSITION_B;
        return 1;
    }
    else if((currentState.boat_location == POSITION_B) && (currentState.ghost < 3) && (currentState.people < 3))
    {
        result->people = currentState.people + 1;
        result->ghost = currentState.ghost + 1;
        result->boat_location = POSITION_A;
        return 1;
    }

    return 0;
} // 111
int twoPeople(State currentState, State *result)
{
    if(currentState.boat_location == POSITION_A && currentState.people > 1 )
    {
        result->people = currentState.people - 2;
        result->ghost = currentState.ghost;
        result->boat_location = !currentState.boat_location;
        return 1;
    }else if(currentState.boat_location == POSITION_B && currentState.people < 2 ){
        result->people = currentState.people + 2;
        result->ghost = currentState.ghost;
        result->boat_location = !currentState.boat_location;
        return 1;
    }
    return 0;
} //201
int isDangers(State state)
{
    State stateInB;
    stateInB.people = MAX_PEOPLE - state.people;
    stateInB.ghost = MAX_GHOST - state.ghost;
    stateInB.boat_location =  !state.boat_location;
    if( ( (state.people > 0) && ( state.ghost > state.people ) ) || ( (stateInB.people > 0) && ( stateInB.ghost > stateInB.people ) ) )
    {
        return 1;
    }
    return 0;
}

int call_operation(State cur_state, State * result, int opt)
{
    switch (opt) {
        case 1: return oneGhost(cur_state, result);
        case 2: return twoGhost(cur_state, result);
        case 3: return onePeople(cur_state, result);
        case 4: return onePeopleOneGhost(cur_state, result);
        case 5: return twoPeople(cur_state, result);
        default: cout << "ERROR";  return 0;
    }
}
void print_State(State state, int option)
{

    cout << endl  << " ["<< state.people << ", " << state.ghost << ", " << state.boat_location << "] " << endl;

}

int findState(State cur_state, queue<Node*> Q)
{
    while(!Q.empty())
    {
        if(Q.front()->state.people == cur_state.people && Q.front()->state.ghost == cur_state.ghost && Q.front()->state.boat_location == cur_state.boat_location )
        {
            return 1;
        }
        Q.pop();
    }
    return 0;
}


Node* BFS(State state)
{
    Node *root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_function = 0;
    queue<Node*> sOpen;
    queue<Node*> sClose;
    sOpen.push(root);
    int test = 1;

    while(!sOpen.empty())
    {
        Node *node = sOpen.front();
        sOpen.pop();
        sClose.push(node);
        if(isWin(node->state))
        {
            return node;
        }

        for(int i = 1; i <= 5; i++)
        {
            State newState;
            makeNullState(&newState);
            if(call_operation(node->state, &newState, i))
            {
                if(findState(newState, sOpen) || findState(newState, sClose))
                    continue;

                if(isDangers(newState))
                {
                    continue;
                }
                Node * newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->Parent = node;
                newNode->no_function = i;
                sOpen.push(newNode);
            }

        }
        test++;
    }
    return NULL;
}
void print_WaysToGetGoal(Node *node)
{
    stack<Node*> stackPrint;

    while(node->Parent != NULL)
    {
        stackPrint.push(node);
        node = node->Parent;
    }
    stackPrint.push(node);
    int action = 0;
    while(!stackPrint.empty())
    {
        print_State(stackPrint.top()->state,action);
        action++;
        stackPrint.pop();
    }
}
int main()
{

    State sState = {3, 3, POSITION_A};

    Node * result = BFS(sState);
    print_WaysToGetGoal(result);
    return 0;
}
