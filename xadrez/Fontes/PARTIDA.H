/***************************************************************************
*  $MCD M�dulo de defini��o: PAR Realizador de partidas de Xadrez
*
*  Arquivo gerado:              PARTIDA.H
*  Letras identificadoras:      PAR
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     0       cev   13/nov/2009 In�cio desenvolvimento
*	  1		  cev	19/nov/2009 Entrega do trabalho
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa as fun��es para a realiza��o de partidas de xadrez
*
*
/***********************************************************************
*
*  $TC Tipo de dados: PAR Condicoes de retorno
*
*
***********************************************************************/

typedef enum{

	PAR_CondRetOK = 0,
		/* Executou corretamente */

}PAR_tpCondRet;

/***** Declara��es importadas pelo m�dulo *****/


/***********************************************************************
*
*  $FC Fun��o: PAR &Iniciar Partida
*
*  $ED Descri��o da fun��o*
*  Prov� ao usu�rio as op��es iniciais para iniciar uma partida ou
*  retomar um jogo salvo.
*
***********************************************************************/

   void PAR_IniciarPartida();

/********** Fim do m�dulo de defini��o: PAR Realizador de partidas de Xadrez **********/