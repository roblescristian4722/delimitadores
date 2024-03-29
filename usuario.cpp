#include "usuario.h"

// GETTERS
string Usuario::getCodigo() const
{ return m_codigo; }
string Usuario::getNombre() const
{ return m_nombre; }
string Usuario::getApellido() const
{ return m_apellido; }
unsigned int Usuario::getEdad() const
{ return m_edad; }
char Usuario::getGenero() const
{ return m_genero; }
float Usuario::getAltura() const
{ return m_altura; }
float Usuario::getPeso() const
{ return m_peso; }

// SETTERS
void Usuario::setCodigo(string codigo)
{ m_codigo = codigo; }
void Usuario::setNombre(const string nombre) 
{ m_nombre = nombre; }
void Usuario::setApellido(const string apellido)
{ m_apellido = apellido; }
void Usuario::setEdad(unsigned int edad)
{ m_edad = edad; }
void Usuario::setGenero(char genero)
{ m_genero = genero; }
void Usuario::setAltura(float altura)
{ m_altura = altura; }
void Usuario::setPeso(float peso)
{ m_peso = peso; }