/***************************************************************************
*  $MCI Módulo de implementação: GER Gerenciador de Xadrez
*
*  Arquivo gerado:              GERENCIADOR.C
*  Letras identificadoras:      GER
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
*  $TC Tipo de dados: GER Peça do Tabuleiro
*
*
***********************************************************************/

typedef struct GER_tgPeca{

	GER_tpTipoPeca Tipo;
		/* tipo da peca */

	GER_tpCorPeca Cor;
		/* cor da peca */

}GER_tpPeca;

/*****  Dados encapsulados no módulo  *****/

GER_tppPeca Tabuleiro[N_LINHAS][N_COLUNAS];
	/* Tabuleiro de Peças */

/***** Protótipos das funções encapsuladas no módulo *****/


GER_tpPeca * ObtemPeca ( char * disposicao );

GER_tpCondRet ValidaLinha ( char * disposicao );

GER_tpTipoPeca ObtemCodigoDoTipo ( char Tipo );

GER_tpCorPeca ObtemCodigoDaCor ( char Cor );

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: GER  &Criar Peça
*  ****/
GER_tppPeca GER_CriarPeca ( GER_tpTipoPeca tipo , GER_tpCorPeca cor  ){
	
	/* Aloca memória para a peça */
	GER_tpPeca * pPeca = ( GER_tpPeca * ) malloc ( sizeof ( GER_tpPeca ) );
	
	/* Verifica alocação */
	if ( pPeca == NULL ){
		return NULL;
	} /* if */
	
	/* Verifica se o tipo é válido */
	if( ( tipo < 0 ) ||
		( tipo >= N_TIPOS ) )
	{
		return NULL;
	} /* if */

	/* Verifica se a cor é válida */
	if( ( cor < 0 ) ||
		( cor >= N_CORES ) )
	{
		return NULL;
	} /* if */
	
	/* Verifica se o tipo e a cor são coerentes */
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

	/* Faz as atribuições */
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;

	return pPeca;
}/* Fim função: GER  &Criar Peça */

/***************************************************************************
*
*  Função: GER  &Destruir Peça
*  ****/
void GER_DestruirPeca ( GER_tppPeca * ppPeca  ){
	
	if ( *ppPeca == NULL )
	{
		return ;
	}

	free( *ppPeca );

	*ppPeca = NULL ;

	return;
}/* Fim função: GER  &Destruir Peça */

/***************************************************************************
*
*  Função: GER  &Atribuir Peça
*  ****/
GER_tpCondRet GER_AtribuirPeca ( GER_tpPeca * pPeca , GER_tpTipoPeca tipo , GER_tpCorPeca cor ){
	
	/* Verifica se a peça existe */
	if ( pPeca == NULL ){
		return GER_CondRetPecaNaoExiste;
	} /* if */
	
	/* Verifica se o tipo é válido */
	if( ( tipo < 0 ) ||
		( tipo >= N_TIPOS ) )
	{
		return GER_CondRetTipoInvalido ;
	} /* if */

	/* Verifica se a cor é válida */
	if( ( cor < 0 ) ||
		( cor >= N_CORES ) )
	{
		return GER_CondRetCorInvalida ;
	} /* if */

		/* Verifica se o tipo e a cor são coerentes */
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

	/* Faz as atribuições */	
	pPeca->Tipo = tipo;
	pPeca->Cor = cor;

	return GER_CondRetOK;
}/* Fim função: GER  &Atribuir Peça */

/***************************************************************************
*
*  Função: GER  &Inicializar Tabuleiro
*  ****/
GER_tpCondRet GER_InicializarTabuleiro ( void ){
	
	/* Inicializa variáveis locais */
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
}/* Fim função: GER  &Inicializar Tabuleiro */

/***************************************************************************
*
*  Função: GER  &Limpar Tabuleiro
*  ****/
void GER_LimparTabuleiro ( void ){
	
	/* Inicializa variáveis locais */
	int linha	= 0;
	int coluna	= 0;

	/* Preenche o tabuleiro com ponteiros para casas vazias */
	for ( linha = 0 ; linha < N_LINHAS ; linha++ ){
		for ( coluna = 0 ; coluna < N_COLUNAS ; coluna++){
			GER_DestruirPeca ( &Tabuleiro[linha][coluna] );
		} /* for */
	} /* for */

	return ;
}/* Fim função: GER  &Limpar Tabuleiro */

/***************************************************************************
*
*  Função: GER  &Preencher Tabuleiro
*  ****/
GER_tpCondRet GER_PreencherTabuleiro ( char * ArquivoDisposicao ){
	
	/* Inicializa variáveis locais */
	FILE * arquivo			= NULL;
	GER_tpCondRet CondRet	= GER_CondRetOK;
	GER_tpPeca * pPeca		= NULL;
	GER_tpTipoPeca Tipo		= GER_TipoVazia;
	GER_tpCorPeca Cor		= GER_CorSemCor;
	char disposicao[TAM_DISPOSICAO];

	/* Abre o arquivo e verifica se abriu corretamente */
	arquivo = fopen ( ArquivoDisposicao , "r" );
	if ( arquivo == NULL ){
		return GER_CondRetArqInexistente;
	} /* if */

	while ( fgets ( disposicao , TAM_DISPOSICAO , arquivo )){
		
		/* Verifica se a linha contém uma disposição válida */
		CondRet = ValidaLinha ( disposicao );
		if ( CondRet != GER_CondRetOK ){
			return CondRet;
		} /* if */

		/* Obtém a casa correspondente à disposição */
		pPeca = ObtemPeca ( disposicao );
		if ( pPeca == NULL )
		{
			return GER_CondRetPecaNaoExiste ;
		} /* if */

		/* Obtem tipo e cor da peça */
		Tipo = GER_ObterCodigoDoTipo ( disposicao[INX_TIPO] );
		Cor = GER_ObterCodigoDaCor ( disposicao[INX_COR] );
		
		/* Faz a atribuição */
		CondRet = GER_AtribuirPeca( pPeca, Tipo, Cor );
		if ( CondRet != GER_CondRetOK){
			return CondRet;
		} /* if */
	}

	/* Fecha o arquivo */
	fclose( arquivo );

	return GER_CondRetOK ;
}/* Fim função: GER  &Preencher Tabuleiro */


/***************************************************************************
*
*  Função: GER  &Obter Peça do Tabuleiro
*  ****/
GER_tpCondRet GER_ObterPecaDoTabuleiro ( GER_tppPeca * ppPeca, char coluna, int linha ){
	
	/* Inicializa variáveis locais */
	int ixColuna	= (int) (coluna - 'A');
	int ixLinha		= linha - 1;

	/* Verifica se a linha é válida */
	if((ixLinha<0)||(ixLinha>=N_LINHAS)){
		return GER_CondRetPecaNaoExiste;
	} /* if */

	/* Verifica se a coluna é válida */
	else if((ixColuna<0)||(ixColuna>=N_COLUNAS)){
		return GER_CondRetPecaNaoExiste;
	} /* else if */

	/* Obtém peça no tabuleiro */
	*ppPeca = Tabuleiro[ixLinha][ixColuna];

	return GER_CondRetOK;
}/* Fim função: GER  &Obter Peça do Tabuleiro */

/***************************************************************************
*
*  Função: GER  &Obter Última Linha do Tabuleiro
*  ****/
int GER_ObterUltimaLinhaTabuleiro ( void ){

	return N_LINHAS;

}/* Fim função: GER  &Obter Última Linha do Tabuleiro */

/***************************************************************************
*
*  Função: GER  &Obter Última Coluna do Tabuleiro
*  ****/
char GER_ObterUltimaColunaTabuleiro ( void ){

	return (char)('A' + N_COLUNAS - 1);

}/* Fim função: GER  &Obter Última Coluna do Tabuleiro */

/***************************************************************************
*
*  Função: GER  &Obter Tipo da Peça
*  ****/
GER_tpTipoPeca GER_ObterTipo ( GER_tppPeca pPeca ) {

	if ( pPeca == NULL )
	{
		return -1;
	}
	return pPeca->Tipo ;

}/* Fim função: GER  &Obter Tipo da Peça */

/***************************************************************************
*
*  Função: GER  &Obter Cor da Peça
*  ****/
GER_tpCorPeca GER_ObterCor ( GER_tppPeca pPeca ) {

	if ( pPeca == NULL )
	{
		return -1;
	}
	return pPeca->Cor ;

}/* Fim função: GER  &Obter Cor da Peça */

/***************************************************************************
*
*  Função: GER  &Obter Código do Tipo
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

}/* Fim função: GER  &Obter Código do Tipo */

/***************************************************************************
*
*  Função: GER  &Obter Código da Cor
*  ****/
GER_tpCorPeca GER_ObterCodigoDaCor ( char Cor ){

	switch ( Cor ){
		case 'B': return GER_CorBranca;
		case 'P': return GER_CorPreta;
		default:  return GER_CorSemCor;
	} /* switch */

} /* Fim função: GER  &Obter Código da Cor */

/***************************************************************************
*
*  Função: GER  &Obter Rei
*  ****/
GER_tpCondRet GER_ObterRei ( GER_tpCorPeca Cor , char * pColuna , int * pLinha ){

	GER_tppPeca pPeca		= NULL ;
	int linha				= 0 ;
	int coluna				= 0 ;
	GER_tpCondRet CondRet	= GER_CondRetOK ;

	for ( linha = 1 ; linha <= GER_ObterUltimaLinhaTabuleiro () ; linha++ )
	{
		for ( coluna = 'A' ; linha <= GER_ObterUltimaColunaTabuleiro () ; coluna++ )
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

} /* Fim função: GER  &Obter Rei */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: GER  -Obter Peça
*
*  $ED Descrição da função
*     Obtém a peça referida pela linha do arquivo de disposição.
*
*  $EP Parâmetros
*	  disposicao - linha do arquivo de disposição
*
*  $FV Valor retornado
*	  Retorna a peça procurada ou NULL se não encontrou a peça.
*
***********************************************************************/

GER_tppPeca ObtemPeca ( char * disposicao ){
	
	/* Inicializa variáveis locais */
	char coluna				='!';
	int linha				=-1 ;
	GER_tppPeca pPeca		= NULL ;
	GER_tpCondRet CondRet	= GER_CondRetOK ;
	
	/* Obtém posição a partir da string */
	if ( sscanf ( disposicao , "%*c %*c %c %d" , 
		          &coluna , &linha ) != 2 )
	{
		return NULL ;
	} /* if */

	/* Obtem peça correspondente à posição */
	CondRet = GER_ObterPecaDoTabuleiro ( &pPeca , coluna , linha );
	if ( CondRet != GER_CondRetOK )
	{
		return NULL ;
	} /* if */

	return pPeca ;
	
}/* Fim função: GER  -Obter Peça */

/***********************************************************************
*
*  $FC Função: GER  -Validar Linha
*
*  $ED Descrição da função
*     Verifica a sintaxe de uma linha do arquivo de disposição de peças.
*
*  $EP Parâmetros
*	  disposicao - linha do arquivo de disposição
*
*  $FV Valor retornado
*	  GER_CondRetOK - linha é válida
*	  GER_CondRetArqDispInvalido - linha é inválida
*
***********************************************************************/

GER_tpCondRet ValidaLinha ( char * disposicao ){
	
	/* Declara e inicializa variáveis */
	int Linha;
	int Coluna;
	char Tipo = disposicao[INX_TIPO];
	char Cor = disposicao[INX_COR];
	char charLinha = disposicao[INX_LINHA];
	char charColuna = disposicao[INX_COLUNA];

	Linha = (int) (charLinha - '1');
	Coluna = (int) (charColuna - 'A');

	/* Verifica posição */
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
} /* Fim função: GER  -Validar Linha */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
