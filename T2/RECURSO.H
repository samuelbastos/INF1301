#if ! defined( RECURSO_ )
#define RECURSO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo recurso
*
*  Arquivo gerado:              RECURSO.H
*  Letras identificadoras:      REC
*
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mv - Mauricio Pedro Silva Gonçalves Vieira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   mv   01/05/2017 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar, alterar
*	  consultar e destruir estruturas do tipo Recurso
*     A árvore possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     A cada momento o módulo admite no máximo uma única árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     A árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*
***************************************************************************/
 
#if defined( RECURSO_OWN )
   #define RECURSO_EXT
#else
   #define RECURSO_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: REC Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

		REC_CondRetOK = 0 ,
			/* Executou correto */

		REC_CondRetFaltouMemoria = 1,
			/* Faltou memória ao alocar dados */

		REC_CondRetRecursoNaoExiste = 2,
			/* O recurso não existe */

		REC_CondRetNomeInvalido = 3
			/* O nome é invalido */

   } REC_tpCondRet ;
   

   /***********************************************************************
   *
   *  $TC Tipo de dados: REC ponteiro para um Recurso
   *
   *
   ***********************************************************************/

   typedef struct tgRecurso tpRecurso;


/***********************************************************************
*
*  $FC Função: REC Criar árvore
*
*  $ED Descrição da função
*     Cria uma instância do tipo Recurso
*
*  $EP Parâmetros
*     $P ptRecurso - ponteiro que vai armazenar o recurso que foi criado
*	  $P novoNome - nome que deverá ser colocado dentro do recurso
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*	  REC_CondRetNomeInvalido
*
***********************************************************************/

   REC_tpCondRet REC_CriarRecurso(tpRecurso ** ptRecurso, char * novoNome) ;


/***********************************************************************
*
*  $FC Função: ARV Destruir recurso
*
*  $ED Descrição da função
*     Destroi o recurso liberando a memoria alocada para a variavel nome
*	  e depois a memoria alocada pro resto da estrutura
*
***********************************************************************/

   void REC_DestruirRecurso( tpRecurso ** ptRecurso ) ;


/***********************************************************************
*
*  $FC Função: REC Alterar nome do recurso
*
*  $EP Parâmetros
*	  $P ptRecurso - Recurso que terá o nome alterado
*	  $P novoNome - nome que deverá ser colocado dentro do recurso no lugar
*					do nome atual
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*	  REC_CondRetRecursoNaoExiste
*	  REC_CondRetNomeInvalido
*
***********************************************************************/

   REC_tpCondRet REC_AlterarNome(tpRecurso * ptRecurso, char * novoNome);


/***********************************************************************
*
*  $FC Função: REC Marca o recurso como ocupado
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será marcada como ocupada
*
*  $FV Valor retornado
*     REC_CondRetOK
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_MarcarComoOcupada(tpRecurso * ptRecurso);


/***********************************************************************
*
*  $FC Função: REC Marca recurso como disponível
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será marcada como disponível
*
*  $FV Valor retornado
*     REC_CondRetOK
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_MarcarComoDisponivel(tpRecurso * ptRecurso);


/***********************************************************************
*
*  $FC Função: REC Consulta o Id do recurso
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será consultada
*
*  $FV Valor retornado
*     REC_CondRetOK
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_ConsultarId(tpRecurso * ptRecurso, int * id);


/***********************************************************************
*
*  $FC Função: REC Consulta o nome do recurso
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será consultada
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_ConsultarNome(tpRecurso * ptRecurso, char * nome);


/***********************************************************************
*
*  $FC Função: REC Consulta a disponibilidade do Recurso
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será consultada
*
*  $FV Valor retornado
*     REC_CondRetOK
*	  REC_CondRetRecursoNaoExiste
*
***********************************************************************/

   REC_tpCondRet REC_ConsultarDisponibilidade(tpRecurso * ptRecurso, int * estaDisponivel);

#undef RECURSO_EXT

/********** Fim do módulo de definição: Módulo recurso **********/

#else
#endif
