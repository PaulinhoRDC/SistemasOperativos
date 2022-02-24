typedef struct Person{
    char name [200];
    int age;
} Person;

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