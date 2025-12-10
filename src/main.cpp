#include "../include/subsistemas/fachada/Fachada.hpp"
#include "../include/subsistemas/armazenamento/ArmazenamentoConsoleStrategy.hpp"
#include "../include/subsistemas/armazenamento/ArmazenamentoArquivoStrategy.hpp"

#include <iostream>
#include <memory>
#include <iomanip>

using std::cout;
using std::endl;

int main() {
    cout << std::fixed << std::setprecision(3);

    cout << "PAINEL DE MONITORAMENTO DE HIDROMETROS\n";
    cout << "--------------------------------------\n\n";

    Fachada fachada;

    auto strategy = std::make_shared<ArmazenamentoArquivoStrategy>("dados/");

    fachada.configurarArmazenamento(strategy);

    fachada.testar();

    // Definir limite de consumo para a usuaria 12345678900
    fachada.definirLimiteConsumoUsuario("12345678900", 500.0);
    
    cout << "\n- CENARIO 2: MONITORAMENTO DE IMAGENS (OCR/SEGMENTACAO)\n"<< endl;

    double v1 = fachada.processarImagemOCR("imagens/hidrometro_001.jpg");
    cout << "Leitura via OCR: " << v1 << " m^3\n" << endl;

    double v2 = fachada.processarImagemSegmentacao("imagens/hidrometro_002.jpg");
    cout << "Leitura via Segmentacao: " << v2 << " m^3" << endl;

    // Exibir histórico de leituras do hidrômetro
    cout << "\n- CENARIO 3: HISTORICO DE LEITURAS\n"<< endl;

    fachada.listarHistoricoHidrometro("H123456");

    fachada.salvarSistema();

    return 0;
}
