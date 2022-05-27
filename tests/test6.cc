#include <iostream>
#include <chrono>

#include "siga.h"
#include "sort.h"

int main(int argc, char* argv[])
{
    string input = INPUT_DIR + string("siga5000.csv");
    // Abre o dataset 
    Siga siga("dataset.bin");
    int n_import = siga.ImportCSVData(input);
  
    int n_estudantes = siga.ObterNumeroEstudantesArmazenados();

    Estudante *temp           = new Estudante[n_estudantes];
    Estudante *estudantes     = siga.ExtractAllEstudantsFromDataSet();

    std::copy(estudantes, estudantes+n_estudantes, temp);

    bubble_sort(temp, n_estudantes, &CompareByNome);

    std::copy(estudantes, estudantes+n_estudantes, temp);

    selection_sort(temp, n_estudantes, &CompareByNome);

    std::copy(estudantes, estudantes+n_estudantes, temp);

    insertion_sort(temp, n_estudantes, &CompareByNome);

    std::copy(estudantes, estudantes+n_estudantes, temp);
    
    merge_sort(temp, n_estudantes, &CompareByNome);

    std::copy(estudantes, estudantes+n_estudantes, temp);
    
    quick_sort(temp, n_estudantes, &CompareByNome);
 
    delete [] temp;
    delete [] estudantes;
    return 0;
}
  
  
    
    
