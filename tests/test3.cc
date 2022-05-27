#include "siga.h"

int main(int argc, char *argv[])
{
    Siga siga("dataset.bin");
    siga.SalvarCSVOrdenadoPorNome("test3.csv", QUICKSORT);
    return 0;
}
