#include "stack.h"
#include <cstring>

namespace laba{

    template <typename T>
    void Stack<T>::push(T info){
        if(count == all){
            all = all * 2 + 1;
            T* temp = new T[all];

            for(int i = 0; i < count; i++){
                temp[i] = this->info[i];
            }
            delete[] this->info;
            this->info = temp;
        }
        this->info[count] = info;
        count += 1;
    }

// a
// a = b
// a = a
    template <typename T>
    Stack<T>& Stack<T>::operator=(const Stack<T> &stack){
        if(this==&stack)return *this;
        count = stack.count;
        all = stack.all;
        // delete
        info = new T[all];
        for(int i = 0; i < stack.count; i++)info[i] = stack.info[i];
        return *this;
    }

    template <typename T>
    Stack<T>& Stack<T>::operator=(Stack<T>&& stack)noexcept{
        if(this==&stack)return *this;
        all = stack.all;
        count = stack.count;
        //delete
        info = stack.info;
        stack.info = nullptr;
        stack.count = 0;
        stack.all = 0;
        return *this;

    }

    template <typename T>
    Stack<T>::~Stack(){
        if(all != 0){//?

            delete[] info;
        }
        count = 0;
        all = 0;
    }

    template <typename T>
    Stack<T>::Stack(Stack&& stack) noexcept{
        info = stack.info;
        stack.info = nullptr;
        all = stack.all;
        count = stack.count;
        stack.count = 0;
        stack.all = 0;
    }

    template <typename T>
    Stack<T>::Stack(){
        count = 0;
        all = 1;
        info = new T[all];
    }

    template <typename T>
    template <typename Itter>
    Stack<T>::Stack(Itter begin, Itter end){
                    int dis = std::distance(begin, end);
                    count = 0;
                    if(dis <= 0)throw Stack_Exception();//?
                    info = new T[dis*2];
                    for(Itter it = end - 1; it != begin-1; it--){
                        info[count++]=*it;
                    }
                    all = dis * 2;
                };

    template<typename T>
    Stack<T>::Stack(std::initializer_list<T>& list)//? {}
    {
        count = list.size();

        all = list.size() * 2;

        info = new T[all];//

        int i = count - 1;

    	for (T item : list) {
            info[i] = item;
            i--;
        }
    }

    template <typename T>
    Stack<T>::Stack(const Stack<T> &stack){
        count = stack.count;
        all = stack.all;
        info = new T[all];
        for(int i = 0; i < stack.count; i++)info[i] = stack.info[i];
    }

    template <typename T>
    T Stack<T>::pop(){
        if(!empty()){
            T temp = info[count - 1];
            count--;
            if(count * 5 < all){
                T* temp = new T[count];
                for(int i = 0; i < count; i++){
                    temp[i] = info[i];
                }
                delete[] info;
                info = temp;
                all = count;
            }
            return temp;

        }else{
            throw Stack_Exception();
        }

    }

    template <typename T>
    T Stack<T>::check_pop() const{
        if(!empty()){
            return info[count-1];
        }else{
            throw Stack_Exception();
        }
    }

    template <typename T>
    int Stack<T>::size() const noexcept{
        return count;
    }

    template <typename T>
    bool Stack<T>::empty() const noexcept{
        return count == 0;
    }

    template <typename T>
    void Stack<T>::top(T& info){
        if(!empty())this->info[count - 1] = info;
    }

    template <typename T>
    void Stack<T>::clear(){
        if(empty())return;
        count = 0;
        all = 0;
    }

    template <typename T>
    void Stack<T>::swap(T& info){
        if(empty())return;
        T temp = this->info[count - 1];
        this->info[count - 1] = info;
        info = temp;
    }

    template <typename T>
    bool Stack<T>::operator==(const Stack<T>& s1) const{
        if(count != s1.count){
            return false;
        }
        else{
            for(int i = 0; i < count; i++){
                if(info[i] != s1.info[i]){
                    return 0;
                }
            }
            return 1;
        }
    }

    template <typename T>
    bool Stack<T>::operator!=(const Stack<T>& s1) const{
        return !(*this == s1);
    }

    template <typename T>
    Stack<T>& Stack<T>::operator>>(T& info){
        info = pop();
        return *this;
    }

    template <typename T>
    Stack<T>& Stack<T>::operator<<(T info){
        push(info);
        return *this;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& out, const Stack<T>& stack){
        out << "STACK CONTAINS " << stack.count << " ELEMENTS\n";
        for(int i = 0; i < stack.count; i++){
            out << stack.info[i] << " ";
        } 
        return out;
    }
};