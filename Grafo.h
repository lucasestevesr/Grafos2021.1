#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;

class Grafo{

    private:
        int ordem;
        int num_arestas;
        bool direcionado;
        bool aresta_ponderado;
        bool no_ponderado;
        No* primeiro_no;
        No* ultimo_no;

        // Funcionalidades privadas do trabalho
        int distMinima(bool visitados[], float dist[]);
        void auxBuscaProf(int id_origem, bool visitados[], string* retorno);
        bool auxVerificarCiclo(int id_origem, bool visitados[], bool* auxRecursiva);
        bool auxBuscaVetor(int vertices[], int tamanho, int id_no);

    public:
        Grafo(int ordem, bool direcionado, bool aresta_ponderado, bool no_ponderado);
        ~Grafo();
        int getOrdem();
        int getNumArestas();
        bool getDirecionado();
        bool getArestaPonderado();
        bool getNoPonderado();
        No* getPrimeiroNo();
        No* getUltimoNo();

        No* getNo(int id);
        No* getNoPorIdAux(int id_aux);
        int getIdPorIdAux(int id_aux);
        int getIdAuxPorId(int id);
        bool existeNo(int id);
        bool existeNoPorIdAux(int id_aux);
        bool existeAresta(int id_aux);
        void inserirNo(int id);
        void removerNo(int id);
        void inserirAresta(int id, int id_alvo, float peso);

        string imprimir();

        // Funcionalidades do trabalho
        string fechoTD(int id_aux);
        string fechoTI(int id_aux);
        string djikstra(int id_aux_origem, int id_aux_alvo);
        string floyd(int id_aux_origem, int id_aux_alvo);
        string agmPrim();
        string buscaProf(int id_aux_origem);
        bool verificarCiclo();
        Grafo* subgrafo(int vertices[], int tamanho);
        string ordTopologica();
};

#endif // GRAFO_H_INCLUDED