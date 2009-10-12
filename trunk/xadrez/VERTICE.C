/***************************************************************************
*  $MCI Módulo de implementação: Módulo vértice de um grafo
*
*  Arquivo gerado:              VERTICE.C
*  Letras identificadoras:      VER
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
*       1.00   cev   25/09/2009 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#include "VERTICE.H"

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor do vértice
*
*
*  $ED Descrição do tipo
*     O vértice é uma estrutura que armazena um valor de qualquer tipo.
*     ...
*
***********************************************************************/

   typedef struct tgVertice {

		 void * Valor;
			   /* Informação do Vértice */

   } tpVertice ;

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

  

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice ( tpVertice ** ppVertice, void * Valor ){

	  if ( *ppVertice != NULL )
      {
         VER_DestruirVertice( &ppVertice ) ;
      } /* if */

      *ppVertice = ( tpVertice * ) malloc( sizeof( tpVertice )) ;
      if ( *ppVertice == NULL )
      {
         return VER_CondRetFaltouMemoria ;
      } /* if */

      (*ppVertice)->Valor = Valor;

	  return VER_CondRetOK ;

} /* Fim função: VER Criar vértice */

/***************************************************************************
*
*  Função: VER Obter valor
*  ****/

   VER_tpCondRet VER_ObterValor ( tpVertice * pVertice, void * Valor ) {
   
		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if ( ( pVertice->Valor ) == NULL )
		{
			return VER_CondRetVerticeVazio ;
		} else {
			
			Valor = pVertice->Valor	
		} /* if */

   	  return VER_CondRetOK ;

} /* Fim função: VER Obter Valor */

/***************************************************************************
*
*  Função: VER Alterar valor
*  ****/

   VER_tpCondRet VER_AlterarValor ( tpVertice * pVertice, void * ValorNovo ){

		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		pVertice->Valor = ValorNovo ;

   	  return VER_CondRetOK ;

} /* Fim função: VER Alterar Valor */

/***************************************************************************
*
*  Função: VER Destruir vértice
*  ****/

	VER_tpCondRet VER_DestruirVertice ( tpVertice * pVertice ){
		
		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		free( pVertice );
		pVertice = NULL;


} /* Fim função: VER Destruir Vertice */

/********** Fim do módulo de implementação: Módulo grafo **********/

