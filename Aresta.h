#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

class Aresta{

    private:
        int id_alvo;
        int id_origem;
        float peso;
        bool direcionado;
        Aresta* prox_aresta;

    public:
        Aresta(int id_alvo, int id_origem, float peso);
        ~Aresta();
        int getIdAlvo();
        int getIdOrigem();
        float getPeso();
        bool getDirecionado();
        Aresta* getProxAresta();
        void setPeso(float peso);
        void setDirecionado(bool direcionado);
        void setProxAresta(Aresta* prox_aresta);
};

#endif // ARESTA_H_INCLUDED