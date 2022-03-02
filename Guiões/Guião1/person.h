typedef struct pessoa {
    int idade; 
    char nome[200];
}Pessoa;

/*
 ----------------
|                |                   Person p; 
 ----------------
^
|

&p -> é assim que obtemos o valor da zona de memoria criada para a struct.

ATENÇÃO :
                    -sizeof(Person) , que é o tamanho da pessoa e não todo o espaço alocado para a struct em si.

 */

/*

Podíamos ter :
                    struct pessoa {
                         int idade; 
                         char nome[200];
                    };

                    typedef struc pessoa pessoa.t

*/