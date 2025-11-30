#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <functional>

/**
 * @brief lista doblemente enlazada
 */
template <typename type>
class list
{
private:
    typedef struct nodo
    {
        type dato;
        struct nodo *ant;
        struct nodo *prox;

        // Constructor para facilitar la creacion de nodos
        nodo(const type &valor) : dato(valor), ant(nullptr), prox(nullptr) {}
    } nodo;

    nodo *head;
    nodo *tail;
    size_t size;

public:
    // Constructores
    list() : head(nullptr), tail(nullptr), size(0) {}

    list(std::initializer_list<type> init) : head(nullptr), tail(nullptr), size(0)
    {
        for (const auto &elemento : init)
        {
            push_back(elemento);
        }
    }

    // Constructor de copia
    list(const list &otra) : head(nullptr), tail(nullptr), size(0)
    {
        nodo *actual = otra.head;
        while (actual != nullptr)
        {
            push_back(actual->dato);
            actual = actual->prox;
        }
    }

    // Operador de asignación
    list &operator=(const list &otra)
    {
        if (this != &otra)
        {
            clear();
            nodo *actual = otra.head;
            while (actual != nullptr)
            {
                push_back(actual->dato);
                actual = actual->prox;
            }
        }
        return *this;
    }

    size_t lenght() const { return this->size; }

    bool empty() const { return this->size == 0; }

    type first() const
    {
        if (empty())
        {
            throw std::runtime_error("Lista vacía");
        }
        return this->head->dato;
    }

    type last() const
    {
        if (empty())
        {
            throw std::runtime_error("Lista vacía");
        }
        return this->tail->dato;
    }

    void push_front(const type &valor)
    {
        nodo *nuevo = new nodo(valor);
        if (empty())
        {
            head = tail = nuevo;
        }
        else
        {
            nuevo->prox = head;
            head->ant = nuevo;
            head = nuevo;
        }
        size++;
    }

    void push_back(const type &valor)
    {
        nodo *nuevo = new nodo(valor);
        if (empty())
        {
            head = tail = nuevo;
        }
        else
        {
            tail->prox = nuevo;
            nuevo->ant = tail;
            tail = nuevo;
        }
        size++;
    }

    void push(const type &valor, size_t pos = 0)
    {
        if (pos > size)
        {
            throw std::out_of_range("Posición fuera de rango");
        }

        if (pos == 0)
        {
            push_front(valor);
            return;
        }
        else if (pos == size)
        {
            push_back(valor);
            return;
        }

        nodo *nuevo = new nodo(valor);
        nodo *actual = head;

        for (size_t i = 0; i < pos; i++)
        {
            actual = actual->prox;
        }

        nuevo->ant = actual->ant;
        nuevo->prox = actual;
        actual->ant->prox = nuevo;
        actual->ant = nuevo;

        size++;
    }

    void pop(size_t pos = 0)
    {
        if (empty())
        {
            throw std::runtime_error("Lista vacía");
        }

        if (pos >= size)
        {
            throw std::out_of_range("Posición fuera de rango");
        }

        if (pos == 0)
        {
            pop_front();
            return;
        }
        else if (pos == size - 1)
        {
            pop_back();
            return;
        }

        nodo *actual = head;

        for (size_t i = 0; i < pos; i++)
        {
            actual = actual->prox;
        }

        actual->ant->prox = actual->prox;
        actual->prox->ant = actual->ant;

        delete actual;
        size--;
    }

    void pop_front()
    {
        if (empty())
            return;

        nodo *temp = head;
        head = head->prox;
        if (head != nullptr)
        {
            head->ant = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        delete temp;
        size--;
    }

    void pop_back()
    {
        if (empty())
            return;

        nodo *temp = tail;
        tail = tail->ant;
        if (tail != nullptr)
        {
            tail->prox = nullptr;
        }
        else
        {
            head = nullptr;
        }

        delete temp;
        size--;
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    ~list()
    {
        clear();
    }

    // Iteradores
    class iterator
    {
    private:
        nodo *actual;

    public:
        iterator(nodo *n) : actual(n) {}

        type &operator*() { return actual->dato; }
        type *operator->() { return &actual->dato; }

        iterator &operator++()
        {
            actual = actual->prox;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator &operator--()
        {
            actual = actual->ant;
            return *this;
        }

        iterator operator--(int)
        {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator &otro) const { return actual == otro.actual; }
        bool operator!=(const iterator &otro) const { return actual != otro.actual; }
    };

    class const_iterator
    {
    private:
        const nodo *actual;

    public:
        const_iterator(const nodo *n) : actual(n) {}

        const type &operator*() const { return actual->dato; }
        const type *operator->() const { return &actual->dato; }

        const_iterator &operator++()
        {
            actual = actual->prox;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }

        const_iterator &operator--()
        {
            actual = actual->ant;
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const const_iterator &otro) const { return actual == otro.actual; }
        bool operator!=(const const_iterator &otro) const { return actual != otro.actual; }
    };

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    const_iterator begin() const { return const_iterator(head); }
    const_iterator end() const { return const_iterator(nullptr); }

    const_iterator cbegin() const { return const_iterator(head); }
    const_iterator cend() const { return const_iterator(nullptr); }

    /**
     * @brief Método foreach personalizado
     * @param func Función a aplicar a cada elemento
     */
    void foreach (std::function<void(type &)> func)
    {
        for (auto it = begin(); it != end(); ++it)
        {
            func(*it);
        }
    }

    /**
     * @brief Método foreach personalizado (versión constante)
     * @param func Función a aplicar a cada elemento
     */
    void foreach (std::function<void(const type &)> func) const
    {
        for (auto it = cbegin(); it != cend(); ++it)
        {
            func(*it);
        }
    }

    type &operator[](size_t pos)
    {
        if (pos >= size)
        {
            throw std::out_of_range("Índice fuera de rango");
        }

        nodo *aux = head;
        for (size_t i = 0; i < pos && aux != nullptr; i++)
        {
            aux = aux->prox;
        }

        if (aux == nullptr)
        {
            throw std::out_of_range("Índice fuera de rango");
        }

        return aux->dato;
    }

    const type &operator[](size_t pos) const
    {
        if (pos >= size)
        {
            throw std::out_of_range("Índice fuera de rango");
        }

        nodo *aux = head;
        for (size_t i = 0; i < pos && aux != nullptr; i++)
        {
            aux = aux->prox;
        }

        if (aux == nullptr)
        {
            throw std::out_of_range("Índice fuera de rango");
        }

        return aux->dato;
    }

    const type &at(size_t pos) const
    {
        if (pos < 1 || pos > size)
        {
            throw std::out_of_range("Posición fuera de rango");
        }
        return operator[](pos - 1);
    }

    friend std::ostream &operator<<(std::ostream &os, const list<type> &lista)
    {
        os << "[";
        typename list<type>::nodo *actual = lista.head;
        size_t count = 0;

        while (actual != nullptr)
        {
            os << actual->dato;
            if (actual->prox != nullptr)
            {
                os << ", ";
            }
            actual = actual->prox;
            count++;
        }

        os << "]";
        return os;
    }
};

#endif