#if ! defined( TAREFA_ )
#define TAREFA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo tarefa
*
*  Arquivo gerado:              TAREFA.H
*  Letras identificadoras:      TRF
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T1 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar tarefas.
*     A árvore possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     A cada momento o módulo admite no máximo uma única tarefa.
*     Ao iniciar a execução do programa não existe tarefa.
*
***************************************************************************/
 
#if defined( TAREFA_OWN )
   #define TAREFA_EXT
#else
   #define TAREFA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: TRF Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

       TRF_CondRetOK = 0,

       TRF_CondRetFaltouMemoria = 1,

       TRF_CondRetAcessoInvalidoVetor = 2

   } TRF_tpCondRet ;

/***********************************************************************
*
*  $FC Função: TRF Criar tarefa
*
*  $ED Descrição da função
*     Cria uma nova tarefa vazia.
*     Caso já exista uma tarefa, esta será destruída.
*
*  $EP Parâmetros
*     $P ptTarefa   - ponteiro passado por referência para apontar para a 
*				      tarefa criada
*     $P id         - id da tarefa a ser criada 
*     $P nome       - nome da tarefa a ser criada 
*     $P descricao - descricao da tarefa a ser criada
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetFaltouMemoria
*
***********************************************************************/

   TRF_tpCondRet TRF_CriarTarefa( void ** ptTarefa, char * novoNome, char * novaDescricao ) ;


/***********************************************************************
*
*  $FC Função: TRF Destruir tarefa
*
*  $EP Parâmetros
*     $P ptTarefa - ponteiro passado por referência que aponta para a 
*                   tarefa que será destruida
*
*  $ED Descrição da função
*    Destroi a tarefa passada por por referência. 
*
***********************************************************************/

   void TRF_DestruirTarefa( void ** ptTarefa ) ;

/***********************************************************************
*
*  $FC Função: ARV Adicionar filho à direita
*
*  $EP Parâmetros
*     $P ptTarefa - ponteiro passado por referência que aponta para a 
*				    árvore onde o filho será adicionado
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso não seja folha para a direita
*
***********************************************************************/

   TRF_tpCondRet TRF_ConectarTarefas( void ** ptTarefaSucessora, void ** ptTarefaPredecessora ) ;

/***********************************************************************
*
*  $FC Função: ARV Obter valor corrente
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a estrutura árvore
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   TRF_tpCondRet  TRF_AlterarTarefa( void ** ptTarefa, char * novoNome, char * novaDescricao  ) ;

/***********************************************************************
*
*  $FC Função: ARV Obter valor corrente
*
*  $EP Parâmetros
*     $P pArvore - ponteiro para a estrutura árvore
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarNomeTarefa( void ** ptTarefa, char ** nomeConsultado ) ;

   TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( void ** ptTarefa, char ** descricaoConsultada ) ;

#undef TAREFA_EXT

/********** Fim do módulo de definição: Módulo tarefa **********/

#else
#endif
