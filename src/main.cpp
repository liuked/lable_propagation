#include <iostream>
#include <queue>

#include "AdjacencyList.h"
#include "CommunityDetection.h"
#include <cstring>


//#include "MinHeap.h"
int main() {


    AdjacencyList g;
    bool debug;
    int  start;

    //string filename = "../graphs/com-youtube.ungraph.graph";
    string graph_fn = "../sample/sample.graph";
    string log_fn = "../sample/sample_comm.log";
    string size_hist_fn = "../sample/comm_size_hist.dat";
    string detec_comm_fn = "../sample/nr_detec.dat";

    // ------------------------------------------------------


    start = (int)time(nullptr);

    srand(time(0));


    debug = false;

    ifstream file(graph_fn);
    if (!file.good()) {
        cout << time(nullptr)-start << "s: " <<  "[ERROR] - main(): No such file ... " << endl;
        exit(0);
    }


    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): loading adjacency list..." << endl;
    g.loadFromFile(graph_fn, debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): printing..." << endl;
    g.print(debug);
    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): finding dominant lable..." << endl;

    DynamicVector<unsigned int> n_detec_comm;
    unsigned int nr;

    for (int i = 0; i < 1000; i++) {
        //sprintf(log_fn, "../sample/sample_comm%d.log", i);
        //cout << log_fn << endl;
        nr = CommunityDetection::lable_propagation(g,log_fn, size_hist_fn, true, false);
        n_detec_comm[nr]++;
    }

    cout << time(nullptr)-start << "s: " << "[EXECUTION] - main(): done!..." << endl;

    fstream out;
    out.open(detec_comm_fn, ios::out);
    n_detec_comm.f_print_nz(out);
    out.close();

    return 0;
}