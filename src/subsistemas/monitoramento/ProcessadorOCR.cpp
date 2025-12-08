#include "../../../include/subsistemas/monitoramento/ProcessadorOCR.hpp"
#include <iostream>

ProcessadorOCR::ProcessadorOCR(const std::string& caminho)
    : ProcessadorImagem(caminho) {
}

void ProcessadorOCR::carregarImagem() {
    std::cout << "[OCR] Carregando imagem..." << std::endl;
}

void ProcessadorOCR::preprocessar() {
    std::cout << "[OCR] Aplicando filtros e ajustes de contraste..." << std::endl;
}

void ProcessadorOCR::detectarDigitos() {
    std::cout << "[OCR] Detectando digitos com OCR..." << std::endl;
    digitosDetectados = "00456789";
}

double ProcessadorOCR::interpretarValor() {
    std::cout << "[OCR] Interpretando valor: " 
              << digitosDetectados << std::endl;
    return 456.789; 
}