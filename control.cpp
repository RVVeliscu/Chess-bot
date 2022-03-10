#include <iostream>
#include "alfa-beta.h"
#include "piese.h"

#define Alb true
#define Negru false

using namespace std;

bool culoare_de_verificat = Negru;
bool e_la_rand = Alb;
int counterMutari = 0;
in_sah Alb_in_sah, Negru_in_sah;
int three_check_alb = 0, three_check_negru = 0;
long long sz;

//Functia de dealocare a memoriei a matricei existente
Piesa*** deallocation(Piesa*** chessboard){
    for (size_t i = 1; i <= 8; i++){
        for (size_t j = 1; j <= 8; j++){
            delete chessboard[i][j];
        }
    }

    for (size_t i = 0; i < 10; i++){
        delete[] chessboard[i];
    }

    delete[] chessboard;
    return chessboard;
}

//Instructiunea New Game in care apelam functia deallocation si apoi cream o matrice noua
Piesa*** new_game(Piesa*** chessboard){
    deallocation(chessboard);
    chessboard = new Piesa **[10];


    for (size_t i = 0; i < 10; i++){
        chessboard[i] = new Piesa *[10];
    }
    Alb_in_sah.sah = false;
    Alb_in_sah.i = 0;
    Alb_in_sah.j = 0;
    Alb_in_sah.tip = '0';
    three_check_alb = 0;
    three_check_negru = 0;
    Negru_in_sah.sah = false;
    Negru_in_sah.i = 0;
    Negru_in_sah.j = 0;
    Negru_in_sah.tip = '0';
    set_board(chessboard);
    culoare_de_verificat = Negru;
    e_la_rand = Alb;
    cout << "variant 3check\n";

    return chessboard;
}

void umplere(Node *loc, int d)
{
    if(d == 0)
        return;
    
    for(int i = 1; i <= 3; i ++){
        loc->childs.push_back(new Node(i, i%2, !(i%2), make_pair(i,0), make_pair(1, 'b'), '0'));
        umplere(loc->childs[i-1], d-1);
    }
}

void afisare(Node *loc, int d)
{
    if(d == 0)
        return;
    
    for(int i = 0; i < loc->childs.size(); i ++){
        if(loc->childs[i]->scor != 0)
            cout << loc->childs[i]->scor << ' ';
    }
    if(loc->childs.size() != 0)
        cout << endl;
    for(int i = 0; i < loc->childs.size(); i ++){
        afisare(loc->childs[i], d-1);
    }
}

int main()
{
    Piesa ***chessboard = new Piesa **[10];
    for (size_t i = 0; i < 10; i++){
        chessboard[i] = new Piesa *[10];
    }
    set_board(chessboard);

    chessboard = new_game(chessboard);

    Tree arbore = new Node(0, 10000, -10000, make_pair(1, 1), make_pair(1, 'a'), '0');
    // generator(&arbore, chessboard, false, 2, 1, false);
    // afisare(arbore, 3);
    chessboard[2][2]->muta(make_pair(2, 'b'), make_pair(4, 'b'), chessboard);
    chessboard[7][3]->muta(make_pair(7, 'c'), make_pair(6, 'c'), chessboard);
    chessboard[1][7]->muta(make_pair(1, 'g'), make_pair(3, 'h'), chessboard);
    chessboard[8][4]->muta(make_pair(8, 'd'), make_pair(6, 'a'), chessboard);
    chessboard[2][4]->muta(make_pair(2, 'd'), make_pair(4, 'd'), chessboard);
    
    generator(&arbore, chessboard, false, 3, 1, false);
    cout <<sz <<'\n';
    cout << sizeof(*arbore) << '\n';
    // afisare(arbore, 4);
    // Tree arbore = new Node(0, 1, 0, make_pair(0,0), make_pair(1, 'b'), '0');
    // Node *p = arbore;
    // cout << p->scor << '\n';

    // umplere(p, 2);

    // p = arbore;
    // afisare(p, 2);
    char mutari[10];
    cout << alpha_beta(arbore, 3, -10000, 10000, 1, mutari) << endl;
    cout << mutari << endl;

    chessboard = deallocation(chessboard);
    return 0;
}