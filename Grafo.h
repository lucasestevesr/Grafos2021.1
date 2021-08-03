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

        void auxBuscaProf(list<int>* listaVisitados, int id);
        bool auxBuscaLista(list<int>* listaVisitados, int id);

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
        bool existeNo(int id);
        void inserirNo(int id);
        void removerNo(int id);
        void inserirAresta(int id, int id_alvo, float peso);

        void imprimir();
        void salvarDot();

        // Funcionalidades do trabalho
        string fechoTD(int id);
        string fechoTI(int id);
        string djikstra(int id, int id_alvo);
        int distMinima(bool visitados[], int dist[]);
        void buscaProf(int id);
};

#endif // GRAFO_H_INCLUDED