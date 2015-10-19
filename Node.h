//
// Created by francisco on 27-09-15.
// @Author: Francisco Gonzalez
// Fixed by Roberto Konow

//

#ifndef ABBTHREAD_NODE_H
#define ABBTHREAD_NODE_H

#include <iostream>

class Node{

public:
    int data;
    Node* m_right;
    Node* m_left;
    Node(int data) : data(data),m_left(nullptr),m_right(nullptr){}
};

#endif //ABBTHREAD_NODE_H
