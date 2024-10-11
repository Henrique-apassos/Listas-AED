# Lista 3
## HashLog - Parte 1
Um sistema de monitoramento de redes registra as conexões recebidas por um servidor ao longo do tempo.
Para cada conexão, registra-se o timestamp T (inteiro de 32bits sem sinal) do momento em que a conexão 
foi aceita pelo servidor e o endereço IP do cliente C além de outros dados.

Um processo de auditoria que roda em paralelo precisa consultar esporadicamente os
dados de conexões recebidas em momentos específicos, indicados por seus timestamps.
Para tal, é necessário criar um registro das conexões para ser gravado num arquivo de log. 
Para cada conexão, o par (T,C) (timestamp, cliente) é armazenado num array dinâmico ordenado pelos timestamps.

Link do Problema: https://iudex.io/problem/63e163178216f900013be1a5/statement

## HashLog
Não salvei o código

Link do Problema: https://iudex.io/problem/62e444b2f485b80001381e27/statement
