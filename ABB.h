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

queue<Node*> divide(ABB* tree, int num_thread){
    queue<Node*> q;
    q = tree->Print_by_level(tree->m_root,num_thread + 1);
    for(int j = 0; j < num_thread - 1;j++){
        q.pop();
    }
    return q;
}

void print_inorder(Node* root,int lower_bound,int upper_bound){

    if(root != nullptr){
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

    queue<Node*> Print_by_level(Node* root,int element){
        queue<Node*> q;
        queue<Node*> m_q;
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

};

#endif //ABBTHREAD_ABB_H