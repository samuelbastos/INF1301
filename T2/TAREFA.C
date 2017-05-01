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

       int id;

       char * nome;

       char * descricao;

       void * recurso;
                
       LIS_tppLista tarefasPredecessoras ;
        
       LIS_tppLista tarefasSucessoras;

   } tpTarefa ;

   static int  idAtual = 0;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DesconectarTarefas( tpTarefa ** ptTarefa ) ;

/***************************************************************************
*
*  Função: TRF Criar tarefa
*  ****/

   TRF_tpCondRet TRF_CriarTarefa( tpTarefa ** ptTarefa, char * novoNome, char * novaDescricao )
   {

      tpTarefa * pTarefa = (*ptTarefa);
      if ( pTarefa != NULL )
      {
         TRF_DestruirTarefa( ptTarefa ) ;
      } /* if */

      pTarefa = ( tpTarefa * ) malloc( sizeof( tpTarefa )) ;
      if ( pTarefa == NULL )
      {
         return TRF_CondRetFaltouMemoria ;
      } /* if */
      
      pTarefa->tarefasPredecessoras = LIS_CriarLista(NULL);
      pTarefa->tarefasSucessoras = LIS_CriarLista(NULL);
      LIS_EsvaziarLista( pTarefa->tarefasPredecessoras );
      LIS_EsvaziarLista( pTarefa->tarefasSucessoras );
      pTarefa->id = idAtual;
      pTarefa->nome = (char*)malloc(strlen(novoNome)+1);
      pTarefa->descricao = (char*)malloc(strlen(novaDescricao)+1);
      strcpy(pTarefa->nome, novoNome);
      strcpy(pTarefa->descricao, novaDescricao);

      idAtual += 1;

      (*ptTarefa) = pTarefa;

      return TRF_CondRetOK ;

   } /* Fim função: TRF Criar tarefa */

/***************************************************************************
*
*  Função: TRF Destruir tarefa
*  ****/

   void TRF_DestruirTarefa( tpTarefa ** ptTarefa )
   {
     tpTarefa * pTarefa = (*ptTarefa);

     if ( ptTarefa != NULL)
     {
        if ( pTarefa != NULL )
        {
          DesconectarTarefas( ptTarefa );

          LIS_EsvaziarLista( pTarefa->tarefasPredecessoras );
          LIS_DestruirLista( pTarefa->tarefasPredecessoras );
          LIS_EsvaziarLista( pTarefa->tarefasSucessoras );
          LIS_DestruirLista( pTarefa->tarefasSucessoras );
          free(pTarefa->nome);
          free(pTarefa->descricao);
          free( pTarefa );
          (*ptTarefa) = NULL;

        } /* if */
     }

   } /* Fim função: TRF Destruir tarefa */

/***************************************************************************
*
*  Função: TRF Conectar tarefas
*  ****/

   TRF_tpCondRet TRF_ConectarTarefas( tpTarefa ** ptTarefaSucessora, tpTarefa ** ptTarefaPredecessora )
   {
       LIS_tpCondRet retornoSucessor;
       LIS_tpCondRet retornoPredecessor;
       LIS_tpCondRet procuraListaDoSucessor;
       LIS_tpCondRet procuraListaDoPredecessor;
       LIS_tpCondRet procuraListaDoSucessorInverso;
       LIS_tpCondRet procuraListaDoPredecessorInverso;

       tpTarefa * pTarefaSucessora = (*ptTarefaSucessora);
       tpTarefa * pTarefaPredecessora = (*ptTarefaPredecessora);

       if(pTarefaSucessora == NULL || pTarefaPredecessora == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       IrInicioLista( pTarefaSucessora->tarefasPredecessoras ) ;
       IrInicioLista( pTarefaPredecessora->tarefasSucessoras ) ;

       procuraListaDoSucessor = LIS_ProcurarValor( pTarefaSucessora->tarefasPredecessoras ,(void *) pTarefaPredecessora);
       procuraListaDoPredecessor = LIS_ProcurarValor( pTarefaPredecessora->tarefasSucessoras, (void*) pTarefaSucessora );

       if(procuraListaDoSucessor == LIS_CondRetOK && procuraListaDoPredecessor == LIS_CondRetOK)
       {
           return TRF_CondRetConexaoJaExistente;
       }

       IrInicioLista( pTarefaPredecessora->tarefasPredecessoras ) ;
       IrInicioLista( pTarefaSucessora->tarefasSucessoras ) ;

       procuraListaDoSucessorInverso = LIS_ProcurarValor( pTarefaPredecessora->tarefasPredecessoras ,(void *) pTarefaSucessora);
       procuraListaDoPredecessorInverso = LIS_ProcurarValor( pTarefaSucessora->tarefasSucessoras ,(void *) pTarefaPredecessora);

       if(procuraListaDoSucessorInverso == LIS_CondRetOK &&  procuraListaDoPredecessorInverso == LIS_CondRetOK)
       {
           return TRF_CondRetConexaoInvalida;
       }

       retornoSucessor = LIS_InserirElementoApos( pTarefaSucessora->tarefasPredecessoras , (void *) pTarefaPredecessora);
       retornoPredecessor = LIS_InserirElementoApos( pTarefaPredecessora->tarefasSucessoras , (void *) pTarefaSucessora);
        
       return TRF_CondRetOK;

   } /* Fim função: TRF Conectar tarefas */


/***************************************************************************
*
*  Função: TRF Alterar Tarefa
*  ****/

   TRF_tpCondRet  TRF_AlterarTarefa( tpTarefa ** ptTarefa, char * novoNome, char * novaDescricao  )
   {
       tpTarefa * pTarefa = (*ptTarefa);

       if (pTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       pTarefa->nome = NULL;
       pTarefa->descricao = NULL;
       pTarefa->nome = (char*)malloc(strlen(novoNome)+1);
       pTarefa->descricao = (char*)malloc(strlen(novaDescricao)+1);
       strcpy(pTarefa->nome, novoNome);
       strcpy(pTarefa->descricao, novaDescricao);

       return TRF_CondRetOK ;

   } /* Fim função: TRF Alterar tarefa */

/***************************************************************************
*
*  Função: TRF Consultar Nome da Tarefa
*  ****/

   TRF_tpCondRet  TRF_ConsultarNomeTarefa( tpTarefa ** ptTarefa, char ** nomeConsultado ) 
   {
       tpTarefa * pTarefa = (*ptTarefa);

       if (pTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       *nomeConsultado = (char*)malloc(strlen(pTarefa->nome));
       strcpy(*nomeConsultado, pTarefa->nome);

       return TRF_CondRetOK ;

   } /* Fim função: TRF Consultar nome da tarefa */

/***************************************************************************
*
*  Função: TRF Consultar Descricao da Tarefa
*  ****/

   TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( tpTarefa ** ptTarefa, char ** descricaoConsultada ) 
   {
       tpTarefa * pTarefa = (*ptTarefa);

       if (pTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       *descricaoConsultada = (char*)malloc(strlen(pTarefa->descricao));
       strcpy(*descricaoConsultada, pTarefa->descricao);

       return TRF_CondRetOK ;

   } /* Fim função: TRF Consultar descricao da tarefa */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TRF Desconectar Tarefas
*
*  $EP Parâmetros
*     $P ptTarefa - ponteiro passado por referência que aponta para a 
*                   tarefa que será desconectada de todas as tarefas
*                   as quais a mesma está conectada
*
***********************************************************************/

   static void DesconectarTarefas( tpTarefa ** ptTarefa )
   {
       LIS_tpCondRet retPred = LIS_CondRetOK;
       LIS_tpCondRet retSuc = LIS_CondRetOK;
       LIS_tpCondRet retSucPre = LIS_CondRetOK;
       LIS_tpCondRet retPreSuc = LIS_CondRetOK;

       tpTarefa * pTarefaCorrentePred;
       tpTarefa * pTarefaCorrenteSuc;
       tpTarefa * pTarefaCorrenteSucPred;
       tpTarefa * pTarefaCorrentePredSuc;

       int numPassos = 1;
       tpTarefa * pTarefa = (*ptTarefa);

       int flag = 0;

       if(LIS_EstaVazia(pTarefa->tarefasPredecessoras) != LIS_CondRetListaVazia)
       {
           IrInicioLista(pTarefa->tarefasPredecessoras);
           pTarefaCorrentePred = (tpTarefa *)LIS_ObterValor( pTarefa->tarefasPredecessoras );
           IrInicioLista(pTarefaCorrentePred->tarefasSucessoras);

           while(retPred != LIS_CondRetFimLista)
           {
               pTarefaCorrentePred = (tpTarefa *)LIS_ObterValor( pTarefa->tarefasPredecessoras );

               while(retPreSuc != LIS_CondRetFimLista)
               {
                   if(flag == 1)
                   {
                       IrInicioLista(pTarefaCorrentePred->tarefasSucessoras);
                       flag = 0;
                   }

                   pTarefaCorrentePredSuc = (tpTarefa *)LIS_ObterValor( pTarefaCorrentePred->tarefasSucessoras );

                   if(pTarefaCorrentePredSuc->id == pTarefa->id)
                   {
                       LIS_ExcluirElemento( pTarefaCorrentePred->tarefasSucessoras );
                       flag = 1;
                       break;
                   }

                   retPreSuc = LIS_AvancarElementoCorrente( pTarefaCorrentePred->tarefasSucessoras , numPassos );
               }
           
              retPred = LIS_AvancarElementoCorrente( pTarefa->tarefasPredecessoras , numPassos );
           }
       }

       if(LIS_EstaVazia(pTarefa->tarefasSucessoras) != LIS_CondRetListaVazia)
       {
           IrInicioLista(pTarefa->tarefasSucessoras);
           pTarefaCorrenteSuc = (tpTarefa *)LIS_ObterValor( pTarefa->tarefasSucessoras );
           IrInicioLista(pTarefaCorrenteSuc->tarefasPredecessoras);

           while(retSuc != LIS_CondRetFimLista)
           {
               pTarefaCorrenteSuc = (tpTarefa *)LIS_ObterValor( pTarefa->tarefasSucessoras );

               while(retSucPre != LIS_CondRetFimLista)
               {
                   if(flag == 1)
                   {
                       IrInicioLista(pTarefaCorrenteSuc->tarefasPredecessoras);
                       flag = 0;
                   }

                   pTarefaCorrenteSucPred = (tpTarefa *)LIS_ObterValor( pTarefaCorrenteSuc->tarefasPredecessoras );

                   if(pTarefaCorrenteSucPred->id == pTarefa->id)
                   {
                       LIS_ExcluirElemento(pTarefaCorrenteSuc->tarefasPredecessoras);
                       flag = 1;
                       break;
                   }

                   retSucPre = LIS_AvancarElementoCorrente( pTarefaCorrenteSuc->tarefasPredecessoras , numPassos );
               }

               retSuc = LIS_AvancarElementoCorrente( pTarefa->tarefasSucessoras , numPassos );
           }
       }
   }

/********** Fim do módulo de implementação: Módulo tarefa **********/
