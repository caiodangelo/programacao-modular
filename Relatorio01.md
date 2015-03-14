# Relatório #01 #

## Introdução ##

Nesta página, faremos uma descrição geral da realização do primeiro trabalho de programação modular.


## Descrição do Trabalho ##

### Múltiplas Árvores ###
A primeira tarefa que precisamos cumprir foi estender o módulo árvore que, inicialmente, trabalhava com apenas uma árvore (declarada como uma variável global no módulo ARVORE.C) para suportar múltiplas árvores. Isso foi implementado passando a cabeça da árvore por referência às funções. Sendo assim, o cliente é quem determina quantas árvores deseja criar.
### Marcar Visitado ###
Em seguida, nós precisamos criar uma função MarcarVisitado() que marca um nó com um modo de visita. Nós criamos um enum do tipo tpModoVisita com todos os modos de visita possíveis e acrescentamos um atributo Modo ao struct tgNoArvore.
### Árvores N-Árias ###
Para estender as árvores binárias para árvores n-árias, nós não precisamos alterar as estruturas de dados. Bastou alterar a semântica dos atributos. Os ponteiros que antes apontavam para filho à direita e filho à esquerda, agora apontam para primeiro filho e primeiro irmão. No entanto, a implementação das funções de percorrimento e inserção foram significativamente modificadas. Retiramos as funções de ir ao nó à direita e à esquerda e substituímos por ir ao nó filho e ao nó irmão. Substituímos as duas funções de inserir filho à esquerda e à direita por uma única, inserir filho. Os filhos de um dado nó encontram-se em uma lista de nós, onde o primeiro nó da lista é o nó apontado por pEsq. Para que seja possível o percorrimento em ambas as direções teria que ser acresentado mais um ponteiro à estrutura de dados, formando, assim, uma lista duplamente encadeada de irmãos.
### Exibir Árvore ###
A função de exibição da árvore foi implementada recursivamente, com o uso de uma função auxiliar. Para testá-la, é necessário saber a priori a árvore que será construída utilizando as funções de inserção e percorrimento. Em seguida, a comparação do resultado esperado com o resultado obtido terá que ser feita visualmente, a partir da impressão na linha de comando. Poderíamos ter implementado isso diferentemente, de forma que o usuário fornecesse a string da árvore impressa no script, mas achamos tal abordagem desnecessariamente trabalhosa, pois a impressão teria de ser feita em um arquivo para posterior comparação.
### Módulo Específico de Teste ###
Para testar o novo módulo ARVORE, precisamos fazer diversas alterações no módulo de teste específico. Agora, existe um vetor global de 10 ponteiros para árvores, para permitir testes com múltiplas árvores. Nos scripts, passa a ser necessário informar o índice (de 0 a 9) da árvore no vetor para especificar a árvore com que se deseja trabalhar. Por causa disso, os scripts de teste que acompanham o arcabouço de testes não funcionam com o novo módulo, pois eles consideram que só há uma única árvore (além do fato de utilizar outras operações que foram removidas, como =insdir ou =iresq). Uma observação: se tentar criar uma árvore em uma posição do vetor em que já exista uma árvore, a árvore antiga será substituída.
### Scripts de Teste ###
Nós fizemos 2 scripts de teste: básico e avançado. A descrição completa deles se encontra na página de casos de teste. Os scripts de teste não cobrem as funções encapsuladas no módulo árvore, como orientado em aula.
###  ###
###  ###