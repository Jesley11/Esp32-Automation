// Função para atualizar o estado do relé no arquivo
void atualizarEstadoRele(int nReles, bool estadoRele) {
    // Abre o arquivo "estado_reles.json" em modo de leitura e gravação
    File arquivo = LittleFS.open("/estado_reles.json", "r+");

    if (!arquivo) {
        // Lida com erros, como o arquivo não encontrado
        Serial.println("Falha ao abrir o arquivo");
        return;
    }

    // Parse o arquivo JSON
    DynamicJsonDocument jsonDocument(200);
    DeserializationError error = deserializeJson(jsonDocument, arquivo);

    if (error) {
        // Lida com erros de parsing
        Serial.println("Falha ao analisar o arquivo JSON");
        arquivo.close();
        return;
    }

    // Verifica se a linha a ser atualizada é válida
    String chave = "Rele" + String(nReles);
    if (jsonDocument.containsKey(chave)) {
        // Atualiza o estado da linha correspondente com base no estado do relé
        jsonDocument[chave] = estadoRele;

        // Fecha o arquivo JSON
        arquivo.close();

        // Abre o arquivo novamente em modo de gravação
        arquivo = LittleFS.open("/estado_reles.json", "w");
        if (!arquivo) {
            // Lida com erros, se ocorrerem
            Serial.println("Falha ao abrir o arquivo para escrita");
            return;
        }

        // Serialize o objeto JSON atualizado em uma string
        String jsonStr;
        serializeJson(jsonDocument, jsonStr);

        // Escreve a string JSON no arquivo
        arquivo.println(jsonStr);

        // Fecha o arquivo após a escrita
        arquivo.close();
    } else {
        // Caso a linha especificada não seja válida, lida com o erro
        Serial.println("Número de relé inválido");
        arquivo.close();
    }
}

// Função que liga ou desliga o relé e atualiza o estado no arquivo
void ligadesliga(int Rele, AsyncWebServerRequest *request, int nReles) {
    // Verifica se o relé está ligado (LOW) ou desligado (HIGH)
    if (digitalRead(Rele) == HIGH) {
        digitalWrite(Rele, LOW); // Liga o relé (LOW)
        atualizarEstadoRele(nReles, true); // Atualiza o estado para "Ligado" no arquivo
        request->send(200, "text/plain", "Rele Ligado"); // Resposta indicando que o relé foi ligado
    } else {
        digitalWrite(Rele, HIGH); // Desliga o relé (HIGH)
        atualizarEstadoRele(nReles, false); // Atualiza o estado para "Desligado" no arquivo
        request->send(200, "text/plain", "Rele Desligado"); // Resposta indicando que o relé foi desligado
    }
}

// Fução que Liga o Rele no seu estado anterior 
void estadoAnterior(int nRele, int Rele[], bool estadoRele) {
    if (estadoRele == true) {
        digitalWrite(Rele[nRele - 1], LOW); // Liga o Relé (LOW)

    } else {
        digitalWrite(Rele[nRele - 1], HIGH); // Desliga o Relé (HIGH)
    }
}

//Carrega o estado anterior dos reles
void estadoReles(int Reles[]) {
    // Abre o arquivo "estado_reles.json" em modo de leitura e gravação
    File arquivo = LittleFS.open("/estado_reles.json", "r");

    if (!arquivo) {
        // Lida com erros, como o arquivo não encontrado
        Serial.println("Falha ao abrir o arquivo");
        return;
    }

    // Crie um objeto JSON para representar o estado dos relés
    StaticJsonDocument<200> jsonDocument;

    // Analise o conteúdo do arquivo JSON
    DeserializationError error = deserializeJson(jsonDocument, arquivo);
    if (error) {
        // Lida com erros durante a análise do JSON
        Serial.print("Erro durante a análise do JSON: ");
        Serial.println(error.c_str());
        arquivo.close(); // Fecha o arquivo
        return;
    }

    // Preencha o objeto JSON com os estados iniciais dos relés
    for (int i = 1; i <= 8; i++) {
        String chave = "Rele" + String(i);
        bool estadoRele = jsonDocument[chave]; // Armazena o estado do rele conforme o Json
        if (estadoRele == true) {
        Serial.println(chave + ": Ligado"); // Aviso caso o relé estivese ligado
        estadoAnterior(i, Reles, estadoRele); // Faz a chamada da função para ligar o relé
        } else {
        Serial.println(chave + ": Desligado"); // Aviso caso o relé estivese desligado
        estadoAnterior(i, Reles, estadoRele); // Faz a chamada da função para desligar o relé
        }
    }
    arquivo.close(); // Fecha o arquivo
}