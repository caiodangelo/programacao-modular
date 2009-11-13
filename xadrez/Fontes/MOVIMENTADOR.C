/***************************************************************************
*  $MCI Módulo de implementação: MOV Movimentador de peças de Xadrez
*
*  Arquivo gerado:              MOVIMENTADOR.C
*  Letras identificadoras:      MOV
*
*  Projeto: INF 1301 Programação Modular
*  Gestor:  DI/PUC-Rio
*  Autores: cev - Caio D'Angelo , Eduardo Velloso e Vitor Barbarisi
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     0       cev   12/set/2009 Início desenvolvimento
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

/***** Protótipos das funções encapsuladas no módulo *****/

int CodificaPosicao ( char Coluna , int Linha );

MOV_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo,  char ColunaCorrente, int LinhaCorrente ,  char ColunaProximo, int LinhaProximo,char TipoDaCasa, GER_tpCorPeca p );

MOV_tpCondRet AdicionaProximosDiscretos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente );

MOV_tpCondRet AdicionaProximosContinuos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimentos, char Coluna, int Linha );

int ReconheceXeque ( char cCor, GRA_tppGrafo pGrafo);

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: MOV  &Adicionar Pecas Ao Grafo
*  ****/

MOV_tpCondRet MOV_AdicionarPecasAoGrafo ( GRA_tppGrafo * ppGrafo ){
	
	/* Declaração das variáveis locais */
	int linha;
	int coluna;
	GER_tpCondRet CondRetGER;
	GRA_tpCondRet CondRetGRA;
	GER_tppPeca pPeca;
	int id;
	printf("Entrou na Adicionar Pecas ao Grafo \n");

	/* Cria o grafo */
	CondRetGRA = GRA_CriarGrafo ( ppGrafo );
	printf("Passou pela GRA_CriarGrafo \n");
	if ( CondRetGRA != GRA_CondRetOK ){
		return MOV_CondRetNaoCriouGrafo;
	}
	printf("Criou o grafo dentro da Adicionar Pecas ao Grafo \n");

	/* Percorre o tabuleiro */
	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){
			
			/* Obtém a peça do tabuleiro */
			CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if ( CondRetGER != GER_CondRetOK ){
				return MOV_CondRetNaoCriouVertice;
			}

			/* Gera o identificador da peça */
			id = CodificaPosicao ( (char)coluna , linha );
			
			/* Insere a peça no grafo com o id gerado */
			CondRetGRA = GRA_InserirVertice ( *ppGrafo , pPeca , id );

			if ( CondRetGRA != GRA_CondRetOK ){

				return MOV_CondRetNaoInseriuPeca;
			}
		}
	}

	return MOV_CondRetOK ;
} /* Fim da Função: MOV  &Adicionar Pecas Ao Grafo */

/***************************************************************************
*
*  Função: MOV  &Gera Movimentações
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

	/* Verifica se o grafo está criado */
	if ( pGrafo == NULL )
	{
		return MOV_CondRetNaoCriouGrafo ;
	}

	/* Percorre todas as peças do tabuleiro */
	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){

			/* Obtém a peça do tabuleiro */
			CondRetGer = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha );
			if (CondRetGer != GER_CondRetOK )
			{
				return MOV_CondRetPosicaoInvalida ;
			}

			/* Obtém o tipo da peça */
			TipoPeca = GER_ObterTipo ( pPeca );
			if ( TipoPeca == -1 )
			{
				return MOV_CondRetPosicaoInvalida;
			}

			/* Abre o arquivo de regras de movimentação discreta para leitura */
			ArquivoDeRegras = fopen ( REGRASD , "r" );
			if ( ArquivoDeRegras == NULL )
			{
				return MOV_CondRetArquivoNaoExiste ;
			}

			/* Busca no arquivo as regras correspondentes àquele tipo */
			while ( fgets ( movimentos , TAM_MOVIMENTO , ArquivoDeRegras ) )
			{
				/* Se a regra corresponder ao tipo, adicionar as peças correspondentes */
				if ( TipoPeca == GER_ObterCodigoDoTipo (  movimentos[INX_TIPO] ) )
				{
					AdicionaProximosDiscretos ( pPeca , pGrafo , movimentos, (char)coluna, linha );					
				}
			}

			/* Fecha o arquivo de regras de movimentação discreta */
			fclose( ArquivoDeRegras );

			/* Abre o arquivo de regras de movimentação contínua para leitura */
			ArquivoDeRegras = fopen ( REGRASC , "r" );
			if ( ArquivoDeRegras == NULL )
			{
				return MOV_CondRetArquivoNaoExiste ;
			}

			/* Busca no arquivo as regras correspondentes àquele tipo */
			while ( fgets ( movimentos , TAM_MOVIMENTO , ArquivoDeRegras ) )
			{
				/* Se a regra corresponder ao tipo, adicionar as peças correspondentes */
				if ( TipoPeca == GER_ObterCodigoDoTipo (  movimentos[INX_TIPO] ) )
				{
					AdicionaProximosContinuos ( pPeca , pGrafo , movimentos, (char)coluna, linha );					
				}
			}

			/* Fecha o arquivo de regras de movimentação contínua */
			fclose( ArquivoDeRegras );

		}
	}

	*ppGrafo = pGrafo;
	return MOV_CondRetOK;
} /* Fim da Função: MOV  &Gera Movimentações */

/***************************************************************************
*
*  Função: MOV  &Reconhecer Xeque Mate
*  ****/
MOV_tpCondRet MOV_ReconhecerXequeMate ( char cCor , GRA_tppGrafo pGrafo ){

        int linha, idAtual, idSucessor, primeiroSucessor;
        char coluna;
        GER_tpCondRet CondRetGerenciador;
        GER_tppPeca pPeca;
        GER_tppPeca pPecaOrigem, pPecaDestino;
        GER_tpCorPeca corPeca, cor;
        GRA_tpCondRet CondRetGrafo;
        GRA_tppGrafo pGrafoLocal = NULL;
        MOV_tpCondRet CondRetMovimentador;

        GER_tpTipoPeca tipoPeca;

        cor = GER_ObterCodigoDaCor ( cCor );

        /* Verifica se o Rei está em xeque */
        if((ReconheceXeque( cCor , pGrafo )) == FALSO)
        {
                return MOV_CondRetNaoEstaEmXequeMate;
        }


        /* Percorre o tabuleiro */
        for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ ){
                for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; (char)(coluna++) ){

                        /* Obém peça do tabuleiro */
                        CondRetGerenciador = GER_ObterPecaDoTabuleiro ( &pPeca, coluna, linha );

                        if(CondRetGerenciador != GER_CondRetOK ){
                                /* tratar erro */

                        }
                       
                        /* Obtém cor da peça */
                        corPeca = GER_ObterCor ( pPeca ) ;
                        tipoPeca = GER_ObterTipo ( pPeca ) ;
                        printf("Tipo da peca: %d - Cor: %d \n",tipoPeca,corPeca);

                        /* Verifica se cor obtida é igual à cor do Rei */
                        if( corPeca == cor ){

                                /* Codifica posição da peça */
                                idAtual = CodificaPosicao ( coluna , linha );
                                printf("Id da peca: %d \n",idAtual);

                                /* Procura a peça no grafo */
                                CondRetGrafo = GRA_IrVerticeComId( pGrafo , idAtual);

                                if( CondRetGrafo != GRA_CondRetOK ){
                                        /* tratar erro */
                                        printf("ERRO \n");

                                }

                                /* Obtém primeiro sucessor = */
                                CondRetGrafo = GRA_ObterSucessor ( pGrafo , idAtual ,
                                                                          &primeiroSucessor );

                                if( CondRetGrafo == GRA_CondRetNaoHaSucessores){
                                        /* Peça não tem movimentos possíveis */

                                }
                                else{

                                        /*  */
                                        idSucessor = primeiroSucessor;

                                        do{

                                                printf("idSucessor ao entrar no loop: %d \n",idSucessor);

                                                /* Obtém valor da peça */
                                                CondRetGrafo = GRA_ObterValorComId( pGrafo , idAtual , &pPecaOrigem );
                                                CondRetGrafo = GRA_ObterValorComId( pGrafo , idSucessor , &pPecaDestino );
                                                printf("Obteve pecas corretamente \n");

                                                /* Gera movimentação */
                                                CondRetGerenciador = GER_MoverPeca ( pPecaOrigem , pPecaDestino );
                                                printf("Gerou movimentacao virtual \n");

                                                /* Cria o grafo à partir do tabuleiro */
                                                CondRetMovimentador = MOV_AdicionarPecasAoGrafo ( &pGrafoLocal );                                              
                                                printf("Criou o grafo local\n");
                                                CondRetMovimentador = MOV_GeraMovimentacoes ( &pGrafoLocal );
                                                printf("Gerou movimentacoes possiveis \n");

                                                /* Verifica se o rei continua em xeque */
                                                if((ReconheceXeque( cCor , pGrafoLocal )) == FALSO)
                                                {
                                                        return MOV_CondRetNaoEstaEmXequeMate;
                                                }

                                                /* Destruir o grafo criado */
                                                CondRetGrafo = GRA_DestruirGrafo( &pGrafoLocal );
                                                //printf("Destruiu o grafo local\n");
                                                pGrafoLocal = NULL;//hack enquanto a destruir grafo não funciona

                                                /* Desfaz movimentação */
                                                CondRetGerenciador = GER_MoverPeca ( pPecaDestino , pPecaOrigem );

                                                /* Obtém o próximo Sucessor */
                                                CondRetGrafo = GRA_ObterSucessor ( pGrafo , idAtual ,
                                                                          &idSucessor );
                                                printf("idSucessor ao sair do loop: %d \n",idSucessor);

                                        }
                                        while( idSucessor != primeiroSucessor );/* do while */
                                }/* else */
                        }/* if */                      
                }/* for */
        }/* for */

        return MOV_CondRetXequeMate;

}/* Fim da função Recohecer Xeque Mate */
/***************************************************************************
*
*  Função: MOV  &Mover Peça
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


}/* Fim da Função: MOV &Mover Peça */

/***************************************************************************
*
*  Função: MOV  &Jogar xadrez
*  ****/

MOV_tpCondRet MOV_JogarXadrez ( void ){
	
	GER_tpCorPeca CorDaVez = GER_CorBranca ;
	int continua = 1;
	int ErroNaJogada = 0 ;
	char ColunaOrigem = '!' ;
	char ColunaDestino = '@' ;
	int LinhaOrigem = -1 ;
	int LinhaDestino = -2 ;
	MOV_tpCondRet CondRet = MOV_CondRetOK ;
	int NumLidos = -1 ;
	GRA_tppGrafo pGrafo = NULL ;

	CondRet = MOV_AdicionarPecasAoGrafo ( &pGrafo ) ;
	if( CondRet != MOV_CondRetOK )
	{
		return CondRet ;
	}

	CondRet = MOV_GeraMovimentacoes ( &pGrafo ) ;
	if( CondRet != MOV_CondRetOK )
	{
		return CondRet ;
	}

	while( continua )
	{
		if ( CorDaVez == GER_CorBranca )
		{
			printf("Vez do jogador BRANCO. Entre com a jogada:\n");
		}
		else
		{
			printf("Vez do jogador PRETO. Entre com a jogada:\n");
		}
		do
		{
			ErroNaJogada = 0 ;
			NumLidos = scanf("%c%i %c%i" , &ColunaOrigem , &LinhaOrigem , &ColunaDestino , &LinhaDestino ) ;
			if ( NumLidos != 4 )
			{
				if ( ( NumLidos == 1 ) && ( ColunaOrigem == 'S' ) )
				{
					printf("Obrigado por SE DIVERTIR!!!");
					return MOV_CondRetOK ;
				}
				ErroNaJogada = 1 ;
				printf("erro na jogada: %d\n", NumLidos );
			}
	
			//CondRet = MOV_MoverPeca ( ColunaOrigem , LinhaOrigem , ColunaDestino , LinhaDestino , pGrafo ) ;
			//if( CondRet != MOV_CondRetOK )
			//{
			//	ErroNaJogada = 1 ;
			//}
			//else
			//{
				if ( CorDaVez == GER_CorBranca )
				{
					CorDaVez = GER_CorPreta ;
				}
				else
				{
					CorDaVez = GER_CorBranca ;
				}
			//}
				
		}while( ErroNaJogada );

	}
	
	return MOV_CondRetOK;
}/* Fim da Função: MOV &Jogar xadrez */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: MOV -Adiciona Próximas Peças ( Movimentação Discreta )
*
*  $ED Descrição da função
*     Adiciona no grafo as peças alcançadas pela peça atual por um movimento
*	  discreto.
*
*  $EP Parâmetros
*     pPeca - referência para a peça de origem
*	  pGrafo - grafo que contém a peça
*	  Movimento - string que determina a movimentação da peça
*	  ColunaCorrente - letra da coluna onde está a peça
*	  LinhaCorrente - número da linha onde está a peça
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as peças sem problemas
*	  MOV_CondRetErroNaStringDeMovimento - string de movimentação com sintaxe incorreta
*	  MOV_CondRetPosicaoInvalida - peça referida pela string de movimento está numa posição inválida
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir a peça
*
***********************************************************************/
MOV_tpCondRet AdicionaProximosDiscretos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento , char ColunaCorrente , int LinhaCorrente ){

	/* Declaração e Inicialização de Variáveis Locais */
	int NumCasasNaVertical		= 0;
	int NumCasasNaHorizontal	= 0;
	char TipoDaCasa				= '!';
	int LinhaDoProximo			= -1;
	char ColunaDoProximo		= '@';
	MOV_tpCondRet CondRetREC	= MOV_CondRetOK ;
	GER_tpCorPeca CorDaPeca		= GER_CorSemCor ;

	/* Obtém os dados a partir da regra */
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
}/* Fim da Função: MOV -Adiciona Próximas Peças ( Movimentação Discreta ) */

/***********************************************************************
*
*  $FC Função: MOV -Adiciona Próximas Peças ( Movimentação Contínua )
*
*  $ED Descrição da função
*     Adiciona no grafo as peças alcançadas pela peça atual por um movimento
*	  contínuo.
*
*  $EP Parâmetros
*     pPeca - referência para a peça de origem
*	  pGrafo - grafo que contém a peça
*	  Movimento - string que determina a movimentação da peça
*	  ColunaCorrente - letra da coluna onde está a peça
*	  LinhaCorrente - número da linha onde está a peça
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as peças sem problemas
*	  MOV_CondRetErroNaStringDeMovimento - string de movimentação com sintaxe incorreta
*	  MOV_CondRetPosicaoInvalida - peça referida pela string de movimento está numa posição inválida
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir a peça
*
***********************************************************************/
MOV_tpCondRet AdicionaProximosContinuos ( GER_tppPeca pPeca , GRA_tppGrafo pGrafo , char * Movimento, char ColunaCorrente, int LinhaCorrente ){
	
	/* Declara e inicializa variáveis */
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

	/* Obtém os dados a partir da regra */
	if ( sscanf ( Movimento , "%*c %s %c",
				&Direcao , &MaxCasas )
				!= 2 )
	{
		return MOV_CondRetErroNaStringDeMovimento;
	}

	/* Verifica as direções possíveis */
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

	/* Verifica o número de casas máximos */
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


	/* Ajusta coeficiente para peças brancas */
	CorDaPeca = GER_ObterCor ( pPeca );
	if ( CorDaPeca == GER_CorBranca )
	{
		CoefHorizontal = CoefHorizontal * (-1);
		CoefVertical = CoefVertical * (-1);
	}

	/* Adiciona as casas possíveis na direção dada */
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
*  $FC Função: MOV -Adiciona Próxima Peça ( Genérica )
*
*  $ED Descrição da função
*     Adiciona no grafo uma peça como próxima de uma outra
*
*  $EP Parâmetros
*	  pGrafo - grafo que contém a peça
*	  ColunaCorrente - coluna da peça de origem
*	  LinhaCorrente - linha da peça de origem
*	  ColunaProximo - coluna da peça de destino
*	  LinhaPróximo - linha da peça de destino
*	  TipoDaCasa - tipo da casa de destino ( se cheia, vazia ou não importa )
*	  CorPecaCorrente - cor da peça de origem
*
*  $FV Valor retornado
*     MOV_CondRetOK - adicionou as peças sem problemas
*	  MOV_CondRetErroNaStringDeMovimento - string de movimentação com sintaxe incorreta
*	  MOV_CondRetPosicaoInvalida - peça referida pela string de movimento está numa posição inválida
*	  MOV_CondRetNaoInseriuPeca - erro ao inserir a peça
*	  MOV_CondRetChegouEmPeca - sucessor contem peça
*
***********************************************************************/
MOV_tpCondRet AdicionaProximo ( GRA_tppGrafo pGrafo, char ColunaCorrente, int LinhaCorrente , char ColunaProximo, int LinhaProximo, char TipoDaCasa, GER_tpCorPeca CorPecaCorrente ){

	/* Declara e inicializa variáveis locais */
	int IdCorrente				= -1;
	int IdProximo				= -1;
	GRA_tpCondRet CondRetGRA	= GRA_CondRetOK;
	GER_tpCondRet CondRetGER	= GER_CondRetOK ;
	GER_tppPeca pPeca			= NULL;
	GER_tpTipoPeca TipoDaPeca	= GER_TipoVazia;	
	GER_tpCorPeca CorDaProxPeca	= GER_CorSemCor ;

	/* Verifica se a posição das peças é válida */
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

	/* Obtém o sucessor */
	CondRetGER = GER_ObterPecaDoTabuleiro ( &pPeca , ColunaProximo , LinhaProximo );
	if ( CondRetGER != GER_CondRetOK )
	{
		return MOV_CondRetPosicaoInvalida ;
	} 

	/* Obtém o tipo do sucessor e verifica se é válido */
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

	/* Obtém a cor do sucessor */
	CorDaProxPeca = GER_ObterCor ( pPeca );
	if ( CorPecaCorrente == CorDaProxPeca )
	{
		return MOV_CondRetPosicaoInvalida ;
	}

	/* Gera os identificadores para as peças */
	IdCorrente = CodificaPosicao ( (char)ColunaCorrente , LinhaCorrente );
	IdProximo = CodificaPosicao ( (char)ColunaProximo , LinhaProximo );

	/* Insere a aresta entre as peças */
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
} /* Fim da Função: MOV -Adiciona Próxima Peça ( Genérica ) */

/***********************************************************************
*
*  $FC Função: MOV -Codifica Posição
*
*  $ED Descrição da função
*     A partir da posição da peça no tabuleiro, gera um identificador para a peça
*
*  $EP Parâmetros
*	  Coluna - letra da coluna da peça no tabuleiro
*	  Linha - número da linha da peça no tabuleiro
*
*  $FV Valor retornado
*     Retorna um identificador único para a peça no grafo.
*
***********************************************************************/
int CodificaPosicao ( char Coluna , int Linha ){
	
	int NumeroDaLinha = Linha -1;
	int NumeroDaColuna = ( int )( Coluna - 'A' )+1;
	int NumeroDeColunas = ( int )( GER_ObterUltimaColunaTabuleiro ( ) - 'A' + 1)  ;

	return ( ( NumeroDaLinha * NumeroDeColunas ) + NumeroDaColuna );
} /* Fim da Função: MOV Codifica Posição */

 /***********************************************************************
*
*  $FC Função: Reconhece Xeque
*
*  $ED Descrição da função
*     Vê se o Rei está em xeque.
*
*  $EP Parâmetros
*     $P cCor - cor do Rei.
*     $P pGrafo - ponteiro para o Grafo montado a partir do tabuleiro.
*
*  $FV Valor retornado
*     Retorna VERDADEIRO se o rei estiver em Xeque
*	  ou FALSO se o rei não estiver em Xeque.
*		
*		Em caso de cCor inválida ou pGrafo inexistente, retorna FALSO. 
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

		if ( CorAntecessor != CorRei ){ /* O REI ESTÁ EM XEQUE */

			return VERDADEIRO;

		} /* if */
		
		CondRetGrafo = GRA_ObterAntecessor ( pGrafo, IdRei, &IdAntecessor );


		if ( CondRetGrafo == GRA_CondRetNaoHaAntecessores || CondRetGrafo == GRA_CondRetIndiceInvalido ){
			return FALSO;
		} /* if */

	}while ( IdAntecessor != IdPrimeiroAntecessor);
	
	return FALSO;

}
