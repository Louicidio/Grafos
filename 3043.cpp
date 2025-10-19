#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 20;

int num_alunos;
bool matrizadj_inimizades[MAX][MAX]; // Matrizs adj de inimizades
bool atual[MAX]; // Alunos na comissao atual
int maior; // Tamanho da maior comissao encontrada

void dfs_busca_comissao(int idx, int count) {

	// Caso base, chegou no fim dos alunos
	if (idx == num_alunos) {
		maior = max(maior, count);
		return;
	}

	// Verifica se o aluno idx pode ser incluido na comissao
	bool inclui = true;
	for (int i = 0; i < idx; i++) {
		if (atual[i] && matrizadj_inimizades[idx][i] == true) {
			inclui = false;
			break;
		}
	}

	// DFS p gerar subconjuntos validos da comissao
	if (inclui) {
		atual[idx] = true;
		dfs_busca_comissao(idx + 1, count + 1); // Inclui aluno idx
		atual[idx] = false;
	}

	dfs_busca_comissao(idx + 1, count); // Nao inclui aluno idx
}

int main() {
	int test = 1;

	while (cin >> num_alunos && num_alunos != 0) {
	    
		// Inicializa matriz de inimizades
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				matrizadj_inimizades[i][j] = false;
			}
		}

    // Inicializa vetor atual
		for (int i = 0; i < MAX; i++) {
			atual[i] = false;
		}
        
    // Para cada aluno, le a lista dos alunos com os quais tem inimizade
		for (int i = 0; i < num_alunos; i++) {
			int x;
			while (cin >> x && x != 0) {
				x--;
				matrizadj_inimizades[i][x] = true; // inimizade i -> x
				matrizadj_inimizades[x][i] = true; // inimizade x -> i
			}
		}

		maior = 0;
		dfs_busca_comissao(0, 0);

		cout << "Teste " << test++ << endl;
		cout << maior << endl << endl;
	}

	return 0;
}
