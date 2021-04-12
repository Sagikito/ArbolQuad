#pragma once


#include <vector>
#include <iostream>
using namespace std;

struct NodoQuad
{
    //datos
    int color; //0 es blanco, 1 es negro, 2 es combinado
    NodoQuad* cuadrantes[4];
    vector<int> ubicacion;

    //constructor
    NodoQuad(int color)
    {
        this->color = color;
        for(int i = 0; i < 4; i++)
            cuadrantes[i] = NULL;
    }

    //operaciones
    bool esHoja();
    int tamano();
    bool N_insertar(int dato);

    void hojas(vector<NodoQuad>& v);
    void graficar(vector<vector<int>>& matriz, int n);

    //recorridos
    void N_preOrden(vector<int>& v);
    //void N_preOrden(vector<NodoQuad>& v);
};



bool NodoQuad::esHoja()
{
    return color != 2;
}

bool NodoQuad::N_insertar(int dato)
{
    // si es hoja no se puede insertar nada en el nodo
    if(esHoja())
        return false;
    
    //si no es hoja
    else
    {
        bool insertado = false;

        //recorremos los hijos mientras no se haya insertado
        for(int i = 0; i < 4 && !insertado; i++)
        {
            //si hay un hijo vacio lo metemos ahí de una
            if(cuadrantes[i] == NULL)
            {
                NodoQuad* nuevo = new NodoQuad(dato);
                cuadrantes[i] = nuevo;

                //este if es para que los hijos directos de la raiz no hereden el 0.
                if((this->ubicacion).front() != 0) 
                {
                    cuadrantes[i]->ubicacion = this->ubicacion;
                    (cuadrantes[i]->ubicacion).push_back(i+1); //se puede push i o push i+1 (me gusta que los hijos vayan de 1-4)
                }
                else
                    (cuadrantes[i]->ubicacion).push_back(i+1); 
                insertado = true;
            }
            
            //si el hijo revisado no es vacio y no es hoja llamamos a insertar sobre el
            else if(!(cuadrantes[i]->esHoja()))
            {
                //si logra insertar el dato en ese hijo insertado se vuelve verdadero
                if(cuadrantes[i]->N_insertar(dato))
                    insertado = true;
            }
        }
        //despues de salir del ciclo retornamos si se inserto o no
        return insertado;
    }
}

int NodoQuad::tamano()
{
    if(esHoja())
        return 1;
    else
    {
        int numNodos = 0;
        for(int i = 0; i < 4; i++)
            if(cuadrantes[i] != NULL)
                numNodos += cuadrantes[i]->tamano();
        return numNodos + 1;
    }
}


/*
estaba pensando en hacer el preorden asi pero el numero del preorden puede ser muy grande... por eso mejor no
long long NodoQuad::preOrden()
{

    if(esHoja)
        return color;
    else
    {
        int aux = color;
        for(int i=0; i<4; i++)
        {
            if(cuadrantes[i] != NULL)
                aux = aux*(elevar(10,cuadrantes[i]->tamano())) + cuadrantes[i]->preOrden();
                // aux = aux*10^cuad[i]->tam + cuad[i]-> preOrden()
        }
        return aux;
    }
}
*/

//recorrido en posorden buscando hojas a partir del nodo actual
void NodoQuad::hojas(vector<NodoQuad>& v)
{
    for(int i=0; i<4; i++)
        if(cuadrantes[i] != NULL)
            cuadrantes[i]->hojas(v);
    if(esHoja())
        v.push_back(*this);
}

/*
//a^n
int elevar(int a, int n)
{
    int res = 1;
    while(n!=0)
    {
        res *= a;
        n--;
    }
    return res;
}
*/

//asi se distribuyen los cuadrantes
// 1 2
// 3 4

//la idea de esta funcion es tomar nodos hoja y graficar en la matriz 
void NodoQuad::graficar(vector<vector<int>>& matriz, int n)
{
    int i_inf = 0, i_sup = n;
    int j_inf = 0, j_sup = n;

    //aqui la idea es usar la ubicacion para calcular los limites 
    //en los cuales el nodo afecta a la matriz
    for(int i=0; i<ubicacion.size(); i++)
    {
        //si es hijo 1 (cuadrante 1)
        if(ubicacion[i] == 1)
        {
            //i_inf, j_inf se mantienen
            i_sup = (i_inf + i_sup)/2;
            j_sup = i_sup;
        }

        //si es hijo 2 (cuadrante 2)
        if(ubicacion[i] == 2)
        {
            //i_inf, j_sup se mantienen
            i_sup = (i_inf + i_sup)/2;
            j_inf = i_sup; 
        }

        //si es hijo 3 (cuadrante 3)
        if(ubicacion[i] == 3)
        {
            //i_sup, j_inf se mantienen
            i_inf = (i_inf + i_sup)/2;
            j_sup = i_inf;
        }
        
        //si es hijo 4 (cuadrante 4)
        if(ubicacion[i] == 4)
        {
            //i_sup, j_sup se mantienen
            i_inf = (i_inf + i_sup)/2;
            j_inf = i_inf;
        }
    }
    //ahora que los limites estan definidos se rellena el pedazo de matriz correspondiente
    for(int i = i_inf; i < i_sup; i++)
        for(int j = j_inf; j < j_sup; j++)
            matriz[i][j]= color;
}    
    
    /*
    esto no es necesario, porque los nodos hoja que obtengo, siempre la idea es que afecten
    a la matriz nxn de entrada

    int i_sup, j_sup;
    if(ubicacion[0] = 0)
    {
        i_sup = n;
        j_sup = n;
    }
    
    else
    {
        //la longitud del codigo de ubicacion me da la altura del nodo relativa a la raiz
        //excepto en el caso de la raiz misma(por eso divido los casos)
        i_sup = n/(elevar(2,ubicacion.size()));
        j_sup = i_sup;
    }
}
*/

//'retorna' (por referencia) un vector con los colores en preorden
void NodoQuad::N_preOrden(vector<int>& v)
{
    v.push_back(color);
    for(int i = 0; i < 4; i++)
        if(cuadrantes[i]!=NULL) 
            cuadrantes[i]->N_preOrden(v);
}

/*
void NodoQuad::N_preOrden(vector<NodoQuad>& v)
{
    v.push_back(*this);
    for(int i = 0; i < 4; i++)
        if(cuadrantes[i]!=NULL) 
            cuadrantes[i]->N_preOrden(v);
}
*/

