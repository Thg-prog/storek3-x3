#ifndef LABA4_polynom_H
#define LABA4_polynom_H

#include <iostream>


namespace laba{

    class Stack_Exception : public std::exception{
    public:
        const char *what() const noexcept override{
            return exception::what();
        }
    };

    template <typename T>
    class Stack{
        private:
            std::size_t all;
            int count;
            T* info;

        public:
            Stack();

            Stack(const Stack &stack);
            Stack(Stack &&stack) noexcept;

            Stack(std::initializer_list<T>& list);
            template <typename Itter>
            Stack(Itter begin, Itter end);
            
            ~Stack();//? +

            Stack& operator=(const Stack &stack); //? +
            Stack& operator=(Stack &&stack) noexcept; //? +
            bool operator==(const Stack& s1) const; //? +
            bool operator!=(const Stack& s1) const; //? +

            // stack1 << 1 << 3 << 5;
            Stack& operator<<(T info); //? +

            // stack1 >> a >> b;
            Stack& operator>>(T& info);

            void push(T info);
            T pop();
            T check_pop() const;

            bool empty() const noexcept;
            void clear();//? noexcept
            int size() const noexcept;

            void top(T& info);

            void swap(T& info);


            template <typename U> friend std::ostream& operator<< (std::ostream& out, const Stack<U>& stack);
    };


}

/*template <typename T>
laba::Stack<T>::Stack(){
    count = 0;
}*/



#endif