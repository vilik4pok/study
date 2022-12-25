#include <iostream>
#include <cstdlib>

template<class T> class Queue2
{
   struct element
   {
      T data;
      element * next;
   } *head, *tail; //индексы головы и хвоста
 public:
   Queue2 () {head=tail=NULL;}
   ~Queue2 ();
   bool isEmpty (void);
   bool isFull (void);
   T Front (void);
   bool EnQueue (T x);
   T DeQueue (void);
};

template<class T>
bool Queue2<T>::isEmpty(void)
{
   return head==NULL;
}

template<class T>
bool Queue2<T>::isFull(void)
{
   element *temp = new (std::nothrow) element;
   if (temp==NULL) return 1;
   delete temp;
   return 0;
}

template<class T>
T Queue2<T>::Front (void)
{
   return head->data;
}

template<class T>
bool Queue2<T>::EnQueue (T x)
{
   element * temp = new (std::nothrow) element;
   if (temp==NULL) return 1;
   temp->data = x;
   temp->next = NULL;
   if (head==NULL)
      head = tail = temp;
   else
   {
      tail->next = temp;
      tail = tail->next;
   }
   return 1;
}

template<class T>
T Queue2<T>::DeQueue (void)
{
   T temp = head->data;
   element * tmp = head;
   head = head->next;
   delete tmp;
   return temp;
}

template<class T>
Queue2<T>::~Queue2 ()
{
   element * temp = head;
   while (head)
   {
         temp = head;
         head = head->next;
         delete temp;
   }
}
