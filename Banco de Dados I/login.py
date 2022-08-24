
from PyQt5 import uic,QtWidgets
import sqlite3


def chama_DesignAPP_2TELA():
    DesignAPP_1TELA.label_4.setText("")
    nome_usuario = DesignAPP_1TELA.lineEdit.text()
    senha = DesignAPP_1TELA.lineEdit_2.text()
    if nome_usuario == "joao123" and senha == "123456" :
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
def abre_tela_cadastro():
    tela_cadastro.show()


def cadastrar():
    nome = tela_cadastro.lineEdit.text()
    login = tela_cadastro.lineEdit_2.text()
    senha = tela_cadastro.lineEdit_3.text()
    c_senha = tela_cadastro.lineEdit_4.text()

    if (senha == c_senha):
        try:
            banco = sqlite3.connect('BancoAcademia.db') 
            cursor = banco.cursor()
            cursor.execute("CREATE TABLE IF NOT EXISTS usuarios (nome text,login text,senha text)")
            cursor.execute("INSERT INTO usuarios VALUES ('"+nome+"','"+login+"','"+senha+"')")

            banco.commit() 
            banco.close()
            tela_cadastro.label.setText("Usuário cadastrado com sucesso.")

        except sqlite3.Error as erro:
            print("Erro ao inserir os dados: ",erro)
    else:
        tela_cadastro.label.setText("As senhas digitadas estão diferentes.")
    

    


app=QtWidgets.QApplication([])
DesignAPP_1TELA=uic.loadUi("DesignAPP_1TELA.ui")
DesignAPP_2TELA = uic.loadUi("DesignAPP_2TELA.ui")
tela_cadastro = uic.loadUi("tela_cadastro.ui")
DesignAPP_1TELA.pushButton.clicked.connect(chama_DesignAPP_2TELA)
DesignAPP_2TELA.pushButton.clicked.connect(logout)
DesignAPP_1TELA.lineEdit_2.setEchoMode(QtWidgets.QLineEdit.Password)
DesignAPP_1TELA.pushButton_2.clicked.connect(abre_tela_cadastro)
tela_cadastro.pushButton.clicked.connect(cadastrar) 
tela_cadastro.pushButton_2.clicked.connect(voltar)


DesignAPP_1TELA.show()
app.exec()