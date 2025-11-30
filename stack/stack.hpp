#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <functional>

/**
 * @class stack
 * @brief representacion de la estructura de datos pila por medio de punteros a nodo
 */
template <typename type>
class stack
{
private:
    /**
     * @struct estructura nodo para empaquetar la lista simplemente enlazada
     */
    struct nodo
    {
        type data;
        nodo *prox;
        nodo(const type &valor) : data(valor), prox(nullptr) {}
    };

    nodo *tope; // tope de la pila
    size_t size;

public:
    /*-------constructores-------*/

    /**
     * @construtor
     * @brief inizializa la pila vacia
     */
    stack() : tope(nullptr), size(0) {}

    /**
     * @brief inizializa la pila con elemento inicial
     */
    stack(const type &valor) : tope(new nodo(valor)), size(1) {}

    stack(const std::initializer_list<type> &init) : tope(nullptr), size(0)
    {
        for (auto it = init.end() - 1; it >= init.begin(); --it)
        {
            push(*it);
        }
    }

    stack(const stack<type> &other) : tope(nullptr), size(0)
    {
        if (!other.empty())
        {
            type *tempArray = new type[other.size];
            nodo *current = other.tope;
            for (size_t i = 0; i < other.size; ++i)
            {
                tempArray[i] = current->data;
                current = current->prox;
            }

            for (int i = other.size - 1; i >= 0; --i)
            {
                push(tempArray[i]);
            }
            delete[] tempArray;
        }
    }

    /*-------modificadores-------*/

    /**
     *
     * @brief apila un nuevo elemento en la pila
     * @param valor nuevo elemento a agregar
     * @note complejidad temporal: O(1)
     */
    void push(const type &valor)
    {
        nodo *aux = new nodo(valor);
        if (!aux)
        {
            throw std::runtime_error("Error: no se pudo asignar memoria"); // CORREGIDO
        }

        aux->prox = tope;
        tope = aux;
        size++;
    }

    /**
     * @brief desapila un elemento de la pila
     * @note complejidad temporal: O(1)
     * @note la pila no puede estar vacia cuando se desapile
     */
    void pop()
    {
        if (empty())
        {
            throw std::runtime_error("Error: pila vacia");
        }
        nodo *temp = tope;
        tope = tope->prox;
        delete temp;
        size--;
    }

    /*-------consultores---------*/

    /**
     * @brief consulta la longitud de la pila
     * @return cantidad de elementos que se encuentran en la pila
     * @note complejidad temporal: O(1)
     */
    size_t lenght() const { return size; }

    /**
     * @brief consulta si la pila se encuentra vacia
     * @return 1 si la pila se encuentra vacia o 0 en caso contrio
     * @note complejidad temporal: O(1)
     */
    bool empty() const { return size == 0; }

    /**
     * @brief consulta el primer elemento de la pila
     * @return el elemento que se encuentre en el tope de la pila
     * @note complejidad temporal: O(1)
     */
    type top() const
    {
        if (empty())
        {
            throw std::runtime_error("Error: pila vacia\n");
        }
        return tope->data;
    }

    /**
     * @brief consulta el ultimo elemento de la pila
     * @return el elemento que se encuentra al final de la pila
     * @note complejidad temporal: O(n)
     */
    type tail()
    {
        if (empty())
        {
            throw std::runtime_error("Error: pila vacia\n");
        }

        nodo *current = tope;
        while (current->prox != nullptr)
        {
            current = current->prox;
        }
        return current->data;
    }

    /*-------destructores--------*/

    /**
     * @brief destruye la pila por completo
     * @note realiza una limpieza de memoria para evitar uso inecesario de memoria
     * @note complejidad temporal: O(n)
     */
    void clear()
    {
        while (!empty())
        {
            pop();
        }
    }

    ~stack()
    {
        clear();
    }

    /*--------operadores---------*/
    type operator[](const size_t pos) const
    {
        if (pos >= size)
        {
            throw std::out_of_range("Error: indice fuera de rango");
        }

        nodo *current = tope;
        for (size_t i = 0; i < pos; ++i)
        {
            current = current->prox;
        }
        return current->data;
    }

    stack<type> &operator=(const stack<type> &other)
    {
        if (this != &other)
        {
            clear();
            if (!other.empty())
            {
                type *tempArray = new type[other.size];
                nodo *current = other.tope;
                for (size_t i = 0; i < other.size; ++i)
                {
                    tempArray[i] = current->data;
                    current = current->prox;
                }

                for (int i = other.size - 1; i >= 0; --i)
                {
                    push(tempArray[i]);
                }
                delete[] tempArray;
            }
        }
        return *this;
    }
};

#endif