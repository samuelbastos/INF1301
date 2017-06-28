/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: avs Arndt Von Staa
*			      mv  Maurício Vieira
*           sb  Samuel Bastos
* 
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

    typedef struct tagElemLista {

        void * pValor ;
            /* Ponteiro para o valor contido no elemento */

        struct tagElemLista * pAnt ;
            /* Ponteiro para o elemento predecessor */

        struct tagElemLista * pProx ;
            /* Ponteiro para o elemento sucessor */

        #ifdef _DEBUG
            int tipo;
                /* tipo do dado armazenado no elemento */

            int tamanho;
                /* tamanho de memoria utilizado pelo elemento */
            
            struct LIS_tagLista * pCabeca;
                /* Ponteiro para a cabeça da lista */
        #endif

    } tpElemLista ;

    /***********************************************************************
    *
    *  $TC Tipo de dados: LIS Descritor da cabeça de lista
    *
    *
    ***********************************************************************/

    typedef struct LIS_tagLista {

        tpElemLista * pOrigemLista ;
            /* Ponteiro para a origem da lista */

        tpElemLista * pFimLista ;
            /* Ponteiro para o final da lista */

        tpElemLista * pElemCorr ;
            /* Ponteiro para o elemento corrente da lista */

        int numElem ;
            /* Número de elementos da lista */

        void ( * ExcluirValor ) ( void * pValor ) ;
            /* Ponteiro para a função de destruição do valor contido em um elemento */

        #ifdef _DEBUG
            int tipo;
                /* tipo do dado armazenado no elemento */

            int tamElementos;
                /* tamanho total de memoria utilizado pelos elementos da lista */
        #endif

    } LIS_tpLista ;

    /***** Protótipos das funções encapuladas no módulo *****/

    static void LiberarElemento( LIS_tppLista   pLista ,
                                 tpElemLista  * pElem   ) ;

    static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                        void *       pValor  ) ;

    static void LimparCabeca( LIS_tppLista pLista ) ;

    /*****  Código das funções exportadas pelo módulo  *****/

    /***************************************************************************
    *
    *  Função: LIS  &Criar lista
    *  ****/

    LIS_tppLista LIS_CriarLista(
                void   ( * ExcluirValor ) ( void * pDado ) )
    {

        LIS_tpLista * pLista = NULL ;

        pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
        if ( pLista == NULL )
        {
            return NULL ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_CriarLista");
        #endif

        LimparCabeca( pLista ) ;

        pLista->ExcluirValor = ExcluirValor ;
        
        #ifdef _DEBUG
            CED_MarcarEspacoAtivo(pLista);
            CED_DefinirTipoEspaco(pLista, LIS_IdCabecaLista);
            pLista->tamElementos = 0;
            pLista->tipo = LIS_IdTipoNaoDefinido;
        #endif

        return pLista ;

    } /* Fim função: LIS  &Criar lista */

    /***************************************************************************
    *
    *  Função: LIS  &Destruir lista
    *  ****/

    void LIS_DestruirLista( LIS_tppLista pLista )
    {
        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        #ifdef _DEBUG
            CNT_CONTAR("LIS_DestruirLista");
        #endif

        LIS_EsvaziarLista( pLista ) ;

        free( pLista ) ;

    } /* Fim função: LIS  &Destruir lista */

    /***************************************************************************
    *
    *  Função: LIS  &Esvaziar lista
    *  ****/

    void LIS_EsvaziarLista( LIS_tppLista pLista )
    {

        tpElemLista * pElem ;
        tpElemLista * pProx ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        pElem = pLista->pOrigemLista ;
        while ( pElem != NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_EsvaziarLista-while0");
            #endif

            pProx = pElem->pProx ;
            LiberarElemento( pLista , pElem ) ;
            pElem = pProx ;
        } /* while */

        LimparCabeca( pLista ) ;

    } /* Fim função: LIS  &Esvaziar lista */

    /***************************************************************************
    *
    *  Função: LIS  &Inserir elemento antes
    *  ****/

    LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                            void * pValor        )
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        /* Criar elemento a inerir antes */

        pElem = CriarElemento( pLista , pValor ) ;
        if ( pElem == NULL )
        {
            return LIS_CondRetFaltouMemoria ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_InserirElementoAntes");
            pElem->pCabeca = pLista;
            pElem->tamanho = CED_ObterTamanhoValor(pValor);
            pElem->tipo = CED_ObterTipoEspaco(pValor);

            pLista->tamElementos += pElem->tamanho + CED_ObterTamanhoValor(pElem);
        #endif

        /* Encadear o elemento antes do elemento corrente */

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoAntes-if0");
            #endif

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;

            #ifdef _DEBUG
                pLista->tipo = pElem->tipo;
            #endif
            
        } else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoAntes-else0");
            #endif

            if ( pLista->pElemCorr->pAnt != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoAntes-if1");
                #endif

                pElem->pAnt  = pLista->pElemCorr->pAnt ;
                pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoAntes-else1");
                #endif

                pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
        } /* if */

        pLista->pElemCorr = pElem ;

        return LIS_CondRetOK ;

    } /* Fim função: LIS  &Inserir elemento antes */

    /***************************************************************************
    *
    *  Função: LIS  &Inserir elemento após
    *  ****/

    LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                           void * pValor        )
      
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        /* Criar elemento a inerir após */

        pElem = CriarElemento( pLista , pValor ) ;
        if ( pElem == NULL )
        {
            return LIS_CondRetFaltouMemoria ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_InserirElementoApos");
            pElem->pCabeca = pLista;
            pElem->tamanho = CED_ObterTamanhoValor(pElem);
            pElem->tipo = CED_ObterTipoEspaco(pElem);

            pLista->tamElementos += pElem->tamanho + CED_ObterTamanhoValor(pElem);
        #endif
        /* Encadear o elemento após o elemento */

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoApos-if0");
            #endif

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
            #ifdef _DEBUG
                pLista->tipo = pElem->tipo;
            #endif
        } else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoApos-else0");
            #endif

            if ( pLista->pElemCorr->pProx != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoApos-if1");
                #endif

                pElem->pProx  = pLista->pElemCorr->pProx ;
                pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoApos-else1");
                #endif

                pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

        } /* if */
                  
        pLista->pElemCorr = pElem ;
                  
        return LIS_CondRetOK ;

    } /* Fim função: LIS  &Inserir elemento após */

    /***************************************************************************
    *
    *  Função: LIS  &Excluir elemento
    *  ****/

    LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista  != NULL ) ;
        #endif

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-if0");
            #endif

            return LIS_CondRetListaVazia ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ExcluirElemento-sq0");
        #endif

        pElem = pLista->pElemCorr ;

        /* Desencadeia à esquerda */

        if ( pElem->pAnt != NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-if1");
            #endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
        } else {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-else1");
            #endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;

        } /* if */

        /* Desencadeia à direita */

        if ( pElem->pProx != NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-if2");
            #endif
            pElem->pProx->pAnt = pElem->pAnt ;
        } else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-else2");
            #endif
            pLista->pFimLista = pElem->pAnt ;
        } /* if */

        LiberarElemento( pLista , pElem ) ;

        #ifdef _DEBUG
            if (LIS_VerificarVazia(pLista) == LIS_CondRetListaVazia)
                pLista->tipo = LIS_IdTipoNaoDefinido;
            else
                pLista->tipo = pLista->pOrigemLista->tipo;
        #endif


        return LIS_CondRetOK ;

    } /* Fim função: LIS  &Excluir elemento */

    /***************************************************************************
    *
    *  Função: LIS  &Obter referência para o valor contido no elemento
    *  ****/

    void * LIS_ObterValor( LIS_tppLista pLista )
    {

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        if ( pLista->pElemCorr == NULL )
        {        
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ObterValor-if0");
            #endif
            return NULL ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ObterValor-sq0");
        #endif

        return pLista->pElemCorr->pValor ;

    } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

    /***************************************************************************
    *
    *  Função: LIS  &Ir para o elemento inicial
    *  ****/

    void IrInicioLista( LIS_tppLista pLista )
    {

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        #ifdef _DEBUG
            CNT_CONTAR("LIS_IrInicioLista");
        #endif

        pLista->pElemCorr = pLista->pOrigemLista ;

    } /* Fim função: LIS  &Ir para o elemento inicial */

    /***************************************************************************
    *
    *  Função: LIS  &Ir para o elemento final
    *  ****/

    void IrFinalLista( LIS_tppLista pLista )
    {

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        #ifdef _DEBUG
            CNT_CONTAR("LIS_IrFinalLista");
        #endif

        pLista->pElemCorr = pLista->pFimLista ;

    } /* Fim função: LIS  &Ir para o elemento final */

    /***************************************************************************
    *
    *  Função: LIS  &Avançar elemento
    *  ****/

    LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                               int numElem )
    {
        int i ;

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        /* Tratar lista vazia */

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-if0");
            #endif
            return LIS_CondRetListaVazia ;

        } /* fim ativa: Tratar lista vazia */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_AvancarElementoCorrente-sq0");
        #endif

        /* Tratar avançar para frente */

        if ( numElem > 0 )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-if1");
            #endif
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-if1-for0");
                #endif
                if ( pElem == NULL )
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_AvancarElementoCorrente-if1-for0-if0");
                    #endif
                    break ;
                } /* if */

                pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-if1-if0");
                #endif
                pLista->pElemCorr = pElem ;
                return LIS_CondRetOK ;
            } /* if */

            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-if1-sq0");
            #endif

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

        } /* fim ativa: Tratar avançar para frente */

        /* Tratar avançar para trás */

        else if ( numElem < 0 )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1");
            #endif
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-for0");
                #endif
                if ( pElem == NULL )
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-for0-if0");
                    #endif
                    break ;
                } /* if */

                pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-if0");
                #endif
                pLista->pElemCorr = pElem ;
                return LIS_CondRetOK ;
            } /* if */

            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-sq0");
            #endif

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

        } /* fim ativa: Tratar avançar para trás */

        /* Tratar não avançar */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_AvancarElementoCorrente-sq1");
        #endif

        return LIS_CondRetOK ;

    } /* Fim função: LIS  &Avançar elemento */

    /***************************************************************************
    *
    *  Função: LIS  &Procurar elemento contendo valor
    *  ****/

    LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                     void * pValor        )
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista  != NULL ) ;
        #endif

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ProcurarValor-if0");
            #endif
            return LIS_CondRetListaVazia ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ProcurarValor-sq0");
        #endif

        for ( pElem  = pLista->pElemCorr ;
              pElem != NULL ;
              pElem  = pElem->pProx )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ProcurarValor-for0");
            #endif

            if ( pElem->pValor == pValor )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_ProcurarValor-for0-if0");
                #endif

                pLista->pElemCorr = pElem ;
                return LIS_CondRetOK ;
            } /* if */
        } /* for */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ProcurarValor-sq1");
        #endif

        return LIS_CondRetNaoAchou ;

    } /* Fim função: LIS  &Procurar elemento contendo valor */

    /***************************************************************************
    *
    *  Função: LIS  &Verificar Vazia
    *  ****/

    LIS_tpCondRet LIS_VerificarVazia( LIS_tppLista pLista ) 
    {
        if (pLista->numElem == 0)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarVazia-if0");
            #endif
            return LIS_CondRetListaVazia;
        }
        else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarVazia-else0");
            #endif
            return LIS_CondRetHaElemento;
        }
    } /* Fim função: LIS  &Verificar Vazia */

    /***************************************************************************
    *
    *  Função: LIS  &Adiciona ao Final
    *  ****/

    LIS_tpCondRet LIS_InserirElementoFinal( LIS_tppLista pLista,	void * pValor  )
    {
        #ifdef _DEBUG
            CNT_CONTAR("LIS_InserirElementoFinal");
        #endif
        IrFinalLista(pLista);
        return LIS_InserirElementoApos(pLista, pValor);

    } /* Fim função: LIS  LIS  &Adiciona ao Final */

    #ifdef _DEBUG

    /***************************************************************************
    *
    *  Função: LIS  &LIS Verificar estrutura
    *  ****/

    LIS_tpCondRet LIS_VerificarEstrutura( LIS_tppLista pLista, int * numErros )
    {
        // Checa se o tamanho da lista esta correto
        int tamanhoRealLista = 0;
        LIS_tpCondRet fimLista = LIS_CondRetOK;

        IrInicioLista(pLista);
        if (pLista->pOrigemLista != NULL)
        {
            while ( fimLista != LIS_CondRetFimLista)
            {
                tamanhoRealLista += pLista->pElemCorr->tamanho + CED_ObterTamanhoValor(pLista->pElemCorr);
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }
        if (tamanhoRealLista != pLista->tamElementos)
            (*numErros)++;

        // Testa se a lista esta perfeitamente conexa
        IrInicioLista(pLista);
        fimLista = LIS_CondRetOK;
        if (pLista->pOrigemLista != NULL)
        {
            while ( fimLista == LIS_CondRetFimLista)
            {
                if (pLista->pElemCorr->pAnt != NULL)
                {
                    if (pLista->pElemCorr->pAnt->pProx != pLista->pElemCorr)
                        (*numErros)++;
                }
                if (pLista->pElemCorr->pProx != NULL)
                {
                    if (pLista->pElemCorr->pProx->pAnt != pLista->pElemCorr)
                        (*numErros)++;
                }
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }

        // Testa se todos os nos dizem ser do mesmo tipo do cabeca
        if (pLista->pOrigemLista != NULL)
        {
            IrInicioLista(pLista);
            fimLista = LIS_CondRetOK;
            while ( fimLista == LIS_CondRetFimLista)
            {
                if ( pLista->pElemCorr->tipo != pLista->tipo )
                    (*numErros)++;
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }
        else
        {
            if (pLista->tipo != LIS_IdTipoNaoDefinido)
            {
                (*numErros)++;
            }
        }

        // Testar se todos os nos possuem o mesmo tipo dos dados que armazenam
        if (pLista->pOrigemLista != NULL)
        {
            IrInicioLista(pLista);
            fimLista = LIS_CondRetOK;
            while ( fimLista == LIS_CondRetFimLista)
            {
                if ( pLista->pElemCorr->tipo != CED_ObterTipoEspaco(pLista->pElemCorr->pValor))
                    (*numErros)++;
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }
    }

    /***************************************************************************
    *
    *  Função: LIS  &LIS Deturpar estrutura
    *  ****/

    LIS_tpCondRet LIS_Deturpar( LIS_tppLista pLista, int flag )
    {
    //todo
    }

    #endif

    /*****  Código das funções encapsuladas no módulo  *****/


    /***********************************************************************
    *
    *  $FC Função: LIS  -Liberar elemento da lista
    *
    *  $ED Descrição da função
    *     Elimina os espaços apontados pelo valor do elemento e o
    *     próprio elemento.
    *
    ***********************************************************************/

    void LiberarElemento( LIS_tppLista   pLista ,
    tpElemLista  * pElem   )
    {
        #ifdef _DEBUG
            pLista->tamElementos -= pElem->tamanho;
            pLista->tamElementos -= CED_ObterTamanhoValor(pElem);
        #endif

        if ( ( pLista->ExcluirValor != NULL )
          && ( pElem->pValor != NULL        ))
        {
            #ifdef _DEBUG
                CNT_CONTAR("LiberarElemento-if0");
            #endif
            pLista->ExcluirValor( pElem->pValor ) ;
        } /* if */

        #ifdef _DEBUG
                CNT_CONTAR("LiberarElemento-pr0");
        #endif

        free( pElem ) ;

        pLista->numElem-- ;


    } /* Fim função: LIS  -Liberar elemento da lista */


    /***********************************************************************
    *
    *  $FC Função: LIS  -Criar o elemento
    *
    ***********************************************************************/

    tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                 void *       pValor  )
    {

        tpElemLista * pElem ;

        pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
        if ( pElem == NULL )
        {
            return NULL ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("CriarElemento");
            CED_MarcarEspacoAtivo(pElem);
            CED_DefinirTipoEspaco(pElem, LIS_IdNoLista);
        #endif

        pElem->pValor = pValor ;
        pElem->pAnt   = NULL  ;
        pElem->pProx  = NULL  ;

        pLista->numElem ++ ;

        return pElem ;

    } /* Fim função: LIS  -Criar o elemento */


    /***********************************************************************
    *
    *  $FC Função: LIS  -Limpar a cabeça da lista
    *
    ***********************************************************************/

    void LimparCabeca( LIS_tppLista pLista )
    {
        #ifdef _DEBUG
            CNT_CONTAR("LimparCabeca");
            pLista->tamElementos = 0;
            pLista->tipo = LIS_IdTipoNaoDefinido;
        #endif
        pLista->pOrigemLista = NULL ;
        pLista->pFimLista = NULL ;
        pLista->pElemCorr = NULL ;
        pLista->numElem   = 0 ;

    } /* Fim função: LIS  -Limpar a cabeça da lista */

    /********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

