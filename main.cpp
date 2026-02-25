#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

enum class NivelClave {
    Insegura,
    Aceptable,
    Fuerte,
    MuyFuerte
};

const int LONGITUD_MINIMA = 8;
const int LONGITUD_ACEPTABLE = 12;
const int LONGITUD_FUERTE = 16;

bool tieneMayuscula(const string& clave) {
    for (char c : clave)
        if (isupper(c)) return true;
    return false;
}

bool tieneMinuscula(const string& clave) {
    for (char c : clave)
        if (islower(c)) return true;
    return false;
}

bool tieneNumero(const string& clave) {
    for (char c : clave)
        if (isdigit(c)) return true;
    return false;
}

bool tieneSimbolo(const string& clave) {
    const string simbolos = "!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?`~";
    for (char c : clave)
        if (simbolos.find(c) != string::npos) return true;
    return false;
}

bool contieneTextoProhibido(const string& clave) {
    const vector<string> prohibidos = {"1234", "password", "qwerty", "admin"};
    for (const string& palabra : prohibidos)
        if (clave.find(palabra) != string::npos) return true;
    return false;
}

NivelClave evaluarNivel(const string& clave) {

    if (clave.length() < LONGITUD_MINIMA) 
        return NivelClave::Insegura;

    bool esValida = tieneMayuscula(clave) &&
                    tieneMinuscula(clave) &&
                    tieneNumero(clave) &&
                    tieneSimbolo(clave) &&
                    !contieneTextoProhibido(clave);

    if (!esValida) 
        return NivelClave::Insegura;

    return (clave.length() >= LONGITUD_FUERTE) ? NivelClave::MuyFuerte :
           (clave.length() >= LONGITUD_ACEPTABLE) ? NivelClave::Fuerte :
           NivelClave::Aceptable;
}

int main() {

    string clave;
    cout << "Ingrese la clave: ";
    getline(cin, clave);

    NivelClave nivel = evaluarNivel(clave);

    switch (nivel) {
        case NivelClave::Aceptable:
            cout << "Clave aceptable\n";
            break;
        case NivelClave::Fuerte:
            cout << "Clave fuerte\n";
            break;
        case NivelClave::MuyFuerte:
            cout << "Clave muy fuerte\n";
            break;
        default:
            cout << "Clave insegura\n";
    }

    return 0;
}