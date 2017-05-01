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
*  Projeto: T2 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar tarefas.
*     A cada momento o módulo admite no máximo duas tarefas (no caso de conectar
*     tarefas).
*     Tarefas possuem um listas de suas sucessoras e predecessoras
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
            /* Executou correto */

       TRF_CondRetFaltouMemoria = 1,
            /* Faltou memória ao alocar os dados */

       TRF_CondRetAcessoInvalidoVetor = 2,
            /* Acesso invalido ao vetor de tarefas */

       TRF_CondRetConexaoJaExistente = 3,
            /* Tarefas já conectadas */

       TRF_CondRetConexaoInvalida = 4,
            /* Conexão inválida de tarefas  */

       TRF_CondRetTarefaInexistente = 5
            /* Tarefas não alocada */

   } TRF_tpCondRet ;

/***********************************************************************
*
*  $FC Função: TRF Criar tarefa
*
*  $ED Descrição da função
*     Cria uma nova tarefa preenchida com nome e descrição.
*     Caso já exista uma tarefa, esta será destruída.
*
*  $EP Parâmetros
*     $P ptTarefa      - ponteiro passado por referência para apontar para a 
*				         tarefa criada
*     $P novoNome      - nome da tarefa a ser criada 
*     $P novaDescricao - descricao da tarefa a ser criada
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
*  $FC Função: TRF Conectar tarefas
*
*  $EP Parâmetros
*     $P ptTarefaSucessora    - ponteiro passado por referência que aponta para a 
*				                tarefa que será conectada como sucessora
*     $P ptTarefaPredecessora - ponteiro passado por referência que aponta para a 
*				                tarefa que será conectada como predecessora
* 
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetConexaoJaExistente
*     TRF_CondRetConexaoInvalida
*
***********************************************************************/

   TRF_tpCondRet TRF_ConectarTarefas( void ** ptTarefaSucessora, void ** ptTarefaPredecessora ) ;

/***********************************************************************
*
*  $FC Função: TRF Alterar tarefa
*
*  $EP Parâmetros
*     $P pTarefa        - ponteiro passado por referência que aponta 
*                         a tarefa a ser alterada
*     $P novoNome       - novo nome da tarefa 
*     $P novaDescricao  - nova descricao da tarefa
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente;
*
***********************************************************************/

   TRF_tpCondRet  TRF_AlterarTarefa( void ** ptTarefa, char * novoNome, char * novaDescricao  ) ;

/***********************************************************************
*
*  $FC Função: TRF Consultar nome da tarefa
*
*  $EP Parâmetros
*     $P pTarefa              - ponteiro passado por referência que aponta 
*                               a tarefa a ser alterada
*     $P nomeConsultado       - nome da tarefa passado por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente;
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarNomeTarefa( void ** ptTarefa, char ** nomeConsultado ) ;

/***********************************************************************
*
*  $FC Função: TRF Consultar descricao da tarefa
*
*  $EP Parâmetros
*     $P pTarefa              - ponteiro passado por referência que aponta 
*                               a tarefa a ser alterada
*     $P nomeConsultado       - descricao da tarefa passada por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente;
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( void ** ptTarefa, char ** descricaoConsultada ) ;

#undef TAREFA_EXT

/********** Fim do módulo de definição: Módulo tarefa **********/

#else
#endif
