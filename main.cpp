// @Author: Francisco Gonzalez
// Fixed by Roberto Konow

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <queue>
#include <random>
#include <tuple>
#include "Time.h"
#include "ABB.h"

    using namespace std;

ABB* create_tree(ABB* a,int size_tree){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100000);
    for (int n = 0; n < size_tree; n++) { //Tamaño del arbol
        a->Insert(dis(gen));
    }
    return a;
}

tuple<int, int> search_range(int range,int size){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, size/2);
    int number = dis(gen);
    return make_tuple(number,number + size*range/100);

}

int main(int argc, char** argv) {
    int n = 1000000;
    int mediciones = 1;
    int threads = atoi(argv[1]);
    queue<Node*> q;
    for(int i = 1; i <= 5;i++){ // 5 mediciones correspondiente a 10% .... 50%
        for(int num_thread = 1; num_thread <= threads; num_thread = num_thread*2){ // cantidad de thread
//            cout << num_thread << endl;
            ABB *a = create_tree(new ABB(),n);
            Timer t;
            for(int num_med = 0; num_med < mediciones; num_med++){ //numero de mediciones
                vector<thread> th;
                divide(a,num_thread,q);
//                cout << "dividido ok" << endl;
//                cout << q.size() << endl;
                auto range = search_range(i*10,n);
                for(int j = 0; j < num_thread;j++){
                    Node* t = q.front();
                    th.push_back(thread(print_inorder,t,get<0>(range),get<1>(range)));
                    q.pop();
                }
                for(int j = 0; j < num_thread;j++){
                    th[j].join();
                }
            }
            t.Stop();
            cout << "t \t = " << num_thread << " \t " << i*10 << "% " << t.ElapsedTimeCPU()/mediciones << endl;
            delete a;
        }
    }
//    delete a;
/* --------------------------------------------------------------------------------------------------------*/

//    int num_thread = 8;
//    for(int size = 1000000; size <= 10000000; size += 1000000){
//        cout << size << endl;
//        ABB* b = create_tree(new ABB(),size);
//        for(int i = 1; i <= 5; i++){
//            for(int num_med = 0; num_med < 5; num_med++){
//                vector<thread> th;
//                queue<Node*> q;
//                q = divide(b,num_thread);
//                auto range = search_range(i*10,size);
//                for(int j = 0; j < num_thread;j++){
//                    th.push_back(thread(print_inorder,q.front(),get<0>(range),get<1>(range)));
//                    q.pop();
//                }
//                for(int j = 0; j < num_thread;j++){
//                    th[j].join();
//                }
//            }
//        }
////        delete b;
//    }
    //    ofstream output_file ("/home/francisco/Dropbox/C++/ABBThread/test.csv");
    //    output_file.close();
    return 0;
}