#include "alfa-beta.h"
#include "piese.h"

#include <iostream>
#include <vector>
#include <cstring>

#define inf 10000
#define minf -10000

using namespace std;

Node::Node(int s, int a, int b, pair <int, int>  st, pair <int, char> fn, char c) : 
	scor(s), alfa(a), beta(b), start(st), finish(fn), captured(c) {}

void generator(Tree *res, Piesa*** board, bool color, int depth, int level, bool curent) // initial level = 1
{
	if(depth >= 1)
	{
		for (int i = 1; i <= 8; i++){
			for (int j = 1; j <= 8; j++){
				//Aici facem verificarile posibile pe care le poate face pionii/pionul daca este aproape de liniile 1/8 si le inregistram in acei 2 vectori creati mutari&plecare
				vector<pair<int, char>> temp{};
				if (curent == board[i][j]->culoare)
					temp = board[i][j]->verifica_posibile(board);
				
				for(int k = 0; k < temp.size(); k++)
				{
					sz += 1;
					if(temp[k].first == -1 && temp[k].second == '\0'){
						(*res)->childs.push_back(new Node((*res)->scor + (board[i][j]->culoare)? -900 : 900, // gresit
														((!color && level % 2) || (color && (level % 2 == 0))? inf : minf),
														((!color && level % 2) || (color && (level % 2 == 0))? minf : inf),
														make_pair(i, j),
														temp[k],
														'r'));
					} else {
						(*res)->childs.push_back(new Node((*res)->scor + board[temp[k].first][letter_index(temp[k].second)]->scor, // gresit
														((!color && level % 2) || (color && (level % 2 == 0))? inf : minf),
														((!color && level % 2) || (color && (level % 2 == 0))? minf : inf),
														make_pair(i, j),
														temp[k],
														board[temp[k].first][letter_index(temp[k].second)]->tip));

						char t = board[temp[k].first][letter_index(temp[k].second)]->tip;
						bool c = board[temp[k].first][letter_index(temp[k].second)]->culoare;
						
						board[i][j]->muta(make_pair(i, index_letter(j)), temp[k], board);
						generator(&((*res)->childs[k]), board, color, depth-1, level+1, !curent);
						board[temp[k].first][letter_index(temp[k].second)]->muta(temp[k], make_pair(i, index_letter(j)), board);
						
						delete board[temp[k].first][letter_index(temp[k].second)];
						switch(t)
						{
							case 'p':
								board[temp[k].first][letter_index(temp[k].second)] = new Pion(temp[k], c);
								break;
							case 'n':
								board[temp[k].first][letter_index(temp[k].second)] = new Nebun(temp[k], c);
								break;
							case 't':
								board[temp[k].first][letter_index(temp[k].second)] = new Tura(temp[k], c);
								break;
							case 'c':
								board[temp[k].first][letter_index(temp[k].second)] = new Cal(temp[k], c);
								break;
							case 'q':
								board[temp[k].first][letter_index(temp[k].second)] = new Regina(temp[k], c);
								break;
							case 'r':
								board[temp[k].first][letter_index(temp[k].second)] = new Rege(temp[k], c);
								break;
							default:
								board[temp[k].first][letter_index(temp[k].second)] = new Piesa(temp[k]);
								break;
						}
					}
					
				}
			}
		}
		
	}
}

int alpha_beta(Node* node, int depth, int alpha, int beta, int player, char mutari[]){
	int eva, maxEva;
	char tmp[5];
	if (depth == 0 || node->childs.size() == 0) {
		char tmp[5];
		tmp[0] = node->start.second + '`';
		tmp[1] = node->start.first + '`';
		tmp[2] = node->finish.second;
		tmp[3] = node->finish.first + '`';
		strcpy(mutari, tmp);
		cout << node->scor << endl;
		return node->scor;
	}
	// cout << node->childs.size() << endl;;

	if (player) {
		maxEva = minf;
		for (int i = 0; i < node->childs.size(); i++) {
			eva = alpha_beta(node->childs[i], depth - 1, alpha, beta, -1, mutari);
			maxEva = max(maxEva, eva);
			alpha = max(maxEva, alpha);
			tmp[0] = node->childs[i]->start.second + '`';
			tmp[1] = node->childs[i]->start.first + '0';
			tmp[2] = node->childs[i]->finish.second;
			tmp[3] = node->childs[i]->finish.first + '0';
			if (beta <= alpha){
				break;
			}
		}
		strcpy(mutari, tmp);
		return maxEva;
	} else {
		int minEva = inf;
		for (int i = 0; i < node->childs.size(); i++) {
			eva = alpha_beta(node->childs[i], depth - 1, alpha, beta, 1, mutari);
			minEva = min(minEva, eva);
			beta = min(minEva, beta);
			tmp[0] = node->childs[i]->start.second + '`';
			tmp[1] = node->childs[i]->start.first + '0';
			tmp[2] = node->childs[i]->finish.second;
			tmp[3] = node->childs[i]->finish.first + '0';
			if (beta <= alpha) {
				break;
			}
		}
		strcpy(mutari, tmp);
		return minEva;
	}
}