//
// Created by francisco on 27-09-15.
// @Author: Francisco Gonzalez
// Fixed by Roberto Konow

//

#ifndef ABBTHREAD_ABB_H
#define ABBTHREAD_ABB_H

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include "Node.h"
#include "Time.h"

using namespace std;


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

    void Print_by_level(Node* root,int element, queue<Node*> &m_q){
        queue<Node*> q;
        q.push(root);
        int cont = 0;
        while(!q.empty() && cont != element){
            if(q.front()->m_left != nullptr){
                q.push(q.front()->m_left);
            }
            if(q.front()->m_right != nullptr){
                q.push(q.front()->m_right);
            }
            m_q.push(q.front());
            cont++;
            q.pop();
//            cout << "entre?? wtf2" << endl;
        }
//        cout << "tamano m_pq = " << m_q.size() << endl;
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

};

void divide(ABB* tree, int num_thread,queue<Node*>& q){
    queue<Node*> q_empty;
    q.swap(q_empty);
//    cout << "divido aca" << endl;
//    cout << "num_thread = " << num_thread << endl;
    int nodos = (1<<num_thread)-1;
//    cout << "nodos = " << nodos << endl;
    tree->Print_by_level(tree->m_root,nodos, q);
    for(int j = 0; j < num_thread - 1;j++){
        q.pop();
    }
//    cout << "taman = " << q.size() << endl;
//    cout << "termino aca" << endl;
}

void print_inorder(Node* root,int lower_bound,int upper_bound){
//    cout << "entre?? wtf" << endl;
    if(root != nullptr){
//        cout << "root es" << root->data << "...." <<  endl;
        print_inorder(root->m_left,lower_bound,upper_bound);
        if(root->data >= lower_bound && root->data <= upper_bound){
            //cout << root->data << endl;
        } else {
            return;
        }
        print_inorder(root->m_right,lower_bound,upper_bound);
    }
//    cout << cont << endl;

}

double print_inorder_2(Node* root,int lower_bound,int upper_bound,double &elapsed_time){
    if(root != nullptr){
        Timer t;
        print_inorder_2(root->m_left,lower_bound,upper_bound,elapsed_time);
        if(root->data >= lower_bound && root->data <= upper_bound){
            //cout << root->data << endl;
        } else {
            t.Stop();
            return elapsed_time += t.ElapsedTime();
        }
        print_inorder_2(root->m_right,lower_bound,upper_bound,elapsed_time);
    }
//    cout << cont << endl;

}
#endif //ABBTHREAD_ABB_H