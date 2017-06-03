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
*  $TC Tipo de dados: TRF Descritor da estrutura de um cronograma
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
*  $TC Tipo de dados: CRO Descritor da cabeça de um cronograma
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
      tpCronograma * pCronograma = NULL;

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
																free(cCronograma->cronograma);

												} /* if */

												//free(cCronograma);
												(*ctCronograma) = NULL;

								} /* if */

				} /* Fim função: CRO Destruir cronograma */

/***************************************************************************
*
*  Função: CRO Insere Tarefa
*  ****/

				CRO_tpCondRet CRO_InserirTarefa( tcCronograma * cCronograma, char * novoNome, char * novaDescricao )
				{
								tcTarefa * tarefaParaInserir = NULL;
								TRF_tpCondRet tarefaCondRet;
								LIS_tpCondRet lisCondRet;

								tarefaCondRet = TRF_CriarTarefa( &tarefaParaInserir, novoNome, novaDescricao);
								if (tarefaCondRet == TRF_CondRetFaltouMemoria)
												return CRO_CondRetFaltouMemoria;

								if (cCronograma == NULL || cCronograma->cronograma == NULL)
												return CRO_CronogramaNaoExiste;

								lisCondRet = LIS_InserirElementoApos(cCronograma->cronograma->listaTarefas, tarefaParaInserir);
								if (lisCondRet == LIS_CondRetFaltouMemoria)
												return CRO_CondRetFaltouMemoria;

								return CRO_CondRetOK;

				} /* Fim função: CRO Insere Tarefa */

/***************************************************************************
*
*  Função: CRO Insere Recurso
*  ****/
				
				CRO_tpCondRet CRO_InserirRecurso( tcCronograma * cCronograma, char * novoNome)
				{
								tcRecurso * recursoParaInserir = NULL;
								REC_tpCondRet recursoCondRet;
								LIS_tpCondRet lisCondRet;

								recursoCondRet = REC_CriarRecurso( &recursoParaInserir, novoNome);
								if (recursoCondRet == REC_CondRetFaltouMemoria)
												return CRO_CondRetFaltouMemoria;
								else if (recursoCondRet == REC_CondRetNomeInvalido)
												return CRO_NomeRecursoInvalido;

								if (cCronograma == NULL || cCronograma->cronograma == NULL)
												return CRO_CronogramaNaoExiste;

								lisCondRet = LIS_InserirElementoApos(cCronograma->cronograma->listaRecursos, recursoParaInserir);
								if (lisCondRet == LIS_CondRetFaltouMemoria)
												return CRO_CondRetFaltouMemoria;

								return CRO_CondRetOK;

				} /* Fim função: CRO Insere Recurso */

/***************************************************************************
*
*  Função: CRO Remover Tarefa
*  ****/
				
				CRO_tpCondRet CRO_RemoveTarefa( tcCronograma * cCronograma, int idParaRemover )
				{
								tcTarefa * tarefaCorrente = NULL;
								int * idTarefaCorrente = (int *) malloc(sizeof(int));

								IrInicioLista(cCronograma->cronograma->listaTarefas);
								tarefaCorrente = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
								TRF_ConsultarIdTarefa(&tarefaCorrente, idTarefaCorrente);
								if ( (*idTarefaCorrente) == idParaRemover)
								{
												LIS_ExcluirElemento(cCronograma->cronograma->listaTarefas);
												return CRO_CondRetOK;
								}

								while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
								{
												tarefaCorrente = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
												TRF_ConsultarIdTarefa(&tarefaCorrente, idTarefaCorrente);
												if ( (*idTarefaCorrente) == idParaRemover)
												{
																LIS_ExcluirElemento(cCronograma->cronograma->listaTarefas);
																return CRO_CondRetOK;
												}
								}

								return CRO_TarefaNaoEncontrada;

				} /* Fim função: CRO Remover Tarefa */

/***************************************************************************
*
*  Função: CRO Remover Recurso
*  ****/
				
				CRO_tpCondRet CRO_RemoveRecurso( tcCronograma * cCronograma, int idParaRemover )
				{
								tcRecurso * recursoCorrente = NULL;
								int * idRecursoCorrente = (int *) malloc(sizeof(int));
								
								IrInicioLista(cCronograma->cronograma->listaRecursos);
								recursoCorrente = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);
								REC_ConsultarId(recursoCorrente, idRecursoCorrente);
								if ( (*idRecursoCorrente) == idParaRemover)
								{
												LIS_ExcluirElemento(cCronograma->cronograma->listaRecursos);
												return CRO_CondRetOK;
								}

								while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaRecursos, 1) != LIS_CondRetFimLista)
								{
												recursoCorrente = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);
												REC_ConsultarId(recursoCorrente, idRecursoCorrente);
												if ( (*idRecursoCorrente) == idParaRemover)
												{
																LIS_ExcluirElemento(cCronograma->cronograma->listaRecursos);
																return CRO_CondRetOK;
												}
								}

								return CRO_RecursoNaoEncontrado;

				} /* Fim função: CRO Remover Recurso */

/***************************************************************************
*
*  Função: CRO Imprime Lista Tarefas
*  ****/

				CRO_tpCondRet CRO_ImprimeListaTarefa( tcCronograma * cCronograma)
				{
								tcTarefa * tarefaCorrente = NULL;
								if (cCronograma == NULL || cCronograma->cronograma == NULL)
												return CRO_CronogramaNaoExiste;

								if (LIS_VerificarVazia(cCronograma->cronograma->listaTarefas) == LIS_CondRetListaVazia)
								{
												printf("A lista de tarefas está vazia\n");
												return CRO_CondRetOK;
								}
								else
								{
												printf("\nLista de Tarefas do Cronograma\n");
								}

								IrInicioLista(cCronograma->cronograma->listaTarefas);
								tarefaCorrente = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
								TRF_ImprimeTarefa(tarefaCorrente);

								while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
								{
												printf("\n");
												tarefaCorrente = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
												TRF_ImprimeTarefa(tarefaCorrente);
								}
								printf("\n");

								return CRO_CondRetOK;

				} /* Fim função: CRO Imprime Lista Tarefas */

/***************************************************************************
*
*  Função: CRO Imprime Lista Recurso
*  ****/

				CRO_tpCondRet CRO_ImprimeListaRecurso( tcCronograma * cCronograma)
				{
								tcRecurso * recursoCorrente = NULL;
								if (cCronograma == NULL || cCronograma->cronograma == NULL)
												return CRO_CronogramaNaoExiste;

								if (LIS_VerificarVazia(cCronograma->cronograma->listaRecursos) == LIS_CondRetListaVazia)
								{
												printf("A lista de recursos está vazia\n");
												return CRO_CondRetOK;
								}
								else
								{
												printf("\nLista de Recursos do Cronograma\n");
								}

								IrInicioLista(cCronograma->cronograma->listaRecursos);
								recursoCorrente = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);
								REC_ImprimeRecurso(recursoCorrente);

								while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaRecursos, 1) != LIS_CondRetFimLista)
								{
												printf("\n");
												recursoCorrente = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);
												REC_ImprimeRecurso(recursoCorrente);
								}
								printf("\n");
								
								return CRO_CondRetOK;

				} /* Fim função: CRO Imprime Lista Recurso */

/********** Fim do módulo de implementação: Módulo cronograma **********/
