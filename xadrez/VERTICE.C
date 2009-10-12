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
#include "LISTA.H"

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
		 
         LIS_tppLista * Sucessores ;
               /* Ponteiro para a lista de vértices que são atingidos*/

         LIS_tppLista * Antecessores ;
               /* Ponteiro para a lista de vértices que atingem*/

		 int idVertice;
			  /* Identificador do vértice */

   } tpVertice ;

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

   VER_tpCondRet VER_AdicionarAntecessor ( tpVertice * pVertice );

   VER_tpCondRet VER_RemoverAntecessor ( tpVertice * pVertice );
  

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice ( tpVertice ** ppVertice, void * Valor, int idVertice ){

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
	  (*ppVertice)->Sucessores = NULL;
	  (*ppVertice)->Antecessores = NULL;
	  (*ppVertice)->idVertice = idVertice;


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

/***************************************************************************
*
*  Função: VER Adicionar Sucessor
*  ****/

	VER_tpCondRet VER_AdicionarSucessor ( tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;
		VER_tpCondRet CondRetVertice;

		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if((pVerticeOrigem->Sucessores)==NULL)
		{
			pVerticeOrigem->Sucessores = LIS_CriarLista( VER_tpCondRet ( * VER_DestruirVertice ) 
														(tpVertice * pVertice ) );

			if((pVerticeOrigem->Sucessores)==NULL)
			{
				return  VER_CondRetFaltouMemoria;				

			}/* if */

		}/* if */

		CondRetLista = LIS_ProcurarValor( pVerticeOrigem->Sucessores ,
                                    pVerticeDestino        ) ;

		if(CondRetLista==LIS_CondRetOK)
		{
			return VER_CondRetVerticeSucessorJahExiste;

		}/* if */

		CondRetLista = LIS_InserirElementoApos( pVerticeOrigem->Sucessores ,
                                          pVerticeDestino        );

		if(CondRetLista == LIS_CondRetOK)
		{
			CondRetVertice = VER_AdicionarAntecessor ( tpVertice * pVerticeDestino, tpVertice * pVerticeOrigem );

			return CondRetVertice;

		}/* if */

		return VER_CondRetFaltouMemoria;


} /* Fim função: VER Adicionar Sucessor */

/***************************************************************************
*
*  Função: VER Remover Sucessor
*  ****/

	VER_tpCondRet VER_RemoverSucessor ( tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;
		VER_tpCondRet CondRetVertice;

		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if((pVerticeOrigem->Sucessores)==NULL)
		{
			return VER_CondRetVerticeNaoEhSucessor;
			

		}/* if */

		CondRetLista = LIS_ProcurarValor( pVerticeOrigem->Sucessores ,
                                    pVerticeDestino        ) ;

		if(CondRetLista==LIS_CondRetNaoEncontrou)
		{
			return VER_CondRetVerticeNaoEhSucessor;

		}/* if */

		if(CondRetLista== LIS_CondRetListaVazia)
		{
			return VER_CondRetVerticeNaoEhSucessor;

		}/* if */

		if(CondRetLista==LIS_CondRetOK)
		{
			CondRetLista = LIS_ExcluirElemento( pVerticeOrigem->Sucessores ) ;

			if(CondRetLista==LIS_CondRetOK)
			{
				CondRetVertice = VER_RemoverAntecessor ( tpVertice * pVerticeDestino, tpVertice * pVerticeOrigem );

				return CondRetVertice;

			}/* if */

		}/* if */

} /* Fim função: VER Remover Sucessor */

	/***************************************************************************
*
*  Função: VER Adicionar Antecessor
*  ****/

	VER_tpCondRet AdicionarAntecessor ( tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;
		VER_tpCondRet CondRetVertice;

		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if((pVerticeOrigem->Antecessores)==NULL)
		{
			pVerticeOrigem->Antecessores = LIS_CriarLista( VER_tpCondRet ( * VER_DestruirVertice ) 
														(tpVertice * pVertice ) );

			if((pVerticeOrigem->Antecessores)==NULL)
			{
				return  VER_CondRetFaltouMemoria;				

			}/* if */

		}/* if */

		CondRetLista = LIS_InserirElementoApos( pVerticeOrigem->Antecessores ,
                                          pVerticeDestino        );

		if(CondRetLista == LIS_CondRetOK)
		{
			
			return VER_CondRetOK;

		}/* if */

		return VER_CondRetFaltouMemoria;

	

} /* Fim função: VER Adicionar Antecessor */

/***************************************************************************
*
*  Função: VER Remover Antecessor
*  ****/

	VER_tpCondRet RemoverAntecessor ( tpVertice * pVerticeOrigem, tpVertice * pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;
		VER_tpCondRet CondRetVertice;

		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if((pVerticeOrigem->Antecessores)==NULL)
		{
			return VER_CondRetVerticeNaoEhAntecessor;
			

		}/* if */

		CondRetLista = LIS_ProcurarValor( pVerticeOrigem->Antecessores ,
                                    pVerticeDestino        ) ;

		if(CondRetLista==LIS_CondRetNaoEncontrou)
		{
			return VER_CondRetVerticeNaoEhAntecessor;

		}/* if */

		if(CondRetLista== LIS_CondRetListaVazia)
		{
			return VER_CondRetVerticeNaoEhAntecessor;

		}/* if */

		if(CondRetLista==LIS_CondRetOK)
		{
			CondRetLista = LIS_ExcluirElemento( pVerticeOrigem->Antecessores ) ;

			if(CondRetLista==LIS_CondRetOK)
			{
				return VER_CondRetOK;

			}/* if */

		}/* if */

} /* Fim função: VER Remover Antecessor */

/********** Fim do módulo de implementação: Módulo vértice **********/