#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Grafo.h"
#include "No.h"

using namespace std;

// Inicio da funcao para leitura do arquivo de entrada
Grafo* leitura(ifstream& arquivo, int direcionado, int aresta_ponderado, int no_ponderado){

    int id_no_origem;
    int id_no_alvo;
    int ordem;

    // Pegando a ordem do grafo
    arquivo >> ordem;

    // Criando objeto grafo
    Grafo* grafo = new Grafo(ordem, direcionado, aresta_ponderado, no_ponderado);

    // Leitura do arquivo
    if(!grafo->getArestaPonderado() && !grafo->getNoPonderado()){
        // Primeiro caso: aresta sem peso e no sem peso
        float peso_aresta;
        while(arquivo >> id_no_origem >> id_no_alvo >> peso_aresta) {
            // Aresta sem peso por padrao recebe peso 1
            peso_aresta = 1;
            cout << "No: " << id_no_origem << endl;
            grafo->inserirAresta(id_no_origem, id_no_alvo, peso_aresta);
        }
    }else if(grafo->getArestaPonderado() && !grafo->getNoPonderado()){
        // Segundo caso: aresta com peso e no sem peso
        float peso_aresta;
        while(arquivo >> id_no_origem >> id_no_alvo >> peso_aresta) {
            grafo->inserirAresta(id_no_origem, id_no_alvo, peso_aresta);
        }
    }else if(grafo->getNoPonderado() && !grafo->getArestaPonderado()){
        // Terceiro caso: aresta sem peso e no com peso
        float peso_no_origem, peso_no_alvo, peso_aresta;
        while(arquivo >> id_no_origem >> peso_no_origem >> id_no_alvo >> peso_no_alvo) {
            peso_aresta = 1;
            grafo->inserirAresta(id_no_origem, id_no_alvo, peso_aresta);
            grafo->getNo(id_no_origem)->setPeso(peso_no_origem);
            grafo->getNo(id_no_alvo)->setPeso(peso_no_alvo);
        }
    }else if(grafo->getNoPonderado() && grafo->getArestaPonderado()){
        // Quarto caso: aresta com peso e no com peso
        float peso_no_origem, peso_no_alvo, peso_aresta;
        while(arquivo >> id_no_origem >> peso_no_origem >> id_no_alvo >> peso_no_alvo >> peso_aresta) {
            grafo->inserirAresta(id_no_origem, id_no_alvo, peso_aresta);
            grafo->getNo(id_no_origem)->setPeso(peso_no_origem);
            grafo->getNo(id_no_alvo)->setPeso(peso_no_alvo);
        }
    }

    return grafo;
}
// Fim da funcao para leitura do arquivo de entrada

// Inicio funcao salvar string em .dot
void salvarStringDot(string retorno, ofstream& arquivo_saida) {
    arquivo_saida << retorno;
}
// Fim funcao salvar string em .dot

// Inicio funcao opcoes no menu
int menu() {
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Fecho Transitivo Direto" << endl;
    cout << "[2] Fecho Transitivo Indireto" << endl;
    cout << "[3] Caminho Minimo entre dois vertices - Dijkstra" << endl;
    cout << "[4] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[5] Arvore Geradora Minima de Prim" << endl;
    cout << "[6] Arvore Geradora Minima de Kruskal" << endl;
    cout << "[7] Arvore pelo Caminhamento em Profundidade" << endl;
    cout << "[8] Imprimir Ordenacao Topologica" << endl;
    cout << "[9] Imprimir Grafo de Entrada" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;
    return selecao;
}
// Fim funcao opcoes no menu

// Inicio funcao menu salvar arquivo
int menuSalvar() {
    int selecao;

    cout << "Voce deseja salvar o resultado da operacao?" << endl;
    cout << "[0] Nao" << endl;
    cout << "[1] Sim" << endl;

    cin >> selecao;

    return selecao;
}
// Fim funcao menu salvar arquivo

// Inicio funcao selecionar no menu
void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida) {
    //String de retorno dos resultados das funcoes, utilizada para exportar o grafo em .dot no arquivo de saida.
    string retorno = "";
    switch (selecao) {
        // Fecho Transitivo Direto
        case 1:{
            retorno = grafo->fechoTD(2);
            break;
        }
        // Fecho Transitivo Indireto
        case 2:{
            retorno = grafo->fechoTI(5);
            break;
        }
        // Caminho Minimo entre dois vertices - Dijkstra
        case 3:{
            retorno = grafo->djikstra(3,5);
            break;
        }
        // Caminho Minimo entre dois vertices - Floyd
        case 4:{
            retorno = grafo->floyd(3,5);
            break;
        }
        // Arvore Geradora Minima de Prim
        case 5:{
            int vertices[5] = {1, 2, 3, 4, 5};
            int tamanho = sizeof(vertices)/sizeof(vertices[0]);
            Grafo* subGrafo = grafo->subgrafo(vertices, tamanho);
            retorno = subGrafo->agmPrim();
            break;
        }
        // Arvore Geradora Minima de Kruskal
        case 6:{
            cout << "Opcao 6 nao implementada" << endl;
            break;
        }
        // Arvore pelo Caminhamento em Profundidade
        case 7:{
            retorno = grafo->buscaProf(1);
            break;
        }
        // Imprimir Ordenacao Topologica
        case 8:{
            retorno = grafo->ordTopologica();
            break;
        }
        // Imprimir Grafo de Entrada
        case 9:{
            retorno = grafo->imprimir();
            break;
        }
        case 0:{
            cout << "Encerrando o programa" << endl;
            return;
        }
        default:{
            cout << "Erro: Opcao invalida!" << endl;
        }
    }
    //Chamada da funcao para verificar se o usuario quer salvar o grafo no arquivo de saida
    int selecaoSalvar = menuSalvar();
    if(selecaoSalvar) {
        salvarStringDot(retorno, arquivo_saida);
    }else {
        salvarStringDot("Voce nao salvou a operacao", arquivo_saida);
    }
}
// Fim funcao selecionar no menu

// Inicio funcao main menu
int mainMenu(ofstream& arquivo_saida, Grafo* grafo){
    int selecao = 1;

    while(selecao != 0){
//        system("@cls||clear");
        selecao = menu();

        if(arquivo_saida.is_open()){
            selecionar(selecao, grafo, arquivo_saida);
        }else{
            cout << "Erro ao abrir o arquivo de saida!" << endl;
        }

        arquivo_saida << endl;
    }

    return 0;
}
// Fim funcao main menu

// Inicio funcao main
int main(int argc, char const *argv[]) {

    // Verifica se todos parametros necessarios para compilar foram definidos
    if (argc != 6) {
        cout << "Erro: Esperando: ./<program_name> <arquivo_entrada> <arquivo_saida> <direcionado> <aresta_ponderado> <no_ponderado> " << endl;
        return 1;
    }

    string nome_programa(argv[0]);
    string nome_arquivo_entrada(argv[1]);

    string instancia;
    if(nome_arquivo_entrada.find("v") <= nome_arquivo_entrada.size()) {
        string instancia = nome_arquivo_entrada.substr(nome_arquivo_entrada.find("v"));
        cout << "Executando " << nome_programa << " com instancia " << instancia << " ... " << endl;
    }

    // Abrindo arquivos de entrada e saida
    ifstream arquivo_entrada;
    ofstream arquivo_saida;
    arquivo_entrada.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);

    // Criando grafo da leitura do arquivo
    Grafo* grafo;

    // Verificando se conseguiu abrir o arquivo de entrada
    if(arquivo_entrada.is_open()) {
        grafo = leitura(arquivo_entrada, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }else {
        cout << "Nao foi possivel abrir o arquivo de entrada: " << argv[1];
    }

    // Chamando main menu
    mainMenu(arquivo_saida, grafo);

    // Fechando arquivo de entrada
    arquivo_entrada.close();

    // Fechando arquivo de saída
    arquivo_saida.close();

    return 0;
}
// Fim funcao main