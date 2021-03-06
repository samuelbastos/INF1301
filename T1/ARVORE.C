/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T1 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#include "LISTA.H"
#undef ARVORE_OWN

/* Parametro que define qual o numero m�ximo de folhas que o programa consegue costurar */

#define NUM_MAX_FOLHA 16

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do n� da �rvore
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� � raiz
               *   Se n�o for raiz, um de pNoEsq ou pNoDir de pNoPai do n�
               *   corrente apontam para o n� corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho � esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do n� X != NULL ent�o pNoPai de pNoEsq aponta para o n� X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho � direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do n� X != NULL ent�o pNoPai de pNoDir aponta para o n� X */
       
         LIS_tppLista Lista ;
               /* Valor do n� */

         char Chave;
               /* Valor alfanum�rico que representa a ordem que as folhas costuradas devem respeitar */

         struct tgNoArvore * pNoCosturado;
               /* Ponteiro para a pr�xima folha da costura */

   } tpNoArvore ;


/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da estrutura para auxiliar a costura
*
*
*  $ED Descri��o do tipo
*     Descreve as estruturas auxiliares que ser�o utilizadas para costurar
*  as folhas da �rvore
*
***********************************************************************/

   typedef struct tgCostura {

	   tpNoArvore ** folhasParaCosturar;
			/* Vetor para organizar as folhas a serem costuradas */

	   int numeroFolhasArmazenadas;
			/* Armazena o n�mero de folhas que j� foi colocada no vetor de organiza��o */

	   tpNoArvore * primeiroNo;
			/* Ponteiro para o primeiro n� da costura uma vez que essa j� foi feita */
	   
   } tpCostura;


/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a de uma �rvore
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a �rvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da �rvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o n� corrente da �rvore */

		 tpCostura * pCostura;
			  /* Ponteiro para estrutura de costura */

   } tpArvore ;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static tpNoArvore * CriarNo( char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC ) ;

   static ARV_tpCondRet CriarNoRaiz( tpArvore ** ptArvore, char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ARV Criar �rvore
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
	  pArvore->pCostura = NULL;

      (*ptArvore) = pArvore;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Criar �rvore */

/***************************************************************************
*
*  Fun��o: ARV Destruir �rvore
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

   } /* Fim fun��o: ARV Destruir �rvore */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( tpArvore ** ptArvore, char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC )
   {

     ARV_tpCondRet CondRet ;

     tpNoArvore * pCorr ;
     tpNoArvore * pNo ;

     tpArvore * pArvore = (*ptArvore);

      /* Tratar vazio, esquerda */
       
     CondRet = CriarNoRaiz( ptArvore, ValorParm, ValorListaA, ValorListaB, ValorListaC ) ;
     if ( CondRet != ARV_CondRetNaoCriouRaiz )
     {
        return CondRet ;
     } /* if */

      /* Criar n� � esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm, ValorListaA, ValorListaB, ValorListaC ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( tpArvore ** ptArvore, char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC )
   {

     ARV_tpCondRet CondRet ;

     tpNoArvore * pCorr ;
     tpNoArvore * pNo ;

     tpArvore * pArvore = (*ptArvore);

      /* Tratar vazio, direita */
     CondRet = CriarNoRaiz( ptArvore, ValorParm, ValorListaA, ValorListaB, ValorListaC ) ;
     if ( CondRet != ARV_CondRetNaoCriouRaiz )
     {
        return CondRet ;
     } /* if */

      /* Criar n� � direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm, ValorListaA, ValorListaB, ValorListaC ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � direita */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� pai
*  ****/

   ARV_tpCondRet ARV_IrPai( tpArvore * pArvore )
   {

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

         return ARV_CondRetOK ;

      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim fun��o: ARV Ir para n� pai */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( tpArvore * pArvore )
   {

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

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( tpArvore * pArvore )
   {

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

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � direita */

/***************************************************************************
*
*  Fun��o: ARV Obter valor corrente
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

   } /* Fim fun��o: ARV Obter valor corrente */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� da �rvore
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC )
   {

	  int retornoA, retornoB, retornoC;
      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
  	  pNo->pNoCosturado = NULL;
      pNo->Chave  = ValorParm ;

	  if(ValorListaA == 0 && ValorListaB == 0 && ValorListaC == 0)
	  {
		  pNo->Lista = NULL;
	  }
	  else
	  {
		  pNo->Lista = LIS_CriarLista(NULL);
		  LIS_EsvaziarLista(pNo->Lista);

		  retornoA = LIS_InserirElementoAntes(pNo->Lista,(void*)ValorListaA);
		  retornoB = LIS_InserirElementoApos(pNo->Lista, (void*)ValorListaB);
		  retornoC = LIS_InserirElementoApos(pNo->Lista, (void*)ValorListaC);
	  }

      return pNo ;

   } /* Fim fun��o: ARV Criar n� da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� raiz da �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( tpArvore ** ptArvore, char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC )
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
         pNo = CriarNo( ValorParm, ValorListaA, ValorListaB, ValorListaC ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim fun��o: ARV Criar n� raiz da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da �rvore
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

   } /* Fim fun��o: ARV Destruir a estrutura da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da costura
*
*
***********************************************************************/

   void DestroiCostura( tpCostura * pCostura )
   {
	  tpNoArvore * currentNo, * deletaPonteiroCostura;
	  if (pCostura == NULL)
	  {
		return;
	  }

      if ( pCostura->folhasParaCosturar != NULL )
      {
	      currentNo = pCostura->primeiroNo;
	      while (currentNo != NULL)
	      {
			  deletaPonteiroCostura = currentNo;
			  currentNo = currentNo->pNoCosturado;
			  deletaPonteiroCostura->pNoCosturado = NULL;
	      }
	      free(pCostura->folhasParaCosturar);
      } /* if */

      free( pCostura ) ;

   } /* Fim fun��o: ARV Destruir a estrutura da costura */


   /***********************************************************************
*
*  $FC Fun��o: ARV Encontra os n�s folhas da Arvore e cria uma referencia para eles
*			   na estrutura auxiliar de ordena��o
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   void ExtraiNosParaCostura( tpArvore * pARV, tpNoArvore * no)
   {
	   if (no == NULL)
	   {
		   return;
	   } /* if */
	   if (no->pNoEsq == NULL && no->pNoDir == NULL)
	   {
		   pARV->pCostura->folhasParaCosturar[pARV->pCostura->numeroFolhasArmazenadas] = no;
		   pARV->pCostura->numeroFolhasArmazenadas++;
		   return;
	   } /* if */
	   ExtraiNosParaCostura(pARV, no->pNoEsq);
	   ExtraiNosParaCostura(pARV, no->pNoDir);
   }


/***********************************************************************
*
*  $FC Fun��o: ARV Costura os n�s folha da �rvore ordenados por sua Chave
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/
   
   ARV_tpCondRet ARV_Costura( void * pArvore)
   {
	   int i, j, minNo, posParaMaximizar;
	   tpNoArvore * noAux;
	   tpArvore * pARV = (tpArvore *) pArvore;

	   if (pARV == NULL)
	   {
		   return ARV_CondRetArvoreNaoExiste;
	   } /* if */
	   if (pARV->pNoRaiz == NULL)
	   {
		   return ARV_CondRetArvoreVazia;
	   } /* if */

	   DestroiCostura(pARV->pCostura);

	   pARV->pCostura =  ( tpCostura * ) malloc( sizeof( tpCostura ));
	   if (pARV->pCostura == NULL)
	   {
		   return ARV_CondRetFaltouMemoria;
	   }

	   pARV->pCostura->folhasParaCosturar = (tpNoArvore **) malloc(NUM_MAX_FOLHA*sizeof(tpNoArvore*));
	   if (pARV->pCostura->folhasParaCosturar == NULL)
	   {
		   return ARV_CondRetFaltouMemoria;
	   }
	   pARV->pCostura->numeroFolhasArmazenadas = 0;
	   pARV->pCostura->primeiroNo = NULL;

	   ExtraiNosParaCostura(pARV, pARV->pNoRaiz);

	   posParaMaximizar = 0;
	   for (i = 0; i < pARV->pCostura->numeroFolhasArmazenadas - 1; i++)
	   {
		   minNo = posParaMaximizar;
		   for (j = posParaMaximizar; j < pARV->pCostura->numeroFolhasArmazenadas; j++)
		   {
			   if (pARV->pCostura->folhasParaCosturar[j]->Chave < pARV->pCostura->folhasParaCosturar[minNo]->Chave)
			   {
				   minNo = j;
			   } /* if */
		   }
		   noAux = pARV->pCostura->folhasParaCosturar[posParaMaximizar];
		   pARV->pCostura->folhasParaCosturar[posParaMaximizar] = pARV->pCostura->folhasParaCosturar[minNo];
		   pARV->pCostura->folhasParaCosturar[minNo] = noAux;
		   posParaMaximizar++;
	   }

	   for (i = 0; i < pARV->pCostura->numeroFolhasArmazenadas - 1; i++)
	   {
		   pARV->pCostura->folhasParaCosturar[i]->pNoCosturado = pARV->pCostura->folhasParaCosturar[i+1];
	   }
	   pARV->pCostura->primeiroNo = pARV->pCostura->folhasParaCosturar[0];

	   return ARV_CondRetOK;
   }


   /***********************************************************************
*
*  $FC Fun��o: ARV Imprime os n�s costurados na ordem em que foram costurados
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*	  ARV_CondRetArvoreNaoCosturada
*
***********************************************************************/

   ARV_tpCondRet ARV_ImprimeCostura( void * pArvore)
   {
	   tpNoArvore * currentNo;
	   tpArvore * pARV = (tpArvore *) pArvore;

	   if (pARV == NULL)
	   {
		   return ARV_CondRetArvoreNaoExiste;
	   } /* if */
	   if (pARV->pNoRaiz == NULL)
	   {
		   return ARV_CondRetArvoreVazia;
	   } /* if */
	   if (pARV->pCostura == NULL || pARV->pCostura->primeiroNo == NULL)
	   {
		   return ARV_CondRetArvoreNaoCosturada;
	   }

	   currentNo = pARV->pCostura->primeiroNo;
	   printf("\nN�s da Arvore na ordem em que foram costurados: ");
	   while (currentNo != NULL)
	   {
		   printf("%c ", currentNo->Chave);
		   currentNo = currentNo->pNoCosturado;
	   }
	   printf("\n");

	   return ARV_CondRetOK;
   }

/********** Fim do m�dulo de implementa��o: M�dulo �rvore **********/
