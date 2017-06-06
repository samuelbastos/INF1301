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

#define TRUE 1
#define FALSE 0

/***********************************************************************
*
*  $TC Tipo de dados: CRO Descritor da estrutura de um cronograma
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
        tcTarefa * tarefa = NULL;
        tcRecurso * recurso = NULL;
        LIS_tpCondRet recursoListaCondRet;
        LIS_tpCondRet tarefaListaCondRet;

        if ( ctCronograma != NULL)
        {
            if ( cCronograma != NULL )
            {
                IrInicioLista(cCronograma->cronograma->listaTarefas);
                tarefa = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
                IrInicioLista(cCronograma->cronograma->listaRecursos);
                recurso = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos); 

                recursoListaCondRet = LIS_VerificarVazia(cCronograma->cronograma->listaRecursos);
                tarefaListaCondRet = LIS_VerificarVazia(cCronograma->cronograma->listaTarefas);

                if (recursoListaCondRet == LIS_CondRetListaVazia && tarefaListaCondRet == LIS_CondRetListaVazia)
                {
                    LIS_DestruirLista( cCronograma->cronograma->listaRecursos );
                    LIS_DestruirLista( cCronograma->cronograma->listaTarefas );
                }
                else
                {
                    while(LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
                    {
                        tarefa = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
                        TRF_DestruirTarefa(&tarefa);
                    }

                    while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaRecursos, 1) != LIS_CondRetFimLista)
                    {
                        recurso = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);
                        REC_DestruirRecurso(&recurso);
                    }

                    LIS_EsvaziarLista( cCronograma->cronograma->listaRecursos );
                    LIS_DestruirLista( cCronograma->cronograma->listaRecursos );
                    LIS_EsvaziarLista( cCronograma->cronograma->listaTarefas );
                    LIS_DestruirLista( cCronograma->cronograma->listaTarefas );
                }

                free(cCronograma->cronograma);

            } /* if */

            (*ctCronograma) = NULL;

        } /* if */

    } /* Fim função: CRO Destruir cronograma */

/***************************************************************************
*
*  Função: CRO Insere Tarefa
*  ****/

    CRO_tpCondRet CRO_InserirTarefa( tcCronograma * cCronograma, char * novoNome, char * novaDescricao, int duracao )
    {
        tcTarefa * tarefaParaInserir = NULL;
        TRF_tpCondRet tarefaCondRet;
        LIS_tpCondRet lisCondRet;

        tarefaCondRet = TRF_CriarTarefa( &tarefaParaInserir, novoNome, novaDescricao, duracao);
        if (tarefaCondRet == TRF_CondRetFaltouMemoria)
            return CRO_CondRetFaltouMemoria;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;

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
            return CRO_CondRetNomeRecursoInvalido;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;

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
        if (idTarefaCorrente == NULL)
            return CRO_CondRetFaltouMemoria;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;

        IrInicioLista(cCronograma->cronograma->listaTarefas);
        tarefaCorrente = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
        TRF_ConsultarIdTarefa(&tarefaCorrente, idTarefaCorrente);
        if ( (*idTarefaCorrente) == idParaRemover)
        {
            TRF_DestruirTarefa(&tarefaCorrente);
            LIS_ExcluirElemento(cCronograma->cronograma->listaTarefas);
            return CRO_CondRetOK;
        }

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
        {
            tarefaCorrente = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
            TRF_ConsultarIdTarefa(&tarefaCorrente, idTarefaCorrente);
            if ( (*idTarefaCorrente) == idParaRemover)
            {
                TRF_DestruirTarefa(&tarefaCorrente);
                LIS_ExcluirElemento(cCronograma->cronograma->listaTarefas);
                return CRO_CondRetOK;
            }
        }

        return CRO_CondRetTarefaNaoEncontrada;

    } /* Fim função: CRO Remover Tarefa */

/***************************************************************************
*
*  Função: CRO Remover Recurso
*  ****/
				
    CRO_tpCondRet CRO_RemoveRecurso( tcCronograma * cCronograma, int idParaRemover )
    {
        tcRecurso * recursoCorrente = NULL;
        int * idRecursoCorrente = (int *) malloc(sizeof(int));
        if (idRecursoCorrente == NULL)
            CRO_CondRetFaltouMemoria;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;
								
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

        return CRO_CondRetRecursoNaoEncontrado;

    } /* Fim função: CRO Remover Recurso */

/***************************************************************************
*
*  Função: CRO Conectar Tarefas
*  ****/

    CRO_tpCondRet CRO_ConectarTarefas( tcCronograma * cCronograma, int idTarefaSucessora, int idTarefaPredecessora )
    {
        TRF_tpCondRet condRet;
        tcTarefa * tarefaAux = NULL;
        tcTarefa * tarefaSucessora = NULL;
        tcTarefa * tarefaPredecessora = NULL;
        int * idTarefaAux = (int *) malloc(sizeof(int));
        if (idTarefaAux == NULL)
            return CRO_CondRetFaltouMemoria;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;

        if (idTarefaSucessora == idTarefaPredecessora)
            return CRO_CondRetConectarTarefaComElaMesma;

        IrInicioLista(cCronograma->cronograma->listaTarefas);
        tarefaAux = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
        TRF_ConsultarIdTarefa(&tarefaAux, idTarefaAux);
        if ( *idTarefaAux == idTarefaSucessora )
            tarefaSucessora = tarefaAux;
        else if ( *idTarefaAux == idTarefaPredecessora )
            tarefaPredecessora = tarefaAux;
								

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
        {
        tarefaAux = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
            TRF_ConsultarIdTarefa(&tarefaAux, idTarefaAux);
            if ( *idTarefaAux == idTarefaSucessora )
                tarefaSucessora = tarefaAux;
            else if ( *idTarefaAux == idTarefaPredecessora )
                tarefaPredecessora = tarefaAux;
        }

        if (tarefaSucessora == NULL || tarefaPredecessora == NULL)
            return CRO_CondRetTarefaNaoEncontrada;

        condRet = TRF_ConectarTarefas(&tarefaSucessora, &tarefaPredecessora);
        if (condRet == TRF_CondRetConexaoJaExistente)
            return CRO_CondRetConexaoJaExistente;
        if (condRet == TRF_CondRetConexaoInvalida)
            return CRO_CondRetConexaoInvalida;

        return CRO_CondRetOK;

    } /* Fim função: CRO Imprime Lista Tarefas */

/***************************************************************************
*
*  Função: CRO Imprime Lista Tarefas
*  ****/

    CRO_tpCondRet CRO_ImprimeListaTarefa( tcCronograma * cCronograma)
    {
        tcTarefa * tarefaCorrente = NULL;
        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;

        if (LIS_VerificarVazia(cCronograma->cronograma->listaTarefas) == LIS_CondRetListaVazia)
        {
            printf("A lista de tarefas esta vazia\n");
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
            return CRO_CondRetCronogramaNaoExiste;

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

/***************************************************************************
*
*  Função: CRO Calcula Caminho Critico
*  ****/

    CRO_tpCondRet CRO_CaminhoCritico( tcCronograma * cCronograma)
    {
        TRF_tpCondRet condRet;
        tcTarefa * tarefaInicial = NULL;
        tcTarefa * tarefaFinal = NULL;
        tcTarefa * tarefaAux = NULL;
        int estaVazia;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;
				
        condRet = TRF_CriarTarefa(&tarefaInicial, "Tarefa Origem", "Primeira tarefa", 0);
        if (condRet == TRF_CondRetFaltouMemoria)
            return CRO_CondRetFaltouMemoria;

        condRet = TRF_CriarTarefa(&tarefaFinal, "Tarefa Final", "Ultima tarefa", 0);
        if (condRet == TRF_CondRetFaltouMemoria)
            return CRO_CondRetFaltouMemoria;
								
        // Adiciona a primeira tarefa e ultima tarefa ao grafo

                
        if (LIS_VerificarVazia( cCronograma->cronograma->listaTarefas ) == LIS_CondRetListaVazia)
            return CRO_NaoExisteNenhumaTarefa;

        IrInicioLista(cCronograma->cronograma->listaTarefas);
        tarefaAux = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
        TRF_TemPredecessores(tarefaAux, &estaVazia);
        if ( estaVazia == TRUE )
            TRF_ConectarTarefas(&tarefaAux, &tarefaInicial);
        TRF_TemSucessores(tarefaAux, &estaVazia);
        if ( estaVazia == TRUE )
            TRF_ConectarTarefas(&tarefaFinal, &tarefaAux);
								

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
        {
            tarefaAux = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
            TRF_TemPredecessores(tarefaAux, &estaVazia);
            if ( estaVazia == TRUE )
                TRF_ConectarTarefas(&tarefaAux, &tarefaInicial);
            TRF_TemSucessores(tarefaAux, &estaVazia);
            if ( estaVazia == TRUE )
                TRF_ConectarTarefas(&tarefaFinal, &tarefaAux);
        }

        TRF_CalculaCaminhoCritico(tarefaInicial);
        TRF_DestruirTarefa(&tarefaFinal);
        TRF_DestruirTarefa(&tarefaInicial);

        return CRO_CondRetOK;

    } /* Fim função: CRO Calcula Caminho Critico */

/***************************************************************************
*
*  Função: CRO Imprime Caminho Critico
*  ****/

    CRO_tpCondRet CRO_ImprimeCaminhoCritico( tcCronograma * cCronograma)
    {
        TRF_tpCondRet condRet;
        tcTarefa * tarefaInicial = NULL;
        tcTarefa * tarefaAux = NULL;
        int estaVazia;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
            return CRO_CondRetCronogramaNaoExiste;
				
        condRet = TRF_CriarTarefa(&tarefaInicial, "Tarefa Origem", "Primeira tarefa", 0);
        if (condRet == TRF_CondRetFaltouMemoria)
            return CRO_CondRetFaltouMemoria;

        if (LIS_VerificarVazia( cCronograma->cronograma->listaTarefas ) == LIS_CondRetListaVazia)
            return CRO_NaoExisteNenhumaTarefa;

        IrInicioLista(cCronograma->cronograma->listaTarefas);
        tarefaAux = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
        TRF_TemPredecessores(tarefaAux, &estaVazia);
        if ( estaVazia == TRUE )
            TRF_ConectarTarefas(&tarefaAux, &tarefaInicial);
								

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
        {
            tarefaAux = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
            TRF_TemPredecessores(tarefaAux, &estaVazia);
            if ( estaVazia == TRUE )
                TRF_ConectarTarefas(&tarefaAux, &tarefaInicial);
        }

        TRF_ImprimeCaminhoCritico(tarefaInicial);
        TRF_DestruirTarefa(&tarefaInicial);

        return CRO_CondRetOK;

    } /* Fim função: CRO Imprime Caminho Critico */


/***************************************************************************
*
*  Função: CRO Altera Tarefa
*  ****/

    CRO_tpCondRet CRO_AlterarTarefa( tcCronograma * cCronograma, int idTarefa, char * novoNome, char * novaDescricao, int novaDuracao )
    {
        tcTarefa * tarefa = NULL;
        int * idTarefaAux = (int *) malloc(sizeof(int));

        int alterada = 0;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
		    return CRO_CondRetCronogramaNaoExiste;

        IrInicioLista(cCronograma->cronograma->listaTarefas);
        tarefa = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
        TRF_ConsultarIdTarefa(&tarefa, idTarefaAux);

		    if ( *idTarefaAux == idTarefa )
        {
            TRF_AlterarTarefa(&tarefa, novoNome, novaDescricao, novaDuracao);
            alterada = 1;
        }

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
        {
				    tarefa = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
				    TRF_ConsultarIdTarefa(&tarefa, idTarefaAux);
				    if ( *idTarefaAux == idTarefa )
            {
                TRF_AlterarTarefa(&tarefa, novoNome, novaDescricao, novaDuracao);
                alterada = 1;
            }
        }

        if(alterada == 0)
            return CRO_CondRetTarefaNaoEncontrada;

        return CRO_CondRetOK;
    } /* Fim função: CRO Altera Tarefa */

/***************************************************************************
*
*  Função: CRO Altera Recurso
*  ****/

    CRO_tpCondRet CRO_AlterarRecurso( tcCronograma * cCronograma, int idRecurso, char * novoNome )
    {
        tcRecurso * recurso = NULL;
        int * idRecursoAux = (int*) malloc(sizeof(int));

        int alterado = 0;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
		    return CRO_CondRetCronogramaNaoExiste;

        IrInicioLista(cCronograma->cronograma->listaRecursos);
        recurso = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);
        REC_ConsultarId(recurso,idRecursoAux); 

        if( *idRecursoAux == idRecurso)
        {
            REC_AlterarNome(recurso,novoNome);
            alterado = 1;
        }

        while(LIS_AvancarElementoCorrente(cCronograma->cronograma->listaRecursos, 1) != LIS_CondRetFimLista)
        {
            recurso = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);
            REC_ConsultarId(recurso,idRecursoAux);
            if( *idRecursoAux == idRecurso)
            {
                REC_AlterarNome(recurso,novoNome);
                alterado = 1;
            }
        }

        if(alterado == 0)
            return CRO_CondRetRecursoNaoEncontrado;

        return CRO_CondRetOK;
    } /* Fim função: CRO Altera Recurso */

/***************************************************************************
*
*  Função: CRO Imprime Cronograma
*  ****/

    CRO_tpCondRet CRO_ImprimeCronograma( tcCronograma * cCronograma )
    {
        tcTarefa * tarefa = NULL;
        tcRecurso * recurso = NULL;
        int encontrado = 0;
        int qtdRecurso = 0;
        int qtdTarefa = 0;
        int * idRecursoAuxiliar = (int*) malloc(sizeof(int));
        LIS_tpCondRet recursoListaCondRet;
        LIS_tpCondRet tarefaListaCondRet;

        if (cCronograma == NULL || cCronograma->cronograma == NULL)
				    return CRO_CondRetCronogramaNaoExiste;

        CRO_CaminhoCritico(cCronograma);

        IrInicioLista(cCronograma->cronograma->listaRecursos);
        IrInicioLista(cCronograma->cronograma->listaTarefas);

        recursoListaCondRet = LIS_VerificarVazia(cCronograma->cronograma->listaRecursos);
        tarefaListaCondRet = LIS_VerificarVazia(cCronograma->cronograma->listaTarefas);

        if (recursoListaCondRet == LIS_CondRetListaVazia && tarefaListaCondRet == LIS_CondRetListaVazia)
            return CRO_CronogramaVazio;

        printf("\nCronograma: \n");

        if (recursoListaCondRet != LIS_CondRetListaVazia)
            qtdRecurso = 1;
            
        if (tarefaListaCondRet != LIS_CondRetListaVazia)
            qtdTarefa = 1;

        while(LIS_AvancarElementoCorrente(cCronograma->cronograma->listaRecursos, 1) != LIS_CondRetFimLista)
            qtdRecurso++;

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
            qtdTarefa++;
            
        if(qtdTarefa > qtdRecurso)
            return CRO_NaoExisteRecursoSuficiente;

        IrInicioLista(cCronograma->cronograma->listaTarefas);
        tarefa = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
        IrInicioLista(cCronograma->cronograma->listaRecursos);
        recurso = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos); 

        recursoListaCondRet = LIS_VerificarVazia(cCronograma->cronograma->listaRecursos);
        tarefaListaCondRet = LIS_VerificarVazia(cCronograma->cronograma->listaTarefas);
            
        while(LIS_AvancarElementoCorrente(cCronograma->cronograma->listaRecursos, 1) != LIS_CondRetFimLista)
            qtdRecurso++;

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
            qtdTarefa++;

        IrInicioLista(cCronograma->cronograma->listaTarefas);
        tarefa = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
        IrInicioLista(cCronograma->cronograma->listaRecursos);
        recurso = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos); 

        REC_ConsultarId(recurso,idRecursoAuxiliar);
        TRF_CadastrarIdRecurso(&tarefa,*idRecursoAuxiliar);

        TRF_ImprimeBasicoTarefa(tarefa);
        REC_ImprimeRecurso(recurso);
        printf("\n");

        while (LIS_AvancarElementoCorrente(cCronograma->cronograma->listaTarefas, 1) != LIS_CondRetFimLista)
        {
				    tarefa = (tcTarefa *) LIS_ObterValor(cCronograma->cronograma->listaTarefas);
				    LIS_AvancarElementoCorrente(cCronograma->cronograma->listaRecursos, 1);
            recurso = (tcRecurso *) LIS_ObterValor(cCronograma->cronograma->listaRecursos);

            REC_ConsultarId(recurso,idRecursoAuxiliar);
            TRF_CadastrarIdRecurso(&tarefa,*idRecursoAuxiliar);

            TRF_ImprimeBasicoTarefa(tarefa);
            REC_ImprimeRecurso(recurso);
            printf("\n");
        }

        return CRO_CondRetOK;
    } /* Fim função: CRO Imprime Cronograma */

#undef TRUE
#undef FALSE

/********** Fim do módulo de implementação: Módulo cronograma **********/
