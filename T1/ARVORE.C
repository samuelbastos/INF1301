/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T1 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#include "LISTA.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */
       
       LIS_tppLista Lista ;
               /* Valor do nó */

       char Chave;
           /* Valor alfanumérico que representa a ordem que as folhas costuradas devem respeitar */

       struct tgNoArvore * pNoCosturado;
          /* Ponteiro para a próxima folha da costura */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm, int valorA, int valorB, int valorC ) ;

   static ARV_tpCondRet CriarNoRaiz( tpArvore ** ptArvore, char ValorParm, int valorA, int valorB, int valorC ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( tpArvore ** ptArvore )
   {
     tpArvore * pArvore = (*ptArvore);
      if ( pArvore != NULL )
      {
         ARV_DestruirArvore( ptArvore ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;

     (*ptArvore) = pArvore;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

   void ARV_DestruirArvore( tpArvore ** ptArvore )
   {
     tpArvore * pArvore = (*ptArvore);
     if ( ptArvore != NULL)
     {
        if ( pArvore != NULL )
        {
          if ( pArvore->pNoRaiz != NULL )
          {
            DestroiArvore( pArvore->pNoRaiz ) ;
          } /* if */
          free( pArvore ) ;
          (*ptArvore) = NULL ;
        } /* if */
     }
   } /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( tpArvore ** ptArvore, char ValorParm, int valorA, int valorB, int valorC )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

     tpArvore * pArvore = (*ptArvore);

      /* Tratar vazio, esquerda */
       
     CondRet = CriarNoRaiz( ptArvore, ValorParm, valorA, valorB, valorC ) ;
     if ( CondRet != ARV_CondRetNaoCriouRaiz )
     {
        return CondRet ;
     } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm, valorA, valorB, valorC ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( tpArvore ** ptArvore, char ValorParm, int valorA, int valorB, int valorC )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

     tpArvore * pArvore = (*ptArvore);

      /* Tratar vazio, direita */
     CondRet = CriarNoRaiz( ptArvore, ValorParm, valorA, valorB, valorC ) ;
     if ( CondRet != ARV_CondRetNaoCriouRaiz )
     {
        return CondRet ;
     } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm, valorA, valorB, valorC ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( tpArvore * pArvore )
   {
	   int valorA, valorB, valorC;
	   char chave;

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;

		  if(pArvore->pNoCorr->Lista != NULL)
		  {
			  IrInicioLista( pArvore->pNoCorr->Lista ) ;
			  valorA = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
			  LIS_AvancarElementoCorrente(pArvore->pNoCorr->Lista, 1);
			  valorB = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
			  LIS_AvancarElementoCorrente(pArvore->pNoCorr->Lista, 1);
			  valorC = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
			  chave = pArvore->pNoCorr->Chave;
			  printf("Chave: %c ; valorA: %d, valorB: %d, valorC: %d \n", chave, valorA, valorB, valorC);
		  }

         return ARV_CondRetOK ;

      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( tpArvore * pArvore )
   {
	  int valorA, valorB, valorC;
	  char chave;

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
	  if(pArvore->pNoCorr->Lista != NULL)
	  {
		  IrInicioLista( pArvore->pNoCorr->Lista ) ;
		  valorA = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
		  LIS_AvancarElementoCorrente(pArvore->pNoCorr->Lista, 1);
		  valorB = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
		  LIS_AvancarElementoCorrente(pArvore->pNoCorr->Lista, 1);
		  valorC = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
		  chave = pArvore->pNoCorr->Chave;
		  printf("Chave: %c ; valorA: %d, valorB: %d, valorC: %d \n", chave, valorA, valorB, valorC);
	  }
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( tpArvore * pArvore )
   {
	    int valorA, valorB, valorC;
		char chave;

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
	  if(pArvore->pNoCorr->Lista != NULL)
	  {
		  IrInicioLista( pArvore->pNoCorr->Lista ) ;
		  valorA = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
		  LIS_AvancarElementoCorrente(pArvore->pNoCorr->Lista, 1);
		  valorB = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
		  LIS_AvancarElementoCorrente(pArvore->pNoCorr->Lista, 1);
		  valorC = (int)LIS_ObterValor( pArvore->pNoCorr->Lista );
		  chave = pArvore->pNoCorr->Chave;
		  printf("Chave: %c ; valorA: %d, valorB: %d, valorC: %d \n", chave, valorA, valorB, valorC);
	  }
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( tpArvore * pArvore, char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Chave ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm, int valorA, int valorB, int valorC )
   {
	  int A,B,C;
      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Chave  = ValorParm ;

	  if(valorA == 0 && valorB == 0 && valorC == 0)
	  {
		  pNo->Lista = NULL;
	  }
	  else
	  {
		  pNo->Lista = LIS_CriarLista(NULL);
		  LIS_EsvaziarLista(pNo->Lista);

		  A = LIS_InserirElementoAntes(pNo->Lista,(void*)valorA);
		  B = LIS_InserirElementoApos(pNo->Lista, (void*)valorB);
		  C = LIS_InserirElementoApos(pNo->Lista, (void*)valorC);
	  }

      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( tpArvore ** ptArvore, char ValorParm, int valorA, int valorB, int valorC )
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;
	 tpArvore * pArvore = (*ptArvore);

      if ( ptArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ptArvore ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm, valorA, valorB, valorC ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: ARV Destruir a estrutura da árvore */

/********** Fim do módulo de implementação: Módulo árvore **********/
