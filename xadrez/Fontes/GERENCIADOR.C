/***************************************************************************
*  $MCI M�dulo de implementa��o: GER Gerenciador de Xadrez
*
*  Arquivo gerado:              GERENCIADOR.C
*  Letras identificadoras:      GER
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
#include "VERTICE.H"
#include <stdlib.h>
#include <stdio.h>

#define N_LINHAS 8
#define N_COLUNAS 8
#define TAM_DISPOSICAO 10
#define INX_TIPO 0
#define INX_COR 2
#define INX_LINHA 6
#define INX_COLUNA 4
#define N_TIPOS 7
#define N_CORES 3

/***********************************************************************
*
*  $TC Tipo de dados: GER Pe�a do Tabuleiro
*
*
***********************************************************************/

typedef struct GER_tgPeca{

	GER_tpTipoPeca Tipo;
		/* tipo da peca */

	GER_tpCorPeca Cor;
		/* cor da peca */

}GER_tpPeca;

/*****  Dados encapsulados no m�dulo  *****/

GER_tppPeca Tabuleiro[N_LINHAS][N_COLUNAS];
	/* Tabuleiro de Pe�as */

GER_tpCorPeca CorDaVez = GER_CorBranca ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/


GER_tpPeca * ObtemPeca ( char * disposicao );

GER_tpCondRet ValidaLinha ( char * disposicao );

GER_tpTipoPeca ObtemCodigoDoTipo ( char Tipo );

GER_tpCorPeca ObtemCodigoDaCor ( char Cor );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***************************************************************************
*
*  Fun��o: GER  &Criar Pe�a
*  ****/
GER_tppPeca GER_CriarPeca ( GER_tpTipoPeca tipo , GER_tpCorPeca cor  ){
	
	/* Aloca mem�ria para a pe�a */
	GER_tpPeca * pPeca = ( GER_tpPeca * ) malloc ( sizeof ( GER_tpPeca ) );
	
	/* Verifica aloca��o */
	if ( pPeca == NULL ){
		return NULL;
	} /* if */
	
	/* Verifica se o tipo � v�lido */
	if( ( tipo < 0 ) ||
		( tipo >= N_TIPOS ) )
	{
		return NULL;
	} /* if */

	/* Verifica se a cor � v�lida */
	if( ( cor < 0 ) ||
		( cor >= N_CORES ) )
	{
		return NULL;
	} /* if */
	
	/* Verifica se o tipo e a cor s�o coerentes */
	if ( ( cor == GER_CorSemCor )&&
		 ( tipo != GER_TipoVazia ) )
	{
		return NULL ;
	} /* if */
	if ( ( cor != GER_CorSemCor )&&
		 ( tipo == GER_TipoVazia ) )
	{
		return NULL ;
	} /* if */

	/* Faz as atribui��es */
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;

	return pPeca;
}/* Fim fun��o: GER  &Criar Pe�a */

/***************************************************************************
*
*  Fun��o: GER  &Destruir Pe�a
*  ****/
void GER_DestruirPeca ( GER_tppPeca * ppPeca  ){
	
	if ( *ppPeca == NULL )
	{
		return ;
	}

	free( *ppPeca );

	*ppPeca = NULL ;

	return;
}/* Fim fun��o: GER  &Destruir Pe�a */

/***************************************************************************
*
*  Fun��o: GER  &Atribuir Pe�a
*  ****/
GER_tpCondRet GER_AtribuirPeca ( GER_tpPeca * pPeca , GER_tpTipoPeca tipo , GER_tpCorPeca cor ){
	
	/* Verifica se a pe�a existe */
	if ( pPeca == NULL ){
		return GER_CondRetPecaNaoExiste;
	} /* if */
	
	/* Verifica se o tipo � v�lido */
	if( ( tipo < 0 ) ||
		( tipo >= N_TIPOS ) )
	{
		return GER_CondRetTipoInvalido ;
	} /* if */

	/* Verifica se a cor � v�lida */
	if( ( cor < 0 ) ||
		( cor >= N_CORES ) )
	{
		return GER_CondRetCorInvalida ;
	} /* if */

		/* Verifica se o tipo e a cor s�o coerentes */
	if ( ( cor == GER_CorSemCor )&&
		 ( tipo != GER_TipoVazia ) )
	{
		return GER_CondRetCorInvalida ;
	} /* if */
	if ( ( cor != GER_CorSemCor )&&
		 ( tipo == GER_TipoVazia ) )
	{
		return GER_CondRetTipoInvalido ;
	} /* if */

	/* Faz as atribui��es */	
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;

	return GER_CondRetOK;
}/* Fim fun��o: GER  &Atribuir Pe�a */

/***************************************************************************
*
*  Fun��o: GER  &Inicializar Tabuleiro
*  ****/
GER_tpCondRet GER_InicializarTabuleiro ( void ){
	
	/* Inicializa vari�veis locais */
	int linha	= 0;
	int coluna	= 0;

	/* Preenche o tabuleiro com ponteiros para casas vazias */
	for ( linha = 0 ; linha < N_LINHAS ; linha++ ){
		for ( coluna = 0 ; coluna < N_COLUNAS ; coluna++){
			Tabuleiro[linha][coluna] = GER_CriarPeca( GER_TipoVazia , GER_CorSemCor );
			if ( Tabuleiro[linha][coluna] == NULL ){
				return GER_CondRetFaltouMemoria;
			} /* if */
		} /* for */
	} /* for */

	return GER_CondRetOK;
}/* Fim fun��o: GER  &Inicializar Tabuleiro */

/***************************************************************************
*
*  Fun��o: GER  &Limpar Tabuleiro
*  ****/
void GER_LimparTabuleiro ( void ){
	
	/* Inicializa vari�veis locais */
	int linha	= 0;
	int coluna	= 0;

	/* Preenche o tabuleiro com ponteiros para casas vazias */
	for ( linha = 0 ; linha < N_LINHAS ; linha++ ){
		for ( coluna = 0 ; coluna < N_COLUNAS ; coluna++){
			GER_DestruirPeca ( &Tabuleiro[linha][coluna] );
		} /* for */
	} /* for */

	return ;
}/* Fim fun��o: GER  &Limpar Tabuleiro */

/***************************************************************************
*
*  Fun��o: GER  &Preencher Tabuleiro
*  ****/
GER_tpCondRet GER_PreencherTabuleiro ( char * ArquivoDisposicao ){
	
	/* Inicializa vari�veis locais */
	FILE * arquivo			= NULL;
	GER_tpCondRet CondRet	= GER_CondRetOK;
	GER_tpPeca * pPeca		= NULL;
	GER_tpTipoPeca Tipo		= GER_TipoVazia;
	GER_tpCorPeca Cor		= GER_CorSemCor;
	char cCor = 'B';
	char disposicao[TAM_DISPOSICAO];

	/* Abre o arquivo e verifica se abriu corretamente */
	arquivo = fopen ( ArquivoDisposicao , "r" );
	if ( arquivo == NULL ){
		return GER_CondRetArqInexistente;
	} /* if */

	fgets ( disposicao , TAM_DISPOSICAO , arquivo ) ;
	sscanf ( disposicao , "%c" , &cCor ) ;
	if ( cCor == 'P' )
	{
		CorDaVez = GER_CorPreta ;
	}
	else
	{
		CorDaVez = GER_CorBranca ;
	}

	while ( fgets ( disposicao , TAM_DISPOSICAO , arquivo )){
		
		/* Verifica se a linha cont�m uma disposi��o v�lida */
		CondRet = ValidaLinha ( disposicao );
		if ( CondRet != GER_CondRetOK ){
			return CondRet;
		} /* if */

		/* Obt�m a casa correspondente � disposi��o */
		pPeca = ObtemPeca ( disposicao );
		if ( pPeca == NULL )
		{
			return GER_CondRetPecaNaoExiste ;
		} /* if */

		/* Obtem tipo e cor da pe�a */
		Tipo = GER_ObterCodigoDoTipo ( disposicao[INX_TIPO] );
		Cor = GER_ObterCodigoDaCor ( disposicao[INX_COR] );
		
		/* Faz a atribui��o */
		CondRet = GER_AtribuirPeca( pPeca, Tipo, Cor );
		if ( CondRet != GER_CondRetOK){
			return CondRet;
		} /* if */
	}

	/* Fecha o arquivo */
	fclose( arquivo );

	return GER_CondRetOK ;
}/* Fim fun��o: GER  &Preencher Tabuleiro */


/***************************************************************************
*
*  Fun��o: GER  &Obter Pe�a do Tabuleiro
*  ****/
GER_tpCondRet GER_ObterPecaDoTabuleiro ( GER_tppPeca * ppPeca, char coluna, int linha ){
	
	/* Inicializa vari�veis locais */
	int ixColuna	= (int) (coluna - 'A');
	int ixLinha		= linha - 1;

	/* Verifica se a linha � v�lida */
	if((ixLinha<0)||(ixLinha>=N_LINHAS)){
		return GER_CondRetPecaNaoExiste;
	} /* if */

	/* Verifica se a coluna � v�lida */
	else if((ixColuna<0)||(ixColuna>=N_COLUNAS)){
		return GER_CondRetPecaNaoExiste;
	} /* else if */

	/* Obt�m pe�a no tabuleiro */
	*ppPeca = Tabuleiro[ixLinha][ixColuna];

	return GER_CondRetOK;
}/* Fim fun��o: GER  &Obter Pe�a do Tabuleiro */

/***************************************************************************
*
*  Fun��o: GER  &Obter �ltima Linha do Tabuleiro
*  ****/
int GER_ObterUltimaLinhaTabuleiro ( void ){

	return N_LINHAS;

}/* Fim fun��o: GER  &Obter �ltima Linha do Tabuleiro */

/***************************************************************************
*
*  Fun��o: GER  &Obter �ltima Coluna do Tabuleiro
*  ****/
char GER_ObterUltimaColunaTabuleiro ( void ){

	return (char)('A' + N_COLUNAS - 1);

}/* Fim fun��o: GER  &Obter �ltima Coluna do Tabuleiro */

/***************************************************************************
*
*  Fun��o: GER  &Obter Tipo da Pe�a
*  ****/
GER_tpTipoPeca GER_ObterTipo ( GER_tppPeca pPeca ) {

	if ( pPeca == NULL )
	{
		return -1;
	}
	return pPeca->Tipo ;

}/* Fim fun��o: GER  &Obter Tipo da Pe�a */

/***************************************************************************
*
*  Fun��o: GER  &Obter Cor da Pe�a
*  ****/
GER_tpCorPeca GER_ObterCor ( GER_tppPeca pPeca ) {

	if ( pPeca == NULL )
	{
		return -1;
	}
	return pPeca->Cor ;

}/* Fim fun��o: GER  &Obter Cor da Pe�a */

/***************************************************************************
*
*  Fun��o: GER  &Obter C�digo do Tipo
*  ****/
GER_tpTipoPeca GER_ObterCodigoDoTipo ( char Tipo ){

	switch ( Tipo ){
		case 'P': return GER_TipoPeao;
		case 'T': return GER_TipoTorre;
		case 'C': return GER_TipoCavalo;
		case 'B': return GER_TipoBispo;
		case 'D': return GER_TipoDama;
		case 'R': return GER_TipoRei;
		default:  return GER_TipoVazia;
	} /* switch */

}/* Fim fun��o: GER  &Obter C�digo do Tipo */

/***************************************************************************
*
*  Fun��o: GER  &Obter C�digo da Cor
*  ****/
GER_tpCorPeca GER_ObterCodigoDaCor ( char Cor ){

	switch ( Cor ){
		case 'B': return GER_CorBranca;
		case 'P': return GER_CorPreta;
		default:  return GER_CorSemCor;
	} /* switch */

} /* Fim fun��o: GER  &Obter C�digo da Cor */

/***************************************************************************
*
*  Fun��o: GER  &Obter Rei
*  ****/
GER_tpCondRet GER_ObterRei ( GER_tpCorPeca Cor , char * pColuna , int * pLinha ){

	GER_tppPeca pPeca		= NULL ;
	int linha				= 0 ;
	int coluna				= 0 ;
	GER_tpCondRet CondRet	= GER_CondRetOK ;

	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ )
	{
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro () ; coluna++ )
		{
			CondRet = GER_ObterPecaDoTabuleiro ( &pPeca , (char)coluna , linha ) ;
			if ( CondRet != GER_CondRetOK )
			{
				return CondRet ;
			} /* if */

			if ( ( GER_ObterTipo ( pPeca ) == GER_TipoRei )&&
				 ( GER_ObterCor ( pPeca ) == Cor ) )
			{
				* pLinha = linha;
				* pColuna = (char)coluna;
				return GER_CondRetOK ;
			} /* if */
			} /* for */
		} /* for */

	return GER_CondRetPecaNaoExiste ;

} /* Fim fun��o: GER  &Obter Rei */

/***************************************************************************
*
*  Fun��o: GER  &Mover Peca
*  ****/
GER_tpCondRet GER_MoverPeca ( GER_tppPeca pPecaOrigem , GER_tppPeca pPecaDestino ) {
	
	GER_tpTipoPeca Tipo ;
	GER_tpCorPeca Cor ;
	GER_tpCondRet CondRet ;

	if (( pPecaOrigem == NULL )
		||( pPecaDestino == NULL ))
	{
		return GER_CondRetPecaNaoExiste ;
	}

	Tipo = GER_ObterTipo ( pPecaOrigem ) ;
	
	Cor = GER_ObterCor ( pPecaOrigem ) ;


	CondRet = GER_AtribuirPeca ( pPecaDestino , Tipo , Cor ) ;
	if ( CondRet != GER_CondRetOK )
	{
		return CondRet ;
	}

	CondRet = GER_AtribuirPeca ( pPecaOrigem , GER_TipoVazia , GER_CorSemCor ) ;
	if ( CondRet != GER_CondRetOK )
	{
		return CondRet ;
	}

	return GER_CondRetOK ;

} /* Fim fun��o: GER &Mover Peca */

/***************************************************************************
*
*  Fun��o: GER  &Alterar Cor da Vez
*  ****/

void GER_AlterarCorDaVez ( void ){

	CorDaVez = !CorDaVez ;

} /* Fim fun��o: GER &Alterar Cor da Vez */

/***************************************************************************
*
*  Fun��o: GER  &Obter Cor da Vez
*  ****/

GER_tpCorPeca GER_ObterCorDaVez ( void ){

	return CorDaVez ;

} /* Fim fun��o: GER &Obter Cor da Vez */

/***************************************************************************
*
*  Fun��o: GER  &Imprimir Tabuleiro
*  ****/
void GER_ImprimirTabuleiro ( void ) {

	char coluna				= 0 ;
	int linha				= 0 ;
	GER_tppPeca	pPeca		= NULL ;
	GER_tpCondRet CondRet	= GER_CondRetOK ;

	printf ( "\n----------------------------\n" ) ;
	printf ( "   | A| B| C| D| E| F| G| H|\n" ) ;
	printf ( "----------------------------\n" ) ;
	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro( ) ; linha++ ){
		printf( "|%d |",linha );
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro( ) ; (char)(coluna++)){
		
			CondRet = GER_ObterPecaDoTabuleiro ( &pPeca , coluna , linha ) ;
			if ( CondRet != GER_CondRetOK )
			{
				return ;
			}

			switch ( GER_ObterTipo ( pPeca ) )
			{
				case GER_TipoPeao:
					printf ( "P" );
					break;
				case GER_TipoTorre:
					printf ( "T" );
					break;
				case GER_TipoCavalo:
					printf ( "C" );
					break;
				case GER_TipoBispo:
					printf ( "B" );
					break;
				case GER_TipoDama:
					printf ( "D" );
					break;
				case GER_TipoRei:
					printf ( "R" );
					break;
				case GER_TipoVazia:
					printf ( " " );
					break;
				default:
					printf ( "&" );
					break;
			}

			switch ( GER_ObterCor ( pPeca ) )
			{
				case GER_CorBranca:
					printf ( "b|" );
					break;
				case GER_CorPreta:
					printf ( "p|" );
					break;
				case GER_CorSemCor:
					printf ( " |" );
					break;
				default:
					printf ( "&" );
					break;
			}		
		}
		printf( "\n----------------------------\n" ) ;
	}

} /* Fim fun��o: GER &Imprimir Tabuleiro */

/***************************************************************************
*
*  Fun��o: GER  &Salvar Tabuleiro
*  ****/
GER_tpCondRet GER_SalvarTabuleiro ( char * ArquivoDisposicao ){
	
	/* Inicializa vari�veis locais */
	FILE * arquivo			= NULL;
	char coluna				= 0 ;
	int linha				= 0 ;
	GER_tppPeca	pPeca		= NULL ;
	GER_tpCondRet CondRet	= GER_CondRetOK ;

	/* Abre o arquivo e verifica se abriu corretamente */
	arquivo = fopen ( ArquivoDisposicao , "w" );
	if ( arquivo == NULL ){
		return GER_CondRetArqInexistente;
	} /* if */

	/* Imprime cor da vez */
	switch(CorDaVez){
		case GER_CorBranca:
			fprintf ( arquivo , "B \n" );
			break;
		case GER_CorPreta:
			fprintf ( arquivo , "P \n" );
			break;
		default:
			fprintf ( arquivo , "B \n" );
			break;
		}	

	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro( ) ; linha++ ){
		for ( coluna = 'A' ; coluna <= GER_ObterUltimaColunaTabuleiro( ) ; (char)(coluna++)){
			CondRet = GER_ObterPecaDoTabuleiro ( &pPeca , coluna , linha ) ;
			if ( CondRet != GER_CondRetOK )
			{
				return CondRet ;
			}
			
			switch ( GER_ObterTipo ( pPeca ) )
			{
				case GER_TipoPeao:
					fprintf ( arquivo , "P " );
					break;
				case GER_TipoTorre:
					fprintf ( arquivo , "T " );
					break;
				case GER_TipoCavalo:
					fprintf ( arquivo , "C " );
					break;
				case GER_TipoBispo:
					fprintf ( arquivo , "B " );
					break;
				case GER_TipoDama:
					fprintf ( arquivo , "D " );
					break;
				case GER_TipoRei:
					fprintf ( arquivo , "R " );
					break;
				case GER_TipoVazia:
					continue ;
				default:
					return GER_CondRetErroAoSalvarTabuleiro ;
			}

			switch ( GER_ObterCor ( pPeca ) )
			{
				case GER_CorBranca:
					fprintf ( arquivo , "B %c %d\n", coluna , linha );
					break;
				case GER_CorPreta:
					fprintf ( arquivo , "P %c %d\n", coluna , linha );
					break;
				case GER_CorSemCor:
					continue ;
				default:
					return GER_CondRetErroAoSalvarTabuleiro ;
			}
		}
	}

	fclose ( arquivo ) ;
	return GER_CondRetOK ;
}/* Fim fun��o: GER  &Salvar Tabuleiro */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: GER  -Obter Pe�a
*
*  $ED Descri��o da fun��o
*     Obt�m a pe�a referida pela linha do arquivo de disposi��o.
*
*  $EP Par�metros
*	  disposicao - linha do arquivo de disposi��o
*
*  $FV Valor retornado
*	  Retorna a pe�a procurada ou NULL se n�o encontrou a pe�a.
*
***********************************************************************/

GER_tppPeca ObtemPeca ( char * disposicao ){
	
	/* Inicializa vari�veis locais */
	char coluna				='!';
	int linha				=-1 ;
	GER_tppPeca pPeca		= NULL ;
	GER_tpCondRet CondRet	= GER_CondRetOK ;
	
	/* Obt�m posi��o a partir da string */
	if ( sscanf ( disposicao , "%*c %*c %c %d" , 
		          &coluna , &linha ) != 2 )
	{
		return NULL ;
	} /* if */

	/* Obtem pe�a correspondente � posi��o */
	CondRet = GER_ObterPecaDoTabuleiro ( &pPeca , coluna , linha );
	if ( CondRet != GER_CondRetOK )
	{
		return NULL ;
	} /* if */

	return pPeca ;
	
}/* Fim fun��o: GER  -Obter Pe�a */

/***********************************************************************
*
*  $FC Fun��o: GER  -Validar Linha
*
*  $ED Descri��o da fun��o
*     Verifica a sintaxe de uma linha do arquivo de disposi��o de pe�as.
*
*  $EP Par�metros
*	  disposicao - linha do arquivo de disposi��o
*
*  $FV Valor retornado
*	  GER_CondRetOK - linha � v�lida
*	  GER_CondRetArqDispInvalido - linha � inv�lida
*
***********************************************************************/

GER_tpCondRet ValidaLinha ( char * disposicao ){
	
	/* Declara e inicializa vari�veis */
	int Linha;
	int Coluna;
	char Tipo = disposicao[INX_TIPO];
	char Cor = disposicao[INX_COR];
	char charLinha = disposicao[INX_LINHA];
	char charColuna = disposicao[INX_COLUNA];

	Linha = (int) (charLinha - '1');
	Coluna = (int) (charColuna - 'A');

	/* Verifica posi��o */
	if((Linha<0)||(Linha>7)){

		return GER_CondRetArqDispInvalido;
	} /* if */
	else if((Coluna<0)||(Coluna>7)){

		return GER_CondRetArqDispInvalido;
	} /* else if */

	/* Verifica tipo */
	if(
		( Tipo != 'P' )&&
		( Tipo != 'T' )&&
		( Tipo != 'C' )&&
		( Tipo != 'B' )&&
		( Tipo != 'D' )&&
		( Tipo != 'R' )
		)
	{

			return GER_CondRetArqDispInvalido;
	} /* if */

	/* Verifica cor */
	if(
		( Cor != 'B' )&&
		( Cor != 'P' )
		)
	{

			return GER_CondRetArqDispInvalido;
	} /* if */
	
	return GER_CondRetOK;
} /* Fim fun��o: GER  -Validar Linha */

/********** Fim do m�dulo de implementa��o: GER Gerenciador de Xadrez **********/
