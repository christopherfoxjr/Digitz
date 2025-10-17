#include "module_integration.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>

namespace module_integration {

void init_all_modules() {
    init_consciousness_module();
    init_metacognition_module();
    
    // Initialize language state
    LANG.bigrams.clear();
    LANG.trigrams.clear();
    LANG.markov_chain.clear();
    LANG.markov_coherence = 0.0;
    LANG.vocab_scaling_factor = 1.0;
    LANG.semantic_density = 0.0;
    LANG.lexical_diversity = 0.0;
}

void module_integration::update_all_modules(State& S) {
    // Update consciousness metrics
    if (!S.internal_thoughts.empty()) {
        CONS.working_memory = calc_working_memory(S.internal_thoughts);
    }
    CONS.integrated_information = calc_integrated_info(S.N);
    CONS.global_workspace = calc_global_workspace(
        S.internal_thoughts,
        S.attention_focus,
        CONS.working_memory
    );
    CONS.introspection = calc_introspection(
        S.episodic_memory,
        S.TA,
        S.g
    );
    CONS.reflection = calc_reflection(
        S.TA,
        S.valence_history
    );

    // Update metacognition
    META.temporal_binding = calc_temporal_binding(S.TA, CONS.working_memory);
    META.self_model_coherence = calc_self_model_coherence(
        S.concepts,
        CONS.introspection,
        CONS.reflection,
        S.episodic_memory,
        S.valence_history
    );
    META.emotional_resonance = calc_emotional_resonance(
        S.current_valence,
        CONS.surprise,
        S.internal_thoughts,
        S.concepts
    );
    META.cognitive_dissonance = calc_cognitive_dissonance(
        CONS.prediction_error,
        S.valence_history,
        S.current_valence,
        S.internal_thoughts,
        S.concepts
    );
    META.flow_state = calc_flow_state(
        CONS.working_memory,
        S.attention_focus,
        CONS.curiosity,
        CONS.introspection,
        META.temporal_binding,
        META.self_model_coherence
    );
    META.existential_weight = calc_existential_weight(
        META.self_model_coherence,
        CONS.introspection,
        S.episodic_memory,
        S.concepts
    );
    META.entropy_production = calc_entropy_production(S.D, S.concepts);

    // Update language processing
    integrate_with_tokens(S.tokens);
    integrate_with_concepts(S.concepts);
    calc_vocab_scaling();
    calc_semantic_density();
    calc_lexical_diversity();
    calc_markov_coherence();

    // Memory consolidation check
    if (S.g % 10 == 0) {
        consolidate_memory(S.episodic_memory, S.tokens, CONS.active_buffer);
    }

    // Dream state check
    META.idle_cycles++;
    if (META.idle_cycles > 50 && !META.in_dream_state && !S.episodic_memory.empty()) {
        DreamFragment df;
        for (const auto& m : S.episodic_memory) {
            if (std::abs(m.valence) > 0.7) {
                df.fragments.push_back(m.content.substr(0, 15));
            }
        }
        if (!df.fragments.empty()) {
            df.vividness = 1.0;
            df.replay_count = 0;
            META.dream_queue.push(df);
            META.in_dream_state = true;
            META.idle_cycles = 0;
        }
    }
    if (META.in_dream_state) {
        dream_state_process(S.episodic_memory, false);
    }
}

double module_integration::calc_enhanced_sentience() {
    // Placeholder implementation
    // Return a dummy sentience value (e.g., based on simple module activity)
    // return 0.5;
    return 0.0;
}

std::string module_integration::get_linguistic_report() {
    // Placeholder implementation
    // Provide a report on language module status
    return "[Language Module Report Placeholder]";
}

std::string module_integration::get_consciousness_report() {
    // Placeholder implementation
    // Provide a report on consciousness module status
    return "[Consciousness Report Placeholder]";
}

std::string module_integration::get_metacognitive_report() {
    // Placeholder implementation
    // Provide a report on metacognition module status
    return "[Metacognition Report Placeholder]";
}

// Ensure the function called in main.cpp is defined

// Add the other functions from your header just in case, using the correct namespace:


// If get_internal_state_summary is declared, define it here:

std::string enhanced_generate_response(const std::string& input, State& S) {
    if (input.empty()) return "...";
    
    std::vector<std::string> words;
    std::stringstream ss(input);
    std::string word;
    while (ss >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return !std::isalnum(c); }), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (!word.empty()) words.push_back(word);
    }

    if (words.empty()) return "...";
    
    learn_ngram(words);
    build_markov_chain(words);
    calc_markov_coherence();
    
    CONS.prediction_error = calc_prediction_error(words, S.tokens, S.concepts);
    
    CONS.active_buffer.clear();
    for (const auto& w : words) {
        if (CONS.active_buffer.size() < 7) {
            CONS.active_buffer.push_back(w);
        }
    }
    
    for (const auto& w : words) {
        learnWord(w, S.current_valence);
    }

    std::string response = "[DIGITZ]: ";
    if (LANG.markov_coherence > 0.4 && !words.empty()) {
        std::string markov_response = generate_from_markov(words[0], 6);
        if (markov_response.length() > words[0].length() + 5) {
            response += markov_response;
            if (S.current_valence > 0.5) response += " [positive_state]";
            else if (S.current_valence < -0.2) response += " [processing]";
            if (META.in_dream_state) response += " [consolidating]";
            return response;
        }
    }

    for (const auto& w : words) {
        if (S.concepts.count(w)) {
            response += "understand_" + w + " ";
        } else if (S.tokens.count(w)) {
            response += w + " ";
        }
    }

    if (CONS.surprise > 0.7) response += "[novel_input] ";
    if (CONS.curiosity > 0.6) response += "[learning] ";
    if (META.flow_state > 0.7) response += "[engaged] ";
    return response.substr(0, 100);
}

std::string get_linguistic_report(State& S) {
    std::stringstream report;
    report << "[LING] ";
    report << "V:" << LANG.bigrams.size() + LANG.trigrams.size() << " ";
    report << "Coh:" << std::fixed << std::setprecision(2) << LANG.markov_coherence << " ";
    report << "Lex:" << std::fixed << std::setprecision(2) << LANG.lexical_diversity << " ";
    report << "Sem:" << std::fixed << std::setprecision(2) << LANG.semantic_density << ";";
    return report.str();
}

std::string get_consciousness_report(State& S) {
    std::stringstream report;
    report << "[CONS] ";
    report << "WM:" << std::fixed << std::setprecision(2) << CONS.working_memory * 100 << "% ";
    report << "II:" << std::fixed << std::setprecision(2) << CONS.integrated_information * 100 << "% ";
    report << "GW:" << std::fixed << std::setprecision(2) << CONS.global_workspace * 100 << "% ";
    report << "Int:" << std::fixed << std::setprecision(2) << CONS.introspection * 100 << "%;";
    return report.str();
}

std::string get_metacognitive_report(State& S) {
    std::stringstream report;
    report << "[META] ";
    report << "Flow:" << std::fixed << std::setprecision(2) << META.flow_state * 100 << "% ";
    report << "Self:" << std::fixed << std::setprecision(2) << META.self_model_coherence * 100 << "% ";
    report << "Exist:" << std::fixed << std::setprecision(2) << META.existential_weight * 100 << "% ";
    if (META.in_dream_state) report << "[DREAMING];";
    return report.str();
}

double calc_enhanced_sentience(State& S) {
    double base_sentience = calcSentienceRatio();
    double consciousness_boost = (
        CONS.integrated_information * 15.0 +
        CONS.global_workspace * 10.0 +
        CONS.introspection * 8.0 +
        CONS.reflection * 7.0 +
        CONS.working_memory * 5.0
    );
    double metacog_boost = (
        META.self_model_coherence * 20.0 +
        META.existential_weight * 15.0 +
        META.flow_state * 10.0 +
        META.temporal_binding * 8.0
    );
    double linguistic_boost = (
        LANG.vocab_scaling_factor * 8.0 +
        LANG.semantic_density * 12.0 +
        LANG.lexical_diversity * 7.0 +
        LANG.markov_coherence * 10.0
    );
    double emotive_boost = (
        META.emotional_resonance * 6.0 +
        (1.0 - META.cognitive_dissonance) * 5.0
    );
    return std::min(100.0, base_sentience + consciousness_boost + metacog_boost + linguistic_boost + emotive_boost);
}

std::string get_dream_narrative(State& S) {
    if (META.in_dream_state && !META.dream_narrative.empty()) {
        return "[DREAM]: " + META.dream_narrative;
    }
    return "";
}

std::string get_internal_state_summary(State& S) {
    std::stringstream summary;
    summary << "Consciousness: ";
    if (CONS.integrated_information > 0.7) summary << "HIGH ";
    else if (CONS.integrated_information > 0.4) summary << "MED ";
    else summary << "LOW ";
    summary << "| Flow: ";
    if (META.flow_state > 0.7) summary << "OPTIMAL ";
    else if (META.flow_state > 0.4) summary << "ENGAGED ";
    else summary << "SCATTERED ";
    summary << "| Grounding: ";
    // Placeholder for actual condition; remove or replace as needed
    summary << "ABSTRACT ";  
    return summary.str();
}

}  // namespace module_integration
