
#include <string>
#include <iostream>
using namespace std;

#include "siga.h"

// Funcão que testa a importação dos dados.
// <input file> - nome do arquivo .csv a ser importado.
//     Use um dos arquivos na pasta tests/input

int main(int argc, char *argv[])
{

    string input = INPUT_DIR + string("siga1000.csv");
    Siga siga("dataset.bin");
    int n_import = siga.ImportCSVData(input);
    if(n_import == 978) return 0;
    return -1;
}




