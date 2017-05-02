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

	   if (novoNome == NULL || strcmp(novoNome, "") == 0 || strcmp(novoNome, " ") == 0)
	   {
		   return REC_CondRetNomeInvalido;
	   } /* if */

	   pRecurso = (tpRecurso *)malloc(sizeof(tpRecurso));
	   if (pRecurso == NULL)
	   {
		   return REC_CondRetFaltouMemoria;
	   } /* if */

	   pRecurso->id = idAtual;
	   idAtual++;

	   pRecurso->nome = (char*) malloc (strlen(novoNome)*sizeof(char) + 1);
	   if (pRecurso->nome == NULL)
	   {
		   return REC_CondRetFaltouMemoria;
	   } /* if */
	   strcpy(pRecurso->nome, novoNome);

	   pRecurso->estaDisponivel = FALSE;

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

/***************************************************************************
*
*  Função: REC Alterar nome do Recurso
*  ****/

   REC_tpCondRet REC_AlterarNome(tpRecurso * ptRecurso, char * novoNome)
   {
		if (ptRecurso == NULL)
		{
			return REC_CondRetRecursoNaoExiste;
		} /* if */

		if (novoNome == NULL || strcmp(novoNome, "") == 0 || strcmp(novoNome, " ") == 0)
		{
			return REC_CondRetNomeInvalido;
		} /* if */

		free(ptRecurso->nome);
		ptRecurso->nome = (char*)malloc(strlen(novoNome) * sizeof(char) + 1);
		if (ptRecurso->nome == NULL)
		{
			return REC_CondRetFaltouMemoria;
		} /* if */
		strcpy(ptRecurso->nome, novoNome);

		return REC_CondRetOK;

   } /* Fim função: REC Alterar nome do Recurso */

/***************************************************************************
*
*  Função: REC Marca o recurso como ocupado
*  ****/

   REC_tpCondRet REC_MarcarComoOcupada(tpRecurso * ptRecurso)
   {
	   if (ptRecurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */
	   
	   ptRecurso->estaDisponivel = FALSE;

	   return REC_CondRetOK;

   } /* Fim função: REC Marca o recurso como ocupado */

/***************************************************************************
*
*  Função: REC Marca recurso como disponível
*  ****/

   REC_tpCondRet REC_MarcarComoDisponivel(tpRecurso * ptRecurso)
   {
	   if (ptRecurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   ptRecurso->estaDisponivel = TRUE;

	   return REC_CondRetOK;

   } /* Fim função: REC Marca recurso como disponível */

/***************************************************************************
*
*  Função: REC Consulta o Id do recurso
*  ****/

   REC_tpCondRet REC_ConsultarId(tpRecurso * ptRecurso, int * id)
   {
	   if (ptRecurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   (*id) = ptRecurso->id;

	   return REC_CondRetOK;

   } /* Fim função: REC Consulta o Id do recurso */

/***************************************************************************
*
*  Função: REC Consulta o Id do recurso
*  ****/

   REC_tpCondRet REC_ConsultarNome(tpRecurso * ptRecurso, char * nome)
   {
	   if (ptRecurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   free(nome);
	   nome = (char*)malloc(strlen(ptRecurso->nome) * sizeof(char) + 1);
	   if (nome == NULL)
	   {
		   return REC_CondRetFaltouMemoria;
	   } /* if */
	   strcpy(nome, ptRecurso->nome);

	   return REC_CondRetOK;

   } /* Fim função: REC Consulta o Id do recurso */

/***************************************************************************
*
*  Função: REC Consulta a disponibilidade do Recurso
*  ****/

   REC_tpCondRet REC_ConsultarDisponibilidade(tpRecurso * ptRecurso, int * estaDisponivel)
   {
	   if (ptRecurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   (*estaDisponivel) = ptRecurso->estaDisponivel;

	   return REC_CondRetOK;

   } /* Fim função: REC Consulta a disponibilidade do Recurso */


#undef TRUE
#undef FALSE

/********** Fim do módulo de implementação: Módulo árvore **********/

