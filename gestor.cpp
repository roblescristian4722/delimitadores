#include "gestor.h"

Gestor::Gestor()
{
    fstream archivo("usuarios.txt", ios::out | ios::in);
    if (!archivo.is_open())
    {
        fstream archivo_abrir("usuarios.txt", ios::out);
        archivo_abrir.close();
    }
    else
    {
        string aux;
        Usuario usuarioTmp;
        while (!archivo.eof())
        {
            getline(archivo, aux, '|');
            if (aux.size() > 0)
            {
                usuarioTmp.setCodigo(aux);
                
                getline(archivo, aux, '|');
                usuarioTmp.setNombre(aux);

                getline(archivo, aux, '|');
                usuarioTmp.setApellido(aux);

                getline(archivo, aux, '|');
                usuarioTmp.setEdad(stoi(aux));

                getline(archivo, aux, '|');
                usuarioTmp.setGenero(aux.c_str()[0]);

                getline(archivo, aux, '|');
                usuarioTmp.setPeso(stof(aux));
                
                getline(archivo, aux);
                usuarioTmp.setAltura(stof(aux));

                m_usuarios.push_back(usuarioTmp);
            }
        }
        archivo.close();
    }
}

Gestor::~Gestor()
{}

void Gestor::menu()
{
    char opc;
    do
    {
        CLEAR;
        cout << " Ingrese la opción a ejecutar: " << endl
             << " " << char(OPC_CAPTURAR) << ") Capturar usuario" << endl
             << " " << char(OPC_MOSTRAR) << ") Mostrar usuarios" << endl
             << " " << char(OPC_BUSCAR) << ") Buscar usuario (por código)" << endl
             << " " << char(OPC_MODIFICAR) << ") Modificar usuario" << endl
             << " " << char(OPC_ELIMINAR) << ") Eliminar usuario" << endl
             << " " << char(OPC_SALIR) << ") Salir" << endl
             << " Opción: ";

        cin >> opc;
        cin.ignore();
        CLEAR;
        switch (opc)
        {
            case OPC_CAPTURAR:
            {
                string codigo;
                string nombre;
                string apellido;
                unsigned int edad;
                char genero;
                float altura;
                float peso;
                Usuario usuarioTmp;

                cout << " Ingrese los siguientes datos: " << endl
                     << endl
                     << " Código: ";
                cin.ignore();
                getline(cin, codigo);
                cout << " Nombre: ";
                getline(cin, nombre);
                cout << " Apellido: ";
                getline(cin, apellido);
                cout << " Edad: ";
                cin >> edad;
                cout << " Género (M = masculino | F = femenino): ";
                cin >> genero;
                cout << " Peso: ";
                cin >> peso;
                cout << " Altura: ";
                cin >> altura;;

                usuarioTmp.setAltura(altura);
                usuarioTmp.setApellido(apellido);
                usuarioTmp.setCodigo(codigo);
                usuarioTmp.setEdad(edad);
                usuarioTmp.setGenero(genero);
                usuarioTmp.setNombre(nombre);
                usuarioTmp.setPeso(peso);

                capturar(usuarioTmp);
            }
            break;

            case OPC_MODIFICAR:
                modificar();
            break;

            case OPC_BUSCAR:
                buscar();
            break;

            case OPC_ELIMINAR:
                eliminar();
            break;

            case OPC_MOSTRAR:
                CLEAR;
                mostrar();
            break;

            case OPC_SALIR:
                cout << " Hasta la próxima" << endl;
            return;

            default:
                cout << " Dato inválido, presione ENTER para continuar..." << endl;
            break;
        }
        cin.get();
    } while (opc != OPC_SALIR);
}

void Gestor::buscar()
{
    string codigo;
    unsigned int i;
    cout << " Ingrese el código a buscar: ";
    getline(cin, codigo);
    if (!m_usuarios.size())
        cout << endl << " Aún no se han ingresado usuarios " << endl
             << " Presione ENTER para continuar..." << endl;
    else
    {
        for (i = 0; i < m_usuarios.size(); i++)
            if(m_usuarios[i].getCodigo() == codigo)
            {

                cout << endl
                    << " Usuario #" << i + 1 << endl
                    << " Código: " << m_usuarios[i].getCodigo() << endl
                    << " Nombre: " << m_usuarios[i].getNombre() << endl
                    << " Apellido: " << m_usuarios[i].getApellido() << endl
                    << " Edad: " << m_usuarios[i].getEdad() << endl
                    << " Género: " << m_usuarios[i].getGenero() << endl
                    << " Peso: " << m_usuarios[i].getPeso() << endl
                    << " Altura: " << m_usuarios[i].getAltura() << endl
                    << "----------------------------------------------"
                    << endl << endl
                    << " Presione ENTER para continuar..." << endl;
                break;
            }
        if (i == m_usuarios.size())
            cout << endl
                << " Código no encontrado, presione ENTER para continuar..." << endl;
    }
}

void Gestor::capturar(const Usuario& usuario)
{
    fstream archivo("usuarios.txt", ios::out | ios::in | ios::app);
    if (!archivo.is_open())
        cerr << "Error en el archivo de salida" << endl;
    archivo << usuario.getCodigo() << '|' << usuario.getNombre() << '|'
            << usuario.getApellido() << '|' << usuario.getEdad() << '|'
            << usuario.getGenero() << '|' << usuario.getPeso() << '|'
            << usuario.getAltura() << '\n';
    m_usuarios.push_back(usuario);
    cout << endl
         << " Usuario añadido exitosamente." << endl
         << " Presione ENTER para continuar..." << endl;
    cin.get();
}

void Gestor::eliminar()
{
    unsigned int i;
    for (i = 0; i < m_usuarios.size(); i++)
    {
    }
    if (!i)
    {
        cout << endl
             << " Aún no ha agregado datos, presione ENTER para continuar";
        cin.get();
    }
}

void Gestor::modificar()
{

}

void Gestor::mostrar()
{
    for (int i = 0; i < m_usuarios.size(); i++)
        cout << " Usuario #" << i + 1 << endl
             << " Código: " << m_usuarios[i].getCodigo() << endl
             << " Nombre: " << m_usuarios[i].getNombre() << endl
             << " Apellido: " << m_usuarios[i].getApellido() << endl
             << " Edad: "   << m_usuarios[i].getEdad() << endl
             << " Género: " << m_usuarios[i].getGenero() << endl
             << " Peso: " << m_usuarios[i].getPeso() << endl
             << " Altura: " << m_usuarios[i].getAltura() << endl
             << "----------------------------------------------"
             << endl;
}