/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo grafo
*
*  Arquivo gerado:              GRAFO.C
*  Letras identificadoras:      GRA
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo, Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     0       cev   12/set/2009 In�cio desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#include "GRAFO.H"
#include "VERTICE.H"
#include "LISTA.H"


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabe�a de um grafo
*
*
*  $ED Descri��o do tipo
*     A cabe�a do grafo � o ponto de acesso para um determinado grafo.
*     ...
*
***********************************************************************/

   typedef struct GRA_tgGrafo {

        LIS_tppLista ListaVertices ;
            /* Ponteiro para a lista de v�rtices do grafo 
			*
			*$EED Assertivas estruturais
			* ... */	 
		LIS_tppLista ListaOrigens ;
			/* Ponteiro para a lista de v�rtices do grafo 
			*
			*$EED Assertivas estruturais
			* ... */	 
		VER_tppVertice VerticeCorrente;
			  /* Ponteiro para o v�rtice corrente */

   } GRA_tpGrafo ;
/*****  Dados encapsulados no m�dulo  *****/

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

  VER_tppVertice ObtemVerticeComId ( GRA_tppGrafo pGrafo, int IdVertice );


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: GRA Criar grafo
*  ****/

   GRA_tpCondRet GRA_CriarGrafo ( GRA_tppGrafo * ppGrafo ){

	  if ( *ppGrafo != NULL ){
         GRA_DestruirGrafo( ppGrafo ) ;
      } /* if */

      *ppGrafo = ( GRA_tppGrafo ) malloc( sizeof( GRA_tpGrafo )) ;
      if ( *ppGrafo == NULL )
      {
         return GRA_CondRetFaltouMemoria ;
      } /* if */

      (*ppGrafo)->ListaVertices = LIS_CriarLista( VER_DestruirVertice );

	  (*ppGrafo)->ListaOrigens = LIS_CriarLista( NULL );
	  
	  (*ppGrafo)->VerticeCorrente = NULL;

	  return GRA_CondRetOK ;

} /* Fim fun��o: GRA Criar grafo */

/***************************************************************************
*
*  Fun��o: GRA Inserir v�rtice
*  ****/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, void * pValor , int IdVertice ){

	   VER_tpCondRet CondRetVertice;
	   LIS_tpCondRet CondRetLista;
	   VER_tppVertice pVertice = NULL;

	   /* Se grafo n�o existir, cria o grafo */
	   if( pGrafo == NULL )
	   {
		 return GRA_CondRetGrafoInexistente;

	   } /* if */

	   /* Checa se o id j� existe */
	   if ( ObtemVerticeComId ( pGrafo, IdVertice ) != NULL )
	   {
		   return GRA_CondRetIdJaExiste;
	   }
	  
	   /* Cria o v�rtice */
	   CondRetVertice = VER_CriarVertice ( &pVertice, pValor , IdVertice );
	   if( CondRetVertice != VER_CondRetOK )
	   {
		   return GRA_CondRetFaltouMemoria;
	   }
	   
	   /* Adiciona o v�rtice na lista de v�rtices */
	   CondRetLista = LIS_InserirElementoAntes( pGrafo->ListaVertices , pVertice );
	   if( CondRetLista == LIS_CondRetOK )
	   {
		   pGrafo->VerticeCorrente = pVertice;
		   return GRA_CondRetOK;
	   } else{
		   return GRA_CondRetFaltouMemoria;
	   } /* if */

} /* Fim fun��o: GRA Inserir v�rtice */

/***************************************************************************
*
*  Fun��o: GRA Excluir v�rtice 
*  ****/

   GRA_tpCondRet GRA_ExcluirVertice ( GRA_tppGrafo pGrafo ){

	  VER_tpCondRet CondRetVertice;

	   LIS_tppLista ListaSucessores;
	   LIS_tppLista ListaAntecessores;
	   LIS_tpCondRet CondRetLista;
	   
	   VER_tppVertice pVertice = pGrafo->VerticeCorrente;
	   VER_tppVertice pVerticeSucessorCorrente;
	   VER_tppVertice pVerticeAntecessorCorrente;
	   
	   if( pGrafo == NULL ){
		  return GRA_CondRetGrafoInexistente;
	   } /* if */

	   if( pVertice == NULL){
		   return GRA_CondRetGrafoVazio;
	   }
	
	   /* Percorre a lista de sucessores do v�rtice e os remove da lista*/
	   ListaSucessores = VER_ObterListaSucessores( pVertice );

	   if (ListaSucessores != NULL){
 
		   do{
			  
			   pVerticeSucessorCorrente = LIS_ObterValor( ListaSucessores ) ;

			   if( pVerticeSucessorCorrente != NULL ){
				   CondRetVertice = VER_RemoverSucessor ( pVertice,	
													  pVerticeSucessorCorrente );
				
					if (CondRetVertice != VER_CondRetOK)
					{
						printf("Erro ao excluir sucessores\n");
						return GRA_CondRetVerticeNaoExiste;
					}/* if */

			   }/* else */
		   }while(  (LIS_AvancarElementoCorrente( ListaSucessores, 1 ))
				 != (LIS_CondRetFimLista||LIS_CondRetListaVazia) ); /* do while */

	   }/* if */
	
	   /* Percorre a lista de antecessores do v�rtice e o remove pVertice 
	      das suas listas de sucessores */
	   ListaAntecessores = VER_ObterListaAntecessores( pVertice );

	   if (ListaAntecessores != NULL){
		  
		   do{
				pVerticeAntecessorCorrente = LIS_ObterValor( ListaAntecessores ) ;

				if( pVerticeAntecessorCorrente != NULL ){
					CondRetVertice = VER_RemoverSucessor ( pVerticeAntecessorCorrente,	
													  pVertice );
				
					if (CondRetVertice != VER_CondRetOK)
					{
						printf("Erro ao excluir antecessores\n");
						return GRA_CondRetVerticeNaoExiste;
					}/* if */
				}/*else */
		   }while(  (LIS_AvancarElementoCorrente( ListaAntecessores, 1 ))
				 != (LIS_CondRetFimLista||LIS_CondRetListaVazia) ); /* do while */

	   }/* if */

	  /* Remove da lista de v�rtices e destr�i*/	

	   IrInicioLista ( pGrafo->ListaVertices );

		 CondRetLista = LIS_ProcurarValor( pGrafo->ListaVertices ,
                                    pVertice        ) ;
		 
		 CondRetLista = LIS_ExcluirElemento( pGrafo->ListaVertices ) ;

		 IrInicioLista ( pGrafo->ListaVertices ) ;

		 pGrafo->VerticeCorrente = LIS_ObterValor ( pGrafo->ListaVertices ) ;
	  /* Remover v�rtice da lista de origens */

		return GRA_CondRetOK;


} /* Fim fun��o: GRA Excluir v�rtice */


   /***************************************************************************
*
*  Fun��o: GRA_MarcarComoOrigem
*  ****/

   GRA_tpCondRet GRA_MarcarComoOrigem ( GRA_tppGrafo pGrafo, int IdVertice ){

		LIS_tpCondRet CondRetLista;
		VER_tppVertice pVertice;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */

		pVertice = ObtemVerticeComId( pGrafo, IdVertice ) ;

		if ( pVertice == NULL){
			return GRA_CondRetIndiceInvalido;  /*Conferir essa CONDRET */
		}/* if */

		CondRetLista = LIS_InserirElementoAntes( pGrafo->ListaOrigens , pVertice ) ;

		if ( CondRetLista == LIS_CondRetFaltouMemoria){
			return GRA_CondRetFaltouMemoria ;
		} else{
			return GRA_CondRetOK ;
		}/* if */

} /* Fim fun��o: GRA_MarcarComoOrigem */


   /***************************************************************************
*
*  Fun��o: GRA_DesmarcarComoOrigem
*  ****/

   GRA_tpCondRet GRA_DesmarcarComoOrigem ( GRA_tppGrafo pGrafo, int IdVertice ){

		LIS_tpCondRet CondRetLista;
		VER_tppVertice pVertice;

		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */

			
		pVertice = ObtemVerticeComId( pGrafo, IdVertice ) ;

		if ( pVertice == NULL){
			return GRA_CondRetVerticeNaoEhOrigem ;
		}/* if */
	
		CondRetLista = LIS_ProcurarValor( pGrafo->ListaOrigens , pVertice );
		
		if ( CondRetLista == LIS_CondRetNaoAchou || CondRetLista == LIS_CondRetListaVazia ){
			return GRA_CondRetVerticeNaoEhOrigem ;
		} /* if */

		CondRetLista = LIS_ExcluirElemento( pGrafo->ListaOrigens) ;

		if ( CondRetLista == LIS_CondRetListaVazia ){
			return GRA_CondRetVerticeNaoEhOrigem ;
		} /* if */
	
		return GRA_CondRetOK;

} /* Fim fun��o: GRA_DesmarcarComoOrigem */

/***************************************************************************
*
*  Fun��o: GRA Inserir aresta
*  ****/

   GRA_tpCondRet GRA_InserirAresta ( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
									int idVerticeDestino ){

		VER_tpCondRet CondRetVertice;
		VER_tppVertice pVerticeOrigem;
		VER_tppVertice pVerticeDestino;
		
		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
	
		pVerticeOrigem = ObtemVerticeComId( pGrafo, idVerticeOrigem ) ;
		pVerticeDestino = ObtemVerticeComId( pGrafo, idVerticeDestino ) ;

		if ( (pVerticeOrigem == NULL) || (pVerticeDestino == NULL) ){
			return GRA_CondRetVerticeNaoExiste;
		}/* if */
		
		CondRetVertice = VER_AdicionarSucessor( pVerticeOrigem, pVerticeDestino ) ;

		if ( CondRetVertice == VER_CondRetFaltouMemoria ){
			return GRA_CondRetFaltouMemoria;
		} /* if */
		if ( CondRetVertice == VER_CondRetVerticeNaoExiste ){
			return GRA_CondRetVerticeNaoExiste;
		} /* if */
		if ( CondRetVertice == VER_CondRetVerticeSucessorJahExiste ){
			return GRA_CondRetArestaJaExiste;
		}else {
			return GRA_CondRetOK ;
		} /* if */
	   
} /* Fim fun��o: GRA Inserir aresta */

/***************************************************************************
*
*  Fun��o: GRA Remover aresta
*  ****/

   GRA_tpCondRet GRA_RemoverAresta ( GRA_tppGrafo pGrafo, int idVerticeOrigem, 
									int idVerticeDestino ){

		VER_tppVertice pVerticeOrigem ;
		VER_tppVertice pVerticeDestino ;
		VER_tpCondRet CondRetVertice;
		
		if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */
		
		pVerticeOrigem = ObtemVerticeComId( pGrafo, idVerticeOrigem ) ;
		pVerticeDestino = ObtemVerticeComId( pGrafo, idVerticeDestino ) ;

		if ( pVerticeOrigem == NULL || pVerticeDestino == NULL ){
			return GRA_CondRetVerticeNaoExiste;
		}/* if */

		CondRetVertice = VER_RemoverSucessor( pVerticeOrigem, pVerticeDestino ) ;

		if ( CondRetVertice == VER_CondRetVerticeNaoExiste ){
			return GRA_CondRetVerticeNaoExiste;
		} /* if */
		if ( CondRetVertice == VER_CondRetVerticeNaoEhSucessor ){
			return GRA_CondRetArestaNaoExiste;
		} else {
			return GRA_CondRetOK ;
		} /* if */
		
} /* Fim fun��o: GRA Remover aresta */


/***************************************************************************
*
*  Fun��o: GRA Exibir grafo
*  ****/

   GRA_tpCondRet GRA_ExibirGrafo ( GRA_tppGrafo pGrafo ){

	    VER_tppVertice pVertice;

		int IdVertice;

	   	if ( pGrafo == NULL ){
			return GRA_CondRetGrafoInexistente;
		}/* if */

	   IrInicioLista( pGrafo->ListaVertices ) ;
  
	   do{
		   pVertice = LIS_ObterValor( pGrafo->ListaVertices ) ;

		   if ( VER_ObterId( pVertice, &IdVertice ) == VER_CondRetVerticeNaoExiste ){
			
			   return GRA_CondRetVerticeNaoExiste;

		   } else {
			    
			   printf("Vertice: %d Sucessores: ", IdVertice);
			   VER_ExibirSucessores(pVertice);
			   printf("\n");
			    printf("Vertice: %d Antecessores: ", IdVertice);
			   VER_ExibirAntecessores(pVertice);
			   printf("\n\n");

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( pGrafo->ListaVertices, 1 )
		     != LIS_CondRetFimLista ); /* do while */

	   printf("<--->\n");

	 return GRA_CondRetOK;

} /* Fim fun��o: GRA Exibir Grafo */

	 
  

/***************************************************************************
*
*  Fun��o: GRA Destruir grafo
*  ****/

   GRA_tpCondRet GRA_DestruirGrafo ( GRA_tppGrafo* ppGrafo ){

	   if( *ppGrafo == NULL ){
		   return GRA_CondRetGrafoInexistente;
	   } /* if */

	   LIS_DestruirLista((*ppGrafo)->ListaVertices);
	   LIS_DestruirLista((*ppGrafo)->ListaOrigens);

	  
	   free(*ppGrafo);
	   (*ppGrafo) = NULL;

	   return GRA_CondRetOK ;

} /* Fim fun��o: GRA Destruir grafo */




/***************************************************************************
*
*  Fun��o: GRA Avan�ar Sucessor
*  ****/

 GRA_tpCondRet GRA_AvancarSucessor ( GRA_tppGrafo pGrafo, int IdVertice ){

	   LIS_tpCondRet CondRetLista;
	   LIS_tppLista ListaSucessores;
	   VER_tppVertice pVertice;
	   int IdVerticeTemp = -1;
	   int controle = 0;

	   if( pGrafo == NULL ){
		   return GRA_CondRetGrafoInexistente;
	   } /* if */

	   pVertice = pGrafo->VerticeCorrente;

	   if( pVertice == NULL )
	   {
		   return GRA_CondRetGrafoVazio;

	   } /* if */

	   ListaSucessores = VER_ObterListaSucessores( pVertice );

	   if( ListaSucessores == NULL )
	   {
		   return GRA_CondRetNaoHaSucessores;
	   }/* if */

	   while( ( ListaSucessores != NULL ) && ( controle == 0 ) )
	   {
		    pVertice = LIS_ObterValor( ListaSucessores );

			if((VER_ObterId ( pVertice, &IdVerticeTemp )) == VER_CondRetOK )
			{
				if( IdVerticeTemp == IdVertice )
				{
					pGrafo->VerticeCorrente = pVertice;
					controle = 1;

				}/* if */

			}/* if */
					   
		   CondRetLista = LIS_AvancarElementoCorrente( ListaSucessores ,
                                              1 ) ;
		   
	   } /* while */

	   if( controle == 1){
		   return GRA_CondRetOK ;

	   }
	   else
	   {
		   return GRA_CondRetVerticeNaoEhSucessor ;

	   }	   

} /* Fim fun��o: GRA Avan�ar Sucessor */


 /***************************************************************************
*
*  Fun��o: GRA Obter Valor Com Id
*  ****/

 GRA_tpCondRet GRA_ObterValorComId( GRA_tppGrafo pGrafo , int IdVertice , void** ppValor ){

	   int IdAuxiliar;
	   VER_tpCondRet CondRetVertice;
	   VER_tppVertice pVertice;

	   if( pGrafo == NULL ){
		   return GRA_CondRetGrafoInexistente;
	   } /* if */

	   IrInicioLista( pGrafo->ListaVertices ) ;
	   
	   do{      
		   pVertice = LIS_ObterValor( pGrafo->ListaVertices ) ;
			   
		   if ( (VER_ObterId( pVertice, &IdAuxiliar )) == VER_CondRetVerticeNaoExiste				   ){
			   return GRA_CondRetIndiceInvalido;

		   } else {
			   							   
			   if ( IdVertice == IdAuxiliar){
				   	
				    CondRetVertice = VER_ObterValor ( pVertice, ppValor );
					if( CondRetVertice == VER_CondRetVerticeVazio ) {
							return GRA_CondRetVerticeVazio;
					}/* if */

			   } /* if */ 

		   }/* if */

	   }while( LIS_AvancarElementoCorrente( pGrafo->ListaVertices, 1 )
		     != LIS_CondRetFimLista ); /* do while */

	  return GRA_CondRetOK;

} /* Fim fun��o: GRA Obter Valor Com Id */


 /***************************************************************************
*
*  Fun��o: GRA Ir Vertice Com Id
*  ****/

  GRA_tpCondRet GRA_IrVerticeComId( GRA_tppGrafo pGrafo , int IdVertice){

		VER_tppVertice pVertice = ObtemVerticeComId( pGrafo, IdVertice);
	
		if ( pVertice == NULL){
			return GRA_CondRetIndiceInvalido;
		}/* if */
		
		pGrafo->VerticeCorrente = pVertice;

		return GRA_CondRetOK;

} /* Fim fun��o: GRA Ir Vertice Com Id */


  /***************************************************************************
*
*  Fun��o: GRA Obter Sucessor
*  ****/

   	 GRA_tpCondRet GRA_ObterSucessor ( GRA_tppGrafo pGrafo , int IdVertice , 
								      int * pIdSucessor ) {
		
		  VER_tpCondRet CondRetVertice;
		  LIS_tpCondRet CondRetLista;
		  LIS_tppLista ListaSucessores;
		  	    
		  VER_tppVertice pVerticeSucessor;
		  VER_tppVertice pVertice = ObtemVerticeComId( pGrafo, IdVertice);

		  if ( pVertice == NULL ){
			  return GRA_CondRetIndiceInvalido ;
		  }/* if */

		  /* Obt�m �ndice do vertice corrente da lista de sucessores de pVertice*/
		  ListaSucessores = VER_ObterListaSucessores ( pVertice );

		  if ( ListaSucessores == NULL ){
			  return GRA_CondRetNaoHaSucessores ;
		  }/* if */

		  pVerticeSucessor = LIS_ObterValor( ListaSucessores ) ;

			  if ( pVerticeSucessor == NULL ){
				  return GRA_CondRetNaoHaSucessores ;
			  }/* if */
														/*modifica valor do id*/
		  CondRetVertice = VER_ObterId( pVerticeSucessor, pIdSucessor ); 

				  if ( CondRetVertice == VER_CondRetVerticeNaoExiste ){
						return GRA_CondRetNaoHaSucessores ;
				  }/* if */

		  /* Seta o novo elemento corrente da lista*/
		  CondRetLista = LIS_AvancarElementoCorrente( ListaSucessores, 1) ;
				  
		  if ( CondRetLista == LIS_CondRetListaVazia ){
				return GRA_CondRetNaoHaSucessores ;
		  }/* if */
		  
		  if ( CondRetLista == LIS_CondRetFimLista ){
				IrInicioLista( ListaSucessores ) ;
		  }/* if */


     return GRA_CondRetOK; 

} /* Fim fun��o: GRA ObterSucessor */


  /***************************************************************************
*
*  Fun��o: GRA Obter Antecessor
*  ****/

   	 GRA_tpCondRet GRA_ObterAntecessor ( GRA_tppGrafo pGrafo , int IdVertice , 
								        int * pIdAntecessor ) {
		
		  VER_tpCondRet CondRetVertice;
		  LIS_tpCondRet CondRetLista;
		  LIS_tppLista ListaAntecessores;

		  VER_tppVertice pVerticeAntecessor;
		  VER_tppVertice pVertice = ObtemVerticeComId( pGrafo, IdVertice);

		  if ( pVertice == NULL ){
			  return GRA_CondRetIndiceInvalido ;
		  }/* if */

		  /* Obt�m �ndice do vertice corrente da lista de antecessores de pVertice*/
		  ListaAntecessores = VER_ObterListaAntecessores ( pVertice );

		  if ( ListaAntecessores == NULL ){
			  return GRA_CondRetNaoHaAntecessores ;
		  }/* if */

		  pVerticeAntecessor = LIS_ObterValor( ListaAntecessores ) ;

			  if ( pVerticeAntecessor == NULL ){
				  return GRA_CondRetNaoHaAntecessores ;
			  }/* if */
														/*modifica valor do id*/
		  CondRetVertice = VER_ObterId( pVerticeAntecessor, pIdAntecessor ); 

				  if ( CondRetVertice == VER_CondRetVerticeNaoExiste ){
						return GRA_CondRetNaoHaAntecessores ;
				  }/* if */

		  /* Seta o novo elemento corrente da lista*/
		  CondRetLista = LIS_AvancarElementoCorrente( ListaAntecessores, 1) ;
				  
		  if ( CondRetLista == LIS_CondRetListaVazia ){
				return GRA_CondRetNaoHaAntecessores ;
		  }/* if */
		  
		  if ( CondRetLista == LIS_CondRetFimLista ){
				IrInicioLista( ListaAntecessores ) ;
		  }/* if */


     return GRA_CondRetOK; 

} /* Fim fun��o: GRA ObterAntecessor */


 /*****  C�digo das fun��es encapsuladas no m�dulo  *****/

 /***********************************************************************
*
*  $FC Fun��o: Obtem V�rtice Com ID
*
*  $ED Descri��o da fun��o
*     Obt�m o v�rtice a partir do �ndice dado.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para a cabe�a do grafo.
*     $P IdVertice - indice do v�rtice a ser marcado como origem.
*
*  $FV Valor retornado
*     Retorna o endere�o do v�rtice (tipo VER_tppVertice) caso este seja encontrado
*	  ou NULL caso n�o seja encontrado nenhum v�rtice com o �ndice passado.
*
***********************************************************************/

   VER_tppVertice ObtemVerticeComId ( GRA_tppGrafo pGrafo, int IdVertice ){

	   int IdAuxiliar;
	   VER_tppVertice pVertice;

	   if( pGrafo == NULL ){
		   return NULL;
	   } /* if */

	   IrInicioLista( pGrafo->ListaVertices ) ;
	   
	   do{      
		   pVertice = LIS_ObterValor( pGrafo->ListaVertices ) ;
		   
		   if ( (VER_ObterId( pVertice, &IdAuxiliar )) == VER_CondRetVerticeNaoExiste ){
			   return NULL;

		   } else {
			   							   
			   if ( IdVertice == IdAuxiliar){
				   return pVertice; 
			   } /* if */ 

		   } /* if */


	   }while( LIS_AvancarElementoCorrente( pGrafo->ListaVertices, 1 )
		     != LIS_CondRetFimLista ); /* do while */

	  return NULL;

} /* Fim fun��o: ObtemVerticeComId */



		
/********** Fim do m�dulo de implementa��o: M�dulo grafo **********/