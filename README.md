# MRC-Library
E uma biblioteca de simulação para Canais de Radio Movel baseada no modelo de soma de sisoides (SOS) para canais de baixa complexidade, ou seja, com o menor numero de sisoides possivel.

### 1. Principio da Soma de Sisoides

$ u(t) = \lim\limits_{N \to \infty} \sum_{n = 1}^{N} c_{n}cos(2\pi f_{n} + \theta_{n})$

### 2. Processo de Rayleigh

$ |u(t)| = |u_{1}(t) + ju_{2}(t)|$

### 3. Processo de Rice
$ |u(t)| = |u(t) + m(t)|$

onde m(t) e chamada componente de linha de visão, dada por:

$ m(t) = cos(ft) + jsin(ft)$

## Composição do codigo 

```cpp
void main()
{

}
```

## Referências
1. Patzold, Matthias. Mobile Radio Channels 2º.