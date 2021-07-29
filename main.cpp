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

Grafo* leitura(ifstream& input_file, int directed, int weightedEdge, int weightedNode){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int id_no_origem;
    int id_no_alvo;
    int ordem;

    //Pegando a ordem do grafo
    input_file >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(ordem, directed, weightedEdge, weightedNode);

    //Leitura de arquivo
    if(!grafo->getArestaPonderado() && !grafo->getNoPonderado()){
        while(input_file >> id_no_origem >> id_no_alvo) {
            grafo->inserirAresta(id_no_origem, id_no_alvo, 0);
        }

    }else if(grafo->getArestaPonderado() && !grafo->getNoPonderado() ){

        float peso_aresta;

        while(input_file >> id_no_origem >> id_no_alvo >> peso_aresta) {

            grafo->inserirAresta(id_no_origem, id_no_alvo, peso_aresta);

        }

    }else if(grafo->getNoPonderado() && !grafo->getArestaPonderado()){

        float peso_no_origem, peso_no_alvo;

        while(input_file >> id_no_origem >> peso_no_origem >> id_no_alvo >> peso_no_alvo) {
            grafo->inserirAresta(id_no_origem, id_no_alvo, 0);
            grafo->getNo(id_no_origem)->setPeso(peso_no_origem);
            grafo->getNo(id_no_alvo)->setPeso(peso_no_alvo);
        }

    }else if(grafo->getNoPonderado() && grafo->getArestaPonderado()){

        float peso_no_origem, peso_no_alvo, peso_aresta;

        while(input_file >> id_no_origem >> peso_no_origem >> id_no_alvo >> peso_no_alvo) {

            grafo->inserirAresta(id_no_origem, id_no_alvo, peso_aresta);
            grafo->getNo(id_no_origem)->setPeso(peso_no_origem);
            grafo->getNo(id_no_alvo)->setPeso(peso_no_alvo);
        }
    }

    return grafo;
}

//Grafo* leituraInstancia(ifstream& input_file, int directed, int weightedEdge, int weightedNode){
//
//    //Variáveis para auxiliar na criação dos nós no Grafo
//    int idNodeSource;
//    int idNodeTarget;
//    int order;
//    int numEdges;
//
//    //Pegando a ordem do grafo
//    input_file >> order >> numEdges;
//
//    //Criando objeto grafo
//    Grafo* graph = new Grafo(order, directed, weightedEdge, weightedNode);
//
//    //Leitura de arquivo
//    while(input_file >> idNodeSource >> idNodeTarget) {
//
//        graph->inserirAresta(idNodeSource, idNodeTarget, directed, 0);
//
//    }
//
//    return graph;
//}

int menu(){
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Subgrafo induzido por conjunto de vertices" << endl;
    cout << "[2] Caminho Minimo entre dois vertices - Dijkstra" << endl;
    cout << "[3] Caminho Minimo entre dois vertices - Floyd" << endl;
    cout << "[4] Arvore Geradora Minima de Prim" << endl;
    cout << "[5] Arvore Geradora Minima de Kruskal" << endl;
    cout << "[6] Imprimir caminhamento em largura" << endl;
    cout << "[7] Imprimir ordenacao topologica" << endl;
    cout << "[8] Algoritmo Guloso" << endl;
    cout << "[9] Algoritmo Guloso Randomizado " << endl;
    cout << "[10] Algoritmo Guloso Randomizado Reativo" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, Grafo* grafo, ofstream& output_file){

    switch (selecao) {
        //Subgrafo induzido por um conjunto de vertices X;
        case 1:{
            cout << "Opcao 1 nao implementada";
            break;
        }
        //Caminho minimo entre dois vertices usando Dijkstra;
        case 2:{
            cout << "Opcao 2 nao implementada";
            break;
        }
        //Caminho minimo entre dois vertices usando Floyd;
        case 3:{
            cout << "Opcao 3 nao implementada";
            break;
        }
        //AGM - Kruscal;
        case 4:{
            cout << "Opcao 4 nao implementada";
            break;
        }
        //AGM Prim;
        case 5:{
            cout << "Opcao 5 nao implementada";
            break;
        }
        //Busca em largura;
        case 6:{
            cout << "Opcao 6 nao implementada";
            break;
        }
        //Ordenação Topologica;
        case 7:{
            cout << "Opcao 7 nao implementada";
            break;
        }
        default:{
            cout << " Error!!! invalid option!!" << endl;
        }

    }
}

int mainMenu(ofstream& output_file, Grafo* grafo){
    int selecao = 1;

    while(selecao != 0){
        system("@cls||clear");
        selecao = menu();

        if(output_file.is_open()){
            selecionar(selecao, grafo, output_file);
        }else{
            cout << "Unable to open the output_file" << endl;
        }

        output_file << endl;
    }

    return 0;
}



int main(int argc, char const *argv[]) {

//    Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {
        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;
    }else{
        cout << "Todos parametros para rodar foram definidos";
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if(input_file_name.find("v") <= input_file_name.size()){
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Grafo* grafo;

    if(input_file.is_open()){
        grafo = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }else
        cout << "Unable to open " << argv[1];

//    mainMenu(output_file, grafo);

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    grafo->fechoTD(2);
    cout << "=====================" << endl;
    grafo->buscaProf(2);

//    grafo->imprimir();
//    grafo->salvarDot();

    return 0;
}
