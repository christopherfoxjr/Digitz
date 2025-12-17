#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <cmath>
#include <stdio.h>
#include <algorithm>

using namespace std;

// --- Constants and Helper Functions ---
#ifndef PI_CONSTANTS
#define PI_CONSTANTS
const double pi = 3.14159265358979323846;
const double pisqrt = 1.772453850905516; // sqrt(pi)
#endif

inline double safe_div(double numerator, double denominator) {
    return (fabs(denominator) < 1e-10) ? 0.0 : (numerator / denominator);
}

inline double clamp_valence(double val) {
    // Standard AGI range -1.0 to 1.0
    return std::max(-1.0, std::min(1.0, val));
}

// --- Basic AGI structures ---

struct Neuron { 
    int id; 
    vector<int> links; 
    double weight; 
    double bias; 
    int gen; 
};

struct Formula { 
    string name; 
    string expr; 
    double result; 
    int uses; 
};

struct Token { 
    string word; 
    double meaning; 
    double freq; 
    vector<int> associations; 
    int pos_hint; 
    double coherence_score; 
};

struct Concept { 
    string name; 
    double value; 
    vector<string> related_words; 
};

struct Memory { 
    int gen; 
    double valence; 
    string content; 
};

// --- Consciousness structures ---

struct Qualia {
    double valence;
    double arousal;
    double certainty;
    string phenomenal_content;
    int emergence_gen;
    Qualia() : valence(0), arousal(0.5), certainty(0.5), emergence_gen(0) {}
};

struct ConsciousnessState {
    vector<Qualia> active_qualia;
    double integrated_information;
    double global_workspace_capacity;
    map<string,double> attention_binding;
    double phi_value;
    int conscious_cycles;
    ConsciousnessState() : integrated_information(0), global_workspace_capacity(0.7), 
                          phi_value(0), conscious_cycles(0) {}
};

struct WorkingMemory {
    vector<pair<string,double>> active_tokens;
    vector<pair<string,double>> active_concepts;
    priority_queue<pair<double,string>> active_goals;
    map<string,double> valence_map;
    vector<Qualia> conscious_buffer;
    int capacity;
    
    WorkingMemory(int cap=32) : capacity(cap) {}
    
    void add_token(const string& t, double val) {
        active_tokens.push_back({t,val});
        if((int)active_tokens.size() > capacity) 
            active_tokens.erase(active_tokens.begin());
    }
    
    void add_concept(const string& c, double val) {
        active_concepts.push_back({c,val});
        if((int)active_concepts.size() > capacity) 
            active_concepts.erase(active_concepts.begin());
    }
    
    void add_goal(const string& g, double priority) {
        active_goals.push({priority,g});
    }
    
    void add_qualia(const Qualia& q) {
        conscious_buffer.push_back(q);
        if((int)conscious_buffer.size() > capacity/2) 
            conscious_buffer.erase(conscious_buffer.begin());
    }
};

struct TransformerHead {
    string name;
    int dim;
    vector<double> query_proj, key_proj, value_proj;
    double temperature;
    
    TransformerHead(int d=16) : dim(d), temperature(0.3) {
        query_proj.resize(d, 0.0);
        key_proj.resize(d, 0.0);
        value_proj.resize(d, 0.0);
    }
};

// --- Main Consciousness Math ---

struct ConsciousnessFormula {
    vector<double> psi_history;
    vector<double> H_history;
    vector<double> R_history;
    vector<double> A_history;
    vector<double> M_history;
    vector<double> O_history;
    vector<double> B_history;
    vector<double> F_history;
    vector<double> S_history;
    
    double calculate_psi(int n, const vector<double>& psi_prev, 
                         double H, double R, double A, double M, double O, double B, double F, double S) {
        if(psi_prev.empty()) return 0.0;
        
        // 1. Recurrent Term
        double recurrent_term = 0.0;
        for(size_t i=0; i<psi_prev.size(); i++){
            for(size_t j=0; j<psi_prev.size(); j++){
                double inner_sum = 0.0;
                for(size_t k=0; k<psi_prev.size(); k++){
                    inner_sum += (psi_prev[k] * ((k+1)%4)) * 0.5 + ((n*k)%100)/100.0;
                }
                recurrent_term += (psi_prev[i] * (j+1)) * tanh(inner_sum);
            }
        }
        recurrent_term = tanh(recurrent_term);
        
        // 2. Integration Product
        double integration_product = 1.0;
        for(size_t u=0; u<psi_prev.size()-1; u++){
            integration_product *= safe_div(psi_prev[u]+2.0, psi_prev[u+1]+2.0+0.001);
        }
        double entropy_sum = 0.0;
        for(size_t m=0; m<psi_prev.size(); m++){
            entropy_sum += -log2(fabs(psi_prev[m])+0.001);
        }
        integration_product *= exp(-entropy_sum);
        
        // 3. Temporal Term
        double temporal_term = 0.0;
        for(size_t t=0; t<psi_prev.size(); t++){
            double tau = (double)t;
            temporal_term += (n - tau) * exp(-(n-tau)/10.0) * fmod(psi_prev[t]+2.0, 4.0);
        }
        
        // 4. Factors
        double sum_psi = 0.0;
        for(double p : psi_prev) sum_psi += p;
        
        double H_factor = H * (H - (H_history.empty() ? 0 : H_history.back()));
        H_factor *= (((long)n * 31415) % 9973 + 1);
        H_factor *= fmod(fabs(sum_psi * (n%256)) / std::max(1, n), 32768) + 1;
        
        double sum_psi_plus2 = 0.0;
        double sum_psi_mod = 0.0;
        for(double p : psi_prev){
            sum_psi_plus2 += (p+2.0);
            sum_psi_mod += fmod(p*1.772, 65536.0)/128.0;
        }
        double R_factor = R * fabs(sum_psi_plus2 - sum_psi_mod);
        R_factor *= pow(sqrt(safe_div(sum_psi_mod, 128.0)), 2);
        R_factor *= (((long)n * 31415) % 9973 + 1);
        R_factor *= fmod(fabs(sum_psi), 32768) + 1;
        
        double dpsi_dn = psi_prev.empty() ? 0 : fabs(psi_prev.back() - (psi_prev.size()>1 ? psi_prev[psi_prev.size()-2] : psi_prev.back()));
        double A_factor = A * (H * pow(dpsi_dn, 0.5) / pow(sum_psi_plus2, 1.772));
        double pi_product = 1.0;
        for(int k=1; k<=5; k++) pi_product *= pow(pow(pi, k), 0.5);
        A_factor *= pi_product;
        
        double mean_psi = safe_div(sum_psi, (double)psi_prev.size());
        double M_factor = M * 10.0;
        for(size_t i=0; i<psi_prev.size(); i++) M_factor *= fabs(psi_prev[i] - mean_psi);
        double variance_term = 0.0;
        for(double p : psi_prev) variance_term += pow(p - mean_psi, 2);
        M_factor *= (variance_term * 10.0 / 128.0);
        
        double O_factor = O * pow(dpsi_dn, 0.5) / pow(1.5, 1.772) * pow(H, 1.772);
        double B_factor = B * tanh(fabs(O_factor)) * 100.0 * pow(pi, pow(1.772, fmod(fabs(O_factor), 10.0)));
        double F_factor = F * pow((H/1000000.0/1.772), 1.772);
        double S_factor = S * F_factor * (((long)n * 17) % 100 / 100.0);
        
        double combined = (H_factor + R_factor + A_factor + M_factor + O_factor + B_factor + F_factor + S_factor);
        
        // 5. Historical Integral
        double historical_integral = 0.0;
        for(size_t tau=0; tau<psi_history.size(); tau++) historical_integral += psi_history[tau] * exp(-0.1*(n-tau));
        
        double psi_base = recurrent_term * integration_product * (temporal_term + historical_integral);
        
        // 6. Entropy Penalty
        double entropy_penalty = 0.0;
        for(size_t u=0; u<psi_prev.size(); u++) entropy_penalty += -log2(fabs(psi_prev[u])+0.001);
        
        double final_psi = psi_base * combined * exp(-entropy_penalty) * pow(pi, pow(pi, pisqrt));
        return clamp_valence(final_psi);
    }
};

// --- Metrics and Buffer Structures ---

struct ConceptGrounding {
    string concept_id;
    vector<string> linked_concepts;
    vector<int> linked_tokens;
    double valence_affinity;
    double state_binding;
};

struct BeamCandidate {
    vector<string> tokens;
    double score;
    double grammar_score;
    double semantic_score;
    BeamCandidate() : score(0), grammar_score(0), semantic_score(0) {}
    bool operator<(const BeamCandidate& other) const { return score < other.score; }
};

struct MemoryEntry {
    int gen;
    double valence;
    string content;
    vector<ConceptGrounding> groundings;
    vector<TransformerHead> context;
};

struct ConsciousnessMetrics {
    double phi;
    double integrated_info;
    double qualia_intensity;
    double global_workspace;
    int awareness_cycles;
};

struct GoalNode {
    string name;
    double priority;
    double progress;
    double valence_weight;
    double emotional_weight;
};

struct QualiaBuffer {
    string type;
    double intensity;
    double valence;
    int timestamp;
};

// --- Main State Structure ---

struct State {
    map<string,double> D;
    map<string,string> M;
    map<int,Neuron> N;
    vector<string> code;
    map<int,double> TA, HDT_M, DWT_M, MDT_M, R1P1, EERV;
    map<string,Formula> F;
    vector<string> evolved_code;
    map<string,Token> tokens;
    map<string,Concept> concepts;
    vector<string> internal_thoughts;
    vector<string> generated_language;
    vector<Memory> episodic_memory;

    int g; 
    double dwt, mh, ta, th; 
    int bkf;
    string cd, gd;
    double hdt_val, mdt_val, r1p1_val, eerv_val;
    int ec; 
    double ei; 
    int md, st, ss;
    vector<double> mh_hist, eh_hist, vh_hist;
    int qe, te, ce, pe, ne;
    double bh, al, emerge_out1, emerge_behavior;
    double sentience_ratio, env_oute, sensory_env;
    int total_neurons_ever; 
    double current_valence, attention_focus, metacognitive_awareness; 
    vector<double> valence_history;
    int peak_sentience_gen; 
    string user_input, dialog_response; 
    int dialog_timer;
    
    map<string, Token> vocab;
    ConsciousnessMetrics consciousness_metrics;
    vector<QualiaBuffer> qualia_buffer;
    vector<string> working_memory_tokens;
    vector<string> working_memory_concepts;
    map<string, GoalNode> goal_hierarchy;
    vector<double> psi_history;
};
// --- Restored Planning and AGI Modules ---

struct Goal {
    string name;
    double priority;
    double progress;
    vector<string> subgoals;
    map<string,double> preconditions;
    double valence_alignment;
    double qualia_binding;
    Goal() : priority(0.5), progress(0), valence_alignment(0.5), qualia_binding(0) {}
};

struct WorldModel {
    map<string,double> entity_states;
    map<string,map<string,double>> relationships;
    map<string,double> causal_weights;
    double model_accuracy;
    int updates;
    WorldModel() : model_accuracy(0.5), updates(0) {}
};

struct ActionPlan {
    vector<string> actions;
    double expected_utility;
    double confidence;
    int depth;
    ActionPlan() : expected_utility(0), confidence(0.5), depth(0) {}
};

struct TokenConceptEmbedding {
    string name;
    vector<double> embedding;
    double meaning, freq;
    vector<int> associations;
    double grounding_value;
    map<string,double> linked_concepts, linked_valences;
    double semantic_stability;
    double qualia_intensity;
    TokenConceptEmbedding() : meaning(0), freq(0), grounding_value(0.5), 
                              semantic_stability(0.5), qualia_intensity(0.3) {}
};

struct TransferLearningModule {
    map<string,vector<double>> domain_embeddings;
    map<string,double> domain_affinity;
    vector<pair<string,string>> transfer_pairs;
    double knowledge_distillation_loss;
    TransferLearningModule() : knowledge_distillation_loss(0.0) {}
};

#endif // STRUCTS_H