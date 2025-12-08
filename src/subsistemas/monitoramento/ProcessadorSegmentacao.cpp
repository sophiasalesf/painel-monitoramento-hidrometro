#include "../../../include/subsistemas/monitoramento/ProcessadorSegmentacao.hpp"
#include <iostream>

ProcessadorSegmentacao::ProcessadorSegmentacao(const std::string& caminho)
    : ProcessadorImagem(caminho) {
}

void ProcessadorSegmentacao::carregarImagem() {
    std::cout << "[SEGMENTACAO] Carregando imagem..." << std::endl;
}

void ProcessadorSegmentacao::preprocessar() {
    std::cout << "[SEGMENTACAO] Aplicando limiarizacao e deteccao de bordas..." 
              << std::endl;
}

void ProcessadorSegmentacao::detectarDigitos() {
    std::cout << "[SEGMENTACAO] Segmentando regioes de digitos..." << std::endl;
    segmentosDetectados = {9, 8, 7, 6, 5, 4}; 
}

double ProcessadorSegmentacao::interpretarValor() {
    std::cout << "[SEGMENTACAO] Interpretando segmentos detectados..." 
              << std::endl;
    return 987.654; 
}
