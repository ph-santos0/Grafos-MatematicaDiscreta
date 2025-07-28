#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

struct Aresta
{
    int vertice;
    int peso;
};

bool direcionado;
int numVertices;
vector<vector<Aresta>> adjacencias;

vector<int> descoberta, termino, antecessor, cor;
vector<int> distancia;
int tempo;

void criarGrafo(bool dir, int vertices)
{
    direcionado = dir;
    numVertices = vertices;
    adjacencias.resize(vertices);
}

void exibirAdjacencias()
{
    cout << "===== Adjacências =====\n";
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Vértice " << i << ":";
        if (!adjacencias[i].empty())
        {
            for (int j = 0; j < adjacencias[i].size(); j++)
            {
                cout << " -> " << adjacencias[i][j].vertice;
            }
        }
        else
        {
            cout << " sem adjacências";
        }
        cout << endl;
    }
    cout << "========================\n";
}

bool consultarAdjacencia(int v1, int v2)
{
    for (int i = 0; i < adjacencias[v1].size(); i++)
    {
        if (adjacencias[v1][i].vertice == v2)
        {
            return true;
        }
    }
    return false;
}

void inserirAresta(int v1, int v2, int peso)
{
    adjacencias[v1].push_back({v2, peso});
    if (!direcionado)
    {
        adjacencias[v2].push_back({v1, peso});
    }
}

void removerAresta(int v1, int v2)
{
    for (int i = 0; i < adjacencias[v1].size(); i++)
    {
        if (adjacencias[v1][i].vertice == v2)
        {
            adjacencias[v1].erase(adjacencias[v1].begin() + i);
            break;
        }
    }

    if (!direcionado)
    {
        for (int i = 0; i < adjacencias[v2].size(); i++)
        {
            if (adjacencias[v2][i].vertice == v1)
            {
                adjacencias[v2].erase(adjacencias[v2].begin() + i);
                break;
            }
        }
    }
}

void importarGrafo(const char *arquivo)
{
    ifstream file(arquivo);
    if (!file.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    string linha;
    getline(file, linha);
    direcionado = (linha.find("sim") != string::npos);

    getline(file, linha);
    numVertices = stoi(linha);

    getline(file, linha);
    int numArestas = stoi(linha);

    adjacencias.resize(numVertices);

    for (int i = 0; i < numArestas; i++)
    {
        int v1, v2, peso;
        file >> v1 >> v2 >> peso;
        inserirAresta(v1, v2, peso);
    }

    file.close();
    cout << "Grafo importado com sucesso!\n";
}

void exportarGrafo(const char *arquivo)
{
    ofstream file(arquivo);
    if (!file.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    file << "direcionado=" << (direcionado ? "sim" : "nao") << endl;
    file << numVertices << endl;

    vector<pair<int, int>> arestasExportadas;
    int numArestas = 0;

    for (int i = 0; i < adjacencias.size(); i++)
    {
        for (int j = 0; j < adjacencias[i].size(); j++)
        {
            int v1 = i;
            int v2 = adjacencias[i][j].vertice;
            if (direcionado || v1 < v2)
            {
                arestasExportadas.push_back({v1, v2});
                numArestas++;
            }
        }
    }

    file << numArestas << endl;

    for (int i = 0; i < arestasExportadas.size(); i++)
    {
        int v1 = arestasExportadas[i].first;
        int v2 = arestasExportadas[i].second;
        for (int j = 0; j < adjacencias[v1].size(); j++)
        {
            if (adjacencias[v1][j].vertice == v2)
            {
                file << v1 << " " << v2 << " " << adjacencias[v1][j].peso << endl;
                break;
            }
        }
    }

    file.close();
    cout << "Grafo exportado com sucesso!\n";
}

void consultarPrimeiroAdjacente(int vertice)
{
    if (!adjacencias[vertice].empty())
    {
        cout << "Primeiro adjacente do vértice " << vertice << ": " << adjacencias[vertice][0].vertice << endl;
    }
    else
    {
        cout << "O vértice " << vertice << " não possui adjacências.\n";
    }
}

void consultarProximoAdjacente(int vertice, int adjAtual)
{
    bool encontrado = false;
    for (int i = 0; i < adjacencias[vertice].size(); i++)
    {
        if (adjacencias[vertice][i].vertice == adjAtual && i + 1 < adjacencias[vertice].size())
        {
            cout << "Próximo adjacente após " << adjAtual << ": " << adjacencias[vertice][i + 1].vertice << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado)
    {
        cout << "Não há próximo adjacente para o vértice " << vertice << " após " << adjAtual << ".\n";
    }
}

void consultarListaAdjacentes(int vertice)
{
    if (!adjacencias[vertice].empty())
    {
        cout << "Lista de adjacentes do vértice " << vertice << ": ";
        for (int i = 0; i < adjacencias[vertice].size(); i++)
        {
            cout << adjacencias[vertice][i].vertice << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "O vértice " << vertice << " não possui adjacências.\n";
    }
}

void visitaEmProfundidade(int vertice)
{
    cor[vertice] = 1;
    tempo++;
    descoberta[vertice] = tempo;
    cout << "Descoberta do vértice " << vertice << " no tempo " << tempo << "\n";

    for (int i = 0; i < adjacencias[vertice].size(); i++)
    {
        int v = adjacencias[vertice][i].vertice;
        if (cor[v] == 0)
        {
            antecessor[v] = vertice;
            visitaEmProfundidade(v);
        }
    }

    cor[vertice] = 2;
    tempo++;
    termino[vertice] = tempo;
    cout << "Finalização do vértice " << vertice << " no tempo " << tempo << "\n";
}

void buscaEmProfundidade()
{
    descoberta.assign(numVertices, 0);
    termino.assign(numVertices, 0);
    antecessor.assign(numVertices, -1);
    cor.assign(numVertices, 0);
    tempo = 0;

    for (int i = 0; i < numVertices; i++)
    {
        if (cor[i] == 0)
        {
            visitaEmProfundidade(i);
        }
    }
}

void visitaEmLargura(int vertice)
{
    vector<int> fila;
    cor[vertice] = 1;
    distancia[vertice] = 0;
    fila.push_back(vertice);
    cout << "Descoberta do vértice " << vertice << "\n";

    while (!fila.empty())
    {
        int v = fila.front();
        fila.erase(fila.begin());

        for (int i = 0; i < adjacencias[v].size(); i++)
        {
            int k = adjacencias[v][i].vertice;
            if (cor[k] == 0)
            {
                cor[k] = 1;
                antecessor[k] = v;
                distancia[k] = distancia[v] + 1;
                fila.push_back(k);
                cout << "Descoberta do vértice " << k << " com distância " << distancia[k] << "\n";
            }
        }
        cor[v] = 2;
        cout << "Finalização do vértice " << v << "\n";
    }
}

void buscaEmLargura()
{
    antecessor.assign(numVertices, -1);
    cor.assign(numVertices, 0);
    distancia.assign(numVertices, 1000);

    for (int i = 0; i < numVertices; i++)
    {
        if (cor[i] == 0)
        {
            visitaEmLargura(i);
        }
    }
}

void prim()
{
    vector<int> menorPesoAresta(numVertices, 1000);
    vector<int> verticePai(numVertices, -1);
    vector<bool> estaNoCirculo(numVertices, false);

    menorPesoAresta[0] = 0;

    for (int i = 0; i < numVertices - 1; i++)
    {
        int minValor = 1000, u = -1;

        for (int v = 0; v < numVertices; v++)
        {
            if (!estaNoCirculo[v] && menorPesoAresta[v] < minValor)
            {
                minValor = menorPesoAresta[v];
                u = v;
            }
        }

        if (u == -1)
            break;

        estaNoCirculo[u] = true;
        cout << "Vértice " << u << " adicionado a circulo.\n";

        for (int j = 0; j < adjacencias[u].size(); j++)
        {
            int v = adjacencias[u][j].vertice;
            int peso = adjacencias[u][j].peso;

            if (!estaNoCirculo[v] && peso < menorPesoAresta[v])
            {
                menorPesoAresta[v] = peso;
                verticePai[v] = u;
                cout << "Atualizando aresta com menor peso do vértice " << v << " para " << peso << "\n";
            }
        }
    }

    cout << "\nÁrvore Geradora Mínima (Prim):\n";
    int pesoTotal = 0;
    for (int v = 1; v < numVertices; v++)
    {
        if (verticePai[v] != -1)
        {
            cout << "Aresta: (" << verticePai[v] << " - " << v << ") com peso " << menorPesoAresta[v] << "\n";
            pesoTotal += menorPesoAresta[v];
        }
    }
    cout << "\nPeso total da árvore: " << pesoTotal << "\n";
}

void dijkstra(int Origem, int Destino)
{
    int origem = Origem;
    int destino = Destino;
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices)
    {
        cout << "Vértices não encontrados!\n";
        return;
    }

    int infinito = 1000;
    vector<int> dist(numVertices, infinito);
    vector<int> antecessor(numVertices, -1);
    vector<bool> visitado(numVertices, false);

    dist[origem] = 0;

    for (int i = 0; i < numVertices; i++)
    {
        int u = -1;
        for (int j = 0; j < numVertices; j++)
        {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }
        if (dist[u] == infinito)
            break;
        visitado[u] = true;

        cout << "Processando vértice " << u << " | Distância: " << dist[u] << "\n";

        for (int j = 0; j < adjacencias[u].size(); j++)
        {
            int v = adjacencias[u][j].vertice, peso = adjacencias[u][j].peso;
            if (!visitado[v] && dist[u] + peso < dist[v])
            {
                dist[v] = dist[u] + peso;
                antecessor[v] = u;
                cout << "Encontrado vértice " << v << " com peso " << dist[v] << "\n";
            }
        }
    }

    if (dist[destino] == infinito)
    {
        cout << "Não há caminho entre os vértices.\n";
        return;
    }

    cout << "\nMenor caminho de " << Origem << " para " << Destino << ":\n";
    vector<int> caminho;
    for (int v = destino; v != -1; v = antecessor[v])
    {
        caminho.push_back(v);
    }

    for (int i = 0; i < caminho.size() / 2; i++)
    {
        int temp = caminho[i];
        caminho[i] = caminho[caminho.size() - 1 - i];
        caminho[caminho.size() - 1 - i] = temp;
    }

    for (int i = 0; i < caminho.size(); i++)
    {
        if (i > 0)
            cout << " -> ";
        cout << caminho[i];
    }
    cout << "\nDistância total: " << dist[destino] << "\n";
}

void exibirMenu()
{
    cout << "===== Menu Principal =====\n";
    cout << "1. Importar Grafo\n";
    cout << "2. Criar Grafo Vazio\n";
    cout << "3. Exibir Adjacências\n";
    cout << "4. Inserir Aresta\n";
    cout << "5. Remover Aresta\n";
    cout << "6. Consultar Adjacência\n";
    cout << "7. Consultar Primeiro Adjacente\n";
    cout << "8. Consultar Próximo Adjacente\n";
    cout << "9. Consultar Lista Completa de Adjacentes\n";
    cout << "10. Exportar Grafo\n";
    cout << "11. Busca em profundidade\n";
    cout << "12. Busca em largura\n";
    cout << "13. Árvore geradora mínima (Prim)\n";
    cout << "14. Menor caminho (Dijkstra)\n";
    cout << "0. Sair\n\n";
    cout << "Escolha: ";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int opcao;

    while (true)
    {
        system("cls");
        exibirMenu();
        cin >> opcao;

        if (opcao == 0)
            break;

        system("cls");
        switch (opcao)
        {
        case 1:
        {
            adjacencias.clear();
            ;
            char arquivo[256];
            cout << "Digite o nome do arquivo para importar o grafo: ";
            cin >> arquivo;
            importarGrafo(arquivo);
            break;
        }
        case 2:
        {
            adjacencias.clear();
            ;
            int vertices;
            char escolha;

            cout << "O grafo será direcionado? (s/n): ";
            cin >> escolha;

            bool direcionado = (escolha == 's' || escolha == 'S');

            cout << "Digite o número de vértices: ";
            cin >> vertices;

            criarGrafo(direcionado, vertices);
            cout << "\nGrafo vazio" << (direcionado ? " direcionado " : " não direcionado ") << "criado com " << vertices << " vértices.\n";

            break;
        }
        case 3:
            exibirAdjacencias();
            break;

        case 4:
        {
            int v1, v2, peso;
            cout << "Digite os vértices e o peso da aresta (v1 v2 peso): ";
            cin >> v1 >> v2 >> peso;
            inserirAresta(v1, v2, peso);
            cout << "Aresta inserida!\n";
            break;
        }
        case 5:
        {
            int v1, v2;
            cout << "Digite os vértices da aresta para remover (v1 v2): ";
            cin >> v1 >> v2;
            removerAresta(v1, v2);
            cout << "Aresta removida!\n";
            break;
        }
        case 6:
        {
            int v1, v2;
            cout << "Digite os vértices para verificar adjacência (v1 v2): ";
            cin >> v1 >> v2;
            cout << (consultarAdjacencia(v1, v2) ? "São adjacentes" : "Não são adjacentes") << endl;
            break;
        }
        case 7:
        {
            int vertice;
            cout << "Digite o vértice: ";
            cin >> vertice;
            consultarPrimeiroAdjacente(vertice);
            break;
        }
        case 8:
        {
            int vertice, adjAtual;
            cout << "Digite o vértice e o adjacente atual (vértice adjAtual): ";
            cin >> vertice >> adjAtual;
            consultarProximoAdjacente(vertice, adjAtual);
            break;
        }
        case 9:
        {
            int vertice;
            cout << "Digite o vértice: ";
            cin >> vertice;
            consultarListaAdjacentes(vertice);
            break;
        }
        case 10:
        {
            char arquivo[256];
            cout << "Digite o nome do arquivo para exportar o grafo: ";
            cin >> arquivo;
            exportarGrafo(arquivo);
            break;
        }
        case 11:
        {
            cout << "Busca em profundidade:\n\n";
            buscaEmProfundidade();
            break;
        }
        case 12:
        {
            cout << "Busca em largura:\n\n";
            buscaEmLargura();
            break;
        }
        case 13:
        {
            prim();
            break;
        }
        case 14:
        {
            int origem, destino;
            cout << "Digite o nome do vértice de origem: ";
            cin.ignore();
            cin >> origem;
            cout << "Digite o nome do vértice de destino: ";
            cin >> destino;
            dijkstra(origem, destino);
            break;
        }

        default:
            cout << "Opção inválida!\n";
        }
        system("pause");
    }

    cout << "Programa encerrado.\n";
    return 0;
}
