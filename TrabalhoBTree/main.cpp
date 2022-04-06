/******************************************
 * TRABALHO �RVORE B                      *
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
            cout << "\n--------Projeto �rvore B----------\n" << endl;
            cout << " 1 - Inserir uma fra��o na �rvore." << endl;
            cout << " 2 - Remover uma fra��o da �rvore." << endl;
            cout << " 3 - Imprimir a �rvore completa." << endl;
            cout << " 4 - Buscar uma fra��o na �rvore." << endl;
            cout << " 5 - Executar conjunto de testes." << endl;
            cout << " 6 - Sair." << endl;
            cout << "\n----------------------------------"<< endl;
            cout << "\nEscolha uma das op��es: ";
            cin >> op;

            switch (op)
            {
            case 1:
            {
                cout << "Op��o de inser��o escolhida. \n";
                cout << "\n";
                cin >> frac;
                try
                {
                    tree.insertKey(frac);
                    cout << "Fra��o simplificada no formato " << frac << " inserida na �rvore com sucesso." << endl;
                }
                catch(...)
                {
                    cout << "Erro de inser��o." << endl;
                }
                break;
            }

            case 2:
            {
                cout << "Op��o de remo��o escolhida.\n";
                cout << "\n";
                cin >> frac;
                try
                {
                    tree.remove(frac);
                    cout << "Fra��o " << frac << " removida da �rvore com sucesso." << endl;
                }
                catch(...)
                {
                    cout << "Erro de remo��o." << endl;
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
                cout << "Op��o de busca escolhida. \n";
                cout << "\n";
                cin >> frac;
                if(tree.search(frac))
                {
                    cout << "Valor encontrado na �rvore." << endl;
                }
                else
                {
                    cout << "Valor n�o encontrado." << endl;
                }
                break;
            }

            case 5:
            {
                cout << "\n--------Rotina de testes---------\n" << endl;
                cout << "             Inser��es               " << endl;
                for(int i = 0; i< 21; i++)
                {
                    frac.setFrac(vetorInsere[i]);
                    if(tree.insertKey(frac))
                    {
                        cout<<"Fra��o inserida: "<< vetorInsere[i] <<endl;
                    }
                }
                cout<<"\nInser��es executadas com sucesso.\nEstado da �rvore:\n" <<endl;
                tree.print();
                cout << "\n             Remo��es                " << endl;
                for(int i = 0; i< 10; i++)
                {
                    frac.setFrac(vetorRemove[i]);
                    if(tree.remove(frac))
                    {
                        cout<<"Fra��o removida: "<< vetorRemove[i] <<endl;
                    }
                }
                cout<<"\nRemo��es executadas com sucesso.\nEstado da �rvore:" <<endl;
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
                cout << "Op��o inv�lida. \n" << "Digite novamente.\n";
                break;
            }
            }
        }
        while (op != 6);
        tree.close();
    }
    else
    {
        cout << "DISCO N�O ABERTO";
    }
    return 0;
}
