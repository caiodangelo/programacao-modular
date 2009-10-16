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

   typedef struct VER_tgVertice {

		 void * Valor;
			   /* Informação do Vértice */
		 
         LIS_tppLista Sucessores ;
               /* Ponteiro para a lista de vértices que são atingidos*/

         LIS_tppLista Antecessores ;
               /* Ponteiro para a lista de vértices que atingem*/

		 int IdVertice;
			  /* Identificador do vértice */

   } VER_tpVertice ;


/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

   VER_tpCondRet AdicionarAntecessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino );

   VER_tpCondRet RemoverAntecessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino );
  

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice ( VER_tppVertice* ppVertice, void * Valor, int IdVertice ){

	  if ( *ppVertice != NULL )
      {
         VER_DestruirVertice( ppVertice ) ;
      } /* if */
	 
      (*ppVertice) = ( VER_tppVertice ) malloc( sizeof( VER_tpVertice )) ;
      if ( *ppVertice == NULL )
      {
         return VER_CondRetFaltouMemoria ;
      } /* if */
	 
      (*ppVertice)->Valor = Valor;
	  (*ppVertice)->Sucessores = NULL;
	  (*ppVertice)->Antecessores = NULL;
	  (*ppVertice)->IdVertice = IdVertice;
	 
	  return VER_CondRetOK ;

} /* Fim função: VER Criar vértice */

/***************************************************************************
*
*  Função: VER Obter valor
*  ****/

   VER_tpCondRet VER_ObterValor ( VER_tppVertice pVertice, void ** ppValor ) {

		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if ( pVertice->Valor == NULL )
		{
			return VER_CondRetVerticeVazio ;
		} /* if */
		
		else {
			*ppValor = pVertice->Valor;
			printf("valor - %d\n", *ppValor );
		} /* else */

   	  return VER_CondRetOK ;

} /* Fim função: VER Obter Valor */

/***************************************************************************
*
*  Função: VER Alterar valor
*  ****/

   VER_tpCondRet VER_AlterarValor ( VER_tppVertice pVertice, void * ValorNovo ){

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

	void VER_DestruirVertice ( VER_tppVertice* ppVertice ){

		if ( *ppVertice == NULL )
		{
			return;
		} /* if */

		if( ((*ppVertice)->Antecessores) != NULL )
		{
			LIS_DestruirLista( ((*ppVertice)->Antecessores) );
		}/* if */
		if( ((*ppVertice)->Sucessores) != NULL )
		{
			LIS_DestruirLista( ((*ppVertice)->Sucessores) );
		}/* if */		

		free( *ppVertice );
		*ppVertice = NULL;
		
		return ;

} /* Fim função: VER Destruir Vertice */

/***************************************************************************
*
*  Função: VER Adicionar Sucessor
*  ****/

	VER_tpCondRet VER_AdicionarSucessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;
		VER_tpCondRet CondRetVertice;

		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if((pVerticeOrigem->Sucessores)==NULL)
		{
			pVerticeOrigem->Sucessores = LIS_CriarLista( NULL );

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
			CondRetVertice = AdicionarAntecessor (  pVerticeDestino, pVerticeOrigem );

			return CondRetVertice;

		}/* if */

		return VER_CondRetFaltouMemoria;


} /* Fim função: VER Adicionar Sucessor */

/***************************************************************************
*
*  Função: VER Remover Sucessor
*  ****/

	VER_tpCondRet VER_RemoverSucessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino ){
		
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

		if(CondRetLista==LIS_CondRetNaoAchou)
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
				CondRetVertice = RemoverAntecessor ( pVerticeDestino, pVerticeOrigem );

				return CondRetVertice;

			}/* if */

		}/* if */

		return VER_CondRetOK;

} /* Fim função: VER Remover Sucessor */

	/***************************************************************************
*
*  Função: VER Adicionar Antecessor
*  ****/

	VER_tpCondRet AdicionarAntecessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;

		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if((pVerticeOrigem->Antecessores)==NULL)
		{
			pVerticeOrigem->Antecessores = LIS_CriarLista( NULL );

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

	VER_tpCondRet RemoverAntecessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;

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

		if(CondRetLista==LIS_CondRetNaoAchou)
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

		return VER_CondRetOK;

} /* Fim função: VER Remover Antecessor */

/***************************************************************************
*
*  Função: VER Obter ID
*  ****/

	VER_tpCondRet VER_ObterId ( VER_tppVertice pVertice, int * pIdVertice ){		

		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste;
		} /* if */

		*pIdVertice = pVertice->IdVertice;
		
		return VER_CondRetOK;

} /* Fim função: VER Obter ID */
/***************************************************************************
*
*  Função: VER Exibir Sucessores
*  ****/

   void VER_ExibirSucessores ( VER_tppVertice pVertice ){

		int IdVertice;
		LIS_tppLista ListaSucessores;

		if( pVertice == NULL )
		{
			return;

		}/* if */

		ListaSucessores = VER_ObterListaSucessores ( pVertice);

		if ( ListaSucessores == NULL ){
			printf ( "Lista de sucessores vazia");
			return ;
		}/* if */

		IrInicioLista( ListaSucessores ) ;

		do{
		   
			pVertice = LIS_ObterValor( ListaSucessores ) ;

		   if ( VER_ObterId( pVertice, &IdVertice ) == VER_CondRetVerticeNaoExiste ){
			   printf("\n");
			   return ;

		   } else {
			    
			   printf(" %d ", IdVertice);

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( ListaSucessores, 1 )
		     != LIS_CondRetFimLista ); /* do while */

		
   return;


} /* Fim função: VER Exibir Sucessores */
/***************************************************************************
*
*  Função: VER Obter Lista de Sucessores
*  ****/

   LIS_tppLista VER_ObterListaSucessores ( VER_tppVertice pVertice ){

	   LIS_tppLista Sucessores;

		if( pVertice == NULL )
		{
			return NULL;
		}/* if */

		if( pVertice->Sucessores == NULL )
		{
			return NULL;
		}/* if */

		IrInicioLista ( pVertice->Sucessores );

		Sucessores = pVertice->Sucessores;

		return Sucessores;

   }/* Fim função: VER Obter Lista de Sucessores */
/***************************************************************************
*
*  Função: VER Obter Lista de Antecessores
*  ****/

   LIS_tppLista VER_ObterListaAntecessores ( VER_tppVertice pVertice ){

	   LIS_tppLista Antecessores;

		if( pVertice == NULL )
		{
			return NULL;
		}/* if */

		if( pVertice->Antecessores == NULL )
		{
			return NULL;
		}/* if */

		IrInicioLista ( pVertice->Antecessores );

		Antecessores = pVertice->Antecessores;

		return Antecessores;

   }/* Fim função: VER Obter Lista de Antecessores */
/********** Fim do módulo de implementação: Módulo vértice **********/
