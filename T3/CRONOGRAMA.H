#if ! defined( CRONOGRAMA_ )
#define CRONOGRAMA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo tarefa
*
*  Arquivo gerado:              CRONOGRAMA.H
*  Letras identificadoras:      CRO
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T3 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar um cronograma
*	  e determinar o seu caminho cr�tico.
*     A cada momento o m�dulo admite no m�ximo um cronograma.
*     Cada cronograma possui uma lista de recursos e uma lista de tarefas.
*     Ao iniciar a execu��o do programa n�o existe cronograma.
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
            /* Faltou mem�ria ao alocar os dados */
												
        CRO_CondRetCronogramaNaoExiste = 2,
            /* A estrutura de cronograma n�o existe */

        CRO_CondRetNomeRecursoInvalido = 3,
            /* Nome fornecido para recurso inv�lido */

        CRO_CondRetTarefaNaoEncontrada = 4,
            /* Tarefa procurada nao encontrada na lista de tarefas */

        CRO_CondRetRecursoNaoEncontrado = 5,
            /* Recurso procurado nao encontrado na lista de recursos */

        CRO_CondRetConectarTarefaComElaMesma = 6,
            /* Usuario tentou conectar uma tarefa nela mesma */

        CRO_CondRetConexaoJaExistente = 7,
            /* Conexao que esta tentando ser criada j� existe */

        CRO_CondRetConexaoInvalida = 8,
            /* Conexao que esta tentando ser criada � inv�lida */

        CRO_NaoExisteNenhumaTarefa = 9,
            /* A lista de tarefas est� vazia e n�o pode estar */

        CRO_NaoExisteRecursoSuficiente = 10,
            /* N�o h� recurso suficiente para gerar o cronograma */

        CRO_CronogramaVazio = 11
            /* N�o existem tarefas nem recursos alocados para o cronograma */
  
    } CRO_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: CRO cabe�a de uma estrutura de cronograma
*
*
***********************************************************************/

    typedef struct tcCronograma tcCronograma;

/***********************************************************************
*
*  $FC Fun��o: CRO Criar Cronograma
*
*  $ED Descri��o da fun��o
*     Cria uma novo cronograma vazio.
*     Caso j� exista um cronograma, este ser� destru�do.
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro passado por refer�ncia para apontar para a 
*				                cabe�a do cronograma a ser criado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

    CRO_tpCondRet CRO_CriarCronograma( tcCronograma ** ctCronograma );

/***********************************************************************
*
*  $FC Fun��o: CRO Destruir cronograma
*
*  $EP Par�metros
*    $P ctCronograma - ponteiro passado por refer�ncia que aponta para a 
*                       cabe�a do cronograma que ser� destruido
*
*  $ED Descri��o da fun��o
*    Destroi o cronograma passado por refer�ncia. 
*
***********************************************************************/

    void CRO_DestruirCronograma( tcCronograma ** ctCronograma );

/***********************************************************************
*
*  $FC Fun��o: CRO Insere Tarefa
*
*  $EP Par�metros
*     $P ctCronograma  - ponteiro para a cabe�a do cronograma
*     $P novoNome      - nome da tarefa a ser inserida
*     $P novaDescricao - descricao da tarefa a ser inserida
*
*  $ED Descri��o da fun��o
*     Insere uma nova tarefa na lista de tarefas do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*			CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

    CRO_tpCondRet CRO_InserirTarefa( tcCronograma * ctCronograma, char * novoNome, char * novaDescricao, int duracao );

/***********************************************************************
*
*  $FC Fun��o: CRO Insere Recurso
*
*  $EP Par�metros
*     $P ctCronograma  - ponteiro para a cabe�a do cronograma
*     $P novoNome      - nome do recurso a ser inserido
*
*  $ED Descri��o da fun��o
*    Insere um novo recurso na lista de recursos do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetFaltouMemoria
*			CRO_CondRetNomeRecursoInvalido
*
***********************************************************************/

    CRO_tpCondRet CRO_InserirRecurso( tcCronograma * ctCronograma, char * novoNome);

/***********************************************************************
*
*  $FC Fun��o: CRO Remover Tarefa
*
*  $EP Par�metros
*     $P ctCronograma  - ponteiro para a cabe�a do cronograma
*			$P idParaRemover - id da tarefa que se deseja remover
*
*  $ED Descri��o da fun��o
*     Remove uma tarefa da lista de tarefas do cronograma
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*			CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetTarefaNaoEncontrada
*
***********************************************************************/

    CRO_tpCondRet CRO_RemoveTarefa( tcCronograma * cCronograma, int idParaRemover );

/***********************************************************************
*
*  $FC Fun��o: CRO Remover Recurso
*
*  $EP Par�metros
*     $P ctCronograma  - ponteiro para a cabe�a do cronograma
*			$P idParaRemover - id do recurso que se deseja remover
*
*  $ED Descri��o da fun��o
*     Remove um recurso da lista de recursos do cronograma
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*			CRO_CondRetCronogramaNaoExiste
*     CRO_CondRetRecursoNaoEncontrado
*
***********************************************************************/

    CRO_tpCondRet CRO_RemoveRecurso( tcCronograma * cCronograma, int idParaRemover );

/***********************************************************************
*
*  $FC Fun��o: CRO Conectar Tarefas
*
*  $EP Par�metros
*     $P ctCronograma							 - ponteiro para a cabe�a do cronograma
*			$P idTarefaSucessora				 - id da tarefa que ser� a sucessora
*			$P idTarefaPredecessora			 - id da tarefa que ser� a predecessora
*
*  $ED Descri��o da fun��o
*     Conecta duas tarefas
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*			CRO_CondRetCronogramaNaoExiste
*			CRO_CondRetTarefaNaoEncontrada
*			CRO_CondRetConectarTarefaComElaMesma
*			CRO_CondRetConexaoJaExistente
*			CRO_CondRetConexaoInvalida
*
***********************************************************************/

    CRO_tpCondRet CRO_ConectarTarefas( tcCronograma * cCronograma, int idTarefaSucessora, int idTarefaPredecessora );

/***********************************************************************
*
*  $FC Fun��o: CRO Imprime Lista Tarefas
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro para a cabe�a do cronograma
*
*  $ED Descri��o da fun��o
*     Insere um novo recurso na lista de tarefas do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

    CRO_tpCondRet CRO_ImprimeListaTarefa( tcCronograma * cCronograma);

/***********************************************************************
*
*  $FC Fun��o: CRO Imprime Lista Recurso
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro para a cabe�a do cronograma
*
*  $ED Descri��o da fun��o
*     Insere um novo recurso na lista de recursos do cronograma passado
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*
***********************************************************************/

    CRO_tpCondRet CRO_ImprimeListaRecurso( tcCronograma * cCronograma);

/***********************************************************************
*
*  $FC Fun��o: CRO Calcula Caminho Critico
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro para a cabe�a do cronograma
*
*  $ED Descri��o da fun��o
*			Calcula o caminho critico baseado nos recursos e
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
*  $FC Fun��o: CRO Imprime Caminho Critico
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro para a cabe�a do cronograma
*
*  $ED Descri��o da fun��o
*			Imprime o Caminho Critico j� calculado pelo m�dulo
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetFaltouMemoria
*     CRO_CondRetCronogramaNaoExiste
*     CRO_NaoExisteNenhumaTarefa
*
***********************************************************************/

    CRO_tpCondRet CRO_ImprimeCaminhoCritico( tcCronograma * cCronograma);

/***********************************************************************
*
*  $FC Fun��o: CRO Altera Tarefa
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro para a cabe�a do cronograma
*     $P idTarefa - id da tarefa
*     $P novoNome - novo nome da tarefa
*     $P novaDescricao - nova descricao da tarefa
*     $P duracao - nova duracao da tarefa
*
*  $ED Descri��o da fun��o
*			Altera nome, descricao e duracao de uma tarefa com base 
*     em seu id.
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
*  $FC Fun��o: CRO Altera Recurso
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro para a cabe�a do cronograma
*     $P idTarefa - id do recurso
*     $P novoNome - novo nome do recurso
*
*  $ED Descri��o da fun��o
*			Altera  nome de um recurso com base em seu id.
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
*  $FC Fun��o: CRO Imprime Cronograma
*
*  $EP Par�metros
*     $P ctCronograma - ponteiro para a cabe�a do cronograma
*
*  $ED Descri��o da fun��o
*     Imprime o cronograma
*
*  $FV Valor retornado
*     CRO_CondRetOK
*     CRO_CondRetCronogramaNaoExiste
*     CRO_NaoExisteRecursoSuficiente
*     CRO_CronogramaVazio

***********************************************************************/

    CRO_tpCondRet CRO_ImprimeCronograma( tcCronograma * cCronograma );

#undef CRONOGRAMA_EXT

/********** Fim do m�dulo de defini��o: M�dulo cronograma **********/

#else
#endif
