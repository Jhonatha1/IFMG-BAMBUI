/*                ________________________________________
                 | Trabalho de Redes de Computadores      |
                 | IFMG - BAMBUÍ 08/2022                  |
                 | Alunos:                                |
                 | Higor Pereira,   RA:0059791            |
                 | Yanky Jhonatha,  RA:0060194            |
                 | Gabriela Dâmaso. RA:0059796            |
                 |________________________________________|          */





//inclui o arquivo .h
#include "respostaServidor.h"

#define Debug false

using namespace std;

//Carregando os dados:
vector<string> respostaServidor::split(string str, char del){

    string temp = ""; //estabelece um valor "vazio" para a variavel temp
    vector<string> stringsHeader;
    for(int i =0; i < (int)str.size(); i++){
    if(str[i] != del){
            temp += str[i];
        }else{
            stringsHeader.push_back(temp);
            temp = "";
        }
    }
    stringsHeader.push_back(temp);
    return stringsHeader;
}



bool respostaServidor::abriArq(string root, int &len, string &n) {
    fstream file;
    file.open(root, fstream::in |fstream::out | fstream::binary);

    if(file.is_open()){
        file.seekg(0, ios::end);
        //definindo o tamanho do arquivo:
        len = file.tellg();
        //lê o arquivo:
        lerArquivo(file, n, len);
        return true;
    }
    else {
        //Se o arquivo não estiver aberto, um outro arquivo de erro vai abrir:
        file.open("pasta/404.html", fstream::in |fstream::out | fstream::binary);
        if(file.is_open()) {
            file.seekg(0, ios::end);
            len = file.tellg();
            lerArquivo(file, n, len);
        } else {
            n = "404 NOT FOUND\n\r";
            len = n.size();
        }
        return false;
    }
}

void respostaServidor::pegArq(int thread_id, int clientSockfd, sockaddr_in clienteEndereco, string caminho){
//mostrando quantas threads temos abertas:
    if(Debug)
    {
       cout << "ID THREAD: " << thread_id << endl;
    }
    string strRequest = "";
    vector<string> extension;
    vector<string> linesHeader;

//não estabelece a conexão se o cliente não tiver um soquete de conexão
    if (clientSockfd == -1)
    {
        return;
    }

    //Convertendo endereço string para endereço web:
    char ipstr[INET_ADDRSTRLEN] = {'\0'};
    inet_ntop(clienteEndereco.sin_family, &clienteEndereco.sin_addr, ipstr, sizeof(ipstr));
    if(Debug){
        cout << "Iniciando conexão com o cliente " << ipstr << " :" << ntohs(clienteEndereco.sin_port) << endl << endl;
    }
    BufferAux datarec = socli.bufferReceptor(clientSockfd);
    if(datarec.tamanhoBuffer > 0){
        strRequest = string(datarec.dadosC, 0, datarec.tamanhoBuffer);
        if(Debug){
            cout<< strRequest << endl;
        }
        linesHeader = split(strRequest,'\n');
        linesHeader = split(linesHeader[0],' ');
        extension = split(linesHeader[1],'.');

        //Analisando possiveis erros:
        try {
            //Tratamento de requisições get:
            if(linesHeader[0] == "GET"){
                if(Debug){
                    cout<<"é uma requisição get"<<endl;
                    cout<<"Pasta Desejada: "<<linesHeader[1]<<endl;
                    cout<<"extensão: "<<extension[extension.size()-1]<<endl;
                }
                //tratando a requisição:
                getdds(thread_id,clientSockfd,clienteEndereco, caminho+linesHeader[1],extension[extension.size()-1], caminho);
            }
            else {
                throw (linesHeader[0]);
            }

        } catch(string n) {
            int len = 0;
            string aux = "", data="";
            aux = "400 BAD REQUEST\n\r"; //informa o 'erro' 400 bad request ( indica que a solicitação enviada pelo navegador do usuário ao servidor web do site é inválida ou está corrompida)
            len = aux.size();
            //pegando o status:
            data = pegStatus(3, len, "html");
            if(Debug){
                cout << data << endl;
            }
            data += aux;
            socli.asksendSocket(clientSockfd, data);
            socli.xSocket(clientSockfd);
        }
    }
    else {
        if(Debug){
            //informando que o tempo excedeu:
            cout<<"Tempo limite de requisição atingido!"<<endl;
        }
        //fechando socket:
        this->socli.xSocket(clientSockfd);
    }
}


//abrindo arquivo:
int respostaServidor::getdds(int thread_id, int clientSockfd, sockaddr_in clienteEndereco, string root,string extension, string caminho){
    string n, data;
    int len;
    if(Debug){
        cout<< "Root " << root << endl;
    }
    n = data = "";
    if(abriArq(root, len, n)) {
         //Se o arquivo chegar status recebe valor 200:
        data = pegStatus(1, len, extension);
        data += n;
        //mandando resposta:
        socli.asksendSocket(clientSockfd, data);
        pegArq(thread_id, clientSockfd,clienteEndereco, caminho);
    } else {
         //se não encontrar o arquivo aparece erro 404
        data = pegStatus(2, len, "html");
        data+= n;
        socli.asksendSocket(clientSockfd, data);
        socli.xSocket(clientSockfd);
    }
    return 0;
}


//Definição do status da requisição
string respostaServidor::pegStatus(int resp, int len, string extension) {
    string text;
    Tipos tip;
    char buff[256];
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = gmtime (&rawtime);
    strftime(buff, sizeof(buff), "%a, %d %b %Y %H:%M:%S GMT\r\n", timeinfo);

    if(resp == 1) {
        //se resp for igual a 1 significa que encontrou com sucesso oq procurava
        text = "HTTP/1.1 200 OK\r\n"
               "Date: " + string(buff) +
               "Content-Length: " + to_string(len) + "\r\n"
               "Keep-Alive: timeout=5, max=100\r\n"
               "Connection: Keep-Alive\r\n"
               "Content-type: " + tip.getTipo(extension) + "; charset=UTF-8\r\n\r\n";
    }
    else if(resp == 2){
        // se resp for igual a 2 significa que não foi possivel encontrar a pagina
        text = "HTTP/1.1 404 NOT FOUND\r\n"
                "Date: " + string(buff) +
                "Content-Length: " + to_string(len) + "\r\n"
                "Connection: Close\r\n"
                "Content-type: " + tip.getTipo(extension) + "; charset=UTF-8\r\n\r\n";
    } else {
        //se resp não for igual a 1 ou 2 temos um BAD REQUEST (indica que a solicitação enviada pelo navegador do usuário ao servidor web do site é inválida ou está corrompida)
        text = "HTTP/1.1 400 BAD REQUEST\r\n"
                "Date: " + string(buff) +
                "Content-Length: " + to_string(len) + "\r\n"
                "Connection: Close\r\n"
                "Content-type: " + tip.getTipo(extension) + "; charset=UTF-8\r\n\r\n";
    }
    return text;
}


//Lendo arquivo:
void respostaServidor::lerArquivo(fstream &file, string &n, int len) {
    char *aux =  new char[len];
    file.clear();
    file.seekg(0, ios::beg);
    file.read(aux, len);
    for(int i = 0; i < len; i++){
        n += aux[i];
    }
    file.close();
    delete[] aux;
    aux = nullptr;
}
