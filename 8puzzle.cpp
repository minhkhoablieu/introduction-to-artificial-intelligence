#include <iostream>
#include <array>
using namespace std;
#define dimension 3


class Node{
public:
    Node(array<array<int, dimension>, dimension> matrix, int x, int y, int cost, int level)
    {
        this->matrix = matrix;
        this->x = x;
        this->y = y;
        this->cost = cost;
        this->level = level;
    }
    Node(const Node &node){
        this->matrix = node.matrix;
        this->x = node.x;
        this->y = node.y;
        this->cost = node.cost;
        this->level = node.level;
    }
    int getX() { return this->x; }
    int getY() { return this->y; }
    int getCost() { return this->cost; }
    int getLevel() { return this->level; }
    array<array<int, dimension>, dimension> getMatrix() { return this->matrix; }
    void swap()
    {
        this->x = x;
    }
private:
    array<array<int, dimension>, dimension> matrix;
    int x, y;
    int cost;
    int level;
};

class Puzzle{
public:
    int calculateCost(array<array<int, dimension>, dimension> initial, array<array<int, dimension>, dimension> goal)
    {
        int count = 0;
        for(int i = 0; i < dimension; i++)
        {
            for(int j = 0; j < dimension; j++)
            {
                if(initial[i][j] != 0 && initial[i][j] == goal[i][j])
                {
                    count++;
                }
            }
        }
        return count;
    }
    void printBoard(array<array<int, dimension>, dimension> matrix)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    bool isSafe(int x, int y)
    {
        return (x >= 0 && x < dimension && y >= 0 && y < dimension);
    }
    Node solve(array<array<int, dimension>, dimension> initial, array<array<int, dimension>, dimension> goal, int x, int y)
    {
        Node node(initial, x ,y ,1 ,1);
        return node;
    }
};



int main() {
    array<array<int, dimension>, dimension> initial = {{
            {1, 8, 2},
            {0, 4, 3},
            {7, 6, 5}
    }};
    array<array<int, dimension>, dimension> goal = {{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
    }};

    int x = 1;
    int y = 0;
    Puzzle puzzle;

    Node node = puzzle.solve(initial, goal, x, y);
    puzzle.printBoard(node.getMatrix());
}
