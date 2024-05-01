// Inclui as bibliotecas
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#include "controleReles.h"
#include "conRede.h"
#include "debug.h"

// Define os pinos para os relés
#define Rele1 13
#define Rele2 12
#define Rele3 14
#define Rele4 27
#define Rele5 26
#define Rele6 25
#define Rele7 33
#define Rele8 32

// Define os pinos para os botões
#define Botao1 35

// Cria um servidor HTTP na porta 80
AsyncWebServer server(80);

void setup() {
    // Inicializa a comunicação serial com uma taxa de 115200 bps
    Serial.begin(115200);

    // Define o LED_BUILTIN como saída
    pinMode(LED_BUILTIN, OUTPUT);

    // Configuração dos pinos como entrada para controle dos relés
    pinMode(Botao1, INPUT);

    // Configuração dos pinos como saída para controlar os relés
    pinMode(Rele1, OUTPUT);
    pinMode(Rele2, OUTPUT);
    pinMode(Rele3, OUTPUT);
    pinMode(Rele4, OUTPUT);
    pinMode(Rele5, OUTPUT);
    pinMode(Rele6, OUTPUT);
    pinMode(Rele7, OUTPUT);
    pinMode(Rele8, OUTPUT);

    // Desliga todos os relés no início
    digitalWrite(Rele1, HIGH);
    digitalWrite(Rele2, HIGH);
    digitalWrite(Rele3, HIGH);
    digitalWrite(Rele4, HIGH);
    digitalWrite(Rele5, HIGH);
    digitalWrite(Rele6, HIGH);
    digitalWrite(Rele7, HIGH);
    digitalWrite(Rele8, HIGH);

    // Inicializa o sistema de arquivos LittleFS
    if (!LittleFS.begin()) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Falha ao montar LittleFS");
        return;
    }

    // Faz a chamada da função que faz conexão com o Wifi
    redeCon();
    
    // Configuração das rotas do servidor web
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Faz a chamada da função que faz toda condiguração do site
    Site();

    // Inicializa os Relés no estado anterior
    int Reles[] = {Rele1, Rele2, Rele3, Rele4, Rele5, Rele6, Rele7, Rele8};
    estadoReles(Reles);
}

void loop() {
    // Loop principal
}

// Variavel que define o numero do rele
int nRele;

// Função que faz toda a configuração das rotas e do site
void Site() {
    // Adicione outras rotas para seus recursos, como CSS e JavaScript
    server.serveStatic("/", LittleFS, "/");
    // Verifica se a solicitação contém Rele1
    server.on("/rele1", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele1, request, nRele = 1); });
    // Verifica se a solicitação contém Rele2
    server.on("/rele2", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele2, request, nRele = 2); });
    // Verifica se a solicitação contém Rele3
    server.on("/rele3", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele3, request, nRele = 3); });
    // Verifica se a solicitação contém Rele4
    server.on("/rele4", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele4, request, nRele = 4); });
    // Verifica se a solicitação contém Rele5
    server.on("/rele5", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele5, request, nRele = 5); });
    // Verifica se a solicitação contém Rele6
    server.on("/rele6", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele6, request, nRele = 6); });
    // Verifica se a solicitação contém Rele7
    server.on("/rele7", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele7, request, nRele = 7); });
    // Verifica se a solicitação contém Rele8
    server.on("/rele8", HTTP_GET, [](AsyncWebServerRequest *request){ ligadesliga(Rele8, request, nRele = 8); });
    // Inicia o servidor
    server.begin();
    Serial.println("Servidor Iniciado");
}