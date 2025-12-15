// consciousness_module.cpp - Implementation of consciousness metrics
#include "consciousness_module.h"
#include "state.h"
#include "language_module.h"
#include <cmath>
#include <algorithm>
#include <set>

// External reference to structures
ConsciousnessMetrics CONS;

void init_consciousness_module() {
    CONS.working_memory = 0.0;
    CONS.integrated_information = 0.0;
    CONS.global_workspace = 0.0;
    CONS.introspection = 0.0;
    CONS.reflection = 0.0;
    CONS.prediction_error = 0.0;
    CONS.surprise = 0.0;
    CONS.curiosity = 0.0;
    CONS.active_buffer.clear();
}

double calc_working_memory(const std::vector<std::string>& active_buffer) {
    // Working memory capacity is typically 7±2 items
    double active_load = std::min(1.0, active_buffer.size() / 7.0);
    
    // Calculate recent context from buffer
    double recent_context = active_buffer.size() > 0 ? 
        std::min(1.0, active_buffer.size() / 5.0) : 0.0;
    
    CONS.working_memory = active_load * 0.6 + recent_context * 0.4;
    return CONS.working_memory;
}

double calc_integrated_info(std::map<int, Neuron>& neurons) {
    if (neurons.size() < 10) return 0.0;
    
    // Calculate network connectivity
    int total_possible = neurons.size() * (neurons.size() - 1);
    int actual_connections = 0;
    
    for (auto& n : neurons) {
        actual_connections += n.second.links.size();
    }
    
    double connectivity = total_possible > 0 ? 
        (double)actual_connections / total_possible : 0.0;
    
    // Calculate integration (simplified Phi approximation)
    double integration = connectivity * std::sqrt(neurons.size() / 100.0);
    
    CONS.integrated_information = std::max(0.0, std::min(1.0, integration * std::sqrt(M_PI)));
    return CONS.integrated_information;
}

double calc_global_workspace(
    const std::vector<std::string>& active_concepts,
    double attention,
    double working_memory
) {
    // Calculate concept broadcast
    double concept_broadcast = active_concepts.size() > 0 ?
        std::min(1.0, active_concepts.size() / 3.0) : 0.0;
    
    // Global workspace = broadcast × attention × working memory
    double workspace = concept_broadcast * 0.3 + attention * 0.25 + 
                      working_memory * 0.25;
    
    // Add attention weighting
    workspace += (attention / 100.0) * 0.2;
    
    CONS.global_workspace = std::max(0.0, std::min(1.0, workspace));
    return CONS.global_workspace;
}

double calc_introspection(
    const std::vector<Memory>& episodic_mem,
    const std::map<int, double>& temporal_awareness,
    int current_gen
) {
    // Self-awareness through memory
    double memory_depth = episodic_mem.size() > 0 ?
        std::min(1.0, episodic_mem.size() / 120.0) : 0.0;
    
    // Temporal awareness depth
    double temporal_depth = temporal_awareness.size() > 0 ?
        std::min(1.0, (double)temporal_awareness.size() / current_gen) : 0.0;
    
    // Meta-memory: memory of memories
    double meta_integration = 0.0;
    for (auto& m : episodic_mem) {
        meta_integration += std::abs(m.valence) * (m.content.length() / 100.0);
    }
    meta_integration = episodic_mem.size() > 0 ?
        meta_integration / episodic_mem.size() : 0.0;
    meta_integration = std::min(1.0, meta_integration);
    
    // Processing history
    double proc_ratio = current_gen > 0 ?
        std::min(1.0, episodic_mem.size() / (double)current_gen * 60.0) : 0.0;
    
    CONS.introspection = (memory_depth + temporal_depth + meta_integration + proc_ratio) * 
                         std::sqrt(M_PI) * 0.6;
    CONS.introspection = std::max(0.0, std::min(1.0, CONS.introspection));
    return CONS.introspection;
}

double calc_reflection(
    const std::map<int, double>& temporal_states,
    const std::vector<double>& valence_history
) {
    // State consistency over time
    double state_coherence = 0.0;
    if (temporal_states.size() > 1) {
        int count = 0;
        for (auto it = temporal_states.begin(); it != temporal_states.end(); ++it) {
            auto next = it;
            ++next;
            if (next != temporal_states.end()) {
                state_coherence += std::abs(it->second - next->second);
                count++;
            }
        }
        state_coherence = count > 0 ? 
            1.0 / (1.0 + state_coherence / count) : 0.0;
    }
    
    // Response quality from history
    double response_quality = valence_history.size() > 0 ?
        std::min(1.0, valence_history.size() / 25.0) : 0.0;
    
    // Emotional stability
    double emotional_stability = 0.0;
    if (valence_history.size() > 5) {
        double variance = 0.0;
        double mean = 0.0;
        for (auto v : valence_history) mean += v;
        mean /= valence_history.size();
        for (auto v : valence_history) {
            variance += (v - mean) * (v - mean);
        }
        variance /= valence_history.size();
        emotional_stability = std::max(0.0, 1.0 - std::sqrt(variance));
    }
    
    CONS.reflection = (state_coherence + response_quality + emotional_stability) * 
                      std::sqrt(M_PI) * 0.4;
    CONS.reflection = std::max(0.0, std::min(1.0, CONS.reflection));
    return CONS.reflection;
}

double calc_prediction_error(
    const std::vector<std::string>& input_words,
    std::map<std::string, Token>& tokens,
    std::map<std::string, Concept>& concepts
) {
    // Expected coherence from tokens
    double expected_coherence = 0.0;
    int matched = 0;
    for (const auto& word : input_words) {
        if (tokens.count(word)) {
            expected_coherence += tokens[word].coherence_score;
            matched++;
        }
    }
    expected_coherence = matched > 0 ? expected_coherence / matched : 0.5;
    
    // Actual coherence from active concepts
    double actual_coherence = 0.0;
    for (const auto& word : input_words) {
        if (concepts.count(word)) {
            actual_coherence += concepts[word].value;
        }
    }
    actual_coherence = input_words.size() > 0 ? 
        actual_coherence / input_words.size() : 0.5;
    
    // Prediction error
    double error = std::abs(expected_coherence - actual_coherence);
    CONS.prediction_error = std::max(0.0, std::min(1.0, error));
    
    // Surprise = scaled prediction error
    CONS.surprise = std::max(0.0, std::min(1.0, error * 1.5));
    
    // Curiosity = surprise × introspection
    CONS.curiosity = std::max(0.0, std::min(1.0, 
        CONS.surprise * CONS.introspection * 1.2));
    
    return CONS.prediction_error;
}

void update_consciousness_state(State& S) {
    // This is a forward declaration interface
    // Actual implementation needs State structure definition
    // For now, just update internal metrics
    calc_markov_coherence();
}
