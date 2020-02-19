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
        CLEAR;
        cin.ignore();
        switch (opc)
        {
            case OPC_CAPTURAR:
            {
                Usuario usuarioTmp;
                capturar_datos(usuarioTmp);
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
    if (!m_usuarios.size())
        cout << " Aún no se han ingresado usuarios " << endl << endl
             << " Presione ENTER para continuar..." << endl;
    else
    {
        cout << " Ingrese el código a buscar: ";
        getline(cin, codigo);
        for (i = 0; i < m_usuarios.size(); i++)
            if(m_usuarios[i].getCodigo() == codigo)
            {
                CLEAR;
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
        {

            cout << endl
                << " Dato inválido, presione ENTER para continuar..."
                << endl;
            cin.get();
        }
    }
}

void Gestor::modificar()
{   
    Usuario usuarioTmp;
    unsigned int i;
    char opc;

    mostrar();
    if (m_usuarios.size())
    {
        cout << " Ingrese número del usuario a modificar: ";
        cin >> i;

        if (i <= m_usuarios.size() && i)
        {   
            do
            {
                cout << endl
                     << " Seleccione el campo a modificar:" << endl;
                cout << char(CAMPO_NOM) << ") Nombre" << endl
                     << char(CAMPO_APE) << ") Apellido" << endl
                     << char(CAMPO_EDAD) << ") Edad" << endl
                     << char(CAMPO_SEXO) << ") Sexo" << endl
                     << char(CAMPO_PESO) << ") Peso" << endl
                     << char(CAMPO_ALTURA) << ") Altura" << endl
                     << char(CAMPO_CANCELAR) << ") Cancelar" << endl
                     << "Opción: ";
                cin >> opc;
            }while(opc < CAMPO_NOM || opc > CAMPO_CANCELAR);
            
            if (opc != CAMPO_CANCELAR)
            {
                usuarioTmp.setAltura((m_usuarios.begin() + i - 1)->getAltura());
                usuarioTmp.setApellido((m_usuarios.begin() + i - 1)->getApellido());
                usuarioTmp.setCodigo((m_usuarios.begin() + i - 1)->getCodigo());
                usuarioTmp.setEdad((m_usuarios.begin() + i - 1)->getEdad());
                usuarioTmp.setGenero((m_usuarios.begin() + i - 1)->getGenero());
                usuarioTmp.setNombre((m_usuarios.begin() + i - 1)->getNombre());
                usuarioTmp.setPeso((m_usuarios.begin() + i - 1)->getPeso());

                modificar_datos(usuarioTmp, opc);

                m_usuarios.erase(m_usuarios.begin() + i -1);
                m_usuarios.insert(m_usuarios.begin() + i - 1, usuarioTmp);

                escribir();

                cout << endl
                     << " Dato modificado correctamente" << endl
                     << " Presione ENTER para continuar..." << endl;
            }
        }

        else
        {
            cout << endl
                 << " Dato inválido, presione ENTER para continuar..."
                 << endl;
            cin.get();       
        }
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

void Gestor::capturar_datos(Usuario& usuario)
{
    string codigo;
    string nombre;
    string apellido;
    unsigned int edad;
    string genero;
    float altura;
    float peso;
    bool continuar = false;

    // Expresiones regulares
    regex expCodigo("([1-9]{1}[0-9]{8})$");
    regex expNombre("(?:[a-zA-ZñÑ]{4,})(?: [a-zA-ZñÑ]{4,})?{1,2}");
    regex expApellido("(?:[a-zA-ZñÑ]{4,})+(?: [a-zA-ZñÑ]{3,})$");
    regex expGenero("(?:[mMfF]){1}$");
    
    cout << " Presione ENTER para continuar e ingrese los siguientes datos"
         << endl << endl;

    // Obtención de código
    do
    {
        CLEAR;
        cout << " Código (9 dígitos): ";
        getline(cin, codigo);
        cout << codigo_usado(codigo) << endl;
        if (codigo_usado(codigo))
        {
            cout << endl
                 << " Error, código en uso. Presione ENTER para continuar";
            cin.get();
        }
        else if (!regex_match(codigo, expCodigo))
        {
            cout << endl
                 << " Error el código debe de tener 9 dígitos y no debe de"
                 << " empezar con cero" << endl
                 << " Presione ENTER para continuar";
            cin.get();
        }
        else
            continuar = true;
    } while (!continuar);
    continuar = false;

    // Obtención de nombre
    do
    {
        CLEAR;
        cout << " Nombre: ";
        getline(cin, nombre);
        if (!regex_match(nombre, expNombre))
        {
            cout << " Error, introducir mínimo un nombre y máximo tres "
                 << endl
                 << " (mínimo cuatro letras por nombre)"
                 << endl
                 << " Presione ENTER para continuar"
                 << endl;
            cin.get();
        }
        else
            continuar = true;
    } while (!continuar);
    continuar = false;

    // Obtención de apellido
    do
    {
        CLEAR;
        cout << " Apellido: ";
        getline(cin, apellido);
        if (!regex_match(apellido, expApellido))
        {
            cout << " Error, se deben de introducir dos apellidos"
                 << " separados por espacios"
                 << endl
                 << " Presione ENTER para continuar"
                 << endl;
            cin.get();
        }
        else
            continuar = true;
    }while(!continuar);

    do
    {
        CLEAR;
        cout << " Edad (de 12 a 115 años): ";
        cin >> edad;
    }while(edad > 115 || edad < 12);

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

bool Gestor::codigo_usado(const string codigo)
{
    for (int i = 0; i < m_usuarios.size(); i++)
        if (codigo == m_usuarios[i].getCodigo())
            return true;
    return false;
}

void Gestor::modificar_datos(Usuario& usuario, char i)
{
    bool continuar = false;

    // Expresiones regulares
    regex expCodigo("([1-9]{1}[0-9]{8})$");
    regex expNombre("(?:[a-zA-ZñÑ]{4,})(?: [a-zA-ZñÑ]{4,})?{1,2}");
    regex expApellido("(?:[a-zA-ZñÑ]{4,})+(?: [a-zA-ZñÑ]{3,})$");
    regex expGenero("(?:[mMfF]){1}$");

    cin.ignore();
    switch (i)
    {
        case CAMPO_NOM:
        {
            string nombre;
            do
            {
                CLEAR;
                cout << " Nombre: ";
                getline(cin, nombre);
                if (!regex_match(nombre, expNombre))
                {
                    cout << " Error, introducir mínimo un nombre y máximo tres "
                        << endl
                        << " (mínimo cuatro letras por nombre)"
                        << endl
                        << " Presione ENTER para continuar"
                        << endl;
                    cin.get();
                }
                else
                    continuar = true;
            } while (!continuar);
            usuario.setNombre(nombre);
        }
        break;

        case CAMPO_APE:
        {
            string apellido;
            do
            {
                CLEAR;
                cout << " Apellido: ";
                getline(cin, apellido);
                if (!regex_match(apellido, expApellido))
                {
                    cout << " Error, se deben de introducir dos apellidos"
                        << " separados por espacios"
                        << endl
                        << " Presione ENTER para continuar"
                        << endl;
                    cin.get();
                }
                else
                    continuar = true;
            }while(!continuar);
            usuario.setApellido(apellido);
        }
        break;

        case CAMPO_EDAD:
        {
            unsigned int edad;
            do
            {
                CLEAR;
                cout << " Edad (de 12 a 115 años): ";
                cin >> edad;
            }while(edad > 115 || edad < 12);
            usuario.setEdad(edad);
        }
        break;

        case CAMPO_PESO:
        {
            float peso;
            do
            {
                CLEAR;
                cout << " Peso (de 30 a 300 kg): ";
                cin >> peso;
            }while(peso > 300 || peso < 30);
            usuario.setPeso(peso);
        }
        break;

        case CAMPO_SEXO:
        {
            string genero;
            do
            {
                CLEAR;
                cout << " Género (M = masculino | F = femenino): ";
                cin >> genero;
            } while(!regex_match(genero, expGenero));
            usuario.setGenero(genero[0]);
        }
        break;

        case CAMPO_ALTURA:
        {
            float altura;
            do
            {   
                CLEAR;
                cout << " Altura (de 0.8 a 2.5 mts): ";
                cin >> altura;;
            } while (altura < 0.8 || altura > 2.5);
            usuario.setAltura(altura);
        }
        break;
    }
}