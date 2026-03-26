/** =======================================================================
 *  Problema das K-Partições — Solução Recursiva com Backtracking
 *  =======================================================================
 *
 * DESCRIÇÃO:
 *   Dado um vetor V de inteiros positivos, o programa encontra todos
 *   os valores de K para os quais V pode ser dividido em K subconjuntos
 *   disjuntos com a mesma soma, cobrindo todos os elementos de V.
 *
 * ESTRATÉGIA:
 *   1. Calcula a soma total de V.
 *   2. Para cada K de 2 até N, verifica se total % K == 0.
 *      Se sim, alvo = total / K.
 *   3. Ordena V em ordem decrescente (melhora a poda).
 *   4. Usa backtracking para alocar cada elemento em um dos K "buckets",
 *      sem ultrapassar o alvo em nenhum bucket.
 *   5. Podas aplicadas:
 *      a) Elemento + soma atual do bucket > alvo → não tenta.
 *      b) Buckets com mesma soma atual são equivalentes → pula duplicatas
 *         (poda de simetria via conjunto de somas já tentadas).
 *      c) O maior elemento do vetor não pode exceder o alvo.
 *
 * COMPLEXIDADE DE PIOR CASO — Notação O:
 *   Sem podas: O(k^n)
 *     Para cada um dos n elementos, há até k escolhas de bucket.
 *   Com poda de simetria: O(k! · k^(n-k))
 *     As primeiras k posições têm permutações eliminadas; as restantes ainda
 *     podem ramificar em k, mas a poda de faixa (soma > alvo) reduz
 *     drasticamente o espaço real de busca.
 *   Na prática, para entradas onde a partição existe, o algoritmo encontra
 *   a solução muito antes de explorar a árvore completa.
 *
 * =========================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <stdexcept>
#include <string>
#include <Windows.h>

using namespace std;

// ─────────────────────────────────────────────────────────────-──-──-──-──
//  Função recursiva principal: backtracking
// ───────────────────────────────────────────────────────────────-──-──-──-

/**
 * Tenta distribuir os elementos de V[idx..n-1] nos k buckets, respeitando
 * o limite 'target' para cada bucket.
 *
 * @param V       Vetor de entrada (ordenado decrescentemente)
 * @param parts   Vetor de partições sendo construídas
 * @param sums    Soma acumulada de cada partição
 * @param idx     Índice do próximo elemento a distribuir
 * @param k       Número de partições
 * @param target  Soma alvo de cada partição
 * @return true se uma distribuição válida foi encontrada
 *
 * Caso base: idx == V.size() → todos alocados; verifica se todas as somas
 * batem com target.
 * Caso recursivo: tenta cada bucket i para V[idx].
 */

 // Caso base
bool backtrack(const vector<int>& V, vector<vector<int>>& parts, vector<int>& sums, int idx, int k, int target) {
    if (idx == (int)V.size()) {
        for (int i = 0; i < k; i++)
            if (sums[i] != target) return false;
        return true;
    }

    int elem = V[idx];

    // Conjunto de somas já usadas neste nível → evita explorar buckets com o mesmo estado atual (poda de simetria)
    set<int> triedSums;

    // Caso recursivo
    for (int i = 0; i < k; i++) {

        // Poda 1: adição ultrapassaria o alvo
        if (sums[i] + elem > target) continue;

        // Poda 2: bucket já tentado com esta soma → simétrico
        if (triedSums.count(sums[i])) continue;

        triedSums.insert(sums[i]);

        // Escolhe o bucket i para elem
        sums[i] += elem;
        parts[i].push_back(elem);

        if (backtrack(V, parts, sums, idx + 1, k, target))
            return true;   // Solução encontrada; propaga true

        // Backtrack: desfaz a escolha
        sums[i] -= elem;
        parts[i].pop_back();
    }

    return false; // Nenhum bucket levou a uma solução válida
}

// ────────────────────────────────────────────────────────────────────────
//  Validação de entrada
// ────────────────────────────────────────────────────────────────────────

/** Verifica se o vetor é válido para o problema.
    @throws invalid_argument em caso de vetor vazio ou elemento não-positivo. */
void validarEntrada(const vector<int>& V) {
    if (V.empty())
        throw invalid_argument("Erro: o vetor não pode ser vazio.");

    for (int x : V)
        if (x <= 0)
            throw invalid_argument(
                "Erro: todos os elementos devem ser inteiros positivos. "
                "Valor inválido: " + to_string(x));
}

// ────────────────────────────────────────────────────────────────────────
//  Orquestrador: testa todos os K válidos
// ────────────────────────────────────────────────────────────────────────

// Para cada K de 2 até n, verifica se V admite K-partição com subconjuntos de mesma soma e imprime as partições encontradas.
void encontrarKParticoes(const vector<int>& V) {
    validarEntrada(V);

    int n = (int)V.size();
    int total = accumulate(V.begin(), V.end(), 0);

    // Imprime o vetor original
    cout << "V = { ";
    for (int i = 0; i < n; i++)
        cout << V[i] << (i < n - 1 ? ", " : " }");
    cout << "\n\n";

    // Ordena decrescente: elementos maiores primeiro aceleram a poda
    vector<int> sortedV = V;
    sort(sortedV.begin(), sortedV.end(), greater<int>());

    bool algumEncontrado = false;

    for (int k = 2; k <= n; k++) {

        // Poda global: total deve ser divisível por k
        if (total % k != 0) continue;

        int target = total / k;

        // Poda global: o maior elemento não pode exceder o alvo
        if (sortedV[0] > target) continue;

        // Inicializa buckets e somas
        vector<vector<int>> parts(k);
        vector<int> sums(k, 0);

        if (backtrack(sortedV, parts, sums, 0, k, target)) {
            algumEncontrado = true;
            cout << "V pode ser particionado em " << k << ".\n";
            cout << "Cada subconjunto tem soma = " << target << "\n";
            for (int i = 0; i < k; i++) {
                cout << "S" << (i + 1) << " = { ";
                for (int j = 0; j < (int)parts[i].size(); j++)
                    cout << parts[i][j]
                    << (j < (int)parts[i].size() - 1 ? ", " : " }");
                cout << "\n";
            }
            cout << "\n";
        }
    }

    if (!algumEncontrado)
        cout << "Nenhuma K-particão válida foi encontrada para este vetor.\n\n";
}

// ────────────────────────────────────────────────────────────────────────
//  main
// ────────────────────────────────────────────────────────────────────────
int main() {
	SetConsoleOutputCP(CP_UTF8);

    try {
        vector<int> V = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 };
        encontrarKParticoes(V);

        // Vetor onde nenhuma partição é possível
        cout << "--- Teste: sem partição válida ---\n";
        vector<int> V2 = { 1, 2, 4 };
        encontrarKParticoes(V2);

        // Vetor simples com 2-partição óbvia
        cout << "--- Teste: partição simples ---\n";
        vector<int> V3 = { 1, 1, 1, 1, 2, 2 };
        encontrarKParticoes(V3);
    }

    catch (const invalid_argument& e) {
        cerr << e.what() << "\n";
        return 1;
    }
    catch (const exception& e) {
        cerr << "Erro inesperado: " << e.what() << "\n";
        return 2;
    }

    return 0;
}