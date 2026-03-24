# 🔢 Problema das K-Partições (Backtracking Recursivo em C++)

## 📌 Descrição do Problema

Este projeto implementa uma solução para o **Problema das K-Partições**, utilizando **recursão com backtracking**.

Dado um vetor de inteiros positivos `V`, o objetivo é:

* Dividir os elementos em **K subconjuntos disjuntos**
* Garantir que:

  * Todos os elementos sejam utilizados
  * Cada subconjunto tenha **a mesma soma**

O programa testa diferentes valores de `K` e exibe todas as partições válidas encontradas.

---

## 🧠 Estratégia da Solução

A abordagem utilizada é baseada em:

* **Recursão**
* **Backtracking (tentativa e erro com retorno)**

### Passos principais:

1. Calcular a soma total do vetor
2. Verificar se é possível dividir em `K` subconjuntos:

   * A soma total deve ser divisível por `K`
3. Definir a soma alvo de cada subconjunto:

   ```
   soma_alvo = soma_total / K
   ```
4. Distribuir os elementos recursivamente:

   * Tentando adicionar cada elemento em um subconjunto
   * Recuando (backtracking) caso a escolha não leve a uma solução válida

---

## 📥 Exemplo de Entrada

```
V = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 }
```

---

## 📤 Exemplos de Saída

### ✔ K = 2 (Soma = 30)

```
S1 = { 5, 3, 8, 4, 6, 4 }
S2 = { 7, 3, 5, 12, 2, 1 }
```

---

### ✔ K = 3 (Soma = 20)

```
S1 = { 2, 1, 3, 4, 6, 4 }
S2 = { 7, 5, 8 }
S3 = { 3, 5, 12 }
```

---

### ✔ K = 4 (Soma = 15)

```
S1 = { 1, 4, 6, 4 }
S2 = { 2, 5, 8 }
S3 = { 12, 3 }
S4 = { 7, 3, 5 }
```

---

### ✔ K = 5 (Soma = 12)

```
S1 = { 2, 6, 4 }
S2 = { 8, 4 }
S3 = { 3, 1, 5, 3 }
S4 = { 12 }
S5 = { 7, 5 }
```

---

## 🔁 Explicação da Recursão

A função recursiva tenta construir os subconjuntos passo a passo.

### Estruturas utilizadas:

* `subsetSum[K]`: armazena a soma atual de cada subconjunto
* `usado[]`: indica quais elementos já foram utilizados
* `subsets[K]`: armazena os elementos de cada subconjunto

### Funcionamento:

Para cada elemento:

1. Tenta adicioná-lo a um subconjunto
2. Verifica se não ultrapassa a soma alvo
3. Chama recursivamente para o próximo elemento
4. Se não funcionar:

   * Remove o elemento (backtracking)
   * Tenta outra possibilidade

---

## ⚡ Otimizações Implementadas

* ✔ **Poda (Pruning)**: evita continuar caminhos inválidos
* ✔ **Evita simetria**: reduz soluções redundantes
* ✔ **Backtracking eficiente**: evita recomputação completa

---

## 📊 Complexidade

### Pior caso:

O algoritmo possui complexidade exponencial:

```
O(K^N)
```

Onde:

* `N` = número de elementos do vetor
* `K` = número de subconjuntos

### Observações:

* O problema é **NP-completo**
* As otimizações reduzem significativamente o tempo prático
* Ainda assim, o crescimento é exponencial para entradas grandes

---

## 🛡️ Tratamento de Erros

O programa trata:

* ❌ `K = 0`
* ❌ Soma total não divisível por `K`
* ❌ Casos impossíveis de particionamento

---

## 📚 Conceitos Envolvidos

* Recursão
* Backtracking
* Problemas combinatórios
* Complexidade de algoritmos
* Poda em árvores de decisão

---

## 👩‍💻 Autora

Projeto desenvolvido por **Nicole Santarosa** como parte de estudos em **Ciência da Computação**.

---
