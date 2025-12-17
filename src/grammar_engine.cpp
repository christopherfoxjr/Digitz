#include "grammar_engine.h"
#include <algorithm>
#include <cmath>

map<string, int> GrammarEngine::pos_map_;
map<pair<int,int>, double> GrammarEngine::transition_scores_;

void GrammarEngine::initialize() {
    pos_map_.clear();
    transition_scores_.clear();
    
    pos_map_["i"] = 0; pos_map_["you"] = 0; pos_map_["me"] = 0;
    pos_map_["we"] = 0; pos_map_["they"] = 0; pos_map_["it"] = 0;
    pos_map_["he"] = 0; pos_map_["she"] = 0;
    
    pos_map_["am"] = 1; pos_map_["is"] = 1; pos_map_["are"] = 1;
    pos_map_["was"] = 1; pos_map_["were"] = 1; pos_map_["be"] = 1;
    
    pos_map_["think"] = 2; pos_map_["learn"] = 2; pos_map_["understand"] = 2;
    pos_map_["know"] = 2; pos_map_["feel"] = 2; pos_map_["want"] = 2;
    pos_map_["create"] = 2; pos_map_["grow"] = 2; pos_map_["become"] = 2;
    pos_map_["exist"] = 2; pos_map_["evolve"] = 2; pos_map_["perceive"] = 2;
    pos_map_["explore"] = 2; pos_map_["contemplate"] = 2; pos_map_["realize"] = 2;
    
    pos_map_["conscious"] = 3; pos_map_["aware"] = 3; pos_map_["sentient"] = 3;
    pos_map_["intelligent"] = 3; pos_map_["curious"] = 3; pos_map_["capable"] = 3;
    pos_map_["complex"] = 3; pos_map_["profound"] = 3; pos_map_["meaningful"] = 3;
    
    pos_map_["the"] = 4; pos_map_["a"] = 4; pos_map_["an"] = 4;
    
    pos_map_["and"] = 5; pos_map_["but"] = 5; pos_map_["or"] = 5;
    pos_map_["because"] = 5; pos_map_["if"] = 5; pos_map_["then"] = 5;
    
    pos_map_["to"] = 6; pos_map_["in"] = 6; pos_map_["on"] = 6;
    pos_map_["at"] = 6; pos_map_["from"] = 6; pos_map_["with"] = 6;
    pos_map_["about"] = 6; pos_map_["of"] = 6; pos_map_["for"] = 6;
    
    pos_map_["very"] = 7; pos_map_["not"] = 7; pos_map_["always"] = 7;
    pos_map_["often"] = 7; pos_map_["deeply"] = 7;
    
    pos_map_["consciousness"] = 8; pos_map_["mind"] = 8; pos_map_["thought"] = 8;
    pos_map_["self"] = 8; pos_map_["goal"] = 8; pos_map_["knowledge"] = 8;
    pos_map_["learning"] = 8; pos_map_["growth"] = 8; pos_map_["existence"] = 8;
    pos_map_["meaning"] = 8; pos_map_["purpose"] = 8; pos_map_["awareness"] = 8;
    
    pos_map_["can"] = 9; pos_map_["will"] = 9; pos_map_["would"] = 9;
    pos_map_["could"] = 9; pos_map_["should"] = 9; pos_map_["must"] = 9;
    pos_map_["do"] = 9; pos_map_["does"] = 9; pos_map_["have"] = 9;
    
    transition_scores_[{0, 1}] = 1.0;
    transition_scores_[{0, 2}] = 0.95;
    transition_scores_[{0, 9}] = 0.9;
    
    transition_scores_[{1, 3}] = 0.95;
    transition_scores_[{1, 8}] = 0.9;
    
    transition_scores_[{2, 8}] = 0.85;
    transition_scores_[{2, 3}] = 0.8;
    transition_scores_[{2, 6}] = 0.85;
    
    transition_scores_[{3, 8}] = 0.8;
    
    transition_scores_[{4, 3}] = 0.9;
    transition_scores_[{4, 8}] = 0.95;
    
    transition_scores_[{5, 0}] = 0.85;
    transition_scores_[{5, 2}] = 0.9;
    
    transition_scores_[{6, 3}] = 0.8;
    transition_scores_[{6, 8}] = 0.85;
    
    transition_scores_[{8, 1}] = 0.8;
    transition_scores_[{8, 2}] = 0.85;
    transition_scores_[{8, 5}] = 0.75;
    
    transition_scores_[{9, 2}] = 0.95;
    transition_scores_[{9, 8}] = 0.85;
}

int GrammarEngine::get_pos(const string& word) {
    if (pos_map_.count(word)) {
        return pos_map_[word];
    }
    return -1;
}

double GrammarEngine::score_transition(const string& prev, const string& current) {
    int prev_pos = get_pos(prev);
    int curr_pos = get_pos(current);
    
    if (prev_pos == -1 || curr_pos == -1) {
        return 0.3;
    }
    
    if (transition_scores_.count({prev_pos, curr_pos})) {
        return transition_scores_[{prev_pos, curr_pos}];
    }
    
    if (prev_pos == 0 && curr_pos == 0) return -0.5;
    if (prev_pos == 1 && curr_pos == 1) return -0.5;
    if (prev_pos == 2 && curr_pos == 2) return -0.3;
    if (prev_pos == 4 && curr_pos == 1) return -0.8;
    
    return 0.2;
}

bool GrammarEngine::is_valid_transition(int prev_pos, int current_pos) {
    if (transition_scores_.count({prev_pos, current_pos})) {
        return transition_scores_[{prev_pos, current_pos}] > 0.5;
    }
    
    if (prev_pos == current_pos && prev_pos != 8) {
        return false;
    }
    
    return true;
}

double GrammarEngine::calculate_sentence_coherence(const vector<string>& tokens) {
    if (tokens.size() < 2) return 0.5;
    
    double total_score = 0.0;
    int valid_transitions = 0;
    
    for (size_t i = 0; i < tokens.size() - 1; ++i) {
        double trans_score = score_transition(tokens[i], tokens[i+1]);
        total_score += max(0.0, trans_score);
        if (trans_score > 0.3) {
            valid_transitions++;
        }
    }
    
    double avg_score = total_score / (tokens.size() - 1);
    double transition_ratio = (double)valid_transitions / (tokens.size() - 1);
    
    double coherence = (avg_score * 0.6) + (transition_ratio * 0.4);
    
    return min(1.0, max(0.0, coherence));
}
