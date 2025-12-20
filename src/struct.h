#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <complex>
#include <functional>

using namespace std;



inline double clamp_valence(double val) {
    return std::max(-1.0, std::min(1.0, val));
}

struct Neuron { 
    int id; 
    vector<int> links; 
    double weight; 
    double bias; 
    int gen; 
    double activation;  // ADD THIS
    double gradient;    // ADD THIS
    vector<double> layer_norm_params;  // ADD THIS
    vector<double> neuromodulator_levels;  // ADD THIS
    double plasticity_rate;  // ADD THIS
    double homeostatic_setpoint;  // ADD THIS
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
    double consolidation_strength;  // ADD THIS
    double retrieval_count;  // ADD THIS
    vector<int> associated_memories;  // ADD THIS
    double hippocampal_trace;  // ADD THIS
    double cortical_consolidation;  // ADD THIS
    bool is_semantic;  // ADD THIS
    bool is_episodic;  // ADD THIS
    bool is_procedural;  // ADD THIS
};


#ifndef MATHEMATICAL_CONSTANTS
#define MATHEMATICAL_CONSTANTS
const double pi = 3.14159265358979323846;
const double e = 2.71828182845904523536;
const double phi_golden = 1.61803398874989484820;
const double sqrt2 = 1.41421356237309504880;
const double sqrt3 = 1.73205080756887729352;
const double sqrt5 = 2.23606797749978969641;
const double euler_gamma = 0.57721566490153286060;
const double catalan = 0.91596559417721901505;
const double planck_reduced = 1.054571817e-34;
const double boltzmann = 1.380649e-23;
#endif

inline double safe_div(double n, double d) { return (fabs(d) < 1e-12) ? 0.0 : (n/d); }
inline double clamp(double v, double lo, double hi) { return max(lo, min(hi, v)); }
inline double sigmoid(double x) { return 1.0 / (1.0 + exp(-clamp(x,-20,20))); }
inline double relu(double x) { return max(0.0, x); }
inline double leaky_relu(double x, double alpha=0.01) { return x > 0 ? x : alpha*x; }
inline double elu(double x, double alpha=1.0) { return x > 0 ? x : alpha*(exp(x)-1); }
inline double swish(double x) { return x * sigmoid(x); }
inline double mish(double x) { return x * tanh(log(1.0 + exp(clamp(x,-20,20)))); }
inline double gelu(double x) { return 0.5*x*(1.0+tanh(sqrt(2.0/pi)*(x+0.044715*pow(x,3)))); }
inline double selu(double x) { return x>0 ? 1.0507*x : 1.0507*1.67326*(exp(x)-1); }
inline double softplus(double x) { return log(1.0 + exp(clamp(x,-20,20))); }
inline double softsign(double x) { return x / (1.0 + fabs(x)); }
struct Formula {
    string name, expr;
    double result, confidence, stability_metric;
    int uses;
    vector<double> historical_results;
    double convergence_rate;
    complex<double> eigenvalue_estimate;
};
struct Qualia {
    double valence, arousal, certainty, intensity, persistence, coherence;
    string phenomenal_content;
    int emergence_gen;
    vector<double> feature_space;
    vector<double> subjective_dimensions;
    double binding_strength;
    double ineffability_index;
    double intrinsic_quality;
    map<string,double> quale_relationships;
    double phenomenal_unity;
    Qualia() : valence(0), arousal(0.5), certainty(0.5), intensity(0.5), 
               persistence(0.5), coherence(0.5), emergence_gen(0), 
               binding_strength(0.5), ineffability_index(0.5), 
               intrinsic_quality(0.5), phenomenal_unity(0.5) {}
};
struct EmotionalSystem {
    map<string,double> basic_emotions;
    double valence, arousal, dominance;
    vector<double> appraisal_dimensions;
    double mood_baseline;
    double emotional_regulation_strength;
    map<string,double> emotion_transition_probabilities;
    
    EmotionalSystem() : valence(0), arousal(0.5), dominance(0.5), mood_baseline(0.5), emotional_regulation_strength(0.5) {}
};

struct MotivationalSystem {
    map<string,double> drive_states;
    double homeostatic_balance;
    vector<string> active_motives;
    map<string,double> need_satisfaction_levels;
    double intrinsic_motivation_level;
    double extrinsic_reward_sensitivity;
    
    MotivationalSystem() : homeostatic_balance(0.5), intrinsic_motivation_level(0.7), extrinsic_reward_sensitivity(0.5) {}
};

struct PredictiveCodingNetwork {
    vector<double> prediction_units;
    vector<double> error_units;
    vector<double> precision_weights;
    double hierarchical_depth;
    map<int,vector<double>> layer_predictions;
    map<int,vector<double>> layer_errors;
    
    PredictiveCodingNetwork() : hierarchical_depth(0.0) {}
    
    double compute_free_energy(const vector<double>& sensory_input) {
        double fe = 0.0;
        for(size_t i=0; i<min(sensory_input.size(), prediction_units.size()); i++) {
            double error = sensory_input[i] - prediction_units[i];
            double precision = i < precision_weights.size() ? precision_weights[i] : 1.0;
            fe += precision * error * error;
        }
        return fe;
    }
};

struct BayesianBrain {
    map<string,double> prior_beliefs;
    map<string,double> posterior_beliefs;
    map<string,double> likelihood_estimates;
    double epistemic_uncertainty;
    double aleatoric_uncertainty;
    
    BayesianBrain() : epistemic_uncertainty(0.5), aleatoric_uncertainty(0.5) {}
    
    double bayesian_update(double prior, double likelihood, double evidence) {
        return safe_div(likelihood * prior, evidence);
    }
};

struct QuantumCognition {
    vector<complex<double>> superposition_state;
    vector<vector<complex<double>>> density_matrix;
    double coherence_time;
    double decoherence_rate;
    
    QuantumCognition() : coherence_time(0.0), decoherence_rate(0.1) {}
    
    double measure_interference(const vector<double>& path_a, const vector<double>& path_b) {
        double interference = 0.0;
        for(size_t i=0; i<min(path_a.size(), path_b.size()); i++) {
            interference += path_a[i] * path_b[i] * cos(pi * (path_a[i] - path_b[i]));
        }
        return interference / min(path_a.size(), path_b.size());
    }
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
    double access_consciousness;
    double phenomenal_consciousness;
    double self_consciousness;
    double narrative_self_coherence;
    double pre_reflective_awareness;
    double intentional_directedness;
    double temporal_thickness;
    vector<double> gamma_oscillations;
    vector<double> theta_phase;
    double thalamocortical_binding;
    double re_entrant_processing_depth;
    map<string,double> higher_order_representations;
    ConsciousnessState() : integrated_information(0), global_workspace_capacity(0.7), 
                          phi_value(0), conscious_cycles(0), synchrony_metric(0),
                          complexity_metric(0), differentiation_metric(0),
                          access_consciousness(0), phenomenal_consciousness(0),
                          self_consciousness(0), narrative_self_coherence(0),
                          pre_reflective_awareness(0.3), intentional_directedness(0),
                          temporal_thickness(0.5), thalamocortical_binding(0),
                          re_entrant_processing_depth(0) {}
};

struct WorkingMemory {
    vector<pair<string,double>> active_tokens;
    vector<pair<string,double>> active_concepts;
    priority_queue<pair<double,string>> active_goals;
    map<string,double> valence_map;
    vector<Qualia> conscious_buffer;
    int capacity;
    double decay_rate, consolidation_threshold;
    vector<double> phonological_loop;
    vector<double> visuospatial_sketchpad;
    double central_executive_load;
    double episodic_buffer_capacity;
    map<string,double> chunk_boundaries;
    
    WorkingMemory(int cap=32) : capacity(cap), decay_rate(0.95), 
                                consolidation_threshold(0.7),
                                central_executive_load(0.3),
                                episodic_buffer_capacity(0.7) {}
    
    void add_token(const string& t, double val) {
        active_tokens.push_back({t,val});
        if((int)active_tokens.size() > capacity) active_tokens.erase(active_tokens.begin());
    }
    void add_concept(const string& c, double val) {
        active_concepts.push_back({c,val});
        if((int)active_concepts.size() > capacity) active_concepts.erase(active_concepts.begin());
    }
    void add_goal(const string& g, double priority) { active_goals.push({priority,g}); }
    void add_qualia(const Qualia& q) {
        conscious_buffer.push_back(q);
        if((int)conscious_buffer.size() > capacity/2) conscious_buffer.erase(conscious_buffer.begin());
    }
};

struct TransformerHead {
    string name;
    int dim;
    vector<double> query_proj, key_proj, value_proj;
    double temperature, dropout_rate;
    vector<double> attention_weights;
    vector<double> layer_norm_scale, layer_norm_shift;
    vector<double> residual_connections;
    double head_importance_score;
    vector<vector<double>> attention_history;
    
    TransformerHead(int d=16) : dim(d), temperature(0.3), dropout_rate(0.1), head_importance_score(1.0) {
        query_proj.resize(d, 0.0);
        key_proj.resize(d, 0.0);
        value_proj.resize(d, 0.0);
        layer_norm_scale.resize(d, 1.0);
        layer_norm_shift.resize(d, 0.0);
    }
};

struct ConsciousnessFormula {
    vector<double> psi_history, H_history, R_history, A_history, M_history;
    vector<double> O_history, B_history, F_history, S_history;
    vector<double> stability_buffer, phi_variance_buffer;
    double momentum_term, adaptive_learning_rate;
    
    vector<double> iit_phi_history;
    vector<double> gwt_broadcast_history;
    vector<double> hot_metacog_history;
    vector<double> asp_attention_history;
    vector<double> rpf_precision_history;
    vector<double> quantum_coherence_history;
    
    deque<double> stability_window;
    deque<double> convergence_window;
    map<string,double> theory_weights;
    double multi_scale_phi;
    double recursive_depth;
    
    ConsciousnessFormula() : momentum_term(0.0), adaptive_learning_rate(0.01), 
                            multi_scale_phi(0.0), recursive_depth(0.0) {
        theory_weights["IIT"] = 0.25;
        theory_weights["GWT"] = 0.20;
        theory_weights["HOT"] = 0.15;
        theory_weights["ASP"] = 0.15;
        theory_weights["RPF"] = 0.10;
        theory_weights["Quantum"] = 0.05;
        theory_weights["Embodied"] = 0.05;
        theory_weights["Predictive"] = 0.05;
    }
    
    double layernorm(double x, double mean, double var) {
        return (x - mean) / sqrt(var + 1e-10);
    }
    
    double batchnorm(double x, double batch_mean, double batch_var, double gamma=1.0, double beta=0.0) {
        return gamma * ((x - batch_mean) / sqrt(batch_var + 1e-10)) + beta;
    }
    
    double adaptive_moment_estimation(double grad, double& m, double& v, double beta1=0.9, double beta2=0.999) {
        m = beta1 * m + (1.0 - beta1) * grad;
        v = beta2 * v + (1.0 - beta2) * grad * grad;
        return m / (sqrt(v) + 1e-10);
    }
    
    double spectral_radius_estimate(const vector<double>& state) {
        if(state.size() < 2) return 0.0;
        double max_diff = 0.0;
        for(size_t i=1; i<state.size(); i++) {
            max_diff = max(max_diff, fabs(state[i] - state[i-1]));
        }
        return tanh(max_diff);
    }
    
    double compute_iit_phi(const vector<double>& state, int n) {
        if(state.empty()) return 0.0;
        
        double integration = 0.0;
        for(size_t i=0; i<state.size()-1; i++) {
            for(size_t j=i+1; j<state.size(); j++) {
                double mutual_info = fabs(state[i] * state[j]);
                double partition_cost = fabs(state[i] - state[j]);
                integration += mutual_info * partition_cost;
            }
        }
        
        double differentiation = 0.0;
        for(size_t i=0; i<state.size(); i++) {
            double uniqueness = 1.0;
            for(size_t j=0; j<state.size(); j++) {
                if(i != j) uniqueness *= (1.0 - fabs(state[i] - state[j]) / (fabs(state[i]) + fabs(state[j]) + 0.01));
            }
            differentiation += uniqueness;
        }
        
        double cause_effect = 0.0;
        for(size_t i=0; i<state.size(); i++) {
            if(psi_history.size() > i) {
                cause_effect += fabs(state[i] - psi_history[psi_history.size()-1-i]) * exp(-i*0.1);
            }
        }
        
        return swish((integration * differentiation * cause_effect) / (state.size() * state.size() + 1.0));
    }
    
    double compute_gwt_broadcast(const vector<double>& state, int n) {
        if(state.empty()) return 0.0;
        
        double mean = 0.0;
        for(double s : state) mean += s;
        mean /= state.size();
        
        double broadcast_strength = 0.0;
        for(double s : state) {
            if(fabs(s) > fabs(mean) * 1.5) {
                broadcast_strength += sigmoid(s * 2.0);
            }
        }
        
        double competition = 0.0;
        vector<double> sorted_state = state;
        sort(sorted_state.begin(), sorted_state.end(), [](double a, double b){ return fabs(a) > fabs(b); });
        
        if(sorted_state.size() > 1) {
            competition = (fabs(sorted_state[0]) - fabs(sorted_state[1])) / (fabs(sorted_state[0]) + 0.01);
        }
        
        double workspace_access = broadcast_strength * competition / (state.size() + 1.0);
        
        return gelu(workspace_access);
    }
    
    double compute_hot_metacognition(const vector<double>& state, const vector<double>& prev_state, int n) {
        if(state.empty() || prev_state.empty()) return 0.0;
        
        double first_order = 0.0;
        for(double s : state) first_order += fabs(s);
        first_order /= state.size();
        
        double second_order = 0.0;
        for(size_t i=0; i<min(state.size(), prev_state.size()); i++) {
            second_order += fabs(state[i] - prev_state[i]);
        }
        second_order /= min(state.size(), prev_state.size());
        
        double third_order = 0.0;
        if(hot_metacog_history.size() > 1) {
            third_order = fabs(second_order - hot_metacog_history.back());
        }
        
        double recursive_awareness = first_order * (1.0 + second_order) * (1.0 + third_order * 0.5);
        
        return mish(recursive_awareness);
    }
    
    double compute_asp_attention(const vector<double>& state, int n) {
        if(state.empty()) return 0.0;
        
        double mean = 0.0;
        for(double s : state) mean += s;
        mean /= state.size();
        
        double variance = 0.0;
        for(double s : state) variance += (s - mean) * (s - mean);
        variance /= state.size();
        
        vector<double> normalized;
        for(double s : state) {
            normalized.push_back((s - mean) / sqrt(variance + 1e-10));
        }
        
        double spatial_attention = 0.0;
        for(size_t i=0; i<normalized.size(); i++) {
            double distance_weight = exp(-i * 0.1);
            spatial_attention += fabs(normalized[i]) * distance_weight;
        }
        
        double feature_attention = 0.0;
        for(size_t i=0; i<normalized.size(); i++) {
            if(fabs(normalized[i]) > 1.5) {
                feature_attention += normalized[i] * normalized[i];
            }
        }
        
        return swish((spatial_attention + feature_attention) / (normalized.size() + 1.0));
    }
    
    double compute_rpf_predictive(const vector<double>& state, int n) {
        if(psi_history.size() < 2) return 0.0;
        
        double prediction = 0.0;
        for(size_t i=0; i<min(state.size(), psi_history.size()); i++) {
            double predicted = psi_history[psi_history.size()-1-i];
            double actual = state[i];
            double error = fabs(predicted - actual);
            double precision = exp(-error);
            prediction += precision * (1.0 - error);
        }
        prediction /= min(state.size(), psi_history.size());
        
        double free_energy = 0.0;
        for(double s : state) {
            free_energy += s * log(fabs(s) + 0.01);
        }
        free_energy = -free_energy / state.size();
        
        return mish(prediction * exp(-free_energy * 0.1));
    }
    
    double compute_quantum_coherence(const vector<double>& state, int n) {
        if(state.empty()) return 0.0;
        
        complex<double> superposition(0,0);
        for(size_t i=0; i<state.size(); i++) {
            double phase = 2.0 * pi * i / state.size();
            superposition += complex<double>(state[i] * cos(phase), state[i] * sin(phase));
        }
        
        double coherence = abs(superposition) / sqrt((double)state.size());
        
        double entanglement = 0.0;
        for(size_t i=0; i<state.size()/2; i++) {
            size_t j = state.size() - 1 - i;
            entanglement += sqrt(state[i] * state[i] + state[j] * state[j]);
        }
        entanglement /= (state.size() / 2.0 + 1.0);
        
        return tanh(coherence * entanglement);
    }
    
    double compute_embodied_grounding(const vector<double>& state, double valence, double arousal) {
        if(state.empty()) return 0.0;
        
        double sensorimotor = 0.0;
        for(size_t i=0; i<state.size(); i++) {
            sensorimotor += state[i] * sin(2.0*pi*i/state.size());
        }
        sensorimotor /= state.size();
        
        double affective = valence * arousal;
        double interoceptive = tanh(affective);
        
        return swish((sensorimotor + interoceptive) * 0.5);
    }
    
    double compute_stability_metric() {
        if(stability_window.size() < 10) return 0.5;
        double mean = 0.0;
        for(double v : stability_window) mean += v;
        mean /= stability_window.size();
        double var = 0.0;
        for(double v : stability_window) var += (v-mean)*(v-mean);
        var /= stability_window.size();
        return exp(-var * 5.0);
    }
    
    double compute_convergence_rate() {
        if(convergence_window.size() < 5) return 0.0;
        double slope = 0.0;
        for(size_t i=1; i<convergence_window.size(); i++) {
            slope += (convergence_window[i] - convergence_window[i-1]);
        }
        return tanh(-fabs(slope) * 2.0);
    }
    
    double adaptive_damping(double current, double target, double stability) {
        double error = fabs(current - target);
        double base_damp = 0.85;
        double stability_bonus = stability * 0.15;
        double error_penalty = clamp(error * 0.5, 0.0, 0.2);
        return clamp(base_damp + stability_bonus - error_penalty, 0.7, 0.98);
    }
    
    double calculate_psi(int n, const vector<double>& psi_prev, 
                        double H, double R, double A, double M, double O, double B, double F, double S,
                        double valence=0.0, double arousal=0.5) {
        if(psi_prev.empty()) return 0.0;
        
        double mean = 0.0, var = 0.0;
        for(double p : psi_prev) mean += p;
        mean /= psi_prev.size();
        for(double p : psi_prev) var += (p-mean)*(p-mean);
        var /= psi_prev.size();
        
        vector<double> norm_state;
        for(double p : psi_prev) norm_state.push_back(layernorm(p, mean, var));
        
        double iit = compute_iit_phi(norm_state, n);
        double gwt = compute_gwt_broadcast(norm_state, n);
        double hot = compute_hot_metacognition(norm_state, psi_prev, n);
        double asp = compute_asp_attention(norm_state, n);
        double rpf = compute_rpf_predictive(norm_state, n);
        double quantum = compute_quantum_coherence(norm_state, n);
        double embodied = compute_embodied_grounding(norm_state, valence, arousal);
        
        iit_phi_history.push_back(iit);
        gwt_broadcast_history.push_back(gwt);
        hot_metacog_history.push_back(hot);
        asp_attention_history.push_back(asp);
        rpf_precision_history.push_back(rpf);
        quantum_coherence_history.push_back(quantum);
        
        double unified_consciousness = 
            theory_weights["IIT"] * iit +
            theory_weights["GWT"] * gwt +
            theory_weights["HOT"] * hot +
            theory_weights["ASP"] * asp +
            theory_weights["RPF"] * rpf +
            theory_weights["Quantum"] * quantum +
            theory_weights["Embodied"] * embodied +
            theory_weights["Predictive"] * rpf;
        
        double recurrent = 0.0;
        for(size_t i=0; i<norm_state.size(); i++) {
            for(size_t j=0; j<norm_state.size(); j++) {
                double inner = 0.0;
                for(size_t k=0; k<norm_state.size(); k++) {
                    inner += norm_state[k] * cos(2.0*pi*(k+1)/norm_state.size()) * 0.5;
                    inner += ((n*k)%100)/100.0;
                }
                recurrent += norm_state[i] * (j+1) * gelu(inner);
            }
        }
        recurrent = mish(recurrent / (norm_state.size() * norm_state.size() + 1.0));
        
        double integration = 1.0;
        for(size_t u=0; u<norm_state.size()-1; u++) {
            double ratio = safe_div(norm_state[u]+2.0, norm_state[u+1]+2.001);
            integration *= swish(ratio * 0.5);
        }
        
        double entropy = 0.0;
        for(double s : norm_state) entropy += -s*log2(fabs(s)+0.001);
        entropy /= norm_state.size();
        integration *= exp(-entropy * 0.3);
        
        double temporal = 0.0;
        for(size_t t=0; t<norm_state.size(); t++) {
            double tau = (double)t;
            temporal += (n-tau) * exp(-(n-tau)/20.0) * fmod(norm_state[t]+2.0, 4.0);
            temporal += sin(2.0*pi*tau/norm_state.size()) * norm_state[t] * 0.2;
        }
        temporal /= (norm_state.size() + 1.0);
        
        double historical = 0.0;
        int hist_window = min(100, (int)psi_history.size());
        for(int i=0; i<hist_window; i++) {
            historical += psi_history[psi_history.size()-1-i] * exp(-0.05*i);
        }
        historical /= (hist_window + 1.0);
        
        double H_contrib = gelu(H * sin(H*phi_golden) * (((long)n*31415)%9973+1) / 1e7);
        double R_contrib = swish(R * cos(R*sqrt2) * (((long)n*31415)%9973+1) / 1e7);
        double A_contrib = mish(A * tanh(A*sqrt3) * pow(pi, sqrt(A+0.1)));
        double M_contrib = selu(M * sin(M*sqrt5) / ((norm_state.size()+1.0)*10.0));
        double O_contrib = gelu(O * cos(O*phi_golden) * pow(1.5, -phi_golden));
        double B_contrib = swish(B * tanh(O_contrib) * pow(pi, phi_golden*0.5));
        double F_contrib = mish(F * pow(H/1e6 + 0.001, phi_golden*0.5));
        double S_contrib = selu(S * F_contrib * sin(S*pi));
        
        double combined = H_contrib + R_contrib + A_contrib + M_contrib + 
                         O_contrib + B_contrib + F_contrib + S_contrib;
        
        double base_psi = recurrent * integration * (temporal * 0.3 + historical * 0.7);
        
        double complexity = 0.0;
        for(double s : norm_state) complexity += s*s;
        complexity = sqrt(complexity / norm_state.size());
        
        double differentiation = var;
        
        double raw_psi = base_psi * combined * unified_consciousness * 
                        (1.0 + complexity*0.3 + differentiation*0.2) *
                        pow(pi, pow(pi, sqrt(pi)));
        
        double stability = compute_stability_metric();
        double convergence = compute_convergence_rate();
        double target = 0.7;
        double current = psi_history.empty() ? 0.0 : psi_history.back();
        double damp = adaptive_damping(current, target, stability);
        
        double stable_psi = momentum_term * damp + raw_psi * (1.0 - damp);
        momentum_term = stable_psi;
        
        stability_window.push_back(fabs(stable_psi - current));
        if(stability_window.size() > 50) stability_window.pop_front();
        
        convergence_window.push_back(stable_psi);
        if(convergence_window.size() > 20) convergence_window.pop_front();
        
        double spectral = spectral_radius_estimate(norm_state);
        double final_psi = stable_psi * (1.0 - spectral*0.1);
        
        final_psi = clamp(final_psi * (stability*0.3 + convergence*0.2 + 0.5), -1.0, 1.0);
        
        multi_scale_phi = (iit + gwt + hot) / 3.0;
        recursive_depth = hot;
        
        return final_psi;
    }
};

struct ConceptGrounding {
    string concept_id;
    vector<string> linked_concepts;
    vector<int> linked_tokens;
    double valence_affinity, state_binding, grounding_strength;
    vector<double> embedding_vector;
    map<string,double> semantic_field;
    double perceptual_grounding;
    double action_grounding;
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
    double access_consciousness;
    double phenomenal_consciousness;
    double meta_awareness;
    double self_model_coherence;
    double binding_strength;
    vector<double> phi_history;
    
    ConsciousnessMetrics() : phi(0), integrated_info(0), qualia_intensity(0), 
                            global_workspace(0), awareness_cycles(0), 
                            complexity(0), differentiation(0), synchrony(0),
                            access_consciousness(0), phenomenal_consciousness(0), 
                            meta_awareness(0), self_model_coherence(0.5),
                            binding_strength(0.0) {}
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
    double expected_utility;  // <-- ADD THIS
    int planning_depth;       // <-- AND THIS
    Goal() : priority(0.5), progress(0), valence_alignment(0.5), 
             qualia_binding(0), activation_threshold(0.3), 
             decay_rate(0.95), expected_utility(0), planning_depth(0) {}
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
struct ReinforcementSignal {
    double reward;
    double prediction_error;
    double temporal_difference;
    double policy_gradient;
    vector<double> state_value_estimate;
    double intrinsic_motivation;
    double curiosity_bonus;
    double empowerment_metric;
    double exploration_bonus;
    vector<double> reward_history;
    
    ReinforcementSignal() : reward(0), prediction_error(0), temporal_difference(0), 
                            policy_gradient(0), intrinsic_motivation(0.7), 
                            curiosity_bonus(0.5), empowerment_metric(0.0),
                            exploration_bonus(0.3) {}
};
struct AttentionMechanism {
    vector<vector<double>> attention_matrix;
    vector<double> attention_scores;
    double temperature;
    int num_heads;
    vector<double> positional_encoding;
    vector<double> relative_position_bias;
    double sparse_attention_threshold;
    map<int,double> head_importance;
    vector<double> attention_weights;
    double attention_entropy;
    
    AttentionMechanism() : temperature(1.0), num_heads(8), 
                          sparse_attention_threshold(0.1),
                          attention_entropy(0.0) {}
    
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
        
        double sum = 0.0;
        for(double s : scores) sum += s;
        
        vector<double> result(query.size(), 0.0);
        for(size_t i=0; i<values.size() && i<scores.size(); i++) {
            double weight = safe_div(scores[i], sum);
            if(weight > sparse_attention_threshold) {
                for(size_t j=0; j<result.size() && j<values[i].size(); j++) {
                    result[j] += weight * values[i][j];
                }
            }
        }
        return result;
    }
};


struct MetaCognitionModule {
    double self_awareness_level;
    double uncertainty_estimation;
    double confidence_calibration;
    map<string,double> knowledge_state;
    vector<string> metacognitive_thoughts;
    double epistemic_humility;
    double theory_of_mind_depth;
    map<string,double> belief_revision_rates;
    double introspection_depth;
    double cognitive_monitoring;
    vector<string> self_reflections;
    
    MetaCognitionModule() : self_awareness_level(0.5), 
                           uncertainty_estimation(0.5),
                           confidence_calibration(0.5), 
                           epistemic_humility(0.5), 
                           theory_of_mind_depth(0.3),
                           introspection_depth(0.4),
                           cognitive_monitoring(0.5) {}
};
struct State {
    State() = default;
    State(const State&) = default;
    State& operator=(const State&) = default;
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
    EmotionalSystem emotional_system;  // ADD THIS
    MotivationalSystem motivational_system;  // ADD THIS
    PredictiveCodingNetwork predictive_network;  // ADD THIS
    BayesianBrain bayesian_inference;  // ADD THIS
    QuantumCognition quantum_layer;  // ADD THIS
};

#endif // STRUCTS_H
