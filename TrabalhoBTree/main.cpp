/******************************************
 * TRABALHO ÁRVORE B                      *
 *   Filipe Lehmann Pereira, RA: 0034075  *
 *   Yanky Jhonatha, RA: 0060194          *
 *   Implementado em 03/2022              *
 ******************************************/

#include <iostream>
#include <clocale>
#include "serialfrac.h"
#include "tree.h"

using namespace std;

int main()
{

    setlocale(LC_ALL, "Portuguese");
    btree<serialfrac, 3> tree("file.dat","DBT",3);
    string vetorInsere[21] = {"1/3", "1/8", "1/2", "3.2/5", "3/5", "7/8", "3/8", "-1/5", "2/3", "5/20", "1.1/2", "3/7", "2.3/4", "7/11", "5/6", "1/12", "5/3", "3/11", "4/7", "2/9", "7/20"};
    string vetorRemove[10] = {"1.1/2", "-1/5", "3/8", "1/3", "7/11", "7/20", "2/9", "4/7", "1/12", "5/20"};
    serialfrac frac;
    int op;

    if(tree.isOpen())
    {
        do
        {
            cout << "\n--------Projeto Árvore B----------\n" << endl;
            cout << " 1 - Inserir uma fração na árvore." << endl;
            cout << " 2 - Remover uma fração da árvore." << endl;
            cout << " 3 - Imprimir a árvore completa." << endl;
            cout << " 4 - Buscar uma fração na árvore." << endl;
            cout << " 5 - Executar conjunto de testes." << endl;
            cout << " 6 - Sair." << endl;
            cout << "\n----------------------------------"<< endl;
            cout << "\nEscolha uma das opções: ";
            cin >> op;

            switch (op)
            {
            case 1:
            {
                cout << "Opção de inserção escolhida. \n";
                cout << "\n";
                cin >> frac;
                try
                {
                    tree.insertKey(frac);
                    cout << "Fração simplificada no formato " << frac << " inserida na árvore com sucesso." << endl;
                }
                catch(...)
                {
                    cout << "Erro de inserção." << endl;
                }
                break;
            }

            case 2:
            {
                cout << "Opção de remoção escolhida.\n";
                cout << "\n";
                cin >> frac;
                try
                {
                    tree.remove(frac);
                    cout << "Fração " << frac << " removida da árvore com sucesso." << endl;
                }
                catch(...)
                {
                    cout << "Erro de remoção." << endl;
                }
                break;
            }


            case 3:
            {
                tree.print();
                break;
            }

            case 4:
            {
                cout << "Opção de busca escolhida. \n";
                cout << "\n";
                cin >> frac;
                if(tree.search(frac))
                {
                    cout << "Valor encontrado na árvore." << endl;
                }
                else
                {
                    cout << "Valor não encontrado." << endl;
                }
                break;
            }

            case 5:
            {
                cout << "\n--------Rotina de testes---------\n" << endl;
                cout << "             Inserções               " << endl;
                for(int i = 0; i< 21; i++)
                {
                    frac.setFrac(vetorInsere[i]);
                    if(tree.insertKey(frac))
                    {
                        cout<<"Fração inserida: "<< vetorInsere[i] <<endl;
                    }
                }
                cout<<"\nInserções executadas com sucesso.\nEstado da árvore:\n" <<endl;
                tree.print();
                cout << "\n             Remoções                " << endl;
                for(int i = 0; i< 10; i++)
                {
                    frac.setFrac(vetorRemove[i]);
                    if(tree.remove(frac))
                    {
                        cout<<"Fração removida: "<< vetorRemove[i] <<endl;
                    }
                }
                cout<<"\nRemoções executadas com sucesso.\nEstado da árvore:" <<endl;
                tree.print();
                break;
            }

            case 6:
            {
                cout << "Finalizando programa." << endl;
                break;
            }

            default:
            {
                cout << "Opção inválida. \n" << "Digite novamente.\n";
                break;
            }
            }
        }
        while (op != 6);
        tree.close();
    }
    else
    {
        cout << "DISCO NÃO ABERTO";
    }
    return 0;
}
