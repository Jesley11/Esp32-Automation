#ifndef conRede_h
#define conRede_h

#include "Arduino.h"

class conRede { 
    public: // Métodos publicos da Classe 
    void redeCon();

    private: // Atributos e Métodos privados da Classe
    void configIp();
    // Variáveis para armazenar as informações de configuração
    IPAddress ip;
    String ssidConfig;
    String passwordConfig;
    IPAddress gatewayConfig;
};

#endif