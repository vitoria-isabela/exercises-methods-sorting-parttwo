#include "siga.h"


int main(int argc, char *argv[])
{

    string input = INPUT_DIR + string("siga2000.csv");
    Siga siga("dataset.bin");
    int n_import = siga.ImportCSVData(input);
    if(n_import == 1052) return 0;
    return -1;
}