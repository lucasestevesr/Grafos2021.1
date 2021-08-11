## Universidade Federal de Juiz de Fora

Departamento de Ciência da Computação</br>
Disciplina DCC059 – Teoria dos Grafos – Semestre 2021-1</br>
Alunos:</br>
&emsp;&emsp;&emsp;Gabriel Antonio Esteves Matta</br>
&emsp;&emsp;&emsp;Lucas Esteves dos Reis Salgado</br>
&emsp;&emsp;&emsp;Pedro Paulo Silva Filogônio</br>
&emsp;&emsp;&emsp;Rafaela Fernandes Horta</br>

## Trabalho 01: Funcionalidades básicas em grafos simples

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

## Padrão do arquivo de entrada
    • Tipo 1: vértices e arestas sem peso
        • id_vértice_origem id_vértice_alvo
    • Tipo 2: vértices sem peso e arestas com peso
        • id_vértice_origem id_vértice_alvo peso_aresta
    • Tipo 3: vértices com peso e arestas sem peso
        • id_vértice_origem peso_vértice_origem id_vértice_alvo peso_vértice_alvo
    • Tipo 4: vértices e arestas com peso
        • id_vértice_origem peso_vértice_origem id_vértice_alvo peso_vértice_alvo peso_aresta
