//
// Created by francisco on 27-09-15.
//

#ifndef ABBTHREAD_ABB_H
#define ABBTHREAD_ABB_H

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include "Node.h"
#include <queue>


using namespace std;
atomic<int> cont;

class ABB{

public:
    Node* m_root;
    ABB() : m_root(nullptr){}

    void Insert(int data){

        if(m_root == nullptr){
            m_root = new Node(data);
        }else{
            Node* aux = m_root;
            while(aux != nullptr){
                if(data < aux->data){
                    if(aux->m_left == nullptr){
                        aux->m_left = new Node(data);
                        return;
                    }
                    aux = aux->m_left;
                }else if(data > aux->data){
                    if(aux->m_right == nullptr){
                        aux->m_right = new Node(data);
                        return;
                    }
                    aux = aux->m_right;
                }else{
                    return;
                }
            }
        }
    }

    queue<Node*> Print_by_level(Node* root){
        queue<Node*> q;
        queue<Node*> m_q;
        q.push(root);
        int cont = 0;
        while(!q.empty() && cont != 7){
            if(q.front()->m_left != nullptr){

                q.push(q.front()->m_left);
            }
            if(q.front()->m_right != nullptr){
                q.push(q.front()->m_right);
            }
            m_q.push(q.front());
            cont++;
            q.pop();
        }
        return m_q;
    }

    void Search_2(Node* root,int lower_bound,int upper_bound){
        if(root != nullptr) {
            queue<Node *> q;
            q.push(root);
            while (!q.empty()) {
                if (q.front()->m_left != nullptr) {
                    if (q.front()->m_left->data >= lower_bound && q.front()->m_left->data <= upper_bound) {
                        q.push(q.front()->m_left);
                    } else {
                        Search_2(q.front()->m_left->m_right, lower_bound, upper_bound);
                    }
                }

                if (q.front()->m_right != nullptr) {
                    if (q.front()->m_right->data >= lower_bound && q.front()->m_right->data <= upper_bound) {
                        q.push(q.front()->m_right);
                    } else {
                        Search_2(q.front()->m_right->m_left, lower_bound, upper_bound);
                    }
                }
                if (q.front()->data >= lower_bound && q.front()->data <= upper_bound) {
                    cout << q.front()->data << endl;
                }
                q.pop();
            }
        }
        return;
    }

    void Search_3(Node* root,int lower_bound,int upper_bound){
        queue<Node*> q = Print_by_level(root); // queue con los primeros tres niveles
        vector<thread> th;
        for(int i = 0; i < 3;i++){  //se elimina los dos primeros niveles
            q.pop();
        }
        for(int i = 0; i < 4;i++){
            th.push_back(thread(print_inorder,q.front(),lower_bound,upper_bound)); //vector de thread
            q.pop();
        }
        for(int i = 0; i < 4; i++){ // se ejecutan los thread
            th[i].join();
        }
    }


    void print_inorder(Node* root,int lower_bound,int upper_bound){
        if(root != nullptr){
            print_inorder(root->m_left,lower_bound,upper_bound);
            if(root->data >= lower_bound && root->data <= upper_bound){
                //cout << root->data << endl;
                //cont++;
                return;
            }
            print_inorder(root->m_right,lower_bound,upper_bound);
        }
        cout << cont << endl;

    }
};

#endif //ABBTHREAD_ABB_H
