#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#TRABALHO 2 - CÁLCULO NUMÉRICO
#AUTOR: YANKY JHONATHA MONTEIRO FONTE BOA
#IFMG - CAMPUS BAMBUÍ
#PARA TESTAR O ALGORITMO COLOQUE SENDO 2 VARIÁVEIS E COMO VALOR 1,2,3 NA LINHA 1, E NA LINHA 2: 2,3,5
import numpy as np


def le_matriz():
 M = []
 n = int(input('Informe o número de variáveis do sistema: '))
 print('Informe a matriz estendida do sistema (linha por linha:')  
 for i in range(n):
     lin = input('Linha {i}: '.format(i=i))
     lin_num = lin.split(',')
     lin_num = [float(i) for i in lin_num]
     M.append(lin_num)
 M = np.array(M, dtype='double')
 return M

#Procura linha pivô em M na coluna col a a partir da linha lin
def linha_pivo(mat, lin, col):
# Maior valor como o primeiro elemento
    maior = abs(M[lin, col])
# Linha pivo como a linha do primeiro elemento
    lin_pivo = lin
# n é o número de linhas de M
    n = np.alen(M)
# Percorremos a coluna col a partir de lin
    for i in range(lin, n):
# Se o elemento da linha atual for maior
        if abs(M[i,col]) > maior:
# Atualizamos o pivô
            maior = abs(M[i,col])
            lin_pivo = i
    return lin_pivo

 # Troca lin1 e lin2 de M
def troca_linha(M, lin1, lin2):
 # Testa se a linhas são diferentes
     if lin1 != lin2:
         print('Troca de linhas: ', lin1, '<->', lin2)
         aux = np.copy(M[lin1, :])
         M[lin1, :] = np.copy(M[lin2, :])
         M[lin2, :] = aux
         print(M)
 # Resolve matriz M no formato de diagonal superior
 
def resolve_diag_sup(M):
 # n é o número de linhas de M
     n = np.alen(M)
# b é o vertor de termos constantes
     b = np.copy(M[:,n])
# Cria vetor x para guardar a solução
     x = np.arange(n, dtype='double')
# Última linha já está isolada
 # x_n = b_n / M_n,n
     if M[n-1, n-1] !=0:
      x[n-1] = b[n-1] / M[n-1, n-1]
     else:
      print ('O sistema não possui solução.')
      return 0
 # Percorre as linhas (em ordem decrescente, ignorando a última)
     for i in range(n-2, -1, -1):
         soma = 0
 # Soma as icógnitas já resolvidas (depois da diagonal)
         for j in range(i+1, n):
             soma += x[j] * M[i, j]
 # x_i = (b_i - (soma das icógnitas)) / M_i,i
         x[i] = (b[i] - soma) / M[i, i]
     return x
 
# Eliminação gaussiana com pivotamento
def gauss_pivo(M):
 # n é o número de linhas de M
     n = np.alen(M)
     for c in range(n-1):
         print('\n\nColuna', c)
         l = linha_pivo(M, c, c)
         troca_linha(M, l, c)
         pivo = M[c,c]
         for l in range(c+1, n):
             print('\nL{l} <- L{l} - L{c} * '.format(l=l, c=c) +
                   '{b} / {p}'.format(b=M[l,c], p=pivo))
             M[l, :] = M[l, :] - M[c, :] * M[l, c] / pivo
             print(M)
     return resolve_diag_sup(M)
M = le_matriz()
print('Matriz original')
print(M)

x = gauss_pivo(M)

print('\nSolução:')
n = np.alen(x)
for i in range(n):
    print('x{i} = {val}'.format(i=i, val=x[i]))
    
#Calculo de raio espectral:
def raio_espectral(T):
 av, _ = np.linalg.eig(T) 
 raio_espectral = max(abs(av))

#Metodo de jacobi
def jacobi(A, b, x0, tol, iteracoes):
 resp=input('Você deseja continuar com a execução para mostrar a solução? S/N: ')
 if resp != 'S':
     print('Encerrando sistema.')
 else:     
  n = np.alen(A) # n é o número de linhas
  x = np.zeros(n, dtype='double') # Solução atual
  xant = x0 # Solução da iteração anterior
 for k in range(iteracoes): # Iterações do método
   for i in range(n): # Iterações para cada incógnita
    x[i] = b[i] # Termo constante
    for j in range(i): # Incógnitas anteriores
     x[i] -= A[i,j]*xant[j]
    for j in range(i+1, n): # Incógnitas posteriores
     x[i] -= A[i,j]*xant[j]
     x[i] /= A[i,i] # Divisão pelo coeficiente da incógnita atual
   erro = np.linalg.norm(x-xant, np.inf) # Cálculo do erro
   print("Iteração {k:3d}: ".format(k=k+1) +
         "x={x}, ".format(x=np.round(x,8)) +
         "Erro={e:+5.8f}".format(e=erro))
   if (erro < tol): # Testa se erro é menor que a tolerância
       return x
 # Copia solução atual para ser a anterior na próxima iteração
xant = np.copy(x)


# Entrada: M, b
M = np.array([
 [ 1, 2, 3],
 [ 2, 3, 5]], dtype='double')


b = np.array([1, 1], dtype='double')
#Aproximação inicial
x0 = np.array([1, 1], dtype='double')
# Executa o método de Jacobi
x = jacobi(M, b, x0, 0.0001, 20)
print('\nSolução aproximada encontrada')
print('x =', x)