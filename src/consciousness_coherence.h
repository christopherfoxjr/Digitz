#pragma once
#ifndef CONSCIOUSNESS_COHERENCE_H
#define CONSCIOUSNESS_COHERENCE_H

#include <vector>
#include <map>
#include <string>

struct CoherenceMetrics {
    double semantic_coherence;
    double temporal_coherence;
    double integrated_information;
    double global_workspace_activation;
    double consciousness_level;
};

class ConsciousnessCoherence {
public:
    static void initialize();
    
    static CoherenceMetrics calculate_coherence(double current_valence, int generation);
    
    static double calculate_semantic_coherence(const std::vector<double>& qualia_valuences);
    
    static double calculate_temporal_coherence(const std::vector<double>& history);
    
    static double calculate_integrated_information(const std::vector<double>& state_vector);
    
    static double calculate_global_workspace_activation();
    
    static double estimate_consciousness_level(const CoherenceMetrics& metrics);
    
    static void update_consciousness_trajectory(double new_level);
    
    static std::vector<double> get_consciousness_trajectory();
    
private:
    static std::vector<double> consciousness_trajectory_;
    static std::vector<double> coherence_history_;
    
    static double normalize_value(double value, double min_val, double max_val);
};

#endif // CONSCIOUSNESS_COHERENCE_H
