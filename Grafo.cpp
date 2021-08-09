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
string Grafo::fechoTI(int id_aux) {
    // Criando string de retorno
    string retorno = "------- Fecho Transitivo Indireto ------- \n";

    if(!this->direcionado) {
        retorno += "Erro: O grafo precisa ser direcionado! \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    // Cabecalho do Grafo em .dot
    retorno += "digraph { \n";

    // Convertendo id auxiliar para id interno
    int id = this->getIdPorIdAux(id_aux);

    // Criando uma pilha auxiliar e colocando o no inicial no topo dela
    stack<int> pilhaAux;
    pilhaAux.push(id);

    // Enquanto a pilha nao for vazia fica rodando
    while(!pilhaAux.empty()) {

        // Recuperando o no do primeiro id da pilha
        int topo = pilhaAux.top();

        // Removendo o topo da pilha
        pilhaAux.pop();

        // Percorrendo Nos do grafo a partir do No que estava no topo da pilha e acabou de ser removido
        for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()) {
            // Verifica se o No alvo possui aresta com o No atual do for
            if(no->existeArestaEntre(topo)) {
                // Preenchendo string de retorno para salvar no arquivo .dot depois
                retorno += "\t" + std::to_string(no->getIdAux())  + " -> " + std::to_string(getIdAuxPorId(topo)) + "\n";
                // No a ser verificado, alimentando o while principal da funcao
                pilhaAux.push(no->getId());
            }
        }
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim Fecho Transitivo Indireto

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
    //Verificando se os vertices existem no grafo
    if(!this->existeNoPorIdAux(id_aux_origem) || !this->existeNoPorIdAux(id_aux_alvo)){
        cout << "Algum dos vertices nao existe! Favor inserir outros vertices!";
        return "";
    }
    // Criando string de retorno
    string retorno = "------- Caminho Minimo Dijkstra ------- \n";

    // Convertendo id aux origem e id aux alvo para id e id alvo
    int id_origem = getIdPorIdAux(id_aux_origem);
    int id_alvo = getIdPorIdAux(id_aux_alvo);
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

    /* Caso a distancia do vertice alvo ao vertice de origem seja infinito, nao existe caminho entre eles.
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
        if(visitados[i]==false && dist[i]<=min){
            min = dist[i];
            idMenor = i;
        }
    }
    // Retorna o vertice de menor valor de distancia
    return idMenor;
}
// Fim função auxiliar menor distancia

// Inicio Caminho Minimo por Floyd
string Grafo::floyd(int id_aux_origem, int id_aux_alvo) {
    //Verificando se os vertices existem no grafo
    if(!this->existeNoPorIdAux(id_aux_origem) || !this->existeNoPorIdAux(id_aux_alvo)){
        cout << "Algum dos vertices nao existe! Favor inserir outros vertices!";
        return "";
    }
    // Criando string de retorno
    string retorno = "------- Caminho Minimo Floyd ------- \n";

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
    string retorno = "AGM por Prim\n";
    string seta;
    if(this->direcionado) {
        retorno += "digraph { \n";
        seta = " -> ";
    }else {
        retorno += "strict graph { \n";
        seta = " -- ";
    }
    for(int i=0; i<this->ordem; i++){
        if(caminho[i] != -1)
            retorno += std::to_string(this->getIdAuxPorId(caminho[i])) + seta + std::to_string(this->getIdAuxPorId(i)) + "\n";
        if(caminho[i] == -1 && i != id_origem)
            retorno += std::to_string(this->getIdAuxPorId(i)) + "\n";
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}
// Fim AGM de Prim

string Grafo::agmKruskal(){
    stack<Aresta*> pilhaAux;
    Aresta* saida[this->ordem - 1];
    for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProxNo()){
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            if(!aresta->getAux())
                pilhaAux.push(aresta);
        }
    }
    Aresta* arestas[pilhaAux.size()];
    int i = 0;
    while(!pilhaAux.empty()){
        arestas[i] = pilhaAux.top();
        pilhaAux.pop();
        i++;
    }
    int contador = 0;
    while(contador < this->num_arestas){
        arestaMenorPeso(&pilhaAux, arestas);
        contador++;
    }
    stack<Aresta*> pilha;
    while(!pilhaAux.empty()){
        pilha.push(pilhaAux.top());
        pilhaAux.pop();
    }
    //Cria vetor auxiliar para verificação de ciclos nas subarvores "criadas"
    int subarvores[this->ordem];
    for(int i=0; i<this->ordem; i++){
        //"Cria" subárvores com nós sozinhos
        subarvores[i] = i;
    }
    contador = 0;
    while(contador != this->ordem - 1){
        Aresta* atual = pilha.top();
        pilha.pop();
        int a = verificaSubarvore(atual->getIdOrigem(), subarvores);
        int b = verificaSubarvore(atual->getIdAlvo(), subarvores);
        if(a != b){
            saida[contador] = atual;
            contador++;
            subarvores[a] = b;
        }
    }
    string retorno = "AGM por Kruskal\n";
    string seta;
    if(this->direcionado) {
        retorno += "digraph { \n";
        seta = " -> ";
    }else {
        retorno += "strict graph { \n";
        seta = " -- ";
    }
    for(int i=0; i<this->ordem - 1; i++){
        retorno += "\t" + std::to_string(saida[i]->getIdAuxOrigem()) + seta + std::to_string(saida[i]->getIdAuxAlvo()) + "\n";
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}

int Grafo::verificaSubarvore(int v,int subarvores[]){

    if(subarvores[v]==v)
        return v;
    return verificaSubarvore(subarvores[v],subarvores);
}

void Grafo::arestaMenorPeso(stack<Aresta*>* pilha, Aresta* arestas[]){
    float infinito = std::numeric_limits<float>::max();
    float menorPeso = infinito;
    int posMenor;
    for(int i=0; i<this->num_arestas; i++){
        if(arestas[i] != nullptr && arestas[i]->getPeso() <= menorPeso){
            menorPeso = arestas[i]->getPeso();
            posMenor = i;
        }
    }
    pilha->push(arestas[posMenor]);
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

    // Marcando todos Nos como nao visitados
    for(int i = 0; i < this->ordem; i++)
        visitados[i] = false;

    // Marcando No de origem como visitado
    visitados[id_origem] = true;

    // Chamando funcao aux para entrar na recursividade
    this->auxBuscaProf(id_origem, visitados, &retorno);

    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}

void Grafo::auxBuscaProf(int id_origem, bool visitados[], string* retorno) {
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
            *retorno += "\t" + std::to_string(aresta->getIdAuxOrigem()) + seta + std::to_string(aresta->getIdAuxAlvo()) + " [color=red] " + "\n";
            // Chamando recursividade novamente
            this->auxBuscaProf(aresta->getIdAlvo(), visitados, retorno);
        }
    }
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

