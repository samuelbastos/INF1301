/***************************************************************************
*  $MCI Módulo de implementação: Módulo tarefa
*
*  Arquivo gerado:              TAREFA.C
*  Letras identificadoras:      TRF
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define TAREFA_OWN
#include "TAREFA.H"
#include "LISTA.H"
#undef TAREFA_OWN

#define INT_MAX 2147483647
#define TRUE 1
#define FALSE 0

/***********************************************************************
*
*  $TC Tipo de dados: TRF Descritor da estrutura de uma tarefa
*
*
*  $ED Descrição do tipo
*     Descreve a estrutura de uma tarefa
*
***********************************************************************/

    typedef struct tgTarefa {

        char * nome;

        char * descricao;

        int idRecurso;

        int duracao;

        int dataMarcada;

        int dataMaisTarde;
                
        LIS_tppLista tarefasPredecessoras ;
        
        LIS_tppLista tarefasSucessoras;

    } tpTarefa ;

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

    typedef struct tcTarefa {

        int id;

        tpTarefa * tarefa;

    } tcTarefa;

/***** Variáveis encapsuladas no módulo *****/

    static int  idAtual = 0;

/***** Protótipos das funções encapsuladas no módulo *****/

    static void DesconectarTarefas( tpTarefa ** ptTarefa ) ;

/***************************************************************************
*
*  Função: TRF Criar tarefa
*  ****/

    TRF_tpCondRet TRF_CriarTarefa( tcTarefa ** ctTarefa, char * novoNome, char * novaDescricao, int duracao )
    {

        tcTarefa * cTarefa = (*ctTarefa);
        tpTarefa * pTarefa;

        if ( cTarefa != NULL )
        {
            TRF_DestruirTarefa( ctTarefa ) ;
        } /* if */

        cTarefa = ( tcTarefa * ) malloc( sizeof( tcTarefa )) ;
        if ( cTarefa == NULL )
        {
            return TRF_CondRetFaltouMemoria ;
        } /* if */
      
        pTarefa = (tpTarefa * ) malloc( sizeof( tpTarefa )) ;

        pTarefa->tarefasPredecessoras = LIS_CriarLista(NULL);
        pTarefa->tarefasSucessoras = LIS_CriarLista(NULL);
        LIS_EsvaziarLista( pTarefa->tarefasPredecessoras );
        LIS_EsvaziarLista( pTarefa->tarefasSucessoras );
        cTarefa->id = idAtual;
        pTarefa->nome = (char*)malloc(strlen(novoNome)+1);
        pTarefa->descricao = (char*)malloc(strlen(novaDescricao)+1);
        pTarefa->duracao = duracao;
        pTarefa->dataMarcada = -1;
        pTarefa->dataMaisTarde = INT_MAX;
        pTarefa->idRecurso = -1;
        strcpy(pTarefa->nome, novoNome);
        strcpy(pTarefa->descricao, novaDescricao);

        idAtual += 1;

        cTarefa->tarefa = pTarefa;
        (*ctTarefa) = cTarefa;

        return TRF_CondRetOK ;

    } /* Fim função: TRF Criar tarefa */

/***************************************************************************
*
*  Função: TRF Destruir tarefa
*  ****/

    void TRF_DestruirTarefa( tcTarefa ** ctTarefa )
    {
        tcTarefa * cTarefa = (*ctTarefa);

        if ( ctTarefa != NULL)
        {
            if ( cTarefa != NULL )
            {
                DesconectarTarefas( ctTarefa );

                LIS_EsvaziarLista( cTarefa->tarefa->tarefasPredecessoras );
                LIS_DestruirLista( cTarefa->tarefa->tarefasPredecessoras );
                LIS_EsvaziarLista( cTarefa->tarefa->tarefasSucessoras );
                LIS_DestruirLista( cTarefa->tarefa->tarefasSucessoras );
                free(cTarefa->tarefa->nome);
                free(cTarefa->tarefa->descricao);
                free( cTarefa->tarefa );
                free( cTarefa );
                (*ctTarefa) = NULL;

            } /* if */
        }

    } /* Fim função: TRF Destruir tarefa */

/***************************************************************************
*
*  Função: TRF Conectar tarefas
*  ****/

    TRF_tpCondRet TRF_ConectarTarefas( tcTarefa ** ctTarefaSucessora, tcTarefa ** ctTarefaPredecessora )
    {
        LIS_tpCondRet retornoSucessor;
        LIS_tpCondRet retornoPredecessor;
        LIS_tpCondRet procuraListaDoSucessor;
        LIS_tpCondRet procuraListaDoPredecessor;
        LIS_tpCondRet procuraListaDoSucessorInverso;
        LIS_tpCondRet procuraListaDoPredecessorInverso;

        tcTarefa * cTarefaSucessora = (*ctTarefaSucessora);
        tcTarefa * cTarefaPredecessora = (*ctTarefaPredecessora);

        if(cTarefaSucessora == NULL || cTarefaPredecessora == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        IrInicioLista( cTarefaSucessora->tarefa->tarefasPredecessoras ) ;
        IrInicioLista( cTarefaPredecessora->tarefa->tarefasSucessoras ) ;

        procuraListaDoSucessor = LIS_ProcurarValor( cTarefaSucessora->tarefa->tarefasPredecessoras ,(void *) cTarefaPredecessora);
        procuraListaDoPredecessor = LIS_ProcurarValor( cTarefaPredecessora->tarefa->tarefasSucessoras, (void*) cTarefaSucessora );

        if(procuraListaDoSucessor == LIS_CondRetOK && procuraListaDoPredecessor == LIS_CondRetOK)
        {
            return TRF_CondRetConexaoJaExistente;
        }

        IrInicioLista( cTarefaPredecessora->tarefa->tarefasPredecessoras ) ;
        IrInicioLista( cTarefaSucessora->tarefa->tarefasSucessoras ) ;

        procuraListaDoSucessorInverso = LIS_ProcurarValor( cTarefaPredecessora->tarefa->tarefasPredecessoras ,(void *) cTarefaSucessora);
        procuraListaDoPredecessorInverso = LIS_ProcurarValor( cTarefaSucessora->tarefa->tarefasSucessoras ,(void *) cTarefaPredecessora);

        if(procuraListaDoSucessorInverso == LIS_CondRetOK &&  procuraListaDoPredecessorInverso == LIS_CondRetOK)
        {
            return TRF_CondRetConexaoInvalida;
        }

        IrFinalLista( cTarefaSucessora->tarefa->tarefasPredecessoras ) ;
        IrFinalLista( cTarefaPredecessora->tarefa->tarefasSucessoras ) ;
        retornoSucessor = LIS_InserirElementoApos( cTarefaSucessora->tarefa->tarefasPredecessoras , (void *) cTarefaPredecessora);
        retornoPredecessor = LIS_InserirElementoApos( cTarefaPredecessora->tarefa->tarefasSucessoras , (void *) cTarefaSucessora);
        
        return TRF_CondRetOK;

    } /* Fim função: TRF Conectar tarefas */


/***************************************************************************
*
*  Função: TRF Alterar Tarefa
*  ****/

    TRF_tpCondRet  TRF_AlterarTarefa( tcTarefa ** ctTarefa, char * novoNome, char * novaDescricao, int duracao )
    {
        tcTarefa * cTarefa = (*ctTarefa);

        if (cTarefa == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        cTarefa->tarefa->nome = NULL;
        cTarefa->tarefa->descricao = NULL;
        cTarefa->tarefa->nome = (char*)malloc(strlen(novoNome)+1);
        cTarefa->tarefa->descricao = (char*)malloc(strlen(novaDescricao)+1);
        cTarefa->tarefa->duracao = duracao;
        strcpy(cTarefa->tarefa->nome, novoNome);
        strcpy(cTarefa->tarefa->descricao, novaDescricao);

        return TRF_CondRetOK ;

    } /* Fim função: TRF Alterar tarefa */

/***************************************************************************
*
*  Função: TRF Consultar id da tarefa
*  ****/
			
    TRF_tpCondRet  TRF_ConsultarIdTarefa( tcTarefa ** ctTarefa, int * idConsultado )
    {
        tcTarefa * cTarefa = (*ctTarefa);

        if (cTarefa == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        (*idConsultado) = cTarefa->id;

        return TRF_CondRetOK;

    } /* Fim função: TRF Consultar id da tarefa */

/***************************************************************************
*
*  Função: TRF Consultar Nome da Tarefa
*  ****/

    TRF_tpCondRet  TRF_ConsultarNomeTarefa( tcTarefa ** ctTarefa, char ** nomeConsultado ) 
    {
        tcTarefa * cTarefa = (*ctTarefa);

        if (cTarefa == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        *nomeConsultado = (char*)malloc(strlen(cTarefa->tarefa->nome));
        strcpy(*nomeConsultado, cTarefa->tarefa->nome);

        return TRF_CondRetOK ;

    } /* Fim função: TRF Consultar nome da tarefa */

/***************************************************************************
*
*  Função: TRF Consultar Descricao da Tarefa
*  ****/

    TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( tcTarefa ** ctTarefa, char ** descricaoConsultada ) 
    {
        tcTarefa * cTarefa = (*ctTarefa);

        if (cTarefa == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        *descricaoConsultada = (char*)malloc(strlen(cTarefa->tarefa->descricao));
        strcpy(*descricaoConsultada, cTarefa->tarefa->descricao);

        return TRF_CondRetOK ;

    } /* Fim função: TRF Consultar descricao da tarefa */

/***************************************************************************
*
*  Função: TRF Consultar duracao da tarefa
*  ****/
			
    TRF_tpCondRet  TRF_ConsultarDuracaoTarefa( tcTarefa ** ctTarefa, int * duracaoConsultada )
    {
        tcTarefa * cTarefa = (*ctTarefa);

        if (cTarefa == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        (*duracaoConsultada) = cTarefa->tarefa->duracao;

        return TRF_CondRetOK;

    } /* Fim função: TRF Consultar duracao da tarefa */
   
/***************************************************************************
*
*  Função: TRF Cadastrar id do recurso da tarefa
*  ****/

   TRF_tpCondRet TRF_CadastrarIdRecurso( tcTarefa ** ctTarefa, int idRecurso )
   {
       tcTarefa * cTarefa = (*ctTarefa);

       if (cTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       cTarefa->tarefa->idRecurso = idRecurso;

       return TRF_CondRetOK ;

   } /* Fim função: TRF Cadastrar id do recurso da tarefa */

/***************************************************************************
*
*  Função: TRF Consultar id do recurso da tarefa
*  ****/

   TRF_tpCondRet TRF_ConsultarIdRecurso( tcTarefa ** ctTarefa, int* idRecurso )
   {
       tcTarefa * cTarefa = (*ctTarefa);

       if (cTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       if(cTarefa->tarefa->idRecurso == -1)
       {
           return TRF_CondRetIdRecursoNaoCadastrado;
       }

       *idRecurso = cTarefa->tarefa->idRecurso; 

       return TRF_CondRetOK ;

   } /* Fim função: TRF Consultar id do recurso da tarefa */

/***************************************************************************
*
*  Função: TRF Imprime informações da Tarefa
*  ****/
			
    TRF_tpCondRet TRF_ImprimeTarefa( tcTarefa * ctTarefa)
    {
        tcTarefa * tarefaAux = NULL;
        if (ctTarefa == NULL || ctTarefa->tarefa == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        printf("Tarefa: %s\n", ctTarefa->tarefa->nome);
        printf("Id: %d\n", ctTarefa->id);
        printf("Descricao: %s\n", ctTarefa->tarefa->descricao);
        printf("Duracao: %d\n", ctTarefa->tarefa->duracao);

        printf("Predecessoras: ");
        if (LIS_VerificarVazia(ctTarefa->tarefa->tarefasPredecessoras) == LIS_CondRetListaVazia)
        {
            printf("Nao tem Tarefas predecessoras\n");
        }
        else
        {
            IrInicioLista(ctTarefa->tarefa->tarefasPredecessoras);
            tarefaAux = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasPredecessoras);
            printf("%s - id: %d", tarefaAux->tarefa->nome, tarefaAux->id);

            while (LIS_AvancarElementoCorrente(ctTarefa->tarefa->tarefasPredecessoras, 1) != LIS_CondRetFimLista)
            {
                printf(", ");
                tarefaAux = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasPredecessoras);
                printf("%s - id: %d", tarefaAux->tarefa->nome, tarefaAux->id);
            }
            printf("\n");
        }

        printf("Sucessoras: ");
        if (LIS_VerificarVazia(ctTarefa->tarefa->tarefasSucessoras) == LIS_CondRetListaVazia)
        {
            printf("Nao tem Tarefas sucessoras\n");
        }
        else
        {
            IrInicioLista(ctTarefa->tarefa->tarefasSucessoras);
            tarefaAux = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasSucessoras);
            printf("%s - id: %d", tarefaAux->tarefa->nome, tarefaAux->id);

            while (LIS_AvancarElementoCorrente(ctTarefa->tarefa->tarefasSucessoras, 1) != LIS_CondRetFimLista)
            {
                printf(", ");
                tarefaAux = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasSucessoras);
                printf("%s - id: %d", tarefaAux->tarefa->nome, tarefaAux->id);
            }
            printf("\n");
        }

        return TRF_CondRetOK;

    } /* Fim função: TRF Imprime informações da Tarefa */

/***************************************************************************
*
*  Função: TRF Checa se a lista de predecessores está vazia
*  ****/
			
    TRF_tpCondRet TRF_TemPredecessores( tcTarefa * ctTarefa, int * temPredecessoras)
    {
        if (ctTarefa == NULL || ctTarefa->tarefa == NULL)
            return TRF_CondRetTarefaInexistente;

        if (LIS_VerificarVazia(ctTarefa->tarefa->tarefasPredecessoras) == LIS_CondRetListaVazia)
            *temPredecessoras = 1;
        else
            *temPredecessoras = 0;

        return TRF_CondRetOK;

    } /* Fim função: TRF Checa se a lista de predecessores está vazia */

/***************************************************************************
*
*  Função: TRF Checa se a lista de sucessoras está vazia
*  ****/
			
    TRF_tpCondRet TRF_TemSucessores( tcTarefa * ctTarefa, int * temSucessoras)
    {
        if (ctTarefa == NULL || ctTarefa->tarefa == NULL)
            return TRF_CondRetTarefaInexistente;

        if (LIS_VerificarVazia(ctTarefa->tarefa->tarefasSucessoras) == LIS_CondRetListaVazia)
            *temSucessoras = 1;
        else
            *temSucessoras = 0;

        return TRF_CondRetOK;

    } /* Fim função: TRF Checa se a lista de predecessores está vazia */

/*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
*
*  Função: TRF Calcula Caminho Crítico
*  ****/
			
    TRF_tpCondRet TRF_CalculaCaminhoCritico( tcTarefa * ctTarefa )
    {
        int dataMarcada, dataMaisTarde, estaVazia;
        tcTarefa * tarefaAtual, * tarefaSucessora, * tarefaPredecessora;
        LIS_tppLista filaDeExecucao = LIS_CriarLista(NULL);
        LIS_EsvaziarLista(filaDeExecucao);
				
        // Coloca na fila de execucao as reais origens do cronograma
        IrInicioLista(ctTarefa->tarefa->tarefasSucessoras);
        tarefaSucessora = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasSucessoras);
        LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);
        tarefaSucessora->tarefa->dataMarcada = 1;

        while (LIS_AvancarElementoCorrente(ctTarefa->tarefa->tarefasSucessoras, 1) != LIS_CondRetFimLista)
        {
            tarefaSucessora = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasSucessoras);
            LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);
            tarefaSucessora->tarefa->dataMarcada = 1;
        }
								
        // Calcula as datas marcadas
        while (LIS_VerificarVazia(filaDeExecucao) != LIS_CondRetListaVazia)
        {
            tarefaAtual = (tcTarefa *) LIS_PopPrimeiro(filaDeExecucao);
            TRF_TemSucessores(tarefaAtual, &estaVazia);
            if (estaVazia == FALSE)
            {
                IrInicioLista(tarefaAtual->tarefa->tarefasSucessoras);
                tarefaSucessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasSucessoras);
                LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);
												
                dataMarcada = tarefaAtual->tarefa->dataMarcada + tarefaAtual->tarefa->duracao;
                if (tarefaSucessora->tarefa->dataMarcada < dataMarcada)
                    tarefaSucessora->tarefa->dataMarcada = dataMarcada;

                while (LIS_AvancarElementoCorrente(tarefaAtual->tarefa->tarefasSucessoras, 1) != LIS_CondRetFimLista)
                {
                    tarefaSucessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasSucessoras);
                    LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);

                    dataMarcada = tarefaAtual->tarefa->dataMarcada + tarefaAtual->tarefa->duracao;
                    if (tarefaSucessora->tarefa->dataMarcada < dataMarcada)
                        tarefaSucessora->tarefa->dataMarcada = dataMarcada;
                }
            }
        }

        // Colocar na fila de execuçao os finais reais do cronograma
        tarefaAtual->tarefa->dataMaisTarde = tarefaAtual->tarefa->dataMarcada;
        IrInicioLista(tarefaAtual->tarefa->tarefasPredecessoras);
        tarefaPredecessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasPredecessoras);
        LIS_InserirElementoFinal(filaDeExecucao, tarefaPredecessora);
        tarefaPredecessora->tarefa->dataMaisTarde = tarefaAtual->tarefa->dataMaisTarde - tarefaPredecessora->tarefa->duracao;

        while (LIS_AvancarElementoCorrente(tarefaAtual->tarefa->tarefasPredecessoras, 1) != LIS_CondRetFimLista)
        {
            tarefaPredecessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasPredecessoras);
            LIS_InserirElementoFinal(filaDeExecucao, tarefaPredecessora);
            tarefaPredecessora->tarefa->dataMaisTarde = tarefaAtual->tarefa->dataMaisTarde - tarefaPredecessora->tarefa->duracao;
        }

        // Calcula as datas mais tardes
        while (LIS_VerificarVazia(filaDeExecucao) != LIS_CondRetListaVazia)
        {
            tarefaAtual = (tcTarefa *) LIS_PopPrimeiro(filaDeExecucao);
            TRF_TemPredecessores(tarefaAtual, &estaVazia);
            if (estaVazia == FALSE)
            {
                IrInicioLista(tarefaAtual->tarefa->tarefasPredecessoras);
                tarefaPredecessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasPredecessoras);
                LIS_InserirElementoFinal(filaDeExecucao, tarefaPredecessora);
												
                dataMaisTarde = tarefaAtual->tarefa->dataMaisTarde - tarefaPredecessora->tarefa->duracao;
                if (tarefaPredecessora->tarefa->dataMaisTarde > dataMaisTarde)
                    tarefaPredecessora->tarefa->dataMaisTarde = dataMaisTarde;

                while (LIS_AvancarElementoCorrente(tarefaAtual->tarefa->tarefasPredecessoras, 1) != LIS_CondRetFimLista)
                {
                    tarefaPredecessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasPredecessoras);
                    LIS_InserirElementoFinal(filaDeExecucao, tarefaPredecessora);

                    dataMaisTarde = tarefaAtual->tarefa->dataMaisTarde - tarefaPredecessora->tarefa->duracao;
                    if (tarefaPredecessora->tarefa->dataMaisTarde > dataMaisTarde)
                        tarefaPredecessora->tarefa->dataMaisTarde = dataMaisTarde;
                }
            }
        }

        return TRF_CondRetOK;

    } /* Fim função: TRF Calcula Caminho Crítico */

/***************************************************************************
*
*  Função: TRF Imprime Caminho Crítico
*  ****/
			
    TRF_tpCondRet TRF_ImprimeCaminhoCritico( tcTarefa * ctTarefa )
    {
        int dataMarcada, dataMaisTarde, estaVazia;
        tcTarefa * tarefaAtual, * tarefaSucessora, * tarefaPredecessora;
        LIS_tppLista filaDeExecucao = LIS_CriarLista(NULL);
        LIS_EsvaziarLista(filaDeExecucao);
				
        // Coloca na fila de execucao as reais origens do cronograma
        IrInicioLista(ctTarefa->tarefa->tarefasSucessoras);
        tarefaSucessora = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasSucessoras);
        if (tarefaSucessora->tarefa->dataMaisTarde - tarefaSucessora->tarefa->dataMarcada == 0)
            LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);

        while (LIS_AvancarElementoCorrente(ctTarefa->tarefa->tarefasSucessoras, 1) != LIS_CondRetFimLista)
        {
            tarefaSucessora = (tcTarefa *) LIS_ObterValor(ctTarefa->tarefa->tarefasSucessoras);
            if (tarefaSucessora->tarefa->dataMaisTarde - tarefaSucessora->tarefa->dataMarcada == 0)
                LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);
        }

        // Imprime tarefas com folga 0
        printf("\nTarefas que formam o caminho Critico\n");
        while (LIS_VerificarVazia(filaDeExecucao) != LIS_CondRetListaVazia)
        {
            tarefaAtual = (tcTarefa *) LIS_PopPrimeiro(filaDeExecucao);
            if (tarefaAtual->tarefa->dataMarcada - tarefaAtual->tarefa->dataMaisTarde == 0)
            {
                printf("Tarefa: %s dia: %d -> ", tarefaAtual->tarefa->nome, tarefaAtual->tarefa->dataMarcada);
            }

            TRF_TemSucessores(tarefaAtual, &estaVazia);
            if (estaVazia == FALSE)
            {
                IrInicioLista(tarefaAtual->tarefa->tarefasSucessoras);
                tarefaSucessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasSucessoras);
                if (tarefaSucessora->tarefa->dataMaisTarde - tarefaSucessora->tarefa->dataMarcada == 0)
                    LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);
								
                while (LIS_AvancarElementoCorrente(tarefaAtual->tarefa->tarefasSucessoras, 1) != LIS_CondRetFimLista)
                {
                    tarefaSucessora = (tcTarefa *) LIS_ObterValor(tarefaAtual->tarefa->tarefasSucessoras);
                    if (tarefaSucessora->tarefa->dataMaisTarde - tarefaSucessora->tarefa->dataMarcada == 0)
                        LIS_InserirElementoFinal(filaDeExecucao, tarefaSucessora);
                }
            }
        }
        printf("Fim\n");

        return TRF_CondRetOK;

    } /* Fim função: TRF Imprime Caminho Crítico */

/***************************************************************************
*
*  Função: TRF Imprime informações da Tarefa relevantes para Cronograma
*  ****/

    TRF_tpCondRet TRF_ImprimeBasicoTarefa( tcTarefa * ctTarefa )
    {
        tcTarefa * tarefaAux = NULL;
        int folga = ctTarefa->tarefa->dataMaisTarde - ctTarefa->tarefa->dataMarcada;
        if (ctTarefa == NULL || ctTarefa->tarefa == NULL)
        {
            return TRF_CondRetTarefaInexistente;
        }

        printf("Tarefa: %s\n", ctTarefa->tarefa->nome);
        printf("Id: %d\n", ctTarefa->id);
        printf("Duracao: %d\n", ctTarefa->tarefa->duracao);
        printf("Data Marcada: %d\n", ctTarefa->tarefa->dataMarcada);
        printf("Folga: %d\n", folga);

        return TRF_CondRetOK;

    } /* Fim função: TRF Imprime informações da Tarefa relevantes para Cronograma */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TRF Desconectar Tarefas
*
*  $EP Parâmetros
*     $P ctTarefa - ponteiro passado por referência que aponta para a 
*                   cabeça tarefa que será desconectada de todas as outras
*                   as quais a mesma está conectada
*
***********************************************************************/

    static void DesconectarTarefas( tcTarefa ** ctTarefa )
    {
        LIS_tpCondRet retPred = LIS_CondRetOK;
        LIS_tpCondRet retSuc = LIS_CondRetOK;
        LIS_tpCondRet retSucPre = LIS_CondRetOK;
        LIS_tpCondRet retPreSuc = LIS_CondRetOK;

        tcTarefa * cTarefaCorrentePred;
        tcTarefa * cTarefaCorrentePredSuc;
        tcTarefa * cTarefaCorrenteSuc;
        tcTarefa * cTarefaCorrenteSucPred;
       

        int numPassos = 1;
        tcTarefa * cTarefa = (*ctTarefa);

        int flag = 0;

        if(LIS_VerificarVazia(cTarefa->tarefa->tarefasPredecessoras) != LIS_CondRetListaVazia)
        {
            IrInicioLista(cTarefa->tarefa->tarefasPredecessoras);
            cTarefaCorrentePred = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasPredecessoras );
            IrInicioLista(cTarefaCorrentePred->tarefa->tarefasSucessoras);

            while(retPred != LIS_CondRetFimLista)
            {
                cTarefaCorrentePred = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasPredecessoras );

                while(retPreSuc != LIS_CondRetFimLista)
                {
                    if(flag == 1)
                    {
                        IrInicioLista(cTarefaCorrentePred->tarefa->tarefasSucessoras);
                        flag = 0;
                    }

                    cTarefaCorrentePredSuc = (tcTarefa *)LIS_ObterValor( cTarefaCorrentePred->tarefa->tarefasSucessoras );

                    if(cTarefaCorrentePredSuc->id == cTarefa->id)
                    {
                        LIS_ExcluirElemento( cTarefaCorrentePred->tarefa->tarefasSucessoras );
                        flag = 1;
                        break;
                    }

                    retPreSuc = LIS_AvancarElementoCorrente( cTarefaCorrentePred->tarefa->tarefasSucessoras , numPassos );
                }
           
                retPred = LIS_AvancarElementoCorrente( cTarefa->tarefa->tarefasPredecessoras , numPassos );
            }
        }

        if(LIS_VerificarVazia(cTarefa->tarefa->tarefasSucessoras) != LIS_CondRetListaVazia)
        {
            IrInicioLista(cTarefa->tarefa->tarefasSucessoras);
            cTarefaCorrenteSuc = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasSucessoras );
            IrInicioLista(cTarefaCorrenteSuc->tarefa->tarefasPredecessoras);

            while(retSuc != LIS_CondRetFimLista)
            {
                cTarefaCorrenteSuc = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasSucessoras );

                while(retSucPre != LIS_CondRetFimLista)
                {
                    if(flag == 1)
                    {
                        IrInicioLista(cTarefaCorrenteSuc->tarefa->tarefasPredecessoras);
                        flag = 0;
                    }

                    cTarefaCorrenteSucPred = (tcTarefa *)LIS_ObterValor( cTarefaCorrenteSuc->tarefa->tarefasPredecessoras );

                    if(cTarefaCorrenteSucPred->id == cTarefa->id)
                    {
                        LIS_ExcluirElemento(cTarefaCorrenteSuc->tarefa->tarefasPredecessoras);
                        flag = 1;
                        break;
                    }

                    retSucPre = LIS_AvancarElementoCorrente( cTarefaCorrenteSuc->tarefa->tarefasPredecessoras , numPassos );
                }

                retSuc = LIS_AvancarElementoCorrente( cTarefa->tarefa->tarefasSucessoras , numPassos );
            }
        }
    }

#undef INT_MAX
#undef TRUE
#undef FALSE

/********** Fim do módulo de implementação: Módulo tarefa **********/
