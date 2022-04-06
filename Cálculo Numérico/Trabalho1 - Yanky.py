#O trabalho consiste na implementação de um sistema de resolução de equações não lineares. Os seguintes pontos devem ser considerados:
#- O programa deve, inicialmente, receber uma equação e um intervalo para plotar o gráfico;
#- Em seguida, o usuário poderá ajustar o intervalo até que decida calcular a raiz da equação;
#- Quando o usuário confirmar o intervalo, o sistema deve calcular a raiz utilizando os métodos estudados;
#- Pelo menos três métodos devem ser implementados;
#- Deverá ser entregue um único arquivo contendo códigos e comentários;
#- O trabalho é individual, cópias da Internet ou colegas serão desconsideradas.

#AUTOR: Yanky Jhonatha Monteiro Fonte Boa
#IFMG - Campus Bambuí - 2022
import numpy as np      #bibliotecas
import matplotlib.pyplot as pyplot
import matplotlib.ticker

def f(x):               #definindo a função.
    return np.log(x)

def plot(a,b,tol,n):    #definindo os cálculos para achar a raiz.
  xant = float('nan')
  for i in range(n):
    x = a+b/2
    fx = f(x)
    sinal = f(a) * fx
    error=abs((x-xant)/max(x,1))
    xant = x
    print('It. {i:3d}:'.format(i=i), 'a={a:+.6f},'.format(a=a),
          'b={b:+6f},'.format(b=b), 'error={e:+.6f},'.format(e=error),
          'x={x:+6f},'.format(x=x), 'f(x)={fx:+.6f},'.format(fx=fx),
          'sinal={s:+.6f}'.format(s=sinal))
    if(fx == 0) or (error < tol):
      print('Raiz aproximada encontrada: {r:+.6f}'.format(r=x))
      break
    if sinal > 0:
      a = x
    else:
      b = x
    x= np.linspace(a, b) 
    pyplot.plot(x, f(x)) #definindo o gráfico da função com raiz.
    pyplot.grid()
    pyplot.show()
        
a = float(input('Informe o início do intervalo: ')) #interação com usuário
b = float(input('Informe o fim do intervalo: '))
plot(a,b,10**-5,20) #função final que plota o gráfico.