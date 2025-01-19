//***********|**********|**********|
// Program : main.cpp
// Course : Data Structures and Algorithms
// Trimester : 2410 
// Name : Khong Wei Yi,Tang Wei Xiong, Enoch Tan Jeng Shen, Hamza Waleed Abdulqader Baharoon
// ID : 1211111275, 1211112069, 1211112081, 1221305803
// Lecture Section : TC2L
// Tutorial Section : TT5L
// Email : 1211111275@soffice.mmu.edumy , 1211112069@soffice.mmu.edu.my , 1211112081@soffice.mmu.edu.my , 1221305803@soffice.mmu.edu.my
// Phone : +60 11-5002 0161 , +60 11-5550 7147 , +60 19-942 2513 , +60 19-732 6788
//***********|***********|***********/

#include <iostream> 
using namespace std; 

template<class T> 

struct Node 
{ 
    T data; 
    Node<T>* next; 
    Node(T x) 
    { 
        data = x; 
        next = nullptr; 
    } 
}; 

template<class T> 
class Queue 
{ 
    
private: 
    Node<T>* front_; 
    Node<T>* back_; 
    int sz; 

public: 

    Queue() 
    { 
        sz = 0; 
        front_ = back_ = nullptr; 
    } 

    ~Queue() // Destructor 
    { 
        sz = 0; 
        while( !empty() ) 
        dequeue(); 
    } 


    Queue(const Queue<T>& q) // CC 
    { 
        //cout << "CC" << "\n"; 
        sz = 0; 
        front_ = back_ = nullptr; 
        Node<T>* ptr = q.front_; 
        while( ptr != nullptr ) 
        { 
            enqueue(ptr->data); 
            ptr = ptr->next; 
        } 

    } 


    Queue& operator=(const Queue<T>& q) // Copy Assignment Operator 
    { 
        //cout << "CAO" << "\n"; 
        if (this != &q) 
        { 
            sz = 0; 
            front_ = back_ = nullptr; 
            Node<T>* ptr = q.front_; 
            while( ptr != nullptr ) 
            { 
                enqueue(ptr->data); 
                ptr = ptr->next; 
            } 
        } 
        return *this; 
    } 


    Queue(Queue<T>&& q) // move constructor 

    { 
        //cout << "MC" << "\n"; 
        sz = q.size(); 
        front_ = q.front_; 
        back_ = q.back_; 
        q.sz = 0;
        q.front_ = nullptr; 
        q.back_ = nullptr; 
    } 


    Queue& operator=(Queue<T>&& q) // move assignment operator 
    { 
        //cout << "MAO" << "\n"; 
        if (this != &q) 
        { 
        swap(sz, q.sz); 
        swap(front_, q.front_); 
        swap(back_, q.back_); 
        } 
        return *this; 
    } 


    bool empty() 
    { 
        if (front_ == nullptr) 
            return true; 
        else 
            return false; 
    } 


    int size() 
    { 
        return sz; 
    } 


    T front() 
    { 
        return front_->data; 
    } 


    T back() 
    { 
        return back_->data; 
    } 


    void enqueue(T x) 
    { 
        if ( empty() ) 
        { 
            front_ = new Node<T>(x); 
            back_ = front_; 
        } 
        else 
        { 
            back_->next = new Node<T>(x); 
            back_ = back_->next; 
        } 
        sz++; 
    } 


    void dequeue() 
    { 
        if ( !empty() ) 
        { 
            Node<T>* p = front_; 
            T x = front_->data; 
            front_ = front_->next; 
            delete p; 
            sz--; 
        } 
        else 
        { 
            cout << "Queue is empty\n"; 
            exit(EXIT_FAILURE); 
        } 
    } 


    // declaration of template parameter 'U' unshadows template parameter 'T' 
    template <class U> 
    friend ostream& operator<< (ostream& os, const Queue<U>& q);

}; 


template <class T> 

ostream& operator<< (ostream& os, const Queue<T>& q) 
{ 
    Node<T>* ptr = q.front_; 
    while( ptr != nullptr ) 
    { 
        os << ptr->data << ' '; 
        ptr = ptr->next; 
    } 
    return os; 
} 

