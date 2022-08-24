
from PyQt5 import uic,QtWidgets
import sqlite3


def chama_DesignAPP_2TELA():
    DesignAPP_1TELA.label_4.setText("")
    nome_usuario = DesignAPP_1TELA.lineEdit.text()
    senha = DesignAPP_1TELA.lineEdit_2.text()
    if nome_usuario == "admin" and senha == "123" :
        DesignAPP_1TELA.close()
        DesignAPP_2TELA.show()
    else :
        DesignAPP_1TELA.label_4.setText("Dados de login incorretos!")
    

def logout():
    DesignAPP_2TELA.close()
    DesignAPP_1TELA.show()
def voltar():
    tela_cadastro.close()
    DesignAPP_1TELA.show()
def voltarMenu():
    DesignAPP_MeuPerfil.close()
    DesignAPP_2TELA.show()
def abre_tela_cadastro():
    tela_cadastro.show()
def meuPerfil():
    DesignAPP_2TELA.close()
    DesignAPP_MeuPerfil.show()

def editarPerfil():
    """ VARIÁVEIS PARA DAR UPDATE CASO QUEIRA \/\/\/ """
    idadeUpdate = DesignAPP_MeuPerfil.lineEdit_9.text()
    nomeUpdate = DesignAPP_MeuPerfil.lineEdit_3.text()
    dataNascimentoUpdate = DesignAPP_MeuPerfil.lineEdit_4.text()
    pesoUpdate = DesignAPP_MeuPerfil.lineEdit_5.text()
    generoUpdate = DesignAPP_MeuPerfil.lineEdit_6.text()
    alturaUpdate = DesignAPP_MeuPerfil.lineEdit_7.text()
    objetivoUpdate = DesignAPP_MeuPerfil.lineEdit_8.text()

    """ VARIÁVEIS PARA PRIMEIRO CADASTRO \/\/\/ """
    idade = tela_cadastro.lineEdit_5.text()
    nome = tela_cadastro.lineEdit.text()
    dataNascimento = tela_cadastro.lineEdit_6.text
    objetivo = tela_cadastro.lineEdit_10.text()
    genero = tela_cadastro.lineEdit_9.text()
    altura = tela_cadastro.lineEdit_8.text()
    peso = tela_cadastro.lineEdit_7.text()

    """ ATUALIZA A ALTURA """
    if (alturaUpdate != altura):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("UPDATE usuarios SET altura = ('"+alturaUpdate+"')")

            banco.commit() 
            banco.close()
            DesignAPP_MeuPerfil.label.setText("Alterações feitas com sucesso.")
            DesignAPP_MeuPerfil.close()
            DesignAPP_2TELA.show()

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("A senha não é a mesma da cadastrada. Não foi possível confirmar as alterações.")
        

    """ ATUALIZA O GÊNERO """
    if (generoUpdate != genero):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("UPDATE usuarios SET genero = ('"+generoUpdate+"')")

            banco.commit() 
            banco.close()
            DesignAPP_MeuPerfil.label.setText("Alterações feitas com sucesso.")
            DesignAPP_MeuPerfil.close()
            DesignAPP_2TELA.show()

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("A senha não é a mesma da cadastrada. Não foi possível confirmar as alterações.")
        

    """ ATUALIZA O OBJETIVO """
    if (objetivoUpdate != objetivo):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("UPDATE usuarios SET objetivo = ('"+objetivoUpdate+"')")

            banco.commit() 
            banco.close()
            DesignAPP_MeuPerfil.label.setText("Alterações feitas com sucesso.")
            DesignAPP_MeuPerfil.close()
            DesignAPP_2TELA.show()

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("A senha não é a mesma da cadastrada. Não foi possível confirmar as alterações.")
        

    """ ATUALIZA O PESO """
    if (pesoUpdate != peso):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("UPDATE usuarios SET peso = ('"+pesoUpdate+"')")

            banco.commit() 
            banco.close()
            DesignAPP_MeuPerfil.label.setText("Alterações feitas com sucesso.")
            DesignAPP_MeuPerfil.close()
            DesignAPP_2TELA.show()

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("A senha não é a mesma da cadastrada. Não foi possível confirmar as alterações.")
        

    """ ATUALIZA A DATA DE NASCIMENTO """

    if(dataNascimentoUpdate != dataNascimento):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("UPDATE usuarios SET dataNascimento = ('"+dataNascimentoUpdate+"')")

            banco.commit() 
            banco.close()
            DesignAPP_MeuPerfil.label.setText("Alterações feitas com sucesso.")
            DesignAPP_MeuPerfil.close()
            DesignAPP_2TELA.show()

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("A senha não é a mesma da cadastrada. Não foi possível confirmar as alterações.")

    """ ATUALIZA A IDADE """
    if (idadeUpdate != idade):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("UPDATE usuarios SET idade = ('"+idadeUpdate+"')")

            banco.commit() 
            banco.close()
            DesignAPP_MeuPerfil.label.setText("Alterações feitas com sucesso.")
            DesignAPP_MeuPerfil.close()
            DesignAPP_2TELA.show()

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("A senha não é a mesma da cadastrada. Não foi possível confirmar as alterações.")
        
    """ ATUALIZA O NOME """
    if (nomeUpdate != nome):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("UPDATE usuarios SET nome = ('"+nomeUpdate+"')")

            banco.commit() 
            banco.close()
            DesignAPP_MeuPerfil.label.setText("Alterações feitas com sucesso.")
            DesignAPP_MeuPerfil.close()
            DesignAPP_2TELA.show()

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("A senha não é a mesma da cadastrada. Não foi possível confirmar as alterações.")

        
def cadastrar():
    nome = tela_cadastro.lineEdit.text()
    login = tela_cadastro.lineEdit_2.text()
    senha = tela_cadastro.lineEdit_3.text()
    c_senha = tela_cadastro.lineEdit_4.text()
    idade = tela_cadastro.lineEdit_5.text()
    dataNascimento = tela_cadastro.lineEdit_6.text()
    idade = tela_cadastro.lineEdit_5.text()
    objetivo = tela_cadastro.lineEdit_10.text()
    genero = tela_cadastro.lineEdit_9.text()
    altura = tela_cadastro.lineEdit_8.text()
    peso = tela_cadastro.lineEdit_7.text()
    if (senha == c_senha):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("CREATE TABLE IF NOT EXISTS usuarios (nome text,login text,senha text, idade text, dataNascimento text, objetivo text, peso text, altura text, genero text)")
            cursor.execute("INSERT INTO usuarios VALUES ('"+nome+"','"+login+"','"+senha+"','"+idade+"','"+dataNascimento+"','"+objetivo+"','"+peso+"', '"+altura+"','"+genero+"')")

            banco.commit() 
            banco.close()
            tela_cadastro.label.setText("Usuário cadastrado com sucesso.")

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("As senhas digitadas estão diferentes.")
    

    

""" /*DECLARAÇÕES E SETS */ """
app=QtWidgets.QApplication([])
DesignAPP_1TELA=uic.loadUi("DesignAPP_1TELA.ui")
DesignAPP_2TELA = uic.loadUi("DesignAPP_2TELA.ui")
tela_cadastro = uic.loadUi("tela_cadastro.ui")
DesignAPP_MeuPerfil = uic.loadUi("DesignAPP_MeuPerfil.ui")


""" //TODAS FUNÇÕES E BOTÕES \/\/\/ """

DesignAPP_1TELA.pushButton.clicked.connect(chama_DesignAPP_2TELA)
DesignAPP_2TELA.pushButton.clicked.connect(logout)
DesignAPP_1TELA.lineEdit_2.setEchoMode(QtWidgets.QLineEdit.Password)
DesignAPP_1TELA.pushButton_2.clicked.connect(abre_tela_cadastro)
tela_cadastro.pushButton.clicked.connect(cadastrar) 
tela_cadastro.pushButton_2.clicked.connect(voltar)
DesignAPP_2TELA.pushButton_3.clicked.connect(meuPerfil)
DesignAPP_MeuPerfil.pushButton.clicked.connect(editarPerfil)
DesignAPP_MeuPerfil.pushButton_4.clicked.connect(voltarMenu)
DesignAPP_1TELA.show()
app.exec()