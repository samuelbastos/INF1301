#if ! defined( CRONOGRAMA_ )
#define CRONOGRAMA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo tarefa
*
*  Arquivo gerado:              CRONOGRAMA.H
*  Letras identificadoras:      CRO
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T3 INF1301 2017.1
*  Autores: mv Maurício Vieira
*           sb Samuel Bastos
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar um cronograma
*	  e determinar o seu caminho crítico.
*     A cada momento o módulo admite no máximo um cronograma.
*     Cada cronograma possui uma lista de recursos e uma lista de tarefas.
*     Ao iniciar a execução do programa não existe cronograma.
*
***************************************************************************/
 
#if defined( CRONOGRAMA_OWN )
   #define CRONOGRAMA_EXT
#else
   #define CRONOGRAMA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: CRO Condicoes de retorno
*
*
***********************************************************************/

    typedef enum {

        CRO_CondRetOK = 0,
            /* Executou correto */

        CRO_CondRetFaltouMemoria = 1,
            /* Faltou memória ao alocar os dados */
												
        CRO_CondRetCronogramaNaoExiste = 2,
            /* A estrutura de cronograma não existe */

        CRO_CondRetNomeRecursoInvalido = 3,
            /* Nome fornecido para recurso inválido */

        CRO_CondRetTarefaNaoEncontrada = 4,
            /* Tarefa procurada nao encontrada na lista de tarefas */

        CRO_CondRetRecursoNaoEncontrado = 5,
            /* Recurso procurado nao encontrado na lista de recursos */

        CRO_CondRetConectarTarefaComElaMesma = 6,
            /* Usuario tentou conectar uma tarefa nela mesma */

        CRO_CondRetConexaoJaExistente = 7,
            /* Conexao que esta tentando ser criada já existe */

        CRO_CondRetConexaoInvalida = 8,
            /* Conexao que esta tentando ser criada é inválida */

        CRO_NaoExisteNenhumaTarefa = 9,
            /* A lista de tarefas está vazia e não pode estar */

        CRO_NaoExisteRecursoSuficiente = 10,
            /* Não há recurso suficiente para gerar o cronograma */

        CRO_CronogramaVazio = 11
            /* Não existem tarefas nem recursos alocados para o cronograma */
  
    } CRO_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: CRO cabeça de uma estrutura de cronograma
*
*
***********************************************************************/

   typedef struct tcCronograma tcCronograma;

/***********************************************************************
*
*  $FC Função: CRO Criar Cronograma
*
*  $ED Descrição da função
*     Cria uma novo cronograma vazio.
*     Caso já exista um cronograma, este será destruído.
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro passado por referência para apontar para a 
*				                   cabeça do cronograma a ser criado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

   CRO_tpCondRet CRO_CriarCronograma( tcCronograma ** ctCronograma );

/***********************************************************************
*
*  $FC Função: CRO Destruir cronograma
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro passado por referência que aponta para a 
*                       cabeça do cronograma que será destruido
*
*  $ED Descrição da função
*    Destroi o cronograma passado por referência. 
*
***********************************************************************/

   void CRO_DestruirCronograma( tcCronograma ** ctCronograma );

/***********************************************************************
*
*  $FC Função: CRO Insere Tarefa
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*     $P novoNome      - nome da tarefa a ser inserida
*     $P novaDescricao - descricao da tarefa a ser inserida
*
*  $ED Descrição da função
*    Insere uma nova tarefa na lista de tarefas do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*			  CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

   CRO_tpCondRet CRO_InserirTarefa( tcCronograma * ctCronograma, char * novoNome, char * novaDescricao, int duracao );

/***********************************************************************
*
*  $FC Função: CRO Insere Recurso
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*     $P novoNome      - nome do recurso a ser inserido
*
*  $ED Descrição da função
*    Insere um novo recurso na lista de recursos do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*					CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetFaltouMemoria
*					CRO_CondRetNomeRecursoInvalido
*
***********************************************************************/

   CRO_tpCondRet CRO_InserirRecurso( tcCronograma * ctCronograma, char * novoNome);

/***********************************************************************
*
*  $FC Função: CRO Remover Tarefa
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*					$P idParaRemover - id da tarefa que se deseja remover
*
*  $ED Descrição da função
*    Remove uma tarefa da lista de tarefas do cronograma
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*					CRO_CondRetCronogramaNaoExiste
*
***********************************************************************/

   CRO_tpCondRet CRO_RemoveTarefa( tcCronograma * cCronograma, int idParaRemover );

/***********************************************************************
*
*  $FC Função: CRO Remover Recurso
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*					$P idParaRemover - id do recurso que se deseja remover
*
*  $ED Descrição da função
*    Remove um recurso da lista de recursos do cronograma
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*					CRO_CondRetCronogramaNaoExiste
*
***********************************************************************/

   CRO_tpCondRet CRO_RemoveRecurso( tcCronograma * cCronograma, int idParaRemover );

/***********************************************************************
*
*  $FC Função: CRO Conectar Tarefas
*
*  $EP Parâmetros
*     $P ctCronograma											- ponteiro para a cabeça do cronograma
*					$P idTarefaSucessora						-	id da tarefa que será a sucessora
*					$P idTarefaPredecessora			- id da tarefa que será a predecessora
*
*  $ED Descrição da função
*    Conecta duas tarefas
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*			  CRO_CondRetCronogramaNaoExiste
*			  CRO_CondRetTarefaNaoEncontrada
*					CRO_CondRetConectarTarefaComElaMesma
*			  CRO_CondRetConexaoJaExistente
*					CRO_CondRetConexaoInvalida
*
***********************************************************************/

   CRO_tpCondRet CRO_ConectarTarefas( tcCronograma * cCronograma, int idTarefaSucessora, int idTarefaPredecessora );

/***********************************************************************
*
*  $FC Função: CRO Imprime Lista Tarefas
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*
*  $ED Descrição da função
*    Insere um novo recurso na lista de tarefas do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

   CRO_tpCondRet CRO_ImprimeListaTarefa( tcCronograma * cCronograma);

/***********************************************************************
*
*  $FC Função: CRO Imprime Lista Recurso
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*
*  $ED Descrição da função
*    Insere um novo recurso na lista de recursos do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

   CRO_tpCondRet CRO_ImprimeListaRecurso( tcCronograma * cCronograma);

/***********************************************************************
*
*  $FC Função: CRO Calcula Caminho Critico
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*
*  $ED Descrição da função
*					Calcula o caminho critico e o imprime na tela baseado nos recursos e
*			tarefas inseridos nas listas do respectivo cronograma
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*     CRO_CondRetCronogramaNaoExiste
*     CRO_NaoExisteNenhumaTarefa
*
***********************************************************************/

   CRO_tpCondRet CRO_CaminhoCritico( tcCronograma * cCronograma);

/***********************************************************************
*
*  $FC Função: CRO Altera Tarefa
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*     $P idTarefa - id da tarefa
*     $P novoNome - novo nome da tarefa
*     $P novaDescricao - nova descricao da tarefa
*     $P duracao - nova duracao da tarefa
*
*  $ED Descrição da função
*					Altera nome, descricao e duracao de uma tarefa com base 
*         em seu id.
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetTarefaNaoEncontrada
*
***********************************************************************/

   CRO_tpCondRet CRO_AlterarTarefa( tcCronograma * cCronograma, int idTarefa, char * novoNome, char * novaDescricao, int novaDuracao );

/***********************************************************************
*
*  $FC Função: CRO Altera Recurso
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*     $P idTarefa - id do recurso
*     $P novoNome - novo nome do recurso
*
*  $ED Descrição da função
*					Altera  nome de um recurso com base 
*         em seu id.
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetRecursoNaoEncontrado
*
***********************************************************************/

   CRO_tpCondRet CRO_AlterarRecurso( tcCronograma * cCronograma, int idRecurso, char * novoNome );

/***********************************************************************
*
*  $FC Função: CRO Gerar Cronograma
*
*  $EP Parâmetros
*     $P ctCronograma - ponteiro para a cabeça do cronograma
*
*  $ED Descrição da função
*     Gere e imprime o cronograma
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetCronogramaNaoExiste
*     CRO_NaoExisteRecursoSuficiente
*     CRO_CronogramaVazio

***********************************************************************/

   CRO_tpCondRet CRO_GerarCronograma( tcCronograma * cCronograma );

#undef CRONOGRAMA_EXT

/********** Fim do módulo de definição: Módulo cronograma **********/

#else
#endif
