#include "ArbolQuad.h"

int main()
{
    ArbolQuad arbol;
    
    int n;
    cout<<"Ingrese el tamano de la imagen: ";
    cin>>n;
    
    short opcion;
    do
    {
        cout<<"\nOpciones\n";
        cout<<"1. insertar un dato\n";
        cout<<"2. imprimir preorden\n";
        cout<<"3. imprimir imagen\n";
        cout<<"4. Salir\n";
        cout<<"Ingrese la opcion: ";
        cin>>opcion;

        switch(opcion)
        {
            //insertar dato
            case 1:
            {
                int dato;
                cout<<"Ingrese el dato: ";
                cin>>dato;
                if(arbol.A_insertar(dato))
                    cout<<"Insertado!\n";
                else
                    cout<<"Dato no insertado\n";
                break;
            }

            //imprimir en preorden
            case 2:
            {
                vector<int> v;

                arbol.A_preOrden(v);
                for(int i=0; i<v.size();i++)
                    cout<<v[i]<<" ";
                cout<<"\n";
                break;
                /*
                esta opcion era para ver el valor de los nodos y sus ubicaciones
                //vector<NodoQuad> v;
                arbol.A_preOrden(v);
                for(int i = 0; i < v.size(); i++)
                {
                    cout<<v[i].color<<"\t ";
                    for(int j = 0;j < (v[i].ubicacion).size();j++)
                        cout<<v[i].ubicacion[j];
                    cout<<"\n";
                }
                break;
                */
               
            }

            //generar la imagen
            case 3:
            {
                vector<vector<int>> imagen;
                vector<int> w;
                int i, j;

                //inicializacion de la imagen nxn toda blanca (0)
                for(i = 0; i < n; i++)
                {
                    imagen.push_back(w);
                    for(j = 0; j < n; j++)
                        imagen[i].push_back(0);
                }
                
                vector<NodoQuad> v;
                arbol.generarImagen(v,imagen,n);

                for(i = 0; i < n; i++)
                {
                    for(j = 0; j < n; j++)
                        cout<<imagen[i][j]<<" ";
                    cout<<"\n";
                }
            }

            //salir
            case 4:
            {
                cout<<"salida exitosa!";
                break;
            }
            default: break;
        }
    }while(opcion>0 && opcion <4);
}