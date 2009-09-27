/***************************************************************************
*  $MCD Módulo de definição: Módulo reconhecedor de xeque mate
*
*  Arquivo gerado:              RECONHECEDOR.H
*  Letras identificadoras:      REC
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   cev   19/09/2009 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa as funções para reconhecer se, dado um
*	  tabuleiro de xadrez, um rei está em xeque mate
*
*
/***********************************************************************
*
*  $TC Tipo de dados: REC Condicoes de retorno
*
*
***********************************************************************/

typedef enum{

	tpCondRetOK = 0;
		/* Executou corretamente */

	tpCondRetArquivoNaoExiste = 1;
		/* O arquivo passado não existe no diretório especificado */

	tpCondRetArquivoInvalido = 2;
		/* O arquivo passado não respeita a sintaxe correta */

	tpCondRetFaltouMemoria = 3;
		/* Faltou memória para ser alocada */

	tpCondRetNaoCriouGrafo = 4;
		/* O grafo para armazenar as peças não pôde ser criado */

	tpCondRetNaoCriouVertice = 5;
		/* Um vértice do grafo não pôde ser criado */

	tpCondRetNaoInseriuPeca = 6;
		/* Não conseguiu inserir a peça */

}REC_tpCondRet;

/***********************************************************************
*
*  $FC Função: REC Reconhece Xeque
*
*  $ED Descrição da função
*     Dado um tabuleiro e uma cor, a função determina se o rei da
*	  cor passada está em xeque mate
*
*  $EP Parâmetros
*     $P Tabuleiro - tabuleiro de xadrez
*	  $P Cor - cor do rei
*
*  $FV Valor retornado
*     Ponteiro para uma casa para onde o rei ainda pode ir
*     NULL se o rei estiver em xeque mate
*
***********************************************************************/

   tpPeca * REC_ReconheceXeque ( tpTabuleiro Tabuleiro, tpCorPeca Cor );


/***********************************************************************
*
*  $FC Função: REC Determinar Regras
*
*  $ED Descrição da função
*     Determina as regras de movimentação das peças
*
*  $EP Parâmetros
*     $P ArquivoRegras - string com o nome do arquivo de regras
*
*  $FV Valor retornado
*     tpCondRetOK
*	  
*	  
*
***********************************************************************/

   REC_tpCondRet REC_DeterminaRegras ( char * ArquivoRegras )


/********** Fim do módulo de definição: Módulo grafo **********/