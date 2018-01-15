//
// Created by Luca De Mori on 13/01/2018.
//

#include "CommunityDetection.h"


unsigned int CommunityDetection::lable_propagation(AdjacencyList &graph, string log_fn, string size_hist_fn, bool append, bool debug) {

    bool changed;
    unsigned int *order = new unsigned int[graph.getNumNodes() + 1]();
    unsigned int *label = new unsigned int[graph.getNumNodes() + 1]();
    unsigned int n;
    unsigned int l;
    unsigned int iterations;
    fstream logfile;
    fstream histfile;

    Node nbr;
    map<unsigned int, unsigned int> lbl_counter;

    map<unsigned int, set<unsigned int> > communities;

    unsigned int max_occurrencies;
    unsigned int domin_label;


    unsigned int temp;
    unsigned int j;


    DynamicVector<unsigned int> size_hist;

    // set default lable = ID
    for (n = 1; n <= graph.getNumNodes(); n++) {
        label[n] = graph.nodes[n].ID;
    }

    // scrumble the array
    for (n = graph.getNumNodes(); n > 0; n--) {

        j = rand()%n+1;
        temp = (order[n] != 0) ? order[n] : n;
        order[n] = (order[j] != 0) ? order[j] : j;
        order[j] = temp;
    }

    if (debug) {
        for (n = 1; n <= graph.getNumNodes(); n++) {
            cout << order[n] << " ";
        }
        cout << endl;
    }



    changed = true;
    iterations = 0;
    while (changed){

        iterations++;
        if (debug) cout << "[DEBUG] CommunityDetection::lable_propagation(): ***Iteration #" << iterations << endl;

        // cycle on every nodes
        for (unsigned int i = 1; i<=graph.getNumNodes(); i++) {

            /*// skip if the node is done
            if (completed[n]) continue;*/

            n = order[i];

            // find max occurring lable in the neighborhood
            max_occurrencies = 0;
            domin_label = 0;
            lbl_counter.clear();
            for (unsigned int nb_idx = 0; nb_idx < graph.nodes[n].degree; nb_idx++){


                nbr = *graph.getNeighbour(n, nb_idx);
                // read the lable
                l = label[nbr.ID];
                // increment the counter in the corrisponding position
                ++ lbl_counter[l];
                if (lbl_counter[l] > max_occurrencies) {
                    max_occurrencies = lbl_counter[l];
                    domin_label = l;
                }

                if (debug) cout << "[DEBUG] CommunityDetection::label_propagation(): n=" << n << " nb=" << nbr.ID
                                << " lbl=" << label[nbr.ID] << " [+1] -> #=" << lbl_counter[label[nbr.ID]] << endl;


            }

            if (debug) cout << "[DEBUG] CommunityDetection::label_propagation(): >>> n=" << n << " dom_lbl="
                            << domin_label << "(" << max_occurrencies << ")" ;

            if (label[n]!=domin_label){
                if (debug) cout << " >>> lbl was: " << label[n] << " -> setting to: " << domin_label << endl;

                communities[label[n]].erase(n);
                // check if is empty so delete the community
                if (communities[label[n]].size()==0){
                    communities.erase(label[n]);
                }
                label[n] = domin_label;
                communities[domin_label].insert(n);

                changed = true;

            } else {
                if (debug) cout << " >>> label unchanged " << label[n] << endl;
                communities[label[n]].insert(n);
                changed = false;
            }

        }


    }


    /*
    if (append)
        logfile.open(log_fn, ios::app);
    else
        logfile.open(log_fn, ios::out);


    map<unsigned int, set<unsigned int> >::iterator c_it;
    set<unsigned int>::iterator n_it;


    if (debug) cout << "[DEBUG] CommunityDetection::lable_propagation(): DETECTED COMMUNITIES: " << communities.size() << endl;
    if (append) logfile << "# ----------------------------------------------------------------" << endl;
    logfile << "# nr communities: " << communities.size() << endl;
    logfile << "# lbl size : n1 n2 n3 ..." << endl;
    for (c_it = communities.begin(); c_it!=communities.end(); ++c_it){

        size_hist[c_it->second.size()]++;

        if (debug) cout << "lbl: " << c_it->first << "(" << c_it->second.size() << ") N={";
        logfile << c_it->first << " " << c_it->second.size() << " : ";
        for (n_it = c_it->second.begin(); n_it!=c_it->second.end(); ++n_it){
            if (debug) cout << *n_it << " ";
            logfile << *n_it << " ";
        }

        if (debug) cout << "}" << endl;
        logfile << endl;
    }

    histfile.open(size_hist_fn, ios::out);
    histfile.open(size_hist_fn, ios::app);

    size_hist.f_print_nz(histfile);

    logfile.close();

    delete[] order;
    delete[] label;

    */

    return  communities.size();

    }


