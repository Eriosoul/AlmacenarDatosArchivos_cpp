#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class Cliente {
public:
    std::string nombre;
    std::string apellidos;
    std::string dni_nie;
    std::string fecha;
    std::string domicilio;
    std::string localidad;
    std::string codPostal;
    std::string telef;

    bool ValidateDate(const std::string& fecha) {
        // Validar formato de fecha (dd/mm/aaaa) y que la fecha sea válida
        // Si la fecha no es válida, lanzar una excepción InvalidDateFormatException
    }

    void escribir(std::ofstream& archivo) {
        // Escribir los datos del cliente en el archivo
        // Tras cada dato guardado se añadira una coma
        std::stringstream ss;
        ss << nombre << "," << apellidos << "," << dni_nie << "," << fecha << ","
           << domicilio << "," << localidad << "," << codPostal << "," << telef;
        archivo << ss.str() << std::endl;
    }

    static Cliente leer(std::ifstream& archivo) {
        // Leer los datos del cliente del archivo
        std::string linea;
        std::getline(archivo, linea);

        std::stringstream ss(linea);
        std::string campo;
        // Indicamos la lectura hsta la coma
        Cliente c;
        std::getline(ss, c.nombre, ',');
        std::getline(ss, c.apellidos, ',');
        std::getline(ss, c.dni_nie, ',');
        std::getline(ss, c.fecha, ',');
        std::getline(ss, c.domicilio, ',');
        std::getline(ss, c.localidad, ',');
        std::getline(ss, c.codPostal, ',');
        std::getline(ss, c.telef, ',');

        return c;
    }
};

class Empleado{
public:
    std::string nombre;
    std::string apellidos;
    std::string dni_nie;
    std::string fecha;
    std::string domicilio;
    std::string localidad;
    std::string codPostal;
    std::string telef;
    std::string departamento;
    std::string catProfesion;

    bool ValidateDate(const std::string& fecha) {
        // Validar formato de fecha (dd/mm/aaaa) y que la fecha sea válida
        // Si la fecha no es válida, lanzar una excepción InvalidDateFormatException
    }

    void escribir(std::ofstream& archivo) {
        // Escribir los datos del Empleado en el archivo
        std::stringstream ss;
        ss << nombre << "," << apellidos << "," << dni_nie << "," << fecha << ","
           << domicilio << "," << localidad << "," << codPostal << "," << telef << ","<< departamento << "," << catProfesion;
        archivo << ss.str() << std::endl;
    }

    static Empleado leer(std::ifstream& archivo) {
        // Leer los datos del Empleado del archivo
        std::string linea;
        std::getline(archivo, linea);

        std::stringstream ss(linea);
        std::string campo;

        Empleado e;
        std::getline(ss, e.nombre, ',');
        std::getline(ss, e.apellidos, ',');
        std::getline(ss, e.dni_nie, ',');
        std::getline(ss, e.fecha, ',');
        std::getline(ss, e.domicilio, ',');
        std::getline(ss, e.localidad, ',');
        std::getline(ss, e.codPostal, ',');
        std::getline(ss, e.telef, ',');
        std::getline(ss, e.departamento, ',');
        std::getline(ss, e.catProfesion, ',');

        return e;
    }
};

std::map<std::string, Cliente> clientes;
std::map<std::string, Empleado> empleados;
// Clase de excepción personalizada para fechas en formato incorrecto
class InvalidDateFormatException : public std::invalid_argument
{
public:
    InvalidDateFormatException(const std::string& message)
        : std::invalid_argument(message) {}
};

// Función que valida una fecha en formato dd/mm/aaaa
void ValidateDate(const std::string& date)
{
    // Validamos el formato de la fecha
    if (date.length() != 10 || date[2] != '/' || date[5] != '/')
    {
        throw InvalidDateFormatException("La fecha debe tener el formato dd/mm/aaaa");
    }

    // Validamos el rango de los días y meses
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    if (day < 1 || day > 31 || month < 1 || month > 12)
    {
        throw InvalidDateFormatException("Día o mes inválidos en la fecha");
    }
}

// Método para leer un cliente desde un archivo
void readClientFile(const std::string& filename) {
    // Abrir el archivo para lectura
    std::ifstream archivo(filename);
    // Leer el archivo y almacenar cada cliente en el mapa
    while (archivo) {
        Cliente c = Cliente::leer(archivo);
        clientes[c.dni_nie] = c;
    }
    // Cerrar el archivo
    archivo.close();
}

// Método para leer un cliente desde un archivo
void readEmpleadoFile(const std::string& filename) {
    // Abrir el archivo para lectura
    std::ifstream archivo(filename);
    // Leer el archivo y almacenar cada cliente en el mapa
    while (archivo) {
        Empleado e = Empleado::leer(archivo);
        empleados[e.dni_nie] = e;
    }
    // Cerrar el archivo
    archivo.close();
}

int menu(){
    system("cls");
    int x;
    std::cout << "Bienvenido a Clínica Radiológica Aranguren" << std::endl;
    std::cout << "Pulse 1 para introducir los datos de un nuevo cliente" << std::endl;
    std::cout << "Pulse 2 para introducir los datos de un nuevo empleado" << std::endl;
    std::cout << "Pulse 3 para ver los registros" << std::endl;
    std::cout << "Pulse 4 para salir del programa" << std::endl;
    std::cin >> x;
    return x;
}

int main() {
    readClientFile("cliente.txt");
    readEmpleadoFile("empleado.txt");
    int opcion2;
    while (true) {
        int opcion = menu();
        switch (opcion) {
            case 1: {
                // Crear un nuevo cliente
                Cliente cliente;
                std::cout << "Introduce el nombre del cliente: ";
                std::cin >> cliente.nombre;
                std::cout << "Introduce los apellidos del cliente: ";
                std::cin.ignore();
                std::getline(std::cin, cliente.apellidos);
                std::cout << "Introduce el DNI/NIE del cliente: ";
                std::getline(std::cin, cliente.dni_nie);

                // Comprobar si el DNI del nuevo cliente ya existe en el mapa
                if (clientes.count(cliente.dni_nie) > 0) {
                    // El DNI ya existe, no se puede añadir al nuevo cliente
                    std::cout << "Ya existe un cliente con ese DNI/NIE" << std::endl;
                    system("pause");
                    break;
                }

                std::cout << "Introduce la fecha de nacimiento del cliente (dd/mm/aaaa): ";
                std::getline(std::cin, cliente.fecha);

                bool inputValid = false;
                while(!inputValid){
                    try{
                        ValidateDate(cliente.fecha);
                        //std::cout << "Fecha válida" << std::endl;
                        inputValid = true;
                    }catch(const InvalidDateFormatException& ex){
                        std::cout << "Error: " << ex.what() << std::endl;
                        std::cout << "Introduce la fecha de nacimiento del cliente (dd/mm/aaaa): ";
                        std::getline(std::cin, cliente.fecha);
                    }
                }

                std::cout << "Introduce el domicilio del cliente: ";
                std::getline(std::cin, cliente.domicilio);
                std::cout << "Introduce la localidad del cliente: ";
                std::getline(std::cin, cliente.localidad);
                std::cout << "Introduce el codigo postal del cliente: ";
                std::cin >> cliente.codPostal;
                bool telefono_valido = false;
                while (!telefono_valido) {
                    std::string telefono;
                    std::cout << "Introduce el numero de telefono del cliente: ";
                    std::cin >> telefono;
                    if (telefono.length() == 9) {
                        telefono_valido = true;
                        cliente.telef = telefono;
                    } else {
                        std::cout << "El numero de telefono debe tener 9 digitos." << std::endl;
                    }
                }

                // Añadir el nuevo cliente al mapa
                clientes[cliente.dni_nie] = cliente;
                // Abrir el archivo para escritura
                std::ofstream archivo("cliente.txt", std::ios::app);
                // Escribe el cliente en el archivo
                cliente.escribir(archivo);
                // Cerrar el archivo
                archivo.close();

                std::cout << "Cliente correctamente almacenado" << std::endl;
                break;
            }
            case 2: {
                Empleado empleado;
                std::cout << "Introduce el nombre del empleado: ";
                std::cin >> empleado.nombre;
                std::cout << "Introduce los apellidos del empleado: ";
                std::cin.ignore();
                std::getline(std::cin, empleado.apellidos);
                std::cout << "Introduce el DNI/NIE del empleado: ";
                std::getline(std::cin, empleado.dni_nie);

                // Comprobar si el DNI del nuevo Empleado ya existe en el mapa
                if (empleados.count(empleado.dni_nie) > 0) {
                    // El DNI ya existe, no se puede añadir al nuevo Empleado
                    std::cout << "Ya existe un empleado con ese DNI/NIE" << std::endl;
                    system("pause");
                    //break;
                }

                std::cout << "Introduce la fecha de nacimiento del empleado (dd/mm/aaaa): ";
                std::getline(std::cin, empleado.fecha);

                bool inputValid = false;
                while(!inputValid){
                    try{
                        ValidateDate(empleado.fecha);
                        //std::cout << "Fecha válida" << std::endl;
                        inputValid = true;
                    }catch(const InvalidDateFormatException& ex){
                        std::cout << "Error: " << ex.what() << std::endl;
                        std::cout << "Introduce la fecha de nacimiento del empleado (dd/mm/aaaa): ";
                        std::getline(std::cin, empleado.fecha);
                    }
                }

                std::cout << "Introduce el domicilio del empleado: ";
                std::getline(std::cin, empleado.domicilio);
                std::cout << "Introduce la localidad del empleado: ";
                std::getline(std::cin, empleado.localidad);
                std::cout << "Introduce el codigo postal del empleado: ";
                std::cin >> empleado.codPostal;
                bool telefono_valido = false;
                while (!telefono_valido) {
                    std::string telefono;
                    std::cout << "Introduce el numero de telefono del empleado: ";
                    std::cin >> telefono;
                    if (telefono.length() == 9) {
                        telefono_valido = true;
                        empleado.telef = telefono;
                    } else {
                        std::cout << "El numero de telefono debe tener 9 digitos." << std::endl;
                    }
                }
                std::cout << "Introduce el domicilio del empleado: ";
                std::cin.ignore();
                std::getline(std::cin, empleado.departamento);
                std::cout << "Introduce el domicilio del empleado: ";
                std::getline(std::cin, empleado.catProfesion);

                // Añadir el nuevo Empleado al mapa
                empleados[empleado.dni_nie] = empleado;
                // Abrir el archivo para escritura
                std::ofstream archivo("empleado.txt", std::ios::app);
                // Escribe el Empleado en el archivo
                empleado.escribir(archivo);
                // Cerrar el archivo
                archivo.close();
                system("pause");
                std::cout << "Empleado correctamente almacenado" << std::endl;
                break;
            }
            case 3:
                std::cout << "Que lista desea ver?"<< std::endl;
                std::cout << "Pulse 1 para ver el listado de los Pacientes" << std::endl;
                std::cout << "Pulse 2 para ver el listado de los Empleados" << std::endl;
                std::cin >> opcion2;
                switch (opcion2) {
                    case 1:
                    system("cls");
                        // Ver el registro de clientes
                        // Mostrar la información de los clientes por pantalla
                        std::cout << "Listado de cliente:" << std::endl;
                        for (const auto& p : clientes) {
                            std::string dni = p.first;
                            Cliente cliente = p.second;
                            std::cout << "Paciente con DNI/NIE: " << cliente.dni_nie << std::endl;
                            std::cout << "Nombre y apellidos: " << cliente.nombre << ' ' << cliente.apellidos << std::endl;
                            std::cout << "Fecha de nacimiento: " << cliente.fecha << std::endl;
                            std::cout << "Domicilio: " << cliente.domicilio << std::endl;
                            std::cout << "C.P.: " << cliente.codPostal << "  Localidad: " << cliente.localidad << std::endl;
                            std::cout << "N* Telefono: " << cliente.telef << std::endl;
                            std::cout << "----------------------------------------------------\n";
                        }
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        // Ver el registro de Empleado
                        // Mostrar la información de los Empleado por pantalla
                        std::cout << "Listado de emplados:" << std::endl;
                        for (const auto& p : empleados) {
                            std::string dni = p.first;
                            Empleado empleado = p.second;
                            std::cout << "Paciente con DNI/NIE: " << empleado.dni_nie << std::endl;
                            std::cout << "Nombre y apellidos: " << empleado.nombre << ' ' << empleado.apellidos << std::endl;
                            std::cout << "Fecha de nacimiento: " << empleado.fecha << std::endl;
                            std::cout << "Domicilio: " << empleado.domicilio << std::endl;
                            std::cout << "C.P.: " << empleado.codPostal << "  Localidad: " << empleado.localidad << std::endl;
                            std::cout << "N* Telefono: " << empleado.telef << std::endl;
                            std::cout << "Departamento: " << empleado.departamento << std::endl;
                            std::cout << "Categoria Profesional: " << empleado.catProfesion << std::endl;
                            std::cout << "----------------------------------------------------\n";
                        }
                        system("pause");
                        break;
                    default:
                        std::cout << "Opción 2 inválida" << std::endl;
                        break;
                }
                break;
            case 4: {
                // Salir del programa
                return 0;
            }
            default: {
                std::cout << "Opción inválida" << std::endl;
                break;
            }
        }
    }
}