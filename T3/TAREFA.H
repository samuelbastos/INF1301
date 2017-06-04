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
*  Projeto: T3 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar tarefas.
*     A cada momento o módulo admite no máximo duas tarefas (no caso de conectar
*     tarefas).
*     Tarefas possuem listas de suas sucessoras e predecessoras
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

       TRF_CondRetConexaoJaExistente = 2,
            /* Tarefas já conectadas */

       TRF_CondRetConexaoInvalida = 3,
            /* Conexão inválida de tarefas  */

       TRF_CondRetTarefaInexistente = 4,
            /* Tarefas não alocada */

       TRF_CondRetIdRecursoNaoCadastrado = 5
            /* Id do recurso não cadastrado */

   } TRF_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: TRF cabeça de uma estrutura de tarefa
*
*
***********************************************************************/

   typedef struct tcTarefa tcTarefa;

/***********************************************************************
*
*  $FC Função: TRF Criar tarefa
*
*  $ED Descrição da função
*     Cria uma nova tarefa preenchida com nome e descrição.
*     Caso já exista uma tarefa, esta será destruída.
*
*  $EP Parâmetros
*     $P ctTarefa      - ponteiro passado por referência para apontar para a 
*				         cabeça da tarefa a ser criada
*     $P novoNome      - nome da tarefa a ser criada 
*     $P novaDescricao - descricao da tarefa a ser criada
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetFaltouMemoria
*
***********************************************************************/

   TRF_tpCondRet TRF_CriarTarefa( tcTarefa ** ctTarefa, char * novoNome, char * novaDescricao, int duracao ) ;

/***********************************************************************
*
*  $FC Função: TRF Destruir tarefa
*
*  $EP Parâmetros
*     $P ctTarefa - ponteiro passado por referência que aponta para a 
*                   cabeça da tarefa que será destruida
*
*  $ED Descrição da função
*    Destroi a tarefa passada por referência. 
*
***********************************************************************/

   void TRF_DestruirTarefa( tcTarefa ** ctTarefa ) ;

/***********************************************************************
*
*  $FC Função: TRF Conectar tarefas
*
*  $EP Parâmetros
*     $P ctTarefaSucessora    - ponteiro passado por referência que aponta para a 
*				                cabeça da tarefa que será conectada como sucessora
*     $P ctTarefaPredecessora - ponteiro passado por referência que aponta para a 
*				                cabeça da tarefa que será conectada como predecessora
* 
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*     TRF_CondRetConexaoJaExistente
*     TRF_CondRetConexaoInvalida
*
***********************************************************************/

   TRF_tpCondRet TRF_ConectarTarefas( tcTarefa ** ctTarefaSucessora, tcTarefa ** ctTarefaPredecessora ) ;

/***********************************************************************
*
*  $FC Função: TRF Alterar tarefa
*
*  $EP Parâmetros
*     $P cTarefa        - ponteiro passado por referência que aponta 
*                         para cabeça tarefa a ser alterada
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
*  $FC Função: TRF Consultar id da tarefa
*
*  $EP Parâmetros
*     $P cTarefa              - ponteiro passado por referência que aponta 
*                               para cabeça da tarefa a ser consultada
*                               nome
*     $P idConsultado									- id da tarefa passado por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarIdTarefa( tcTarefa ** ctTarefa, int * idConsultado ) ;

/***********************************************************************
*
*  $FC Função: TRF Consultar nome da tarefa
*
*  $EP Parâmetros
*     $P cTarefa              - ponteiro passado por referência que aponta 
*                               para cabeça da tarefa a ser consultada
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
*  $FC Função: TRF Consultar descricao da tarefa
*
*  $EP Parâmetros
*     $P cTarefa              - ponteiro passado por referência que aponta 
*                               para cabeça da tarefa a ser consultada
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
*  $FC Função: TRF Consultar duracao da tarefa
*
*  $EP Parâmetros
*     $P cTarefa              - ponteiro passado por referência que aponta 
*                               para cabeça da tarefa a ser consultada
*                               nome
*     $P duracaoConsultada				- duracao da tarefa passado por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarDuracaoTarefa( tcTarefa ** ctTarefa, int * duracaoConsultada ) ;

/***********************************************************************
*
*  $FC Função: TRF Cadastrar id do recurso da tarefa
*
*  $EP Parâmetros
*     $P cTarefa              - ponteiro passado por referência que aponta 
*                               para cabeça da tarefa a se cadastrar id 
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
*  $FC Função: TRF Consultar id do recurso da tarefa
*
*  $EP Parâmetros
*     $P cTarefa              - ponteiro passado por referência que aponta 
*                               para cabeça da tarefa a ser consultada
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

/***********************************************************************
*
*  $FC Função: TRF Imprime informações da Tarefa
*
*  $EP Parâmetros
*     $P cTarefa              - ponteiro para a cabeça da tarefa que terá
*																															suas informações impressas
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet TRF_ImprimeTarefa( tcTarefa * ctTarefa) ;

/***********************************************************************
*
*  $FC Função: TRF Checa se a lista de predecessores está vazia
*
*  $EP Parâmetros
*     $P cTarefa            - ponteiro para a cabeça da tarefa que terá
*																													suas informações impressas
*					$P temPredecessores			- variavel na qual sera retornado se a tarefa possui
*																													predecessores 1 para se estiver vazio e 0 caso contrario
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet TRF_TemPredecessores( tcTarefa * ctTarefa, int * temPredecessoras) ;

/***********************************************************************
*
*  $FC Função: TRF Checa se a lista de sucessores está vazia
*
*  $EP Parâmetros
*     $P cTarefa            - ponteiro para a cabeça da tarefa que terá
*																													suas informações impressas
*					$P temSucessores						- variavel na qual sera retornado se a tarefa possui
*																													sucessores 1 para se estiver vazio e 0 caso contrario
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente
*
***********************************************************************/

   TRF_tpCondRet TRF_TemSucessores( tcTarefa * ctTarefa, int * temSucessoras) ;


#undef TAREFA_EXT

/********** Fim do módulo de definição: Módulo tarefa **********/

#else
#endif
