// @Author: Francisco Gonzalez
// Fixed by Roberto Konow

#include <iostream>
#include <fstream>
#include <sstream>
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
    uniform_int_distribution<> dis(0, 10000000);
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
    int n = 10000000;
    int mediciones = 10;
    int threads = atoi(argv[1]);
    ofstream myfile ("/home/francisco/Gitlab/ABBThread/Meditions.csv");
    queue<Node*> q;
//    ABB *a = create_tree(new ABB(),n);
    for(int i = 1; i <= 5;i++){ // 5 mediciones correspondiente a 10% .... 50%
        int cont = 0;
        ABB *a = create_tree(new ABB(),n);
        auto range = search_range(i*10,n);
        for(int num_thread = 1; num_thread <= threads; num_thread = num_thread*2){ // cantidad de thread
            Timer t;
            t.Restart();
            cont++;
            for(int num_med = 0; num_med < mediciones; num_med++){ //numero de mediciones
                vector<thread> th;
//                vector<int> v;
                divide(a,cont,q,get<0>(range),get<1>(range));
                for(int j = 0; j < num_thread;j++){
                    Node* t = q.front();
                    th.push_back(thread(Search,q.front(),get<0>(range),get<1>(range)));
                    q.pop();
                }
                for(int j = 0; j < num_thread;j++){
                    th[j].join();
                }
            }
            t.Stop();
            cout << "t \t = " << num_thread << " \t " << i*10 << "% " << t.ElapsedTime()/mediciones << endl;
            ostringstream thread;
            thread <<num_thread;
            ostringstream time;
            time <<t.ElapsedTime()/mediciones;
            myfile << thread.str() << "," << time.str() << endl;
        }
        delete a;
    }
//    delete a;
/* --------------------------------------------------------------------------------------------------------*/


    //    output_file.close();
    return 0;
}
