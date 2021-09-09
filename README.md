# Universidade Federal de Juiz de Fora

Departamento de Ciência da Computação</br>
Disciplina DCC059 – Teoria dos Grafos – Semestre 2021-1</br>
Alunos:</br>
&emsp;&emsp;&emsp;Gabriel Antonio Esteves Matta</br>
&emsp;&emsp;&emsp;Lucas Esteves dos Reis Salgado</br>
&emsp;&emsp;&emsp;Pedro Paulo Silva Filogônio</br>
&emsp;&emsp;&emsp;Rafaela Fernandes Horta</br>

# Trabalho 01: Funcionalidades básicas em grafos simples

	• TAD para trabalhar com grafos usando lista de adjacência;
    • Arquivo de entrada em formato .txt
    • Arquivo de saída em formato .dot
	• [1] Fecho Transitivo Direto;
    • [2] Fecho Transitivo Indireto;
    • [3] Caminho Minimo entre dois vertices - Dijkstra;
    • [4] Caminho Minimo entre dois vertices - Floyd;
    • [5] Arvore Geradora Minima de Prim;
    • [6] Arvore Geradora Minima de Kruskal;
    • [7] Arvore pelo Caminhamento em Profundidade;
    • [8] Imprimir Ordenacao Topologica;
    

### Padrão do arquivo de entrada
    • Tipo 1: vértices e arestas sem peso
        • id_vértice_origem id_vértice_alvo
    • Tipo 2: vértices sem peso e arestas com peso
        • id_vértice_origem id_vértice_alvo peso_aresta
    • Tipo 3: vértices com peso e arestas sem peso
        • id_vértice_origem peso_vértice_origem id_vértice_alvo peso_vértice_alvo
    • Tipo 4: vértices e arestas com peso
        • id_vértice_origem peso_vértice_origem id_vértice_alvo peso_vértice_alvo peso_aresta
	

# Trabalho 02: Algoritmos para o Problema da Árvore Geradora Mínima Generaliza

### Padrão de execução em linha de comando

"diretório da pasta do arquivo\execGrupo2.exe" <arquivo_entrada> saida.dot 0 1 0

### Em que:
	• Diretório do arquivo de entrada é o diretório no qual se encontra a pasta do arquivo contendo o trabalho;
	• execGrupo2.exe é o nome do executável do programa;
	• <arquivo_entrada> é o arquivo para o grafo de entrada desejado;
	• saida.dot é o nome do arquivo de saída, aonde serão gravados os retornos das funções;
	• 0 1 0 são os parâmetros passados para o programa do grafo (<direcionado> <ponderado_arestas> <ponderado_nos>, 0 representando false e 1 representando true)

### Algoritmo Guloso
Para executar o Algoritmo Guloso para a AGMG, após executar o programa e aparecer o menu na tela, selecionar a opção [10]. Após o algoritmo ser executado, o programa perguntará se você deseja ou não salvar o resultado no arquivo de saída (para salvar, selecione a opção [1]).

### Algoritmo Guloso Randomizado
Para executar o Algoritmo Guloso Randomizado para a AGMG, após executar o programa e aparecer o menu na tela, selecionar a opção [11]. Após o algoritmo ser executado, o programa perguntará se você deseja ou não salvar o resultado no arquivo de saída (para salvar, selecione a opção [1]).

### Algoritmo Guloso Randomizado Reativo
Para executar o Algoritmo Guloso Randomizado Reativo para a AGMG, após executar o programa e aparecer o menu na tela, selecionar a opção [12]. Após o algoritmo ser executado, o programa perguntará se você deseja ou não salvar o resultado no arquivo de saída (para salvar, selecione a opção [1]).

### Parâmetros de teste:

	• As sementes de randomização alfa são as mesmas para ambos: 0.05, 0.10, 0.15, 0.30, 0.50

	• Algoritmo Guloso Randomizado: O algoritmo é executado um total de 10 vezes por alfa, aonde o número de iterações
	passado como parâmetro pela função é de 500. Ou seja, o algoritmo roda 5000x em cada alfa, totalizando 25000 repetições no total.

	• Algoritmo Guloso Randomizado Reativo: O algoritmo é executado um total de 10x, aonde o número de iterações passado
	como parâmetro pela função é de 2500, e as probabilidades dos alfas são atualizadas a cada 100 repetições. Ou seja, no total,
	são realizadas 25000 repetições.
