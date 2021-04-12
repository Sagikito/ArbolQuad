#include "ArbolQuad.h"
#include <fstream>
#include <queue>

int main()
{
    ArbolQuad arbol;


    //todo esto es de lectura del archivo qt
    string nombreArch;
    string x;
    queue<int> numeros;
    int dimensiones[2];
    
    cout<<"Nombre del archivo a leer: ";
    cin>> nombreArch;
    ifstream inputFile; //variable para almacenar el archivo del cual vamos a leer.
    inputFile.open(nombreArch);
    
    //si se puede abrir el archivo
    if(inputFile.is_open())
    {
        cout<<"archivo abierto exitosamente\n";
        //se van leyendo las 'cadenas' del archivo de entrada

        int i = 0;
        while(inputFile >> x) //similar a cin>>palabra solo que lo hacemos desde file
        {
            
            //se insertan las dimensiones (esta funcion cambia un string a numero)
            if(i<2)
            {
                int n = 0;
                for(char letra : x)
                    n = n*10 + (letra - 48);
                dimensiones[i] = n;
            }

            //se inserta numero por numero del codigo en la fila
            // i = 3 implica que ya estamos leyendo el codigo
            else
            {
                for(char letra : x)    
                    numeros.push(letra-48); //eg: int k = '3' - 48 = 51-48 = 3; 
            }
            i++;
        }
        inputFile.close();
    }
    else
        cout<<"el archivo no se pudo abrir\n";

    //ciclo para ver el codigo ingresado
    int i = 0;
    while(i<numeros.size())
    {
        cout<<numeros.front()<<" ";
        numeros.push(numeros.front());
        numeros.pop();
        i++;
    }
    cout<<endl;
    
    //luego de leer el archivo...
    //n es el tamano de la imagen
    int n = dimensiones[0];


    //ahora insertamos dato por dato en el arbol
    int dato;
    while(!numeros.empty())
    {
        dato = numeros.front();
        bool insertado;
        /*if(arbol.A_insertar(dato))
            cout<<dato<<": Insertado!\n";
        else
            cout<<dato<<": Dato no insertado\n";
        */
        insertado = arbol.A_insertar(dato); //no se si es necesaria la variable insertado
        numeros.pop();
    }


    //aqui empieza el menu de opciones

    short opcion;
    do
    {
        cout<<"\nOpciones\n";
        cout<<"1. imprimir preorden\n";
        cout<<"2. imprimir imagen\n";
        cout<<"3. Salir\n";
        cout<<"Ingrese la opcion: ";
        cin>>opcion;

        switch(opcion)
        {
            //imprimir en preorden
            case 1:
            {
                vector<int> v;

                arbol.A_preOrden(v);
                for(int i=0; i<v.size();i++)
                    cout<<v[i]<<" ";
                cout<<"\n";
                /*
                //esta opcion era para ver el valor de los nodos y sus ubicaciones
                vector<NodoQuad> w;
                arbol.A_preOrden(w);
                for(int i = 0; i < w.size(); i++)
                {
                    cout<<w[i].color<<"\t ";
                    for(int j = 0;j < (w[i].ubicacion).size();j++)
                        cout<<w[i].ubicacion[j];
                    cout<<"\n";
                }*/
                break;
            }

            //generar la imagen
            case 2:
            {
                string name;
                cout<<"Ingrese el nombre del archivo de salida: ";
                cin>>name;
                ofstream outputFile(name);
                //es equivalente a ofstream outputFile; outputFile.open(name);

                if(outputFile.is_open())
                {
                    outputFile<<"P1\n";
                    outputFile<<"# Imagen generada del archivo "<<nombreArch<<endl;
                    outputFile<<dimensiones[0]<<" "<<dimensiones[1]<<"\n";

                    
                    //inicializacion de la imagen nxn toda blanca (0)
                    vector<vector<int>> imagen;
                    vector<int> w;
                    int i, j;

                    for(i = 0; i < n; i++)
                    {
                        imagen.push_back(w);
                        for(j = 0; j < n; j++)
                            imagen[i].push_back(0);
                    }
                    
                    vector<NodoQuad> v; //este es el que almacena las hojas
                    arbol.generarImagen(v,imagen,n); //esto rellena la imagen

                    for(i = 0; i < n; i++)
                    {
                        for(j = 0; j < n; j++)
                            outputFile<<imagen[i][j]<<" ";
                        outputFile<<"\n";
                    }
                    outputFile.close();
                }
                else
                    cout<<"No se creo el archivo de salida!\n";
                break;
            }

            //salir
            case 3:
            {
                cout<<"salida exitosa!";
                break;
            }
            default: break;
        }
    }while(opcion>0 && opcion <3);
}