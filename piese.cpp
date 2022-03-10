#include <iostream>
#include <vector>
#include "piese.h"

#define Alb true
#define Negru false

using namespace std;
bool neluat = true, nemutatPion = true;
int i_rege_alb, j_rege_alb, i_rege_negru, j_rege_negru;

//functie care returneaza indexul corespunzator literei (axa x pe tabla de joc, am presupus ca le vom nota cu litere mici)
int letter_index (char c){
    return c - 'a' + 1;
}

//avand un index, functia returneaza litera corespunzatoare
char index_letter (int n){
    return static_cast <char> (n + 96);
}

//functie care elimina o piesa de pe tabla
void clear_piece (Piesa* obj){
    obj->culoare = false;
    obj->pozitie = make_pair(0, 0);
    obj->prima = true;
    obj->tip = '0';
}

//functie care copiaza o piesa
void copy_piece (Piesa* obj1, Piesa* obj2){
    obj1->culoare = obj2->culoare;
    obj1->pozitie = obj2->pozitie;
    obj1->prima = obj2->prima;
    obj1->tip = obj2->tip;

    clear_piece(obj1);
}

//Se apeleaza la joc nou / comanda new
//Pune tabla de joc la setup-ul initial
void set_board (Piesa*** board){
    //Asezare piese albe
    board[1][1] = new Tura(make_pair(1, 'a'), Alb);
    board[1][2] = new Cal(make_pair(1, 'b'), Alb);
    board[1][3] = new Nebun(make_pair(1, 'c'), Alb);
    board[1][4] = new Regina(make_pair(1, 'd'), Alb);
    board[1][5] = new Rege(make_pair(1, 'e'), Alb);
    board[1][6] = new Nebun(make_pair(1, 'f'), Alb);
    board[1][7] = new Cal(make_pair(1, 'g'), Alb);
    board[1][8] = new Tura(make_pair(1, 'h'), Alb);

    for (int i = 1; i <= 8; i++)
        board[2][i] = new Pion(make_pair(2, index_letter(i)), Alb);
    
    //Asezare piese negre
    board[8][1] = new Tura(make_pair(8, 'a'), Negru);
    board[8][2] = new Cal(make_pair(8, 'b'), Negru);
    board[8][3] = new Nebun(make_pair(8, 'c'), Negru);
    board[8][4] = new Regina(make_pair(8, 'd'), Negru);
    board[8][5] = new Rege(make_pair(8, 'e'), Negru);
    board[8][6] = new Nebun(make_pair(8, 'f'), Negru);
    board[8][7] = new Cal(make_pair(8, 'g'), Negru);
    board[8][8] = new Tura(make_pair(8, 'h'), Negru);

    for (int i = 1; i <= 8; i++)
        board[7][i] = new Pion(make_pair(7, index_letter(i)), Negru);
    
    for (size_t i = 3; i <= 6; i++)
        for (size_t j = 1; j <= 8; j++)
            board[i][j] = new Piesa(make_pair(i, index_letter(j)));
}

bool in_between(pair <int,char> p, bool color){
	int i_rege = (color)? i_rege_alb: i_rege_negru;	
	int j_rege = (color)? j_rege_alb: j_rege_negru;
	in_sah culoare_in_sah = (color)? Alb_in_sah :Negru_in_sah;
	if (culoare_in_sah.tip == 'c'){
		return false;
	}
	if ((p.first*(j_rege - culoare_in_sah.j) + (p.second - '`')*(culoare_in_sah.i - i_rege) + ((i_rege*culoare_in_sah.j) - (culoare_in_sah.i*j_rege))) == 0){
		if (p.first >= min(i_rege,culoare_in_sah.i) && p.first <= max(i_rege, culoare_in_sah.i) 
			&& (p.second - '`') >= min(j_rege, culoare_in_sah.j) && (p.second - '`') <= max(j_rege, culoare_in_sah.j)){
			return true;
		}
	}
	return false;
}


/* ---------- Piesa ----------*/
/*
Functia check e folosita in principal pe board
c - culoarea piesei care apeleaza functia
Return values:
1 - loc gol
2 - piesa de culoare opusa
3 - rege de culoare opusa
0 - piesa de aceeasi culoare
*/
int Piesa::check(bool c){
    if(this->tip == '0'){
        return 1;
    } else {
        if(this->culoare != c){
            if(this->tip != 'r'){
                return 2;
            } else {
                return 3;
            }
        } else {
            return 0;
        }
    }
}

Piesa::Piesa(){}
Piesa::~Piesa(){}

Piesa::Piesa(pair<int, char> pozitie){
    this->pozitie = pozitie;
    this->scor = 0;
}

Piesa::Piesa(pair<int, char> pozitie, bool culoare){
    this->pozitie = pozitie;
    this->culoare = culoare;
    this->scor = 0;
}

Piesa::Piesa(pair<int, char> pozitie, bool culoare, char tip){
    this->pozitie = pozitie;
    this->culoare = culoare;
    this->tip = tip;
    this->scor = 0;
}

void Piesa::seteaza_tip(char tip){
    this->tip = tip;
}

vector<pair<int, char>> Piesa::verifica_posibile(Piesa*** board){
    vector<pair<int, char>> temp{};
    return temp;
}

void Piesa::afiseaza_tip(){
    cout << "0\n";
}
bool Piesa::verifica_rocada(char tip, Piesa ***board)
{
    return true;
}

bool Piesa::muta(pair<int, char> src, pair<int, char> dest, Piesa ***board) {
    //apelez muta pe un obiect pion pe care il sterg in aceasta functie, nu cred ca e prea corect :)))
    if(board[dest.first][letter_index(dest.second)]->tip != '0') {
        neluat = false;
    }
    delete board[dest.first][letter_index(dest.second)];
    
    switch(board[src.first][letter_index(src.second)]->tip)
    {
        case 'p':
            // if((dest.first == 4 && dest.second == 'b') || (src.first == 4 && src.second == 'b'))
            //     cout << src.first  << src.second << " -> " << dest.first  << dest.second << ' ' <<board[src.first][letter_index(src.second)]->tip << '\n';
            board[dest.first][letter_index(dest.second)] = new Pion(dest, board[src.first][letter_index(src.second)]->culoare);
            nemutatPion = false;
            break;
        case 'n':
            board[dest.first][letter_index(dest.second)] = new Nebun(dest, board[src.first][letter_index(src.second)]->culoare);
            break;
        case 't':
            board[dest.first][letter_index(dest.second)] = new Tura(dest, board[src.first][letter_index(src.second)]->culoare);
            break;
        case 'c':
            board[dest.first][letter_index(dest.second)] = new Cal(dest, board[src.first][letter_index(src.second)]->culoare);
            break;
        case 'q':
            board[dest.first][letter_index(dest.second)] = new Regina(dest, board[src.first][letter_index(src.second)]->culoare);
            break;
        case 'r':
            board[dest.first][letter_index(dest.second)] = new Rege(dest, board[src.first][letter_index(src.second)]->culoare);
            break;
        default:
            // // return false;
            // for (int i = 1; i <= 8; i++){
            //     for (int j = 1; j <= 8; j++){
            //         if(board[i][j]->culoare || board[i][j]->tip == '0')
            //             cout << board[i][j]->tip << ' ';
            //         else
            //             cout << (char)(board[i][j]->tip - 32) << ' ';
            //     }
            //     cout <<'\n';
            // }
            
            // cout << src.first  << src.second << " -> " << dest.first  << dest.second << ' ' <<board[src.first][letter_index(src.second)]->tip << '\n';
            break;
    }
    
    board[dest.first][letter_index(dest.second)]->prima = false;

    delete board[src.first][letter_index(src.second)];

    board[src.first][letter_index(src.second)] = new Piesa(src);

    board[src.first][letter_index(src.second)]->tip = '0';

    if((dest.first == 1 || dest.first == 8)&& board[dest.first][letter_index(dest.second)]->tip == 'p')
        Pion::upgrade('q', dest, board);

    return false;
}

/* 
    m am gandit mai bine aseara si nu e deloc sturdy ce am facut aici
    dar am cateva idei si nevoie de ajutor:
    1. e ok principial ce am facut pana acum?
    2. pe axele X si Y verific doar tura si regina, 
    fara posibili pioni sau nebuni care pot veni din diagonala
    3. imi mai da ceva cu virgula dar nu stiu cum sa explic
*/

bool Piesa::mutareSah(Piesa ***board, pair <int, char> dest){
    pair <int, int> poz_rege;
    bool st = true; //stanga
    bool dr = true; //dreapta
    bool f  = true; //fata
    bool s  = true; //spate
    bool sf = true; //stanga "fata" (adica + 1)
    bool ss = true; //stanga "spate" (adica - 1)
    bool df = true; //dreapta "fata"
    bool ds = true; //dreapta "fata"
    // poz_rege.first  = (this->culoare)? i_rege_alb : i_rege_negru;
    // poz_rege.second = (this->culoare)? j_rege_alb : j_rege_negru;
    // in_sah rege_in_sah = (this->culoare)? Alb_in_sah: Negru_in_sah;
    // if (dest.first == rege_in_sah.i && letter_index(dest.second) == rege_in_sah.j){
    //     return 1;
    // }
    if (board[dest.first][letter_index(dest.second)]->check(this->culoare) == 3 ||
        board[dest.first][letter_index(dest.second)]->check(this->culoare) == 0 ||
        (dest.first > 1 && board[dest.first - 1][letter_index(dest.second)]->check(this->culoare) == 3) || 
        (dest.second > 'a' && board[dest.first][letter_index(dest.second) - 1]->check(this->culoare) == 3) ||
        (dest.first < 8 && board[dest.first + 1][letter_index(dest.second)]->check(this->culoare) == 3) ||
        (dest.second < 'h' && board[dest.first][letter_index(dest.second) + 1]->check(this->culoare) == 3) || 
        (dest.first > 1 && dest.second > 'a' && board[dest.first - 1][letter_index(dest.second) - 1]->check(this->culoare) == 3) ||
        (dest.first < 8 && dest.second > 'a' && board[dest.first + 1][letter_index(dest.second) - 1]->check(this->culoare) == 3) ||
        (dest.first > 1 && dest.second < 'h' && board[dest.first - 1][letter_index(dest.second) + 1]->check(this->culoare) == 3) ||
        (dest.first < 8 && dest.second < 'h' && board[dest.first + 1][letter_index(dest.second) + 1]->check(this->culoare) == 3))
        return 0;

    // pt piese regulate
    for (int i = 1; i <= 8; i++) {
        // fata
        if (dest.first - i >= 1 && f) {
            if ((board[dest.first - i][letter_index(dest.second)]->tip == 't' || 
            	board[dest.first - i][letter_index(dest.second)]->tip == 'q' || 
            	board[dest.first - i][letter_index(dest.second)]->tip == 'r') && 
            	board[dest.first - i][letter_index(dest.second)]->check(this->culoare) == 2) {
                return 0;
            } else if (board[dest.first - i][letter_index(dest.second)]->check(this->culoare) != 1 && !( 
                board[dest.first - i][letter_index(dest.second)]->culoare == this->culoare &&
                board[dest.first - i][letter_index(dest.second)]->tip == 'r')){
                f = false;
            }
        }

        // spate
        if (dest.first + i <= 8 && s) {
            if ((board[dest.first + i][letter_index(dest.second)]->tip == 't' || 
            	board[dest.first + i][letter_index(dest.second)]->tip == 'q' || 
            	board[dest.first + i][letter_index(dest.second)]->tip == 'r') && 
            	board[dest.first + i][letter_index(dest.second)]->check(this->culoare) == 2) {
                return 0;
            } else if (board[dest.first + i][letter_index(dest.second)]->check(this->culoare) != 1 && !( 
                board[dest.first + i][letter_index(dest.second)]->culoare == this->culoare &&
                board[dest.first + i][letter_index(dest.second)]->tip == 'r')){
                s = false;
            }
        }

        // stanga
        if (letter_index(dest.second) - i >= 1 && st) {
            if ((board[dest.first][letter_index(dest.second) - i]->tip == 't' || 
            	board[dest.first][letter_index(dest.second) - i]->tip == 'q' || 
            	board[dest.first][letter_index(dest.second) - i]->tip == 'r') && 
            	board[dest.first][letter_index(dest.second) - i]->check(this->culoare) == 2) {
                return 0;
            } else if (board[dest.first][letter_index(dest.second) - i]->check(this->culoare) != 1 && !( 
                board[dest.first][letter_index(dest.second) - i]->culoare == this->culoare &&
                board[dest.first][letter_index(dest.second) - i]->tip == 'r')){
                st = false;
            }
        }

        // dreapta
        if (letter_index(dest.second) + i <= 8 && dr) {
            if ((board[dest.first][letter_index(dest.second) + i]->tip == 't' || 
            	board[dest.first][letter_index(dest.second) + i]->tip == 'q' || 
            	board[dest.first][letter_index(dest.second) + i]->tip == 'r') && 
            	board[dest.first][letter_index(dest.second) + i]->check(this->culoare) == 2) {
                return 0;
            } else if (board[dest.first][letter_index(dest.second) + i]->check(this->culoare) != 1 && !( 
                board[dest.first][letter_index(dest.second) + i]->culoare == this->culoare &&
                board[dest.first][letter_index(dest.second) + i]->tip == 'r')){
                dr = false;
            }
        }

        // stanga spate
        if (dest.first - i >= 1 && letter_index(dest.second) - i >= 1 && ss) {
            if (((board[dest.first - i][letter_index(dest.second) - i]->tip == 'n' || 
            	board[dest.first - i][letter_index(dest.second) - i]->tip == 'q' || 
            	board[dest.first - i][letter_index(dest.second) - i]->tip == 'r') && 
            	board[dest.first - i][letter_index(dest.second) - i]->check(this->culoare) == 2) 
                || ((i == 1) && (board[dest.first - i][letter_index(dest.second) - i]->tip == 'p') && board[dest.first - i][letter_index(dest.second) - i]->culoare == Alb)) {
                    return 0;
            } else if (board[dest.first - i][letter_index(dest.second) - i]->check(this->culoare) != 1 && !( 
                board[dest.first - i][letter_index(dest.second) - i]->culoare == this->culoare &&
                board[dest.first - i][letter_index(dest.second) - i]->tip == 'r')){
                ss = false;
            }
        }

        // dreapta spate
        if (dest.first - i >= 1 && letter_index(dest.second) + i <= 8 && ds) {
            if (((board[dest.first - i][letter_index(dest.second) + i]->tip == 'n' || 
            	board[dest.first - i][letter_index(dest.second) + i]->tip == 'q' || 
            	board[dest.first - i][letter_index(dest.second) + i]->tip == 'r') && 
            	board[dest.first - i][letter_index(dest.second) + i]->check(this->culoare) == 2) 
                || ((i == 1) && (board[dest.first - i][letter_index(dest.second) + i]->tip == 'p') && board[dest.first - i][letter_index(dest.second) + i]->culoare == Alb)) {
                    return 0;
            } else if (board[dest.first - i][letter_index(dest.second) + i]->check(this->culoare) != 1 && !( 
                board[dest.first - i][letter_index(dest.second) + i]->culoare == this->culoare &&
                board[dest.first - i][letter_index(dest.second) + i]->tip == 'r')){
                ds = false;
            }
        }

        // stanga fata
        if (dest.first + i <= 8 && letter_index(dest.second) - i >= 1 && sf) {
            if (((board[dest.first + i][letter_index(dest.second) - i]->tip == 'n' || 
            	board[dest.first + i][letter_index(dest.second) - i]->tip == 'q' || 
            	board[dest.first + i][letter_index(dest.second) - i]->tip == 'r') && 
            	board[dest.first + i][letter_index(dest.second) - i]->check(this->culoare) == 2) 
                || ((i == 1) && (board[dest.first + i][letter_index(dest.second) - i]->tip == 'p') && board[dest.first + i][letter_index(dest.second) - i]->culoare == Negru)) {
                    return 0;
            } else if (board[dest.first + i][letter_index(dest.second) - i]->check(this->culoare) != 1 && !( 
                board[dest.first + i][letter_index(dest.second) - i]->culoare == this->culoare &&
                board[dest.first + i][letter_index(dest.second) - i]->tip == 'r')){
                sf = false;
            }
        }

        // dreapta fata
        if (dest.first + i <= 8 && letter_index(dest.second) + i <= 8 && df) {
            if (((board[dest.first + i][letter_index(dest.second) + i]->tip == 'n' || 
            	board[dest.first + i][letter_index(dest.second) + i]->tip == 'q' || 
            	board[dest.first + i][letter_index(dest.second) + i]->tip == 'r') && 
            	board[dest.first + i][letter_index(dest.second) + i]->check(this->culoare) == 2) 
                || ((i == 1) && (board[dest.first + i][letter_index(dest.second) + i]->tip == 'p') && board[dest.first + i][letter_index(dest.second) + i]->culoare == Negru)) {
                    return 0;
            } else if (board[dest.first + i][letter_index(dest.second) + i]->check(this->culoare) != 1 && !( 
                board[dest.first + i][letter_index(dest.second) + i]->culoare == this->culoare &&
                board[dest.first + i][letter_index(dest.second) + i]->tip == 'r')){
                df = false;
            }
        }
    }
    // pt caluti
    //sus stanga
		if ((dest.first < 7) && (letter_index(dest.second) > 1)){
			if(board[dest.first + 2][letter_index(dest.second) - 1]->check(this->culoare) == 2 && board[dest.first + 2][letter_index(dest.second) - 1]->tip == 'c')
            return 0;
        }
	            
	    //sus dreapta
	    if ((dest.first < 7) && (dest.second < 'h')){
			if(board[dest.first + 2][letter_index(dest.second) + 1]->check(this->culoare) == 2 && board[dest.first + 2][letter_index(dest.second) + 1]->tip == 'c')
            return 0;
        }
	            
	    //jos stanga
	    if ((dest.first > 2) && (dest.second > 'a')){
			if(board[dest.first - 2][letter_index(dest.second) - 1]->check(this->culoare) == 2 && board[dest.first - 2][letter_index(dest.second) - 1]->tip == 'c')
            return 0;
        }
                
	   	//jos dreapta
	    if ((dest.first > 2) && (dest.second < 'h')){
			if(board[dest.first - 2][letter_index(dest.second) + 1]->check(this->culoare) == 2 && board[dest.first - 2][letter_index(dest.second) + 1]->tip == 'c')
            return 0;
        }

	   	//dreapta jos
	    if ((dest.first < 8) && (dest.second < 'g')){
			if(board[dest.first + 1][letter_index(dest.second) + 2]->check(this->culoare) == 2 && board[dest.first + 1][letter_index(dest.second) + 2]->tip == 'c')
            return 0;
        }

 		//dreapta sus
	    if ((dest.first > 1) && (dest.second < 'g')){
			if(board[dest.first - 1][letter_index(dest.second) + 2]->check(this->culoare) == 2 && board[dest.first - 1][letter_index(dest.second) + 2]->tip == 'c')
            return 0;
        }

	    //stanga sus
	    if ((dest.first > 1) && (dest.second > 'b')){
			if(board[dest.first - 1][letter_index(dest.second) - 2]->check(this->culoare) == 2 && board[dest.first - 1][letter_index(dest.second) - 2]->tip == 'c')
            return 0;
        }

	   	//stanga jos
	    if ((dest.first < 8) && (dest.second > 'b')){
			if(board[dest.first + 1][letter_index(dest.second) - 2]->check(this->culoare) == 2 && board[dest.first + 1][letter_index(dest.second) - 2]->tip == 'c')
            return 0;
        }
        return 1;
}   

//va returna 0 daca prin aceasta mutare vom lasa regele de aceeasi culoare in sah
//           1 daca nu
bool Piesa::deschide_sah(Piesa ***board, pair <int, char> dest,bool color){
    pair <int, int> poz_rege;
    poz_rege.first  = (color)? i_rege_alb : i_rege_negru;
    poz_rege.second = (color)? j_rege_alb : j_rege_negru;

    if(this->pozitie.first < poz_rege.first && letter_index(this->pozitie.second) == poz_rege.second && letter_index(dest.second) != poz_rege.second) {
        //jos
        for (int i = this->pozitie.first + 1; i < poz_rege.first; i++)
            if(board[i][poz_rege.second]->culoare == color  && board[i][poz_rege.second]->tip != '0')
                {return 1;};
        
        for (int i = this->pozitie.first - 1; i >= 1; i--) {
            if((board[i][poz_rege.second]->tip == 't' || board[i][poz_rege.second]->tip == 'q') && board[i][poz_rege.second]->culoare != color){
                {return 0;};
            } else {
                if(board[i][poz_rege.second]->tip != '0')
                    {return 1;};
            }
        }
        
    }

    if (this->pozitie.first > poz_rege.first && letter_index(this->pozitie.second) == poz_rege.second  && letter_index(dest.second) != poz_rege.second) {
        // sus
        for (int i = this->pozitie.first - 1; i > poz_rege.first; i--)
            if(board[i][poz_rege.second]->culoare == color  && board[i][poz_rege.second]->tip != '0')
                {return 1;};

        for (int i = this->pozitie.first + 1; i <= 8; i++) {
            if((board[i][poz_rege.second]->tip == 't' || board[i][poz_rege.second]->tip == 'q') && board[i][poz_rege.second]->culoare != color){
                {return 0;};
            } else {
                if(board[i][poz_rege.second]->tip != '0')
                    {return 1;};
            }
        }
    }
    if (this->pozitie.first == poz_rege.first && letter_index(this->pozitie.second) < poz_rege.second  && dest.first != poz_rege.first) {
        //stanga
        for (int i = letter_index(this->pozitie.second) + 1; i < poz_rege.second; i++)
            if(board[poz_rege.first][i]->culoare == color && board[poz_rege.first][i]->tip != '0')
                {return 1;};
    
        for (int i = letter_index(this->pozitie.second) - 1; i >= 1; i--) {
            if((board[poz_rege.first][i]->tip == 't' || board[poz_rege.first][i]->tip == 'q') && board[poz_rege.first][i]->culoare != color){
                {return 0;};
            } else {
                if(board[poz_rege.first][i]->tip != '0')
                    {return 1;};
            }
        }
    }
    if (this->pozitie.first == poz_rege.first && letter_index(this->pozitie.second) > poz_rege.second) {
        //dreapta
        for (int i = poz_rege.second + 1; i < letter_index(this->pozitie.second); i++)
            if(board[poz_rege.first][i]->culoare == color  && board[poz_rege.first][i]->tip != '0')
                {return 1;};
        
        for (int i = letter_index(this->pozitie.second) + 1; i <= 8; i++) {
            if((board[poz_rege.first][i]->tip == 't' || board[poz_rege.first][i]->tip == 'q') && board[poz_rege.first][i]->culoare != color){
                {return 0;};
            } else {
                if(board[poz_rege.first][i]->tip != '0')
                    {return 1;};
            }
        }
    }
    if ((this->pozitie.first - poz_rege.first) == (letter_index(this->pozitie.second) - poz_rege.second)) {
        //diag pp
        
        if ((this->pozitie.first - poz_rege.first) < 0){
            //diag cu minus (diag st jos)
            for (int i = 1; i < poz_rege.first - this->pozitie.first; i++){
                if(board[poz_rege.first - i][poz_rege.second - i]->culoare == color && board[poz_rege.first - i][poz_rege.second - i]->tip != '0')
                    {return 1;};
            }
            
            for (int i = 1; i < min(this->pozitie.first, letter_index(this->pozitie.second)); i++) {
                if((board[this->pozitie.first - i][letter_index(this->pozitie.second) - i]->tip == 'n' || 
                	board[this->pozitie.first - i][letter_index(this->pozitie.second) - i]->tip == 'q') && 
                    board[this->pozitie.first - i][letter_index(this->pozitie.second) - i]->culoare != color){
                    {return 0;};
                } else {
                    if(board[this->pozitie.first - i][letter_index(this->pozitie.second) - i]->tip != '0')
                        {return 1;};
                }
            }
        } else {
            //diag cu plus (dr sus)
            for (int i = 1; i < this->pozitie.first - poz_rege.first; i++){
                if(board[poz_rege.first + i][poz_rege.second + i]->culoare == color  && board[poz_rege.first + i][poz_rege.second + i]->tip != '0')
                    {return 1;};
            }
            
            for (int i = 1; i <= 8 - max(this->pozitie.first, letter_index(this->pozitie.second)); i++) {
                if((board[this->pozitie.first + i][letter_index(this->pozitie.second) + i]->tip == 'n' || 
                	board[this->pozitie.first + i][letter_index(this->pozitie.second) + i]->tip == 'q') && 
                    board[this->pozitie.first + i][letter_index(this->pozitie.second) + i]->culoare != color){
                    {return 0;};
                } else {
                    if(board[this->pozitie.first + i][letter_index(this->pozitie.second) + i]->tip != '0')
                        {return 1;};
                }
            }
        }
        
    }
    if ((this->pozitie.first - poz_rege.first) == (poz_rege.second - letter_index(this->pozitie.second))) {
        //diag sec
        if ((this->pozitie.first - poz_rege.first) < 0){
            //diag cu minus (diag dr jos)
            for (int i = 1; i < poz_rege.first - this->pozitie.first; i++){
                if(board[poz_rege.first - i][poz_rege.second + i]->culoare == color  && board[poz_rege.first - i][poz_rege.second + i]->tip != '0')
                    {return 1;};
            }
            
            for (int i = 1; i < min(this->pozitie.first, 9-letter_index(this->pozitie.second)); i++) {
                if((board[this->pozitie.first - i][letter_index(this->pozitie.second) + i]->tip == 'n' || 
                	board[this->pozitie.first - i][letter_index(this->pozitie.second) + i]->tip == 'q') && 
                    board[this->pozitie.first - i][letter_index(this->pozitie.second) + i]->culoare != color){
                    {return 0;};
                } else {
                    if(board[this->pozitie.first - i][letter_index(this->pozitie.second) + i]->tip != '0')
                        {return 1;};
                }
            }
        } else {
            //diag cu plus st sus
            for (int i = 1; i < this->pozitie.first - poz_rege.first; i++){
                if(board[poz_rege.first + i][poz_rege.second - i]->culoare == color  && board[poz_rege.first + i][poz_rege.second - i]->tip != '0')
                    {return 1;};
            }
            
            for (int i = 1; i < min(9 - this->pozitie.first, letter_index(this->pozitie.second)); i++) {
                if((board[this->pozitie.first + i][letter_index(this->pozitie.second) - i]->tip == 'n' || 
                	board[this->pozitie.first + i][letter_index(this->pozitie.second) - i]->tip == 'q') && 
                    board[this->pozitie.first + i][letter_index(this->pozitie.second) - i]->culoare != color){
                    {return 0;};
                } else {
                    if(board[this->pozitie.first + i][letter_index(this->pozitie.second) - i]->tip != '0')
                        {return 1;};
                }
            }
        }
    
    }
    return 1;
}

/* ---------- Pion ----------*/
void Pion::afiseaza_tip(){
    cout << "p\n";
}

Pion::Pion() : Piesa(){
    seteaza_tip('p');
    this->scor = 10;
}

Pion::Pion(pair<int, char> pozitie) : Piesa(pozitie){
    seteaza_tip('p');
    this->scor = 10;
}

Pion::Pion(pair<int, char> pozitie, bool culoare) : Piesa(pozitie, culoare, 'p'){
    this->scor = (this->culoare)? 10 : -10;
}

vector<pair<int, char>> Pion::verifica_posibile(Piesa*** board) {
    vector<pair<int, char>> temp{};
    vector<pair<int, char>> ret{};
    in_sah *culoare_in_sah = (this->culoare)? &Alb_in_sah :&Negru_in_sah;
    if(!this->culoare){ // pionul se muta in feluri diferite daca e negru sau alb, aici tratez pentru negru
        if(this->prima){ //daca e prima data cand se muta pionul se poate muta cu 2 in fata
            if(board[this->pozitie.first - 2][letter_index(this->pozitie.second)]->check(this->culoare) == 1 && 
                board[this->pozitie.first - 1][letter_index(this->pozitie.second)]->check(this->culoare) == 1 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 2, this->pozitie.second), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - 2 == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first - 2, this->pozitie.second), this->culoare)))))
                temp.push_back(make_pair(this->pozitie.first - 2, this->pozitie.second));
        }

        //caz normal, se muta 1 in fata
        if(this->pozitie.first - 1 >= 1)
            if(board[this->pozitie.first - 1][letter_index(this->pozitie.second)]->check(this->culoare) == 1 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 1, this->pozitie.second), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - 1 == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first - 1, this->pozitie.second), this->culoare)))))
                temp.push_back(make_pair(this->pozitie.first - 1, this->pozitie.second));

        //caz de atac
        if(letter_index(this->pozitie.second) - 1 >= 1 && this->pozitie.first - 1 >= 1) // daca nu ies de pe tabla in lateral
            if(board[this->pozitie.first - 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 2 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 1, this->pozitie.second - 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first == culoare_in_sah->i) && (this->pozitie.second - 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first, this->pozitie.second - 1), this->culoare))))){ //trebuie sa fie ocupata pozitia de atac cu piesa de culoare opusa
                temp.push_back(make_pair(this->pozitie.first - 1, index_letter(letter_index(this->pozitie.second) - 1)));
            }else if (board[this->pozitie.first - 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        
        if(letter_index(this->pozitie.second) + 1 <= 8 && this->pozitie.first - 1 >= 1) // daca nu ies de pe tabla in lateral
            if(board[this->pozitie.first - 1][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 2 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 1, this->pozitie.second + 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - 1 == culoare_in_sah->i) && (this->pozitie.second + 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first - 1, this->pozitie.second + 1), this->culoare))))){
                temp.push_back(make_pair(this->pozitie.first - 1, index_letter(letter_index(this->pozitie.second) + 1)));
        }else if (board[this->pozitie.first - 1][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
    }
    else {
        if(prima){ //daca e prima data cand se muta pionul se poate muta cu 2 in fata
            if(board[this->pozitie.first + 2][letter_index(this->pozitie.second)]->check(this->culoare) == 1 &&
                    board[this->pozitie.first + 1][letter_index(this->pozitie.second)]->check(this->culoare) == 1 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 2, this->pozitie.second), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 2 == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 2, this->pozitie.second), this->culoare)))))
                temp.push_back(make_pair(this->pozitie.first + 2, this->pozitie.second));
        }

        //caz normal, se muta 1 in fata
        if(this->pozitie.first + 1 <= 8)
            if(board[this->pozitie.first + 1][letter_index(this->pozitie.second)]->check(this->culoare) == 1 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 1, this->pozitie.second), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 1 == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 1, this->pozitie.second), this->culoare)))))
                temp.push_back(make_pair(this->pozitie.first + 1, this->pozitie.second));

        //caz de atac
        if(letter_index(this->pozitie.second)-1 >= 1 && this->pozitie.first + 1 <= 8) // daca nu ies de pe tabla in lateral
            if(board[this->pozitie.first + 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 2 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 1, this->pozitie.second - 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 1 == culoare_in_sah->i) && (this->pozitie.second - 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 1, this->pozitie.second - 1), this->culoare))))){ //trebuie sa fie ocupata pozitia de atac cu piesa de culoare opusa
                temp.push_back(make_pair(this->pozitie.first + 1, index_letter(letter_index(this->pozitie.second) - 1)));
            }else if (board[this->pozitie.first + 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        
        if(letter_index(this->pozitie.second) + 1 <= 8 && this->pozitie.first + 1 <= 8) // daca nu ies de pe tabla in lateral
            if(board[this->pozitie.first + 1][letter_index(this->pozitie.second)+1]->check(this->culoare) == 2 && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 1, this->pozitie.second + 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 1 == culoare_in_sah->i) && (this->pozitie.second + 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 1, this->pozitie.second + 1), this->culoare))))){
                temp.push_back(make_pair(this->pozitie.first + 1, index_letter(letter_index(this->pozitie.second) + 1)));
            }else if (board[this->pozitie.first + 1][letter_index(this->pozitie.second)+1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
    }
    return temp;
}

//dupa ce pe board am un alt obiect, pionul care a ajuns acolo si nu mai e in board inca exista in memorie
//pot face un ~Pion() (deconstructor) si apelez acolo unde am dat comanda de upgrade??
void Pion::upgrade(char tip, pair<int, char> poz, Piesa ***board){
        bool temp_c = board[poz.first][letter_index(poz.second)]->culoare;
        delete board[poz.first][letter_index(poz.second)];
        // board[poz.first][letter_index(poz.second)] = new Regina(poz, temp_c);
        switch(tip){
            case 'n':
                board[poz.first][letter_index(poz.second)] = new Cal(poz, temp_c);
                break;
            case 'b':
                board[poz.first][letter_index(poz.second)] = new Nebun(poz, temp_c);
                break;
            case 'r':
                board[poz.first][letter_index(poz.second)] = new Tura(poz, temp_c);
                break;
            default:
                board[poz.first][letter_index(poz.second)] = new Regina(poz, temp_c);
                break;
        }
        board[poz.first][letter_index(poz.second)]->prima = false;
}

/* ---------- Cal ----------*/

Cal::Cal() : Piesa(){
    seteaza_tip('c');
    this->scor = 30;
}

Cal::Cal(pair<int, char> pozitie) : Piesa(pozitie){
    seteaza_tip('c');
    this->scor = 30;
}

Cal::Cal(pair<int, char> pozitie, bool culoare) : Piesa(pozitie, culoare, 'c')
{
        this->scor = (this->culoare)? 30 : -30;
}

vector<pair<int, char>> Cal::verifica_posibile(Piesa*** board){
    //de implementat, nu conteaza culoarea, sunt acelasi 8 pozitii de verificat si pt alb si negru, si odar pozitiile alea, nu is drumul(calul poate sarii)
    vector<pair<int, char>> temp{};
    vector<pair<int, char>> ret{};
    in_sah *culoare_in_sah = (this->culoare)? &Alb_in_sah :&Negru_in_sah;
		//sus stanga
		if ((this->pozitie.first < 7) && (this->pozitie.second > 'a'))
			if(((board[this->pozitie.first + 2][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 1) || 
				(board[this->pozitie.first + 2][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 2, this->pozitie.second - 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 2 == culoare_in_sah->i) && (this->pozitie.second - 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 2, this->pozitie.second - 1), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first + 2, this->pozitie.second - 1));
            }else if (board[this->pozitie.first + 2][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
	    //sus dreapta
	    if ((this->pozitie.first < 7) && (this->pozitie.second < 'h'))
			if(((board[this->pozitie.first + 2][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 1) || 
				(board[this->pozitie.first + 2][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 2, this->pozitie.second + 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 2 == culoare_in_sah->i) && (this->pozitie.second + 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 2, this->pozitie.second + 1), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first + 2, this->pozitie.second + 1));
            }else if (board[this->pozitie.first + 2][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
	    //jos stanga
	    if ((this->pozitie.first > 2) && (this->pozitie.second > 'a'))
			if(((board[this->pozitie.first - 2][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 1) || 
				(board[this->pozitie.first - 2][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 2, this->pozitie.second - 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - 2 == culoare_in_sah->i) && (this->pozitie.second - 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first - 2, this->pozitie.second - 1), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first - 2, this->pozitie.second - 1));
            }else if (board[this->pozitie.first - 2][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
	   	//jos dreapta
	    if ((this->pozitie.first > 2) && (this->pozitie.second < 'h'))
			if(((board[this->pozitie.first - 2][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 1) || 
				(board[this->pozitie.first - 2][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 2, this->pozitie.second + 1), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - 2 == culoare_in_sah->i) && (this->pozitie.second + 1 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first - 2, this->pozitie.second + 1), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first - 2, this->pozitie.second + 1));
            }else if (board[this->pozitie.first - 2][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
	   	//dreapta jos
	    if ((this->pozitie.first < 8) && (this->pozitie.second < 'g'))
			if(((board[this->pozitie.first + 1][letter_index(this->pozitie.second) + 2]->check(this->culoare) == 1) || 
				(board[this->pozitie.first + 1][letter_index(this->pozitie.second) + 2]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 1, this->pozitie.second + 2), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 1 == culoare_in_sah->i) && (this->pozitie.second + 2 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 1, this->pozitie.second + 2), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first + 1, this->pozitie.second + 2));
            }else if (board[this->pozitie.first + 1][letter_index(this->pozitie.second) + 2]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
 		//dreapta sus
	    if ((this->pozitie.first > 1) && (this->pozitie.second < 'g'))
			if(((board[this->pozitie.first - 1][letter_index(this->pozitie.second) + 2]->check(this->culoare) == 1) || 
				(board[this->pozitie.first - 1][letter_index(this->pozitie.second) + 2]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 1, this->pozitie.second + 2), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - 1 == culoare_in_sah->i) && (this->pozitie.second + 2 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first - 1, this->pozitie.second + 2), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first - 1, this->pozitie.second + 2));
            }else if (board[this->pozitie.first - 1][letter_index(this->pozitie.second) + 2]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
	    //stanga sus
	    if ((this->pozitie.first > 1) && (this->pozitie.second > 'b'))
			if(((board[this->pozitie.first - 1][letter_index(this->pozitie.second) - 2]->check(this->culoare) == 1) || 
				(board[this->pozitie.first - 1][letter_index(this->pozitie.second) - 2]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first - 1, this->pozitie.second - 2), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - 1 == culoare_in_sah->i) && (this->pozitie.second - 2 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first - 1, this->pozitie.second - 2), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first - 1, this->pozitie.second - 2));
            }else if (board[this->pozitie.first - 1][letter_index(this->pozitie.second) - 2]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
	   	//stanga jos
	    if ((this->pozitie.first < 8) && (this->pozitie.second > 'b'))
			if(((board[this->pozitie.first + 1][letter_index(this->pozitie.second) - 2]->check(this->culoare) == 1) || 
				(board[this->pozitie.first + 1][letter_index(this->pozitie.second) - 2]->check(this->culoare) == 2)) && 
                board[this->pozitie.first][letter_index(this->pozitie.second)]->deschide_sah(board, make_pair(this->pozitie.first + 1, this->pozitie.second - 2), this->culoare) && 
                (culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + 1 == culoare_in_sah->i) && (this->pozitie.second - 2 == culoare_in_sah->j + '`') ||
                in_between(make_pair(this->pozitie.first + 1, this->pozitie.second - 2), this->culoare))))){
	            temp.push_back(make_pair(this->pozitie.first + 1, this->pozitie.second - 2));
            }else if (board[this->pozitie.first + 1][letter_index(this->pozitie.second) - 2]->check(this->culoare) == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
    return temp;
}

/* ---------- Nebun ----------*/

Nebun::Nebun() : Piesa(){
    seteaza_tip('n');
    this->scor = 30;
}

Nebun::Nebun(pair<int, char> pozitie) : Piesa(pozitie){
    seteaza_tip('n');
    this->scor = 30;
}

Nebun::Nebun(pair<int, char> pozitie, bool culoare) : Piesa(pozitie, culoare, 'n')
{
    this->scor = (this->culoare)? 30 : -30;
}

vector<pair<int, char>> Nebun::verifica_posibile(Piesa*** board){
    vector<pair<int, char>> temp{};
    vector<pair<int, char>> ret{};
    in_sah *culoare_in_sah = (this->culoare)? &Alb_in_sah :&Negru_in_sah;
    bool sf = true; //stanga "fata" (adica + 1)
    bool ss = true; //stanga "spate" (adica - 1)
    bool df = true; //dreapta "fata"
    bool ds = true; //dreapta "fata"
    for (int i = 1; i < 8; i++)
    {
        int aux = 0;
        //stanga, spre alb
        if (this->pozitie.first - i >= 1 && letter_index(this->pozitie.second) - i >= 1 && ss)
        {
            aux = board[this->pozitie.first - i][letter_index(this->pozitie.second) - i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first - i, index_letter(letter_index(this->pozitie.second) - i)), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - i == culoare_in_sah->i) && (this->pozitie.second - i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first - i, this->pozitie.second - i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first - i, this->pozitie.second - i));
                }
                if(aux == 2)
                    ss = false;
            }
            else
                ss = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            ss = false;
        
        //dreapta, spre alb
        if (this->pozitie.first - i >= 1 && letter_index(this->pozitie.second) + i <= 8 && ds)
        {
            aux = board[this->pozitie.first - i][letter_index(this->pozitie.second) + i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first - i, index_letter(letter_index(this->pozitie.second) + i)), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - i == culoare_in_sah->i) && (this->pozitie.second + i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first - i, this->pozitie.second + i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first - i, this->pozitie.second + i));
                }
                if(aux == 2)
                    ds = false;
            }
            else
                ds = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            ds = false;

        //stanga, spre negru
        if (this->pozitie.first + i <= 8 && letter_index(this->pozitie.second) - i >= 1 && sf)
        {
            aux = board[this->pozitie.first + i][letter_index(this->pozitie.second) - i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first + i, index_letter(letter_index(this->pozitie.second) - i)), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + i == culoare_in_sah->i) && (this->pozitie.second - i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first + i, this->pozitie.second - i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first + i, this->pozitie.second - i));
                }
                if(aux == 2)
                    sf = false;
            }
            else
                sf = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            sf = false;

        //dreapta, spre negru
        if (this->pozitie.first + i <= 8 && letter_index(this->pozitie.second) + i <= 8 && df)
        {
            aux = board[this->pozitie.first + i][letter_index(this->pozitie.second) + i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first + i, index_letter(letter_index(this->pozitie.second) + i)), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + i == culoare_in_sah->i) && (this->pozitie.second + i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first + i, this->pozitie.second + i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first + i, this->pozitie.second + i));
                }
                if(aux == 2)
                    df = false;
            }
            else
                df = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            df = false;
    }
    return temp;
}

/* ---------- Regina ----------*/

Regina::Regina() : Piesa(){
    seteaza_tip('q');
    this->scor = 90;
}

Regina::Regina(pair<int, char> pozitie) : Piesa(pozitie){
    seteaza_tip('q');
    this->scor = 90;
}

Regina::Regina(pair<int, char> pozitie, bool culoare) : Piesa(pozitie, culoare, 'q')
{
    this->scor = (this->culoare)? 90 : -90;
}

vector<pair<int, char>> Regina::verifica_posibile(Piesa*** board){
    vector<pair<int, char>> temp{};
    vector<pair<int, char>> ret{};
    in_sah *culoare_in_sah = (this->culoare)? &Alb_in_sah :&Negru_in_sah;
    bool st = true; //stanga
    bool dr = true; //dreapta
    bool f  = true; //fata
    bool s  = true; //spate
    bool sf = true; //stanga "fata" (adica + 1)
    bool ss = true; //stanga "spate" (adica - 1)
    bool df = true; //dreapta "fata"
    bool ds = true; //dreapta "fata"
    for (int i = 1; i < 8; i++)
    {
        int aux = 0;
        //fata
        if (this->pozitie.first - i >= 1 && f)
        {
            aux = board[this->pozitie.first - i][letter_index(this->pozitie.second)]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first - i, this->pozitie.second), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - i == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first - i, this->pozitie.second), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first - i, this->pozitie.second));
                }
                if(aux == 2)
                    f = false;
            }
            else
                f = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            f = false;
        
        //spate
        if (this->pozitie.first + i <= 8 && s)
        {
            aux = board[this->pozitie.first + i][letter_index(this->pozitie.second)]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first + i, this->pozitie.second), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + i == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first + i, this->pozitie.second), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first + i, this->pozitie.second));
                }
                if(aux == 2)
                    s = false;
            }
            else
                s = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            s = false;

        //stanga
        if (letter_index(this->pozitie.second) - i >= 1 && st)
        {
            aux = board[this->pozitie.first][letter_index(this->pozitie.second) - i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first, this->pozitie.second - i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first == culoare_in_sah->i) && (this->pozitie.second - i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first, this->pozitie.second - i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first, this->pozitie.second - i));
                }
                if(aux == 2)
                    st = false;
            }
            else
                st = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            st = false;

        //dreapta
        if (letter_index(this->pozitie.second) + i <= 8 && dr)
        {
            aux = board[this->pozitie.first][letter_index(this->pozitie.second) + i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first, this->pozitie.second + i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first == culoare_in_sah->i) && (this->pozitie.second + i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first, this->pozitie.second + i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first, this->pozitie.second + i));
                }
                if(aux == 2)
                    dr = false;
            }
            else
                dr = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            dr = false;

        //stanga, spre alb
        if (this->pozitie.first - i >= 1 && letter_index(this->pozitie.second) - i >= 1 && ss)
        {
            aux = board[this->pozitie.first - i][letter_index(this->pozitie.second) - i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first - i, this->pozitie.second - i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - i == culoare_in_sah->i) && (this->pozitie.second - i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first - i, this->pozitie.second - i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first - i, this->pozitie.second - i));
                }
                if(aux == 2)
                    ss = false;
            }
            else
                ss = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            ss = false;
        
        //dreapta, spre alb
        if (this->pozitie.first - i >= 1 && letter_index(this->pozitie.second) + i <= 8 && ds)
        {
            aux = board[this->pozitie.first - i][letter_index(this->pozitie.second) + i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first - i, this->pozitie.second + i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - i == culoare_in_sah->i) && (this->pozitie.second + i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first - i, this->pozitie.second + i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first - i, this->pozitie.second + i));
                }
                if(aux == 2)
                    ds = false;
            }
            else
                ds = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            ds = false;

        //stanga, spre negru
        if (this->pozitie.first + i <= 8 && letter_index(this->pozitie.second) - i >= 1 && sf)
        {
            aux = board[this->pozitie.first + i][letter_index(this->pozitie.second) - i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first + i, this->pozitie.second - i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + i == culoare_in_sah->i) && (this->pozitie.second - i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first + i, this->pozitie.second - i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first + i, this->pozitie.second - i));
                }
                if(aux == 2)
                    sf = false;
            }
            else
                sf = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            sf = false;

        //dreapta, spre negru
        if (this->pozitie.first + i <= 8 && letter_index(this->pozitie.second) + i <= 8 && df)
        {
            aux = board[this->pozitie.first + i][letter_index(this->pozitie.second) + i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first + i, this->pozitie.second + i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + i == culoare_in_sah->i) && (this->pozitie.second + i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first + i, this->pozitie.second + i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first + i, this->pozitie.second + i));
                }
                if(aux == 2)
                    df = false;
            }
            else
                df = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            df = false;
    }
    return temp;
}

/* ---------- Tura ----------*/

Tura::Tura() : Piesa(){
    seteaza_tip('t');
    this->scor = 50;
}

Tura::Tura(pair<int, char> pozitie) : Piesa(pozitie){
    seteaza_tip('t');
    this->scor = 50;
}

Tura::Tura(pair<int, char> pozitie, bool culoare) : Piesa(pozitie, culoare, 't')
{
    this->scor = (this->culoare)? 50 : -50;
}

vector<pair<int, char>> Tura::verifica_posibile(Piesa*** board){
    vector<pair<int, char>> temp{};
    vector<pair<int, char>> ret{};
    in_sah *culoare_in_sah = (this->culoare)? &Alb_in_sah :&Negru_in_sah;
    bool st = true; //stanga
    bool dr = true; //dreapta
    bool f  = true; //fata
    bool s  = true; //spate
    for (int i = 1; i < 8; i++)
    {
        int aux = 0;
        //fata
        if (this->pozitie.first - i >= 1 && f)
        {
            aux = board[this->pozitie.first - i][letter_index(this->pozitie.second)]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first - i, this->pozitie.second), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first - i == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first - i, this->pozitie.second), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first - i, this->pozitie.second));
                }
                if(aux == 2)
                    f = false;
            }
            else
                f = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            f = false;
        
        //spate
        if (this->pozitie.first + i <= 8 && s)
        {
            aux = board[this->pozitie.first + i][letter_index(this->pozitie.second)]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first + i, this->pozitie.second), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first + i == culoare_in_sah->i) && (this->pozitie.second == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first + i, this->pozitie.second), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first + i, this->pozitie.second));
                }
                if(aux == 2)
                    s = false;
            }
            else
                s = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            s = false;

        //stanga
        if (letter_index(this->pozitie.second) - i >= 1 && st)
        {
            aux = board[this->pozitie.first][letter_index(this->pozitie.second) - i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first, this->pozitie.second - i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first == culoare_in_sah->i) && (this->pozitie.second - i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first, this->pozitie.second - i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first, this->pozitie.second - i));
                }
                if(aux == 2)
                    st = false;
            }
            else
                st = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            st = false;

        //dreapta
        if (letter_index(this->pozitie.second) + i <= 8 && dr)
        {
            aux = board[this->pozitie.first][letter_index(this->pozitie.second) + i]->check(this->culoare);
            if((aux == 1 || aux == 2) && this->deschide_sah(board, make_pair(this->pozitie.first, this->pozitie.second + i), this->culoare))
            {
                if ((culoare_in_sah->sah == false || (culoare_in_sah->sah && ((this->pozitie.first == culoare_in_sah->i) && (this->pozitie.second + i == culoare_in_sah->j + '`')) ||
                in_between(make_pair(this->pozitie.first , this->pozitie.second + i), this->culoare)))){
                    temp.push_back(make_pair(this->pozitie.first, this->pozitie.second + i));
                }
                if(aux == 2)
                    dr = false;
            }
            else
                dr = false;

            if (aux == 3){
                ret.push_back(make_pair(-1,'\0'));
                return ret;
            }
        }
        else
            dr = false;
    }
    return temp;
}

/* ---------- Rege ----------*/

Rege::Rege() : Piesa(){
    seteaza_tip('r');
    this->scor = 900;
}

Rege::Rege(pair<int, char> pozitie) : Piesa(pozitie){
    seteaza_tip('r');
    this->scor = 900;
}

Rege::Rege(pair<int, char> pozitie, bool culoare) : Piesa(pozitie, culoare, 'r'){
    if(culoare == Alb){
        i_rege_alb = pozitie.first;
        j_rege_alb = letter_index(pozitie.second);
    } else {
        i_rege_negru = pozitie.first;
        j_rege_negru = letter_index(pozitie.second);
    }

    this->scor = (this->culoare)? 900 : -900;
}

vector<pair<int, char>> Rege::verifica_posibile(Piesa*** board){
    // cam ca la pion, dar si in spate si in fata, trebuie verificat si daca nu se intra in sah
    //caz special, se apeleaza verifica_roacada si se adauga cumva in vectorul de posibilitati??
    vector<pair<int, char>> temp{};
        // cout << "\n------\n";
    // merge in fata/spate
    if ((this->pozitie.first - 1 >= 1)){
        if ((board[this->pozitie.first - 1][letter_index(this->pozitie.second)]->check(this->culoare) == 1 || 
        	(board[this->pozitie.first - 1][letter_index(this->pozitie.second)]->check(this->culoare) == 2)) && 
        	board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first - 1, this->pozitie.second)))
            temp.push_back(make_pair(this->pozitie.first - 1, this->pozitie.second));
    }
    if (this->pozitie.first + 1 <= 8) {
        if ((board[this->pozitie.first + 1][letter_index(this->pozitie.second)]->check(this->culoare) == 1 || 
        	(board[this->pozitie.first + 1][letter_index(this->pozitie.second)]->check(this->culoare) == 2)) && 
        	board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first + 1, this->pozitie.second)))
            temp.push_back(make_pair(this->pozitie.first + 1, this->pozitie.second));
    }

    //diagonala
    if (letter_index(this->pozitie.second) - 1 >= 1 && this->pozitie.first - 1 >= 1){
        if (((board[this->pozitie.first - 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 1) || 
        	(board[this->pozitie.first - 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 2)) && 
        	board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first - 1, this->pozitie.second - 1)))
            temp.push_back(make_pair(this->pozitie.first - 1, index_letter(letter_index(this->pozitie.second) - 1)));
    }
    if (letter_index(this->pozitie.second) - 1 >= 1 && this->pozitie.first + 1 <= 8) {
        if (((board[this->pozitie.first + 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 1) || 
        	(board[this->pozitie.first + 1][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 2)) && 
        	board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first + 1, this->pozitie.second - 1)))
            temp.push_back(make_pair(this->pozitie.first + 1, index_letter(letter_index(this->pozitie.second) - 1)));
    }

    //lateral
    if (letter_index(this->pozitie.second) - 1 >= 1){
        if (((board[this->pozitie.first][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 1) || 
        	(board[this->pozitie.first][letter_index(this->pozitie.second) - 1]->check(this->culoare) == 2)) && 
        	board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first, this->pozitie.second - 1)))
            temp.push_back(make_pair(this->pozitie.first, index_letter(letter_index(this->pozitie.second) - 1)));
    }
    if (letter_index(this->pozitie.second) + 1 <= 8){
        if (((board[this->pozitie.first][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 1) || 
        	(board[this->pozitie.first][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 2)) && 
        	board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first, this->pozitie.second + 1)))
        temp.push_back(make_pair(this->pozitie.first, index_letter(letter_index(this->pozitie.second) + 1)));
    }

    if (letter_index(this->pozitie.second) + 1 <= 8 && this->pozitie.first + 1 <= 8){
        if (((board[this->pozitie.first + 1][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 1) || 
            (board[this->pozitie.first + 1][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 2)) && 
            board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first + 1, this->pozitie.second + 1)))
            temp.push_back(make_pair(this->pozitie.first + 1, index_letter(letter_index(this->pozitie.second) + 1)));
    }
    if (letter_index(this->pozitie.second) + 1 <= 8 && this->pozitie.first - 1 >= 1) {
        if (((board[this->pozitie.first - 1][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 1) || 
            (board[this->pozitie.first - 1][letter_index(this->pozitie.second) + 1]->check(this->culoare) == 2)) && 
            board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first - 1, this->pozitie.second + 1)))
            temp.push_back(make_pair(this->pozitie.first - 1, index_letter(letter_index(this->pozitie.second) + 1)));
    }
    return temp;

}

bool Rege::verifica_rocada(char tip, Piesa*** board){
    if (this->pozitie.second != 'e') {
        return 0;
    }
    //trebuie verificat daca trece prin sah sau ajunge in sah sau este in sah regele
    if(tip == 'm'){ //rocada mica
        bool gol = true;
        for(int i = 1; i <= 2; i++){
            if(board[this->pozitie.first][letter_index(this->pozitie.second) + i]->check(this->culoare) != 1)
                gol = false;
        }
        if (!board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first, this->pozitie.second - 1))) {
            gol = false;
        }
        if(gol == true && this->prima == true && board[this->pozitie.first][letter_index('h')]->prima == true)
            return 1; //daca tura nu e la locul ei nu merge
        return 0;
    } 
    else {// adica 'M', rocada mare
        bool gol = true;
        for(int i = 1; i <= 3; i++){
            if(board[this->pozitie.first][letter_index(this->pozitie.second) - i]->check(this->culoare) != 1)
                gol = false;
        }
        if (!board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first, this->pozitie.second - 1)) || 
        	!board[this->pozitie.first][letter_index(this->pozitie.second)]->mutareSah(board, make_pair(this->pozitie.first, this->pozitie.second - 2))) {
            gol = false;
        }
        if(gol == true && this->prima == true && board[this->pozitie.first][letter_index('a')]->prima == true)
            return 1; //daca tura nu e la locul ei nu merge
        return 0;
    }
}                    