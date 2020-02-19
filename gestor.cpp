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
                Usuario usuarioTmp;
                capturarDatos(usuarioTmp);
                capturar(usuarioTmp);
                cin.ignore();
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
}

void Gestor::eliminar()
{
    unsigned int i;
    mostrar();
    if (m_usuarios.size())
    {
        cout << " Ingrese número del usuario a eliminar: ";
        cin >> i;
        if (i <= m_usuarios.size() && i)
        {
            m_usuarios.erase(m_usuarios.begin() + i - 1);
            escribir();
        }
        else
            cout << endl
                << " Dato inválido, presione ENTER para continuar..."
                << endl;
    }
}

void Gestor::modificar()
{   
    Usuario usuarioTmp;
    unsigned int i;
    mostrar();

    if (m_usuarios.size())
    {
        cout << " Ingrese número del usuario a eliminar: ";
        cin >> i;

        if (i <= m_usuarios.size() && i)
        {
            capturarDatos(usuarioTmp);

            m_usuarios.erase(m_usuarios.begin() + i -1);

            m_usuarios.insert(m_usuarios.begin() + i - 1, usuarioTmp);

            escribir();
        }
        else
            cout << endl
                 << " Dato inválido, presione ENTER para continuar..."
                 << endl;
    }
}

void Gestor::mostrar()
{
    unsigned int i;
    for (i = 0; i < m_usuarios.size(); i++)
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
    if (!i)
        cout << " Aún no se han ingresado usuarios" << endl;
    cout << endl << endl
         << " Presione ENTER para continuar" << endl;
}

void Gestor::escribir()
{
    fstream archivo("usuarios.txt", ios::out);
    if (!archivo.is_open())
        cerr << " Error en el archivo" << endl;
    else
        for (int i = 0; i < m_usuarios.size(); i++)
            archivo << m_usuarios[i].getCodigo() << '|'
                    << m_usuarios[i].getNombre() << '|'
                    << m_usuarios[i].getApellido() << '|'
                    << m_usuarios[i].getEdad() << '|'
                    << m_usuarios[i].getGenero() << '|'
                    << m_usuarios[i].getPeso() << '|'
                    << m_usuarios[i].getAltura() << '\n';
}

void Gestor::capturarDatos(Usuario& usuario)
{
    string codigo;
    string nombre;
    string apellido;
    unsigned int edad;
    string genero;
    float altura;
    float peso;

    // Expresiones regulares
    regex expCodigo("([1-9]{1}[0-9]{8})$");
    regex expNombre("(?:[a-zA-ZñÑ]{4,})+(?: [a-zA-ZñÑ]{3,})?+");
    regex expApellido("(?:[a-zA-ZñÑ]{4,})+(?: [a-zA-ZñÑ]{3,})$");
    regex expGenero("(?:[mMfF]){1}$");
    
    cout << " Presione ENTER para continuar e ingrese los siguientes datos"
         << endl << endl;
    do
    {
        CLEAR;
        cout << " Código: ";
        getline(cin, codigo);
    } while (!regex_match(codigo, expCodigo));

    do
    {
        CLEAR;
        cout << " Nombre: ";
        getline(cin, nombre);
    } while (!regex_match(nombre, expNombre));

    do
    {
        CLEAR;
        cout << " Apellido: ";
        getline(cin, apellido);
    }while(!regex_match(apellido, expApellido));

    do
    {
        CLEAR;
        cout << " Edad (de 1 a 115 años): ";
        cin >> edad;
    }while(edad > 115 || !edad);

    do
    {
        CLEAR;
        cout << " Género (M = masculino | F = femenino): ";
        cin >> genero;
    } while(!regex_match(genero, expGenero));

    do
    {
        CLEAR;
        cout << " Peso (de 30 a 300 kg): ";
        cin >> peso;
    }while(peso > 300 || peso < 30);

    do
    {   
        CLEAR;
        cout << " Altura (de 0.8 a 2.5 mts): ";
        cin >> altura;;
    } while (altura < 0.8 || altura > 2.5);

    usuario.setAltura(altura);
    usuario.setApellido(apellido);
    usuario.setCodigo(codigo);
    usuario.setEdad(edad);
    usuario.setGenero(genero[0]);
    usuario.setNombre(nombre);
    usuario.setPeso(peso);
}