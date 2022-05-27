#include "siga.h"


int main(int argc, char *argv[])
{
    Siga siga("dataset.bin");
    siga.SalvarCSVOrdenadoPorNome("test2.csv", MERGESORT);
    return 0;
}
