        ##############################################################
        ##                   Trabalho 1 - Busca                     ##
        ##           Inteligência Artificial - Período 6            ##
        ##          Aluno Yanky Jhonatha Monteiro Fonte Boa         ##
        ## Algoritmo que resolve labirinto usando Busca em Largura. ##
        ##############################################################


import sys
import copy                                 
indexVisitados = []                                                       
agent = "Y"                                     
inicialIndex = [(10,0)]                           
linhas , colunas = (12,12)                          
labirinto = []                                      

for i in range(linhas):                          
    coluna = []
    for j in range(colunas):                       
        coluna.append("#")                        
    labirinto.append(coluna)

# Os "*" são caminhos e os "#" são paredes. O "Y" representa no caso o "agente", que se move do início do labirinto até a saída.
labirinto[1][1] = "*"
labirinto[2][1] = "*"
labirinto[1][2] = "*"
labirinto[1][3] = "*"
labirinto[2][3] = "*"
labirinto[3][3] = "*"
labirinto[4][3] = "*"
labirinto[4][1] = "*"
labirinto[4][2] = "*"
labirinto[4][4] = "*"
labirinto[5][4] = "*"
labirinto[6][4] = "*"
labirinto[7][4] = "*"
labirinto[8][4] = "*"
labirinto[8][1] = "*"
labirinto[8][2] = "*"
labirinto[8][3] = "*"
labirinto[8][5] = "*"
labirinto[8][6] = "*"
labirinto[8][7] = "*"
labirinto[8][8] = "*"
labirinto[6][1] = "*"
labirinto[6][2] = "*"
labirinto[7][2] = "*"
labirinto[10][0] = "*"
labirinto[10][1] = "*"
labirinto[10][2] = "*"
labirinto[10][3] = "*"
labirinto[10][4] = "*"
labirinto[10][5] = "*"
labirinto[10][6] = "*"
labirinto[1][10] = "*"
labirinto[2][10] = "*"
labirinto[3][10] = "*"
labirinto[4][10] = "*"
labirinto[5][10] = "*"
labirinto[6][10] = "*"
labirinto[7][10] = "*"
labirinto[8][10] = "*"
labirinto[9][10] = "*"
labirinto[10][10] = "*"
labirinto[10][8] = "*"
labirinto[10][9] = "*"
labirinto[1][5] = "*"
labirinto[1][6] = "*"
labirinto[1][7] = "*"
labirinto[1][8] = "*"
labirinto[1][9] = "*"
labirinto[2][5] = "*"
labirinto[3][5] = "*"
labirinto[3][6] = "*"
labirinto[3][7] = "*"
labirinto[3][8] = "*"
labirinto[4][8] = "*"
labirinto[5][8] = "*"
labirinto[6][8] = "*"
labirinto[7][8] = "*"
labirinto[5][6] = "*"
labirinto[6][6] = "*"
labirinto[7][6] = "*"
labirinto[9][6] = "*"

# Entrada inicial do labirinto.
labirinto[4][11] = "Y"

agenteIndex = [(index, colunas.index(agent)) for index, colunas in enumerate(labirinto) if agent in colunas]  
x = agenteIndex[0][0]                                                                           
y = agenteIndex[0][1]                                                                           

def printMatrix(mat) :                                                                          
    for i in range(linhas):
        for j in range(colunas):
            print(mat[i][j],end = ' ')
        print()

def matrixIndex(state):                                                                       
    temp = state.copy()
    idx = [(index, colunas.index(agent)) for index, colunas in enumerate(temp) if agent in colunas]      
    x = idx[0][0]                                                                               
    y = idx[0][1]                                                                               
    return idx,x,y

class Node:
    def __init__(self, state, parent, operator, moves):             
        self.state = state
        self.parent = parent
        self.operator = operator
        self.moves = moves

def criarNo(state, parent, operator, cost):                        
    return Node(state, parent, operator, cost)

def expandirNo(node,n):                                                  
    nosExpandidos = []
    stateTemp = irCima(node.state,n)   

    if (stateTemp is not None):
        noTemp1 = criarNo(stateTemp,node, "cima", node.moves+1)    
        nosExpandidos.append(noTemp1)                              
    stateTemp2 = irEsquerda(node.state,n)  
    if (stateTemp2 is not None):
        noTemp2 = criarNo(stateTemp2,node, "esquerda", node.moves+1) 
        nosExpandidos.append(noTemp2)                               
    
    stateTemp3 = irDireita(node.state,n) 
    if (stateTemp3 is not None):
        noTemp3 = criarNo(stateTemp3,node, "direita", node.moves+1) 
        nosExpandidos.append(noTemp3)                               
    
    temp_state = irBaixo(node.state,n)                               
    if (temp_state is not None):
        noTemp = criarNo(temp_state,node, "baixo", node.moves+1)    
        nosExpandidos.append(noTemp)                                       

    return nosExpandidos

def irEsquerda(state,n):
    swap = copy.deepcopy(state)
    idx,x,y = matrixIndex(swap)                                                                  
    if (swap[x][y-1] == "#" or y <= 0):                                                             
        return None
    else:
        swap[x][y-1] , swap[x][y] = swap[x][y] , swap[x][y-1]                                       
        return swap

def irDireita(state,n):
    swap = copy.deepcopy(state)
    idx,x,y = matrixIndex(swap)                                                                   
    
    if (y >= n-1 or swap[x][y+1] == "#"):                                                           
        return None
    else:
        swap[x][y+1] , swap[x][y] = swap[x][y] , swap[x][y+1]                                       
        return swap

def irCima(state,n):
    swap = copy.deepcopy(state)
    idx,x,y = matrixIndex(swap)                                                                  
    
    if (swap[x-1][y] == "#" or x <= 0 ):                                                           
        return None
    else:
        
        swap[x-1][y] , swap[x][y] = swap[x][y] , swap[x-1][y]                                      
        return swap

def irBaixo(state,n):
    swap = copy.deepcopy(state)
    idx,x,y = matrixIndex(swap)                                                                   
    
    if (swap[x+1][y] == "#" or x >= n-1):                                                           
        return None
    else:
        swap[x+1][y] , swap[x][y] = swap[x][y] , swap[x+1][y]                                       
        return swap

def algoritmoBFS(start,n): 
    tempCount =0
    tempIndex,x1,y1 = matrixIndex(start) 
    
    if (tempIndex == inicialIndex):
        return [None]
    else:
        praExpandir = []                                                                        
        noAtual = criarNo(start,None,None,0)                                               
        praExpandir.append(noAtual)                                                           
        while (1):
            tempExpandido = []                                                                      
            size = len(praExpandir)                                                             
            for j in range(size) :
                index,x1,y1 = matrixIndex (praExpandir[j].state)  
                if (index in indexVisitados) :                                                     
                                        continue  
                noArray = expandirNo(praExpandir[j],n) 
                for k in range(len(noArray)):
                    idx,x,y = matrixIndex(noArray[k].state)  
                    tempCount+=1
                    if (idx == inicialIndex):
                        print()
                        print("***Resolvedor de labirinto com o Algoritmo BFS (Busca em Largura)***")
                        print()
                        print("Labirinto resolvido.")
                        print("Resultado: ")
                        print()
                        printMatrix(noArray[k].state)
                        print()
                        print("Número de explorações: ", tempCount)
                        return noArray[k]
                    else :
                        tempExpandido.append(noArray[k])                                        
                        indexVisitados.append(index)                                               
            praExpandir.clear()                                                                  
            praExpandir = tempExpandido.copy()                                                   
            tempExpandido.clear()                                                                      
    return None 

def main():
    n=12
    stateInicial = labirinto
    result = algoritmoBFS(stateInicial,n)
    if result == None:
        print("Não obtive solução.")
    elif result == [None]:
        print  ("O nó inicial começou.")
    else:
        print ("Total de nós que precisaram ser visitados: ", result.moves)

# Caso queira ver todo o procedimento do labirinto sendo feito é só tirar os comentários abaixo.
#        path = []
#        path.append(result.state)
#        current = result      
#        flag = True     
#        while (flag):
#            parent = current.parent
#            prevState = parent.state
#            path.append(prevState)
#            current = parent         
#            if (prevState == stateInicial):
#                flag = False              
#        path.reverse()      
#        for state in path:
#            printMatrix(state)
#            print()
    print()
    print()
    print("***FIM***")
    print()

if __name__ == "__main__":
    main()

