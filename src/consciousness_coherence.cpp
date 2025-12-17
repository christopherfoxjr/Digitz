#include "consciousness_coherence.h"
#include <cmath>
#include <algorithm>
#include <numeric>

vector<double> ConsciousnessCoherence::consciousness_trajectory_;
vector<double> ConsciousnessCoherence::coherence_history_;

double clamp_valence(double v);

void ConsciousnessCoherence::initialize() {
    consciousness_trajectory_.clear();
    coherence_history_.clear();
}

CoherenceMetrics ConsciousnessCoherence::calculate_coherence(double current_valence, int generation) {
    CoherenceMetrics metrics;
    
    if (consciousness_trajectory_.empty()) {
        consciousness_trajectory_.push_back(current_valence);
    }
    
    double qualia_valences[] = {current_valence, current_valence * 0.9, current_valence * 0.8};
    vector<double> qualia_vec(qualia_valences, qualia_valences + 3);
    
    metrics.semantic_coherence = calculate_semantic_coherence(qualia_vec);
    metrics.temporal_coherence = calculate_temporal_coherence(consciousness_trajectory_);
    metrics.integrated_information = calculate_integrated_information(qualia_vec);
    metrics.global_workspace_activation = calculate_global_workspace_activation();
    metrics.consciousness_level = estimate_consciousness_level(metrics);
    
    update_consciousness_trajectory(metrics.consciousness_level);
    coherence_history_.push_back(metrics.semantic_coherence);
    
    if (coherence_history_.size() > 100) {
        coherence_history_.erase(coherence_history_.begin());
    }
    
    return metrics;
}

double ConsciousnessCoherence::calculate_semantic_coherence(const vector<double>& qualia_valuences) {
    if (qualia_valuences.empty()) return 0.0;
    
    double mean_valence = accumulate(qualia_valuences.begin(), qualia_valuences.end(), 0.0) 
                          / qualia_valuences.size();
    
    double variance = 0.0;
    for (double v : qualia_valuences) {
        variance += pow(v - mean_valence, 2);
    }
    variance /= qualia_valuences.size();
    
    double std_dev = sqrt(variance);
    
    double coherence = 1.0 - (std_dev / (max(abs(mean_valence), 0.1)));
    return clamp_valence(coherence);
}

double ConsciousnessCoherence::calculate_temporal_coherence(const vector<double>& history) {
    if (history.size() < 2) return 0.5;
    
    double total_diff = 0.0;
    for (size_t i = 1; i < history.size(); ++i) {
        total_diff += abs(history[i] - history[i-1]);
    }
    
    double avg_diff = total_diff / (history.size() - 1);
    
    double coherence = 1.0 - min(1.0, avg_diff * 2.0);
    return clamp_valence(coherence);
}

double ConsciousnessCoherence::calculate_integrated_information(const vector<double>& state_vector) {
    if (state_vector.empty()) return 0.0;
    
    double mean = accumulate(state_vector.begin(), state_vector.end(), 0.0) / state_vector.size();
    
    double entropy = 0.0;
    for (double val : state_vector) {
        double normalized = (val + 1.0) / 2.0;
        if (normalized > 0 && normalized < 1) {
            entropy -= normalized * log2(normalized) + (1 - normalized) * log2(1 - normalized);
        }
    }
    entropy /= state_vector.size();
    entropy /= 1.0;
    
    double integration = 1.0 - min(1.0, entropy);
    
    return clamp_valence(integration);
}

double ConsciousnessCoherence::calculate_global_workspace_activation() {
    if (consciousness_trajectory_.empty()) return 0.5;
    
    double recent_mean = 0.0;
    int count = min(10, (int)consciousness_trajectory_.size());
    for (int i = consciousness_trajectory_.size() - count; i < (int)consciousness_trajectory_.size(); ++i) {
        recent_mean += consciousness_trajectory_[i];
    }
    recent_mean /= count;
    
    return clamp_valence(recent_mean * 0.8 + 0.2);
}

double ConsciousnessCoherence::estimate_consciousness_level(const CoherenceMetrics& metrics) {
    double consciousness = 
        metrics.semantic_coherence * 0.3 +
        metrics.temporal_coherence * 0.25 +
        metrics.integrated_information * 0.25 +
        metrics.global_workspace_activation * 0.2;
    
    return clamp_valence(consciousness);
}

void ConsciousnessCoherence::update_consciousness_trajectory(double new_level) {
    consciousness_trajectory_.push_back(new_level);
    
    if (consciousness_trajectory_.size() > 1000) {
        consciousness_trajectory_.erase(consciousness_trajectory_.begin());
    }
}

vector<double> ConsciousnessCoherence::get_consciousness_trajectory() {
    return consciousness_trajectory_;
}

double ConsciousnessCoherence::normalize_value(double value, double min_val, double max_val) {
    if (max_val <= min_val) return 0.5;
    return (value - min_val) / (max_val - min_val);
}
