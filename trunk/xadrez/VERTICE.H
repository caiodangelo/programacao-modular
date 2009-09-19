typedef enum {
		VER_CondRetOK = 0 ,
               /* Executou correto */

         VER_CondRetVerticeNaoExiste = 1 ,
               /* Vértice não existe */

        VER_CondRetVerticeVazio = 2 ,
               /* Vértice está vazia */

         VER_CondRetFaltouMemoria = 3 ,
               /* Faltou memória ao alocar dados */

} VER_tpCondRet;

/* Pode retornar 0, 1, 2 */
VER_tpCondRet VER_ObterValor ( tpVertice * Vertice, void * Valor );

/* Pode retornar 0, 3*/
VER_tpCondRet VER_CriarVertice ( tpVertice * Vertice, void * Valor );

/* Pode retornar 0, 1*/
VER_tpCondRet VER_DestruirVertice ( tpVertice * Vertice );

/* Pode retornar 0,1*/
VER_tpCondRet VER_AlterarValor ( tpVertice * Vertice, void * ValorNovo );