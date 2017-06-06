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
*     O recurso possui uma cabeça que contém uma referência para a estrutura recurso
*     O módulo admite a criação de mais de um recurso
*     Ao iniciar a execução do programa não existe recurso.
*     Se a cabeça de um recurso existir o ponteiro recurso dessa estrutura de cabeça
*	  necessariamente precisa apontar para uma estrutura Recurso diferente de NULL
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

        REC_CondRetRecursoNaoExiste = 1,
            /* O recurso não existe */

        REC_CondRetNomeInvalido = 2,
            /* O nome é invalido */

        REC_CondRetFaltouMemoria = 3
            /* Faltou memória ao alocar dados */

    } REC_tpCondRet ;
   

/***********************************************************************
*
*  $TC Tipo de dados: REC cabeça de uma estrutura de recurso
*
*
***********************************************************************/

   typedef struct tcRecurso tcRecurso;


/***********************************************************************
*
*  $FC Função: REC Criar recurso
*
*  $ED Descrição da função
*     Cria uma instância do tipo Recurso
*
*  $EP Parâmetros
*     $P ptRecurso - ponteiro que vai armazenar o recurso que foi criado
*	    $P novoNome - nome que deverá ser colocado dentro do recurso
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*			REC_CondRetNomeInvalido
*
***********************************************************************/

    REC_tpCondRet REC_CriarRecurso(tcRecurso ** ptRecurso, char * novoNome) ;


/***********************************************************************
*
*  $FC Função: REC Destruir recurso
*
*  $ED Descrição da função
*     Destroi o recurso liberando a memoria alocada para a variavel nome
*	    e depois a memoria alocada pro resto da estrutura
*
***********************************************************************/

    void REC_DestruirRecurso( tcRecurso ** ptRecurso ) ;


/***********************************************************************
*
*  $FC Função: REC Alterar nome do recurso
*
*  $EP Parâmetros
*	    $P ptRecurso  - Recurso que terá o nome alterado
*	    $P novoNome   - nome que deverá ser colocado dentro do recurso no lugar
*					            do nome atual
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*	    REC_CondRetRecursoNaoExiste
*	    REC_CondRetNomeInvalido
*
***********************************************************************/

    REC_tpCondRet REC_AlterarNome(tcRecurso * ptRecurso, char * novoNome);


/***********************************************************************
*
*  $FC Função: REC Marca o recurso como ocupado
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será marcada como ocupada
*
*  $FV Valor retornado
*     REC_CondRetOK
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

    REC_tpCondRet REC_MarcarComoOcupada(tcRecurso * ptRecurso);


/***********************************************************************
*
*  $FC Função: REC Marca recurso como disponível
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será marcada como disponível
*
*  $FV Valor retornado
*     REC_CondRetOK
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

    REC_tpCondRet REC_MarcarComoDisponivel(tcRecurso * ptRecurso);


/***********************************************************************
*
*  $FC Função: REC Consulta o Id do recurso
*
*  $EP Parâmetros
*     $P ptRecurso   - Recurso que será consultada
*	    $P id          - ponteiro para o local de memoria onde o id do 
*			                 recurso será armazenado para consulta externa
*
*  $FV Valor retornado
*     REC_CondRetOK
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

    REC_tpCondRet REC_ConsultarId(tcRecurso * ptRecurso, int * id);


/***********************************************************************
*
*  $FC Função: REC Consulta o nome do recurso
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será consultada
*	    $P pNome     - ponteiro para o local de memoria onde o nome do recurso 
*				             será armazenado para consulta externa
*
*  $FV Valor retornado
*     REC_CondRetOK
*     REC_CondRetFaltouMemoria
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

    REC_tpCondRet REC_ConsultarNome(tcRecurso * ptRecurso, char ** pNome);


/***********************************************************************
*
*  $FC Função: REC Consulta a disponibilidade do Recurso
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que será consultada
*	    $P id        - ponteiro para o local de memoria onde a disponibilidade do 
*			               recurso será armazenada para consulta externa
*
*  $FV Valor retornado
*     REC_CondRetOK
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

    REC_tpCondRet REC_ConsultarDisponibilidade(tcRecurso * ptRecurso, int * estaDisponivel);

/***********************************************************************
*
*  $FC Função: REC Imprime informações do Recurso
*
*  $EP Parâmetros
*     $P ptRecurso - Recurso que terá suas informações impressas
*
*  $FV Valor retornado
*     REC_CondRetOK
*	    REC_CondRetRecursoNaoExiste
*
***********************************************************************/

    REC_tpCondRet REC_ImprimeRecurso(tcRecurso * ptRecurso);

#undef RECURSO_EXT

/********** Fim do módulo de definição: Módulo recurso **********/

#else
#endif
