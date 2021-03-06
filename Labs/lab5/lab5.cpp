#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template <class T>
class node
{
  public:
    node *next;
    node *prev;
    T data;

    node(T d)
    {
        next = NULL;
        prev = NULL;
        data = d;
    }
};

template <class T>
class linked_list
{
  private:
    node<T> *head;
    node<T> *tail;
    node<T> *ptrUsr;

  public:

    linked_list()
    {
        head = NULL;
    }

    void reset_ptr()
    {
        ptrUsr = head;
    }

    void adv_ptr()
    {
        if(ptrUsr->next) ptrUsr = ptrUsr->next;
    }

    void rew_ptr()
    {
        if(ptrUsr) { ptrUsr = ptrUsr->prev; }
    }

    T getup()
    {
        if(ptrUsr) return ptrUsr->data;
        else {
            return 0;
        }
    }

    T get(int n)
    {
        if (n < size())
        {
            node<T> *tptr = head;
            for (int i = 0; i < n; i++)
                tptr = tptr->next;
            return tptr->data;
        }
        else
            return (T)0;
    }

    T get_first()
    {
        if (head)
            return head->data;
        else
            return (T)0;
    }

    T get_last()
    {
        if (head)
        {
            node<T> *ptr = head;
            while (ptr->next)
                ptr = ptr->next;
            return ptr->data;
        }
        else
            return (T)0;
    }

    int size()
    {
        node<T> *tptr = head;

        int c = 0;

        while (tptr)
        {
            c++;
            tptr = tptr->next;
        }

        return c;
    }

    void add(int index, T d)
    {
        int count = size();

        // Outside bounds of the array
        if (index > count || index < 0) return;

        // If inserting at the beginning...
        if (index == 0)
        {
            node<T> *nhp = new node<T>(d);

            // ... and there is already a node at the beginnning
            if(head) {
                nhp->next = head;
                head->prev = nhp;
                head = nhp;
            }
            // ... and there is no node at the beginning 
            else {
                head = nhp;
                tail = head;
                ptrUsr = nhp;
            }
        }
        // If inserting at the end
        else if (index == count)
        {
            node<T> *tptr = head;
            while (tptr->next != NULL) tptr = tptr->next;
            tptr->next = new node<T>(d);
            tail = tptr->next;
            tail->prev = tptr;
        }
        // If inserting in the middle
        else if (index < count)
        {
            node<T> *tptr = head;
            node<T> *nptr = new node<T>(d);
            for (int i = 0; i < index - 1; i++)
            {
                tptr = tptr->next;
            }
            nptr->next = tptr->next;
            tptr->next = nptr;
            nptr->prev = tptr;
            nptr->next->prev = nptr;
        }
    }

    void add_first(T d)
    {
        add(0, d);
    }

    void add_last(T d)
    {
        add(size(), d);
    }

    void remove_first()
    {
        remove(0);
    }

    void remove_last()
    {
        remove(size() - 1);
    }

    void remove(int n)
    {
        // If list is empty
        if (!head) return;

        // If n is outside of list
        if (n >= size()) return;

        // If removing the only node
        if (n == 0 && size() == 1)
        {
            delete head;
            head = NULL;
            tail = NULL;
            ptrUsr = NULL;
            return;
        }

        node<T> *tptr = head;
        node<T> *delptr;

        // If removing the head node
        if (n == 0)
        {
            tptr = head;
            if(ptrUsr == head) adv_ptr();
            head = tptr->next;
            head->prev = NULL;
            delete tptr;
            return;
        }

        for (int i = 0; i < n - 1; i++) tptr = tptr->next;

        delptr = tptr->next;

        if (delptr->next) 
        {
            if(delptr == ptrUsr) adv_ptr();
            tptr->next = delptr->next;
            tptr->next->prev = tptr;
        }
        else {
            if(delptr == ptrUsr) rew_ptr();
            tptr->next = NULL;
            tail = tptr;
        }

        delete delptr;
    }
    void dump()
    {
        node<T> *tptr;
        node<T> *hptr;

        cout << "    DUMP: (size = " << size() << ", first = " << get_first() << ", last = " << get_last() << ")\n";

        if (head == NULL)
        {
            cout << "    DUMP: head = NULL\n\n";
            return;
        }

        hptr = head;
        tptr = tail;

        cout << "    DUMP:   head = " << hptr->data << "   tail = " << tail->data << endl;
        while (hptr->next != NULL)
        {
            hptr = hptr->next;
            tptr = tptr->prev;
            cout << "    DUMP:   data = " << hptr->data << "   data = " << tptr->data << endl;
        }
        cout << endl;
    }
};

int main(void)
{
    linked_list<int> ll;
    string cmd;
    int d, i;

    while (cin >> cmd >> i >> d)
    {

        cout << "MAIN: cmd = " << cmd << ", index = " << i
             << ", data = " << d << endl;

        if (cmd == "add")
            ll.add(i, d);
        else if (cmd == "addf")
            ll.add_first(d);
        else if (cmd == "addl")
            ll.add_last(d);
        else if (cmd == "rem")
            ll.remove(i);
        else if (cmd == "remf")
            ll.remove_first();
        else if (cmd == "reml")
            ll.remove_last();
        else if (cmd == "get")
        {
            d = ll.get(i);
            cout << "get returns: " << d << endl;
        }
        else if (cmd == "getf")
        {
            d = ll.get_first();
            cout << "getf returns: " << d << endl;
        }
        else if (cmd == "getl")
        {
            d = ll.get_last();
            cout << "getl returns: " << d << endl;
        }
        else if (cmd == "reset")
        { // set user ptr to head of list
            ll.reset_ptr();
        }
        else if (cmd == "adv")
        { // advance user ptr to next node
            ll.adv_ptr();
        }
        else if (cmd == "rew")
        { // rewind  user ptr to prev node
            ll.rew_ptr();
        }
        else if (cmd == "getup")
        { // return value at user ptr node
            int i = ll.getup();
            cout << "getup returns: " << i << endl;
        }
        else if (cmd == "dump")
            ll.dump();
        else if (cmd == "quit")
            exit(0);
    }
}
