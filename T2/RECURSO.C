/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              RECURSO.C
*  Letras identificadoras:      REC
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mv - Mauricio Pedro Silva Gonçalves Vieira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   mp   01/05/2017 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define RECURSO_OWN
#include "RECURSO.H"
#undef RECURSO_OWN

#define TRUE 1
#define FALSE 0

/***********************************************************************
*
*  $TC Tipo de dados: REC Variavel que controla o id de cada tarefa
*
***********************************************************************/

static int idAtual = 0;

/***********************************************************************
*
*  $TC Tipo de dados: REC Descritor do Recurso
*
*
*  $ED Descrição do tipo
*     Descreve a organização de um Recurso
*
***********************************************************************/

   typedef struct tgRecurso {

		int id;
				/* 
			     *	Sequencial que identifica unicamente um Recurso
			     */

		char * nome;
				/*
				 *	Nome do Recurso
				 */

		int estaDisponivel;
				/*
				 *	Variável que indica se o Recurso está atualmente ligado a
				 *	alguma tarefa, seu valor será 1 quando ela estiver disponível
				 *	e 0 quando não estiver
				 */

   } tpRecurso ;

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

//   typedef struct tgArvore {
//
//         tpNoArvore * pNoRaiz ;
//               /* Ponteiro para a raiz da árvore */
//
//         tpNoArvore * pNoCorr ;
//               /* Ponteiro para o nó corrente da árvore */
//
//   } tpArvore ;
//
///*****  Dados encapsulados no módulo  *****/
//
//      static tpArvore * pArvore = NULL ;
//            /* Ponteiro para a cabe‡a da árvore */
//
///***** Protótipos das funções encapuladas no módulo *****/
//
//   static tpNoArvore * CriarNo( char ValorParm ) ;
//
//   static ARV_tpCondRet CriarNoRaiz( char ValorParm ) ;
//
//   static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: REC Criar Recurso
*  ****/

   REC_tpCondRet REC_CriarRecurso (tpRecurso ** ptRecurso, char * novoNome)
   {

	   tpRecurso * pRecurso = (*ptRecurso);
	   if (pRecurso != NULL)
	   {
		   REC_DestruirRecurso(ptRecurso);
	   } /* if */

	   pRecurso = (tpRecurso *)malloc(sizeof(tpRecurso));
	   if (pRecurso == NULL)
	   {
		   return REC_CondRetFaltouMemoria;
	   } /* if */

	   pRecurso->id = idAtual;
	   pRecurso->nome = (char*) malloc (strlen(novoNome)*sizeof(char) + 1);
	   strcpy(pRecurso->nome, novoNome);
	   pRecurso->estaDisponivel = FALSE;
	   idAtual++;

	   (*ptRecurso) = pRecurso;

	   return REC_CondRetOK;

   } /* Fim função: REC Criar Recurso */

/***************************************************************************
*
*  Função: REC Destruir Recurso
*  ****/

   void REC_DestruirRecurso (tpRecurso ** ptRecurso)
   {
	  tpRecurso * pRecurso = (*ptRecurso);

	  if (ptRecurso != NULL)

	  {
		  if (pRecurso != NULL)
		  {
			  free(pRecurso->nome);
			  free(pRecurso);
			  (*ptRecurso) = NULL;
		  } /* if */

	  } /* if */

   } /* Fim função: REC Destruir Recurso */

///***************************************************************************
//*
//*  Função: ARV Adicionar filho à esquerda
//*  ****/
//
//   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm )
//   {
//
//      ARV_tpCondRet CondRet ;
//
//      tpNoArvore * pCorr ;
//      tpNoArvore * pNo ;
//
//      /* Tratar vazio, esquerda */
//
//         CondRet = CriarNoRaiz( ValorParm ) ;
//         if ( CondRet != ARV_CondRetNaoCriouRaiz )
//         {
//            return CondRet ;
//         } /* if */
//
//      /* Criar nó à esquerda de folha */
//
//         pCorr = pArvore->pNoCorr ;
//         if ( pCorr == NULL )
//         {
//            return ARV_CondRetErroEstrutura ;
//         } /* if */
//               
//         if ( pCorr->pNoEsq == NULL )
//         {
//            pNo = CriarNo( ValorParm ) ;
//            if ( pNo == NULL )
//            {
//               return ARV_CondRetFaltouMemoria ;
//            } /* if */
//            pNo->pNoPai      = pCorr ;
//            pCorr->pNoEsq    = pNo ;
//            pArvore->pNoCorr = pNo ;
//
//            return ARV_CondRetOK ;
//         } /* if */
//
//      /* Tratar não folha à esquerda */
//
//         return ARV_CondRetNaoEhFolha ;
//
//   } /* Fim função: ARV Adicionar filho à esquerda */
//
///***************************************************************************
//*
//*  Função: ARV Adicionar filho à direita
//*  ****/
//
//   ARV_tpCondRet ARV_InserirDireita( char ValorParm )
//   {
//
//      ARV_tpCondRet CondRet ;
//
//      tpNoArvore * pCorr ;
//      tpNoArvore * pNo ;
//
//      /* Tratar vazio, direita */
//
//         CondRet = CriarNoRaiz( ValorParm ) ;
//         if ( CondRet != ARV_CondRetNaoCriouRaiz )
//         {
//            return CondRet ;
//         } /* if */
//
//      /* Criar nó à direita de folha */
//
//         pCorr = pArvore->pNoCorr ;
//         if ( pCorr == NULL )
//         {
//            return ARV_CondRetErroEstrutura ;
//         } /* if */
//
//         if ( pCorr->pNoDir == NULL )
//         {
//            pNo = CriarNo( ValorParm ) ;
//            if ( pNo == NULL )
//            {
//               return ARV_CondRetFaltouMemoria ;
//            } /* if */
//            pNo->pNoPai      = pCorr ;
//            pCorr->pNoDir    = pNo ;
//            pArvore->pNoCorr = pNo ;
//
//            return ARV_CondRetOK ;
//         } /* if */
//
//      /* Tratar não folha à direita */
//
//         return ARV_CondRetNaoEhFolha ;
//
//   } /* Fim função: ARV Adicionar filho à direita */
//
///***************************************************************************
//*
//*  Função: ARV Ir para nó pai
//*  ****/
//
//   ARV_tpCondRet ARV_IrPai( void )
//   {
//
//      if ( pArvore == NULL )
//      {
//         return ARV_CondRetArvoreNaoExiste ;
//      } /* if */
//      if ( pArvore->pNoCorr == NULL )
//      {
//         return ARV_CondRetArvoreVazia ;
//      } /* if */
//
//      if ( pArvore->pNoCorr->pNoPai != NULL )
//      {
//         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
//         return ARV_CondRetOK ;
//      } else {
//         return ARV_CondRetNohEhRaiz ;
//      } /* if */
//
//   } /* Fim função: ARV Ir para nó pai */
//
///***************************************************************************
//*
//*  Função: ARV Ir para nó à esquerda
//*  ****/
//
//   ARV_tpCondRet ARV_IrNoEsquerda( void )
//   {
//
//      if ( pArvore == NULL )
//      {
//         return ARV_CondRetArvoreNaoExiste ;
//      } /* if */
//
//      if ( pArvore->pNoCorr == NULL )
//      {
//         return ARV_CondRetArvoreVazia ;
//      } /* if */
//
//      if ( pArvore->pNoCorr->pNoEsq == NULL )
//      {
//         return ARV_CondRetNaoPossuiFilho ;
//      } /* if */
//
//      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
//      return ARV_CondRetOK ;
//
//   } /* Fim função: ARV Ir para nó à esquerda */
//
///***************************************************************************
//*
//*  Função: ARV Ir para nó à direita
//*  ****/
//
//   ARV_tpCondRet ARV_IrNoDireita( void )
//   {
//
//      if ( pArvore == NULL )
//      {
//         return ARV_CondRetArvoreNaoExiste ;
//      } /* if */
//
//      if ( pArvore->pNoCorr == NULL )
//      {
//         return ARV_CondRetArvoreVazia ;
//      } /* if */
//
//      if ( pArvore->pNoCorr->pNoDir == NULL )
//      {
//         return ARV_CondRetNaoPossuiFilho ;
//      } /* if */
//
//      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
//      return ARV_CondRetOK ;
//
//   } /* Fim função: ARV Ir para nó à direita */
//
///***************************************************************************
//*
//*  Função: ARV Obter valor corrente
//*  ****/
//
//   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
//   {
//
//      if ( pArvore == NULL )
//      {
//         return ARV_CondRetArvoreNaoExiste ;
//      } /* if */
//      if ( pArvore->pNoCorr == NULL )
//      {
//         return ARV_CondRetArvoreVazia ;
//      } /* if */
//      * ValorParm = pArvore->pNoCorr->Valor ;
//
//      return ARV_CondRetOK ;
//
//   } /* Fim função: ARV Obter valor corrente */
//
//
///*****  Código das funções encapsuladas no módulo  *****/
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Criar nó da árvore
//*
//*  $FV Valor retornado
//*     Ponteiro para o nó criado.
//*     Será NULL caso a memória tenha se esgotado.
//*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
//*     parâmetro.
//*
//***********************************************************************/
//
//   tpNoArvore * CriarNo( char ValorParm )
//   {
//
//      tpNoArvore * pNo ;
//
//      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
//      if ( pNo == NULL )
//      {
//         return NULL ;
//      } /* if */
//
//      pNo->pNoPai = NULL ;
//      pNo->pNoEsq = NULL ;
//      pNo->pNoDir = NULL ;
//      pNo->Valor  = ValorParm ;
//      return pNo ;
//
//   } /* Fim função: ARV Criar nó da árvore */
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Criar nó raiz da árvore
//*
//*  $FV Valor retornado
//*     ARV_CondRetOK
//*     ARV_CondRetFaltouMemoria
//*     ARV_CondRetNaoCriouRaiz
//*
//***********************************************************************/
//
//   ARV_tpCondRet CriarNoRaiz( char ValorParm )
//   {
//
//      ARV_tpCondRet CondRet ;
//      tpNoArvore * pNo ;
//
//      if ( pArvore == NULL )
//      {
//         CondRet = ARV_CriarArvore( ) ;
//
//         if ( CondRet != ARV_CondRetOK )
//         {
//            return CondRet ;
//         } /* if */
//      } /* if */
//
//      if ( pArvore->pNoRaiz == NULL )
//      {
//         pNo = CriarNo( ValorParm ) ;
//         if ( pNo == NULL )
//         {
//            return ARV_CondRetFaltouMemoria ;
//         } /* if */
//         pArvore->pNoRaiz = pNo ;
//         pArvore->pNoCorr = pNo ;
//
//         return ARV_CondRetOK ;
//      } /* if */
//
//      return ARV_CondRetNaoCriouRaiz ;
//
//   } /* Fim função: ARV Criar nó raiz da árvore */
//
//
///***********************************************************************
//*
//*  $FC Função: ARV Destruir a estrutura da árvore
//*
//*  $EAE Assertivas de entradas esperadas
//*     pNoArvore != NULL
//*
//***********************************************************************/
//
//   void DestroiArvore( tpNoArvore * pNo )
//   {
//
//      if ( pNo->pNoEsq != NULL )
//      {
//         DestroiArvore( pNo->pNoEsq ) ;
//      } /* if */
//
//      if ( pNo->pNoDir != NULL )
//      {
//         DestroiArvore( pNo->pNoDir ) ;
//      } /* if */
//
//      free( pNo ) ;
//
//   } /* Fim função: ARV Destruir a estrutura da árvore */

#undef TRUE
#undef FALSE

/********** Fim do módulo de implementação: Módulo árvore **********/

