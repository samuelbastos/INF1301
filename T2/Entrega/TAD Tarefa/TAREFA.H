#if ! defined( TAREFA_ )
#define TAREFA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo tarefa
*
*  Arquivo gerado:              TAREFA.H
*  Letras identificadoras:      TRF
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar tarefas.
*     A cada momento o m�dulo admite no m�ximo duas tarefas (no caso de conectar
*     tarefas).
*     Tarefas possuem listas de suas sucessoras e predecessoras
*     Ao iniciar a execu��o do programa n�o existe tarefa.
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
            /* Executou correto */

       TRF_CondRetFaltouMemoria = 1,
            /* Faltou mem�ria ao alocar os dados */

       TRF_CondRetConexaoJaExistente = 2,
            /* Tarefas j� conectadas */

       TRF_CondRetConexaoInvalida = 3,
            /* Conex�o inv�lida de tarefas  */

       TRF_CondRetTarefaInexistente = 4,
            /* Tarefas n�o alocada */

       TRF_CondRetIdRecursoNaoCadastrado = 5
            /* Id do recurso n�o cadastrado */

   } TRF_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: TRF cabe�a de uma estrutura de tarefa
*
*
***********************************************************************/

   typedef struct tcTarefa tcTarefa;

/***********************************************************************
*
*  $FC Fun��o: TRF Criar tarefa
*
*  $ED Descri��o da fun��o
*     Cria uma nova tarefa preenchida com nome e descri��o.
*     Caso j� exista uma tarefa, esta ser� destru�da.
*
*  $EP Par�metros
*     $P ctTarefa      - ponteiro passado por refer�ncia para apontar para a 
*				         cabe�a da tarefa a ser criada
*     $P novoNome      - nome da tarefa a ser criada 
*     $P novaDescricao - descricao da tarefa a ser criada
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetFaltouMemoria
*
***********************************************************************/

   TRF_tpCondRet TRF_CriarTarefa( tcTarefa ** ctTarefa, char * novoNome, char * novaDescricao ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Destruir tarefa
*
*  $EP Par�metros
*     $P ctTarefa - ponteiro passado por refer�ncia que aponta para a 
*                   cabe�a da tarefa que ser� destruida
*
*  $ED Descri��o da fun��o
*    Destroi a tarefa passada por por refer�ncia. 
*
***********************************************************************/

   void TRF_DestruirTarefa( tcTarefa ** ctTarefa ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Conectar tarefas
*
*  $EP Par�metros
*     $P ctTarefaSucessora    - ponteiro passado por refer�ncia que aponta para a 
*				                cabe�a da tarefa que ser� conectada como sucessora
*     $P ctTarefaPredecessora - ponteiro passado por refer�ncia que aponta para a 
*				                cabe�a da tarefa que ser� conectada como predecessora
* 
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*     TRF_CondRetConexaoJaExistente
*     TRF_CondRetConexaoInvalida
*
***********************************************************************/

   TRF_tpCondRet TRF_ConectarTarefas( tcTarefa ** ctTarefaSucessora, void ** ctTarefaPredecessora ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Alterar tarefa
*
*  $EP Par�metros
*     $P cTarefa        - ponteiro passado por refer�ncia que aponta 
*                         para cabe�a tarefa a ser alterada
*     $P novoNome       - novo nome da tarefa 
*     $P novaDescricao  - nova descricao da tarefa
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet  TRF_AlterarTarefa( tcTarefa ** ctTarefa, char * novoNome, char * novaDescricao  ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Consultar nome da tarefa
*
*  $EP Par�metros
*     $P cTarefa              - ponteiro passado por refer�ncia que aponta 
*                               para cabe�a da tarefa a ser consultada
*                               nome
*     $P nomeConsultado       - nome da tarefa passado por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarNomeTarefa( tcTarefa ** ctTarefa, char ** nomeConsultado ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Consultar descricao da tarefa
*
*  $EP Par�metros
*     $P cTarefa              - ponteiro passado por refer�ncia que aponta 
*                               para cabe�a da tarefa a ser consultada
*                               descricao
*     $P nomeConsultado       - descricao da tarefa passada por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( tcTarefa ** ctTarefa, char ** descricaoConsultada ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Cadastrar id do recurso da tarefa
*
*  $EP Par�metros
*     $P cTarefa              - ponteiro passado por refer�ncia que aponta 
*                               para cabe�a da tarefa a se cadastrar id 
*                               do recurso
*     $P idRecurso            - id do recurso a ser cadastrado na tarefa
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet TRF_CadastrarIdRecurso( tcTarefa ** ctTarefa, int idRecurso ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Consultar id do recurso da tarefa
*
*  $EP Par�metros
*     $P cTarefa              - ponteiro passado por refer�ncia que aponta 
*                               para cabe�a da tarefa a ser consultada
*                               id de recurso
*     $P idRecurso            - ponteiro para o id do recurso da tarefa
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*     TRF_CondRetIdRecursoNaoCadastrado
*
***********************************************************************/

   TRF_tpCondRet TRF_ConsultarIdRecurso( tcTarefa ** ctTarefa, int * idRecurso ) ;

#undef TAREFA_EXT

/********** Fim do m�dulo de defini��o: M�dulo tarefa **********/

#else
#endif
