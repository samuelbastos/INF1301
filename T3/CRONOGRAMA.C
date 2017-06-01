/***************************************************************************
*  $MCI Módulo de implementação: Módulo cronograma
*
*  Arquivo gerado:              CRONOGRAMA.C
*  Letras identificadoras:      CRO
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T3 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define CRONOGRAMA_OWN
#include "CRONOGRAMA.H"
#include "LISTA.H"
#include "TAREFA.H"
#include "RECURSO.H"
#undef CRONOGRAMA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TRF Descritor da estrutura de uma tarefa
*
*
*  $ED Descrição do tipo
*     Descreve a estrutura de uma tarefa
*
***********************************************************************/

   typedef struct tpCronograma {
                
       LIS_tppLista listaTarefas ;
        
       LIS_tppLista listaRecursos;

   } tpCronograma ;

/***********************************************************************
*
*  $TC Tipo de dados: TRF Descritor da cabeça de uma tarefa
*
*
*  $ED Descrição do tipo
*     A cabeça da tarefa é o ponto de acesso para uma determinada tarefa.
*     Nela é guardada o ponteiro da tarefa em si e sua id.
*
***********************************************************************/

   typedef struct tcCronograma {

       int id;

       tpCronograma * cronograma;

   } tcCronograma;

/***** Variáveis encapsuladas no módulo *****/

   static int  idAtual = 0;

/***** Protótipos das funções encapsuladas no módulo *****/

   //static void DesconectarTarefas( tpTarefa ** ptTarefa ) ;

/***************************************************************************
*
*  Função: CRO Criar cronograma
*  ****/

   CRO_tpCondRet CRO_CriarCronograma( tcCronograma ** ctCronograma )
   {

      tcCronograma * cCronograma = (*ctCronograma);
      tpCronograma * pCronograma;

      if ( cCronograma != NULL )
      {
         CRO_DestruirCronograma( ctCronograma ) ;
      } /* if */

      cCronograma = ( tcCronograma * ) malloc( sizeof( cCronograma )) ;
      if ( cCronograma == NULL )
      {
         return CRO_CondRetFaltouMemoria ;
      } /* if */
      
      pCronograma = (tpCronograma * ) malloc( sizeof( tpCronograma )) ;

      pCronograma->listaRecursos = LIS_CriarLista(NULL);
      pCronograma->listaTarefas = LIS_CriarLista(NULL);
      LIS_EsvaziarLista( pCronograma->listaRecursos );
						LIS_EsvaziarLista( pCronograma->listaTarefas );
      cCronograma->id = idAtual;

      idAtual += 1;

      cCronograma->cronograma = pCronograma;
      (*ctCronograma) = cCronograma;

      return CRO_CondRetOK ;

   } /* Fim função: CRO Criar cronograma */

/***************************************************************************
*
*  Função: CRO Destruir cronograma
*  ****/

				void CRO_DestruirCronograma( tcCronograma ** ctCronograma )
				{
								tcCronograma * cCronograma = (*ctCronograma);

								if ( ctCronograma != NULL)
								{
												if ( cCronograma != NULL )
												{
																LIS_EsvaziarLista( cCronograma->cronograma->listaRecursos );
																LIS_DestruirLista( cCronograma->cronograma->listaRecursos );
																LIS_EsvaziarLista( cCronograma->cronograma->listaTarefas );
																LIS_DestruirLista( cCronograma->cronograma->listaTarefas );
																free( cCronograma );
																(*ctCronograma) = NULL;

												} /* if */
								}

				} /* Fim função: CRO Destruir cronograma */

/***************************************************************************
*
*  Função: CRO Inserir uma nova tarefa na lista de tarefas
*  ****/

				CRO_tpCondRet CRO_InserirTarefa( tcCronograma ** ctCronograma, char * novoNome, char * novaDescricao )
				{

				}


/********** Fim do módulo de implementação: Módulo cronograma **********/
