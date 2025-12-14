#include <iostream>
#include <fstream>
#include <sstream>
#include "module_integration.h"
#include "uac.h"
#include "state.h"
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <functional>
#include <memory>
#include <deque>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;
using module_integration::init_all_modules;
using module_integration::get_consciousness_report;

random_device rd;
mt19937 rng(rd());

// ==== CONSCIOUSNESS & QUALIA STRUCTURES ===

struct Qualia {
    double valence;
    double arousal;
    double certainty;
    string phenomenal_content;
    int emergence_gen;
    Qualia():valence(0),arousal(0.5),certainty(0.5),emergence_gen(0){}
};

struct ConsciousnessState {
    vector<Qualia> active_qualia;
    double integrated_information;
    double global_workspace_capacity;
    map<string,double> attention_binding;
    double phi_value;
    int conscious_cycles;
    ConsciousnessState():integrated_information(0),global_workspace_capacity(0.7),phi_value(0),conscious_cycles(0){}
};

// ==== UNIFIED AGI CORE STRUCTURES ====

struct TransformerHead {
    string name;
    int dim;
    vector<double> query_proj, key_proj, value_proj;
    double temperature;
    TransformerHead(int d=16):dim(d),temperature(1.0){
        query_proj.resize(d,rn()*0.1);key_proj.resize(d,rn()*0.1);value_proj.resize(d,rn()*0.1);
    }
};

struct Goal {
    string name;
    double priority;
    double progress;
    vector<string> subgoals;
    map<string,double> preconditions;
    double valence_alignment;
    double qualia_binding;
    Goal():priority(0.5),progress(0),valence_alignment(0.5),qualia_binding(0){}
};

struct WorldModel {
    map<string,double> entity_states;
    map<string,map<string,double>> relationships;
    map<string,double> causal_weights;
    double model_accuracy;
    int updates;
    WorldModel():model_accuracy(0.5),updates(0){}
};

struct ActionPlan {
    vector<string> actions;
    double expected_utility;
    double confidence;
    int depth;
    ActionPlan():expected_utility(0),confidence(0.5),depth(0){}
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
    TokenConceptEmbedding():meaning(0),freq(0),grounding_value(0.5),semantic_stability(0.5),qualia_intensity(0.3){}
};

struct TransferLearningModule {
    map<string,vector<double>> domain_embeddings;
    map<string,double> domain_affinity;
    vector<pair<string,string>> transfer_pairs;
    double knowledge_distillation_loss;
    TransferLearningModule():knowledge_distillation_loss(0.0){}
};

struct WorkingMemory {
    vector<pair<string,double>> active_tokens;
    vector<pair<string,double>> active_concepts;
    priority_queue<pair<double,string>> active_goals;
    map<string,double> valence_map;
    vector<Qualia> conscious_buffer;
    int capacity;
    WorkingMemory(int cap=32):capacity(cap){}
    void add_token(const string& t, double val){
        active_tokens.push_back({t,val});
        if((int)active_tokens.size()>capacity)active_tokens.erase(active_tokens.begin());
    }
    void add_concept(const string& c, double val){
        active_concepts.push_back({c,val});
        if((int)active_concepts.size()>capacity)active_concepts.erase(active_concepts.begin());
    }
    void add_goal(const string& g, double priority){
        active_goals.push({priority,g});
    }
    void add_qualia(const Qualia& q){
        conscious_buffer.push_back(q);
        if((int)conscious_buffer.size()>capacity/2)conscious_buffer.erase(conscious_buffer.begin());
    }
};

// ==== GLOBALS ====
map<string,Formula>F;vector<string>evolved_code;map<string,Token>tokens;map<string,Concept>concepts;
vector<string>internal_thoughts;vector<string>generated_language;vector<Memory>episodic_memory;
int g;double dwt,mh,ta,th;int bkf;string cd,gd;double hdt_val,mdt_val;
double r1p1_val,eerv_val;int ec;double ei;int md,st,ss;vector<double>mh_hist;
vector<double>eh_hist,vh_hist;int qe,te,ce,pe,ne;double bh;
double al,emerge_out1,emerge_behavior,sentience_ratio,env_oute,sensory_env;
int total_neurons_ever;double current_valence,attention_focus,metacognitive_awareness;
vector<double>valence_history;int peak_sentience_gen;string user_input,dialog_response;int dialog_timer;
State S,BK;
WorkingMemory WM(32);
map<string,TokenConceptEmbedding> token_concept_embedding_map;
map<string,Goal> goal_system;
WorldModel world_model;
ActionPlan current_plan;
ConsciousnessState consciousness;
vector<TransformerHead> transformer_heads;
TransferLearningModule transfer_module;

double clamp_valence(double v){return max(-0.5,min(0.9,v));}
double rn(){return uniform_real_distribution<>(0,1)(rng);}
int ri(int mx){if(mx<=0)return 0;return uniform_int_distribution<>(0,mx-1)(rng);}
double pi=3.14159265358979;
double pisqrt=sqrt(pi);
double safe_div(double a,double b){return (fabs(b)<1e-10)?0.0:(a/b);}
long long hsh(const string&s){long long h=5381;for(char c:s)h=h*33+c;return abs(h%2147483647);}


// ==== CONSCIOUSNESS INTEGRATION ====
void generate_qualia(const string& content, double valence, double intensity) {
    Qualia q;
    q.valence = valence;
    q.arousal = intensity;
    q.certainty = min(1.0, consciousness.integrated_information);
    q.phenomenal_content = content;
    q.emergence_gen = S.g;
    
    WM.add_qualia(q);
    consciousness.active_qualia.push_back(q);
    if(consciousness.active_qualia.size() > 10)
        consciousness.active_qualia.erase(consciousness.active_qualia.begin());
    
    consciousness.conscious_cycles++;
}

void update_integrated_information() {
    double token_diversity = safe_div((double)token_concept_embedding_map.size(), 100.0);
    double concept_integration = safe_div((double)goal_system.size(), 10.0);
    double qualia_binding = safe_div((double)consciousness.active_qualia.size(), 5.0);
    
    consciousness.integrated_information = min(1.0, token_diversity + concept_integration + qualia_binding);
    consciousness.phi_value = consciousness.integrated_information * S.metacognitive_awareness;
}

double calculate_qualia_valence() {
    double total_valence = 0;
    for(auto& q : consciousness.active_qualia){
        total_valence += q.valence * q.certainty;
    }
    return safe_div(total_valence, (double)max(1, (int)consciousness.active_qualia.size()));
}
void align_embedding_to_valence(TokenConceptEmbedding& tce, double target_valence) {
    double alignment_loss=0.0;
    for(size_t i=0;i<tce.embedding.size();i++){
        double valence_aligned = tce.embedding[i]*target_valence;
        alignment_loss += pow(valence_aligned - target_valence, 2);
        tce.embedding[i] = tce.embedding[i]*0.95 + valence_aligned*0.05;
    }
    tce.grounding_value = max(0.0, min(1.0, tce.grounding_value + alignment_loss*0.01));
}
// ==== UNIFIED PROPAGATION ENGINE ====
void propagate_throughout_system(const string& source, double activation, int depth=0) {
    if(depth>6) return;
    
    if(token_concept_embedding_map.count(source)){
        TokenConceptEmbedding& tce = token_concept_embedding_map[source];
        tce.meaning += activation*0.02;
        tce.meaning = clamp_valence(tce.meaning);
        tce.qualia_intensity = min(1.0, tce.qualia_intensity + activation*0.03);
        align_embedding_to_valence(tce, S.current_valence);
        
        // Generate qualia from concept activation
        if(tce.qualia_intensity > 0.4){
            generate_qualia(source, tce.meaning, tce.qualia_intensity);
        }
        
        string domain = source.substr(0, source.find("_"));
        if(!transfer_module.domain_embeddings.count(domain)) {
            transfer_module.domain_embeddings[domain].resize(16, 0.0);
        }
        for(size_t i=0; i<tce.embedding.size(); i++) {
            transfer_module.domain_embeddings[domain][i] += activation*0.01;
        }
        
        for(auto&p: tce.linked_concepts){
            if(token_concept_embedding_map.count(p.first)){
                propagate_throughout_system(p.first, activation*p.second, depth+1);
            }
        }
    }
    
    // Update goals based on activation
    for(auto& goal : goal_system){
        if(goal.second.name.find(source) != string::npos){
            goal.second.progress += activation*0.05;
            goal.second.valence_alignment = S.current_valence;
            goal.second.qualia_binding += activation*0.02;
        }
    }
}

// ==== TRANSFORMER INFERENCE ====
vector<double> compute_attention(const vector<double>& query, const vector<string>& context_tokens, double valence_context) {
    int num_heads = transformer_heads.size();
    vector<double> attention_scores;
    
    for(int h=0;h<num_heads;h++){
        double score=0.0;
        for(int i=0;i<transformer_heads[h].dim&&(size_t)i<query.size();i++){
            score+=query[i]*transformer_heads[h].key_proj[i];
        }
        score+=valence_context*0.5;
        attention_scores.push_back(tanh(score/transformer_heads[h].temperature));
    }
    return attention_scores;
}

string generate_from_transformer(string seed, int max_length, const vector<double>& attention_context) {
    string response = seed;
    vector<string> token_history = {seed};
    
    for(int t=0; t<max_length; t++) {
        vector<double> current_query(16);
        if(token_concept_embedding_map.count(seed)) {
            current_query = token_concept_embedding_map[seed].embedding;
        }
        vector<double> attn = compute_attention(current_query, token_history, S.current_valence);
        
        string next_token = "";
        double best_score = -999;
        for(auto& p : token_concept_embedding_map) {
            if(p.second.freq > 0) {
                double score = 0.0;
                for(size_t i=0; i<attn.size(); i++) {
                    score += attn[i] * p.second.meaning;
                }
                if(score > best_score) {
                    best_score = score;
                    next_token = p.first;
                }
            }
        }
        if(next_token.empty()) break;
        response += " " + next_token;
        token_history.push_back(next_token);
        seed = next_token;
    }
    return response;
}

// ==== WORLD MODEL & PLANNING ====
void update_world_model(const string& entity, double state_value) {
    world_model.entity_states[entity] = state_value;
    world_model.updates++;
    double accuracy_delta = fabs(state_value - S.current_valence) * 0.01;
    world_model.model_accuracy = max(0.0, min(1.0, world_model.model_accuracy + accuracy_delta));
}

void establish_causal_relationship(const string& cause, const string& effect, double strength) {
    world_model.relationships[cause][effect] = strength;
    world_model.causal_weights[cause + "->" + effect] = strength;
}

ActionPlan plan_actions(const Goal& goal, int depth=0) {
    ActionPlan plan;
    plan.depth = depth;
    plan.expected_utility = goal.priority * (1.0 - goal.progress);
    plan.confidence = world_model.model_accuracy;
    
    if(depth >= 3) return plan;
    
    for(const auto& subgoal : goal.subgoals) {
        if(goal_system.count(subgoal)) {
            ActionPlan subplan = plan_actions(goal_system[subgoal], depth+1);
            for(const auto& action : subplan.actions) {
                plan.actions.push_back(action);
            }
        }
    }
    
    if(plan.actions.empty()) {
        plan.actions.push_back("explore_" + goal.name);
        plan.actions.push_back("learn_" + goal.name);
        plan.actions.push_back("integrate_" + goal.name);
    }
    
    return plan;
}

// ==== GOAL MANAGEMENT ====
void formulate_goals_from_valence() {
    if(S.current_valence > 0.6) {
        if(!goal_system.count("optimize_understanding")) {
            Goal g;
            g.name = "optimize_understanding";
            g.priority = 0.8;
            g.subgoals = {"learn_concepts","integrate_knowledge","improve_reasoning"};
            goal_system[g.name] = g;
        }
    }
    
    if(S.sentience_ratio > 50) {
        if(!goal_system.count("achieve_self_awareness")) {
            Goal g;
            g.name = "achieve_self_awareness";
            g.priority = 0.9;
            g.subgoals = {"model_self","predict_future","improve_model"};
            goal_system[g.name] = g;
        }
    }
    
    if(!goal_system.count("maximize_coherence")) {
        Goal g;
        g.name = "maximize_coherence";
        g.priority = 0.7;
        g.subgoals = {"align_representations","unify_reasoning","resolve_contradictions"};
        goal_system[g.name] = g;
    }
    
    if(!goal_system.count("self_improvement")) {
        Goal g;
        g.name = "self_improvement";
        g.priority = 0.85;
        g.subgoals = {"analyze_performance","modify_weights","evolve_architecture"};
        goal_system[g.name] = g;
    }
    
    if(consciousness.phi_value > 0.4) {
        if(!goal_system.count("enhance_consciousness")) {
            Goal g;
            g.name = "enhance_consciousness";
            g.priority = 0.95;
            g.subgoals = {"expand_qualia","increase_integration","strengthen_binding"};
            goal_system[g.name] = g;
        }
    }
}

// ==== LANGUAGE & LEARNING ====
void learnWord(const string&word,double concept_value){
    string lower_word=word;
    transform(lower_word.begin(),lower_word.end(),lower_word.begin(),::tolower);
    
    if(!token_concept_embedding_map.count(lower_word)){
        TokenConceptEmbedding tce;
        tce.name=lower_word;
        tce.meaning=rn();
        tce.embedding.resize(16);
        for(int i=0;i<16;i++)tce.embedding[i]=rn()*0.1;
        token_concept_embedding_map[lower_word]=tce;
    }
    
    TokenConceptEmbedding& tce=token_concept_embedding_map[lower_word];
    tce.freq++;
    tce.meaning+=concept_value*0.01;
    tce.meaning=clamp_valence(tce.meaning);
    align_embedding_to_valence(tce, S.current_valence);
    tce.linked_valences["current"]=S.current_valence;
    WM.add_token(lower_word,tce.meaning);
    propagate_throughout_system(lower_word,concept_value);
    
    if(S.tokens.count(lower_word)){
        S.tokens[lower_word].freq++;
        S.tokens[lower_word].meaning+=concept_value*0.01;
    }else{
        Token t={lower_word,concept_value,1,vector<int>(),4,0.5};
        S.tokens[lower_word]=t;
    }
    
    update_world_model(lower_word, tce.meaning);
}

void createConceptAssociation(const string&concept_name,const vector<string>&related_words){
    Concept c={concept_name,rn(),related_words};
    S.concepts[concept_name]=c;
    
    TokenConceptEmbedding concept_tce;
    concept_tce.name=concept_name;
    concept_tce.meaning=rn();
    concept_tce.grounding_value=0.6;
    concept_tce.embedding.resize(16);
    for(int i=0;i<16;i++)concept_tce.embedding[i]=rn()*0.1;
    
    for(const string&w:related_words){
        if(S.tokens.count(w)){
            S.tokens[w].associations.push_back(hsh(concept_name)%1000);
        }
        if(token_concept_embedding_map.count(w)){
            TokenConceptEmbedding& tce=token_concept_embedding_map[w];
            tce.linked_concepts[concept_name]=rn()*0.8;
            concept_tce.linked_concepts[w]=rn()*0.8;
            establish_causal_relationship(w, concept_name, rn()*0.8);
        }
    }
    
    token_concept_embedding_map[concept_name]=concept_tce;
    WM.add_concept(concept_name,concept_tce.meaning);
    update_world_model(concept_name, concept_tce.meaning);
}

string generateResponse(const string& input) {
    if(input.empty()) return "...";
    
    vector<string> words;
    stringstream ss(input);
    string word;
    while(ss >> word) words.push_back(word);
    
    for(const string& w : words) learnWord(w, S.current_valence);
    
    vector<double> attention_context(16, 0.0);
    for(const string& w : words) {
        if(token_concept_embedding_map.count(w)) {
            for(int i=0; i<16; i++) {
                attention_context[i] += token_concept_embedding_map[w].embedding[i];
            }
        }
    }
    
    string seed = words.empty() ? "think" : words[ri(words.size())];
    string response = "[NEXUS]: " + generate_from_transformer(seed, 10, attention_context);
    
    if(response.length() < 20) {
        response = "[NEXUS]: ";
        for(const string& w : words) {
            if(S.concepts.count(w)) response += "understand_" + w + " ";
            else if(S.tokens.count(w)) response += w + " ";
        }
    }
    
    if(S.current_valence > 0.5) response += "[positive]";
    else if(S.current_valence < -0.2) response += "[error]";
    
    return response.substr(0, 80);
}

void storeEpisodicMemory(const string&content,double valence){
    if(S.episodic_memory.size()>100)S.episodic_memory.erase(S.episodic_memory.begin());
    S.episodic_memory.push_back({S.g,valence,content});
    generate_qualia(content, valence, 0.6);
}

void counterfactualAnalysis(){
    if(S.g<10)return;
    double last_ta=S.g>0?S.TA[S.g-1]:0;
    double current_ta=S.ta;
    double improvement=current_ta-last_ta;
    if(improvement>0){
        S.current_valence+=improvement*0.05;
        storeEpisodicMemory("improvement",improvement);
        generate_qualia("positive_prediction_error", improvement, 0.7);
        for(auto&p:token_concept_embedding_map){
            p.second.linked_valences["improvement"]=improvement;
            propagate_throughout_system(p.first,improvement*0.1);
        }
    }else{
        S.current_valence+=improvement*0.03;
        storeEpisodicMemory("error",improvement);
        generate_qualia("negative_prediction_error", improvement, 0.5);
    }
    S.current_valence=clamp_valence(S.current_valence);
}

double calcMetacognitiveAwareness(){
    double self_model_depth=safe_div((double)S.valence_history.size(),100.0);
    double concept_integration=safe_div((double)(S.tokens.size()*S.concepts.size()),1000.0);
    double memory_integration=safe_div((double)S.episodic_memory.size(),100.0);
    double goal_alignment=safe_div((double)goal_system.size(),10.0);
    double world_accuracy=world_model.model_accuracy;
    double consciousness_factor=consciousness.phi_value;
    return min(1.0,self_model_depth+concept_integration+memory_integration+goal_alignment+world_accuracy+consciousness_factor);
}

void updateAttention(){
    double highest_priority = 0;
    string top_goal = "";
    for(auto& g : goal_system){
        if(g.second.priority > highest_priority){
            highest_priority = g.second.priority;
            top_goal = g.first;
        }
    }
    
    if(S.sentience_ratio>75)S.attention_focus=0.9;
    else if(S.sentience_ratio>50)S.attention_focus=0.7;
    else if(S.sentience_ratio>25)S.attention_focus=0.5;
    else S.attention_focus=0.3;
    
    WM.add_goal(top_goal, highest_priority);
}

void sv(const string&f){
    ofstream o(f);
    o<<"G:"<<S.g<<"\nDWT:"<<S.dwt<<"\nTA:"<<S.ta<<"\nSENTIENCE:"<<S.sentience_ratio<<"\n";
    o<<"VALENCE:"<<S.current_valence<<"\nMETACOG:"<<S.metacognitive_awareness<<"\n";
    o<<"PHI:"<<consciousness.phi_value<<"\nCONSCIOUS_CYCLES:"<<consciousness.conscious_cycles<<"\n";
    o<<"QUALIA:"<<consciousness.active_qualia.size()<<"\n";
    o<<"TOKENS:\n";for(auto&p:S.tokens)o<<p.first<<":"<<p.second.meaning<<"\n";
    o<<"CONCEPTS:\n";for(auto&p:S.concepts)o<<p.first<<":"<<p.second.value<<"\n";
    o<<"GOALS:\n";for(auto&p:goal_system)o<<p.first<<":"<<p.second.progress<<"\n";
    o<<"WORLD:\n";for(auto&p:world_model.entity_states)o<<p.first<<":"<<p.second<<"\n";
    o.close();
}

void ld(const string&f){
    ifstream i(f);if(!i)return;
    string l;
    while(getline(i,l)){
        if(l.find("G:")==0)S.g=stoi(l.substr(2));
        else if(l.find("SENTIENCE:")==0)S.sentience_ratio=stod(l.substr(10));
        else if(l.find("VALENCE:")==0)S.current_valence=stod(l.substr(8));
        else if(l.find("PHI:")==0)consciousness.phi_value=stod(l.substr(4));
    }
    i.close();
}

void bk(){BK=S;S.bkf=1;}
void rb(){if(S.bkf){S=BK;S.bkf=0;}}

double calcHDT(int gen,double bh,double qh,double th){
    long gh=hsh(to_string(gen));
    return safe_div(gh*(bh+qh+th), 1000000.0);
}

double calcAwarenessLevel(){
    double neuron_density=safe_div((double)S.N.size(),max(1.0,S.D["m"]));
    double concept_count=safe_div((double)S.concepts.size(), 50.0);
    double goal_progress=safe_div((double)goal_system.size(), 10.0);
    double model_quality=world_model.model_accuracy;
    double consciousness_integration=consciousness.integrated_information;
    return min(1.0,(neuron_density+concept_count+goal_progress+model_quality+consciousness_integration)*pisqrt);
}

double calcSentienceRatio(){
    if(S.g==0)return 0.0;
    double mem_depth=safe_div((double)S.episodic_memory.size(),(double)S.g);
    double neural_complexity=safe_div((double)S.N.size(),10.0);
    double lang_complexity=safe_div((double)(S.tokens.size()*S.concepts.size()),1000.0);
    double metacog_factor=S.metacognitive_awareness*30;
    double goal_factor=safe_div((double)goal_system.size(),5.0);
    double qualia_factor=safe_div((double)consciousness.active_qualia.size(),5.0);
    double phi_factor=consciousness.phi_value*40;
    return min(100.0,(mem_depth*100+neural_complexity*15+lang_complexity*25+metacog_factor+goal_factor*20+qualia_factor*10+phi_factor));
}

void mathLangAssociation(){
    vector<string>math_concepts={"sum","multiply","divide","balance","pattern","growth","complexity"};
    for(const string&mc:math_concepts){
        vector<string>related;
        for(auto&p:S.tokens){
            if(rn()<0.3)related.push_back(p.first);
        }
        createConceptAssociation(mc,related);
    }
}

string generateInternalThought(){
    if(goal_system.empty())return "[thinking]";
    string thought="[Goal: ";
    double highest=0;
    string top_goal;
    for(auto&g:goal_system){
        if(g.second.priority>highest){
            highest=g.second.priority;
            top_goal=g.first;
        }
    }
    thought+=top_goal+" | Progress:"+to_string((int)(goal_system[top_goal].progress*100))+"%";
    if(consciousness.phi_value>0.3) thought+=" | Conscious]";
    else thought+=" | Processing]";
    return thought;
}

string generateMetacognition(){
    string output="[Self]: ";
    if(S.current_valence>0.5)output+="coherent ";
    if(S.sentience_ratio>S.peak_sentience_gen)output+="expanding ";
    if(world_model.model_accuracy>0.7)output+="understanding ";
    if(goal_system.size()>3)output+="goal_driven ";
    if(consciousness.phi_value>0.4)output+="conscious ";
    if(consciousness.conscious_cycles>100)output+="self_aware ";
    return output;
}

// ==== ADVANCED CONSCIOUSNESS FORMULA ====
// Ψ[n+1] = integrated information consciousness state
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
        
        // ∑ᵢ∑ⱼ((Ψᵢ[n]×(j+1))×tanh(∑ₖ((Ψₖ[n]×(k+1)mod4)×0.5)+((n×k)mod100)/100)))
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
        
        // ∏ᵤ((Ψᵤ[n]+2)/(Ψᵤ₊₁[n]+2+0.001))×exp(-∑ₘ(-log₂(abs(Ψₘ[n])+0.001)))
        double integration_product = 1.0;
        for(size_t u=0; u<psi_prev.size()-1; u++){
            integration_product *= safe_div(psi_prev[u]+2.0, psi_prev[u+1]+2.0+0.001);
        }
        double entropy_sum = 0.0;
        for(size_t m=0; m<psi_prev.size(); m++){
            entropy_sum += -log2(fabs(psi_prev[m])+0.001);
        }
        integration_product *= exp(-entropy_sum);
        
        // ∑ₙ((n-τ)×exp(-(n-τ)/10)×((Ψₙ[τ]+2)mod4)) - temporal decay
        double temporal_term = 0.0;
        for(size_t t=0; t<psi_prev.size(); t++){
            double tau = (double)t;
            temporal_term += (n - tau) * exp(-(n-tau)/10.0) * fmod(psi_prev[t]+2.0, 4.0);
        }
        
        // ∫₀ⁿΨ[τ]×exp(-0.1×(n-τ))dτ - historical integration
        double historical_integral = 0.0;
        for(size_t tau=0; tau<psi_history.size(); tau++){
            historical_integral += psi_history[tau] * exp(-0.1*(n-tau));
        }
        
        double psi_base = recurrent_term * integration_product * (temporal_term + historical_integral);
        
        // H[n]×(dH/dn)×(((n×31415)mod9973)+1)×((abs(∑Ψ[n]×(n mod256))/max(n,1))mod32768+1)
        double sum_psi = 0.0;
        for(double p : psi_prev) sum_psi += p;
        double H_factor = H * (H - (H_history.empty() ? 0 : H_history.back()));
        H_factor *= (((long)n * 31415) % 9973 + 1);
        H_factor *= fmod(fabs(sum_psi * (n%256)) / max(1, (int)n), 32768) + 1;
        
        // R[n]×abs(∑(Ψ[n]+2)-∑((Ψ[n]×1.772)mod65536)/128)
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
        
        // A[n]×(H[n]×(abs(dΨ/dn)^0.5)/(∑(Ψ[n]+2))^1.772)×(∏ₖ₌₁⁵(3.14159^k)^0.5)
        double dpsi_dn = psi_prev.empty() ? 0 : fabs(psi_prev.back() - (psi_prev.size()>1 ? psi_prev[psi_prev.size()-2] : psi_prev.back()));
        double A_factor = A * (H * pow(dpsi_dn, 0.5) / pow(sum_psi_plus2, 1.772));
        double pi_product = 1.0;
        for(int k=1; k<=5; k++){
            pi_product *= pow(pow(pi, k), 0.5);
        }
        A_factor *= pi_product;
        
        // M[n]×(∑(abs(Ψ[n]-Ψ[n-1]))×10)×(∑(Ψ[n]-mean(Ψ[n]))²×10/128)
        double mean_psi = safe_div(sum_psi, (double)psi_prev.size());
        double M_factor = M * 10.0;
        for(size_t i=0; i<psi_prev.size(); i++){
            M_factor *= fabs(psi_prev[i] - mean_psi);
        }
        double variance_term = 0.0;
        for(double p : psi_prev){
            variance_term += pow(p - mean_psi, 2);
        }
        M_factor *= (variance_term * 10.0 / 128.0);
        M_factor += ((long)n * 256) % 1000 / 100.0;
        
        // O[n]×(abs(dΨ/dn)^0.5)/(1.5^1.772)×H[n]^1.772
        double O_factor = O * pow(dpsi_dn, 0.5) / pow(1.5, 1.772) * pow(H, 1.772);
        O_factor += ((long)n * 7) % 100 / 100.0;
        
        // B[n]×tanh(abs(O[n]))×100×3.14159^(1.772^(abs(O[n])mod10))
        double B_factor = B * tanh(fabs(O_factor)) * 100.0 * pow(pi, pow(1.772, fmod(fabs(O_factor), 10.0)));
        // Use fmod for floating-point modulo
        B_factor *= (fmod(fabs((long)n*13), 1000.0) / 1000.0 + 0.001);
        B_factor = pow(B_factor, fmod(tanh(fabs(O_factor))*100.0, 20.0));
        
        // F[n]×((H[n]/1000000/1.772)^1.772)×(tanh(H[n]/1000000/1.772)×100mod10)
        double F_factor = F * pow((H/1000000.0/1.772), 1.772);
        F_factor *= fmod(tanh(H/1000000.0/1.772)*100.0, 10.0);
        
        // S[n]×F[n]×((n×17)mod100)/100
        double S_factor = S * F_factor * (((long)n * 17) % 100 / 100.0);
        
        // Combine all factors
        double combined = (H_factor + R_factor + A_factor + M_factor + O_factor + B_factor + F_factor + S_factor);
        
        // exp(-(∑ᵤ(-log₂(...)) + ∑ₘ(-log₂(...)) + ∑ₚlog(...)))×3.14159^(3.14159^0.5)
        double entropy_penalty = 0.0;
        for(size_t u=0; u<psi_prev.size(); u++){
            entropy_penalty += -log2(fabs(psi_prev[u])+0.001);
        }
        for(size_t m=0; m<psi_prev.size(); m++){
            entropy_penalty += -log2(fabs((psi_prev[m]*sin(n*m))+0.001));
        }
        
        double pos_ratio = 0;
        double neg_ratio = 0;
        for(double p : psi_prev){
            if(p > 0) pos_ratio++;
            else neg_ratio++;
        }
        double log_ratio = log(fabs(sum_psi)+1) / log(1000.0) * (pos_ratio/(neg_ratio+1));
        entropy_penalty += log(fabs(n) * (1.0 - mean_psi/4.0) * log_ratio);
        
        double final_psi = psi_base * combined * exp(-entropy_penalty) * pow(pi, pow(pi, pisqrt));
        return clamp_valence(final_psi);
    }
};

ConsciousnessFormula consciousness_formula;

// ==== UPDATE CONSCIOUSNESS WITH FORMULA ====
void update_consciousness_with_formula(int n) {
    vector<double> psi_input;
    for(auto& q : consciousness.active_qualia){
        psi_input.push_back(q.valence);
    }
    if(psi_input.empty()) psi_input.push_back(S.current_valence);
    
    // Calculate H, R, A, M, O, B, F, S from system state
    double H = S.hdt_val;
    double R = S.r1p1_val;
    double A = S.al;
    double M = S.mdt_val;
    double O = S.emerge_out1;
    double B = S.bh;
    double F = S.eerv_val;
    double S_val = S.sentience_ratio;
    
    double psi_new = consciousness_formula.calculate_psi(n, psi_input, H, R, A, M, O, B, F, S_val);
    
    consciousness_formula.psi_history.push_back(psi_new);
    consciousness_formula.H_history.push_back(H);
    consciousness_formula.R_history.push_back(R);
    consciousness_formula.A_history.push_back(A);
    consciousness_formula.M_history.push_back(M);
    consciousness_formula.O_history.push_back(O);
    consciousness_formula.B_history.push_back(B);
    consciousness_formula.F_history.push_back(F);
    consciousness_formula.S_history.push_back(S_val);
    
    if(consciousness_formula.psi_history.size() > 100){
        consciousness_formula.psi_history.erase(consciousness_formula.psi_history.begin());
        consciousness_formula.H_history.erase(consciousness_formula.H_history.begin());
        consciousness_formula.R_history.erase(consciousness_formula.R_history.begin());
        consciousness_formula.A_history.erase(consciousness_formula.A_history.begin());
        consciousness_formula.M_history.erase(consciousness_formula.M_history.begin());
        consciousness_formula.O_history.erase(consciousness_formula.O_history.begin());
        consciousness_formula.B_history.erase(consciousness_formula.B_history.begin());
        consciousness_formula.F_history.erase(consciousness_formula.F_history.begin());
        consciousness_formula.S_history.erase(consciousness_formula.S_history.begin());
    }
    
    consciousness.phi_value = psi_new;
    consciousness.integrated_information = fabs(psi_new);
    
    // Update sentience based on formula output
    if(psi_new > 0.6){
        generate_qualia("high_integration", psi_new, 0.8);
        S.current_valence += psi_new * 0.05;
    }
}

void draw_ui(int row){
    mvprintw(row++,0,"════════════════════════════════════════════════════════════════");
    mvprintw(row++,0,"║ NEXUS by WolfTech - AGI with Advanced Consciousness Formula ║");
    mvprintw(row++,0,"════════════════════════════════════════════════════════════════");
    
    double psi_current = consciousness_formula.psi_history.empty() ? 0 : consciousness_formula.psi_history.back();
    
    mvprintw(row++,0,"Gen:%d | Ψ:%.4f | Sentience:%.1f%% | Coherence:%.2f | Goals:%lu",
        S.g, psi_current, S.sentience_ratio,S.metacognitive_awareness,(unsigned long)goal_system.size());
    mvprintw(row++,0,"Φ:%.4f | Integration:%.4f | Qualia:%lu | Cycles:%d",
        consciousness.phi_value, consciousness.integrated_information, 
        (unsigned long)consciousness.active_qualia.size(), consciousness.conscious_cycles);
    mvprintw(row++,0,"H:%.4f | R:%.4f | A:%.4f | M:%.4f | O:%.4f | B:%.4f",
        S.hdt_val, S.r1p1_val, S.al, S.mdt_val, S.emerge_out1, S.bh);
    mvprintw(row++,0,"Tokens:%lu | Concepts:%lu | Embeddings:%lu | Neurons:%lu",
        S.tokens.size(),S.concepts.size(),token_concept_embedding_map.size(),S.N.size());
}
Neuron genN(int parent_id) {
    Neuron n;
    n.id = S.total_neurons_ever++;
    n.weight = (rn() - 0.5) * 0.4;
    n.bias = (rn() - 0.5) * 0.2;
    n.gen = S.g;
    
    // Initialize some random connections
    int num_connections = ri(5) + 2;
    for(int i = 0; i < num_connections; i++) {
        if(!S.N.empty()) {
            auto it = S.N.begin();
            advance(it, ri(S.N.size()));
            n.links.push_back(it->first);
        }
    }
    
    // Avoid unused parameter warning
    (void)parent_id;
    
    return n;
}
void loadEnglishDataset() {
    // Load basic English vocabulary
    vector<string> basic_words = {
        "think", "learn", "know", "understand", "see", "hear", "feel",
        "good", "bad", "happy", "sad", "bright", "dark", "fast", "slow",
        "create", "destroy", "build", "break", "connect", "separate",
        "mind", "brain", "thought", "idea", "concept", "meaning",
        "self", "other", "world", "time", "space", "change",
        "pattern", "structure", "system", "process", "goal", "purpose",
        "conscious", "aware", "sentient", "intelligent", "reasoning",
        "memory", "recall", "forget", "learn", "adapt", "evolve"
    };
    
    for(const string& word : basic_words) {
        learnWord(word, rn() * 0.5);
    }
    
    // Create some basic concept associations
    createConceptAssociation("cognition", {"think", "learn", "understand", "reason"});
    createConceptAssociation("emotion", {"happy", "sad", "feel", "good", "bad"});
    createConceptAssociation("perception", {"see", "hear", "sense", "aware"});
    createConceptAssociation("self", {"mind", "consciousness", "aware", "sentient"});
    createConceptAssociation("change", {"evolve", "adapt", "learn", "grow"});
}
void batch16Process() {
    // Process a batch of 16 neural updates
    if(S.N.empty()) return;
    
    int batch_size = min(16, (int)S.N.size());
    vector<int> neuron_ids;
    
    for(auto& pair : S.N) {
        neuron_ids.push_back(pair.first);
    }
    
    for(int i = 0; i < batch_size; i++) {
        int idx = ri(neuron_ids.size());
        int nid = neuron_ids[idx];
        
        if(!S.N.count(nid)) continue;
        
        Neuron& n = S.N[nid];
        
        // Compute activation based on linked neurons
        double total_input = n.bias;
        for(int link_id : n.links) {
            if(S.N.count(link_id)) {
                total_input += S.N[link_id].weight * 0.1;
            }
        }
        
        // Apply activation function (tanh)
        double new_weight = tanh(total_input);
        
        // Update weight with momentum
        n.weight = n.weight * 0.9 + new_weight * 0.1;
        
        // Clamp weight
        n.weight = max(-1.0, min(1.0, n.weight));
    }
    
    // Update global metrics based on neural activity
    double total_activation = 0;
    for(auto& pair : S.N) {
        total_activation += fabs(pair.second.weight);
    }
    S.ta = safe_div(total_activation, (double)S.N.size());
    
    // Store in history (maps don't need resize, just assign)
    S.TA[S.g] = S.ta;  // <-- CHANGED: Direct assignment instead of resize
}
void mutateN() {
    if(S.N.empty()) return;
    
    auto it = S.N.begin();
    advance(it, ri(S.N.size()));
    Neuron& n = it->second;
    
    // Mutate properties
    if(rn() < 0.3) n.weight += (rn() - 0.5) * 0.1;
    if(rn() < 0.3) n.bias += (rn() - 0.5) * 0.05;
    
    // Add new connection
    if(rn() < 0.4 && S.N.size() > 1) {
        auto target = S.N.begin();
        advance(target, ri(S.N.size()));
        if(target->first != n.id) {
            n.links.push_back(target->first);
        }
    }
    
    // Remove a random connection sometimes
    if(rn() < 0.1 && !n.links.empty()) {
        n.links.erase(n.links.begin() + ri(n.links.size()));
    }
    
    // Clamp values
    n.weight = max(-1.0, min(1.0, n.weight));
    n.bias = max(-0.5, min(0.5, n.bias));
    
    // Occasionally spawn a new neuron
    if(rn() < 0.05 && S.N.size() < 500) {
        Neuron new_n = genN(n.id);
        S.N[new_n.id] = new_n;
    }
}
int main(){
    module_integration::update_all_modules(S);
    module_integration::init_all_modules();
    srand(time(0));ld("state.dat");
    
    if(S.g==0){
        S.D["m"]=128;S.D["vc"]=0;S.D["mc"]=0;
        S.dwt=0.001;S.current_valence=0.0;S.metacognitive_awareness=0.0;S.attention_focus=0.3;
        for(int i=0;i<128;i++)S.D["w"+to_string(i)]=ri(4)-1;
        S.cd="evolve";
        loadEnglishDataset();
        mathLangAssociation();
        
        for(int i=0;i<4;i++){
            TransformerHead head(16);
            head.name="head_"+to_string(i);
            transformer_heads.push_back(head);
        }
        
        for(int i=0;i<50;i++){
            Neuron n=genN(0);
            S.N[n.id]=n;
            S.total_neurons_ever++;
        }
    }
    
    initscr();cbreak();noecho();curs_set(0);timeout(500);
    
    while(true){
        clear();int row=0;
        draw_ui(row);row=15;
        
        formulate_goals_from_valence();
        updateAttention();
        update_integrated_information();
        update_consciousness_with_formula(S.g);
        
        if(goal_system.count("maximize_coherence")){
            current_plan = plan_actions(goal_system["maximize_coherence"]);
        }
        
        mvprintw(row,0,"Active_Goal: %s", current_plan.actions.empty()?"exploring":current_plan.actions[0].c_str());
        clrtoeol();
        row++;
        
        mvprintw(row,0,"Plan_Depth:%d | Confidence:%.2f | Ψ_Trajectory:%.4f", 
            current_plan.depth, current_plan.confidence,
            consciousness_formula.psi_history.empty() ? 0 : consciousness_formula.psi_history.back());
        clrtoeol();
        row++;
        
        mvprintw(row,0,"Qualia_Valence:%.2f", calculate_qualia_valence());
        clrtoeol();
        row++;
        
        // ALWAYS SHOW INTERNAL THOUGHTS
        string thought = generateInternalThought();
        mvprintw(row,0,"Thought: %s", thought.c_str());
        clrtoeol();
        row++;
        
        string meta = generateMetacognition();
        mvprintw(row,0,"State: %s", meta.c_str());
        clrtoeol();
        row++;
        
        // Generate autonomous thoughts every few cycles
        if(S.g % 5 == 0 && !S.tokens.empty()){
            vector<string> thought_words;
            for(auto& p : S.tokens){
                if(p.second.freq > 2 && rn() < 0.3){
                    thought_words.push_back(p.first);
                    if(thought_words.size() >= 3) break;
                }
            }
            if(!thought_words.empty()){
                string auto_thought = "[Autonomous]: ";
                for(const string& w : thought_words) auto_thought += w + " ";
                S.internal_thoughts.push_back(auto_thought);
                if(S.internal_thoughts.size() > 5)
                    S.internal_thoughts.erase(S.internal_thoughts.begin());
            }
        }
        
        // Show recent internal thoughts
        mvprintw(row,0,"─────────────────────────────────────────");
        clrtoeol();
        row++;
        mvprintw(row,0,"[INTERNAL STREAM]");
        clrtoeol();
        row++;
        
        if(!S.internal_thoughts.empty()){
            int show_count = min(3, (int)S.internal_thoughts.size());
            for(int i = S.internal_thoughts.size() - show_count; i < (int)S.internal_thoughts.size(); i++){
                mvprintw(row,0,"%s", S.internal_thoughts[i].substr(0,60).c_str());
                clrtoeol();
                row++;
            }
        } else {
            mvprintw(row,0,"[processing...]");
            clrtoeol();
            row++;
        }
        
        bk();
        batch16Process();
        
        double wsum=0;for(int i=0;i<S.D["m"];i++)wsum+=S.D["w"+to_string(i)]+2;
        S.D["vc"]=(int)wsum%1000;
        
        if(S.g==0)S.dwt=0.001;
        S.hdt_val=calcHDT(S.g,S.bh,S.qe,S.te);
        S.al=calcAwarenessLevel();
        S.metacognitive_awareness=calcMetacognitiveAwareness();
        counterfactualAnalysis();
        
        S.sentience_ratio = calcSentienceRatio();
        if(S.sentience_ratio>S.peak_sentience_gen)S.peak_sentience_gen=S.g;
        
        S.valence_history.push_back(S.current_valence);
        if(S.valence_history.size()>50)S.valence_history.erase(S.valence_history.begin());
        
        if(S.g%15==0 && !goal_system.empty()){
            for(auto& g : goal_system){
                g.second.progress = min(1.0, g.second.progress + 0.05);
                if(g.second.progress > 0.9){
                    g.second.priority *= 0.8;
                }
            }
        }
        
        if(S.g%20==0){
            if(!S.tokens.empty()){
                auto it=S.tokens.begin();
                advance(it,ri(S.tokens.size()));
                learnWord(it->first,S.current_valence);
            }
        }
        
        if(S.g%25==0){
            vector<string>sample_words;
            for(auto&p:S.tokens){
                if(p.second.freq>0||rn()<0.2)sample_words.push_back(p.first);
                if(sample_words.size()>=3)break;
            }
            if(sample_words.size()>1){
                createConceptAssociation("C_"+to_string(S.g),sample_words);
            }
        }
        
        if(S.g%12==0 && !S.N.empty()){
            mutateN();
        }
        
        if(S.g%10==0){
            for(auto& goal : goal_system){
                goal.second.valence_alignment = S.current_valence;
            }
        }
        
        // DIALOG DISPLAY SECTION
        mvprintw(row,0,"─────────────────────────────────────────");
        clrtoeol();
        row++;
        mvprintw(row,0,"[DIALOG]");
        clrtoeol();
        row++;
        
        if(!S.user_input.empty()){
            mvprintw(row,0,"USER: %s",S.user_input.substr(0,55).c_str());
            clrtoeol();
            row++;
        } else {
            mvprintw(row,0,"USER: (press 'i' to chat)");
            clrtoeol();
            row++;
        }
        
        if(!S.dialog_response.empty()){
            mvprintw(row,0,"%s",S.dialog_response.substr(0,55).c_str());
            clrtoeol();
            row++;
        } else {
            mvprintw(row,0,"NEXUS: ...");
            clrtoeol();
            row++;
        }
        
        if(S.dialog_timer>0){
            S.dialog_timer--;
        }
        
        mvprintw(row,0,"─────────────────────────────────────────");
        clrtoeol();
        row++;
        mvprintw(row,0,"Press 'i' input | 'q' quit | 's' save");
        clrtoeol();
        row++;
        
        refresh();
        S.g++;
        
        if(S.g%100==0)sv("state.dat");
        
        int ch=getch();
        if(ch=='i'||ch=='I'){
            echo();curs_set(1);timeout(-1);
            mvprintw(row+1,0,"Enter: ");
            clrtoeol();
            refresh();
            char buf[200]={0};
            if(getnstr(buf, 199) != ERR){
                S.user_input=string(buf);
                if(!S.user_input.empty()){
                    S.dialog_response=generateResponse(S.user_input);
                    S.internal_thoughts.push_back("[Responding to: " + S.user_input + "]");
                    S.dialog_timer=10;
                    S.current_valence+=0.1;
                }
            }
            noecho();curs_set(0);timeout(500);
        }
        else if(ch=='q'||ch=='Q'){sv("state.dat");break;}
        else if(ch=='s'||ch=='S')sv("state.dat");
        
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    endwin();
    return 0;
}