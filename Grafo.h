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
        int qtdGrupos;

        // Funcionalidades privadas do trabalho
        int distMinima(bool visitados[], float dist[]);
        int distMinimaOutroGrupo(bool visitados[], bool gruposVisitados[], float distancia[]);
        void auxBuscaProf(int id_origem, bool visitados[], string* retorno, bool verificaCor[]);
        bool auxVerificarCiclo(int id_origem, bool visitados[], bool* auxRecursiva);
        bool auxBuscaVetor(int vertices[], int tamanho, int id_no);
        bool verificaPesoNegativo(int id, int id_alvo);
        bool verificarCiclo();
        void arestaMenorPeso(stack<Aresta*>* pilha, Aresta* arestas[], int qtdArestas);
        int verificaSubarvore(int v,int auxBuscaCiclo[]);
        void auxFTIRec(int id, bool visitados[], string* retorno);
        bool existeGrupo(int grupo);

    public:
        Grafo(int ordem, bool direcionado, bool aresta_ponderado, bool no_ponderado);
        ~Grafo();
        int getOrdem();
        int getNumArestas();
        int getQtdGrupos();
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
        void inserirNoComGrupo(int grupo);
        void removerNo(int id);
        void inserirAresta(int id, int id_alvo, float peso);

        string imprimir();

        // Funcionalidades do trabalho
        string fechoTD(int id_aux);
        string fechoTI(int id_aux);
        string fechoTIRec(int id_aux);
        string djikstra(int id_aux_origem, int id_aux_alvo);
        string floyd(int id_aux_origem, int id_aux_alvo);
        string agmPrim();
        string agmKruskal();
        string buscaProf(int id_aux_origem);
        Grafo* subgrafo(int vertices[], int tamanho);
        string ordTopologica();

        // Guloso
        string AGMGPrim();
        float auxAGMGPrim(int id_origem, int solucao[]);

        // Guloso Randomizado
        string AGMGPrimRandomizado(float alfa, int num_iteracoes);
        float auxAGMGPrimRandomizado(int id_origem, float alfa, int solucao[]);
        bool percorrerGrafo(float alfa, int solucao[], bool gruposVisitados[], bool possiveisNos[]);
        int proximoNoAGMGrandomizado(bool possiveisNos[]);
        int escolherArestaAGMGrandomizado(int prox_id, int solucao[], bool gruposVisitados[]);

        // Guloso Randomizado Reativo
        float AGMGPrimRandomizadoReativo(int solucaoAtual[], int* id_origem, int* i_melhor_alfa);
        string AGMGRandReativo();
};

#endif // GRAFO_H_INCLUDED