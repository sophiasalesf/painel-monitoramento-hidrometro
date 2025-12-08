#ifndef PROCESSADOR_OCR_HPP
#define PROCESSADOR_OCR_HPP

#include "ProcessadorImagem.hpp"
#include <string>

class ProcessadorOCR : public ProcessadorImagem {
public:
    ProcessadorOCR(const std::string& caminho);
    ~ProcessadorOCR() = default;

private:
    std::string digitosDetectados;
    
protected:
    void carregarImagem() override;
    void preprocessar() override;
    void detectarDigitos() override;
    double interpretarValor() override;
};

#endif