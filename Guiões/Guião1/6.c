/*
6.  Considere uma estrutura (struct) com dados de uma pessoa (nome, idade, ...) 
e um ficheiro binário que contém registos organizados segundo esta estrutura.

Não assuma que o ficheiro cabe todo em mem ória.

Escreva um programa que, consoante a opção, permita:

    -i -  Acrescentar pessoas a um ficheiro de dados (binário – a idade  é um inteiro).
    -u -  Atualizar a idade de uma determinada pessoa no ficheiro de dados.
    
Exemplos:
$ pessoas  -i "José Mourinho" 55
$ pessoas  -u "José Mourinho" 56 

Meça o tempo que demora a inserir 1.000.000 de pessoas (nomes e idades gerados por si).   
Observa alguma degradação de desempenho à medida que o ficheiro cresce?

*/



