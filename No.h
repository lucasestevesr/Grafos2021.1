#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include "Aresta.h"

using namespace std;

class No{

    private:
        int id;
        float peso;
        unsigned int grau_entrada;
        unsigned int grau_saida;
        Aresta* primeira_aresta;
        Aresta* ultima_aresta;
        No* prox_no;

    public:
        No(int id);
        ~No();
        int getId();
        float getPeso();
        int getGrauEntrada();
        int getGrauSaida();
        Aresta* getPrimeiraAresta();
        Aresta* getUltimaAresta();
        No* getProxNo();
        void setPeso(float peso);
        void setProxNo(No* prox_no);

        void inserirAresta(int id_alvo, float peso);
        void removerTodasArestas();
        int removerAresta(int id, bool direcionado, No* no_alvo);
        Aresta* getArestaEntre(int id_alvo);
        bool existeArestaEntre(int id_alvo);
        void aumentarGrauEntrada();
        void diminuirGrauEntrada();
        void aumentarGrauSaida();
        void diminuirGrauSaida();
};

#endif // NO_H_INCLUDED