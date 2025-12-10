#include "../../../include/subsistemas/monitoramento/ProcessadorOCR.hpp"
#include <iostream>

ProcessadorOCR::ProcessadorOCR(const std::string& caminho)
    : ProcessadorImagem(caminho) {
}

void ProcessadorOCR::carregarImagem() {}

void ProcessadorOCR::preprocessar() {}

void ProcessadorOCR::detectarDigitos() {
    digitosDetectados = "00456789";
}

double ProcessadorOCR::interpretarValor() {
    return 456.789;
}