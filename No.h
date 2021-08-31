#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include "Aresta.h"

using namespace std;

class No{

    private:
        int id;             // -> Id interno do sistema (ordem++)
        int id_aux;         // -> Id personalizado do usuario
        float peso;
        int grupo;
        unsigned int grau_entrada;
        unsigned int grau_saida;
        Aresta* primeira_aresta;
        Aresta* ultima_aresta;
        No* prox_no;

    public:
        No(int id, int id_aux);
        ~No();
        int getId();
        int getIdAux();
        float getPeso();
        int getGrauEntrada();
        int getGrauSaida();
        Aresta* getPrimeiraAresta();
        Aresta* getUltimaAresta();
        No* getProxNo();
        void setPeso(float peso);
        void setProxNo(No* prox_no);
        void setGrupo(int grupo);
        int getGrupo();

        void inserirAresta(int id_alvo, int id_aux_alvo, float peso, bool aux = false);
        void removerTodasArestas();
        void removerAresta(No* no_alvo, bool direcionado);
        Aresta* getArestaEntre(int id_alvo);
        bool existeArestaEntre(int id_alvo);
        void aumentarGrauEntrada();
        void diminuirGrauEntrada();
        void aumentarGrauSaida();
        void diminuirGrauSaida();
};

#endif // NO_H_INCLUDED