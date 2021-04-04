#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <typeinfo>
#define STATE_MAX 1000

using namespace std;

ifstream fin("nfa.in");
ofstream fout("nfa.out");


typedef pair<int, string> transition;
vector <transition> dfa[STATE_MAX];



struct traced_transition
{
    int this_state, parent_state;
    string input_str;
};

vector <int> vec, vect, track, final_states;
vector <traced_transition> q;
vector <string> inputs;


void addTransition(int first_state, int second_state, string input_str)
{
    dfa[first_state].push_back({second_state, input_str});
}

int main()
{
    int yes = 0, no_states, no_transitions, state1, state2, first_state, final_state, no_final_states, no_inputs;
    string input, inputt, str;
    fin>>no_states>>no_transitions;
    for (int i = 0; i < no_transitions; i++)
    {
        fin>>state1>>state2>>str;
        addTransition(state1,state2,str);
    }
    fin>>first_state;
    fin>>no_final_states;
    for(int i = 0; i < no_final_states; i++)
    {
        fin>>final_state;
        final_states.push_back(final_state);
    }
    fin>>no_inputs;
    for(int i = 0; i < no_inputs; i++)
    {
        fin>>inputt;
        inputs.push_back(inputt);
    }

    for (int k = 0; k < inputs.size(); k++)
    {
        yes = 0;
        input = inputs[k];
        while (!vec.empty())
            vec.pop_back();
        while (!vect.empty())
            vect.pop_back();
        while (!track.empty())
            track.pop_back();
        while (!q.empty())
            q.pop_back();
        vec.push_back(first_state);
        traced_transition ft;
        ft.this_state = 0;
        ft.parent_state = -1;
        ft.input_str = input;
        q.push_back(ft);

        while (input != "")
        {
            while (!vect.empty())
                vect.pop_back();
            for (int i = 0; i < vec.size(); i++)
                for (int j = 0; j < dfa[vec[i]].size(); j++)
                    if (dfa[vec[i]][j].second[0] == input[0])
                    {
                        vect.push_back(dfa[vec[i]][j].first);
                        traced_transition tt;
                        tt.this_state = dfa[vec[i]][j].first;
                        tt.parent_state = vec[i];
                        tt.input_str = input.substr(1);
                        q.push_back(tt);
                    }
            if (vect.empty())
            {
                fout<<"NU"<<endl;
                break;
            }
            while (!vec.empty())
                vec.pop_back();
            vec.resize(vect.size());
            for (int i = 0; i < vect.size(); i++)
                vec[i] = vect[i];
            input = input.substr(1);
        }

        for (int i = 0; i < vec.size(); i++)
        {
            for (int j = 0; j < final_states.size(); j++)
                if (vec[i] == final_states[j])
                {
                    fout<<"DA"<<endl;
                    yes = 1;
                    break;
                }
            break;
        }

        int idx_q;
        for (int i = q.size() - 1; i>=0; i--)
            if (q[i].this_state == final_state)
                idx_q = i;

        if (yes == 1)
        {
            while(q[idx_q].parent_state != -1)
            {
                track.push_back(q[idx_q].this_state);
                for (int i = 0; i < q.size(); i++)
                {
                    if (q[idx_q].parent_state == q[i].this_state && q[i].input_str.length() == q[idx_q].input_str.length() + 1)
                    {
                        idx_q = i;
                        break;
                    }
                }
            }
            track.push_back(first_state);

            fout<<"Traseu: ";
            for (int i = track.size()-1; i >= 0; i--)
                fout<<track[i]<<" ";
            fout<<endl;
        }
    }
    return 0;
}
