#include <stdlib.h>
#include <string.h>

// Clase ArduVector
template<typename Data>

class ArduVector {

    public:
        ArduVector() : d_size(0), d_capacity(0), d_data(0) {}; // Constructor
        ArduVector(ArduVector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) {
            d_data = (Data *)malloc(d_capacity * sizeof(Data));
            memcpy(d_data, other.d_data, d_size * sizeof(Data));
        }; // Constuctor copia
        ~ArduVector() { free(d_data); }; // Destructor

        ArduVector &operator=(ArduVector const &other) { // Sobrecargas a operadores
            free(d_data); d_size = other.d_size;
            d_capacity = other.d_capacity;
            d_data = (Data *)malloc(d_capacity * sizeof(Data));
            memcpy(d_data, other.d_data, d_size * sizeof(Data));
            return *this;
        };
        Data const &operator[](size_t idx) const { return d_data[idx]; };
        Data &operator[](size_t idx) {
            if(idx > d_capacity)
            {
                resize(idx+1);
                d_size = idx + 1;
            }
            return d_data[idx];
        };

        void push_back(Data const &x) { // Añade elemento
            if (d_capacity == d_size) resize();
            d_data[d_size++] = x;
        };
        size_t size() const { return d_size; }; // Obtiene tamaño
        size_t capacity() const { return d_capacity; }; // Obtiene capacidad
        void reserve(size_t num) { // Reserva capacidad
            if(num > d_capacity && num <= MAX_VSIZE)
                resize(num);
        }
        void shrink_to_fit() { // Reduce la capacidad el vector a su tamaño
            if(d_capacity > d_size) {
                d_capacity = d_size;
                resize(d_size);
            }
        };
        bool empty() const { return (d_size == 0) ? true: false; }; // Indica si hay elementos
        void sort() { // Ordenación por inserción
            for(size_t i = 1; i < size(); ++i) {
                Data tmp = d_data[i];
                size_t j = i;
                while(j > 0 && tmp < d_data[j - 1]) {
                    d_data[j] = d_data[j - 1];
                    --j;
                }
                d_data[j] = tmp;
            }
        }

    private:
        static const size_t MAX_VSIZE = 1024; // Tamaño máximo permitido para el vector
        static const char NULLCHAR = '\0'; // Caracter nulo
        size_t d_size; // Elementos actualmente almacenados
        size_t d_capacity; // Capacidad total
        Data *d_data; // Puntero a datos

        void resize(size_t tam = 0) { // Incrementa el tamaño reservado
            d_capacity = (tam == 0) ? d_capacity + 1 : tam;
            Data *newdata = (Data *)malloc(d_capacity * sizeof(Data));
            memset(newdata, NULLCHAR, d_capacity * sizeof(Data));
            memcpy(newdata, d_data, d_size * sizeof(Data));
            free(d_data);
            d_data = newdata;
        };
};
