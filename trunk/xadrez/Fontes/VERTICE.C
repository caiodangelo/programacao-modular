/***************************************************************************
*  $MCI Módulo de implementação: Módulo vértice
*
*  Arquivo gerado:              VERTICE.C
*  Letras identificadoras:      VER
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       0	   cev   12/09/2009 Início do desenvolvimento
*       1	   cev   19/10/2009 Entrega do trabalho
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#include "VERTICE.H"
#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: VER &Descritor do vértice
*
*
*  $ED Descrição do tipo
*     O vértice é uma estrutura que armazena uma referência para um valor
*	  de qualquer tipo. Ele também armazena uma lista de sucessores, uma
*	  lista de antecessores e um identificador.
*
***********************************************************************/

   typedef struct VER_tgVertice {

		 void * Valor;
			   /* Informação do Vértice */
		 
         LIS_tppLista Sucessores ;
               /* Ponteiro para a lista de próximos vértices */

         LIS_tppLista Antecessores ;
               /* Ponteiro para a lista de vértices anteriores */

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
*  Função: VER &Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice ( VER_tppVertice* ppVertice, void * Valor, int IdVertice ){

	  /* Verifica se existe valor armazenado no ponteiro */
	  if ( *ppVertice != NULL )
      {
         VER_DestruirVertice( *ppVertice ) ;
      } /* if */
	 
	  /* Aloca a memória para o vértice */
      (*ppVertice) = ( VER_tppVertice ) malloc( sizeof( VER_tpVertice )) ;
      if ( *ppVertice == NULL )
      {
         return VER_CondRetFaltouMemoria ;
      } /* if */
	 
	  /* Preenche os atributos */
      (*ppVertice)->Valor = Valor;
	  (*ppVertice)->Sucessores = LIS_CriarLista( NULL );
	  (*ppVertice)->Antecessores = LIS_CriarLista( NULL );
	  (*ppVertice)->IdVertice = IdVertice;
	 
	  return VER_CondRetOK ;

} /* Fim função: VER &Criar vértice */

/***************************************************************************
*
*  Função: VER &Obter valor
*  ****/

   VER_tpCondRet VER_ObterValor ( VER_tppVertice pVertice, void ** ppValor ) {

	   /* Verifica se o vértice existe */
		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		/* Verifica se o vértice está vazio */
		if ( pVertice->Valor == NULL )
		{
			return VER_CondRetVerticeVazio ;
		} /* if */
		
		/* Faz a atribuição */
		else {
			*ppValor = pVertice->Valor;
		} /* else */

   	  return VER_CondRetOK ;

} /* Fim função: VER &Obter Valor */

/***************************************************************************
*
*  Função: VER &Alterar valor
*  ****/

   VER_tpCondRet VER_AlterarValor ( VER_tppVertice pVertice, void * ValorNovo ){

	   /* Verifica se o vértice existe */
		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		/* Faz a atribuição */
		pVertice->Valor = ValorNovo ;

   	  return VER_CondRetOK ;

} /* Fim função: VER &Alterar Valor */

/***************************************************************************
*
*  Função: VER &Destruir vértice
*  ****/

	void VER_DestruirVertice ( void * pVerticeVoid ){
		
		VER_tppVertice pVertice = ( VER_tppVertice ) pVerticeVoid ;

		/* Verifica se o vértice existe */
		if ( pVertice == NULL ){
			return;
		} /* if */

		/* Libera o espaço alocado pelas listas */
		LIS_DestruirLista( pVertice->Sucessores );
		LIS_DestruirLista( pVertice->Antecessores );

		/* Libera o espaço alocado pelo vértice */
		free( pVertice );
		
		return ;

} /* Fim função: VER &Destruir Vertice */

/***************************************************************************
*
*  Função: VER &Adicionar Sucessor
*  ****/

	VER_tpCondRet VER_AdicionarSucessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino ){
		
		/* Declara variáveis locais */
		LIS_tpCondRet CondRetLista;
		VER_tpCondRet CondRetVertice;

		/* Verifica se o vértice existe */
		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		/* Verifica se existe a lista de sucessores */
		if((pVerticeOrigem->Sucessores)==NULL)
		{
			pVerticeOrigem->Sucessores = LIS_CriarLista( NULL );

			if((pVerticeOrigem->Sucessores)==NULL)
			{
				return  VER_CondRetFaltouMemoria;				

			}/* if */

		}/* if */

		/* Verifica se o vértice adicionado já está na lista */
		CondRetLista = LIS_ProcurarValor( pVerticeOrigem->Sucessores ,
                                    pVerticeDestino        ) ;

		if(CondRetLista==LIS_CondRetOK)
		{
			return VER_CondRetVerticeSucessorJahExiste;

		}/* if */

		/* Insere o vértice na lista de sucessores */
		CondRetLista = LIS_InserirElementoApos( pVerticeOrigem->Sucessores ,
                                          pVerticeDestino        );

		/* Se insere na lista de sucessores do vértice */
		if(CondRetLista == LIS_CondRetOK)
		{
			CondRetVertice = AdicionarAntecessor (  pVerticeDestino, pVerticeOrigem );

			return CondRetVertice;

		}/* if */

		return VER_CondRetFaltouMemoria;


} /* Fim função: VER &Adicionar Sucessor */

/***************************************************************************
*
*  Função: VER &Remover Sucessor
*  ****/

	VER_tpCondRet VER_RemoverSucessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino ){
		
		/* Declara variáveis locais */
		LIS_tpCondRet CondRetLista;
		VER_tpCondRet CondRetVertice;
	
		/* Verifica se o vértice existe */
		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		/* Verifica se a lista de sucessores da origem existe */
		if((pVerticeOrigem->Sucessores)==NULL)
		{
			return VER_CondRetErroEstrutural;
			
		}/* if */

		/* Busca o valor na lista */
		IrInicioLista ( pVerticeOrigem->Sucessores );

		CondRetLista = LIS_ProcurarValor( pVerticeOrigem->Sucessores ,
                                    pVerticeDestino        );

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

} /* Fim função: VER &Remover Sucessor */

/***************************************************************************
*
*  Função: VER &Obter ID
*  ****/

	VER_tpCondRet VER_ObterId ( VER_tppVertice pVertice, int * pIdVertice ){		

		if ( pVertice == NULL )
		{
			return VER_CondRetVerticeNaoExiste;
		} /* if */
		*pIdVertice = pVertice->IdVertice;
		
		return VER_CondRetOK;

} /* Fim função: VER &Obter ID */
/***************************************************************************
*
*  Função: VER &Exibir Sucessores
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
			printf ( "Erro estrutural");
			return ;
		}/* if */

		IrInicioLista( ListaSucessores ) ;

		do{
		   
			pVertice = LIS_ObterValor( ListaSucessores ) ;

			if ( pVertice == NULL ){
				printf(" Nao ha sucessores.");
			}/* if */

		   if ( VER_ObterId( pVertice, &IdVertice ) == VER_CondRetVerticeNaoExiste ){
			   return ;

		   } else {
			    
			   printf(" %d ", IdVertice);

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( ListaSucessores, 1 )
		     != LIS_CondRetFimLista ); /* do while */

		
   return;


} /* Fim função: VER &Exibir Sucessores */
/***************************************************************************
*
*  Função: VER &Obter Lista de Sucessores
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

		//IrInicioLista ( pVertice->Sucessores );

		Sucessores = pVertice->Sucessores;

		return Sucessores;

   }/* Fim função: VER &Obter Lista de Sucessores */
/***************************************************************************
*
*  Função: VER &Obter Lista de Antecessores
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

		Antecessores = pVertice->Antecessores;

		return Antecessores;

   }/* Fim função: VER &Obter Lista de Antecessores */
/***************************************************************************
*
*  Função: VER &Exibir Antecessores
*  ****/

   void VER_ExibirAntecessores ( VER_tppVertice pVertice ){

		int IdVertice;
		LIS_tppLista ListaAntecessores;

		if( pVertice == NULL )
		{
			return;
		}/* if */

		ListaAntecessores = VER_ObterListaAntecessores ( pVertice);

		if ( ListaAntecessores == NULL ){
			printf ( "Erro estrutural.");
			return ;
		}/* if */

		IrInicioLista( ListaAntecessores ) ;

		do{
		   
			pVertice = LIS_ObterValor( ListaAntecessores ) ;

			if ( pVertice == NULL ){
				printf(" Nao ha antecessores.");
			}/* if */

		   if ( VER_ObterId( pVertice, &IdVertice ) == VER_CondRetVerticeNaoExiste ){
			   return ;

		   } else {
			    
			   printf(" %d ", IdVertice);

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( ListaAntecessores, 1 )
		     != LIS_CondRetFimLista ); /* do while */

		
   return;


} /* Fim função: VER &Exibir Antecessores */

/*****  Código das funções exportadas pelo módulo  *****/ 

/***************************************************************************
*
*  Função: VER -Adicionar Antecessor
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

	

} /* Fim função: VER -Adicionar Antecessor */

/***************************************************************************
*
*  Função: VER -Remover Antecessor
*  ****/

	VER_tpCondRet RemoverAntecessor ( VER_tppVertice pVerticeOrigem, VER_tppVertice pVerticeDestino ){
		
		LIS_tpCondRet CondRetLista;

		if ( pVerticeOrigem == NULL )
		{
			return VER_CondRetVerticeNaoExiste ;
		} /* if */

		if((pVerticeOrigem->Antecessores)==NULL)
		{
			return VER_CondRetErroEstrutural;
			

		}/* if */

		IrInicioLista ( pVerticeOrigem->Antecessores );

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

} /* Fim função: VER -Remover Antecessor */
/********** Fim do módulo de implementação: Módulo vértice **********/
