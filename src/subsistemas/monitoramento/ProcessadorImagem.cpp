#include "../../../include/subsistemas/monitoramento/ProcessadorImagem.hpp"
#include <iostream>

ProcessadorImagem::ProcessadorImagem(const std::string& caminho)
    : caminhoImagem(caminho) {
}

double ProcessadorImagem::processar() {
    std::cout << "[PROCESSADOR] Iniciando processamento de: " 
              << caminhoImagem << std::endl;
    
    carregarImagem();
    preprocessar();
    detectarDigitos();
    double valor = interpretarValor();
    
    std::cout << "[PROCESSADOR] Processamento concluido!" << std::endl;
    
    return valor;
}