# Lista 2
## Ranking
Isolado em casa sem nada pra fazer, você descobre perambulando pela internet um jogo extremamente viciante chamando "GAME OF THE ANIMAL". 
Nele, os jogadores competem apostando em números representados por animais, e, se sorteados, ganham pontuação.

Por ser muito popular, o jogo conta com uma ampla comunidade de jogadores. Mas, infelizmente, não há nenhuma organização 
entre as pontuações, tornando impossível saber quem é melhor jogador que quem.

Comovido por essa triste realidade e motivado a por em prática seus conhecimentos de programação, você decide implementar um sistema
de rankings que recebe o nome e a pontuação de jogadores e os organiza de uma maneira eficiente.

### Descrição do Problema
No começo do programa, vocẽ receberá um inteiro K e logo após K comandos do tipo ADD, para adicionar jogadores no sistema, ou PROX, 
que pede ao sistema que informe as proximidades de um jogador particular.

As proximidades de um jogador são definidas pelo sucessor e predecessor do jogador, se existirem, em ordem crescente de pontuação.

Exemplo:
| Jogador | Ana | Bob | Carlos | Daniel | Elisa |
| --- | --- | --- | --- | --- | --- |
| Pontuação | 2 | 3 | 6 | 4 | 5 |

Em ordem de pontuação, temos:

**Ana - Bob - Daniel - Elisa - Carlos**

Portanto:
- Proximidades de **Ana**: **Bob** é sucessor.
- Proximidades de **Daniel**: **Bob** é seu predecessor, e **Elisa** é sua sucessora.
- Proximidades de **Carlos**: **Elisa** é sua predecessora.

#### Obs
1. Todos os jogadores possuem nomes únicos e pontuações únicas.
2. Não será requisitada as proximidades de um jogador que não se encontra no sistema.

### Comandos
- **ADD N P** -> Insere um jogador de nome **N** pontuação **P**.
- **PROX P** -> Retorna as *proximidades* do jogador de pontuação **P**.


Link do problema: https://iudex.io/problem/6167437897713f0001036f42/statement

## Goleiro Sistemas

Link do problema: https://iudex.io/problem/6234ff9a3f99be0001bcf002/statement
