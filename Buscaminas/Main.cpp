//Buscaminas con Interfaz desde la terminal 
//Jose Barrera Ramos

#include<iostream>
#include<stdlib.h>
#include<cstdlib>
#include<fstream>

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Jugador {
    private:
        string nombre;
        int puntaje;
        bool vivo;
    public:
        Jugador(string, int, bool);
        void leerInfo();
        int getPuntaje();
        void setPuntaje(int puntaje);
        string getNombre();
        bool getVivo();
        void setVivo(bool vivo);
};

Jugador::Jugador(string nombre, int puntaje, bool vivo) {
    this->nombre = nombre;
    this->puntaje = puntaje;
    this->vivo = vivo;
}

void Jugador::leerInfo() {
    cout<<"Nombre Jugador: "<<nombre<<endl;
    cout<<"Puntaje: "<<puntaje<<endl;
}

int Jugador::getPuntaje() {
    return puntaje;
}

void Jugador::setPuntaje(int puntaje) {
    this->puntaje = puntaje;
}

string Jugador::getNombre() {
    return nombre;
}

bool Jugador::getVivo() {
    return vivo;
}

void Jugador::setVivo(bool vivo) {
    this->vivo = vivo;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Tablero {
    private:
        int fila;
        int columna;
        string** mapaTablero;
        string** mapaBomba;
    public:
        Tablero(int, int);
        void crearTablero();
        void verTablero();
        void crearBombas();
        bool jugar(int, int);
        void ponerBandera(int, int);
};

Tablero::Tablero(int fila, int columna) {
    this->fila = fila;
    this->columna = columna;

    mapaTablero = new string*[fila]; // Asignar memoria para filas
    for(int i=0; i<fila; i++) {
        mapaTablero[i] = new string[columna]; // Asignar memoria para columnas
    }

    mapaBomba = new string*[fila];
    for(int y=0; y<fila; y++) {
        mapaBomba[y] = new string[columna];
    }
}

void Tablero::crearTablero() {
    for(int i=0; i<fila; i++) {
        for(int y=0; y<columna; y++)
        {
            mapaTablero[i][y] = " # ";
        }
    }
}

void Tablero::verTablero() {
    for(int i=0; i<fila; i++) {
        for(int y=0; y<columna; y++)
        {
            cout<<mapaTablero[i][y];
        }
        cout<<endl;
    }
    cout<<endl;

    for(int i=0; i<fila; i++) {
        for(int y=0; y<columna; y++)
        {
            cout<<mapaBomba[i][y];
        }
        cout<<endl;
    }
    cout<<endl;
}

void Tablero::crearBombas() {
    srand(time(NULL)); // inicializamos la semilla con la hora actual
    int num = 0; 
    for(int i=0; i<fila; i++) {
        for(int y=0; y<columna; y++)
        {
            mapaBomba[i][y] = " 0 ";
            num = rand() % (10 - 1 + 1) + 1;
            if(num>8) {
                mapaBomba[i][y] = " X ";
            }
        }
    }
}

bool Tablero::jugar(int posicionFila, int posicionColumna) {
    bool valor = true;
    int contador = 0;
    if(mapaBomba[posicionFila][posicionColumna]==" X ") {
        valor = false;
        cout<<"Ha pisado una mina, has perdido"<<endl;
    } else {
        if(mapaBomba[posicionFila-1][posicionColumna-1]==" X ") {
            contador++;
        }

        if(mapaBomba[posicionFila-1][posicionColumna]==" X ") {
            contador++;
        }

        if(mapaBomba[posicionFila-1][posicionColumna+1]==" X ") {
            contador++;
        }

        if(mapaBomba[posicionFila][posicionColumna-1]==" X ") {
            contador++;
        }

        if(mapaBomba[posicionFila][posicionColumna+1]==" X ") {
            contador++;
        }

        if(mapaBomba[posicionFila+1][posicionColumna-1]==" X ") {
            contador++;
        }

        if(mapaBomba[posicionFila+1][posicionColumna]==" X ") {
            contador++;
        }

        if(mapaBomba[posicionFila+1][posicionColumna+1]==" X ") {
            contador++;
        }

        mapaTablero[posicionFila][posicionColumna] = " "+to_string(contador)+" ";
    }

    return valor;
}

void Tablero::ponerBandera(int posicionFila, int posicionColumna) {
    if(mapaTablero[posicionFila][posicionColumna]==" # ") {
        mapaTablero[posicionFila][posicionColumna] = " ♦ ";
    } else if(mapaTablero[posicionFila][posicionColumna]==" ♦ ") {
        mapaTablero[posicionFila][posicionColumna] = " # ";
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Main principal
int main() {

    ofstream archivo("puntajes.txt");

    bool vivo = true;
    int dificultad = 0;
    int puntaje = 0;
    int fila = 0; //horizontal --
    int columna = 0; //Vertical I
    string nombre = "Jugador";
    cout<<endl;
    cout<<"                Buscaminas              "<<endl;
    cout<<endl;
    cout<<"     Selecciona el nivel de dificultad      "<<endl;
    cout<<endl;
    cout<<"        Facil                     1           "<<endl;
    cout<<"        Normal                    2           "<<endl;
    cout<<"        Dificil                   3           "<<endl;
    cout<<"        Infierno                  4           "<<endl;

    cout<<endl;
    cout<<"Dificultad: "; cin>>dificultad; cout<<endl;
    cout<<"Digite su nombre: "; cin>>nombre; cout<<endl;

    Jugador j1 = Jugador(nombre, puntaje, vivo);
    Tablero t = Tablero(fila, columna);

    switch (dificultad) {
        case 1: {
            fila = 8;
            columna = 8;
            t = Tablero(fila, columna);
            t.crearTablero();
            t.crearBombas();
            break;
        }

        case 2: {
            fila = 12;
            columna = 12;
            t = Tablero(fila, columna);
            t.crearTablero();
            t.crearBombas();
            break;
        }

        case 3: {
            fila = 15;
            columna = 15;
            t = Tablero(fila, columna);
            t.crearTablero();
            t.crearBombas();
            break;
        }

        case 4: {
            fila = 20;
            columna = 20;
            t = Tablero(fila, columna);
            t.crearTablero();
            t.crearBombas();
            break;
        }

        default:
            cout<<"Porfavor digite un valor que sea valido entre el 1 y el 4 :)"<<endl;
            break;
    }

    int posicionFila;
    int posicionColumna;
    int opcion;
    bool sigueVivo = true;
    bool gano = false;
    int puntajeActual = 0;

    while(j1.getVivo()==true && gano==false ) {
        cout<<"------------------------------------------------------------------------------------------------------------------"<<endl;
        t.verTablero();

        cout<<"1) Seleccionar una celda"<<endl;
        cout<<"2) Poner o quitar una bandera"<<endl;
        cout<<"3) Ver Ranking de los jugadores"<<endl;
        cout<<"4) Rendirte"<<endl;
        cout<<"Elija una opcion: "; cin>>opcion; cout<<endl;

        switch(opcion) {
            case 1: {
                cout<<"Recuerde que las posiciones empiezan desde 0 hasta "<<fila-1<<endl;
                cout<<"Digite la posicion de la fila: "; cin>>posicionFila;
                cout<<"Digite la posicion de la columna: "; cin>>posicionColumna; cout<<endl;
                sigueVivo = t.jugar(posicionFila, posicionColumna);
                if(sigueVivo==false) {
                    j1.setVivo(sigueVivo);
                } else {
                    puntajeActual = j1.getPuntaje()+100;
                    j1.setPuntaje(puntajeActual);
                }
                break;
            }

            case 2: {
                cout<<"Recuerde que las posiciones empiezan desde 0 hasta "<<fila-1<<endl;
                cout<<"Digite la posicion de la fila: "; cin>>posicionFila;
                cout<<"Digite la posicion de la columna: "; cin>>posicionColumna; cout<<endl;
                t.ponerBandera(posicionFila, posicionColumna);
                break;
            }

            case 3: {
                break;
            }

            case 4: {
                gano = true;
                break;
            }
            
            default:
                cout<<"Porfavor digite una opcion valida"<<endl;
                break;
        }
    }

    if (archivo.is_open()) { // verificamos si se pudo abrir el archivo
        archivo<<nombre<<","<<j1.getPuntaje()<<endl; // escribimos en el archivo
        archivo.close(); // cerramos el archivo
        cout<<"Se ha escrito en el archivo."<<endl;
    } else {
        cout<<"No se pudo abrir el archivo."<<endl;
    }

    cout<<"Puntaje Final: "<<j1.getPuntaje()<<endl;
    cout<<"--Fin del juego, gracias por jugar--";

    return 0;
}