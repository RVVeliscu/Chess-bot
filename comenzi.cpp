#include <cstdio>
#include <cstdlib>
#include <bits/stdc++.h>
#include "piese.h"

#define Alb true
#define Negru false

using namespace std;

bool culoare_de_verificat = Negru;
bool e_la_rand = Alb;
int counterMutari = 0;
in_sah Alb_in_sah, Negru_in_sah;
int three_check_alb = 0, three_check_negru = 0;

typedef struct queue_mutari {
    char mutare[7][5];
    int lastIndex = -1;
}queue_mutari;

queue_mutari bufferAlb;
queue_mutari bufferNegru;

class Moves{
    public:
        Moves(){

        }

        //muta pentru calculator dand de ex comanda move e4e5 pentru xboard
        void move(char initialX, int initialY, char finalX, int finalY){
            cout << "move " << initialX << initialY << finalX << finalY << "\n";
        }
};

class Commands{
    public:
        char command[20];

        Commands(){

        }

        Commands(char command[20]){
            strncpy(this->command, command, 20);
        }

        //aici bagam toate comenzile ce pot veni de la xboard sau trebuiesc date la xboard
        static void parse_instruction(char instruction[1024]){
            if (strstr(instruction, "resign")){
                cout << "resign\n";
            }

            if (strstr(instruction, "protover")){
                cout << "feature san=0 sigint=0\n";
            }

            if (strstr(instruction, "black")){
                culoare_de_verificat = Negru;
            }

            if (strstr(instruction, "white")){
                culoare_de_verificat = Alb;
            }
        }
};

//Functia care muta pentru calculator bazandu-se pe miscarile posibile din matrice
Piesa*** go_instruction(Piesa*** chessboard, vector<pair<int, char>> en_passant_mutare, vector<pair<int, int>> en_passant_plecare){
    Moves move;
    //Schimbam culoarea deoarece dupa ce am facut noi mutarea urmeaza mutarea culorii opuse si cream 2 vectori pentru posibilele mutari
    e_la_rand = !e_la_rand;
    counterMutari++;
    vector<pair<int, char>> mutari{};
    vector<pair<int, int>> plecare{};
    //Copiem en_passant_mutare si en_passant_plecare in vectorii mutari si plecare
    for (int i = 0; i < en_passant_mutare.size(); ++i){
    	mutari.push_back(en_passant_mutare[i]);
    	plecare.push_back(en_passant_plecare[i]);
    }

    for (size_t i = 1; i <= 8; i++){
        for (size_t j = 1; j <= 8; j++){
        	//daca exista posibilitatea de a face rocada o fac
            if(culoare_de_verificat == chessboard[i][j]->culoare && chessboard[i][j]->tip == 'r')
            {
                if(chessboard[i][j]->verifica_rocada('m', chessboard))
                {
                    //afiseaza ca faci rocada mica
                    cout << "move " << 'e' << i << 'g' << i << '\n';
                    //rege la linia i, coloana g
                    chessboard[i][j]->muta(make_pair(i, index_letter(j)), make_pair(i, 'g'), chessboard);
                    //tura la linia i, coloana f
                    chessboard[i][8]->muta(make_pair(i, index_letter(8)), make_pair(i, 'f'), chessboard);
                    e_la_rand = !e_la_rand;
                    return chessboard;
                }

                if(chessboard[i][j]->verifica_rocada('M', chessboard))
                {
                    //afiseaza ca faci rocada mare
                    cout << "move " << 'e' << i << 'c' << i << '\n';
                    //rege la linia i, coloana c
                    chessboard[i][j]->muta(make_pair(i, index_letter(j)), make_pair(i, 'c'), chessboard);
                    //tura la linia i, coloana d
                    chessboard[i][1]->muta(make_pair(i, index_letter(1)), make_pair(i, 'd'), chessboard);
                    e_la_rand = !e_la_rand;
                    return chessboard;
                }
            }

            vector<pair<int, char>> temp{};
            //Aici facem verificarile posibile pe care le poate face pionii/pionul daca este aproape de liniile 1/8 si le inregistram in acei 2 vectori creati mutari&plecare
            if (culoare_de_verificat == chessboard[i][j]->culoare)
                temp = chessboard[i][j]->verifica_posibile(chessboard);

            for (size_t k = 0; k < temp.size(); k++){
                mutari.push_back(temp[k]);
                plecare.push_back(make_pair(i, j));
            }
        }
    }
    //Aici verificam mai intai daca avem mutari posibile pentru a face mutarea calculatorului fie dam resign in caz contrar
    if (mutari.size() != 0 && plecare.size() != 0){
    	int aux = rand() % mutari.size();
        if(mutari[aux].first == 8 && chessboard[plecare[aux].first][plecare[aux].second]->tip == 'p'){
            //fac upgrade la regina
            cout << index_letter(plecare[aux].second) << plecare[aux].first << mutari[aux].second << mutari[aux].first <<"q\n";
        } else {
            move.move(index_letter(plecare[aux].second), plecare[aux].first, mutari[aux].second, mutari[aux].first);
        }
        in_sah *culoare_in_sah = (culoare_de_verificat)? &Alb_in_sah :&Negru_in_sah;
        if (culoare_in_sah->sah){
        	culoare_in_sah->i = 0;
            culoare_in_sah->j = 0;
            culoare_in_sah->tip = '0';
            culoare_in_sah->sah = false;
        }
        chessboard[plecare[aux].first][plecare[aux].second]->muta(make_pair(plecare[aux].first, index_letter(plecare[aux].second)), make_pair(mutari[aux].first, mutari[aux].second), chessboard);
        if (e_la_rand == Alb) { 
            bufferAlb.lastIndex = (bufferAlb.lastIndex + 1) % 6;
            bufferAlb.mutare[bufferAlb.lastIndex][0] = ('0' + plecare[aux].second);
            bufferAlb.mutare[bufferAlb.lastIndex][1] = ('0' + plecare[aux].first); 
            bufferAlb.mutare[bufferAlb.lastIndex][2] = mutari[aux].second; 
            bufferAlb.mutare[bufferAlb.lastIndex][3] = ('0' + mutari[aux].first); 
 
        } else {
            bufferNegru.lastIndex = (bufferNegru.lastIndex + 1) % 6;
            bufferNegru.mutare[bufferNegru.lastIndex][0] = ('0' + plecare[aux].second); 
            bufferNegru.mutare[bufferNegru.lastIndex][1] = ('0' + plecare[aux].first); 
            bufferNegru.mutare[bufferNegru.lastIndex][2] = mutari[aux].second; 
            bufferNegru.mutare[bufferNegru.lastIndex][3] = ('0' + mutari[aux].first); 
        }
        e_la_rand = !e_la_rand;
    }
    else{
        cout << "resign\n";
    }
    return chessboard;
}

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

int main()
{
    for (int i = 1; i <= 10; i++) {
        strcpy(bufferAlb.mutare[i], "----");
        strcpy(bufferNegru.mutare[i], "----");
    }
    char *resigne = (char *)malloc(7 * sizeof(*resigne));
    strcpy(resigne, "resign");
    char *variante = (char *)malloc(15 * sizeof(*variante));
    strcpy(variante, "variant 3check");
    Commands resign(resigne), variant(variante);
    free(variante);
    free(resigne);

    srand(time(0)); //dau seed pentru partea de randomizare

    //Alocam memorie pentru tabla de joc si setam piesele pe ea.
    Piesa ***chessboard = new Piesa **[10];
    for (size_t i = 0; i < 10; i++){
        chessboard[i] = new Piesa *[10];
    }
    set_board(chessboard);
    Moves move;
    char instruction[1024];
    char mutari[1024];

    //Acest while este partea principala a codului, aici se primesc instructiunile si se fac toate comenzile necesare jocului.
    while (1){
        if (three_check_negru == 3 || three_check_alb == 3){
            cout << "resign" << endl;
        }
        if (strcmp(bufferAlb.mutare[5], "----") != 0) {
            if (strcmp(bufferAlb.mutare[1], bufferAlb.mutare[3]) == 0 && strcmp(bufferAlb.mutare[3], bufferAlb.mutare[5]) == 0) {
                cout << "offer draw" << endl;
            }
        }
        if (strcmp(bufferNegru.mutare[5], "----") != 0) {
            if (strcmp(bufferNegru.mutare[1], bufferNegru.mutare[3]) == 0 && strcmp(bufferNegru.mutare[3], bufferNegru.mutare[5]) == 0) {
                cout << "offer draw" << endl;
            }
        }
        //Primim instructiunile fie scrise in terminal fie transmise prin intermediul xboard-ului
        cin.getline(instruction, 1024);
        //Verificam daca in stringul de mai sus nu este vre-o instructiune care se afla in clasa Commands
        Commands::parse_instruction(instruction);
        //Aici verificam daca al doilea caracter din instructiune este o cifra pentru a face in matricea creata de noi aceleasi mutari pe care le facem si in xboard
        if (isdigit(instruction[1])){
            if (e_la_rand == Alb) { 
                bufferAlb.lastIndex = (bufferAlb.lastIndex + 1) % 6;
                strcpy(bufferAlb.mutare[bufferAlb.lastIndex], instruction); 
            } else {
                bufferNegru.lastIndex = (bufferNegru.lastIndex + 1) % 6;
                strcpy(bufferNegru.mutare[bufferNegru.lastIndex], instruction); 
            }
            counterMutari++;
        	vector<pair<int, char>> en_passant_mutare{};
    		vector<pair<int, int>> en_passant_plecare{};
    		//Verificam daca piesa curenta este pion si daca face prima mutare
        	if ((chessboard[instruction[1] - '0'][letter_index(instruction[0])]->tip == 'p') && (chessboard[instruction[1] - '0'][letter_index(instruction[0])]->prima)){
        		//Verificam daca este pe o coloana mai mare decat 1 pentru a verifica in stanga
                if (letter_index(instruction[0]) > 1){
        			//Verificam daca tipul piesei din stanga piesei noastre mutate este de culoare diferita si este pion
                    if ((chessboard[instruction[3] - '0'][letter_index(instruction[0])-1]->tip == 'p') && 
        				(chessboard[instruction[3] - '0'][letter_index(instruction[0])-1]->culoare != chessboard[instruction[1] - '0'][letter_index(instruction[0])]->culoare)){
        				//Introducem in en_passant_mutare media aritmetica a celor 2 piese pentru a ne da coloana necesara noua si deasemenea 
        				//introducem si in vectorul en_passant_plecare pozitia pionului pe care il mutam
        				en_passant_mutare.push_back(make_pair(((instruction[1] - '0')+(instruction[3]-'0'))/2, instruction[0]));
        				en_passant_plecare.push_back(make_pair(instruction[3] - '0', letter_index(instruction[0] - 1)));
        			}
        		}
        		//Verificam daca este pe o coloana mai mica decat 8 pentru a verifica in dreapta
                if (letter_index(instruction[0]) < 8){
        			//Verificam daca tipul piesei din stanga piesei noastre mutate este de culoare diferita si este pion
                    if ((chessboard[instruction[3] - '0'][letter_index(instruction[0])+1]->tip == 'p') && 
        				(chessboard[instruction[3] - '0'][letter_index(instruction[0])+1]->culoare != chessboard[instruction[1] - '0'][letter_index(instruction[0])]->culoare)){
        				//De asemenea introducem in en_passant_mutare si in en_passant_plecare pozitiile necesare la fel ca mai sus
        				en_passant_mutare.push_back(make_pair(((instruction[1] - '0')+(instruction[3]-'0'))/2, instruction[0]));
        				en_passant_plecare.push_back(make_pair(instruction[3] - '0', letter_index(instruction[0] + 1)));
        			}
        		}
        	}
            //aceasta instructiune chessboar[i][j]->muta este pentru a marca in matrice mutarea
            if ((instruction[0] == 'e' && (instruction[1] == '8' || instruction[1] == '1') && (instruction[2] == 'g' || instruction[2] == 'c')) && 
                chessboard[instruction[1] - '0'][letter_index(instruction[0])]->tip == 'r'){
                chessboard[instruction[1] - '0'][letter_index(instruction[0])]->muta(make_pair(instruction[1] - '0', instruction[0]), make_pair(instruction[3] - '0', instruction[2]), chessboard);
                if (instruction[2] == 'g'){
                    chessboard[instruction[1] - '0'][letter_index('h')]->muta(make_pair(instruction[1] - '0', 'h'),make_pair(instruction[1] - '0', 'f'), chessboard);
                }else
                    chessboard[instruction[1] - '0'][letter_index('a')]->muta(make_pair(instruction[1] - '0', 'a'),make_pair(instruction[1] - '0', 'd'), chessboard);
            }else
                chessboard[instruction[1] - '0'][letter_index(instruction[0])]->muta(make_pair(instruction[1] - '0', instruction[0]), make_pair(instruction[3] - '0', instruction[2]), chessboard);
            if(strlen(instruction) == 5 && (instruction[3] - '0' == 8 || instruction[3] - '0' == 1)){
                //fac upgrade
                Pion::upgrade(instruction[4], make_pair(instruction[3] - '0', instruction[2]), chessboard);
            }
            vector<pair<int, char>> ret{};
            ret = chessboard[instruction[3] - '0'][letter_index(instruction[2])]->verifica_posibile(chessboard);
            if (ret.size() != 0){
                if (ret.front().first == -1){
                    in_sah *culoare_in_sah = (culoare_de_verificat)? &Alb_in_sah :&Negru_in_sah;
                    if (culoare_de_verificat){
                        three_check_alb++;
                    }else
                        three_check_negru++;
                    culoare_in_sah->i = instruction[3] - '0';
                    culoare_in_sah->j = letter_index(instruction[2]);
                    culoare_in_sah->tip = chessboard[instruction[3] - '0'][letter_index(instruction[2])]->tip;
                    culoare_in_sah->sah = true;
                }
            }
            chessboard = go_instruction(chessboard, en_passant_mutare, en_passant_plecare);
        }
        else if ((e_la_rand == culoare_de_verificat) && (strstr(instruction, "go"))){
            chessboard = go_instruction(chessboard, vector<pair<int, char>>(), vector<pair<int, int>>());
        }

        if (counterMutari > 50 && neluat && nemutatPion){
            cout << "offer draw\n";
        }

        //Instructiunea new unde stergem matricea existenta si cream alta noua
        if (strstr(instruction, "new")){
            chessboard = new_game(chessboard);
        }
           
        if (strstr(instruction, "force")){
            while (2){
                //Citim instructiunile de la tastatura fie date de xboard si le verficam cu clasa Commands
                cin.getline(instruction, 1024);
                Commands::parse_instruction(instruction);
                //Inregistram fiecare miscare in matricea noastra facuta in force mode
                if (isdigit(instruction[1])){
                    vector<pair<int, char>> ret{};
                	if (Negru_in_sah.sah == true && e_la_rand == false){
		                Negru_in_sah.i = 0;
		                Negru_in_sah.j = 0;
		                Negru_in_sah.tip = '0';
		                Negru_in_sah.sah = false;
                	}
                	if (Alb_in_sah.sah == true && e_la_rand == true){
                		Alb_in_sah.i = 0;
		                Alb_in_sah.j = 0;
		                Alb_in_sah.tip = '0';
		                Alb_in_sah.sah = false;
                	}
                    counterMutari++;
                    if (e_la_rand == Alb) { 
                        bufferAlb.lastIndex = (bufferAlb.lastIndex + 1) % 6;
                        strcpy(bufferAlb.mutare[bufferAlb.lastIndex], instruction); 
                    } else {
                        bufferNegru.lastIndex = (bufferNegru.lastIndex + 1) % 6;
                        strcpy(bufferNegru.mutare[bufferNegru.lastIndex], instruction); 
                    }
                    e_la_rand = !e_la_rand;
                    if ((instruction[0] == 'e' && (instruction[1] == '8' || instruction[1] == '1') && (instruction[2] == 'g' || instruction[2] == 'c')) && 
                        chessboard[instruction[1] - '0'][letter_index(instruction[0])]->tip == 'r'){
                        chessboard[instruction[1] - '0'][letter_index(instruction[0])]->muta(make_pair(instruction[1] - '0', instruction[0]), make_pair(instruction[3] - '0', instruction[2]), chessboard);
                        if (instruction[2] == 'g'){
                            chessboard[instruction[1] - '0'][letter_index('h')]->muta(make_pair(instruction[1] - '0', 'h'),make_pair(instruction[1] - '0', 'f'), chessboard);
                        }else
                            chessboard[instruction[1] - '0'][letter_index('a')]->muta(make_pair(instruction[1] - '0', 'a'),make_pair(instruction[1] - '0', 'd'), chessboard);
                    }else
                        chessboard[instruction[1] - '0'][letter_index(instruction[0])]->muta(make_pair(instruction[1] - '0', instruction[0]), make_pair(instruction[3] - '0', instruction[2]), chessboard);
                    if(strlen(instruction) == 5 && (instruction[3] - '0' == 8 || instruction[3] - '0' == 1)){
                        //fac upgrade
                        Pion::upgrade(instruction[4], make_pair(instruction[3] - '0', instruction[2]), chessboard);
                    }
                    ret = chessboard[instruction[3] - '0'][letter_index(instruction[2])]->verifica_posibile(chessboard);
		            if (ret.size() != 0 && ret.front().first == -1){
		            	if (e_la_rand == true)
		            	{
                            three_check_alb++;
			                Alb_in_sah.i = instruction[3] - '0';
			                Alb_in_sah.j = letter_index(instruction[2]);
			                Alb_in_sah.tip = chessboard[instruction[3] - '0'][letter_index(instruction[2])]->tip;
			                Alb_in_sah.sah = true;
		            	}else{
                            three_check_negru++;
		            		Negru_in_sah.i = instruction[3] - '0';
			                Negru_in_sah.j = letter_index(instruction[2]);
			                Negru_in_sah.tip = chessboard[instruction[3] - '0'][letter_index(instruction[2])]->tip;
			                Negru_in_sah.sah = true;
		            	}
		            }
                }

                if (strstr(instruction, "quit")){
                    chessboard = deallocation(chessboard);
                    return 0;
                }
                if (strstr(instruction, "go")){
                    chessboard = go_instruction(chessboard, vector<pair<int, char>>(), vector<pair<int, int>>());
                    break;
                }
                if (strstr(instruction, "new")){
                    chessboard = new_game(chessboard);
                    break;
                }
            }
        }

        //Instructiunea quit in care dealocam memoria din matrice si iesim din while
        if (strstr(instruction, "quit")){
            chessboard = deallocation(chessboard);
            break;
        }
    }
    return 0;
}