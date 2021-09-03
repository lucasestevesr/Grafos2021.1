#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <iterator>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
# include <limits>

using namespace std;

// Inicio construtor do Grafo
Grafo::Grafo(int ordem, bool direcionado, bool aresta_ponderado, bool no_ponderado) {
    this->ordem = 0;
    this->direcionado = direcionado;
    this->aresta_ponderado = aresta_ponderado;
    this->no_ponderado = no_ponderado;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->num_arestas = 0;
    this->qtdGrupos = 0;
}
// Fim construtor do Grafo

// Inicio destrutor do Grafo
Grafo::~Grafo() {
    No* prox_no = this->primeiro_no;

    while (prox_no != nullptr) {
        prox_no->removerTodasArestas();
        No* aux_no = prox_no->getProxNo();
        delete prox_no;
        prox_no = aux_no;
    }
}
// Fim destrutor do Grafo

// Inicio getters e setters
int Grafo::getOrdem() {
    return this->ordem;
}

int Grafo::getNumArestas() {
    return this->num_arestas;
}

int Grafo::getQtdGrupos() {
    return this->qtdGrupos;
}

bool Grafo::getDirecionado() {
    return this->direcionado;
}

bool Grafo::getArestaPonderado() {
    return this->aresta_ponderado;
}

bool Grafo::getNoPonderado() {
    return this->no_ponderado;
}

No* Grafo::getPrimeiroNo() {
    return this->primeiro_no;
}

No* Grafo::getUltimoNo() {
    return this->ultimo_no;
}
// Fim getters e setters

// Inicio funcao get No por Id
No* Grafo::getNo(int id) {
    // Veririca se tem No nesse grafo
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            // Se encontrar o No pelo Id, retorna ele
            if(no->getId() == id) {
                return no;
            }
        }
    }
    return nullptr;
}
// Fim funcao get No por Id

// Inicio funcao get No por Id Aux
No* Grafo::getNoPorIdAux(int id_aux) {
    // Veririca se tem No nesse grafo
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            // Se encontrar o No pelo Id Aux, retorna ele
            if(no->getIdAux() == id_aux) {
                return no;
            }
        }
    }
    return nullptr;
}
// Fim funcao get No por Id Aux

// Inicio funcao converter Id aux em Id interno
int Grafo::getIdPorIdAux(int id_aux) {
    // Veririca se tem No nesse grafo
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            // Se encontrar o No pelo Id Aux, retorna o id interno dele
            if(no->getIdAux() == id_aux) {
                return no->getId();
            }
        }
    }
    // Se nao encontrar retorna -1
    return -1;
}
// Fim funcao converter Id aux em Id interno

// Inicio funcao converter Id Interno em Id Aux
int Grafo::getIdAuxPorId(int id) {
    // Veririca se tem No nesse grafo
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            // Se encontrar o No pelo Id, retorna o id aux dele
            if(no->getId() == id) {
                return no->getIdAux();
            }
        }
    }
    // Se nao encontrar retorna -1
    return -1;
}
// Fim funcao converter Id Interno em Id Aux

// Inicio funcao verificar existe No por Id
bool Grafo::existeNo(int id) {
    // Veririca se tem No nesse grafo
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr ; no = no->getProxNo()) {
            // Se encontrar o No pelo Id, retorna verdadeiro
            if(no->getId() == id) {
                return true;
            }
        }
    }
    return false;
}
// Fim funcao verificar existe No por Id

// Inicio funcao verificar existe No por Id Aux
bool Grafo::existeNoPorIdAux(int id_aux) {
    // Veririca se tem No nesse grafo
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr ; no = no->getProxNo()) {
            // Se encontrar o No pelo Id Aux, retorna verdadeiro
            if(no->getIdAux() == id_aux) {
                return true;
            }
        }
    }
    return false;
}
// Fim funcao verificar existe No por Id Aux

// Inicio funcao verificar se tem alguma aresta em um No
bool Grafo::existeAresta(int id_aux) {
    // Veririca se tem No nesse grafo
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr ; no = no->getProxNo()) {
            // Percorre as Arestas dos Nos
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
                // Verifica se essa aresta chega ou sai do id
                if(aresta->getIdAuxOrigem() == id_aux || aresta->getIdAuxAlvo() == id_aux) {
                    return true;
                }
            }
        }
    }
    return false;
}
// Fim funcao verificar se tem alguma aresta em um No

// Inicio funcao inserir No
void Grafo::inserirNo(int id_aux) {

    // Cria o No com Id interno (ordem) e Id personalizado
    No* no = new No(this->ordem, id_aux);

    // Verifica se e o primeiro No do Grafo
    if(this->primeiro_no == nullptr){
        // Atualiza a referencia de primeiro e ultimo
        this->primeiro_no = no;
        this->ultimo_no = no;
    }else{
        // Se nao for o primeiro, atualiza a referencia do ultimo
        this->ultimo_no->setProxNo(no);
        this->ultimo_no = no;
    }
    // Incrementa a ordem do Grafo
    this->ordem ++;
}
// Fim funcao inserir No

// Inicio funcao inserir No
void Grafo::inserirNoComGrupo(int grupo) {
    // Incrementar quantidade de grupos
    if(!this->existeGrupo(grupo)) {
        this->qtdGrupos++;
    }

    // Cria o No com Id interno (ordem) com grupo
    No* no = new No(this->ordem, this->ordem);
    no->setGrupo(grupo);

    // Verifica se e o primeiro No do Grafo
    if(this->primeiro_no == nullptr){
        // Atualiza a referencia de primeiro e ultimo
        this->primeiro_no = no;
        this->ultimo_no = no;
    }else{
        // Se nao for o primeiro, atualiza a referencia do ultimo
        this->ultimo_no->setProxNo(no);
        this->ultimo_no = no;
    }

    // Incrementa a ordem do Grafo
    this->ordem ++;
}
// Fim funcao inserir No

// Inicio funcao verificar grupo
bool Grafo::existeGrupo(int grupo) {
    // Percorre todos Nos
    if(this->primeiro_no != nullptr) {
        // Percorre os Nos do grafo
        for (No* no = this->primeiro_no; no != nullptr ; no = no->getProxNo()) {
            // Se encontrar o No pelo grupo, retorna verdadeiro
            if(no->getGrupo() == grupo) {
                return true;
            }
        }
    }
    return false;
}
// Fim funcao verificar grupo

// Inicio funcao remover No
void Grafo::removerNo(int id) {
    // Verificando se o No existe
    if(existeNo(id)) {
        // Criando No de partida e No temp de auxilio
        No* no = this->primeiro_no;
        No* temp = nullptr;

        // Procurando No a ser excluido e salvando o temp
        while(no->getId() != id) {
            temp = no;
            no = no->getProxNo();
        }

        if(temp != nullptr) {
            temp->setProxNo(no->getProxNo());
        } else{
            this->primeiro_no = no->getProxNo();
        }

        if(no == this->ultimo_no) {
            this->ultimo_no = temp;
        }

        if(no->getProxNo() == this->ultimo_no) {
            this->ultimo_no = no->getProxNo();
        }

        No* aux = this->getPrimeiroNo();

        // Removendo arestas que incidam neste No
        while(aux != nullptr) {
            aux->removerAresta(no, this->direcionado);
            aux = aux->getProxNo();
        }

        // Deletando No
        delete no;

        // Decrementando ordem do Grafo
        this->ordem--;
    }
}
// Fim funcao remover No

// Inicio funcao de inserir Aresta
void Grafo::inserirAresta(int id_aux, int id_alvo_aux, float peso) {
    // Cria o No de origem se ele nao existir
    if(!this->existeNoPorIdAux(id_aux))
        inserirNo(id_aux);

    // Cria o No alvo se ele nao existir
    if(!this->existeNoPorIdAux(id_alvo_aux))
        inserirNo(id_alvo_aux);

    // Pega o No de origem e o No alvo
    No* no_origem = this->getNoPorIdAux(id_aux);
    No* no_alvo = this->getNoPorIdAux(id_alvo_aux);

    // Verifica se o grafo e direcionado
    if(this->direcionado) {
        // Se for direcionado insere a aresta com a direcao
        no_origem->inserirAresta(no_alvo->getId(), no_alvo->getIdAux(), peso);
        // Atualiza os graus de entrada e saida
        no_origem->aumentarGrauSaida();
        no_alvo->aumentarGrauEntrada();
    }else {
        // Se nao for direcionado insere a aresta de ida e de volta
        no_origem->inserirAresta(no_alvo->getId(), no_alvo->getIdAux(), peso);
        // Na aresta de volta evidencia que e uma aresta auxiliar no ultimo parametro
        no_alvo->inserirAresta(no_origem->getId(), no_origem->getIdAux(), peso, true);
        // Atualiza os graus de entrada e saida
        no_origem->aumentarGrauSaida();
        no_origem->aumentarGrauEntrada();
        no_alvo->aumentarGrauSaida();
        no_alvo->aumentarGrauEntrada();
    }
    // Incrementa o numero de arestas do Grafo
    this->num_arestas++;
}
// Fim funcao de inserir Aresta

// Inicio funcao imprimir Grafo
string Grafo::imprimir() {
    // Criando string de retorno
    string retorno = "--------- Imprimindo Grafo --------- \n";

    // Verificando se o grafo e vazio
    if(this->primeiro_no == nullptr) {
        retorno += "Erro: Grafo vazio! \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    // Escrevendo ordem do grafo
    retorno += "Ordem: " + std::to_string(this->ordem) + "\n";

    // Configurando cabecalho e seta do Grafo
    string seta;
    if(this->direcionado) {
        retorno += "digraph { \n";
        seta += " -> ";
    } else {
        retorno += "graph { \n";
        seta += " -- ";
    }

    // Percorrendo todos os Nos do Grafo
    for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
        // Escrevendo o No sozinho caso ele nao tenha arestas
        if(!this->existeAresta(no->getIdAux())) {
            retorno += "\t" + std::to_string(no->getIdAux()) + "\n";
        }
        // Percorrendo todas arestas do No
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
            // Verifica se nao e aresta de retorno
            if(!aresta->getAux()) {
                // Escreve o No com a aresta e o No de destino
                retorno += "\t" + std::to_string(aresta->getIdAuxOrigem()) + seta + std::to_string(aresta->getIdAuxAlvo()) + " [label=" + std::to_string(aresta->getPeso()) + "]" + "\n";
            }
        }
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim funcao imprimir Grafo

// Funcionalidades do trabalho

// Inicio Fecho Transitivo Direto
string Grafo::fechoTD(int id_aux) {
    // Criando string de retorno
    string retorno = "------- Fecho Transitivo Direto ------- \n";

    if(!this->direcionado) {
        retorno += "Erro: O grafo precisa ser direcionado! \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    //Verificando se os vertices existem no grafo
    if(!this->existeNoPorIdAux(id_aux)){
        retorno += "O vertice nao existe! Favor inserir outro vertice!";
        retorno += "---------------------------------------";
        return retorno;
    }

    // Cabecalho do Grafo em .dot
    retorno += "digraph { \n";

    // Convertendo id auxiliar para id interno
    int id = this->getIdPorIdAux(id_aux);

    // Declarando vetor bool de nos visitados
    bool visitados[this->ordem];

    // Pre-definindo que nenhum no do vertice foi visitado ainda
    for(int i = 0; i < this->ordem; i++)
        visitados[i] = false;

    // Definindo que o no inicial foi visitado
    visitados[id] = true;

    // Criando uma pilha auxiliar e colocando o no inicial no topo dela
    stack<int> pilhaAux;
    pilhaAux.push(id);

    // Enquanto a pilha nao for vazia fica rodando
    while(!pilhaAux.empty()) {

        // Recuperando o no do primeiro id da pilha
        No* no = this->getNo(pilhaAux.top());

        // Removendo o topo da pilha
        pilhaAux.pop();

        // Percorrendo as arestas do no que estava no topo da pilha e acabou de ser removido
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
            // Verifica se o no alvo de cada aresta ainda nao foi visitado
            if(!visitados[aresta->getIdAlvo()]) {
                // Se ele ainda nao foi visitado, coloca ele como visitado
                visitados[aresta->getIdAlvo()] = true;
                // Preenchendo string de retorno para salvar no arquivo .dot depois
                retorno += "\t" + std::to_string(aresta->getIdAuxOrigem()) + " -> " + std::to_string(aresta->getIdAuxAlvo()) + "\n";
                /* Adiciona o id do alvo da aresta atual que esta no loop sendo o proximo
                no a ser verificado, alimentando o while principal da funcao */
                pilhaAux.push(aresta->getIdAlvo());
            }
        }
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim Fecho Transitivo Direto

// Inicio Fecho Transitivo Indireto
// Nao esta funcionando para Grafo grandes
//string Grafo::fechoTI(int id_aux) {
//    // Criando string de retorno
//    string retorno = "------- Fecho Transitivo Indireto ------- \n";
//
//    if(!this->direcionado) {
//        retorno += "Erro: O grafo precisa ser direcionado! \n";
//        retorno += "---------------------------------------";
//        return retorno;
//    }
//
//    // Cabecalho do Grafo em .dot
//    retorno += "digraph { \n";
//
//    // Convertendo id auxiliar para id interno
//    int id = this->getIdPorIdAux(id_aux);
//
//    // Criando uma pilha auxiliar e colocando o no inicial no topo dela
//    stack<int> pilhaAux;
//    pilhaAux.push(id);
//
//    // Enquanto a pilha nao for vazia fica rodando
//    while(!pilhaAux.empty()) {
//
//        // Recuperando o no do primeiro id da pilha
//        int topo = pilhaAux.top();
//
//        // Removendo o topo da pilha
//        pilhaAux.pop();
//
//        // Percorrendo Nos do grafo a partir do No que estava no topo da pilha e acabou de ser removido
//        for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()) {
//            // Verifica se o No alvo possui aresta com o No atual do for
//            if(no->existeArestaEntre(topo)) {
//                // Preenchendo string de retorno para salvar no arquivo .dot depois
//                retorno += "\t" + std::to_string(no->getIdAux())  + " -> " + std::to_string(getIdAuxPorId(topo)) + "\n";
//                // No a ser verificado, alimentando o while principal da funcao
//                pilhaAux.push(no->getId());
//            }
//        }
//    }
//    retorno += "} \n";
//    retorno += "---------------------------------------";
//    return retorno;
//}
// Fim Fecho Transitivo Indireto

// Inicio Fecho Transitivo Indireto Recursiva
string Grafo::fechoTIRec(int id_aux) {
    // Criando string de retorno
    string retorno = "------- Fecho Transitivo Indireto ------- \n";

    if(!this->direcionado) {
        retorno += "Erro: O grafo precisa ser direcionado! \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    //Verificando se os vertices existem no grafo
    if(!this->existeNoPorIdAux(id_aux)){
        retorno += "O vertice nao existe! Favor inserir outro vertice!";
        retorno += "---------------------------------------";
        return retorno;
    }

    // Cabecalho do Grafo em .dot
    retorno += "digraph { \n";

    // Convertendo id auxiliar para id interno
    int id = this->getIdPorIdAux(id_aux);

    // Criando vetor de vertices visitados
    bool visitados[this->ordem];

    // Marcando todos vertices como nao visitados
    for(int i = 0; i < this->ordem; i++)
        visitados[i] = false;

    // Marcando No de origem como visitado
    visitados[id] = true;

    // Chamando funcao recursiva auxiliar
    this->auxFTIRec(id, visitados, &retorno);

    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim Fecho Transitivo Indireto Recursiva

void Grafo::auxFTIRec(int id, bool visitados[], string* retorno) {
    // Pegando No referente ao id origem
    No* no = this->getNo(id);

    // Percorrendo todas arestas do No de origem
    for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
        // Se o vertice do alvo da aresta ainda nao foi visitado
        if(!visitados[aresta->getIdAlvo()]) {
            // Marcando o vertice do alvo da aresta como visitado
            visitados[aresta->getIdAlvo()] = true;
            // Preenchendo string de retorno
            *retorno += "\t" + std::to_string(aresta->getIdAuxOrigem()) + " -> " + std::to_string(aresta->getIdAuxAlvo()) + " [label=" + std::to_string(aresta->getPeso()) + "]" + "\n";
            // Chamando recursividade novamente
            this->auxFTIRec(aresta->getIdAlvo(), visitados, retorno);
        }
    }
}

//Função auxiliar para verificar se a aresta entre dois vértices possui peso negativo.
bool Grafo::verificaPesoNegativo(int id, int id_alvo){
    No* no = this->getNo(id);
    Aresta* aresta = no->getArestaEntre(id_alvo);
    if(aresta->getPeso() < 0)
        return true;
    return false;
}
//Fim função auxiliar

// Inicio Caminho Minimo por Djikstra
string Grafo::djikstra(int id_aux_origem, int id_aux_alvo) {

    // Criando string de retorno
    string retorno = "------- Caminho Minimo Dijkstra ------- \n";

    //Verificando se os vertices existem no grafo
    if(!this->existeNoPorIdAux(id_aux_origem) || !this->existeNoPorIdAux(id_aux_alvo)){
        retorno += "Algum dos vertices nao existe! Favor inserir outros vertices!";
        retorno += "---------------------------------------";
        return retorno;
    }

    // Convertendo id aux origem e id aux alvo para id e id alvo
    int id_origem = getIdPorIdAux(id_aux_origem);
    int id_alvo = getIdPorIdAux(id_aux_alvo);

    if(id_origem == id_alvo) {
        retorno += "Custo caminho: 0 \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    // Variavel infinito utilizada para numerar as distancias entre vertices que nao possuem caminho
    float infinito = std::numeric_limits<float>::max();
    // Vetor booleano para verificar quais vertices foram visitados
    bool visitados[this->ordem];
    // Vetor para armazenar a distancia entre os vertices
    float dist[this->ordem];
    // Vetor para auxiliar a "gravar" o caminho entre os vertices
    int auxCaminho[this->ordem];
    // Inicializando as distancias entre os vertices como infinito, e marcando os vertices como nao visitados
    for(int i=0; i<this->ordem; i++) {
        dist[i] = infinito;
        visitados[i] = false;
        auxCaminho[i] = id_origem;
    }
    // Inicializando a distancia do vertice de origem para ele mesmo como 0, e marcando-o como visitado
    dist[id_origem] = 0;
    visitados[id_origem] = true;
    No* noAux = this->getNo(id_origem);
    /* Percorrendo as arestas do vertice de origem, calculando as distancias entre ele e seus adjacentes,
    e gravando-as no vetor dist[] */
    for(Aresta* arestaAux = noAux->getPrimeiraAresta(); arestaAux != nullptr; arestaAux = arestaAux->getProxAresta()) {
        dist[arestaAux->getIdAlvo()] = arestaAux->getPeso();
    }
    // Laco que percorre todos os vertices do grafo
    for(int i = 0; i < this->ordem-1; i++) {
        // Chamada da funcao que calcula o id do vertice de menor distancia (entre os vertices nao visitados) aos ja visitados
        int j = distMinima(visitados, dist);
        if(j == id_alvo)
            continue;
        // Marca o vertice de menor distancia como visitado
        visitados[j] = true;
        // Laco que percorre os vertices do grafo
        for(int k = 0; k < this->ordem; k++) {
            No* atual = getNo(j);
            /* Condicao que atualiza o valor de dist caso o vertice sendo verificado (k) nao tenha sido visitado,
            a distancia do No atual (j) ate o No de origem nao seja infinito, e caso exista aresta entre os Nos k e j */
            if(!visitados[k] && dist[j] != infinito && atual->existeArestaEntre(k)) {
                Aresta* arestaEntre = atual->getArestaEntre(k);
                // Atualiza o valor da distancia caso o novo calculo seja menor do que o anterior.
                if(dist[j] + arestaEntre->getPeso() < dist[k]){
                    dist[k] = dist[j] + arestaEntre->getPeso();
                    /*"Grava" o caminho no vetor auxCaminho, para ser realizada a impressao no arquivo de saida no final
                    A ideia e gravar de onde o vertice k veio, armazenando na posiçao k o id de j */
                    auxCaminho[k] = j;
                }
            }
        }
    }

    // Colocando o cabecalho do grafo corretamente, verificando se e grafo ou digrafo.
    string seta;
    if(this->direcionado) {
        retorno += "digraph { \n";
        seta = " -> ";
    }else {
        retorno += "strict graph { \n";
        seta = " -- ";
    }

    /* Caso a distancia do vertice alvo ao vertice de origem seja infinito ou 0, nao existe caminho entre eles.
    Portanto, e impresso na tela uma mensagem de erro e encerrada a função */
    if(dist[id_alvo] == infinito){
        retorno += "Erro: Nao existe caminho entre os vertices! \n";
        retorno += "---------------------------------------";
        return retorno;
    }
    // Variavel apra auxiliar a na criacao do texto em .dot
    int k = id_alvo;
    // Criacao do texto em .dot, que e colocado na string de retorno
    do {
        int auxK;
        auxK = k;
        // Aqui, utilizamos o vetor auxiliar para ir "retornando" no caminho que fazemos do vertice origem ate o alvo
        k = auxCaminho[k];
        //Caso haja alguma aresta com peso negativo, retornar erro.
        if(verificaPesoNegativo(k, auxK)){
            return "\tCaminho Minimo por Dijkstra: Erro! Aresta com peso negativo! \n";
        }
        retorno += "\t" + std::to_string(this->getIdAuxPorId(k)) + seta + std::to_string(this->getIdAuxPorId(auxK)) + "\n";
    } while(k != id_origem);
    retorno += "} \n";
    retorno += "Custo caminho: " + std::to_string(dist[id_alvo]) + "\n";
    retorno += "---------------------------------------";
    return retorno;
}
//Fim Caminho Minimo por Djikstra

// Inicio função auxiliar para calcular o vertice de menor distancia dentre os vertices nao visitados
int Grafo::distMinima(bool visitados[], float dist[]) {
    // Variavel de valor minimo, inicializada como + infinito
    float min = std::numeric_limits<float>::max();
    // Variavel para gravar o id do menor vertice
    int idMenor;
    // Laco que percorre o grafo
    for(int i=0; i<this->ordem; i++){
        // Caso o vertice não tenha sido visitado e tenha distancia menor que a variavel 'min', o mesmo passa a ser o menor
        if(!visitados[i] && dist[i]<=min){
            min = dist[i];
            idMenor = i;
        }
    }
    // Retorna o vertice de menor valor de distancia
    return idMenor;
}
// Fim função auxiliar menor distancia

int Grafo::distMinimaOutroGrupo(bool visitados[], bool gruposVisitados[], float distancia[]) {
    // Variavel de valor minimo, inicializada como + infinito
    float min = std::numeric_limits<float>::max();
    // Variavel para gravar o id do menor vertice
    int idMenor = -1;
    // Percorrendo o grafo
    for(int i = 0; i < this->ordem; i++){
        /* Caso o vertice nem o seu grupo nao tenha sido visitado e tenha distancia
        menor que a variavel 'min', o mesmo passa a ser o menor */
        if(!visitados[i] && !gruposVisitados[this->getNo(i)->getGrupo()] && distancia[i] <= min) {
            // Atualiza o min e o id menor
            min = distancia[i];
            idMenor = i;
        }
    }
    // Retorna o vertice de menor valor de distancia
    return idMenor;
}

// Inicio Caminho Minimo por Floyd
string Grafo::floyd(int id_aux_origem, int id_aux_alvo) {
    // Criando string de retorno
    string retorno = "------- Caminho Minimo Floyd ------- \n";
    //Verificando se os vertices existem no grafo
    if(!this->existeNoPorIdAux(id_aux_origem) || !this->existeNoPorIdAux(id_aux_alvo)){
        retorno += "Algum dos vertices nao existe! Favor inserir outros vertices!";
        retorno += "---------------------------------------";
        return retorno;
    }

    // Declarando variavel infinito para usar quando nao tiver caminho
    float infinito = std::numeric_limits<float>::max();
    // Criando matriz de distancia entre todos vertices
    float distancia[this->ordem][this->ordem];
    // Criando matriz auxiliar para guardar o proximo vertice
    int proximo[this->ordem][this->ordem];
    // Percorrendo a matriz de distancia e proximo para fazer o primeiro preenchimento
    for(int id_o = 0; id_o < this->ordem; id_o++) {
        for(int id_a = 0; id_a < this->ordem; id_a++) {
            if(id_o == id_a) {
                distancia[id_o][id_a] = 0;
                proximo[id_o][id_a] = -1;
            }else {
                // Pegando o No referente ao id origem do primeiro for para percorrer as Arestas dele
                No* no = getNo(id_o);
                // Pegando aresta entre o No de origem do passo anterior e o No alvo do loop
                Aresta* aresta = no->getArestaEntre(id_a);
                // Verificando se existe a aresta
                if(aresta != nullptr) {
                    // Se existe preenche a distancia da origem para o alvo sendo o peso
                    distancia[id_o][id_a] = aresta->getPeso();
                    // Inicialmente o caminho mais curto da origem para o alvo e passando direto pela aresta origem/alvo
                    proximo[id_o][id_a] = id_a;
                }else {
                    // Se nao existe aresta a distancia recebe infinito
                    distancia[id_o][id_a] = infinito;
                    // E o proximo recebe -1, ou seja, nao tem proximo
                    proximo[id_o][id_a] = -1;
                }
            }
        }
    }
    /* Percorre dois for novamente, igual anteriormente, um para o No de origem (id_o), outro para
    o No alvo (id_a) e agora um terceiro for para um No intermediario (id_i) */
    for (int id_i = 0; id_i < this->ordem; id_i++) {
        for (int id_o = 0; id_o < this->ordem; id_o++) {
            for (int id_a = 0; id_a < this->ordem; id_a++) {
                // Se a distancia entre o No origem para o No alvo for infinita passa para o proximo
                if (distancia[id_o][id_i] == infinito || distancia[id_i][id_a] == infinito)
                    continue;
                /* Se a distancia entre o No origem para o No alvo for maior do que a distancia
                do No origem para um No intermediario + a distancia do No intermediario para o No alvo */
                if (distancia[id_o][id_a] > distancia[id_o][id_i] + distancia[id_i][id_a]) {
                    // Se sim, significa que achou um caminho mais curto, entao atualiza as matrizes
                    distancia[id_o][id_a] = distancia[id_o][id_i] + distancia[id_i][id_a];
                    proximo[id_o][id_a] = proximo[id_o][id_i];
                }
            }
        }
    }

    // Colocando o cabecalho do grafo corretamente, verificando se e grafo ou digrafo.
    string seta;
    if(this->direcionado) {
        retorno += "digraph { \n";
        seta = " -> ";
    }else {
        retorno += "strict graph { \n";
        seta = " -- ";
    }

    // Convertendo id aux origem e id aux alvo para id e id alvo
    int id_origem = getIdPorIdAux(id_aux_origem);
    int id_alvo = getIdPorIdAux(id_aux_alvo);

    /* Caso a distancia do vertice alvo ao vertice de origem seja infinito, nao existe caminho entre eles.
    Portanto, e impresso na tela uma mensagem de erro e encerrada a funcao */
    if(distancia[id_origem][id_alvo] == infinito) {
        retorno += "Erro: Nao existe caminho entre os vertices! \n";
        retorno += "---------------------------------------";
        return retorno;
    }
    // Variaveis auxiliares para recuperar o caminho mais curto
    int id_o = id_origem, id_a = id_alvo;
    float pesoAresta;
    // Partindo do Id de Origem, enquanto nao chegar no Alvo nao para
    while(id_o != id_a) {
        pesoAresta = distancia[id_o][proximo[id_o][id_a]];
        retorno += "\t" + std::to_string(this->getIdAuxPorId(id_o)) + seta;
        id_o = proximo[id_o][id_a];
        retorno += std::to_string(this->getIdAuxPorId(id_o)) + " [label=" + std::to_string(pesoAresta) + "]" + "\n";
    }
    retorno += "} \n";
    retorno += "Custo caminho: " + std::to_string(distancia[id_origem][id_alvo]) + "\n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim Caminho Minimo por Floyd

// Inicio AGM de Prim
string Grafo::agmPrim(){
    string retorno = "AGM por Prim\n";
    if(this->direcionado){
        retorno += "Erro! Grafo direcionado!";
        return retorno;
    }
    bool visitados[this->ordem];
    float distancia[this->ordem];
    int caminho[this->ordem];
    float infinito = std::numeric_limits<float>::max();
    float menorPeso = infinito;
    Aresta* menorAresta;
    for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()){
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            if(aresta->getPeso() <= menorPeso){
                menorPeso = aresta->getPeso();
                menorAresta = aresta;
            }
        }
    }
    int id_origem = menorAresta->getIdOrigem();
    for(int i=0;i<this->ordem;i++){
        visitados[i] = false;
        distancia[i] = infinito;
        caminho[i] = -1;
    }
    distancia[id_origem] = 0;
    for(int i=0; i<this->ordem; i++){
        int u = distMinima(visitados, distancia);
        visitados[u] = true;
        No* noAux = this->getNo(u);
        for(Aresta* adjacente = noAux->getPrimeiraAresta(); adjacente != nullptr; adjacente = adjacente->getProxAresta()){
            if(!visitados[adjacente->getIdAlvo()] && adjacente->getPeso() < distancia[adjacente->getIdAlvo()]){
                distancia[adjacente->getIdAlvo()] = adjacente->getPeso();
                caminho[adjacente->getIdAlvo()] = u;
            }
        }
    }
    string seta = " -- ";
    retorno += "strict graph { \n";

    for(int i=0; i<this->ordem; i++){
        if(caminho[i] != -1)
            retorno += "\t" + std::to_string(this->getIdAuxPorId(i)) + seta + std::to_string(this->getIdAuxPorId(caminho[i])) + "\n";
        else if(caminho[i] == -1 && i != id_origem)
            retorno += "\t" + std::to_string(this->getIdAuxPorId(i)) + "\n";
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim AGM de Prim

//Início AGM de Kruskal
string Grafo::agmKruskal(){
    //Criando string de retorno
    string retorno = "AGM por Kruskal\n";
    //Caso seja um grafo direcionado, retornar erro
    if(this->direcionado){
        retorno += "Erro! Grafo direcionado!";
        return retorno;
    }
    //Criando pilha auxiliar para guardar as arestas não auxiliares do grafo.
    stack<Aresta*> pilhaAux;
    //Variável para guardar a quantidade de arestas
    int qtdArestas = 0;
    for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()){
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            if(!aresta->getAux()){
                //Colocando as arestas na pilha e aumentando o valor de qtdArestas
                pilhaAux.push(aresta);
                qtdArestas++;
            }
        }
    }
    //Vetor de arestas saida com tamanho igual a quantidade de arestas, utilizado para imprimir o resultado mais a frente
    Aresta* saida[qtdArestas];
    //Caso o grafo não contenha arestas, imprimir somente os vertices isolados e retornar
    if(qtdArestas == 0){
        retorno += "strict graph { \n";
        for(int i=0; i<this->ordem; i++){
            retorno += "\t" + std::to_string(this->getIdAuxPorId(i)) + "\n";
        }
        retorno += "} \n";
        retorno += "---------------------------------------";
        return retorno;
    }
    //Vetor para armazenar as arestas do grafo
    Aresta* arestas[qtdArestas];
    int i = 0;
    while(!pilhaAux.empty()){
        arestas[i] = pilhaAux.top();
        pilhaAux.pop();
        i++;
    }
    int contador = 0;
    //Laço para colocar as arestas em ordem de maior para menor peso
    while(contador < qtdArestas){
        arestaMenorPeso(&pilhaAux, arestas, qtdArestas);
        contador++;
    }
    stack<Aresta*> pilha;
    //Invertendo a ordem das arestas, para que o topo da pilha sempre seja a aresta de menor peso
    while(!pilhaAux.empty()){
        pilha.push(pilhaAux.top());
        pilhaAux.pop();
    }
    //Cria vetor auxiliar para verificação de ciclos nas subarvores "criadas"
    int subarvores[this->ordem];
    for(No* noAux = this->getPrimeiroNo(); noAux != nullptr; noAux = noAux->getProxNo()){
        //Cria subarvores com vertices sozinhos
        subarvores[noAux->getId()] = noAux->getId();
    }
    contador = 0;
    /*Laço para realizar a operação até que todas as arestas necessarias para se formar a arvore tenham sido colocadas,
    ou até a pilha estar vazia */
    while(contador != this->ordem -1 && !pilha.empty()){
        //Pega a aresta de menor valor, e a retira da pilha
        Aresta* atual = pilha.top();
        pilha.pop();
        //Chama a função para identificar a subarvore dos vértices de origem e alvo da aresta
        int a = verificaSubarvore(atual->getIdOrigem(), subarvores);
        int b = verificaSubarvore(atual->getIdAlvo(), subarvores);
        //Caso estejam em subarvores diferentes, adiciona a aresta na saida (resolução)
        if(a != b){
            saida[contador] = atual;
            //Aumenta o número de arestas na saída
            contador++;
            //Coloca os vértices na mesma subarvore
            subarvores[a] = b;
        }
    }
    //Cria o cabeçalho do arquivo .dot
    string seta;
    retorno += "strict graph { \n";
    seta = " -- ";
    //Imprime as arestas do retorno
    for(int i=0; i<contador; i++){
        retorno += "\t" + std::to_string(saida[i]->getIdAuxOrigem()) + seta + std::to_string(saida[i]->getIdAuxAlvo()) + " [label=" + std::to_string(saida[i]->getPeso()) + "]" + "\n";
    }
    //Imprime os vértices isolados da árvore
    for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()){
        if(no->getPrimeiraAresta() == nullptr){
            retorno += "\t" + std::to_string(no->getIdAux()) + "\n";
        }
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
//Fim AGM de Kruskal

//Início função auxiliar de Kruskal para identificação de subárvores
int Grafo::verificaSubarvore(int id,int subarvores[]){
    //Caso a subárvore do id seja ele mesmo, retorna o id
     if(subarvores[id]==id)
        return id;
     //Caso contrário, chama recursivamente a função com o id da subárvore do id atual
    return verificaSubarvore(subarvores[id],subarvores);
}
//Fim função auxiliar verificaSubarvore

//Início função auxiliar para encontrar a aresta de menor peso
void Grafo::arestaMenorPeso(stack<Aresta*>* pilhaAux, Aresta* arestas[], int qtdArestas){
    //Cria valor infinito (limite numérico da classe float)
    float infinito = std::numeric_limits<float>::max();
    //Define uma variável menorPeso e inicializa-a com o valor infinito
    float menorPeso = infinito;
    //variável para guardar a posição do menor valor
    int posMenor;
    //Laço que percorre a quantidade de arestas do grafo
    for(int i=0; i<qtdArestas; i++){
        //Caso a aresta na posição i não seja NULL, e seu peso seja menor ou igual ao menor peso, ela se torna a de menor peso
        if(arestas[i] != nullptr && arestas[i]->getPeso() <= menorPeso){
            menorPeso = arestas[i]->getPeso();
            posMenor = i;
        }
    }
    //Coloca a aresta de menor peso na pilha
    pilhaAux->push(arestas[posMenor]);
    //Modifica a aresta de menor peso para o ponteiro nulo, "retirando-a" da lista de arestas
    arestas[posMenor] = nullptr;
}

// Inicio funcao retornar subgrafo vertice induzido
Grafo* Grafo::subgrafo(int vertices[], int tamanho) {
    // Cria um subgrafo
    Grafo* subGrafo = new Grafo(tamanho, this->direcionado, this->aresta_ponderado, this->no_ponderado);
    //Verifica se os vertices passados existem no grafo principal.
    for(int i=0; i<tamanho; i++){
        if(!this->existeNoPorIdAux(vertices[i])){
            cout << "Vertice nao existe no grafo! Favor inserir outros vertices!";
            return subGrafo;
        }
    }
    // Percorre todos Nos do grafo fonte
    for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
        // Verifica se o No atual do loop esta no conjunto de vertices induzidos
        if(this->auxBuscaVetor(vertices, tamanho, no->getIdAux())) {
            // Verifica se o No ja existe no subgrafo
            if(!subGrafo->existeNoPorIdAux(no->getIdAux())) {
                // Se nao existe cria ele no subgrafo
                subGrafo->inserirNo(no->getIdAux());
            }
            // Percorre as arestas do No atual do loop
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
                // Se o No do alvo da aresta tiver no conjunto vertice induzido
                if(this->auxBuscaVetor(vertices, tamanho, aresta->getIdAuxAlvo())) {
                    // Cria a aresta e la dentro cria o No alvo caso nao exista ainda
                    subGrafo->inserirAresta(aresta->getIdAuxOrigem(), aresta->getIdAuxAlvo(), aresta->getPeso());
                }
            }
        }
    }
    return subGrafo;
}
// Fim funcao retornar subgrafo vertice induzido

// Funcao auxiliar verificar se um ID esta em um vetor
bool Grafo::auxBuscaVetor(int vertices[], int tamanho, int id_aux) {
    // Percorre o vetor
    for(int i = 0; i < tamanho; i++) {
        // Se encontrar, retorna true
        if(vertices[i] == id_aux) {
            return true;
        }
    }
    return false;
}
// Fim auxiliar verificar se um ID esta em um vetor

string Grafo::buscaProf(int id_aux_origem) {
    //Verificando se os vertices existem no grafo
    if(!this->existeNoPorIdAux(id_aux_origem)){
        cout << "Vertice nao existe no grafo! Favor inserir outro vertice!";
        return "";
    }
    // Criando string de retorno
    string retorno = "------- Caminhamento em Profundidade ------- \n";

    if(this->direcionado)
        retorno += "digraph { \n";
    else
        retorno += "strict graph { \n";

    // Convertendo id aux origem para id
    int id_origem = getIdPorIdAux(id_aux_origem);

    // Criando vetor para armazenar o Nos visitados
    bool visitados[this->ordem];
    bool verificaCor[this->ordem];

    // Marcando todos Nos como nao visitados
    for(int i = 0; i < this->ordem; i++){
        visitados[i] = false;
        verificaCor[i] = false;
    }

    // Marcando No de origem como visitado
    visitados[id_origem] = true;

    // Chamando funcao aux para entrar na recursividade
    this->auxBuscaProf(id_origem, visitados, &retorno, verificaCor);

    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}

void Grafo::auxBuscaProf(int id_origem, bool visitados[], string* retorno, bool verificaCor[]) {
    // Pegando No referente ao id origem
    No* no = this->getNo(id_origem);

    // Criando variavel seta de acordo com o tipo de grafo
    string seta = " -- ";
    if(this->direcionado)
        seta = " -> ";

    // Percorrendo todas arestas do No de origem
    for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
        // Se o vertice do alvo da aresta ainda nao foi visitado
        if(!visitados[aresta->getIdAlvo()]) {
            // Marcando o vertice do alvo da aresta como visitado
            visitados[aresta->getIdAlvo()] = true;
            // Se nao for direcionado
            if(!this->direcionado) {
                // Marcando, tambem, a aresta invertida auxiliar como visitado
                visitados[no->getId()] = true;
            }
            // Preenchendo string de retorno
            *retorno += "\t" + std::to_string(aresta->getIdAuxOrigem()) + seta + std::to_string(aresta->getIdAuxAlvo()) + "\n";
            // Chamando recursividade novamente
            this->auxBuscaProf(aresta->getIdAlvo(), visitados, retorno, verificaCor);
        }
        if(visitados[aresta->getIdAlvo()] && !verificaCor[aresta->getIdAlvo()] && !aresta->getAux()){
            *retorno += "\t" + std::to_string(aresta->getIdAuxOrigem()) + seta + std::to_string(aresta->getIdAuxAlvo()) + " [color=red] " + "\n";
        }
    }
    verificaCor[id_origem] = true;
}

string Grafo::ordTopologica() {
    // Criando string de retorno
    string retorno = "------- Ordenacao Topologica ------- \n";

    if(!this->direcionado) {
        retorno += "Erro: O grafo precisa ser direcionado! \n";
        retorno += "---------------------------------------";
        return retorno;
    }
    if(this->verificarCiclo()) {
        retorno += "Erro: O grafo nao pode ter ciclo! \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    stack<int> pilhaAux;
    bool visitados[this->ordem];
    int grauEntrada[this->ordem];
    for(int i = 0; i < this->ordem; i++) {
        visitados[i] = false;
        grauEntrada[i] = this->getNo(i)->getGrauEntrada();
    }

    while(pilhaAux.size() != this->ordem) {
        for(int i = 0; i < this->ordem; i++) {
            if(grauEntrada[i] == 0 && !visitados[i]) {
                No* no = getNo(i);
                pilhaAux.push(i);
                visitados[i] = true;
                for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
                    grauEntrada[aresta->getIdAlvo()] = grauEntrada[aresta->getIdAlvo()] - 1;
                }
            }
        }
    }

    stack<int> pilhaSaida;
    while(!pilhaAux.empty()) {
        pilhaSaida.push(pilhaAux.top());
        pilhaAux.pop();
    }

    retorno += "[";
    retorno += std::to_string(this->getIdAuxPorId(pilhaSaida.top()));
    pilhaSaida.pop();
    while(!pilhaSaida.empty()) {
        retorno += "," + std::to_string(this->getIdAuxPorId(pilhaSaida.top()));
        pilhaSaida.pop();
    }
    retorno += "]";

    retorno += "\n ---------------------------------------";
    return retorno;
}

bool Grafo::auxVerificarCiclo(int id_origem, bool visitados[], bool* auxRecursiva) {
    if(!visitados[id_origem]) {
        visitados[id_origem] = true;
        auxRecursiva[id_origem] = true;
        No* no = this->getNo(id_origem);
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
            if(!visitados[aresta->getIdAlvo()] && auxVerificarCiclo(aresta->getIdAlvo(), visitados, auxRecursiva)) {
                return true;
            }else if(auxRecursiva[aresta->getIdAlvo()]) {
                return true;
            }
        }
    }
    auxRecursiva[id_origem] = false;
    return false;
}

bool Grafo::verificarCiclo() {
    // Criando vetor para armazenar o Nos visitados
    bool visitados[this->ordem];
    // Criando vetor auxiliar
    bool auxRecursiva[this->ordem];

    // Marcando todos Nos como nao visitados
    for(int i = 0; i < this->ordem; i++) {
        visitados[i] = false;
        auxRecursiva[i] = false;
    }

    for(int id_origem = 0; id_origem < this->ordem; id_origem++) {
        // Chamando funcao aux para entrar na recursividade
        if(this->auxVerificarCiclo(id_origem, visitados, auxRecursiva)) {
            return true;
        }
    }
    return false;
}

// Inicio funcao agmg prim guluso
string Grafo::AGMGPrim() {
    // Declarando variaveis de controle
    int id_origem = 0;
    float alfa = 1;
    float infinito = std::numeric_limits<float>::max();
    float melhorCusto = infinito;
    float custoSolucao = 0;
    int solucao[this->ordem];
    int melhorSolucao[this->ordem];

    // Percorrendo todos vertices do grafo
    for(int i = 0; i < this->ordem; i++) {
        // Chama o agmg prim guloso para todos vertices do grafo
        custoSolucao = this->auxAGMGPrim(i, solucao);
        // Compara o custo recebido da solucao com o melhor custo
        if(custoSolucao < melhorCusto) {
            // Se for melhor faz o backup da solucao
            for(int j = 0; j < this->ordem; j++) {
                melhorSolucao[j] = solucao[j];
            }
            id_origem = i;
            melhorCusto = custoSolucao;
        }
    }

    // Daqui para baixo e so salvando a solucao no arquivo de saida
    string retorno = "AGMG Guloso - Prim\n";
    if(this->direcionado){
        retorno += "Erro! Grafo direcionado!";
        return retorno;
    }

    string seta = " -- ";
    retorno += "// Vértice Inicial = " + std::to_string(id_origem) + "\n";
    retorno += "// Custo Total = " + std::to_string(melhorCusto) + "\n";
    retorno += "// Qtd. Grupos = " + std::to_string(this->qtdGrupos) + "\n";
    retorno += "strict graph { \n";

    string cores[10] = {"red", "orange", "blue", "yellow", "gray", "beige", "pink", "green", "violet", "purple"};
    int grupo = 0;
    for(int i = 0; i < this->ordem; i++) {
        if(melhorSolucao[i] != -1) {
            grupo = this->getNo(i)->getGrupo();
            if(grupo <= this->qtdGrupos){
                retorno += "\t" + std::to_string(i) + " [color=" + cores[grupo-1] + "]" + "\n";
            }
            retorno += "\t" + std::to_string(i) + seta + std::to_string(melhorSolucao[i]) + " [label=" + std::to_string(this->getNo(i)->getArestaEntre(melhorSolucao[i])->getPeso()) + "]" + "\n";
        }
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim funcao agmg prim guluso

// Inicio funcao aux do agmg prim guloso
float Grafo::auxAGMGPrim(int id_origem, int solucao[]) {
    // Declarando vetores e parametros auxiliares
    bool visitados[this->ordem];
    bool gruposVisitados[this->qtdGrupos+1];    // Grupos 1 a n
    float distancia[this->ordem];
    float infinito = std::numeric_limits<float>::max();
    float menorPeso = infinito;
    float custoTotal = 0;

    // Inicializando os vetores
    for(int i = 0; i < this->ordem; i++) {
        visitados[i] = false;
        distancia[i] = infinito;
        solucao[i] = -1;
    }
    // Inicializando grupos visitados 1 a n (necessario ter o menor igual (<=))
    for(int i = 0; i <= this->qtdGrupos; i++){
        gruposVisitados[i] = false;
    }

    // Inicializando a distancia para a origem como 0
    distancia[id_origem] = 0;

    // Percorrendo todos os vertices
    for(int i = 0; i < this->ordem; i++) {
        // Usando funcao auxiliar para
        int prox_id = distMinimaOutroGrupo(visitados, gruposVisitados, distancia);
        // Se retornar -1 ja visitou todos os grupos
        if(prox_id == -1) {
            break;
        }
        // Busca o proximo vertice
        No* noAux = this->getNo(prox_id);
        // Marca o proximo vertice e o grupo dele como visitados
        visitados[prox_id] = true;
        gruposVisitados[noAux->getGrupo()] = true;
        // Percorrendo todas arestas do proximo vertice
        for(Aresta* adjacente = noAux->getPrimeiraAresta(); adjacente != nullptr; adjacente = adjacente->getProxAresta()) {
            // Se algum vertice que liga com ele ainda nao foi visitado e tem uma distancia menor do que a distancia armazenada
            if(!visitados[adjacente->getIdAlvo()] && adjacente->getPeso() < distancia[adjacente->getIdAlvo()]){
                // Atualiza a distancia e o caminho
                distancia[adjacente->getIdAlvo()] = adjacente->getPeso();
                solucao[adjacente->getIdAlvo()] = prox_id;
            }
        }
    }
    // Limpando solucao e pegando custo total
    for(int i = 0; i < this->ordem; i++) {
        if(!visitados[i])
            solucao[i] = -1;
    }

    for(int i = 0; i < this->ordem; i++) {
        if(solucao[i] != -1)
            custoTotal += this->getNo(i)->getArestaEntre(solucao[i])->getPeso();
    }

    // Retornando custo
    return custoTotal;
}
// Fim funcao aux do agmg prim guloso

// Inicio funcao agmg prim randomizada
string Grafo::AGMGPrimRandomizado(float alfa, int num_iteracoes) {
    // Variavel para incrementar a iteracao atual
    int qnt_iteracoes = 0;
    // Variavel de controle para armazenar o id do no de origem
    int id_origem = 0;
    // Solucao do algoritmo que vai ser passa para funcao aux
    int solucao[this->ordem];
    // Armazenar o backup da melhor solucao
    int melhorSolucao[this->ordem];
    // Armazenar o melhor custo, comeca como + infinito para o primeiro custo entrar como melhor
    float melhorCusto = std::numeric_limits<float>::max();
    // Custo da solucao atual
    float custoSolucao = 0;

    // Enquanto nao percorrer todas iteracoes nao acaba
    while(num_iteracoes > qnt_iteracoes) {
        // Percorre passando o id de todos vertices do grafo
        for (int i = 0; i < this->ordem; i++) {
            // Chama o algoritmo e armazena o custo dele
            custoSolucao = this->auxAGMGPrimRandomizado(i, alfa, solucao);
            // Incrementa o quantidade de iteracoes
            qnt_iteracoes++;
            // Se o custo for melhor do que o melhor custo
            if (custoSolucao < melhorCusto) {
                // Faz o backup da solucao
                for (int j = 0; j < this->ordem; j++) {
                    melhorSolucao[j] = solucao[j];
                }
                // Pega o id de origem da atual melhor solucao
                id_origem = i;
                // Atualiza o melhor custo
                melhorCusto = custoSolucao;
            }
        }
    }

    // Daqui para baixo e so salvando a solucao no arquivo de saida
    string retorno = "AGMG Guloso Randomizado - Prim\n";
    if(this->direcionado){
        retorno += "Erro! Grafo direcionado!";
        return retorno;
    }

    string seta = " -- ";
    retorno += "// Vértice Inicial = " + std::to_string(id_origem) + "\n";
    retorno += "// Custo Total = " + std::to_string(melhorCusto) + "\n";
    retorno += "// Qtd. Grupos = " + std::to_string(this->qtdGrupos) + "\n";
    retorno += "strict graph { \n";

    string cores[10] = {"red", "orange", "blue", "yellow", "gray", "beige", "pink", "green", "violet", "purple"};
    int grupo = 0;
    for(int i = 0; i < this->ordem; i++) {
        if(melhorSolucao[i] != -1) {
            grupo = this->getNo(i)->getGrupo();
            if(grupo <= this->qtdGrupos){
                retorno += "\t" + std::to_string(i) + " [color=" + cores[grupo-1] + "]" + "\n";
            }
            retorno += "\t" + std::to_string(i) + seta + std::to_string(melhorSolucao[i]) + " [label=" + std::to_string(this->getNo(i)->getArestaEntre(melhorSolucao[i])->getPeso()) + "]" + "\n";
        }
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim funcao agmg prim randomizada

// Inicio da funcao auxiliar do agmg prim randomizado
float Grafo::auxAGMGPrimRandomizado(int id_origem, float alfa, int solucao[]) {
    // Declarando variaveis de controle para rodar o algoritmo
    bool possiveisNos[this->ordem];
    bool gruposVisitados[this->qtdGrupos+1];
    // Custo total do algoritmo comeca como 0
    float custoTotal = 0;

    // Inicializa o vetor solucao
    for(int i = 0; i < this->ordem; i++) {
        solucao[i] = -1;
    }
    // Inicializa o vetor de grupos visitados
    for(int i = 0; i <= this->qtdGrupos; i++) {
        gruposVisitados[i] = false;
    }

    // Define a solucao inicial partindo dele mesmo
    solucao[id_origem] = id_origem;
    // Define o grupo do No inicial como visitado
    gruposVisitados[this->getNo(id_origem)->getGrupo()] = true;

    // Variavel para alimentar o loop
    bool rodando = true;
    // Loop principal do algoritmo do agmg randomizado de prim
    while(rodando) {
        // Chama funcao que percorre o grafo das possiveis solucoes e retorna se deve continuar rodando
        rodando = percorrerGrafo(alfa, solucao, gruposVisitados, possiveisNos);
        // Se deve continuar rodando
        if(rodando) {
            // Pega o proximo no
            int prox_id = proximoNoAGMGrandomizado(possiveisNos);
            // Pega o alvo desse vertice com base na aresta de menor peso
            int id_alvo = escolherArestaAGMGrandomizado(prox_id, solucao, gruposVisitados);
            // Se tiver retornado um alvo
            if(id_alvo != -1){
                // Atualiza o vetor solucao
                solucao[prox_id] = id_alvo;
                // Marca o grupo do proximo no como visitado
                gruposVisitados[this->getNo(prox_id)->getGrupo()] = true;
            }
        }
    }
    // Retira o vertice inicial da solucao
    solucao[id_origem] = -1;

    // Calcula o custo total do grafo solucao
    // Percorre o vetor solucao
    for(int i = 0; i < this->ordem; i++) {
        // Se o vertice atual tem solucao
        if(solucao[i] != -1) {
            // Incrementa o custo total
            custoTotal += this->getNo(i)->getArestaEntre(solucao[i])->getPeso();
        }
    }

    // Retorna o custo total
    return custoTotal;
}
// Fim da funcao auxiliar do agmg prim randomizado

// Inicio da funcao para percorrer o grafo no agmg randomizado e retorna o status do algoritmo
bool Grafo::percorrerGrafo(float alfa, int solucao[], bool gruposVisitados[], bool possiveisNos[]) {
    // Declara variaveis referencia de menor e maior peso
    float min_peso, max_peso;
    // Variavel para saber se esta na primeira iteracao
    bool primeiraIt = true;

    // For para inicializar todos nos possiveis como false
    for(int i = 0; i < this->getOrdem(); i++) {
        possiveisNos[i] = false;
    }

    // Percorrendo todos nos
    for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
        // Se o no ja foi visitado, ou seja, esta na solucao
        if(solucao[no->getId()] != -1) {
            // Percorre todas arestas dele
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
                // Se o alvo da aresta nem seu respectivo grupo ainda nao foram visitados
                if(solucao[aresta->getIdAlvo()] == -1 && !gruposVisitados[this->getNo(aresta->getIdAlvo())->getGrupo()]) {
                    // Se for a primeira iteracao
                    if(primeiraIt){
                        // Define o menor e o maior peso como o peso do alvo da aresta atual
                        min_peso = aresta->getPeso();
                        max_peso = aresta->getPeso();
                        // Muda a variavel de controle da primeira iteracao
                        primeiraIt = false;
                    }else {
                        // Se nao for a primeira iteracao faz a comparacao com a referencia salva
                        if(min_peso > aresta->getPeso()) {
                            // Atualiza a referencia de menor peso
                            min_peso = aresta->getPeso();
                        }
                        if(max_peso < aresta->getPeso()) {
                            // Atualiza a referencia de maior peso
                            max_peso = aresta->getPeso();
                        }
                    }
                }
            }
        }
    }
    // Variavel de controle que vai retornar para o loop principal
    bool rodando = false;

    // Se nao for a primeira iteracao
    if(!primeiraIt) {
        // Calcula o D_MAX com base na formula
        float d_max = min_peso + (alfa * (max_peso - min_peso));

        // Percorre todos os nos do grafo
        for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            // Se ele nao tiver na solucao ainda, logo nao foi visitado
            if(solucao[no->getId()] != -1) {
                // Percorre todas arestas desse No
                for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
                    // Se a aresta tem o peso menor que o peso calculado da formula e o alvo dela nao foi visitada nem o grupo
                    if (aresta->getPeso() <= d_max && solucao[aresta->getIdAlvo()] == -1 && !gruposVisitados[this->getNo(aresta->getIdAlvo())->getGrupo()]) {
                        // O alvo da aresta entra como possivel no
                        possiveisNos[aresta->getIdAlvo()] = true;
                        // Variavel de controle do algoritmo fica rodando
                        rodando = true;
                    }
                }
            }
        }
    }
    // Retorna o controle do algoritmo
    return rodando;
}
// Fim da funcao para percorrer o grafo no agmg randomizado e retorna o status do algoritmo

// Inicio da funcao para sortear um prox no com base nos nos possiveis
int Grafo::proximoNoAGMGrandomizado(bool possiveisNos[]) {
    // Declarando variaveis de controle
    int qntPossiveis = 0;
    int noEscolhido = -1;

    // Contando quantos nos vao entrar no vetor de possiveis sorteados
    for(int i = 0; i < this->ordem; i++) {
        // Se ele estiver como possivel de ser sorteado incrementa a variavel
        if(possiveisNos[i])
            qntPossiveis++;
    }

    // Se tiver algum no para ser sorteado
    if(qntPossiveis != 0) {
        // Declara o vetor para sortear o no
        int nosSorteados[qntPossiveis];

        // Faz a copia dos nos possiveis para dentro do vetor que vai sortear um no
        int k = 0;
        for(int i = 0; i < this->ordem; i++) {
            if(possiveisNos[i]) {
                nosSorteados[k] = i;
                k++;
            }
        }
        // Seta a seed do aleatorio
        srand(time(0));
        // Pega um no aleatorio
        noEscolhido = nosSorteados[rand()%qntPossiveis];
    }
    // Retorna o no aleatorio
    return noEscolhido;
}
// Fim da funcao para sortear um prox no com base nos nos possiveis

// Inicio da funcao para pegar o no da aresta de menor peso
int Grafo::escolherArestaAGMGrandomizado(int prox_id, int solucao[], bool gruposVisitados[]) {
    // Declarando variavel de peso minimo sendo + infinito
    float min_peso = std::numeric_limits<float>::max();
    // Instanciando variaveis de controle
    float peso_atual;
    int noEscolhido = -1;

    // Percorrendo todos vertices
    for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
        // Se ele ja tiver sido visitado, ou seja, esta na solucao
        if(solucao[no->getId()] != -1) {
            // Verifica se existe aresta entre o no atual do loop com o prox no do algoritmo de prim
            if(no->existeArestaEntre(prox_id)){
                // Pega o peso
                peso_atual = no->getArestaEntre(prox_id)->getPeso();
                // Compara com o menor peso, se for a primeira vez vai entrar porque comeca com + infinito
                if(min_peso > peso_atual){
                    // Atualiza o menor peso e pega o no
                    min_peso = peso_atual;
                    noEscolhido = no->getId();
                }
            }
        }
    }
    // Retorna o No escolhido
    return noEscolhido;
}
// Fim da funcao para pegar o no da aresta de menor peso

// Inicio funcao agmg prim randomizado reativo
string Grafo::AGMGPrimRandomizadoReativo() {
    // Variavel de controle para o numero de iteracoes tera o algoritmo
    int NUM_ITERACOES = 500;
    // Variavel para incrementar a iteracao atual
    int qnt_iteracoes = 0;
    // Variavel de controle para armazenar o id do no de origem
    int id_origem = 0;
    // Variavel de controle para saber o index do alfa atual
    int i_alfa = 0;
    // Para armazenar o melhor alfa
    int i_melhor_alfa = 0;
    // Solucao do algoritmo que vai ser passa para funcao aux
    int solucao[this->ordem];
    // Armazenar o backup da melhor solucao
    int melhorSolucao[this->ordem];
    // Armazenar o melhor custo, comeca como + infinito para o primeiro custo entrar como melhor
    float melhorCusto = std::numeric_limits<float>::max();
    // Custo da solucao atual
    float custoSolucao = 0;
    // Vetor de alfas a serem testados
    float alfas[5] = {0.05, 0.10, 0.15, 0.30, 0.50};

    // Enquanto nao percorrer todas iteracoes nao acaba
    while(NUM_ITERACOES > qnt_iteracoes) {
        // Percorre passando o id de todos vertices do grafo
        for (int i = 0; i < this->ordem; i++) {
            // Verifica qual iteracao esta e troca o id do alfa
            if(qnt_iteracoes >= 100 && qnt_iteracoes < 200)
                i_alfa = 1;
            else if(qnt_iteracoes >= 200 && qnt_iteracoes < 300)
                i_alfa = 2;
            else if(qnt_iteracoes >= 300 && qnt_iteracoes < 400)
                i_alfa = 3;
            else if(qnt_iteracoes >= 400)
                i_alfa = 4;
            // Chama o algoritmo e armazena o custo dele
            custoSolucao = this->auxAGMGPrimRandomizado(i, alfas[i_alfa], solucao);
            // Incrementa o quantidade de iteracoes
            qnt_iteracoes++;
            // Se o custo for melhor do que o melhor custo
            if (custoSolucao < melhorCusto) {
                // Faz o backup da solucao
                for (int j = 0; j < this->ordem; j++) {
                    melhorSolucao[j] = solucao[j];
                }
                // Pega o id de origem da atual melhor solucao
                id_origem = i;
                // Atualiza o melhor custo
                melhorCusto = custoSolucao;
                // Salva o alfa da melhor solucao
                i_melhor_alfa = i_alfa;
            }
        }
    }

    // Daqui para baixo e so salvando a solucao no arquivo de saida
    string retorno = "AGMG Guloso Randomizado Reativo - Prim\n";
    if(this->direcionado){
        retorno += "Erro! Grafo direcionado!";
        return retorno;
    }

    string seta = " -- ";
    retorno += "// Vértice Inicial = " + std::to_string(id_origem) + "\n";
    retorno += "// Custo Total = " + std::to_string(melhorCusto) + "\n";
    retorno += "// Qtd. Grupos = " + std::to_string(this->qtdGrupos) + "\n";
    retorno += "// Alfa = " + std::to_string(alfas[i_melhor_alfa]) + "\n";
    retorno += "strict graph { \n";

    string cores[10] = {"red", "orange", "blue", "yellow", "gray", "beige", "pink", "green", "violet", "purple"};
    int grupo = 0;
    for(int i = 0; i < this->ordem; i++) {
        if(melhorSolucao[i] != -1) {
            grupo = this->getNo(i)->getGrupo();
            if(grupo <= this->qtdGrupos){
                retorno += "\t" + std::to_string(i) + " [color=" + cores[grupo-1] + "]" + "\n";
            }
            retorno += "\t" + std::to_string(i) + seta + std::to_string(melhorSolucao[i]) + " [label=" + std::to_string(this->getNo(i)->getArestaEntre(melhorSolucao[i])->getPeso()) + "]" + "\n";
        }
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim funcao agmg prim randomizado reativo



















//Inicio Algoritmo Guloso AGMG

//string Grafo::AGMG(){
//    //Criando string de retorno
//    string retorno = "Algoritmo Guloso AGMG\n";
//    //Caso seja um grafo direcionado, retornar erro
//    if(this->direcionado){
//        retorno += "Erro! Grafo direcionado!";
//        return retorno;
//    }
//    //Criando pilha auxiliar para guardar as arestas não auxiliares do grafo.
//    stack<Aresta*> pilhaAux;
//    //Variável para guardar a quantidade de arestas
//    int qtdArestas = 0;
//    for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()){
//        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
//            if(!aresta->getAux()){
//                //Colocando as arestas na pilha e aumentando o valor de qtdArestas
//                pilhaAux.push(aresta);
//                qtdArestas++;
//            }
//        }
//    }
//    //Vetor de arestas saida com tamanho igual a quantidade de arestas, utilizado para imprimir o resultado mais a frente
//    Aresta* saida[qtdArestas];
//    //Caso o grafo não contenha arestas, imprimir somente os vertices isolados e retornar
//    if(qtdArestas == 0){
//        retorno += "strict graph { \n";
//        for(int i=0; i<this->ordem; i++){
//            retorno += "\t" + std::to_string(this->getIdAuxPorId(i)) + "\n";
//        }
//        retorno += "} \n";
//        retorno += "---------------------------------------";
//        return retorno;
//    }
//    //Vetor para armazenar as arestas do grafo
//    Aresta* arestas[qtdArestas];
//    int i = 0;
//    while(!pilhaAux.empty()){
//        arestas[i] = pilhaAux.top();
//        pilhaAux.pop();
//        i++;
//    }
//    int contador = 0;
//    //Laço para colocar as arestas em ordem de maior para menor peso
//    while(contador < qtdArestas){
//        arestaMenorPeso(&pilhaAux, arestas, qtdArestas);
//        contador++;
//    }
//    stack<Aresta*> pilha;
//    //Invertendo a ordem das arestas, para que o topo da pilha sempre seja a aresta de menor peso
//    while(!pilhaAux.empty()){
//        pilha.push(pilhaAux.top());
//        pilhaAux.pop();
//    }
//    int gama[this->qtdGrupos];
//    for(int i=0; i<this->qtdGrupos; i++){
//        gama[i] = -1;
//    }
//    //Cria vetor auxiliar para verificação de ciclos nas subarvores "criadas"
//    int subarvores[this->ordem];
//    for(No* noAux = this->getPrimeiroNo(); noAux != nullptr; noAux = noAux->getProxNo()){
//        //Cria subarvores com vertices sozinhos
//        subarvores[noAux->getId()] = noAux->getId();
//    }
//    contador = 0;
//    while(contador < this->qtdGrupos -1 && !pilha.empty()){
//        Aresta* atual = pilha.top();
//        pilha.pop();
//        No* noOrigem = this->getNo(atual->getIdOrigem());
//        No* noAlvo = this->getNo(atual->getIdAlvo());
//        if(gama[noAlvo->getGrupo()] == -1 && gama[noOrigem->getGrupo()] == -1){
//            if(noOrigem->getGrupo() != noAlvo->getGrupo()){
//                saida[contador] = atual;
//                gama[noOrigem->getGrupo()] = noOrigem->getId();
//                gama[noAlvo->getGrupo()] = noAlvo->getId();
//                contador++;
//            }
//        }
//        else if(gama[noAlvo->getGrupo()] == noAlvo->getId() && gama[noOrigem->getGrupo()] == -1){
//            saida[contador] = atual;
//            gama[noOrigem->getGrupo()] = noOrigem->getId();
//            contador++;
//        }
//        else if(gama[noAlvo->getGrupo()] == -1 && gama[noOrigem->getGrupo()] == noOrigem->getId()){
//            saida[contador] = atual;
//            gama[noAlvo->getGrupo()] = noAlvo->getId();
//            contador++;
//        }
//        else if(gama[noAlvo->getGrupo()] == noAlvo->getId() && gama[noOrigem->getGrupo()] == noOrigem->getId()){
//            //Chama a função para identificar a subarvore dos vértices de origem e alvo da aresta
//            int a = verificaSubarvore(noOrigem->getId(), subarvores);
//            int b = verificaSubarvore(noAlvo->getId(), subarvores);
//            //Caso estejam em subarvores diferentes, adiciona a aresta na saida (resolução)
//            if(a != b){
//                saida[contador] = atual;
//                contador++;
//                //Coloca os vértices na mesma subarvore
//                subarvores[a] = b;
//            }
//        }
//    }
//    //Cria o cabeçalho do arquivo .dot
//    string seta;
//    retorno += "strict graph { \n";
//    seta = " -- ";
//    //Imprime as arestas do retorno
//    for(int i=0; i<contador; i++){
//        retorno += "\t" + std::to_string(saida[i]->getIdAuxOrigem()) + seta + std::to_string(saida[i]->getIdAuxAlvo()) + " [label=" + std::to_string(saida[i]->getPeso()) + "]" + "\n";
//    }
//    //Imprime os vértices isolados da árvore
//    for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()){
//        if(no->getPrimeiraAresta() == nullptr){
//            retorno += "\t" + std::to_string(no->getIdAux()) + "\n";
//        }
//    }
//    retorno += "} \n";
//    retorno += "---------------------------------------";
//    return retorno;
//}

//Fim Algoritmo Guloso AGMG
