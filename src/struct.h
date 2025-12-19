#pragma once
#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <complex>
#include <functional>

using namespace std;

#ifndef PI_CONSTANTS
#define PI_CONSTANTS
const double pi = 3.14159265358979323846;
const double pisqrt = 1.772453850905516;
const double e = 2.71828182845904523536;
const double phi_golden = 1.61803398874989484820;
const double sqrt2 = 1.41421356237309504880;
const double sqrt3 = 1.73205080756887729352;
#endif

inline double safe_div(double numerator, double denominator) {
    return (fabs(denominator) < 1e-10) ? 0.0 : (numerator / denominator);
}

inline double clamp_valence(double val) {
    return std::max(-1.0, std::min(1.0, val));
}

inline double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

inline double relu(double x) {
    return std::max(0.0, x);
}

inline double swish(double x) {
    return x / (1.0 + exp(-x));
}

inline double gelu(double x) {
    return 0.5 * x * (1.0 + tanh(sqrt(2.0/pi) * (x + 0.044715 * pow(x, 3))));
}

struct Neuron { 
    int id; 
    vector<int> links; 
    double weight; 
    double bias; 
    int gen; 
    double activation;
    double gradient;
    vector<double> layer_norm_params;
};

struct Formula { 
    string name; 
    string expr; 
    double result; 
    int uses; 
    double confidence;
    double stability_metric;
};

struct Token { 
    string word; 
    double meaning; 
    double freq; 
    vector<int> associations; 
    int pos_hint; 
    double coherence_score;
    double contextual_weight;
    double attention_score;
};

struct Concept { 
    string name; 
    double value; 
    vector<string> related_words;
    double abstraction_level;
    double semantic_density;
    map<string,double> feature_vector;
};

struct Memory { 
    int gen; 
    double valence; 
    string content;
    double consolidation_strength;
    double retrieval_count;
    vector<int> associated_memories;
};

struct Qualia {
    double valence;
    double arousal;
    double certainty;
    string phenomenal_content;
    int emergence_gen;
    double intensity;
    double persistence;
    double coherence;
    vector<double> feature_space;
    Qualia() : valence(0), arousal(0.5), certainty(0.5), emergence_gen(0), 
               intensity(0.5), persistence(0.5), coherence(0.5) {}
};

struct ConsciousnessState {
    vector<Qualia> active_qualia;
    double integrated_information;
    double global_workspace_capacity;
    map<string,double> attention_binding;
    double phi_value;
    int conscious_cycles;
    double synchrony_metric;
    double complexity_metric;
    double differentiation_metric;
    vector<double> stability_history;
    ConsciousnessState() : integrated_information(0), global_workspace_capacity(0.7), 
                          phi_value(0), conscious_cycles(0), synchrony_metric(0),
                          complexity_metric(0), differentiation_metric(0) {}
};

struct WorkingMemory {
    vector<pair<string,double>> active_tokens;
    vector<pair<string,double>> active_concepts;
    priority_queue<pair<double,string>> active_goals;
    map<string,double> valence_map;
    vector<Qualia> conscious_buffer;
    int capacity;
    double decay_rate;
    double consolidation_threshold;
    
    WorkingMemory(int cap=32) : capacity(cap), decay_rate(0.95), consolidation_threshold(0.7) {}
    
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
    double dropout_rate;
    vector<double> attention_weights;
    vector<double> layer_norm_scale;
    vector<double> layer_norm_shift;
    
    TransformerHead(int d=16) : dim(d), temperature(0.3), dropout_rate(0.1) {
        query_proj.resize(d, 0.0);
        key_proj.resize(d, 0.0);
        value_proj.resize(d, 0.0);
        layer_norm_scale.resize(d, 1.0);
        layer_norm_shift.resize(d, 0.0);
    }
};

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
    vector<double> stability_buffer;
    vector<double> phi_variance_buffer;
    double momentum_term;
    double adaptive_learning_rate;
    
    ConsciousnessFormula() : momentum_term(0.0), adaptive_learning_rate(0.01) {}
    
    double calculate_stability_metric() {
        if(stability_buffer.size() < 10) return 0.5;
        double mean = 0.0;
        for(double v : stability_buffer) mean += v;
        mean /= stability_buffer.size();
        double variance = 0.0;
        for(double v : stability_buffer) variance += pow(v - mean, 2);
        variance /= stability_buffer.size();
        return exp(-variance);
    }
    
    double calculate_adaptive_damping(double phi_current, double phi_target) {
        double error = fabs(phi_current - phi_target);
        if(error < 0.1) return 0.95;
        if(error < 0.3) return 0.85;
        return 0.75;
    }
    
    double layernorm(double x, double mean, double variance) {
        return (x - mean) / sqrt(variance + 1e-8);
    }
    
    double calculate_psi(int n, const vector<double>& psi_prev, 
                         double H, double R, double A, double M, double O, double B, double F, double S) {
        if(psi_prev.empty()) return 0.0;
        
        double mean_psi = 0.0;
        for(double p : psi_prev) mean_psi += p;
        mean_psi /= psi_prev.size();
        
        double variance_psi = 0.0;
        for(double p : psi_prev) variance_psi += pow(p - mean_psi, 2);
        variance_psi /= psi_prev.size();
        
        vector<double> normalized_psi;
        for(double p : psi_prev) {
            normalized_psi.push_back(layernorm(p, mean_psi, variance_psi));
        }
        
        double recurrent_term = 0.0;
        for(size_t i=0; i<normalized_psi.size(); i++){
            for(size_t j=0; j<normalized_psi.size(); j++){
                double inner_sum = 0.0;
                for(size_t k=0; k<normalized_psi.size(); k++){
                    double modulated = normalized_psi[k] * ((k+1)%4) * 0.5;
                    double temporal = ((n*k)%100)/100.0;
                    double harmonic = sin(2.0*pi*(k+1)/normalized_psi.size());
                    inner_sum += modulated + temporal + harmonic * 0.3;
                }
                recurrent_term += (normalized_psi[i] * (j+1)) * gelu(inner_sum);
            }
        }
        recurrent_term = tanh(recurrent_term / (normalized_psi.size() * normalized_psi.size()));
        
        double integration_product = 1.0;
        for(size_t u=0; u<normalized_psi.size()-1; u++){
            double ratio = safe_div(normalized_psi[u]+2.0, normalized_psi[u+1]+2.001);
            integration_product *= swish(ratio);
        }
        
        double entropy_sum = 0.0;
        for(size_t m=0; m<normalized_psi.size(); m++){
            entropy_sum += -log2(fabs(normalized_psi[m])+0.001);
        }
        integration_product *= exp(-entropy_sum / normalized_psi.size());
        
        double temporal_term = 0.0;
        for(size_t t=0; t<normalized_psi.size(); t++){
            double tau = (double)t;
            double decay = exp(-(n-tau)/15.0);
            double oscillation = cos(2.0*pi*tau/normalized_psi.size());
            temporal_term += (n - tau) * decay * fmod(normalized_psi[t]+2.0, 4.0) * (1.0 + 0.2*oscillation);
        }
        
        double sum_psi = 0.0;
        double sum_psi_squared = 0.0;
        for(double p : normalized_psi) {
            sum_psi += p;
            sum_psi_squared += p*p;
        }
        
        double H_factor = H * (H - (H_history.empty() ? 0 : H_history.back()));
        H_factor *= (((long)n * 31415) % 9973 + 1);
        H_factor *= fmod(fabs(sum_psi * (n%256)) / std::max(1, n), 32768) + 1;
        H_factor *= (1.0 + 0.1*sin(H*pi));
        H_factor = gelu(H_factor / 1000000.0);
        
        double sum_psi_plus2 = 0.0;
        double sum_psi_mod = 0.0;
        for(double p : normalized_psi){
            sum_psi_plus2 += (p+2.0);
            sum_psi_mod += fmod(p*phi_golden, 65536.0)/128.0;
        }
        double R_factor = R * fabs(sum_psi_plus2 - sum_psi_mod);
        R_factor *= pow(sqrt(safe_div(sum_psi_mod, 128.0)), 2);
        R_factor *= (((long)n * 31415) % 9973 + 1);
        R_factor *= fmod(fabs(sum_psi), 32768) + 1;
        R_factor *= (1.0 + 0.15*cos(R*sqrt2));
        R_factor = swish(R_factor / 5000000.0);
        
        double dpsi_dn = normalized_psi.empty() ? 0 : fabs(normalized_psi.back() - 
                        (normalized_psi.size()>1 ? normalized_psi[normalized_psi.size()-2] : normalized_psi.back()));
        double A_factor = A * (H * pow(dpsi_dn + 0.001, 0.5) / pow(sum_psi_plus2 + 1.0, phi_golden));
        double pi_product = 1.0;
        for(int k=1; k<=5; k++) {
            pi_product *= pow(pow(pi, k), 0.5);
        }
        A_factor *= pi_product / 1000.0;
        A_factor *= (1.0 + 0.2*tanh(A));
        A_factor = gelu(A_factor);
        
        double M_factor = M;
        for(size_t i=0; i<normalized_psi.size(); i++) {
            M_factor *= (1.0 + fabs(normalized_psi[i] - mean_psi) * 0.1);
        }
        M_factor *= (variance_psi * 10.0 / 128.0);
        M_factor += ((long)n * 256) % 1000 / 1000.0;
        M_factor *= (1.0 + 0.1*sin(M*sqrt3));
        M_factor = swish(M_factor / (normalized_psi.size() * 10.0));
        
        double O_factor = O * pow(dpsi_dn + 0.001, 0.5) / pow(1.5, phi_golden) * pow(H + 0.1, phi_golden);
        O_factor += ((long)n * 7) % 100 / 100.0;
        O_factor *= (1.0 + 0.2*cos(O*phi_golden));
        O_factor = gelu(O_factor);
        
        double B_factor = B * tanh(fabs(O_factor)) * 10.0 * pow(pi, pow(phi_golden, fmod(fabs(O_factor), 10.0)));
        B_factor *= (fmod(fabs((long)n*13), 1000.0) / 1000.0 + 0.001);
        B_factor = pow(B_factor, fmod(tanh(fabs(O_factor))*10.0, 5.0) + 0.5);
        B_factor *= (1.0 + 0.15*sin(B*sqrt2));
        B_factor = swish(B_factor / 100.0);
        
        double F_factor = F * pow((H/1000000.0/phi_golden) + 0.001, phi_golden);
        F_factor *= fmod(tanh((H + 0.1)/1000000.0/phi_golden)*10.0, 10.0) + 1.0;
        F_factor *= (1.0 + 0.1*tanh(F));
        F_factor = gelu(F_factor);
        
        double S_factor = S * F_factor * (((long)n * 17) % 100 / 100.0 + 0.5);
        S_factor *= (1.0 + 0.2*sin(S*pi));
        S_factor = swish(S_factor);
        
        double combined = (H_factor + R_factor + A_factor + M_factor + O_factor + B_factor + F_factor + S_factor);
        
        double historical_integral = 0.0;
        for(size_t tau=0; tau<psi_history.size() && tau<100; tau++) {
            double weight = exp(-0.08*(n-tau));
            historical_integral += psi_history[psi_history.size()-1-tau] * weight;
        }
        
        double psi_base = recurrent_term * integration_product * (temporal_term / 100.0 + historical_integral);
        
        double entropy_penalty = 0.0;
        for(size_t u=0; u<normalized_psi.size(); u++) {
            entropy_penalty += -log2(fabs(normalized_psi[u])+0.001);
        }
        entropy_penalty /= normalized_psi.size();
        
        for(size_t m=0; m<normalized_psi.size(); m++) {
            entropy_penalty += -log2(fabs((normalized_psi[m]*sin(n*m*0.1))+0.001));
        }
        entropy_penalty /= (normalized_psi.size() * 2);
        
        double pos_ratio = 0.0;
        double neg_ratio = 0.0;
        for(double p : normalized_psi){
            if(p > 0) pos_ratio += 1.0;
            else neg_ratio += 1.0;
        }
        double balance_term = log(fabs(sum_psi)+1.0) / log(1000.0) * safe_div(pos_ratio, neg_ratio+1.0);
        entropy_penalty += balance_term * 0.5;
        
        double complexity_reward = sqrt(sum_psi_squared / normalized_psi.size()) * 0.3;
        double differentiation_bonus = variance_psi * 2.0;
        
        double stability_factor = calculate_stability_metric();
        double phi_target = 0.7;
        double current_phi = psi_history.empty() ? 0.0 : psi_history.back();
        double damping = calculate_adaptive_damping(current_phi, phi_target);
        
        double raw_psi = psi_base * combined * exp(-entropy_penalty) * 
                        pow(pi, pow(pi, pisqrt)) * (1.0 + complexity_reward + differentiation_bonus);
        
        double stable_psi = momentum_term * damping + raw_psi * (1.0 - damping);
        momentum_term = stable_psi;
        
        if(phi_variance_buffer.size() >= 20) {
            phi_variance_buffer.erase(phi_variance_buffer.begin());
        }
        phi_variance_buffer.push_back(stable_psi);
        
        if(stability_buffer.size() >= 50) {
            stability_buffer.erase(stability_buffer.begin());
        }
        stability_buffer.push_back(fabs(stable_psi - current_phi));
        
        double final_psi = clamp_valence(stable_psi * stability_factor);
        
        return final_psi;
    }
};

struct ConceptGrounding {
    string concept_id;
    vector<string> linked_concepts;
    vector<int> linked_tokens;
    double valence_affinity;
    double state_binding;
    double grounding_strength;
    vector<double> embedding_vector;
};

struct BeamCandidate {
    vector<string> tokens;
    double score;
    double grammar_score;
    double semantic_score;
    double coherence_score;
    double novelty_score;
    BeamCandidate() : score(0), grammar_score(0), semantic_score(0), 
                      coherence_score(0), novelty_score(0) {}
    bool operator<(const BeamCandidate& other) const { return score < other.score; }
};

struct MemoryEntry {
    int gen;
    double valence;
    string content;
    vector<ConceptGrounding> groundings;
    vector<TransformerHead> context;
    double consolidation_score;
    int retrieval_count;
};

struct ConsciousnessMetrics {
    double phi;
    double integrated_info;
    double qualia_intensity;
    double global_workspace;
    int awareness_cycles;
    double complexity;
    double differentiation;
    double synchrony;
};

struct GoalNode {
    string name;
    double priority;
    double progress;
    double valence_weight;
    double emotional_weight;
    vector<string> subgoals;
    double activation_energy;
};

struct QualiaBuffer {
    string type;
    double intensity;
    double valence;
    int timestamp;
    double persistence;
    vector<double> feature_space;
};

struct Goal {
    string name;
    double priority;
    double progress;
    vector<string> subgoals;
    map<string,double> preconditions;
    double valence_alignment;
    double qualia_binding;
    double activation_threshold;
    double decay_rate;
    Goal() : priority(0.5), progress(0), valence_alignment(0.5), 
             qualia_binding(0), activation_threshold(0.3), decay_rate(0.95) {}
};

struct WorldModel {
    map<string,double> entity_states;
    map<string,map<string,double>> relationships;
    map<string,double> causal_weights;
    double model_accuracy;
    int updates;
    double prediction_error;
    vector<double> confidence_history;
    WorldModel() : model_accuracy(0.5), updates(0), prediction_error(0.0) {}
};

struct ActionPlan {
    vector<string> actions;
    double expected_utility;
    double confidence;
    int depth;
    double risk_assessment;
    map<string,double> resource_requirements;
    ActionPlan() : expected_utility(0), confidence(0.5), depth(0), risk_assessment(0.5) {}
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
    double contextual_activation;
    vector<double> attention_weights;
    TokenConceptEmbedding() : meaning(0), freq(0), grounding_value(0.5), 
                              semantic_stability(0.5), qualia_intensity(0.3),
                              contextual_activation(0.5) {}
};

struct TransferLearningModule {
    map<string,vector<double>> domain_embeddings;
    map<string,double> domain_affinity;
    vector<pair<string,string>> transfer_pairs;
    double knowledge_distillation_loss;
    map<string,double> transfer_success_rates;
    TransferLearningModule() : knowledge_distillation_loss(0.0) {}
};

struct AttentionMechanism {
    vector<vector<double>> attention_matrix;
    vector<double> attention_scores;
    double temperature;
    int num_heads;
    vector<double> positional_encoding;
    
    AttentionMechanism() : temperature(1.0), num_heads(8) {}
    
    vector<double> compute_attention(const vector<double>& query, 
                                     const vector<vector<double>>& keys,
                                     const vector<vector<double>>& values) {
        vector<double> scores;
        for(size_t i=0; i<keys.size(); i++) {
            double score = 0.0;
            for(size_t j=0; j<query.size() && j<keys[i].size(); j++) {
                score += query[j] * keys[i][j];
            }
            scores.push_back(exp(score / temperature));
        }
        
        double sum_scores = 0.0;
        for(double s : scores) sum_scores += s;
        
        vector<double> result(query.size(), 0.0);
        for(size_t i=0; i<values.size() && i<scores.size(); i++) {
            double weight = safe_div(scores[i], sum_scores);
            for(size_t j=0; j<result.size() && j<values[i].size(); j++) {
                result[j] += weight * values[i][j];
            }
        }
        
        return result;
    }
};

struct ReinforcementSignal {
    double reward;
    double prediction_error;
    double temporal_difference;
    double policy_gradient;
    vector<double> state_value_estimate;
};

struct MetaCognitionModule {
    double self_awareness_level;
    double uncertainty_estimation;
    double confidence_calibration;
    map<string,double> knowledge_state;
    vector<string> metacognitive_thoughts;
    
    MetaCognitionModule() : self_awareness_level(0.5), uncertainty_estimation(0.5),
                           confidence_calibration(0.5) {}
};

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
    AttentionMechanism attention_system;
    MetaCognitionModule metacognition;
    ReinforcementSignal learning_signal;
};

#endif // STRUCT_H
