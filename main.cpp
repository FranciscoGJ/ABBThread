// @Author: Francisco Gonzalez
// Fixed by Roberto Konow

#include <iostream>
#include <thread>
#include <queue>
#include <random>
#include "ABB.h"


int main() {

   ABB *a = new ABB();
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000000);

    for (int n = 0; n < 1000000; n++){
        a->Insert(dis(gen));
        //cout << dis(gen) << endl;
    }*/
    a->Insert(17);
    a->Insert(45);
    a->Insert(35);
    a->Insert(67);
    a->Insert(56);
    a->Insert(67);
    a->Insert(83);
    a->Insert(48);
    a->Insert(79);
    a->Insert(4);

    queue<Node*> q;
    q = a->Print_by_level(a->m_root);
    print_inorder(a->m_root,0,1000);
    cout << "....." << endl;
    vector<thread> th;
    for(int i = 0; i < 1;i++){
        cout << q.front()->data << endl;
        q.pop();
    }
    for(int i = 0; i < 2;i++){
        th.push_back(thread(print_inorder,q.front(),12,80));
        q.pop();
    }
    for(int i = 0; i < 2; i++) {
        th[i].join();
    }

    delete a;
    return 0;
}