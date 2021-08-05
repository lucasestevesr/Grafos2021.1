#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
# include <limits>


using namespace std;

Grafo::Grafo(int ordem, bool direcionado, bool aresta_ponderado, bool no_ponderado) {
    this->ordem = 0;
    this->direcionado = direcionado;
    this->aresta_ponderado = aresta_ponderado;
    this->no_ponderado = no_ponderado;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->num_arestas = 0;

    for(int i = 0; i < ordem; i++) {
        this->inserirNo(i);
    }
}

Grafo::~Grafo() {
    No* prox_no = this->primeiro_no;

    while (prox_no != nullptr) {
        prox_no->removerTodasArestas();
        No* aux_no = prox_no->getProxNo();
        delete prox_no;
        prox_no = aux_no;
    }
}

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

No* Grafo::getNo(int id) {
    if(this->primeiro_no != nullptr) {
        for (No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            if(no->getId() == id) {
                return no;
            }
        }
    }
    return NULL;
}

bool Grafo::existeNo(int id) {
    if(this->primeiro_no != nullptr) {
        for (No* no = this->primeiro_no; no != nullptr ; no = no->getProxNo()) {
            if(no->getId() == id) {
                return true;
            }
        }
    }
    return false;
}

void Grafo::inserirNo(int id) {
    No* no = new No(id);

    if(this->primeiro_no == nullptr){
        this->primeiro_no = no;
        this->ultimo_no = no;
    }else{
        this->ultimo_no->setProxNo(no);
        this->ultimo_no = no;
    }
    ordem ++;
}

void Grafo::removerNo(int id) {
    if(existeNo(id)) {
        No* node = this->getPrimeiroNo();
        No* temp = nullptr;

        while(node->getId() != id) {
            temp = node;
            node = node->getProxNo();
        }

        if(temp != nullptr)
            temp->setProxNo(node->getProxNo());
        else
            this->primeiro_no = node->getProxNo();

        if(node == this->ultimo_no)
            this->ultimo_no = temp;

        if(node->getProxNo() == this->ultimo_no)
            this->ultimo_no = node->getProxNo();

        No* aux = this->getPrimeiroNo();

        while(aux != nullptr) {
            aux->removerAresta(node->getId(), this->direcionado, node);
            aux = aux->getProxNo();
        }

        delete node;
        this->ordem--;
    }
}

void Grafo::inserirAresta(int id, int id_alvo, float peso) {
    if(existeNo(id) && existeNo(id_alvo)) {
        No* no_origem = this->getNo(id);
        No* no_alvo = this->getNo(id_alvo);
        if(this->direcionado) {
            no_origem->inserirAresta(id_alvo, peso);
            no_origem->aumentarGrauSaida();
            no_alvo->aumentarGrauEntrada();
        }else {
            no_origem->inserirAresta(id_alvo, peso);
            no_alvo->inserirAresta(id, peso);
            no_origem->aumentarGrauSaida();
            no_origem->aumentarGrauEntrada();
            no_alvo->aumentarGrauSaida();
            no_alvo->aumentarGrauEntrada();
        }
        this->num_arestas++;
    }else{
        cout << "Erro: Algum dos Nos da aresta nao existe!" << endl;
    }
}

void Grafo::imprimir() {
    cout << "Funcao imprimir Grafo: " << endl;
    if(this->primeiro_no != nullptr) {
        for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            cout << "No: "  << no->getId() << endl;
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
                if(!aresta->getDirecionado() || this->direcionado){
                    cout << no->getId()  << " " << aresta->getIdAlvo() << endl;
                }
            }
        }
    }else {
        cout << "Grafo vazio" << endl;
    }
}

void Grafo::salvarDot() {
    std::ofstream saida("saida.dot");

    if(!saida.is_open()){
        std::cerr << "Erro na abertura do arquivo" << std::endl;
    }

    if(this->primeiro_no != nullptr) {
        if(this->direcionado) {
            saida << "digraph {" << std::endl;
        }else {
            saida << "strict graph {" << std::endl;
        }
        for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
                if(this->direcionado) {
                    saida << "\t" << no->getId()  << " -> " << aresta->getIdAlvo() << ";" << std::endl;
                }else {
                    saida << "\t" << no->getId()  << " -- " << aresta->getIdAlvo() << ";" << std::endl;
                }
            }
        }
        saida << "}" << std::endl;
    }else {
        saida << "Erro: Grafo vazio" << std::endl;
    }
}

// Funcionalidades do trabalho

// Inicio Fecho Transitivo Direto
string Grafo::fechoTD(int id) {
    // Criando string de retorno
    string retorno = "------- Fecho Transitivo Direto ------- \n";

    if(!this->direcionado) {
        retorno += "Erro: O grafo precisa ser direcionado! \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    retorno += "digraph { \n";

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
                retorno += "\t" + std::to_string(no->getId()) + " -> " + std::to_string(aresta->getIdAlvo()) + "\n";
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
string Grafo::fechoTI(int id) {
    // Criando string de retorno
    string retorno = "------- Fecho Transitivo Indireto ------- \n";

    if(!this->direcionado) {
        retorno += "Erro: O grafo precisa ser direcionado! \n";
        retorno += "---------------------------------------";
        return retorno;
    }

    retorno += "digraph { \n";

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
                retorno += "\t" + std::to_string(no->getId())  + " -> " + std::to_string(topo) + "\n";
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

// Inicio Caminho Minimo por Djikstra
string Grafo::djikstra(int id, int id_alvo) {
    // Criando string de retorno
    string retorno = "------- Caminho Minimo Dijkstra ------- \n";

    // Verificando se o grafo possui peso nas arestas, e retornando caso nao seja.
    if(!this->aresta_ponderado) {
        retorno += "Erro: O grafo precisa ter Arestas ponderadas! \n";
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
        auxCaminho[i] = id;
    }
    // Inicializando a distancia do vertice de origem para ele mesmo como 0, e marcando-o como visitado
    dist[id] = 0;
    visitados[id] = true;
    No* noAux = this->getNo(id);
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
        retorno += "\t" + std::to_string(k) + seta + std::to_string(auxK) + "\n";
    } while(k != id);
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
string Grafo::floyd(int id, int id_alvo) {
    // Criando string de retorno
    string retorno = "------- Caminho Minimo Floyd ------- \n";

    // Verificando se o grafo possui peso nas arestas, e retornando caso nao seja.
    if(!this->aresta_ponderado) {
        retorno += "Erro: O grafo precisa ter Arestas ponderadas! \n";
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

    /* Caso a distancia do vertice alvo ao vertice de origem seja infinito, nao existe caminho entre eles.
    Portanto, e impresso na tela uma mensagem de erro e encerrada a funcao */
    if(distancia[id][id_alvo] == infinito) {
        retorno += "Erro: Nao existe caminho entre os vertices! \n";
        retorno += "---------------------------------------";
        return retorno;
    }
    // Variaveis auxiliares para recuperar o caminho mais curto
    int id_o = id, id_a = id_alvo;
    float pesoAresta;
    // Partindo do Id de Origem, enquanto nao chegar no Alvo nao para
    while(id_o != id_a) {
        pesoAresta = distancia[id_o][proximo[id_o][id_a]];
        retorno += "\t" + std::to_string(id_o) + seta;
        id_o = proximo[id_o][id_a];
        retorno += std::to_string(id_o) + " [label=" + std::to_string(pesoAresta) + "]" + "\n";
    }
    retorno += "} \n";
    retorno += "Custo caminho: " + std::to_string(distancia[id][id_alvo]) + "\n";
    retorno += "---------------------------------------";
    return retorno;
}
//Fim Caminho Minimo por Floyd

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
            retorno += std::to_string(caminho[i]) + seta + std::to_string(i) + "\n";
        if(caminho[i] == -1 && i != id_origem)
            retorno += std::to_string(i) + "\n";
    }
    retorno += "} \n";
    retorno += "---------------------------------------";
    return retorno;
}

//Grafo* Grafo::subgrafo(int tamanho, int conjunto[], bool direcao, bool aresta_ponderada, bool no_ponderado, Grafo* origem){
//    Grafo* subgrafo = new Grafo(tamanho, direcao, aresta_ponderada, no_ponderado);
//    for(No* no = origem->getPrimeiroNo(); no != nullptr; no = no->getProxNo()){
//        for(int i=0; i<tamanho; i++){
//            if(no->getId() == conjunto[i]){
//                for(int j=0; j<tamanho; j++){
//                    if(no->existeArestaEntre(conjunto[j])){
//                        Aresta* aresta = no->getArestaEntre(conjunto[j]);
//                        subgrafo->inserirAresta(conjunto[i], conjunto[j], aresta->getPeso());
//                    }
//                }
//            }
//        }
//    }
//    return subgrafo;
//}

//string Grafo::prim(int tamanho, int conjunto[]){
//    Grafo* subgrafo = this->subgrafo(tamanho, conjunto, this->direcionado, this->aresta_ponderado, this->no_ponderado, this);
//    string retorno = "";
//    retorno = subgrafo->agmPrim();
//    return retorno;
//}

string Grafo::buscaProf(int id_origem) {
    // Criando string de retorno
    string retorno = "------- Caminhamento em Profundidade ------- \n";

    if(this->direcionado)
        retorno += "digraph { \n";
    else
        retorno += "strict graph { \n";

    // Criando vetor para armazenar o Nos visitados
    bool visitados[this->ordem];

    // Marcando todos Nos como nao visitados
    for(int i = 0; i < this->ordem; i++)
        visitados[i] = false;

    // Marcando No de origem como visitado
    visitados[id_origem] = true;

    // Chamando funcao aux para entrar na recursividade
    auxBuscaProf(id_origem, visitados, &retorno);

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
            *retorno += "\t" + std::to_string(no->getId()) + seta + std::to_string(aresta->getIdAlvo()) + "\n";
            // Chamando recursividade novamente
            this->auxBuscaProf(aresta->getIdAlvo(), visitados, retorno);
        }
    }
}


// Nao usada
//bool Grafo::auxBuscaLista(list<int>* lista, int id) {
//    list<int>::iterator it;
//    for(it = lista->begin(); it!=lista->end();it++){
//        if(*it == id) {
//            return true;
//        }
//    }
//    return false;
//}