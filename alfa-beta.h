#ifndef ALPHA_BETA
#define ALPHA_BETA

#include <vector>
#include "piese.h"

using namespace std;
extern long long sz;

struct Node{
    int scor;
    int alfa, beta;
    
    pair <int, char> finish; //ultima mutare
    pair <int, int>  start;

    char captured; // tipul piesei pe care am luat-o facand mutarea

    vector <Node*> childs{};

    Node(int scor, int alfa, int beta, pair <int, int>  start, pair <int, char> finish, char captured);
};  

typedef Node* Tree;

void generator(Tree *res, Piesa*** board, bool color, int depth, int level, bool curent);

int alpha_beta(Node* node, int depth, int alpha, int beta, int player, char mutari[]);

#endif

/*
arbore:
scor
ultima mutare
char cu piesa luata?
vector copii
alfa beta
*/