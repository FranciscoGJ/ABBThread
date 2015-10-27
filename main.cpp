// @Author: Francisco Gonzalez
// Fixed by Roberto Konow

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <random>
#include <atomic>
#include "ABB.h"


int main() {

     ABB *a = new ABB();
     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_int_distribution<> dis(0, 100000000);

    int tamanio_tree = 10000000;
     for (int n = 0; n < tamanio_tree; n++){ //Tamaño del arbol
         a->Insert(dis(gen));
         //cout << dis(gen) << endl;
     }
    for(int i = 1; i <= 5;i++){ // 5 mediciones correspondiente a 10% .... 50%
        for(int num_thread = 2; num_thread <= 16; num_thread = num_thread*2){ // cantidad de thread
            queue<Node*> q;
            q = divide(a,num_thread);
            for(int num_med = 0; num_med < 30; num_med++){ //numero de mediciones
                vector<thread> th;
                for(int j = 0; j < num_thread;j++){
                    th.push_back(thread(print_inorder,q.front(),1200,8508000));
                    q.pop();
                }
                for(int j = 0; j < num_thread;j++){
                    th[j].join();
                }
            }
        }
    }


   /* queue<Node*> q;
    q = a->Print_by_level(a->m_root);
    vector<thread> th;

     for(int i = 0; i < 7;i++){

        cout << q.front()->data << endl;
        q.pop();
     }

     for(int i = 0; i < 8;i++){
        th.push_back(thread(print_inorder,q.front(),1200,8508000));
        q.pop();
     }

     for(int i = 0; i < 8; i++) {
        th[i].join();
     }

    cout << "entre" << endl;
    cout << print_inorder(q.front(),1200,850800) << endl;
    cout << elapsed_time << endl;*/
    delete a;
    return 0;
}