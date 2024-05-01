// Variáveis para armazenar as informações de configuração
IPAddress ip;
String ssidConfig;
String passwordConfig;
IPAddress gatewayConfig;

// Função que faz a leitura do Arquivo Json

void configIp() {
    // Abre o arquivo JSON em modo de leitura
    File configFile = LittleFS.open("/configWifi.json", "r");
    if (!configFile) {
        Serial.println("Falha ao abrir o arquivo JSON.");
        return;
    }

    // Tamanho máximo do arquivo JSON
    const size_t capacity = JSON_OBJECT_SIZE(4) + 100;

    // Aloca memória para o buffer JSON
    DynamicJsonDocument jsonBuffer(capacity);

    // Deserializa o JSON a partir do arquivo
    DeserializationError error = deserializeJson(jsonBuffer, configFile);

    if (error) {
        Serial.println("Falha na leitura do JSON.");
        configFile.close();
        return;
    } 

    // Obtém os valores do JSON e armazena nas variáveis
    ip.fromString(jsonBuffer["ip"].as<String>());
    ssidConfig = jsonBuffer["ssid"].as<String>();
    passwordConfig = jsonBuffer["password"].as<String>();
    gatewayConfig.fromString(jsonBuffer["gateway"].as<String>());

    // Fechar o arquivo JSON
    configFile.close();
}

void redeCon() {

    // Faz a chamada da função que coleta as informações do arquivo
    configIp();

    // Inicia o processo de conexão Wi-Fi com as credenciais fornecidas
    WiFi.begin(ssidConfig, passwordConfig);
    Serial.print("Procurando rede ...");
    digitalWrite(LED_BUILTIN, HIGH);

    // Aguarda até que a conexão Wi-Fi seja estabelecida
    while (WiFi.status() != WL_CONNECTED) {
        // Acende o LED embutido para indicar que ainda está procurando a rede
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);  // Aguarda meio segundo antes de verificar o status novamente
        Serial.print(".");
    }

    // Desliga o LED embutido quando a conexão Wi-Fi é estabelecida
    digitalWrite(LED_BUILTIN, LOW);

    // Configuração do endereço IP fixo
    IPAddress local_IP = ip;            // Use o endereço IP configurado no arquivo JSON
    IPAddress gateway = gateway;        // Use o gateway configurado no arquivo JSON
    IPAddress subnet(255, 255, 255, 0); // Máscara de sub-rede

    // Configura o endereço IP local
    if (!WiFi.config(local_IP, gateway, subnet)) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Falha ao configurar o endereço IP fixo.");
    } else {
        Serial.println("Endereço IP configurado com sucesso: " + local_IP.toString());
    }
}
