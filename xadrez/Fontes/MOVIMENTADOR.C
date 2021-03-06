/***************************************************************************
*  $MCI M�dulo de implementa��o: MOV Movimentador de pe�as de Xadrez
*
*  Arquivo gerado:              MOVIMENTADOR.C
*  Letras identificadoras:      MOV
*
*  Projeto: INF 1301 Programa��o Modular
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo , Eduardo Velloso e Vitor Barbarisi
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     0       cev   12/set/2009 In�cio desenvolvimento
*	  1		  cev	19/out/2009 Entrega do trabalho
*
***************************************************************************/
#include "GERENCIADOR.H"
#include "MOVIMENTADOR.H"
#include "GRAFO.H"
#include <stdio.h>
#include <stdlib.h>

#define TAM_MOVIMENTO 10
#define REGRASD "..\\Definicao\\REGRASD.TXT"
#define REGRASC "..\\Definicao\\REGRASC.TXT"
#define INX_TIPO 0
#define FALSO 0
#define VERDADEIRO 1

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

int CodificaPosicao ( char Coluna , int Linha );

MOV_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo,  char ColunaCorrente, int LinhaCorrente ,  char ColunaProximo, int LinhaProximo,char TipoDaCasa, GER_tpCorPeca p );

MOV_tpCondRet AdicionaProximosDiscretos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente );

MOV_tpCondRet AdicionaProximosContinuos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimentos, char Coluna, int Linha );

int ReconheceXeque ( char cCor, GRA_tppGrafo pGrafo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***************************************************************************
*
*  Fun��o: MOV  &Adicionar Pecas Ao Grafo
*  ****/

MOV_tpCondRet MOV_AdicionarPecasAoGrafo ( GRA_tppGrafo * ppGrafo ){
	
	/* Declara��o das vari�veis locais */
	int linha;
	int coluna;
	GER_tpCondRet CondRetGER;
	GRA_tpCondRet CondRetGRA;
	GER_tppPeca pPeca;
	int id;

	/* Cria o grafo */
	CondRetGRA = GRA_CriarGrafo ( ppGrafo );
	if ( CondRetGRA != GRA_CondRetOK ){
		return MOV_CondRetNaoCriouGrafo;
	}

	/* Percorre o tabuleiro */
	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){
			
			/* Obt�m a pe�a do tabuleiro */
			CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if ( CondRetGER != GER_CondRetOK ){
				return MOV_CondRetNaoCriouVertice;
			}

			/* Gera o identificador da pe�a */
			id = CodificaPosicao ( (char)coluna , linha );
			
			/* Insere a pe�a no grafo com o id gerado */
			CondRetGRA = GRA_InserirVertice ( *ppGrafo , pPeca , id );

			if ( CondRetGRA != GRA_CondRetOK ){

				return MOV_CondRetNaoInseriuPeca;
			}
		}
	}

	return MOV_CondRetOK ;
} /* Fim da Fun��o: MOV  &Adicionar Pecas Ao Grafo */

/***************************************************************************
*
*  Fun��o: MOV  &Gera Movimenta��es
*  ****/
MOV_tpCondRet MOV_GeraMovimentacoes ( GRA_tppGrafo * ppGrafo ){
	FILE * ArquivoDeRegras;
	GRA_tppGrafo pGrafo = * ppGrafo;
	int linha;
	int coluna;
	GER_tpCondRet CondRetGer;
	GER_tppPeca pPeca;
	char movimentos[TAM_MOVIMENTO];
	GER_tpTipoPeca TipoPeca;

	/* Verifica se o grafo est� criado */
	if ( pGrafo == NULL )
	{
		return MOV_CondRetNaoCriouGrafo ;
	}

	/* Percorre todas as pe�as do tabuleiro */
	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){

			/* Obt�m a pe�a do tabuleiro */
			CondRetGer = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if (CondRetGer != GER_CondRetOK )
			{
				return MOV_CondRetPosicaoInvalida ;
			}

			/* Obt�m o tipo da pe�a */
			TipoPeca = GER_ObterTipo ( pPeca );
			if ( TipoPeca == -1 )
			{
				return MOV_CondRetPosicaoInvalida;
			}

			/* Abre o arquivo de regras de movimenta��o discreta para leitura */
			ArquivoDeRegras = fopen ( REGRASD , "r" );
			if ( ArquivoDeRegras == NULL )
			{
				return MOV_CondRetArquivoNaoExiste ;
			}

			/* Busca no arquivo as regras correspondentes �quele tipo */
			while ( fgets ( movimentos , TAM_MOVIMENTO , ArquivoDeRegras ) )
			{
				/* Se a regra corresponder ao tipo, adicionar as pe�as correspondentes */
				if ( TipoPeca == GER_ObterCodigoDoTipo (  movimentos[INX_TIPO] ) )
				{
					AdicionaProximosDiscretos ( pPeca , pGrafo , movimentos, (char)coluna, linha );					
				}
			}

			/* Fecha o arquivo de regras de movimenta��o discreta */
			fclose( ArquivoDeRegras );

			/* Abre o arquivo de regras de movimenta��o cont�nua para leitura */
			ArquivoDeRegras = fopen ( REGRASC , "r" );
			if ( ArquivoDeRegras == NULL )
			{
				return MOV_CondRetArquivoNaoExiste ;
			}

			/* Busca no arquivo as regras correspondentes �quele tipo */
			while ( fgets ( movimentos , TAM_MOVIMENTO , ArquivoDeRegras ) )
			{
				/* Se a regra corresponder ao tipo, adicionar as pe�as correspondentes */
				if ( TipoPeca == GER_ObterCodigoDoTipo (  movimentos[INX_TIPO] ) )
				{
					AdicionaProximosContinuos ( pPeca , pGrafo , movimentos, (char)coluna, linha );					
				}
			}

			/* Fecha o arquivo de regras de movimenta��o cont�nua */
			fclose( ArquivoDeRegras );

		}
	}

	*ppGrafo = pGrafo;
	return MOV_CondRetOK;
} /* Fim da Fun��o: MOV  &Gera Movimenta��es */

/***************************************************************************
*
*  Fun��o: MOV  &Reconhecer Xeque Mate
*  ****/
MOV_tpCondRet MOV_ReconhecerXequeMate ( char cCor , GRA_tppGrafo pGrafo ){

        int linha, idAtual, idSucessor, primeiroSucessor;
        char coluna;
        GER_tpCondRet CondRetGerenciador;
        GER_tppPeca pPeca;
        GER_tppPeca pPecaOrigem, pPecaDestino;
		GER_tppPeca pPecaTemp;
        GER_tpCorPeca corPeca, cor, corPecaTemp;
        GRA_tpCondRet CondRetGrafo;
        GRA_tppGrafo pGrafoLocal = NULL;
        MOV_tpCondRet CondRetMovimentador;

        GER_tpTipoPeca tipoPeca, tipoPecaTemp;

        cor = GER_ObterCodigoDaCor ( cCor );

        /* Verifica se o Rei est� em xeque */
        if((ReconheceXeque( cCor , pGrafo )) == FALSO)
        {
                return MOV_CondRetNaoEstaEmXequeMate;
        }


        /* Percorre o tabuleiro */
        for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro() ; linha++ ){
                for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){

                        /* Ob�m pe�a do tabuleiro */
                        CondRetGerenciador = GER_ObterPecaDoTabuleiro ( &pPeca, coluna, linha );

                        if(CondRetGerenciador != GER_CondRetOK ){
                                printf("Erro ao obter peca do tabuleiro.\n");
								return MOV_CondRetPecaNaoExiste;

                        }
                       
                        /* Obt�m cor da pe�a */
                        corPeca = GER_ObterCor ( pPeca ) ;
                        tipoPeca = GER_ObterTipo ( pPeca ) ;

                        /* Verifica se cor obtida � igual � cor do Rei */
                        if( corPeca == cor ){

                                /* Codifica posi��o da pe�a */
                                idAtual = CodificaPosicao ( coluna , linha );

                                /* Procura a pe�a no grafo */
                                CondRetGrafo = GRA_IrVerticeComId( pGrafo , idAtual);

                                if( CondRetGrafo != GRA_CondRetOK ){
                                        printf("Erro ao caminhar no grafo de movimentos.\n");
										return MOV_CondRetPecaNaoExiste;

                                }

                                /* Obt�m primeiro sucessor = */
                                CondRetGrafo = GRA_ObterSucessor ( pGrafo , idAtual ,
                                                                          &primeiroSucessor );

                                if( CondRetGrafo == GRA_CondRetNaoHaSucessores){
                                        /* Pe�a n�o tem movimentos poss�veis */
										continue;
                                }
                                else{

                                        /*  */
                                        idSucessor = primeiroSucessor;

                                        do{
												/* Obt�m valor da pe�a */
                                                CondRetGrafo = GRA_ObterValorComId( pGrafo , idAtual , &pPecaOrigem );
                                                CondRetGrafo = GRA_ObterValorComId( pGrafo , idSucessor , &pPecaDestino );
												pPecaTemp = pPecaDestino;
												corPecaTemp = GER_ObterCor ( pPecaTemp );
												tipoPecaTemp = GER_ObterTipo ( pPecaTemp );


                                                /* Gera movimenta��o */
                                                CondRetGerenciador = GER_MoverPeca ( pPecaOrigem , pPecaDestino );

                                                /* Cria o grafo � partir do novo tabuleiro */
                                                CondRetMovimentador = MOV_AdicionarPecasAoGrafo ( &pGrafoLocal ); 
                                                CondRetMovimentador = MOV_GeraMovimentacoes ( &pGrafoLocal );

                                                /* Verifica se o rei continua em xeque */
                                                if((ReconheceXeque( cCor , pGrafoLocal )) == FALSO)
                                                {
														/* Destruir o grafo criado */
														CondRetGrafo = GRA_DestruirGrafo( &pGrafoLocal );

														/* Desfaz movimenta��o */
														CondRetGerenciador = GER_MoverPeca ( pPecaDestino , pPecaOrigem );
														CondRetGerenciador = GER_AtribuirPeca ( pPecaTemp, tipoPecaTemp, corPecaTemp );

                                                        return MOV_CondRetNaoEstaEmXequeMate;
                                                }

                                                /* Destruir o grafo criado */
                                                CondRetGrafo = GRA_DestruirGrafo( &pGrafoLocal );

                                                /* Desfaz movimenta��o */
                                                CondRetGerenciador = GER_MoverPeca ( pPecaDestino , pPecaOrigem );
												CondRetGerenciador = GER_AtribuirPeca ( pPecaTemp, tipoPecaTemp, corPecaTemp );

                                                /* Obt�m o pr�ximo Sucessor */
                                                CondRetGrafo = GRA_ObterSucessor ( pGrafo , idAtual ,
                                                                          &idSucessor );

                                        }
                                        while( idSucessor != primeiroSucessor );/* do while */
                                }/* else */
                        }/* if */                      
                }/* for */
        }/* for */

        return MOV_CondRetXequeMate;

}/* Fim da fun��o Recohecer Xeque Mate */
/***************************************************************************
*
*  Fun��o: MOV  &Mover Pe�a
*  ****/
MOV_tpCondRet MOV_MoverPeca ( char ColunaOrigem , int LinhaOrigem , char ColunaDestino , int LinhaDestino , GRA_tppGrafo pGrafo ){
       
        GER_tppPeca pPecaOrigem ;
        GER_tppPeca pPecaDestino ;
        int idOrigem = -1 ;
        int idDestino = -2 ;
        int idTemp = -3 ;
        int idPrimeiro = -4 ;
        GER_tpCondRet CondRetGER = GER_CondRetOK ;
        GRA_tpCondRet CondRetGRA = GRA_CondRetOK ;


        CondRetGER = GER_ObterPecaDoTabuleiro ( &pPecaOrigem , ColunaOrigem , LinhaOrigem ) ;
        if ( CondRetGER != GER_CondRetOK )
        {
                return MOV_CondRetPecaNaoExiste ;
        }

       

        idOrigem = CodificaPosicao ( ColunaOrigem , LinhaOrigem ) ;
        idDestino = CodificaPosicao ( ColunaDestino , LinhaDestino ) ;

        CondRetGRA = GRA_ObterSucessor ( pGrafo , idOrigem , &idPrimeiro ) ;
        if ( CondRetGRA == GRA_CondRetNaoHaSucessores )
        {
                return MOV_CondRetMovimentoInvalido ;
        }

        idTemp = idPrimeiro ;
        do
        {
                if ( idTemp == idDestino )
                {
                        CondRetGER = GER_ObterPecaDoTabuleiro ( &pPecaDestino , ColunaDestino , LinhaDestino ) ;
                        if ( CondRetGER != GER_CondRetOK )
                        {
                                return MOV_CondRetPecaNaoExiste ;
                        }

                        CondRetGER = GER_MoverPeca ( pPecaOrigem , pPecaDestino );
                        if ( CondRetGER != GER_CondRetOK )
                        {
                                return MOV_CondRetMovimentoInvalido ;
                        }
                       
                        return MOV_CondRetOK ;
                }

                CondRetGRA = GRA_ObterSucessor ( pGrafo , idOrigem , &idTemp ) ;
                if ( CondRetGRA == GRA_CondRetNaoHaSucessores )
                {
                        return MOV_CondRetMovimentoInvalido ;
                }
        }while ( idTemp != idPrimeiro );

        return MOV_CondRetMovimentoInvalido;


}/* Fim da Fun��o: MOV &Mover Pe�a */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: MOV -Adiciona Pr�ximas Pe�as ( Movimenta��o Discreta )
*
*  $ED Descri��o da fun��o
*     Adiciona no grafo as pe�as alcan�adas pela pe�a atual por um movimento
*	  discreto.
*
*  $EP Par�metros
*     pPeca - refer�ncia para a pe�a de origem
*	  pGrafo - grafo que cont�m a pe�a
*	  Movimento - string que determina a movimenta��o da pe�a
*	  ColunaCorrente - letra da coluna onde est� a pe�a
*	  LinhaCorrente - n�mero da linha onde est� a pe�a
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as pe�as sem problemas
*	  MOV_CondRetErroNaStringDeMovimento - string de movimenta��o com sintaxe incorreta
*	  MOV_CondRetPosicaoInvalida - pe�a referida pela string de movimento est� numa posi��o inv�lida
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir a pe�a
*
***********************************************************************/
MOV_tpCondRet AdicionaProximosDiscretos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente ){

	/* Declara��o e Inicializa��o de Vari�veis Locais */
	int NumCasasNaVertical		= 0;
	int NumCasasNaHorizontal	= 0;
	char TipoDaCasa				= '!';
	int LinhaDoProximo			= -1;
	char ColunaDoProximo		= '@';
	MOV_tpCondRet CondRetREC	= MOV_CondRetOK ;
	GER_tpCorPeca CorDaPeca		= GER_CorSemCor ;

	/* Obt�m os dados a partir da regra */
	if ( sscanf ( Movimento , "%*c %c %d %d" , 
				&TipoDaCasa , &NumCasasNaVertical , &NumCasasNaHorizontal )
				!= 3)
	{
		return MOV_CondRetErroNaStringDeMovimento;
	}

	CorDaPeca = GER_ObterCor ( pPeca ) ;
	if ( CorDaPeca == GER_CorBranca )
	{
		NumCasasNaVertical = NumCasasNaVertical * (-1) ;
		NumCasasNaHorizontal = NumCasasNaHorizontal * (-1) ;
	}

	LinhaDoProximo = LinhaCorrente + NumCasasNaVertical ;
	ColunaDoProximo = ( char )( ColunaCorrente + NumCasasNaHorizontal ) ;

	CondRetREC = AdicionaProximo ( pGrafo , (char)ColunaCorrente , LinhaCorrente , (char)ColunaDoProximo , LinhaDoProximo, (char)TipoDaCasa, CorDaPeca );
	if (CondRetREC == MOV_CondRetChegouEmPeca )
	{
		return MOV_CondRetOK ;
	}
	return CondRetREC;
}/* Fim da Fun��o: MOV -Adiciona Pr�ximas Pe�as ( Movimenta��o Discreta ) */

/***********************************************************************
*
*  $FC Fun��o: MOV -Adiciona Pr�ximas Pe�as ( Movimenta��o Cont�nua )
*
*  $ED Descri��o da fun��o
*     Adiciona no grafo as pe�as alcan�adas pela pe�a atual por um movimento
*	  cont�nuo.
*
*  $EP Par�metros
*     pPeca - refer�ncia para a pe�a de origem
*	  pGrafo - grafo que cont�m a pe�a
*	  Movimento - string que determina a movimenta��o da pe�a
*	  ColunaCorrente - letra da coluna onde est� a pe�a
*	  LinhaCorrente - n�mero da linha onde est� a pe�a
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as pe�as sem problemas
*	  MOV_CondRetErroNaStringDeMovimento - string de movimenta��o com sintaxe incorreta
*	  MOV_CondRetPosicaoInvalida - pe�a referida pela string de movimento est� numa posi��o inv�lida
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir a pe�a
*
***********************************************************************/
MOV_tpCondRet AdicionaProximosContinuos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento, char ColunaCorrente, int LinhaCorrente ){
	
	/* Declara e inicializa vari�veis */
	char Direcao[2]				= "";
	int NumMaxDeCasas			= 0;
	int CoefHorizontal			= 0;
	int CoefVertical			= 0;
	int Fator					= 0;
	MOV_tpCondRet CondRetREC	= MOV_CondRetOK;
	int LinhaDoProximo			= -1;
	char ColunaDoProximo		='@';
	char MaxCasas				= '#';
	GER_tpCorPeca CorDaPeca		= GER_CorSemCor ;

	/* Obt�m os dados a partir da regra */
	if ( sscanf ( Movimento , "%*c %s %c",
				&Direcao , &MaxCasas )
				!= 2 )
	{
		return MOV_CondRetErroNaStringDeMovimento;
	}

	/* Verifica as dire��es poss�veis */
	switch ( Direcao[0] ){
		case 'N': CoefVertical = 1; break;
		case 'S': CoefVertical = -1; break;
		case 'E': CoefVertical = 0; break;
		case 'W': CoefVertical = 0; break;
		default: return MOV_CondRetErroNaStringDeMovimento ;
	}

	switch ( Direcao[1] ){
		case 'N': CoefHorizontal = 0; break;
		case 'S': CoefHorizontal = 0; break;
		case 'E': CoefHorizontal = 1; break;
		case 'W': CoefHorizontal = -1; break;
		default: return MOV_CondRetErroNaStringDeMovimento ;
	}

	/* Verifica o n�mero de casas m�ximos */
	if ( MaxCasas == 'N' )
	{
		NumMaxDeCasas = GER_ObterUltimaLinhaTabuleiro();
	}
	else if ( ( MaxCasas > '9' )||
		      ( MaxCasas < '0' ) )
	{
		return MOV_CondRetErroNaStringDeMovimento;
	}
	else
	{
		NumMaxDeCasas = ( int )( MaxCasas - '0' );
	}


	/* Ajusta coeficiente para pe�as brancas */
	CorDaPeca = GER_ObterCor ( pPeca );
	if ( CorDaPeca == GER_CorBranca )
	{
		CoefHorizontal = CoefHorizontal * (-1);
		CoefVertical = CoefVertical * (-1);
	}

	/* Adiciona as casas poss�veis na dire��o dada */
	for ( Fator = 1 ; Fator <=NumMaxDeCasas ; Fator++ )
	{
		LinhaDoProximo = LinhaCorrente + Fator * CoefVertical;
		ColunaDoProximo = ( char )( ColunaCorrente + Fator * CoefHorizontal );

		CondRetREC = AdicionaProximo ( pGrafo, ColunaCorrente , LinhaCorrente, ColunaDoProximo, LinhaDoProximo, '?', CorDaPeca );
		if ( CondRetREC != MOV_CondRetOK )
		{
			break;
		}
	}

	return MOV_CondRetOK;
}

/***********************************************************************
*
*  $FC Fun��o: MOV -Adiciona Pr�xima Pe�a ( Gen�rica )
*
*  $ED Descri��o da fun��o
*     Adiciona no grafo uma pe�a como pr�xima de uma outra
*
*  $EP Par�metros
*	  pGrafo - grafo que cont�m a pe�a
*	  ColunaCorrente - coluna da pe�a de origem
*	  LinhaCorrente - linha da pe�a de origem
*	  ColunaProximo - coluna da pe�a de destino
*	  LinhaPr�ximo - linha da pe�a de destino
*	  TipoDaCasa - tipo da casa de destino ( se cheia, vazia ou n�o importa )
*	  CorPecaCorrente - cor da pe�a de origem
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as pe�as sem problemas
*	  MOV_CondRetErroNaStringDeMovimento - string de movimenta��o com sintaxe incorreta
*	  MOV_CondRetPosicaoInvalida - pe�a referida pela string de movimento est� numa posi��o inv�lida
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir a pe�a
*	  MOV_CondRetChegouEmPeca - sucessor contem pe�a
*
***********************************************************************/
MOV_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo, char ColunaCorrente, int LinhaCorrente , char ColunaProximo, int LinhaProximo, char TipoDaCasa, GER_tpCorPeca CorPecaCorrente ){

	/* Declara e inicializa vari�veis locais */
	int IdCorrente				= -1;
	int IdProximo				= -1;
	GRA_tpCondRet CondRetGRA	= GRA_CondRetOK;
	GER_tpCondRet CondRetGER	= GER_CondRetOK ;
	GER_tppPeca pPeca			= NULL;
	GER_tpTipoPeca TipoDaPeca	= GER_TipoVazia;	
	GER_tpCorPeca CorDaProxPeca	= GER_CorSemCor ;

	/* Verifica se a posi��o das pe�as � v�lida */
	if (( LinhaCorrente < 1 )||
		( LinhaProximo < 1 )||
		( LinhaCorrente > GER_ObterUltimaLinhaTabuleiro() )||
		( LinhaProximo > GER_ObterUltimaLinhaTabuleiro() )||
		( ColunaCorrente < 'A' )||
		( ColunaProximo < 'A' )||
		( ColunaCorrente > GER_ObterUltimaColunaTabuleiro() )||
		( ColunaProximo > GER_ObterUltimaColunaTabuleiro() ) )
	{
		return MOV_CondRetPosicaoInvalida;
	}

	/* Obt�m o sucessor */
	CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , ColunaProximo , LinhaProximo );
	if ( CondRetGER != GER_CondRetOK )
	{
		return MOV_CondRetPosicaoInvalida ;
	} 

	/* Obt�m o tipo do sucessor e verifica se � v�lido */
	TipoDaPeca = GER_ObterTipo ( pPeca );
	if (( TipoDaPeca == GER_TipoVazia )&&
		( TipoDaCasa == 'C' ))
	{
		return MOV_CondRetPosicaoInvalida;
	}
	else if (( TipoDaPeca != GER_TipoVazia)&&
			( TipoDaCasa == 'V'))
	{
		return MOV_CondRetPosicaoInvalida;
	}

	/* Obt�m a cor do sucessor */
	CorDaProxPeca = GER_ObterCor ( pPeca );
	if ( CorPecaCorrente == CorDaProxPeca )
	{
		return MOV_CondRetPosicaoInvalida ;
	}

	/* Gera os identificadores para as pe�as */
	IdCorrente = CodificaPosicao ( (char)ColunaCorrente , LinhaCorrente );
	IdProximo = CodificaPosicao ( (char)ColunaProximo , LinhaProximo );

	/* Insere a aresta entre as pe�as */
	CondRetGRA = GRA_InserirAresta ( pGrafo , IdCorrente , IdProximo );
	if ( CondRetGRA != GRA_CondRetOK )
	{
		return MOV_CondRetNaoAdicionouProx;
	}

	if ( TipoDaPeca != GER_TipoVazia )
	{
		return MOV_CondRetChegouEmPeca ;
	}

	return MOV_CondRetOK;
} /* Fim da Fun��o: MOV -Adiciona Pr�xima Pe�a ( Gen�rica ) */

/***********************************************************************
*
*  $FC Fun��o: MOV -Codifica Posi��o
*
*  $ED Descri��o da fun��o
*     A partir da posi��o da pe�a no tabuleiro, gera um identificador para a pe�a
*
*  $EP Par�metros
*	  Coluna - letra da coluna da pe�a no tabuleiro
*	  Linha - n�mero da linha da pe�a no tabuleiro
*
*  $FV Valor retornado
*     Retorna um identificador �nico para a pe�a no grafo.
*
***********************************************************************/
int CodificaPosicao ( char Coluna , int Linha ){
	
	int NumeroDaLinha = Linha -1;
	int NumeroDaColuna = ( int )( Coluna - 'A' )+1;
	int NumeroDeColunas = ( int )( GER_ObterUltimaColunaTabuleiro ( ) - 'A' + 1)  ;

	return ( ( NumeroDaLinha * NumeroDeColunas ) + NumeroDaColuna );
} /* Fim da Fun��o: MOV Codifica Posi��o */

 /***********************************************************************
*
*  $FC Fun��o: Reconhece Xeque
*
*  $ED Descri��o da fun��o
*     V� se o Rei est� em xeque.
*
*  $EP Par�metros
*     $P cCor - cor do Rei.
*     $P pGrafo - ponteiro para o Grafo montado a partir do tabuleiro.
*
*  $FV Valor retornado
*     Retorna VERDADEIRO se o rei estiver em Xeque
*	  ou FALSO se o rei n�o estiver em Xeque.
*		
*		Em caso de cCor inv�lida ou pGrafo inexistente, retorna FALSO. 
*
***********************************************************************/

int ReconheceXeque ( char cCor, GRA_tppGrafo pGrafo){
	
	char Coluna;
	int Linha;
	int IdAntecessor;
	
	int IdPrimeiroAntecessor;
	int IdRei;
	
	GER_tpCondRet CondRetGerenciador;
	GRA_tpCondRet CondRetGrafo;

	GER_tppPeca pPeca;
	GER_tpCorPeca CorAntecessor;
	GER_tpCorPeca CorRei = GER_ObterCodigoDaCor ( cCor );


	if ( CorRei == GER_CorSemCor || pGrafo == NULL){	
		return FALSO;
	} /* if */

	CondRetGerenciador = GER_ObterRei ( CorRei, &Coluna, &Linha );

	if ( CondRetGerenciador == GER_CondRetPecaNaoExiste){
		return FALSO;
	} /* if */

	IdRei = CodificaPosicao ( Coluna , Linha );

	CondRetGrafo = GRA_ObterAntecessor ( pGrafo, IdRei, &IdAntecessor );

	if ( CondRetGrafo == GRA_CondRetNaoHaAntecessores || CondRetGrafo == GRA_CondRetIndiceInvalido ){
		return FALSO;
	}/* if */

	IdPrimeiroAntecessor = IdAntecessor;	
	
	do{
		
		CondRetGrafo = GRA_ObterValorComId ( pGrafo, IdAntecessor, &pPeca);

		if ( CondRetGrafo == GRA_CondRetIndiceInvalido || CondRetGrafo == GRA_CondRetGrafoInexistente ){
			return FALSO;
		} /* if */
		
		CorAntecessor = GER_ObterCor( pPeca );

		if ( CorAntecessor == GER_CorSemCor ){
			return FALSO;
		} /* if */

		if ( CorAntecessor != CorRei ){ /* O REI EST� EM XEQUE */

			return VERDADEIRO;

		} /* if */
		
		CondRetGrafo = GRA_ObterAntecessor ( pGrafo, IdRei, &IdAntecessor );


		if ( CondRetGrafo == GRA_CondRetNaoHaAntecessores || CondRetGrafo == GRA_CondRetIndiceInvalido ){
			return FALSO;
		} /* if */

	}while ( IdAntecessor != IdPrimeiroAntecessor);
	
	return FALSO;

}
