#if ! defined( Tst_Espc_ )
#define Tst_Espc_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TSTE Interface de teste espec�fico
*
*  Arquivo gerado:              Tst_Espc.h
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo consta somente do m�dulo de defini��o de todos os m�dulos
*     de teste espec�ficos a serem desenvolvidos, e tamb�m da especifica��o
*     do tipo de condi��es de retorno deste m�dulo.
*
*     Ele estabelece a interface a ser utilizada pelo m�dulo de teste
*     gen�rico com todos os m�dulos de teste espec�fico a serem
*     desenvolvidos.
*
*     Os m�dulos de teste espec�fico devem sempre incluir este m�dulo
*     de defini��o e, idealmente, n�o devem adicionar mais itens
*     � interface.
*
*     O m�dulo de teste espec�fico cont�m a fun��o de teste de um
*     determinado m�dulo ou conjunto de m�dulos. Mais especificamente,
*     cont�m a fun��o que interpreta os comandos de teste que exercitar�o
*     as fun��es do(s) m�dulo(s) em teste.
*
*     Poder� conter tamb�m diversas fun��es auxiliares requeridas para
*     realizar os testes, vide "contexto" a seguir.
*
*     O contexto � formado por vari�veis e estruturas auxiliares necess�rias
*     para que se possa efetuar todos os comandos de teste.
*     Por exemplo pode-se desejar testar v�rias inst�ncias de uma
*     mesma estrutura. Uma forma de resolver isto � criar um vetor
*     global static
*     de n elementos em que cada elemento aponta para a cabe�a de
*     uma determinada inst�ncia dessa estrutura. Para realizar um
*     teste relativo a uma determinada inst�ncia, torna-se necess�rio
*     selecion�-la atrav�s de um �ndice contido no comando de teste.
*     Este par�metro, embora seja um �ndice, � na realidade o identificador
*     da inst�ncia da estrutura a ser manipulada (idEstrutura).
*
*     Caso o m�dulo em teste requeira um contexto, este dever� ser
*     estabelecido no presente m�dulo. Para tal devem ser declaradas
*     vari�veis e estruturas encapsuladas e devem ser inclu�dos comandos
*     de teste capazes de manipular o contexto.
*
*     Uma das formas para estabelecer o contexto seria a de incluir
*     no m�odulo de teste espec�fico comando semelhantes a:
*
*       =iniciaXXX  que inicializa o contexto do m�dulo sob teste para
*                   vazio. Este comando deve ser utilizado uma �nica vez
*                   logo ao inciar a execu��o do teste.
*       =reset      restaura o contexto para vazio. Este comando usualmente
*                   assumir� que o contexto a esvaziar esteja correto.
*                   O comando dever� liberar os espa�os alocados aos
*                   elementos, anular as refer�ncias a ele, inicializar
*                   valores de vetores de refer�ncias, etc.
*                   O comando tem utilidade especial ao segmentar um teste
*                   em partes estanques e ao controlar vazamento de
*                   mem�ria.
*       =terminaXXX este comando destr�i todo o contexto e n�o o
*                   reinicializa. O objetivo � poder verificar vazamento
*                   de mem�ria.
*
*     Evidentemente, outra forma seria a de alterar as fun��es de
*     inicializa��o e t�rmino do m�dulo de teste gen�rico o que � pouco
*     recomend�vel pois viola o princ�pio de um mesmo m�dulo gen�rico
*     servir para testar todos os construtos.
*
*     Para cada fun��o do m�dulo a ser testado deve existir pelo menos
*     um comando de teste. Em alguns casos pode ser interessante criar
*     comandos que armazenem, alterem ou consultem vari�veis de
*     estado do pr�prio m�dulo de teste. Ver os coment�rios sobre
*     contexto acima. Ou seja, podem existir comandos de teste que
*     t�m o prop�sito de agir sobre o contexto e, n�o, o de efetuar
*     um determinado teste. Alguns desses comandos podem inclusive
*     realizar verifica��es entre um resultado esperado e existente
*     no contexto.
*
*     Todos os controles de consist�ncia dos par�metros dos comandos
*     de teste devem ser realizados no m�dulo de teste espec�fico.
*     Recomenda-se que seja sempre retornado TST_CondRetParm,
*     sinalizando erro de sintaxe do comando de teste ou valores
*     n�o permitidos. Deve ser sempre assumido que os par�metros
*     podem estar em erro. Ou seja, o controle da integridade dos
*     comando � mandat�ria.
*
*     Caso seja necess�rio emitir mensagens  especiais,
*     deve ser utilizada a fun��o gen�rica "TST_ExibirPrefixo".
*     Caso seja desejado acrescentar um texto a alguma mensagem j� exibida,
*     (prefixo, ou comparar), utilize a fun��o
*        fprintf( TST_ObterArqLog( ) , "..." , ... )
*     na qual n�o deve ocorrer avan�o de linha ou nova linha ("\n" ou "\r")
*     no par�metro indicador de formato (2o. par�metro). Essa comven��o
*     assegura a consist�ncia do aspecto das mensagens com o restante do
*     programa de teste.
*
*     Cada comando deve ser completamente interpretado pelo seu
*     respectivo fragmento de interpreta��o. Ou seja, n�o dever� ser
*     retornado para o m�dulo gen�rico qualquer dado adicional �
*     condi��o de retorno da fun��o de teste espec�fico. Veja
*     "TST_ExibirPrefixo" acima, caso seja desejado adicionar detalhes
*     � mensagen j� exibida.
*
*     A fun��o TST_NotificarFalha sempre registra uma falha, enquanto que
*     a fun��o TST_ExibirPrefixo pode ser usada para emitir mensagens
*     de informa��o ou mesmo de advert�ncia. Caso a fun��o TST_ExibirPrefixo
*     seja utilizada para sinalizar uma falha, � necess�rio chamar
*     tamb�m a fun��o TST_ContarFalha( ) para que seja notificada a falha.
*     Isto n�o � necess�rio no caso da fun��o TST_NotificarFalha, pois
*     esta sempre conta falhas.
*
*     As fun��es a testar que retornem um valor sempre devem ter
*     este valor verificado, mesmo que seja uma condi��o de retorno.
*     Utilize para isto uma das fun��es " Comparar" do arcabou�o.
*     Caso uma fun��o retorne dois ou mais valores, incluindo
*     a condi��o de retorno, utilize um c�digo semelhante ao
*     descrito a seguir.
*
*     Seja
*        FuncATestar( p1, p2, p3 ... ) => v1, v2, ...
*     a fun��o a ser testada e, v1, v2, ... os dados retornados de
*     alguma forma (valor retornado, par�metro por refer�ncia, vari�vel
*     global). Assumindo que v1 seja o valor retornado.
*
*        v1Obtido = FuncATestar( ...
*        CondRet  = TST_CompararXXX( v1Obtido , v1Esperado , "mensagem 1" ) ;
*        if ( CondRet != TST_CondRetOK )
*        {
*           return CondRet ;
*        }
*
*        CondRet  = TST_CompararXXX( v2Obtido , v2Esperado , "mensagem 2" ) ;
*        if ( CondRet != TST_CondRetOK )
*        {
*           return CondRet ;
*        }
*        ...
*
*        TST_CompararXXX( vnObtido , vnEsperado , "mensagem n" ) ;
*
***************************************************************************/
 
#if defined( Tst_Espc_OWN )
   #define Tst_Espc_EXT
#else
   #define Tst_Espc_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

#define     SINALIZA_ERRO       ">>>"
#define     SINALIZA_RECUPERA   "<<<"
#define     SINALIZA_COMENTARIO "!!!"


/***********************************************************************
*
*  $TC Tipo de dados: TST Cond ret m�dulo de teste espec�fico
*
*
*  $ED Descri��o do tipo
*     Este tipo enumera todas as condi��es de retorno que podem ser
*     geradas pela fun��o de teste espec�fica.
*
***********************************************************************/

   typedef enum {

         TST_CondRetOK ,
               /* Comando de teste executou corretamente */

         TST_CondRetErro ,
               /* Comando de teste encontrou uma ou mais falhas
               *
               *$ED Descri��o
               *   Esta condi��o sinaliza que um ou mais resultados da execu��o
               *   da fun��o sob teste resultou em um valor diferente do esperado. */

         TST_CondRetParm ,
               /* Comando de teste est� com a sintaxe em erro
               *
               *$ED Descri��o
               *   A presente condi��o de retorno deve ser retornada caso a sintaxe
               *   ou os valores do comando de teste estiverem em erro.
               *
               *   Todos os fragmentos de interpreta��o devem:
               *   - realizar a an�lise dos par�metros do comando
               *   - verificar se todos os par�metros foram lidos
               *   - verificar se os valores dos par�metros est�o corretos
               *     por exemplo: verificar se os �ndices de acesso a elementos
               *     est�o dentro dos limites dos correspondentes vetores.
               *   - efetuar a fun��o a testar
               *   - verificar se os resultados retornados por esta fun��o est�o
               *     corretos */

         TST_CondRetNaoExecutou ,
               /* Comando de teste n�o se destina ao presente interpretador
               *
               *$ED Descri��o
               *   Esta condi��o deve ser retornada por todas as fun��es de interpreta��o
               *   de comandos de teste relativas a m�dulos do pr�prio arcabou�o,
               *   caso n�o tenha sido encontrado um comando v�lido. Isso permite
               *   estabelecer um "daisy chain" de interpretadores em que cada qual
               *   tenha finalidade espec�fica no contexto do arcabou�o. */

         TST_CondRetNaoConhec ,
               /* Comando de teste n�o � conhecido
               *
               *$ED Descri��o
               *   Esta condi��o deve ser retornada por todas as fun��es de interpreta��o
               *   de casos de teste espec�fico visando determinado m�dulo em teste,
               *   sempre que esse interpretador n�o consiga identificar o comando.
               *
               *   Cabe salientar a diferen�a entre TST_CondRetNaoExecutou e
               *   TST_CondRetNaoConhec. A primeira corresponde � n�o interpreta��o
               *   de um comando possivelmente v�lido em interpretadores subsequentes.
               *   A segunda corresponde a comandos n�o v�lidos considerando todos
               *   os interpretadores. */

         TST_CondRetNaoImplementado ,
               /* Comando de teste n�o implementado
               *
               *$ED Descri��o
               *   Esta condi��o deve ser retornada ao interpretar um comando de teste
               *   espec�fico ainda n�o implementado.
               *
               *   Recomenda-se que o desenvolvimento dos m�dulos sob teste e do
               *   correpondente m�dulo de teste espec�fico se d� incrementalmente.
               *   Consequentemente diversos comandos n�o estar�o implementados
               *   no in�cio do desenvolvimento. Esta incompleteza poder� ser
               *   sinalizada com esta condi��o de retorno. */

         TST_CondRetMemoria
               /* Faltou mem�ria para executar o comando
               *
               *$ED Descri��o
               *   Esta condi��o deve ser retornada caso tenha ocorrido algum erro
               *   quando o m�dulo de teste espec�fico tentar alocar mem�ria ou
               *   outro recurso. */

   } TST_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: TSTE &Efetuar comandos de teste espec�ficos
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     sendo testado.
*
*     Cada m�dulo de teste espec�fico deve desenvolver esta fun��o.
*     Poder� conter diversas outras conforme necess�rio. No entanto
*     estas devem todas ser fun��es encapsuladas no m�dulo (static)
*
*     Freq�entemente � necess�rio desenvolver um contexto para o teste.
*     Por exemplo, pode ser necess�rio tratar n elementos disponibilizados
*     pelo m�dulo sob teste. Neste caso deveria ser criado um vetor
*     global com refer�ncias para estas elemento. Ao iniciar os teste
*     este vetor dever� ser inicializado. Ao terminar, os elementos do
*     vetor referenciando algum elemento devem ser destru�dos.
*
*     Todos os controles de consist�ncia devem ser realizados no
*     m�dulo de teste espec�fico.
*
*     A fun��o TST_EfetuarComando( ) deve retornar as condi��es de retorno
*     identificadas no tipo TST_tpCondRet.
*
*     As fun��es do m�dulo sob teste que retornam algum valor sempre
*     devem sempre ter este valor verificado, mesmo sendo uma condi��o de
*     retorno. Para fazer a verefica��o da corretude, recomenda-se
*     utilizar as fun��es TST_CompararXXX definidas no m�dulo gen�rico.
*     Assegura-se assim a uniformidade da sa�da gerada durante o teste.
*
*     Para realizar a an�lise de um comando de teste recomenda-se
*     utilizar as fun��es definidas no m�dulo LerParm. Elas, al�m
*     de realizarem a an�lise l�xica, permitem o uso intercambi�vel
*     de par�metros simb�licos ou literais. Tamb�m realizam a
*     verifica��o da corretude dos tipos dos par�metros, contribuindo
*     assim para a redu��o de erros de reda��o de scripts de teste
*     que possam passar despercebidos.
*
*     As fun��es a serem testadas que requeiram algum argumento, devem
*     ser chamadas com valores (par�metros) extra�dos do comando de
*     teste sendo executado. Use sempre as fun��es do m�dulo LerParm
*     para realizar a an�lise sint�tica.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     TST_CondRetXXX       - veja a descri�c�o dos poss�veis valores
*                            retornados na especifica��o do correspondente
*                            enum
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) ;

#undef Tst_Espc_EXT

/********** Fim do m�dulo de defini��o: TSTE Interface de teste espec�fico **********/

#else
#endif
