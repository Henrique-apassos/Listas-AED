# Lista 1

## Pilhados

Pilhonaldo é um empacotador muito suspeito. Durante o dia trabalha em um armazém, empilhando caixas da shopee,
mas sonha em ser professor de matemática no ensino fundamental.

Para isso, ele teve um ideia de atividade enquanto empilhava as caixas. Pilhonaldo percebeu que poderia trabalhar
com seus alunos a subtração e a paridade de números com um jogo.

Cada rodada do jogo consiste em empilhar as caixas uma em cima da outra, na ordem em que vierem.
Mas existe uma complicação: cada vez que uma caixa é empilhada em cima de uma que tem número com paridade igual 
(ambas ímpares ou ambas pares), as duas são substituídas por uma única caixa com número igual à diferença (em absoluto) entre as duas.

Exemplo:
Dada uma pilha que foram empilhadas as caixas com 3, 2 e 1 pacotes, nessa ordem (sendo 1 no topo):


![image](https://github.com/user-attachments/assets/37ad3ec2-ffa0-4c19-9d79-1f7b0c2fa957)


Ao adicionar uma caixa com 7 pacotes em cima de uma de 1, a operação de subtração deve ser realizada:

![image](https://github.com/user-attachments/assets/bfe796b5-463d-4ac2-973f-79e2326bb179)

##### Observações:

- Note que, no caso de ter sido adicionada uma caixa de número 1 em cima de uma de número 7,
  ambas as caixas também seria substituídas por uma caixa contendo **|7-1| = 6** pacotes.
  Assim, a subtração é dada em absoluto, não importando a ordem das caixas.
- A operação de subtração é sucessiva, e continuará acontecendo entre a caixa no topo e a caixa imediatamente
  adjacente ao topo até que a paridade delas seja diferente, como pode ser visto no exemplo.


Link do problema: https://iudex.io/problem/654ccbdfe0c9bd0001fd509f/statement


## Petris

O jogo de Petris é uma variação do jogo Tetris na qual temos N colunas de pedras coloridas, numeradas de 1 a N.
A cada instante, uma nova pedra vem de cima e o jogador pode movimentá-la de forma que ela caia no topo de uma das N colunas, 
ou então inicie uma nova coluna à esquerda ou à direita das demais. Cada vez que uma pedra de cor C é adicionada 
ao topo da coluna sobre outra pedra de cor idêntica, todas a pedras de mesma cor C são removidas do topo dessa coluna.
Quando uma coluna se torna vazia, ela é removida e as colunas à direita são todas deslocadas 
uma posição à esquerda para preencher o espaço deixado. O objetivo é manter o número total de pedras e colunas o menor possível.


Por exemplo, suponha que a configuração atual do jogo seja a seguinte, sendo cada cor representada por um número.

![image](https://github.com/user-attachments/assets/c73b5f5b-10de-4a2b-874f-4863fa9ee22f)

Se uma pedra de cor 2 for adicionada à coluna 2, teremos

![image](https://github.com/user-attachments/assets/6a1e0fd3-7c95-4220-961e-fa4781f497f2)

E então

![image](https://github.com/user-attachments/assets/d96d4962-2790-455f-82d0-43211ef54f63)

Se, em seguida, uma pedra de cor 0 for adicionada à mesma coluna, ficaremos com

![image](https://github.com/user-attachments/assets/5d3d586b-1050-4607-9129-979342e8829d)

e logo

![image](https://github.com/user-attachments/assets/98c8f8be-12c2-481b-8222-c6a98ec09db6)

fazendo com que a coluna na posição 2 desapareça, termiando finalmente com

![image](https://github.com/user-attachments/assets/729061d7-cf5b-4f88-9133-07ae8ff00ff9)


Link do problema: https://iudex.io/problem/64863a8324242400012d55ef/statement

## Cuscuz: Uma rodada

O segundo evento do jogo Cuscuz é uma rodada ROUND, no qual cada jogador em disputa, 
em ordem 0..N-1, retira a primeira carta da sua fila e a joga num monte central (o cuscuz),
organizado como uma pilha. O jogador que colocar a carta com maior valor no cuscuz vence a rodada.
O valor de cada carta é dado pelo seu número A=1 < 2 <...< 9 e, em caso de empate, pelo naipe C < E < O < P.
Neste exercício, consideramos uma versão simplificada em que o cuscuz (pilha) é descartado no início de cada rodada, ou seja, 
cada rodada começa com uma pilha de cartas vazia.

Link do problema: https://iudex.io/problem/639e63568200550001708dd4/statement
