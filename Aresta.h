#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

class Aresta{

    private:
        int id_origem;
        int id_alvo;
        int id_aux_origem;
        int id_aux_alvo;
        bool aux;
        float peso;
        Aresta* prox_aresta;

    public:
        Aresta(int id_origem, int id_alvo, int id_aux_origem, int id_aux_alvo, float peso, bool aux);
        ~Aresta();
        int getIdOrigem();
        int getIdAlvo();
        int getIdAuxOrigem();
        int getIdAuxAlvo();
        bool getAux();
        float getPeso();
        Aresta* getProxAresta();
        void setPeso(float peso);
        void setProxAresta(Aresta* prox_aresta);
};

#endif // ARESTA_H_INCLUDED