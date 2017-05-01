/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              TAREFA.C
*  Letras identificadoras:      TRF
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
#include   <string.h>

#define TAREFA_OWN
#include "TAREFA.H"
#include "LISTA.H"
#undef TAREFA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
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
   static TRF_tpCondRet DesconectaTarefas( tpTarefa ** ptTarefa ) ;

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
      pTarefa->nome = (char*)malloc(strlen(novoNome));
      pTarefa->descricao = (char*)malloc(strlen(novaDescricao));
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
          DesconectaTarefas( ptTarefa );

          LIS_EsvaziarLista( pTarefa->tarefasPredecessoras );
          LIS_DestruirLista( pTarefa->tarefasPredecessoras );
          LIS_EsvaziarLista( pTarefa->tarefasSucessoras );
          LIS_DestruirLista( pTarefa->tarefasSucessoras );

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

       tpTarefa * pTarefaSucessora = (*ptTarefaSucessora);
       tpTarefa * pTarefaPredecessora = (*ptTarefaPredecessora);

       retornoSucessor = LIS_InserirElementoApos( pTarefaSucessora->tarefasPredecessoras , (void *) pTarefaPredecessora);
       retornoPredecessor = LIS_InserirElementoApos( pTarefaPredecessora->tarefasSucessoras , (void *) pTarefaSucessora);

        //Apenas checa se realmente foram conectadas as tarefas
        procuraListaDoSucessor = LIS_ProcurarValor( pTarefaSucessora->tarefasPredecessoras ,(void *) pTarefaPredecessora);
        procuraListaDoPredecessor = LIS_ProcurarValor( pTarefaPredecessora->tarefasSucessoras, (void*) pTarefaSucessora );
        
       return TRF_CondRetOK;

   } /* Fim função: TRF Conectar tarefas */


/***************************************************************************
*
*  Função: TRF Alterar Tarefa
*  ****/

   TRF_tpCondRet  TRF_AlterarTarefa( tpTarefa ** ptTarefa, char * novoNome, char * novaDescricao  )
   {
       tpTarefa * pTarefa = (*ptTarefa);

       pTarefa->nome = (char*)malloc(strlen(novoNome));
       pTarefa->descricao = (char*)malloc(strlen(novaDescricao));
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

       *nomeConsultado = (char*)malloc(strlen(pTarefa->nome));
       strcpy(*nomeConsultado, pTarefa->nome);

       return TRF_CondRetOK ;

   } /* Fim função: TRF Consultar tarefa */

/***************************************************************************
*
*  Função: TRF Consultar Descricao da Tarefa
*  ****/

   TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( tpTarefa ** ptTarefa, char ** descricaoConsultada ) 
   {
       tpTarefa * pTarefa = (*ptTarefa);

       *descricaoConsultada = (char*)malloc(strlen(pTarefa->descricao));
       strcpy(*descricaoConsultada, pTarefa->descricao);

       return TRF_CondRetOK ;

   } /* Fim função: TRF Consultar tarefa */


   static TRF_tpCondRet DesconectaTarefas( tpTarefa ** ptTarefa )
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
                   pTarefaCorrentePredSuc = (tpTarefa *)LIS_ObterValor( pTarefaCorrentePred->tarefasSucessoras );

                   if(pTarefaCorrentePredSuc->id == pTarefa->id)
                   {
                       LIS_ExcluirElemento( pTarefaCorrentePred->tarefasSucessoras );
                       break;
                   }
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
                   pTarefaCorrenteSucPred = (tpTarefa *)LIS_ObterValor( pTarefaCorrenteSuc->tarefasPredecessoras );

                   if(pTarefaCorrenteSucPred->id == pTarefa->id)
                   {
                       LIS_ExcluirElemento(pTarefaCorrenteSuc->tarefasPredecessoras);
                       break;
                   }

                   retSucPre = LIS_AvancarElementoCorrente( pTarefaCorrenteSuc->tarefasPredecessoras , numPassos );
               }

               retSuc = LIS_AvancarElementoCorrente( pTarefa->tarefasSucessoras , numPassos );
           }
       }

       return TRF_CondRetOK;
   }

/********** Fim do módulo de implementação: Módulo tarefa **********/
