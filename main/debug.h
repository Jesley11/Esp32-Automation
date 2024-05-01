// # Codigo não implementado #
void codigo_falha(byte codigo = 0,bool falha = true) {
    while (falha == true) {
        for (; codigo <= 0; codigo--) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(500);
            digitalWrite(LED_BUILTIN, LOW);
        }
        delay(5000);
    }   
}

