#include "../../../include/subsistemas/monitoramento/ProcessadorSegmentacao.hpp"
#include <iostream>

using std::cout;
using std::endl;

ProcessadorSegmentacao::ProcessadorSegmentacao(const std::string& caminho)
    : ProcessadorImagem(caminho) {
}

void ProcessadorSegmentacao::carregarImagem() {}

void ProcessadorSegmentacao::preprocessar() {}

void ProcessadorSegmentacao::detectarDigitos() {
    segmentosDetectados = {9, 8, 7, 6, 5, 4};
}

double ProcessadorSegmentacao::interpretarValor() {
    return 987.654;
}