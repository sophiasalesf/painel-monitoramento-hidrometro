#ifndef PROCESSADOR_SEGMENTACAO_HPP
#define PROCESSADOR_SEGMENTACAO_HPP

#include "ProcessadorImagem.hpp"
#include <vector>

class ProcessadorSegmentacao : public ProcessadorImagem {
public:
    ProcessadorSegmentacao(const std::string& caminho);
    ~ProcessadorSegmentacao() = default;

private:
    std::vector<int> segmentosDetectados;
    
protected:
    void carregarImagem() override;
    void preprocessar() override;
    void detectarDigitos() override;
    double interpretarValor() override;
};

#endif
