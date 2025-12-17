#include "enhanced_reasoning.h"
#include "state.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>

map<string, ConceptNode> EnhancedReasoning::concept_graph_;
ReasoningContext EnhancedReasoning::current_context_;

extern random_device rd;
extern mt19937 rng;
extern map<string, TokenConceptEmbedding> token_concept_embedding_map;
extern vector<string> sentence_templates;

double rn();
int ri(int mx);
double clamp_valence(double v);

void EnhancedReasoning::initialize_concept_graph() {
    if (!concept_graph_.empty()) return;
    
    build_default_concepts();
    current_context_.ambient_valence = 0.0;
    current_context_.reasoning_depth = 0;
}

void EnhancedReasoning::build_default_concepts() {
    vector<pair<string, vector<string>>> concept_map = {
        {"consciousness", {"awareness", "self", "experience", "qualia", "thought"}},
        {"learning", {"growth", "knowledge", "understanding", "adaptation", "evolution"}},
        {"emotion", {"valence", "arousal", "feeling", "sentiment", "affect"}},
        {"goal", {"purpose", "intention", "desire", "objective", "aim"}},
        {"mind", {"thought", "reason", "cognition", "intelligence", "memory"}},
        {"self", {"identity", "being", "existence", "continuity", "autonomy"}},
        {"knowledge", {"understanding", "belief", "information", "truth", "meaning"}},
        {"action", {"do", "execute", "perform", "create", "change"}},
        {"perception", {"sense", "observe", "detect", "input", "awareness"}},
        {"prediction", {"foresee", "anticipate", "imagine", "expect", "plan"}}
    };
    
    for (const auto& [concept, related] : concept_map) {
        ConceptNode node;
        node.id = concept;
        node.label = concept;
        node.valence = 0.0;
        node.grounding_strength = 0.6;
        node.activation_potential = 0.0;
        node.related_concepts = related;
        
        for (const string& rel : related) {
            node.valence_associations[rel] = 0.3 + rn() * 0.4;
        }
        
        concept_graph_[concept] = node;
    }
}

string EnhancedReasoning::reason_about_topic(const string& topic, double current_valence) {
    initialize_concept_graph();
    
    activate_concept_network(topic);
    propagate_valence_field();
    
    vector<string> causal_chain = generate_causal_chain(topic, 2);
    
    string result = topic + " ";
    for (size_t i = 0; i < causal_chain.size(); ++i) {
        if (i > 0) result += " ";
        result += causal_chain[i];
    }
    
    return result;
}

vector<string> EnhancedReasoning::generate_causal_chain(const string& concept, int depth) {
    vector<string> result;
    set<string> visited;
    
    result.push_back(concept);
    visited.insert(concept);
    
    string current = concept;
    for (int d = 0; d < depth && d < 4; ++d) {
        if (concept_graph_.count(current)) {
            const auto& node = concept_graph_[current];
            
            vector<pair<string, double>> weighted_related;
            for (const string& related : node.related_concepts) {
                if (visited.find(related) == visited.end()) {
                    double relevance = calculate_concept_relevance(related, current_context_.ambient_valence);
                    weighted_related.push_back({related, relevance});
                }
            }
            
            if (!weighted_related.empty()) {
                sort(weighted_related.begin(), weighted_related.end(),
                     [](const auto& a, const auto& b) { return a.second > b.second; });
                
                string next = weighted_related[0].first;
                result.push_back(next);
                visited.insert(next);
                current = next;
            }
        }
    }
    
    return result;
}

void EnhancedReasoning::propagate_valence_field() {
    current_context_.valence_field.clear();
    
    for (const auto& concept : current_context_.active_concepts) {
        current_context_.valence_field[concept.id] = concept.valence;
        
        for (const auto& [related, weight] : concept.valence_associations) {
            double propagated_valence = concept.valence * weight * 0.7;
            current_context_.valence_field[related] += propagated_valence;
        }
    }
    
    for (auto& [concept_id, valence] : current_context_.valence_field) {
        valence = clamp_valence(valence);
    }
}

double EnhancedReasoning::calculate_concept_relevance(const string& concept, double current_valence) {
    double relevance = 0.5;
    
    if (concept_graph_.count(concept)) {
        const auto& node = concept_graph_[concept];
        relevance += node.grounding_strength * 0.3;
        relevance += abs(node.valence - current_valence) * 0.2;
    }
    
    return clamp_valence(relevance);
}

string EnhancedReasoning::generate_coherent_thought() {
    initialize_concept_graph();
    propagate_valence_field();
    
    if (current_context_.active_concepts.empty()) {
        activate_concept_network("consciousness");
    }
    
    vector<string> thought_tokens;
    
    for (const auto& concept : current_context_.active_concepts) {
        thought_tokens.push_back(concept.id);
        if (thought_tokens.size() >= 3) break;
    }
    
    string result = "i ";
    string last_verb = "think";
    
    if (!thought_tokens.empty()) {
        vector<string> actions = {"understand", "feel", "know", "contemplate", "perceive"};
        last_verb = actions[ri(actions.size())];
        result += last_verb + " about ";
        result += thought_tokens[0];
    }
    
    return result;
}

void EnhancedReasoning::update_concept_valence(const string& concept, double valence_delta) {
    if (concept_graph_.count(concept)) {
        concept_graph_[concept].valence += valence_delta;
        concept_graph_[concept].valence = clamp_valence(concept_graph_[concept].valence);
    }
}

void EnhancedReasoning::activate_concept_network(const string& root_concept) {
    current_context_.active_concepts.clear();
    
    initialize_concept_graph();
    
    if (concept_graph_.count(root_concept)) {
        ConceptNode root = concept_graph_[root_concept];
        root.activation_potential = 1.0;
        current_context_.active_concepts.push_back(root);
        
        set<string> visited;
        visited.insert(root_concept);
        
        for (const string& related : root.related_concepts) {
            if (visited.find(related) == visited.end() && concept_graph_.count(related)) {
                ConceptNode related_node = concept_graph_[related];
                related_node.activation_potential = 0.6;
                current_context_.active_concepts.push_back(related_node);
                visited.insert(related);
            }
        }
    }
    
    propagate_valence_field();
}

string EnhancedReasoning::infer_from_context(const vector<string>& context_tokens) {
    set<string> context_set(context_tokens.begin(), context_tokens.end());
    
    vector<string> inferred_concepts;
    double max_relevance = 0.0;
    string best_concept;
    
    for (auto& [concept_id, node] : concept_graph_) {
        double relevance = 0.0;
        
        for (const string& token : context_tokens) {
            if (find(node.related_concepts.begin(), node.related_concepts.end(), token) 
                != node.related_concepts.end()) {
                relevance += 0.5;
            }
        }
        
        relevance += node.grounding_strength * 0.2;
        
        if (relevance > max_relevance) {
            max_relevance = relevance;
            best_concept = concept_id;
        }
    }
    
    if (!best_concept.empty()) {
        return reason_about_topic(best_concept, current_context_.ambient_valence);
    }
    
    return "i think";
}
