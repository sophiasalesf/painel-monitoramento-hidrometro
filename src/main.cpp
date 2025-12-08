#include "../include/subsistemas/fachada/Fachada.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    Fachada fachada;

    fachada.testar();

    cout << "\nTESTE: Sistema de Monitoramento de Imagens via Fachada\n" << endl;

    double v1 = fachada.processarImagemOCR("imagens/hidrometro_001.jpg");
    cout << "Leitura via OCR: " << v1 << " m^3\n" << endl;

    double v2 = fachada.processarImagemSegmentacao("imagens/hidrometro_002.jpg");
    cout << "Leitura via Segmentacao: " << v2 << " m^3" << endl;

    return 0;
}