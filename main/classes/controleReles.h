#ifndef conRele_h
#define conRele_h

#include "ESPAsyncWebSrv.h"

class controleReles { 
    public: // Métodos publicos da Classe 
    void estadoReles(int Reles[]); // Carrega o estado anterior dos reles
    void ligadesliga(int Rele, AsyncWebServerRequest *request, int nReles); // Função que liga ou desliga o relé e atualiza o estado no arquivo
    
    private: // Métodos privados da Classe
    void atualizarEstadoRele(int nReles, bool estadoRele); // Função para atualizar o estado do relé no arquivo
    void estadoAnterior(int nRele, int Rele[], bool estadoRele); // Fução que Liga o Rele no seu estado anterior 
};

#endif