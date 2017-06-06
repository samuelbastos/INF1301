#include <stdio.h>
#include <string.h>
#include "CRONOGRAMA.H"

#define MAX_STRING 1000

int main (void)
{   
     tcCronograma * cronograma = NULL;
     int codigo = 0;

     /* Variaveis do usuario */
     char nomeRecurso[MAX_STRING];
     int idRecursoRemovido;
     char nomeTarefa[MAX_STRING];
     char descricaoTarefa[MAX_STRING];
     int duracaoTarefa;
     int idTarefaRemovida;
     int idTarefaSucessora;
     int idTarefaPredecessora;
     char encerraAplicacao[MAX_STRING];
     char nomeAlteradoRecurso[MAX_STRING];
     int idRecursoAlterado;
     int idTarefaAlterada;
     char nomeAlteradoTarefa[MAX_STRING];
     char descricaoAlteradaTarefa[MAX_STRING];
     int duracaoAlterada;

     /* CondRets de cada funcao */
     CRO_tpCondRet insereRecurso;
     CRO_tpCondRet removeRecurso;
     CRO_tpCondRet conectaTarefas;
     CRO_tpCondRet alteraRecurso;
     CRO_tpCondRet alteraTarefa;
     CRO_tpCondRet geraCronograma;

     CRO_CriarCronograma(&cronograma);

     printf("CRONOGRAMA \n\n");

     while(codigo != 12)
     {
         printf("Insira o codigo: \n");
         printf("1 - para inserir um novo recurso; \n");
         printf("2 - para remover um recurso; \n");
         printf("3 - para alterar um recurso; \n");
         printf("4 - para inserir uma nova tarefa; \n");
         printf("5 - para remover uma tarefa; \n");
         printf("6 - para alterar uma tarefa; \n");
         printf("7 - para conectar tarefas; \n");
         printf("8 - para imprimir lista de tarefas; \n");
         printf("9 - para imprimir lista de recursos; \n");
         printf("10 - para imprimir o caminho critico; \n");
         printf("11 - para imprimir o cronograma; \n");
         printf("12 - para finalizar a aplicacao Cronograma; \n");
         printf("Codigo: ");
         scanf("%d", &codigo);
     
         switch(codigo)
         {
             case 1:
                 printf("\nNome do recurso: ");
                 scanf(" %[^\n]", nomeRecurso);
                 insereRecurso = CRO_InserirRecurso(cronograma, nomeRecurso);
                 if(insereRecurso == CRO_CondRetNomeRecursoInvalido) 
                     printf("\n Nome invalido. Tente novamente. \n");
                 else 
                     printf("\nRecurso inserido com sucesso. \n\n");
                 break;

             case 2:
                 printf("\nId do recurso a ser removido: ");
                 scanf("%d", &idRecursoRemovido);
                 removeRecurso = CRO_RemoveRecurso(cronograma, idRecursoRemovido);
                 if(removeRecurso == CRO_CondRetRecursoNaoEncontrado) 
                     printf("\nRecurso nao encontrado. Tente novamente. \n\n");
                 else 
                     printf("\nRecurso removido com sucesso \n\n");
                 break;

             case 3:
                 printf("\nId do recurso a ser alterado: ");
                 scanf("%d", &idRecursoAlterado);
                 printf("\nNovo nome para o recurso: ");
                 scanf(" %[^\n]", nomeAlteradoRecurso);
                 alteraRecurso = CRO_AlterarRecurso(cronograma, idRecursoAlterado, nomeAlteradoRecurso);
                 if(alteraRecurso == CRO_CondRetRecursoNaoEncontrado)
                     printf("\nRecurso na encontrado. Tente novamente. \n\n");
                 else 
                     printf("\nRecurso alterado com sucesso \n\n");
                 break;

             case 4:
                 printf("\nNome da tarefa: ");
                 scanf(" %[^\n]",nomeTarefa);
                 printf("\nDescricao da tarefa: ");
                 scanf(" %[^\n]", descricaoTarefa);
                 printf("\nDuracao da tarefa: ");
                 scanf("%d", &duracaoTarefa);
                 CRO_InserirTarefa(cronograma, nomeTarefa, descricaoTarefa, duracaoTarefa) ; 
                 printf("\nTarefa inserida com sucesso. \n\n");
                 break;

             case 5:
                 printf("\nId da tarefa a ser removida: ");
                 scanf("%d", &idTarefaRemovida);
                 removeRecurso = CRO_RemoveTarefa(cronograma, idTarefaRemovida);
                 if(removeRecurso == CRO_CondRetTarefaNaoEncontrada) 
                     printf("\nTarefa nao encontrada. Tente novamente. \n\n");
                 else 
                     printf("\Tarefa removida com sucesso. \n\n");
                 break;

             case 6:
                 printf("\nId da tarefa a ser alterada: ");
                 scanf("%d", &idTarefaAlterada);
                 printf("\nNovo nome para a tarefa: ");
                 scanf(" %[^\n]", nomeAlteradoTarefa);
                 printf("\nNova descricao para a tarefa: ");
                 scanf(" %[^\n]", descricaoAlteradaTarefa);
                 printf("\nNova duracao para a tarefa: ");
                 scanf("%d", &duracaoAlterada);
                 alteraTarefa = CRO_AlterarTarefa(cronograma, idTarefaAlterada, nomeAlteradoTarefa, descricaoAlteradaTarefa, duracaoAlterada);
                 if(alteraTarefa == CRO_CondRetTarefaNaoEncontrada) 
                     printf("\nTarefa nao encontrada. Tente novamente. \n\n");
                 else 
                     printf("\nTarefa alterada com sucesso. \n\n");
                 break;

             case 7:
                 printf("\nId da tarefa sucessora: ");
                 scanf("%d", &idTarefaSucessora);
                 printf("\nId da tarefa predecessora: ");
                 scanf("%d", &idTarefaPredecessora);
                 conectaTarefas = CRO_ConectarTarefas(cronograma, idTarefaSucessora, idTarefaPredecessora);
                 if(conectaTarefas == CRO_CondRetConectarTarefaComElaMesma) 
                     printf("\nTarefas iguais. Tente novamente. \n\n");
                 else if(conectaTarefas == CRO_CondRetConexaoJaExistente) 
                     printf("\nConexao entre tarefas ja existente. Tente novamente. \n\n");
                 else if(conectaTarefas == CRO_CondRetConexaoInvalida) 
                     printf("\nConexao entre tarefas invalida. Tente novamente. \n\n");
                 else if(conectaTarefas == CRO_CondRetTarefaNaoEncontrada) 
                     printf("\nUma das tarefas (ou as duas) nao foi encontrada. Tente novamente. \n\n");
                 else 
                     printf("\nTarefas conectadas com sucesso. \n\n");
                 break;

             case 8:
                 printf("\n");
                 CRO_ImprimeListaTarefa(cronograma);
                 printf("\n");
                 break;

             case 9:
                 printf("\n");
                 CRO_ImprimeListaRecurso(cronograma);
                 printf("\n");
                 break;

             case 10:
                 printf("\n");
                 CRO_CaminhoCritico(cronograma);
                 CRO_ImprimeCaminhoCritico(cronograma);
                 printf("\n");
                 break;
            
             case 11:
                 printf("\n");
                 geraCronograma = CRO_ImprimeCronograma(cronograma);
                 if(geraCronograma == CRO_NaoExisteRecursoSuficiente)
                     printf("\nNao ha recurso suficiente. Tente novamente. \n\n");
                 else if(geraCronograma == CRO_CronogramaVazio)
                     printf("\nNao ha recursos nem tarefas alocadas neste cronograma. Tente novamente. \n\n");
                 printf("\n");
                 break;

             case 12:
                 printf("\nDeseja encerrar a aplicacao? (S/N)\n");
                 printf("Resposta: ");
                 scanf(" %[^\n]", encerraAplicacao);
                 if(strcmp(encerraAplicacao,"N") == 0 || strcmp(encerraAplicacao,"n") == 0) codigo = 0; 
                 else printf("\nAplicacao finalizada.\n\n");
                 break;
         }
     }

     CRO_DestruirCronograma(&cronograma);

     return 0;
}