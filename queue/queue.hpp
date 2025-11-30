#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename type>
class queue
{
private:
    struct nodo
    {
        type dato;
        nodo *prox;
        nodo *ant;
        nodo(const type &valor) : dato(valor), prox(nullptr), ant(nullptr) {}
    };

    nodo *head;
    nodo *tail;
    size_t size;

public:
    // Constructores
    queue() : head(nullptr), tail(nullptr), size(0) {}

    queue(const type &valor) : head(new nodo(valor)), tail(head), size(1) {}

    queue(const queue<type> &other) : head(nullptr), tail(nullptr), size(0)
    {
        nodo *actual = other.head;
        while (actual != nullptr)
        {
            push(actual->dato);
            actual = actual->prox;
        }
    }

    queue<type> &operator=(const queue<type> &other)
    {
        if (this != &other)
        {
            clear();
            nodo *actual = other.head;
            while (actual != nullptr)
            {
                push(actual->dato);
                actual = actual->prox;
            }
        }
        return *this;
    }

    /*-----------modificadores-----------*/

    /**
     * @brief Añade un nuevo elemento al final de la cola
     * @param valor nuevo elemento a añadir
     * @note complejidad temporal: O(1)
     */
    void push(const type &valor)
    {
        nodo *nuevo = new nodo(valor);

        if (head == nullptr)
        {
            head = nuevo;
            tail = nuevo;
        }
        else
        {
            nuevo->ant = tail;
            tail->prox = nuevo;
            tail = nuevo;
        }
        size++;
    }

    /**
     * @brief Elimina el primer elemento que se encuentre en la cola
     * @note complejidad temporal: O(1)
     */
    void pop()
    {
        if (empty())
        {
            throw std::runtime_error("Error: cola vacia\n");
        }

        nodo *temp = head;
        head = head->prox;

        if (head != nullptr)
        {
            head->ant = nullptr;
        }
        else
        {
            // Si head es nullptr, la cola quedó vacía
            tail = nullptr;
        }

        delete temp;
        size--;
    }

    /*------------consultores------------*/

    /**
     * @brief Consulta la longitud de la cola
     * @return retorna el numero de elementos que se encuentre en la cola
     * @note complejidad temporal: O(1)
     */
    size_t lenght() const { return size; }

    /**
     * @brief Consulta se la cola se encuentra vacia
     * @return 1 en caso que se encuentre vacia o 0 en caso contrario
     * @note complejidad temporal: O(1)
     */
    bool empty() const { return size == 0; }

    /**
     * @brief Consulta el primer elemento de la cola
     * @return el elemento que se encuentre en el frente de la cola
     * @note complejidad temporal: O(1)
     */
    type front() const
    {
        if (empty())
        {
            throw std::runtime_error("Error: cola vacia\n");
        }
        return head->dato;
    }

    /**
     * @brief Consulta el primer elemento de la cola
     * @return el elemento que se encuentre en el frente de la cola
     * @note complejidad temporal: O(1)
     */
    type last() const
    {
        if (empty())
        {
            throw std::runtime_error("Error: cola vacia\n");
        }
        return tail->dato;
    }

    /*----------destructores------------*/
    /**
     * @brief Destructor: elimina todos los elementos de la cola
     * @note vacia la cola por completo
     * @note complejidad temporal: O(n)
     */
    void clear()
    {
        while (!empty())
        {
            pop();
        }
    }

    ~queue()
    {
        clear();
    }

    /*------------operadores------------*/
    bool operator==(const queue<type> &other) const
    {
        if (size != other.size)
        {
            return false;
        }

        nodo *actual1 = head;
        nodo *actual2 = other.head;

        while (actual1 != nullptr)
        {
            if (actual1->dato != actual2->dato)
            {
                return false;
            }
            actual1 = actual1->prox;
            actual2 = actual2->prox;
        }
        return true;
    }

    bool operator!=(const queue<type> &other) const
    {
        return !(*this == other);
    }

    type &operator[](size_t pos)
    {
        if (empty())
        {
            throw std::runtime_error("Error: cola vacia\n");
        }

        if (pos >= size)
        {
            throw std::range_error("Error: posicion fuera de rango\n");
        }

        nodo *aux = head;
        for (size_t i = 0; i < pos; i++)
        {
            aux = aux->prox;
        }

        return aux->dato;
    }

    const type &operator[](size_t pos) const
    {
        if (empty())
        {
            throw std::runtime_error("Error: cola vacia\n");
        }

        if (pos >= size)
        {
            throw std::range_error("Error: posicion fuera de rango\n");
        }

        nodo *aux = head;
        for (size_t i = 0; i < pos; i++)
        {
            aux = aux->prox;
        }

        return aux->dato;
    }
};

#endif
