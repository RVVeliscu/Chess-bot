#ifndef PIESE_H
#define PIESE_H

#include <vector>

using namespace std;

typedef struct In_sah{
    bool sah = false;
    int i = 0;
    int j = 0;
    char tip = '0';
}in_sah;

extern in_sah Alb_in_sah, Negru_in_sah;

extern int i_rege_alb, j_rege_alb, i_rege_negru, j_rege_negru;

int letter_index(char c);
char index_letter(int n);
extern bool neluat, nemutatPion;

class Piesa{
public:
    pair <int, char> pozitie; //first reprezinta liniile iar second coloanele
    bool culoare = false; //false e negru
    char tip = '0'; 
    bool prima = true;
    int scor;

    bool muta(pair<int, char> src, pair<int, char> dest, Piesa ***board);
    virtual vector<pair<int, char>> verifica_posibile(Piesa ***board);
    void afiseaza_tip();
    virtual bool verifica_rocada(char tip, Piesa ***board);

    bool deschide_sah(Piesa ***board, pair <int, char> dest, bool color);
    bool mutareSah(Piesa ***board, pair <int, char> dest);

    /*
    Functia check e folosita in principal pe board
    c - culoarea piesei care apeleaza functia
    Return values:
    1 - loc gol
    2 - piesa de culoare opusa
    3 - rege de culoare opusa
    0 - piesa de aceeasi culoare
    */
    int check(bool c);

    Piesa();
    Piesa(pair<int, char> pozitie);
    Piesa(pair<int, char> pozitie, bool culoare);
    Piesa(pair<int, char> pozitie, bool culoare, char tip);
    ~Piesa();

protected:
    void seteaza_tip(char tip);
};

class Pion : public Piesa{
public:
    Pion();
    Pion(pair<int, char> pozitie);
    Pion(pair<int, char> pozitie, bool culoare);
    virtual vector<pair<int, char>> verifica_posibile(Piesa ***board);
    void afiseaza_tip();
    static void upgrade(char tip, pair<int, char> poz, Piesa ***board);
};

class Cal : public Piesa {
public:
    Cal();
    Cal(pair<int, char> pozitie);
    Cal(pair<int, char> pozitie, bool culoare);

    virtual vector<pair<int, char>> verifica_posibile(Piesa ***board);
};

class Nebun : public Piesa {
public:
    Nebun();
    Nebun(pair<int, char> pozitie);
    Nebun(pair<int, char> pozitie, bool culoare);

    virtual vector<pair<int, char>> verifica_posibile(Piesa ***board);
};

class Regina : public Piesa {
public:
    Regina();
    Regina(pair<int, char> pozitie);
    Regina(pair<int, char> pozitie, bool culoare);

    virtual vector<pair<int, char>> verifica_posibile(Piesa ***board);
};

class Tura : public Piesa {
// private:
//     friend class Rege;
public:
    Tura();
    Tura(pair<int, char> pozitie);
    Tura(pair<int, char> pozitie, bool culoare);

    virtual vector<pair<int, char>> verifica_posibile(Piesa ***board);
};

class Rege : public Piesa {
public:
    Rege();
    Rege(pair<int, char> pozitie);
    Rege(pair<int, char> pozitie, bool culoare);

    virtual vector<pair<int, char>> verifica_posibile(Piesa ***board);
    bool verifica_rocada(char tip, Piesa ***board);
};

void set_board(Piesa ***board);

#endif