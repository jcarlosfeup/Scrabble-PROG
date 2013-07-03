#ifndef JOGO_H_
#define JOGO_H_

#include <iostream>
#include <string>
#include <vector>
#include "Peca.h"
#include "Jogador.h"
#include "Celula.h"
#include "Tabuleiro.h"
#include "Pontuacao.h"

using std::string;
using std::vector;

class Jogo
{
private:
	vector<string> dicionario;
	vector<Peca> baralho;
	vector<Pontuacao> rank;
	vector<Jogador> jogadores;
	Tabuleiro tabuleiro;
	friend int main();
	vector<int> vec_ponto;
	vector<string> nome_j;



public:
	Jogo();
	~Jogo();
	void add_jogador(Jogador player);
	void show_tabuleiro();
	void update_jogos(string filename);
	bool ver_tabuleiro(int ver, int hor, char ori);
	void carrega_vec_jogo(string filename);
	void mostrar_nome_jogo();
	void nome_jogo(string n);
	string devolve_no_jogo(int i);
	void cria_dicionario(string filename);
	void cria_baralho(string filename);
	// void cria_tabuleiro(string filename);
	Tabuleiro GetTabuleiro();
	void SetTabuleiro(Tabuleiro tb);
	bool verifica_palavra(string palavra);
	bool verifica_tamanho(string palavra, int pos_horizontal, int pos_vertical, char direccao);
	bool verifica_inicio();
	void completa_mao(int i);
	bool verifica_posiblidade(string palavra, int pos_horiz, int pos_vert, char direc);
	void troca_mao(string letras_trocar, int i);
	void actualiza_pontuacao(int actualizacao, int i);
	bool verif_pal_tabuleiro(string palavra, int pos_horiz, int pos_vert, char direc, int i);
	int pont_palavra(string palavra, int pos_horizontal, int pos_vertical, char orientacao);
	vector<Peca> cria_mao();
	string mostra_mao(int i);
	void criar_ranking(string filename);
	void update_best_scores(Pontuacao s);
	void mostrar_ranking();
	void guarda_ranking(string filename, unsigned int n_best);
	void coloca_palavra(string palavra, int pos_horiz, int pos_vert, char direc, vector<Peca> & mao);
	Jogador & acesso_jogador(int i);
	void guardar_jogo(string filename);
	int terminar();
	int pontos_mao(int i);
	void carregar_jogo(string filename);

};
#endif
