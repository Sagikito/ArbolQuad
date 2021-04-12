#include "NodoQuad.h"

struct ArbolQuad
{
    NodoQuad* raiz;

    ArbolQuad(){raiz = NULL;}

    bool esVacio(){return raiz == NULL;}

    bool A_insertar(int dato);

    //void A_hojas(vector<NodoQuad>& v);
    void generarImagen(vector<NodoQuad>& v, vector<vector<int>>& matriz, int n);


    void A_preOrden(std::vector<int>& v);
    //void A_preOrden(vector<NodoQuad>& v);

};



bool ArbolQuad::A_insertar(int dato)
{
    if(esVacio())
    {
        NodoQuad* nuevo = new NodoQuad(dato);
        (nuevo->ubicacion).push_back(0);
        raiz = nuevo;
        return true;
    }
    else
        return raiz->N_insertar(dato);
}

/*
void ArbolQuad::A_hojas(vector<NodoQuad>& v)
{
    if(esVacio())
        cout<<"Arbol vacio!\n";
    else
        raiz->N_hojas(v);
}
*/

void ArbolQuad::generarImagen(vector<NodoQuad>& v, vector<vector<int>>& matriz, int n)
{
    if(esVacio())
        cout<<"Arbol vacio!\n";
    else
    {
        //buscar y almacenar las hojas del arbol en el vector de Nodos v.
        raiz->N_hojas(v);
        
        //hoja por hoja ir graficando el pedazo en la matriz
        for(int i = 0; i<v.size(); i++)
            v[i].graficar(matriz, n);
    }
}



void ArbolQuad::A_preOrden(vector<int>& v)
{
    if(esVacio())
        cout<<"Arbol vacio!\n";
    else
        raiz->N_preOrden(v);
}

/*
void ArbolQuad::A_preOrden(vector<NodoQuad>& v)
{
    if(esVacio())
        cout<<"Arbol vacio!\n";
    else
        raiz->N_preOrden(v);
}
*/
