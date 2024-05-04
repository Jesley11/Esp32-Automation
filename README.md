# Esp32 Automation

Esp32 Automation é um aplicativo de automação residencial programado em C++ para a placa ESP32. Ele inicia um servidor HTTP com um site onde você pode controlar relés.

## Funcionalidades

- **Automação Residencial**: Controle os dispositivos da sua casa.
- **Interface Web**: Acesse o servidor HTTP embutido na placa ESP32 para controlar os dispositivos através de um site.
- **App Mobile**: App mobile que permite o controle dos réles: [Project_Alice](https://github.com/Jesley11/Project_Alice)

## Requisitos

- Placa ESP32

## Dependências

- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [LittleFS](https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#uploading-files-to-file-system)
- [ArduinoJson](https://arduinojson.org/)
- [WiFi](https://www.arduino.cc/en/Reference/WiFi)

## Como Usar

1. Clone o repositório:

   ```
   git clone https://github.com/Jesley11/Esp32-Automation.git
   ```

2. Abra o projeto na IDE do Arduino.

3. Defina os pinos que serão utilizados na sua placa ESP32 no arquivo `Main.ino`:

   ```cpp
    #define Rele1 13
    #define Rele2 12
    #define Rele3 14
   ```

4. Configure sua rede Wi-Fi no arquivo `main/data/configWifi.json`:

   ```json
    "ip": "Ip Para o Esp32",
    "ssid": "Nome Wifi",
    "password": "Senha Wifi",
    "gateway": "192.168.0.1"
   ```

5. Carregue os arquivos de configuração usando o LittleFS pela Arduino IDE:

   - Baixe e instale o [ESP32 filesystem uploader](https://github.com/me-no-dev/arduino-esp32fs-plugin) na sua IDE do Arduino.
   - No Arduino IDE, vá em **Ferramentas > ESP32 Sketch Data Upload** para carregar os arquivos de configuração para o ESP32.
   

6. Compile e carregue o código na sua placa ESP32.

7. Abra um navegador web e digite o endereço IP configurado no arquivo `configWifi.json`.

8. Conectado a interface web você pode controlar os dispositivos em cada cômodo.

## Contribuindo

Contribuições são bem-vindas! Se você quiser melhorar o projeto, sinta-se à vontade para enviar um pull request.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
