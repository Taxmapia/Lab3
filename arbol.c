#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct Nodo
{
  char x;
  struct Nodo *izq;
  struct Nodo *der;
}tNodo;
typedef tNodo *ABO;

#define VERDADERO 1
#define FALSO 0
typedef int BOOL;

#define L 100


ABO Arbol = NULL;

ABO CreaNodo(int valor)
{
  ABO aux;

  aux = (ABO)malloc(sizeof(tNodo));
  if (aux != NULL)
  {
    aux->x = valor;
    aux->izq = NULL;
    aux->der = NULL;
  }
  else
  {
    system("cls");
    printf("\n\tERROR: No hay memoria suficiente para generar un nuevo Nodo.");
    printf("\n\tCerrando el programa...");
    exit(1);
  }
  return aux;
}
int Maximo(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}
BOOL EsVacio(ABO A)
{
  if (A == NULL)
  {
    return VERDADERO;  
  }
  return FALSO;
}
BOOL EsHoja(ABO A)
{
  if (A == NULL)
  {
    return FALSO;
  }
  if (A->izq == NULL && A->der == NULL)
  {
    return VERDADERO;
  }
  return FALSO;
}
int Altura(ABO A)
{
    if (A == NULL)
    {
        return 0;
    }
    else
    {
        return Maximo(Altura(A->izq), Altura(A->der)) + 1;
    }
}
ABO Insertar(ABO A, int valor)
{
  if (EsVacio(A))
  {
    A = CreaNodo(valor);
  }
  else
  {
    if (A->x > valor)
    {
      A->izq = Insertar(A->izq, valor);
    }
    else
    {
      A->der = Insertar(A->der, valor);
    }
  }
  return A;
}
int BuscaPosicionRaiz(char arreglo[L], int ini, int fin)
{
    int Parentesis = 1;
    int cont;

    cont = ini+1;
    while(cont <= fin)
    {
        if(Parentesis == 0)
        {
            return cont;
        }
        if(arreglo[cont] == '(')
        {
            Parentesis++;
        }
        if (arreglo[cont] == ')')
        {
            Parentesis--;
        }
        cont++;
    }
    return cont;
}
void ImprimeElementosNivel(ABO A, int nivel)
{
  if (A == NULL)
      printf(" -");
  else
  {
    if (nivel == 0)
    {
        printf("%c", A->x);
    }
    else
    {
      ImprimeElementosNivel(A->izq, nivel-1);
      printf("|");
      ImprimeElementosNivel(A->der, nivel-1);
    }  
  }
}
ABO ImprimeAB(ABO arbol)
{
  int h,i;
  h = Altura(Arbol);
  if(arbol!= NULL)
  {
    printf("\n");
  }
  for(i=0;i<h;i++)
  {
    printf("\n\t");
    ImprimeElementosNivel(Arbol, i);
  }
  printf("\n\n\n");
}
ABO CrearArbol(char arreglo[L], int ini, int fin)
{
  int raiz;                                    
  ABO aux;
  raiz = BuscaPosicionRaiz(arreglo,ini,fin); 

  aux=CreaNodo(arreglo[raiz]);
  if(ini==fin)
    {
      aux = CreaNodo(arreglo[ini]);
      return aux;
    }
  else
    {
      aux->izq = CrearArbol(arreglo, ini+1, raiz-2);
      aux->der = CrearArbol(arreglo, raiz+2, fin-1);
    }
}
int Operacion(ABO A)
{
  int n;
  if (EsVacio(A))
  {
    return 0;
  } 
  else if (EsHoja(A))
  {
    n = A->x - '0';
    return n;
  }
  else if (A->x == '+')
  {
    return  Operacion(A->izq) + Operacion(A->der);
  }
  else if (A->x == '-')
  {
    return  Operacion(A->izq) - Operacion(A->der);
  }
  else if (A->x == '*')
  {
    return  Operacion(A->izq) * Operacion(A->der);
  }
  else if (A->x == '/')
  {
    return  Operacion(A->izq) / Operacion(A->der);
  }
  else if (A->x == '^')
  {
    return  pow(Operacion(A->izq),Operacion(A->der));
  }
  else if (A->x == '%')
  {
    return  fmod(Operacion(A->izq),Operacion(A->der));
  }
  return n;
}
void LecturaArchivo()
{
  FILE *arch;
  int largo,ini,fin,cont;
  char archivo[L];
  char arreglo[L];
  int  a = 0, i = 0;

  printf("Ingrese nombre del archivo: ");

  while (a == 0)
  {
    scanf("%s",archivo);

    arch = fopen(archivo,"r");
    if (arch == NULL)
    {
      printf("\nError al abrir el archivo de texto\n");
      printf("\nReingrese el nombre del archivo: ");
    }
    else
    {
      a++;
      while((arreglo[i] = fgetc(arch)) != EOF)
      {
        printf("%c",arreglo[i]);
        i++;
        cont=i;
      }
      largo = cont;

      ini = 0;
      fin = largo - 2;
    }
    if(arreglo[largo-1] == '\n')
    {
      arreglo[largo-1] = '\0';
    }
    Arbol = CrearArbol(arreglo,ini,fin);
    ImprimeAB(Arbol);
    printf("%d\n",Operacion(Arbol));
  }
}

int main(int argc , char* argv[])
{
  printf("------------------------------------------\n");
  LecturaArchivo();
  printf("------------------------------------------\n");
  return 0;
}
