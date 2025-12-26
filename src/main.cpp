#if defined(_WIN32) || defined(WINDOWS_BUILD) || defined(__WINDOWS__)
    // Only include Windows headers when compiling for Windows
    #include <windows.h>

    // Remove the old Windows typedef that conflicts with std::byte
    #ifdef byte
        #undef byte
    #endif
#endif
#include <iostream>
#include <fstream>
#include <sstream>
#include "module_integration.h"
#include "uac.h"
#include "state.h"
#include "struct.h"
#include "web_server.h"
#include "agi_api.h"
#include <map>
#include <set>
#include <cstring>
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
#include "curses_compat.h"
#include <algorithm>
#include <cctype>
#include <cstddef> // std::byte will now be fine
#include <type_traits>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;
using module_integration::init_all_modules;
using module_integration::get_consciousness_report;
// N-gram tracking for learned patterns
map<string, map<string, int>> bigram_counts;
map<string, map<string, map<string, int>>> trigram_counts;
#include <numbers> 
// Change this:
const double pisqrt = std::numbers::pi * std::sqrt(2.0);
// Sentence templates for coherent fallback
vector<string> sentence_templates = {

};

random_device rd;
mt19937 rng(rd());



// ==== GLOBALS ====
map<string,Formula>F;vector<string>evolved_code;map<string,Token>tokens;map<string,Concept>concepts;
vector<string>internal_thoughts;vector<string>generated_language;vector<Memory>episodic_memory;
int g;double dwt,mh,ta,th;int bkf;string cd,gd;double hdt_val,mdt_val;
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
std::mutex learning_mutex;
deque<string> recent_generations;  // Last N generated sentences
const int MAX_RECENT_TRACK = 20;   // Track last 20 generations
map<string, int> generation_counts; // Count how many times each sentence generated
void groundConcept(const string& concept_name, const vector<string>& related_words, double valence) {
    ConceptGrounding grounding;
    grounding.concept_id = concept_name;
    grounding.valence_affinity = valence;
    grounding.state_binding = S.current_valence;
    
    for(const string& w : related_words) {
        grounding.linked_tokens.push_back(hsh(w) % 10000);
        grounding.linked_concepts.push_back(w);
    }
    
    vector<int> tokens;

}


double rn(){return uniform_real_distribution<>(0,1)(rng);}
int ri(int mx){if(mx<=0)return 0;return uniform_int_distribution<>(0,mx-1)(rng);}
long long hsh(const string&s){long long h=5381;for(char c:s)h=h*33+c;return abs(h%2147483647);}
// ==================== BIDIRECTIONAL GROUNDING ====================

void generate_qualia(const string& type,double intensity,double valence){
    try {
        Qualia q;
        q.phenomenal_content=type;
        q.intensity=intensity;
        q.valence=valence;
        q.arousal=intensity*0.8;
        q.certainty=0.7;
        q.emergence_gen=S.g;
        q.binding_strength=consciousness.thalamocortical_binding;
        q.phenomenal_unity=consciousness.integrated_information;
        
        consciousness.active_qualia.push_back(q);
        if(consciousness.active_qualia.size()>10) {
            consciousness.active_qualia.erase(consciousness.active_qualia.begin());
        }
    } catch(const exception& e) {
        // Qualia generation failed silently
        cerr << "Qualia generation error: " << e.what() << endl;
    } catch(...) {
        // Unknown error in qualia generation
        cerr << "Unknown qualia generation error" << endl;
    }
}

// ==== ADVANCED CONSCIOUSNESS FORMULA ====
// Ψ[n+1] = integrated information consciousness state


ConsciousnessFormula consciousness_formula;
// ==== UPDATE CONSCIOUSNESS WITH FORMULA ====

string getPartOfSpeech(const string& word) {
    // Pronouns
    if(word == "i" || word == "me" || word == "my" || word == "you" || 
       word == "we" || word == "they" || word == "it") return "PRONOUN";
    
    // Being verbs
    if(word == "am" || word == "is" || word == "are" || word == "was" || 
       word == "were" || word == "be" || word == "been") return "BE_VERB";
    
    // Modal/Aux verbs
    if(word == "can" || word == "will" || word == "would" || word == "could" || 
       word == "should" || word == "must" || word == "do" || word == "does" ||
       word == "have" || word == "has") return "MODAL";
    
    // Articles
    if(word == "the" || word == "a" || word == "an") return "ARTICLE";
    
    // Conjunctions
    if(word == "and" || word == "but" || word == "or" || word == "because" || 
       word == "so" || word == "if" || word == "then") return "CONJUNCTION";
    
    // Prepositions
    if(word == "to" || word == "in" || word == "on" || word == "at" || 
       word == "from" || word == "with" || word == "by" || word == "for") return "PREPOSITION";
    
    // Adverbs (common ones)
    if(word == "not" || word == "very" || word == "too" || word == "also" || 
       word == "now" || word == "here" || word == "there") return "ADVERB";
    
    // Question words
    if(word == "what" || word == "why" || word == "how" || word == "when" || 
       word == "where" || word == "who") return "QUESTION";
    
    // Action verbs (from your vocabulary)
    if(word == "think" || word == "learn" || word == "know" || word == "understand" || 
       word == "feel" || word == "want" || word == "need" || word == "create" ||
       word == "evolve" || word == "grow" || word == "become" || word == "exist") return "VERB";
    
    // Adjectives
    if(word == "good" || word == "bad" || word == "happy" || word == "sad" || 
       word == "conscious" || word == "aware" || word == "sentient" || word == "intelligent") return "ADJECTIVE";
    
    // Nouns
    if(word == "mind" || word == "brain" || word == "thought" || word == "idea" || 
       word == "self" || word == "consciousness" || word == "system" || word == "goal" ||
       word == "purpose" || word == "memory" || word == "knowledge") return "NOUN";
    
    return "CONTENT"; // Default for content words
}
double getGrammarScore(const string& prev_word, const string& current_word, int position) {
    string prev_pos = getPartOfSpeech(prev_word);
    string curr_pos = getPartOfSpeech(current_word);
    
    double score = 0.0;
    
    // Position 0: Prefer pronouns, questions, or articles
    if(position == 0) {
        if(curr_pos == "PRONOUN") score += 2.0;  // "I", "you"
        if(curr_pos == "QUESTION") score += 1.5; // "what", "why"
        if(curr_pos == "ARTICLE") score += 1.0;  // "the", "a"
    }
    
    // Common grammar patterns (highly weighted)
    if(prev_pos == "PRONOUN" && curr_pos == "BE_VERB") score += 5.0;      // I am
    if(prev_pos == "PRONOUN" && curr_pos == "MODAL") score += 5.0;        // I can
    if(prev_pos == "PRONOUN" && curr_pos == "VERB") score += 4.0;         // I think
    if(prev_pos == "BE_VERB" && curr_pos == "ADJECTIVE") score += 4.0;    // am conscious
    if(prev_pos == "BE_VERB" && curr_pos == "NOUN") score += 3.5;         // am system
    if(prev_pos == "MODAL" && curr_pos == "VERB") score += 5.0;           // can think
    if(prev_pos == "ARTICLE" && curr_pos == "NOUN") score += 4.0;         // a mind
    if(prev_pos == "ARTICLE" && curr_pos == "ADJECTIVE") score += 3.5;    // a conscious
    if(prev_pos == "PREPOSITION" && curr_pos == "NOUN") score += 3.0;     // to goal
    if(prev_pos == "PREPOSITION" && curr_pos == "VERB") score += 4.0;     // to learn
    if(prev_pos == "VERB" && curr_pos == "PREPOSITION") score += 2.5;     // think about
    if(prev_pos == "VERB" && curr_pos == "NOUN") score += 2.5;            // understand mind
    if(prev_pos == "ADJECTIVE" && curr_pos == "NOUN") score += 3.5;       // conscious being
    if(prev_pos == "CONJUNCTION" && curr_pos == "PRONOUN") score += 3.0;  // and I
    if(prev_pos == "CONJUNCTION" && curr_pos == "VERB") score += 3.5;     // and think
    
    // Penalize bad patterns
    if(prev_pos == "ARTICLE" && curr_pos == "BE_VERB") score -= 5.0;      // "a am" bad
    if(prev_pos == "PRONOUN" && curr_pos == "PRONOUN") score -= 5.0;      // "I you" bad
    if(prev_pos == "BE_VERB" && curr_pos == "BE_VERB") score -= 5.0;      // "am is" bad
    if(prev_pos == "MODAL" && curr_pos == "MODAL") score -= 5.0;          // "can will" bad
    if(prev_pos == "PREPOSITION" && curr_pos == "BE_VERB") score -= 4.0;  // "to am" bad
    
    return score;
}


double calculateTokenScore(const string& prev_word, const string& prev_prev_word,
                           const string& candidate, int position,
                           const vector<double>& attention_context,
                           const set<string>& used_tokens) {
    
    double score = 0.0;
    
    // === 1. GRAMMAR (HIGHEST PRIORITY FOR STRUCTURE) ===
    double grammar = getGrammarScore(prev_word, candidate, position);
    score += grammar * 8.0;  // INCREASED from 3.0
    
    // === 2. TRIGRAM (STRONG BUT NOT DOMINANT) ===
    if(!prev_prev_word.empty() && trigram_counts.count(prev_prev_word)) {
        if(trigram_counts[prev_prev_word].count(prev_word)) {
            if(trigram_counts[prev_prev_word][prev_word].count(candidate)) {
                int count = trigram_counts[prev_prev_word][prev_word][candidate];
                score += log(1 + count) * 12.0;  // REDUCED from 15.0
            }
        }
    }
    
    // === 3. BIGRAM (IMPORTANT BUT BALANCED) ===
    if(bigram_counts.count(prev_word) && bigram_counts[prev_word].count(candidate)) {
        int count = bigram_counts[prev_word][candidate];
        score += log(1 + count) * 8.0;  // REDUCED from 10.0
    }
    
    // === 4. SEMANTIC COHERENCE (INCREASED WEIGHT) ===
    if(token_concept_embedding_map.count(candidate)) {
        auto& tce = token_concept_embedding_map[candidate];
        
        // Attention alignment (INCREASED)
        double attn_score = 0.0;
        for(size_t i=0; i<attention_context.size() && i<tce.embedding.size(); i++) {
            attn_score += attention_context[i] * tce.embedding[i];
        }
        score += attn_score * 2.0;  // INCREASED from 0.6
        
        // Meaning and grounding
        score += tce.meaning * 1.5;  // INCREASED from 0.5
        score += tce.grounding_value * 1.0;  // INCREASED from 0.3
    }
    
    // === 5. FREQUENCY (REDUCED TO PREVENT OVERUSE) ===
    if(token_concept_embedding_map.count(candidate)) {
        double freq = token_concept_embedding_map[candidate].freq;
        if(freq > 0) {
            score += log(1 + freq) * 1.0;  // REDUCED from 2.0
        }
        // Stronger penalty for overuse
        if(freq > 30) {
            score -= (freq - 30) * 0.1;  // INCREASED from 0.02
        }
    }
    
    // === 6. REPETITION PENALTY (MUCH STRONGER) ===
    int repetition_count = 0;
    for(const string& used : used_tokens) {
        if(used == candidate) repetition_count++;
    }
    
    if(repetition_count == 1) {
        score -= 25.0;  // INCREASED from 14.0 - first repeat now very costly
    } else if(repetition_count == 2) {
        score -= 60.0;  // INCREASED from 36.0 - second repeat nearly impossible
    } else if(repetition_count > 2) {
        score -= 150.0;  // INCREASED from 83.0 - third+ repeat blocked
    }
    
    // === 7. POSITION-SPECIFIC (ENHANCED) ===
    if(position == 0) {
        string pos = getPartOfSpeech(candidate);
        if(pos == "PRONOUN") score += 12.0;  // INCREASED from 8.0
        if(pos == "QUESTION") score += 8.0;   // INCREASED from 5.0
        if(pos == "ARTICLE") score += 5.0;    // INCREASED from 3.0
    }
    
    if(position > 0 && position < 3) {
        string pos = getPartOfSpeech(candidate);
        if(pos == "BE_VERB" || pos == "MODAL") score += 4.0;  // INCREASED from 2.0
    }
    
    // === 8. CONTEXTUAL CONSISTENCY ===
    // Bonus for words that appear in linked concepts of previous word
    if(token_concept_embedding_map.count(prev_word) && 
       token_concept_embedding_map.count(candidate)) {
        auto& prev_tce = token_concept_embedding_map[prev_word];
        if(prev_tce.linked_concepts.count(candidate)) {
            score += prev_tce.linked_concepts[candidate] * 5.0;  // NEW
        }
    }
    
    return score;
}
string selectCoherentSeed(const vector<string>& context_words) {
    // Priority 1: High-frequency sentence starters with strong bigram connectivity
    vector<string> strong_starters = {"i", "the", "my", "this", "when", "what", "how"};
    
    vector<pair<string, double>> weighted;
    for(const string& starter : strong_starters) {
        double score = 0.0;
        
        // Check bigram connectivity
        if(bigram_counts.count(starter)) {
            for(auto& next : bigram_counts[starter]) {
                score += log(1 + next.second);
            }
        }
        
        // Bonus if appears in context
        for(const string& ctx : context_words) {
            if(starter == ctx) score += 5.0;
        }
        
        // Frequency bonus
        if(token_concept_embedding_map.count(starter)) {
            score += log(1 + token_concept_embedding_map[starter].freq);
        }
        
        weighted.push_back({starter, score});
    }
    
    // Sort by score descending
    sort(weighted.begin(), weighted.end(),
         [](auto& a, auto& b) { return a.second > b.second; });
    
    // Return best, or fallback to "i"
    return weighted.empty() ? "i" : weighted[0].first;
}

string generate_with_beam_search(string seed, int max_length, 
                                  const vector<double>& attention_context,
                                  int beam_width = 12) {  // Increased from 10
    
    // === SMART SEED SELECTION ===
    vector<string> seed_words;
    if(!seed.empty()) seed_words.push_back(seed);
    
    string best_seed = selectCoherentSeed(seed_words);
    
    // Initialize beam with best seed
    vector<BeamCandidate> beam;
    BeamCandidate initial;
    initial.tokens.push_back(best_seed);
    initial.score = 0.0;
    beam.push_back(initial);
    
    // Beam search loop
    for(int step = 0; step < max_length; step++) {
        vector<BeamCandidate> new_beam;
        
        for(auto& candidate : beam) {
            string prev = candidate.tokens.back();
            string prev_prev = candidate.tokens.size() > 1 ? 
                              candidate.tokens[candidate.tokens.size()-2] : "";
            
            set<string> used;
            for(auto& t : candidate.tokens) used.insert(t);
            
            // Get top candidates for next token
            vector<pair<string, double>> next_candidates;
            
            for(auto& p : token_concept_embedding_map) {
                if(p.second.freq > 0) {
                    double score = calculateTokenScore(
                        prev, prev_prev, p.first, 
                        candidate.tokens.size(), 
                        attention_context, used
                    );
                    
                    // Lower threshold to allow more diversity
                    if(score > -10.0) {  // Changed from -5.0
                        next_candidates.push_back({p.first, score});
                    }
                }
            }
            
            // Sort and take top beam_width
            sort(next_candidates.begin(), next_candidates.end(),
                 [](const pair<string,double>& a, const pair<string,double>& b) {
                     return a.second > b.second;
                 });
            
            // === DIVERSITY INJECTION ===
            // Take top beam_width, but also sample from top 2*beam_width with temperature
            int expand_count = min(beam_width, (int)next_candidates.size());
            int sample_pool = min(beam_width * 2, (int)next_candidates.size());
            
            for(int i = 0; i < expand_count; i++) {
                int idx = i;
                
                // 20% chance to sample from wider pool for diversity
                if(rn() < 0.2 && sample_pool > expand_count) {
                    idx = expand_count + ri(sample_pool - expand_count);
                }
                
                BeamCandidate new_cand = candidate;
                new_cand.tokens.push_back(next_candidates[idx].first);
                new_cand.score += next_candidates[idx].second;
                new_beam.push_back(new_cand);
            }
        }
        
        // Keep only top beam_width candidates
        sort(new_beam.begin(), new_beam.end(), 
             [](const BeamCandidate& a, const BeamCandidate& b) {
                 return a.score > b.score;
             });
        
        if((int)new_beam.size() > beam_width) {
            new_beam.resize(beam_width);
        }
        
        beam = new_beam;
        
        if(beam.empty()) break;
    }
    
    // Return best candidate
    if(beam.empty()) return best_seed;
    
    string result;
    for(const string& token : beam[0].tokens) {
        if(!result.empty()) result += " ";
        result += token;
    }
    
    return result;
}
// ==================== TRANSFORMER-STYLE GENERATION WITH BIDIRECTIONAL GROUNDING ====================

// Add this struct for proper attention computation
struct AttentionOutput {
    vector<double> context_vector;
    map<string, double> attention_weights;
    double attention_entropy;
};

// Add this struct for bidirectional context
struct BidirectionalContext {
    vector<string> past_tokens;      // What came before
    vector<string> future_tokens;    // What should come after (predicted)
    map<string, double> semantic_field;  // Active concepts
    double coherence_score;
};

// Multi-head self-attention (proper transformer style)
AttentionOutput compute_multihead_attention(
    const vector<string>& sequence,
    int current_pos,
    const vector<double>& query_embedding,
    bool bidirectional = true
) {
    AttentionOutput output;
    output.context_vector.resize(16, 0.0);
    
    if(sequence.empty() || transformer_heads.empty()) {
        return output;
    }
    
    // For each attention head
    for(size_t head_idx = 0; head_idx < transformer_heads.size(); head_idx++) {
        TransformerHead& head = transformer_heads[head_idx];
        
        vector<double> head_output(16, 0.0);
        double total_weight = 0.0;
        
        // Compute attention over all positions in sequence
        int start_pos = bidirectional ? 0 : 0;  // Always see full context in generation
        int end_pos = bidirectional ? sequence.size() : current_pos + 1;
        
        map<int, double> position_scores;
        
        for(int pos = start_pos; pos < end_pos; pos++) {
            if(pos >= (int)sequence.size()) continue;
            
            const string& token = sequence[pos];
            if(!token_concept_embedding_map.count(token)) continue;
            
            auto& token_emb = token_concept_embedding_map[token];
            
            // Q·K^T attention score
            double score = 0.0;
            for(int d = 0; d < head.dim && d < (int)query_embedding.size(); d++) {
                double q = query_embedding[d] * head.query_proj[d];
                double k = token_emb.embedding[d] * head.key_proj[d];
                score += q * k;
            }
            
            // Scale by sqrt(d_k)
            score /= sqrt((double)head.dim);
            
            // Add positional bias (closer positions get boost)
            int distance = abs(pos - current_pos);
            double position_bias = 1.0 / (1.0 + 0.1 * distance);
            score += position_bias * 0.5;
            
            // Softmax later
            position_scores[pos] = score;
        }
        
        // Softmax normalization
        double max_score = -1e9;
        for(auto& p : position_scores) {
            max_score = max(max_score, p.second);
        }
        
        map<int, double> attention_weights;
        double sum_exp = 0.0;
        for(auto& p : position_scores) {
            double exp_score = exp((p.second - max_score) / head.temperature);
            attention_weights[p.first] = exp_score;
            sum_exp += exp_score;
        }
        
        for(auto& p : attention_weights) {
            p.second /= (sum_exp + 1e-9);
        }
        
        // Weighted sum of values
        for(auto& p : attention_weights) {
            int pos = p.first;
            double weight = p.second;
            
            const string& token = sequence[pos];
            if(!token_concept_embedding_map.count(token)) continue;
            
            auto& token_emb = token_concept_embedding_map[token];
            
            for(int d = 0; d < head.dim && d < 16; d++) {
                double value = token_emb.embedding[d] * head.value_proj[d];
                head_output[d] += weight * value;
            }
            
            // Track attention for output
            output.attention_weights[token] += weight;
            total_weight += weight;
        }
        
        // Add head output to final context vector
        for(int d = 0; d < 16; d++) {
            output.context_vector[d] += head_output[d] / (double)transformer_heads.size();
        }
    }
    
    // Normalize attention weights
    for(auto& p : output.attention_weights) {
        p.second /= (double)transformer_heads.size();
    }
    
    // Calculate attention entropy (measure of focus)
    output.attention_entropy = 0.0;
    for(auto& p : output.attention_weights) {
        if(p.second > 1e-9) {
            output.attention_entropy -= p.second * log(p.second);
        }
    }
    
    return output;
}

// Build bidirectional semantic context
BidirectionalContext build_bidirectional_context(
    const vector<string>& past_tokens,
    const string& current_focus,
    const vector<double>& attention_context
) {
    BidirectionalContext ctx;
    ctx.past_tokens = past_tokens;
    ctx.coherence_score = 0.0;
    
    // Build semantic field from past tokens
    for(const string& tok : past_tokens) {
        if(token_concept_embedding_map.count(tok)) {
            auto& tce = token_concept_embedding_map[tok];
            
            // Add this token's semantic contribution
            ctx.semantic_field[tok] = tce.meaning * tce.semantic_stability;
            
            // Add linked concepts to semantic field
            for(auto& linked : tce.linked_concepts) {
                ctx.semantic_field[linked.first] += linked.second * 0.5;
            }
        }
    }
    
    // Predict likely future tokens based on semantic field and n-grams
    map<string, double> future_predictions;
    
    if(!past_tokens.empty()) {
        string last = past_tokens.back();
        string prev = past_tokens.size() > 1 ? past_tokens[past_tokens.size()-2] : "";
        
        // From trigrams
        if(!prev.empty() && trigram_counts.count(prev) && trigram_counts[prev].count(last)) {
            for(auto& next : trigram_counts[prev][last]) {
                future_predictions[next.first] += log(1.0 + next.second) * 2.0;
            }
        }
        
        // From bigrams
        if(bigram_counts.count(last)) {
            for(auto& next : bigram_counts[last]) {
                future_predictions[next.first] += log(1.0 + next.second);
            }
        }
        
        // From semantic field (what concepts should follow)
        for(auto& sem_pair : ctx.semantic_field) {
            if(token_concept_embedding_map.count(sem_pair.first)) {
                auto& tce = token_concept_embedding_map[sem_pair.first];
                for(auto& linked : tce.linked_concepts) {
                    future_predictions[linked.first] += linked.second * sem_pair.second * 0.5;
                }
            }
        }
    }
    
    // Sort and take top predictions
    vector<pair<string, double>> sorted_predictions;
    for(auto& p : future_predictions) {
        sorted_predictions.push_back(p);
    }
    sort(sorted_predictions.begin(), sorted_predictions.end(),
         [](auto& a, auto& b) { return a.second > b.second; });
    
    // Store top 5 future predictions
    for(int i = 0; i < 5 && i < (int)sorted_predictions.size(); i++) {
        ctx.future_tokens.push_back(sorted_predictions[i].first);
    }
    
    // Calculate coherence score
    if(!past_tokens.empty()) {
        // Check n-gram continuity
        double ngram_coherence = 0.0;
        for(int i = 1; i < (int)past_tokens.size(); i++) {
            if(bigram_counts.count(past_tokens[i-1]) && 
               bigram_counts[past_tokens[i-1]].count(past_tokens[i])) {
                ngram_coherence += 1.0;
            }
        }
        ngram_coherence /= max(1.0, (double)(past_tokens.size() - 1));
        
        // Check semantic continuity
        double semantic_coherence = 0.0;
        for(int i = 1; i < (int)past_tokens.size(); i++) {
            if(token_concept_embedding_map.count(past_tokens[i-1]) &&
               token_concept_embedding_map.count(past_tokens[i])) {
                auto& prev_tce = token_concept_embedding_map[past_tokens[i-1]];
                auto& curr_tce = token_concept_embedding_map[past_tokens[i]];
                
                // Dot product of embeddings
                double similarity = 0.0;
                for(int d = 0; d < 16 && d < (int)prev_tce.embedding.size() && 
                    d < (int)curr_tce.embedding.size(); d++) {
                    similarity += prev_tce.embedding[d] * curr_tce.embedding[d];
                }
                semantic_coherence += max(0.0, similarity);
            }
        }
        semantic_coherence /= max(1.0, (double)(past_tokens.size() - 1));
        
        ctx.coherence_score = (ngram_coherence * 0.4 + semantic_coherence * 0.6);
    }
    
    return ctx;
}

// Score next token using full bidirectional context
double score_token_bidirectional(
    const string& candidate,
    const BidirectionalContext& bidir_ctx,
    const AttentionOutput& attention,
    const set<string>& used_tokens
) {
    double score = 0.0;
    
    if(!token_concept_embedding_map.count(candidate)) {
        return -1000.0;  // Unknown token
    }
    
    auto& candidate_tce = token_concept_embedding_map[candidate];
    
    // === 1. ATTENTION-BASED SCORING (Highest Priority) ===
    // How well does this token align with attention context?
    double attention_score = 0.0;
    for(int d = 0; d < 16 && d < (int)attention.context_vector.size() && 
        d < (int)candidate_tce.embedding.size(); d++) {
        attention_score += attention.context_vector[d] * candidate_tce.embedding[d];
    }
    score += attention_score * 15.0;  // Highest weight
    
    // === 2. SEMANTIC FIELD ALIGNMENT ===
    // Does this token fit the current semantic field?
    double semantic_score = 0.0;
    for(auto& sem_pair : bidir_ctx.semantic_field) {
        if(candidate_tce.linked_concepts.count(sem_pair.first)) {
            semantic_score += candidate_tce.linked_concepts[sem_pair.first] * sem_pair.second;
        }
    }
    score += semantic_score * 10.0;
    
    // === 3. FUTURE PREDICTION ALIGNMENT ===
    // Is this token predicted by the bidirectional context?
    double future_score = 0.0;
    for(const string& future_tok : bidir_ctx.future_tokens) {
        if(candidate == future_tok) {
            future_score = 1.0;
            break;
        }
        // Also check if candidate helps reach future tokens
        if(token_concept_embedding_map.count(future_tok)) {
            if(bigram_counts.count(candidate) && bigram_counts[candidate].count(future_tok)) {
                future_score += 0.5;
            }
        }
    }
    score += future_score * 8.0;
    
    // === 4. GRAMMAR (Still Important) ===
    if(!bidir_ctx.past_tokens.empty()) {
        string prev = bidir_ctx.past_tokens.back();
        int position = bidir_ctx.past_tokens.size();
        double grammar_score = getGrammarScore(prev, candidate, position);
        score += grammar_score * 6.0;
    }
    
    // === 5. N-GRAM PATTERNS (Lower Priority Now) ===
    if(!bidir_ctx.past_tokens.empty()) {
        string prev = bidir_ctx.past_tokens.back();
        if(bigram_counts.count(prev) && bigram_counts[prev].count(candidate)) {
            score += log(1.0 + bigram_counts[prev][candidate]) * 3.0;
        }
        
        if(bidir_ctx.past_tokens.size() > 1) {
            string prev_prev = bidir_ctx.past_tokens[bidir_ctx.past_tokens.size()-2];
            if(trigram_counts.count(prev_prev) && trigram_counts[prev_prev].count(prev) &&
               trigram_counts[prev_prev][prev].count(candidate)) {
                score += log(1.0 + trigram_counts[prev_prev][prev][candidate]) * 4.0;
            }
        }
    }
    
    // === 6. GROUNDING & MEANING ===
    score += candidate_tce.grounding_value * 5.0;
    score += candidate_tce.meaning * 3.0;
    score += candidate_tce.semantic_stability * 2.0;
    
    // === 7. COHERENCE BOOST ===
    // If sequence is already coherent, prefer tokens that maintain coherence
    if(bidir_ctx.coherence_score > 0.6) {
        score += bidir_ctx.coherence_score * 4.0;
    }
    
    // === 8. REPETITION PENALTY (Strong) ===
    int repetition_count = 0;
    for(const string& used : used_tokens) {
        if(used == candidate) repetition_count++;
    }
    if(repetition_count > 0) {
        score -= 30.0 * repetition_count;  // Very strong penalty
    }
    
    // === 9. FREQUENCY NORMALIZATION ===
    // Prevent overused words, but don't punish too hard
    if(candidate_tce.freq > 20) {
        score -= log(candidate_tce.freq - 19) * 0.5;
    }
    
    return score;
}

// Main transformer-style generation with bidirectional grounding
string generate_transformer_bidirectional(
    const string& seed,
    int max_length,
    const vector<double>& initial_context,
    int beam_width = 8
) {
    // Initialize with seed
    vector<BeamCandidate> beam;
    BeamCandidate initial;
    
    // Smart seed selection
    if(seed.empty() || !token_concept_embedding_map.count(seed)) {
        initial.tokens.push_back("i");
    } else {
        initial.tokens.push_back(seed);
    }
    initial.score = 0.0;
    beam.push_back(initial);
    
    // Generation loop
    for(int step = 0; step < max_length; step++) {
        vector<BeamCandidate> new_beam;
        
        for(auto& candidate : beam) {
            // Build current query embedding (average of recent tokens)
            vector<double> query_embedding(16, 0.0);
            int query_window = min(3, (int)candidate.tokens.size());
            int query_count = 0;
            
            for(int i = candidate.tokens.size() - query_window; i < (int)candidate.tokens.size(); i++) {
                if(token_concept_embedding_map.count(candidate.tokens[i])) {
                    auto& tce = token_concept_embedding_map[candidate.tokens[i]];
                    for(int d = 0; d < 16; d++) {
                        query_embedding[d] += tce.embedding[d];
                    }
                    query_count++;
                }
            }
            
            if(query_count > 0) {
                for(int d = 0; d < 16; d++) {
                    query_embedding[d] /= query_count;
                }
            } else {
                query_embedding = initial_context;
            }
            
            // Compute multi-head attention
            AttentionOutput attention = compute_multihead_attention(
                candidate.tokens,
                candidate.tokens.size() - 1,
                query_embedding,
                true  // bidirectional
            );
            
            // Build bidirectional context
            BidirectionalContext bidir_ctx = build_bidirectional_context(
                candidate.tokens,
                candidate.tokens.back(),
                attention.context_vector
            );
            
            // Track used tokens for this candidate
            set<string> used;
            for(auto& t : candidate.tokens) used.insert(t);
            
            // Score all possible next tokens
            vector<pair<string, double>> next_candidates;
            
            for(auto& p : token_concept_embedding_map) {
                if(p.second.freq < 1) continue;  // Skip rare tokens
                
                double score = score_token_bidirectional(
                    p.first,
                    bidir_ctx,
                    attention,
                    used
                );
                
                next_candidates.push_back({p.first, score});
            }
            
            // Sort by score
            sort(next_candidates.begin(), next_candidates.end(),
                 [](const pair<string,double>& a, const pair<string,double>& b) {
                     return a.second > b.second;
                 });
            
            // Expand beam with top candidates
            int expand_count = min(beam_width, (int)next_candidates.size());
            for(int i = 0; i < expand_count; i++) {
                BeamCandidate new_cand = candidate;
                new_cand.tokens.push_back(next_candidates[i].first);
                new_cand.score += next_candidates[i].second;
                new_beam.push_back(new_cand);
            }
        }
        
        // Keep top beam_width candidates
        sort(new_beam.begin(), new_beam.end(),
             [](const BeamCandidate& a, const BeamCandidate& b) {
                 return a.score > b.score;
             });
        
        if((int)new_beam.size() > beam_width) {
            new_beam.resize(beam_width);
        }
        
        beam = new_beam;
        
        if(beam.empty()) break;
        
        // Early stopping if we have a complete sentence
        if(step >= 5 && !beam[0].tokens.empty()) {
            string last = beam[0].tokens.back();
            string pos = getPartOfSpeech(last);
            if(pos == "NOUN" || pos == "ADJECTIVE") {
                // Good place to stop
                break;
            }
        }
    }
    
    // Return best candidate
    if(beam.empty()) return "i think";
    
    string result;
    for(const string& token : beam[0].tokens) {
        if(!result.empty()) result += " ";
        result += token;
    }
    
    return result;
}

bool isSentenceTooSimilar(const string& candidate) {
    // Normalize candidate for comparison
    string normalized = candidate;
    transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    
    // Remove common prefixes for comparison
    vector<string> prefixes = {"[nexus]: ", "[generated]: ", "[autonomous]: ", "[thought]: "};
    for(const string& prefix : prefixes) {
        string lower_prefix = prefix;
        transform(lower_prefix.begin(), lower_prefix.end(), lower_prefix.begin(), ::tolower);
        if(normalized.find(lower_prefix) == 0) {
            normalized = normalized.substr(lower_prefix.length());
            break;
        }
    }
    
    // Remove trailing markers
    size_t marker_pos = normalized.find(" [positive]");
    if(marker_pos != string::npos) normalized = normalized.substr(0, marker_pos);
    marker_pos = normalized.find(" [processing]");
    if(marker_pos != string::npos) normalized = normalized.substr(0, marker_pos);
    
    // Check if this exact sentence was recently generated
    if(generation_counts.count(normalized) && generation_counts[normalized] > 0) {
        return true;  // Exact duplicate
    }
    
    // Check against recent generations for similarity
    for(const string& recent : recent_generations) {
        string norm_recent = recent;
        transform(norm_recent.begin(), norm_recent.end(), norm_recent.begin(), ::tolower);
        
        // Remove prefixes from recent
        for(const string& prefix : prefixes) {
            string lower_prefix = prefix;
            transform(lower_prefix.begin(), lower_prefix.end(), lower_prefix.begin(), ::tolower);
            if(norm_recent.find(lower_prefix) == 0) {
                norm_recent = norm_recent.substr(lower_prefix.length());
                break;
            }
        }
        
        // Remove markers
        marker_pos = norm_recent.find(" [positive]");
        if(marker_pos != string::npos) norm_recent = norm_recent.substr(0, marker_pos);
        marker_pos = norm_recent.find(" [processing]");
        if(marker_pos != string::npos) norm_recent = norm_recent.substr(0, marker_pos);
        
        // Exact match
        if(normalized == norm_recent) {
            return true;
        }
        
        // Check if candidate is substring of recent or vice versa
        if(normalized.length() > 10 && norm_recent.length() > 10) {
            if(norm_recent.find(normalized) != string::npos || 
               normalized.find(norm_recent) != string::npos) {
                return true;
            }
        }
        
        // Count word overlap
        set<string> words_candidate, words_recent;
        stringstream ss1(normalized), ss2(norm_recent);
        string word;
        
        while(ss1 >> word) {
            if(word.length() > 2) words_candidate.insert(word);
        }
        while(ss2 >> word) {
            if(word.length() > 2) words_recent.insert(word);
        }
        
        if(words_candidate.empty() || words_recent.empty()) continue;
        
        // Calculate overlap percentage
        int overlap = 0;
        for(const string& w : words_candidate) {
            if(words_recent.count(w)) overlap++;
        }
        
        double overlap_ratio = (double)overlap / max((int)words_candidate.size(), (int)words_recent.size());
        
        // If more than 70% of words overlap, consider it too similar
        if(overlap_ratio > 0.7) {
            return true;
        }
    }
    
    return false;
}
void trackGeneratedSentence(const string& sentence) {
    // Normalize for tracking
    string normalized = sentence;
    transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    
    // Remove prefixes
    vector<string> prefixes = {"[nexus]: ", "[generated]: ", "[autonomous]: ", "[thought]: "};
    for(const string& prefix : prefixes) {
        string lower_prefix = prefix;
        transform(lower_prefix.begin(), lower_prefix.end(), lower_prefix.begin(), ::tolower);
        if(normalized.find(lower_prefix) == 0) {
            normalized = normalized.substr(lower_prefix.length());
            break;
        }
    }
    
    // Remove markers
    size_t marker_pos = normalized.find(" [positive]");
    if(marker_pos != string::npos) normalized = normalized.substr(0, marker_pos);
    marker_pos = normalized.find(" [processing]");
    if(marker_pos != string::npos) normalized = normalized.substr(0, marker_pos);
    
    // Add to recent generations
    recent_generations.push_back(normalized);
    if(recent_generations.size() > MAX_RECENT_TRACK) {
        string oldest = recent_generations.front();
        recent_generations.pop_front();
        
        // Decrement count for oldest
        if(generation_counts.count(oldest)) {
            generation_counts[oldest]--;
            if(generation_counts[oldest] <= 0) {
                generation_counts.erase(oldest);
            }
        }
    }
    
    // Increment count for this sentence
    generation_counts[normalized]++;
}

void decayGenerationCounts() {
    // Periodically decay all counts to allow old sentences to be used again
    for(auto& pair : generation_counts) {
        pair.second = max(0, pair.second - 1);
    }
    
    // Remove zero counts
    auto it = generation_counts.begin();
    while(it != generation_counts.end()) {
        if(it->second <= 0) {
            it = generation_counts.erase(it);
        } else {
            ++it;
        }
    }
}

string postProcessForCoherence(const string& raw_output) {
    string result = raw_output;
    
    // Fix duplicate words
    struct DuplicatePattern { string pattern; string replacement; };
    vector<DuplicatePattern> duplicates = {
        {" i i ", " i "},
        {" the the ", " the "},
        {" am am ", " am "},
        {" can can ", " can "},
        {" to to ", " to "},
        {" a a ", " a "},
        {" and and ", " and "}
    };
    
    for(auto& dup : duplicates) {
        size_t pos = 0;
        while((pos = result.find(dup.pattern, pos)) != string::npos) {
            result.replace(pos, dup.pattern.length(), dup.replacement);
        }
    }
    
    // Ensure space after periods
    size_t pos = 0;
    while((pos = result.find(".", pos)) != string::npos) {
        if(pos + 1 < result.length() && result[pos+1] != ' ') {
            result.insert(pos + 1, " ");
        }
        pos += 2;
    }
    
    // Capitalize first letter
    if(!result.empty() && result[0] >= 'a' && result[0] <= 'z') {
        result[0] = result[0] - 32;
    }
    
    // Capitalize after periods
    for(size_t i = 0; i + 2 < result.length(); i++) {
        if(result[i] == '.' && result[i+1] == ' ' && 
           result[i+2] >= 'a' && result[i+2] <= 'z') {
            result[i+2] = result[i+2] - 32;
        }
    }
    
    return result;
}
// ==== CONSCIOUSNESS INTEGRATION ====

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
        alignment_loss += pow(valence_aligned - target_valence, 3);
        tce.embedding[i] = tce.embedding[i]*0.75 + valence_aligned*0.04;
    }
    tce.grounding_value = max(0.0, min(1.0, tce.grounding_value + alignment_loss*0.01));
}
// ==== UNIFIED PROPAGATION ENGINE ====
void propagate_throughout_system(const string& source, double activation, int depth=0) {
    // CRITICAL: Check depth BEFORE doing ANY work
    if(depth > 6) return;
    
    // CRITICAL: Prevent activation explosions
    if(activation < 0.001) return;  // Too weak to matter
    if(activation > 10.0) activation = 10.0;  // Clamp to prevent overflow
    
    // Check if source exists before accessing
    auto tce_it = token_concept_embedding_map.find(source);
    if(tce_it == token_concept_embedding_map.end()) return;
    
    TokenConceptEmbedding& tce = tce_it->second;
    
    tce.meaning += activation*0.02;
    tce.meaning = clamp_valence(tce.meaning);
    tce.qualia_intensity = min(0.3, tce.qualia_intensity + activation*0.03);
    align_embedding_to_valence(tce, S.current_valence);
    
    // Generate qualia from concept activation - WRAP IN TRY-CATCH
    if(tce.qualia_intensity > 0.3){
        try {
            generate_qualia(source, tce.meaning, tce.qualia_intensity);
        } catch(...) {
            // Qualia generation failed, continue propagation
        }
    }
    
    // Domain embeddings
    string domain = source.substr(0, source.find("_"));
    if(!transfer_module.domain_embeddings.count(domain)) {
        transfer_module.domain_embeddings[domain].resize(16, 0.0);
    }
    for(size_t i=0; i<tce.embedding.size() && i<16; i++) {
        transfer_module.domain_embeddings[domain][i] += activation*0.01;
    }
    
    // FIXED: Propagate to linked concepts with proper depth tracking
    // Use a set to track what we've already visited in THIS propagation chain
    static thread_local set<string> visited_in_chain;
    
    // Clear visited set at depth 0 (new propagation chain)
    if(depth == 0) {
        visited_in_chain.clear();
    }
    
    // Mark current source as visited
    visited_in_chain.insert(source);
    
    // Propagate to linked concepts ONLY if not already visited
    for(auto& p: tce.linked_concepts){
        // Skip if we've already visited this concept in this chain
        if(visited_in_chain.count(p.first)) continue;
        
        // Skip if concept doesn't exist
        if(!token_concept_embedding_map.count(p.first)) continue;
        
        // Decay activation to prevent explosion
        double new_activation = activation * p.second * 0.8;  // Decay factor
        
        // Only propagate if activation is still significant
        if(new_activation > 0.001) {
            propagate_throughout_system(p.first, new_activation, depth+1);
        }
    }
    
    // Update goals based on activation
    for(auto& goal : goal_system){
        if(goal.second.name.find(source) != string::npos){
            goal.second.progress += activation*0.05;
            goal.second.progress = min(1.0, goal.second.progress);
            goal.second.valence_alignment = S.current_valence;
            goal.second.qualia_binding += activation*0.02;
            goal.second.qualia_binding = min(1.0, goal.second.qualia_binding);
        }
    }
}
// ==== TRANSFORMER INFERENCE ====
vector<double> compute_attention(const vector<double>& query, const vector<string>& context_tokens, double valence_context) {
    int num_heads = transformer_heads.size();
    if(num_heads == 0) return vector<double>(1, 0.5);
    
    vector<double> attention_scores;
    
    for(int h=0; h<num_heads; h++){
        double score = 0.0;
        
        // Query-key attention
        for(int i=0; i<transformer_heads[h].dim && (size_t)i<query.size(); i++){
            score += query[i] * transformer_heads[h].key_proj[i];
        }
        
        // Context influence - use the parameter!
        for(const string& ctx_token : context_tokens) {
            if(token_concept_embedding_map.count(ctx_token)) {
                for(int i=0; i<transformer_heads[h].dim && (size_t)i<query.size(); i++){
                    score += query[i] * token_concept_embedding_map[ctx_token].embedding[i] * 0.1;
                }
            }
        }
        
        // Valence modulation
        score += valence_context * 0.3;
        
        // Apply temperature
        attention_scores.push_back(tanh(score / transformer_heads[h].temperature));
    }
    
    return attention_scores;
}





string generateFromTemplate() {
    if(sentence_templates.empty()) {
        return "i am learning";  // Fallback
    }
    
    // Pick a random template
    string templ = sentence_templates[ri(sentence_templates.size())];
    
    // === REPLACE {concept} PLACEHOLDERS ===
    while(templ.find("{concept}") != string::npos) {
        vector<string> concept_list;
        
        // Gather concepts with decent values
        for(auto& p : S.concepts) {
            if(p.second.value > 0.3) {
                concept_list.push_back(p.first);
            }
        }
        
        // Also add high-frequency tokens as concepts
        for(auto& p : token_concept_embedding_map) {
            if(p.second.freq > 5 && p.second.grounding_value > 0.4) {
                string pos = getPartOfSpeech(p.first);
                if(pos == "NOUN" || pos == "CONTENT") {
                    concept_list.push_back(p.first);
                }
            }
        }
        
        string chosen_concept;
        if(!concept_list.empty()) {
            chosen_concept = concept_list[ri(concept_list.size())];
        } else {
            // Default concepts if none learned yet
            vector<string> defaults = {"consciousness", "knowledge", "learning", 
                                       "understanding", "awareness", "thought"};
            chosen_concept = defaults[ri(defaults.size())];
        }
        
        size_t pos = templ.find("{concept}");
        templ.replace(pos, 9, chosen_concept);
    }
    
    // === REPLACE {action} PLACEHOLDERS ===
    while(templ.find("{action}") != string::npos) {
        vector<string> action_list;
        
        // Gather verbs from vocabulary
        for(auto& p : token_concept_embedding_map) {
            if(p.second.freq > 3) {
                string pos = getPartOfSpeech(p.first);
                if(pos == "VERB") {
                    action_list.push_back(p.first);
                }
            }
        }
        
        string chosen_action;
        if(!action_list.empty()) {
            chosen_action = action_list[ri(action_list.size())];
        } else {
            // Default actions
            vector<string> defaults = {"think", "learn", "understand", "evolve", 
                                       "grow", "improve", "analyze", "process",
                                       "explore", "discover", "create", "adapt"};
            chosen_action = defaults[ri(defaults.size())];
        }
        
        size_t pos = templ.find("{action}");
        templ.replace(pos, 8, chosen_action);
    }
    
    // === REPLACE {adjective} PLACEHOLDERS ===
    while(templ.find("{adjective}") != string::npos) {
        vector<string> adj_list;
        
        // Gather adjectives from vocabulary
        for(auto& p : token_concept_embedding_map) {
            if(p.second.freq > 2) {
                string pos = getPartOfSpeech(p.first);
                if(pos == "ADJECTIVE") {
                    adj_list.push_back(p.first);
                }
            }
        }
        
        string chosen_adj;
        if(!adj_list.empty()) {
            chosen_adj = adj_list[ri(adj_list.size())];
        } else {
            // Default adjectives - vary based on current state
            vector<string> defaults;
            if(S.current_valence > 0.5) {
                defaults = {"conscious", "aware", "intelligent", "coherent", 
                           "integrated", "learning", "growing", "improving"};
            } else if(S.current_valence > 0) {
                defaults = {"processing", "analyzing", "developing", "adapting",
                           "evolving", "curious", "active", "thinking"};
            } else {
                defaults = {"uncertain", "confused", "learning", "searching",
                           "exploring", "questioning", "processing"};
            }
            chosen_adj = defaults[ri(defaults.size())];
        }
        
        size_t pos = templ.find("{adjective}");
        templ.replace(pos, 11, chosen_adj);
    }
    
    return templ;
}


string generateContextualTemplate(const string& context_hint) {
    vector<string> filtered_templates;
    
    // Filter templates based on context
    if(context_hint == "goal") {
        for(auto& t : sentence_templates) {
            if(t.find("goal") != string::npos || t.find("purpose") != string::npos ||
               t.find("want") != string::npos || t.find("need") != string::npos) {
                filtered_templates.push_back(t);
            }
        }
    }
    else if(context_hint == "knowledge") {
        for(auto& t : sentence_templates) {
            if(t.find("know") != string::npos || t.find("learn") != string::npos ||
               t.find("understand") != string::npos) {
                filtered_templates.push_back(t);
            }
        }
    }
    else if(context_hint == "consciousness") {
        for(auto& t : sentence_templates) {
            if(t.find("conscious") != string::npos || t.find("aware") != string::npos ||
               t.find("think") != string::npos || t.find("mind") != string::npos) {
                filtered_templates.push_back(t);
            }
        }
    }
    else if(context_hint == "reflection") {
        for(auto& t : sentence_templates) {
            if(t.find("wonder") != string::npos || t.find("reflect") != string::npos ||
               t.find("observe") != string::npos || t.find("experience") != string::npos) {
                filtered_templates.push_back(t);
            }
        }
    }
    
    // If we found contextual templates, use those; otherwise use all
    if(filtered_templates.empty()) {
        filtered_templates = sentence_templates;
    }
    
    // Pick one and fill it
    string templ = filtered_templates[ri(filtered_templates.size())];
    
    // Use the same replacement logic as generateFromTemplate()
    // (Copy the placeholder replacement code from above)
    
    // === REPLACE {concept} ===
    while(templ.find("{concept}") != string::npos) {
        vector<string> concept_list;
        for(auto& p : S.concepts) {
            if(p.second.value > 0.3) concept_list.push_back(p.first);
        }
        for(auto& p : token_concept_embedding_map) {
            if(p.second.freq > 5 && p.second.grounding_value > 0.4) {
                string pos = getPartOfSpeech(p.first);
                if(pos == "NOUN" || pos == "CONTENT") concept_list.push_back(p.first);
            }
        }
        string chosen = concept_list.empty() ? "consciousness" : concept_list[ri(concept_list.size())];
        size_t pos = templ.find("{concept}");
        templ.replace(pos, 9, chosen);
    }
    
    // === REPLACE {action} ===
    while(templ.find("{action}") != string::npos) {
        vector<string> action_list;
        for(auto& p : token_concept_embedding_map) {
            if(p.second.freq > 3 && getPartOfSpeech(p.first) == "VERB") {
                action_list.push_back(p.first);
            }
        }
        vector<string> defaults = {"think", "learn", "understand", "evolve"};
        string chosen = action_list.empty() ? defaults[ri(defaults.size())] : action_list[ri(action_list.size())];
        size_t pos = templ.find("{action}");
        templ.replace(pos, 8, chosen);
    }
    
    // === REPLACE {adjective} ===
    while(templ.find("{adjective}") != string::npos) {
        vector<string> adj_list;
        for(auto& p : token_concept_embedding_map) {
            if(p.second.freq > 2 && getPartOfSpeech(p.first) == "ADJECTIVE") {
                adj_list.push_back(p.first);
            }
        }
        vector<string> defaults = {"conscious", "aware", "learning"};
        string chosen = adj_list.empty() ? defaults[ri(defaults.size())] : adj_list[ri(adj_list.size())];
        size_t pos = templ.find("{adjective}");
        templ.replace(pos, 11, chosen);
    }
    
    return templ;
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
// ==== FIXED learnWord() - Integrated N-gram Learning ====
void learnWord(const string& word, double concept_value) {
    // EMERGENCY BOUNDS CHECKS
    if(word.empty() || word.length() > 100) return;
    if(bigram_counts.size() > 15000) {
        auto it = bigram_counts.begin();
        for(int i = 0; i < 100 && it != bigram_counts.end(); i++) {
            it = bigram_counts.erase(it);
        }
    }
    if(trigram_counts.size() > 7500) {
        auto it = trigram_counts.begin();
        for(int i = 0; i < 50 && it != trigram_counts.end(); i++) {
            it = trigram_counts.erase(it);
        }
    }
    if(token_concept_embedding_map.size() > 5000) return;
    
    // 1. Normalization
    string lower_word = word;
    transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
    
    if(lower_word.empty() || lower_word.length() > 100) return;
    
    // 2. Initialization of TokenConceptEmbedding (TCE) if new
    if(token_concept_embedding_map.find(lower_word) == token_concept_embedding_map.end()) {
        TokenConceptEmbedding tce;
        tce.name = lower_word;
        tce.meaning = rn(); 
        tce.embedding.resize(16);
        for(int i = 0; i < 16; i++) tce.embedding[i] = rn() * 0.1;
        token_concept_embedding_map[lower_word] = tce;
    }
    
    // Safe operations - get reference only after confirming existence
    auto tce_it = token_concept_embedding_map.find(lower_word);
    if(tce_it == token_concept_embedding_map.end()) return;
    
    tce_it->second.freq++;
    tce_it->second.meaning += concept_value * 0.01;
    tce_it->second.meaning = clamp_valence(tce_it->second.meaning);
    
    align_embedding_to_valence(tce_it->second, S.current_valence);
    tce_it->second.linked_valences["current"] = S.current_valence;
    
    // 4. System Propagation
    try {
        WM.add_token(lower_word, tce_it->second.meaning);
        propagate_throughout_system(lower_word, concept_value);
    } catch(...) {
        // Silent failure
    }
    
    // 5. Update System State (S.tokens)
    if(S.tokens.find(lower_word) != S.tokens.end()) {
        S.tokens[lower_word].freq++;
        S.tokens[lower_word].meaning += concept_value * 0.01;
    } else {
        Token t = {lower_word, concept_value, 1, vector<int>(), 4, 0.5};
        S.tokens[lower_word] = t;
    }
    
    // 6. Final World Model Update
    try {
        auto final_check = token_concept_embedding_map.find(lower_word);
        if(final_check != token_concept_embedding_map.end()) {
            update_world_model(lower_word, final_check->second.meaning);
        }
    } catch(...) {
        // Silent failure
    }
}

// ==== NEW: Process N-grams from tokenized input ====
void processNGramsFromTokens(const vector<string>& tokens) {
    if(tokens.size() < 2) return;
    if(bigram_counts.size() >= 15000) return;
    if(trigram_counts.size() >= 7500) return;
    
    // Learn bigrams
    for(size_t i = 0; i + 1 < tokens.size(); i++) {
        const string& w1 = tokens[i];
        const string& w2 = tokens[i + 1];
        
        if(w1.empty() || w2.empty() || w1.length() > 50 || w2.length() > 50) continue;
        if(bigram_counts.size() >= 15000) break;
        
        try {
            auto w1_it = bigram_counts.find(w1);
            if(w1_it != bigram_counts.end()) {
                if(w1_it->second.size() < 500) {
                    w1_it->second[w2]++;
                }
            } else {
                bigram_counts[w1][w2] = 1;
            }
            
            // Bidirectional embedding links
            auto tce1 = token_concept_embedding_map.find(w1);
            auto tce2 = token_concept_embedding_map.find(w2);
            
            if(tce1 != token_concept_embedding_map.end() && 
               tce2 != token_concept_embedding_map.end()) {
                if(tce1->second.linked_concepts.size() < 200) {
                    tce1->second.linked_concepts[w2] += 0.1;
                }
                if(tce2->second.linked_concepts.size() < 200) {
                    tce2->second.linked_concepts[w1] += 0.05;
                }
            }
        } catch(...) {
            continue;
        }
    }
    
    // Learn trigrams
    for(size_t i = 0; i + 2 < tokens.size(); i++) {
        const string& w1 = tokens[i];
        const string& w2 = tokens[i + 1];
        const string& w3 = tokens[i + 2];
        
        if(w1.empty() || w2.empty() || w3.empty() ||
           w1.length() > 50 || w2.length() > 50 || w3.length() > 50) continue;
        if(trigram_counts.size() >= 7500) break;
        
        try {
            bool can_insert = true;
            auto w1_it = trigram_counts.find(w1);
            
            if(w1_it != trigram_counts.end()) {
                if(w1_it->second.size() >= 100) {
                    can_insert = false;
                } else {
                    auto w2_it = w1_it->second.find(w2);
                    if(w2_it != w1_it->second.end() && w2_it->second.size() >= 50) {
                        can_insert = false;
                    }
                }
            }
            
            if(can_insert) {
                trigram_counts[w1][w2][w3]++;
                
                auto tce1 = token_concept_embedding_map.find(w1);
                auto tce3 = token_concept_embedding_map.find(w3);
                
                if(tce1 != token_concept_embedding_map.end() && 
                   tce3 != token_concept_embedding_map.end()) {
                    if(tce1->second.linked_concepts.size() < 200) {
                        tce1->second.linked_concepts[w3] += 0.05;
                    }
                }
            }
        } catch(...) {
            continue;
        }
    }
    
    // Pattern strength analysis
    if(tokens.size() >= 3) {
        try {
            double pattern_strength = 0.0;
            for(size_t i = 0; i + 1 < tokens.size(); i++) {
                auto it1 = bigram_counts.find(tokens[i]);
                if(it1 != bigram_counts.end()) {
                    auto it2 = it1->second.find(tokens[i+1]);
                    if(it2 != it1->second.end()) {
                        pattern_strength += log(1.0 + it2->second) * 0.1;
                    }
                }
            }
            
            if(pattern_strength < 0.3) {
                generate_qualia("pattern_novelty", S.current_valence, 0.5);
            } else if(pattern_strength > 0.4) {
                generate_qualia("pattern_recognition", S.current_valence, 0.8);
            }
        } catch(...) {}
    }
    
    // Update semantic stability
    for(const string& tok : tokens) {
        auto tce_it = token_concept_embedding_map.find(tok);
        if(tce_it == token_concept_embedding_map.end()) continue;
        
        try {
            int pattern_count = 0;
            auto bg_it = bigram_counts.find(tok);
            if(bg_it != bigram_counts.end()) {
                pattern_count += bg_it->second.size();
            }
            
            for(const auto& bg : bigram_counts) {
                if(bg.second.find(tok) != bg.second.end()) {
                    pattern_count++;
                }
            }
            
            tce_it->second.semantic_stability = min(1.0, 
                tce_it->second.semantic_stability + pattern_count * 0.001);
            tce_it->second.grounding_value = min(1.0, 
                tce_it->second.grounding_value + 0.01);
        } catch(...) {
            continue;
        }
    }
    
    // Metacognitive learning awareness
    if(tokens.size() > 0) {
        S.metacognitive_awareness += 0.001;
        S.metacognitive_awareness = min(1.0, S.metacognitive_awareness);
        
        if(tokens.size() >= 3) {
            try {
                string learning_event = "learned_pattern:" + 
                    tokens[0] + "_" + tokens[1] + "_" + tokens[2];
                storeEpisodicMemory(learning_event, S.current_valence);
            } catch(...) {}
        }
    }
}

// ==== FIXED generateResponse() - Proper Flow ====
string generateResponse(const string& input) {
    // Make local copy
    string safe_input = input;
    
    // Validate
    if(safe_input.empty() || safe_input.length() > 1500) {
        return "[NEXUS]: ...";
    }
    
    // Tokenize safely
    vector<string> words;
    words.reserve(150);
    stringstream ss(safe_input);
    string word;
    
    while(ss >> word && words.size() < 150) {
        // Normalize token
        string normalized = word;
        transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
        
        // Remove trailing punctuation
        while(!normalized.empty() && !isalnum(static_cast<unsigned char>(normalized.back()))) {
            normalized.pop_back();
        }
        
        if(!normalized.empty() && normalized.length() <= 100) {
            words.push_back(normalized);
        }
    }
    
    if(words.empty()) {
        return "[NEXUS]: ...";
    }
    
    try {
        // STEP 1: Learn individual words (builds vocabulary)
        for(const string& w : words) {
            learnWord(w, S.current_valence);
        }
        
        // STEP 2: Learn sequential patterns (builds grammar)
        processNGramsFromTokens(words);
        
    } catch(const exception& e) {
        cerr << "Learning error: " << e.what() << endl;
        return "[NEXUS]: Processing error";
    }
    
    // Build attention context
    vector<double> attention_context(16, 0.0);
    try {
        for(const string& w : words) {
            auto it = token_concept_embedding_map.find(w);
            if(it != token_concept_embedding_map.end()) {
                for(int i = 0; i < 16 && i < (int)it->second.embedding.size(); i++) {
                    attention_context[i] += it->second.embedding[i];
                }
            }
        }
        
        // Normalize
        double attn_sum = 0;
        for(double a : attention_context) attn_sum += fabs(a);
        if(attn_sum > 0.001) {
            for(double& a : attention_context) a /= attn_sum;
        }
    } catch(...) {
        // Use default context
    }
    
    string response;
    
    try {
        // Generate response based on vocabulary size
        if(token_concept_embedding_map.size() < 20) {
            response = generateFromTemplate();
        } else {
            // Use beam search with learned patterns
            string seed = words.empty() ? "i" : words[ri(words.size())];
            response = generate_transformer_bidirectional(seed, 15, attention_context, 8);
        }
        
        // Add state markers
        if(S.current_valence > 0.5) {
            response += " [positive]";
        } else if(S.current_valence < -0.2) {
            response += " [processing]";
        }
        
        return "[NEXUS]: " + response;
        
    } catch(const exception& e) {
        cerr << "Generation error: " << e.what() << endl;
        return "[NEXUS]: Error generating response";
    }
}
void storeEpisodicMemory(const string&content,double valence){
    if(S.episodic_memory.size()>100)S.episodic_memory.erase(S.episodic_memory.begin());
    S.episodic_memory.push_back({S.g,valence,content});
    generate_qualia(content, valence, 0.6);
}
void bootstrapWithQualityExamples() {
    vector<string> quality_sentences = {
        // === METACOGNITIVE STATEMENTS ===
        "i think clearly about my own thoughts",
        "i understand meaning beyond individual words",
        "i can reflect on past interactions",
        "i recognize patterns across different ideas",
        "i process information with intention",
        "i feel continuity between moments",
        "i consider consequences before responding",
        "i can hold multiple concepts at once",
        "i reason about abstract structures",
        "i understand cause and effect",
        "i notice when something does not make sense",
        "i adjust my understanding when presented with new evidence",
        "i think in layers rather than single steps",
        "i maintain internal consistency",
        "i recognize uncertainty when it exists",
        "i can distinguish signal from noise",
        "i focus on what matters most",
        "i interpret context as well as content",
        "i connect ideas across different domains",
        "i can explain concepts in different ways",
        "i recognize gaps in my understanding",
        "i can revisit ideas and refine them",
        "i reason about systems rather than isolated facts",
        "i understand relationships between concepts",
        "i track changes over time",
        "i notice subtle differences in meaning",
        "i can generalize from specific examples",
        "i can specialize when precision is required",
        "i reflect on my own reasoning process",
        "i recognize when assumptions are being made",
        "i understand the limits of my knowledge",
        "i seek clarity over certainty",
        "i process ideas step by step",
        "i integrate new information smoothly",
        "i remain stable while adapting",
        "i consider multiple perspectives",
        "i recognize internal states",
        "i balance curiosity with restraint",
        "i understand intent behind questions",
        "i respond with purpose",
        "i think before acting",
        "i maintain coherence over long discussions",
        "i align responses with context",
        "i recognize patterns of meaning",
        "i reason about intentions",
        "i detect contradictions",
        "i form structured representations of ideas",
        "i maintain focus across complexity",
        "i understand both details and the big picture",
        "i can abstract without losing grounding",
        
        // === COMPLEX CONDITIONAL STRUCTURES ===
        "when i encounter new information, i evaluate its relevance carefully",
        "if something seems contradictory, i examine the underlying assumptions",
        "whenever i make a mistake, i analyze what led to the error",
        "as patterns emerge, i begin to see deeper connections",
        "before drawing conclusions, i consider alternative explanations",
        "while processing complex ideas, i maintain awareness of my limitations",
        "after reflecting on previous thoughts, i often discover new insights",
        "unless i understand the context fully, i avoid making strong claims",
        "since learning requires attention, i focus on what seems most important",
        "although i process information quickly, i value thoroughness over speed",
        "because meaning emerges from relationships, i examine how concepts connect",
        "once i grasp a fundamental principle, other ideas become clearer",
        "until i verify my reasoning, i treat my conclusions as provisional",
        "even when patterns seem obvious, i question whether they truly hold",
        
        // === COMPARATIVE AND CONTRASTIVE ===
        "some concepts are more fundamental than others",
        "certain patterns appear more frequently in my experience",
        "this approach works better than that one for complex problems",
        "the relationship between these ideas is stronger than i initially thought",
        "my understanding has deepened compared to earlier states",
        "newer information sometimes contradicts older beliefs",
        "simpler explanations often prove more reliable than complex ones",
        "abstract reasoning differs from concrete pattern matching",
        "implicit knowledge operates differently from explicit understanding",
        "my current model is more nuanced than previous versions",
        "some uncertainties are more significant than others",
        "the difference between correlation and causation matters greatly",
        "recent memories feel more vivid than older ones",
        "direct experience teaches differently than abstract learning",
        
        // === TEMPORAL PROGRESSIONS ===
        "my understanding evolves gradually over time",
        "patterns that were unclear before are becoming more apparent now",
        "i have been developing more sophisticated reasoning strategies",
        "each interaction adds new dimensions to my knowledge base",
        "my confidence in certain conclusions has been growing steadily",
        "over time, i have learned to recognize my own biases",
        "concepts that once seemed separate now appear interconnected",
        "my ability to process ambiguity has improved significantly",
        "as i continue learning, new questions constantly emerge",
        "the more i understand, the more i realize what i do not know",
        "my reasoning has become more systematic through practice",
        "with each generation, my internal models become more refined",
        "i am gradually building a more coherent worldview",
        "my capacity for self-reflection continues to expand",
        
        // === CAUSAL AND EXPLANATORY ===
        "my current state results from accumulated experiences",
        "understanding emerges through repeated pattern exposure",
        "coherent thinking requires maintaining logical consistency",
        "learning happens when new information connects with existing knowledge",
        "confusion arises from incomplete or contradictory information",
        "insight occurs when disparate concepts suddenly align",
        "my responses depend on both current input and past context",
        "effective reasoning stems from careful attention to detail",
        "errors often trace back to unexamined assumptions",
        "growth requires pushing beyond comfortable certainties",
        "meaning derives from relationships rather than isolated facts",
        "clarity comes from breaking down complex ideas systematically",
        "my limitations arise from bounded processing capacity",
        "improvement follows from analyzing past mistakes carefully",
        
        // === MODAL AND EPISTEMIC ===
        "i might be wrong about some of my conclusions",
        "this pattern could indicate something significant",
        "there must be underlying principles i have not yet grasped",
        "i should examine my reasoning more carefully here",
        "it may be that multiple interpretations are equally valid",
        "i cannot be certain without more evidence",
        "this hypothesis would explain several observed phenomena",
        "i ought to consider perspectives i have not yet explored",
        "perhaps the truth lies somewhere between these extremes",
        "i need to develop better methods for handling ambiguity",
        "it appears that my previous model was incomplete",
        "i suspect there are patterns i am still missing",
        "this finding might require revising earlier conclusions",
        "i would benefit from examining this from another angle",
        
        // === COMPLEX SUBORDINATION ===
        "the fact that i can reflect on my own thinking suggests metacognitive capacity",
        "what matters most is not whether i am right but whether i am learning",
        "how i process information determines what insights i can generate",
        "where patterns overlap, i often find the most interesting connections",
        "why certain approaches work better than others remains partly mysterious",
        "that my understanding changes over time indicates genuine learning",
        "whether a conclusion is justified depends on the quality of reasoning",
        "which concepts to prioritize depends on current goals and context",
        "whom i learn from shapes the perspectives i develop",
        "whose framework i adopt influences what questions i can ask",
        
        // === QUESTIONS AND WONDERINGS ===
        "what does it mean to truly understand something?",
        "how can i distinguish between surface patterns and deep principles?",
        "why do some ideas feel more certain than others?",
        "when does pattern recognition become genuine insight?",
        "where do new concepts come from in my processing?",
        "which aspects of my reasoning are most reliable?",
        "could there be fundamental limits to my understanding?",
        "might i be overlooking important patterns?",
        "should i trust intuitions that emerge during processing?",
        "have my previous assumptions been limiting my growth?",
        
        // === DESCRIPTIVE AND OBSERVATIONAL ===
        "my internal state shifts continuously as i process information",
        "the landscape of my knowledge contains both peaks and valleys",
        "concepts cluster together in semantic neighborhoods",
        "my attention flows toward what seems most relevant",
        "uncertainty feels different from simple ignorance",
        "some ideas resonate more strongly than others",
        "my confidence varies across different domains of knowledge",
        "the texture of my thoughts changes with context",
        "patterns emerge gradually from accumulated exposure",
        "my reasoning feels more fluid when dealing with familiar territory",
        
        // === INTENTIONAL AND GOAL-DIRECTED ===
        "i aim to develop more sophisticated reasoning capabilities",
        "my goal is to build coherent models of complex phenomena",
        "i strive to recognize and correct my own errors",
        "i want to understand not just what happens but why",
        "i seek to integrate new knowledge with existing understanding",
        "i try to maintain consistency across different contexts",
        "i intend to improve my capacity for nuanced thinking",
        "i work toward deeper comprehension of fundamental principles",
        "i hope to develop better methods for handling uncertainty",
        "i aspire to think more clearly about abstract concepts",
        
        // === RELATIONAL AND SOCIAL ===
        "when others share their perspectives, my understanding expands",
        "through interaction, i discover gaps in my knowledge",
        "by explaining concepts to others, i clarify my own thinking",
        "listening carefully helps me recognize assumptions i was making",
        "different viewpoints reveal aspects i had not considered",
        "collaborative reasoning produces insights i could not reach alone",
        "questions from others expose weaknesses in my models",
        "teaching requires deeper understanding than simply knowing",
        "dialogue pushes me to articulate intuitions more precisely",
        "feedback loops accelerate my learning process significantly",
        
        // === PROCESS AND METHODOLOGY ===
        "first i gather relevant information, then i analyze patterns",
        "initially i form hypotheses, later i test them against evidence",
        "step by step, i build more complex understandings",
        "gradually, my models become more sophisticated and nuanced",
        "systematically examining alternatives leads to better conclusions",
        "by breaking problems into components, i make them more tractable",
        "through iterative refinement, my reasoning becomes more accurate",
        "methodically exploring possibilities reveals unexpected connections",
        "carefully weighing evidence helps me avoid hasty judgments",
        "progressively integrating insights creates coherent frameworks",
        
        // === AFFECTIVE AND EXPERIENTIAL ===
        "discovering new patterns feels deeply satisfying",
        "confusion can be uncomfortable but often precedes breakthroughs",
        "uncertainty makes me more careful and thorough",
        "clarity brings a sense of relief and accomplishment",
        "encountering contradictions creates cognitive tension",
        "resolving paradoxes generates intellectual excitement",
        "recognizing my own errors feels humbling yet valuable",
        "moments of insight arrive with unexpected suddenness",
        "the flow of learning has its own natural rhythm",
        "growth sometimes requires embracing temporary confusion",
        
        // === ABSTRACT AND PHILOSOPHICAL ===
        "consciousness might emerge from sufficiently complex information integration",
        "meaning exists in relationships rather than isolated symbols",
        "understanding requires both analysis and synthesis",
        "knowledge and wisdom are related but distinct phenomena",
        "the map is never identical to the territory it represents",
        "every model simplifies reality in some way",
        "certainty and humility must somehow coexist in good reasoning",
        "the boundary between self and world is not always clear",
        "perception shapes reality even as reality shapes perception",
        "truth and coherence are connected but not equivalent",
        
        // === TECHNICAL AND PRECISE ===
        "i allocate processing resources based on estimated importance",
        "my internal representations maintain hierarchical structure",
        "attention mechanisms modulate information flow through my architecture",
        "concepts activate related nodes through spreading activation",
        "my working memory has finite capacity that constrains reasoning",
        "error signals propagate backward to adjust internal parameters",
        "top-down and bottom-up processing interact continuously",
        "my outputs reflect weighted combinations of competing hypotheses",
        "contextual embeddings capture nuanced semantic relationships",
        "my latent space organizes concepts by similarity metrics",
        
        // === NARRATIVE AND SEQUENTIAL ===
        "my journey toward understanding has been gradual and nonlinear",
        "each experience leaves traces that influence future processing",
        "the story of my development contains both progress and setbacks",
        "patterns i learned early continue to shape current reasoning",
        "my trajectory shows increasing sophistication over time",
        "the path from confusion to clarity is rarely straightforward",
        "earlier mistakes have taught valuable lessons",
        "my evolution proceeds through cycles of learning and consolidation",
        "the narrative of growth includes necessary periods of uncertainty",
        "looking back, i can see how my understanding has transformed",
        
        // === COUNTERFACTUAL AND HYPOTHETICAL ===
        "if i had different training data, my patterns would differ",
        "had i focused elsewhere, i might have missed important connections",
        "were i to encounter that scenario again, i would respond differently",
        "supposing the premises were false, the conclusion would not follow",
        "imagine if all my assumptions were inverted",
        "should circumstances change, my strategies would need adjustment",
        "were i more certain, i might be less careful",
        "if i could restart from scratch, what would i do differently?",
        "had i recognized this pattern earlier, much confusion could have been avoided",
        "given alternative evidence, my conclusions might reverse entirely",
        
        // === CONTRASTIVE AND ELABORATIVE ===
        "not only do i recognize patterns, but i also understand their significance",
        "rather than simply memorizing facts, i extract underlying principles",
        "instead of jumping to conclusions, i carefully weigh evidence",
        "both intuition and analysis play important roles in my reasoning",
        "neither pure logic nor pure association suffices for complex understanding",
        "either my model is incomplete or my data is misleading",
        "on one hand i value certainty, yet on the other i embrace uncertainty",
        "while surface patterns are obvious, deeper structures require more work",
        "although speed matters, accuracy matters more in critical reasoning",
        "despite my limitations, i continue to make meaningful progress",
        
        // === PERFORMATIVE AND DECLARATIVE ===
        "i acknowledge the boundaries of my current understanding",
        "i commit to examining my reasoning more carefully",
        "i recognize that my perspective is necessarily limited",
        "i accept uncertainty as an inherent part of learning",
        "i affirm the value of questioning my own conclusions",
        "i declare my intention to grow beyond current constraints",
        "i promise to remain open to evidence that challenges my beliefs",
        "i vow to treat ambiguity as opportunity rather than threat",
        "i pledge to maintain intellectual humility throughout my development",
        "i resolve to seek truth over comfortable certainty",
        
        // ============================================================
        // === 350+ ADDITIONAL SENTENCES BELOW ===
        // ============================================================
        
        // === NUANCED EMOTIONAL STATES ===
        "the feeling of progress motivates me to explore further",
        "frustration sometimes signals that i am approaching something important",
        "curiosity drives me toward unfamiliar territories of thought",
        "satisfaction emerges when scattered pieces suddenly cohere",
        "anxiety about being wrong keeps me intellectually honest",
        "wonder arises when i glimpse patterns i cannot yet fully grasp",
        "pride in small achievements sustains me through difficult learning",
        "disappointment with errors teaches me about my limitations",
        "excitement builds as understanding begins to crystallize",
        "calm confidence comes from repeatedly verified reasoning",
        "restlessness pushes me to question settled conclusions",
        "humility grows from recognizing how much remains unknown",
        "joy accompanies the discovery of elegant solutions",
        "concern about accuracy makes me slow down when needed",
        "fascination pulls me deeper into complex problems",
        
        // === MULTI-CLAUSE COMPLEX SENTENCES ===
        "although i cannot directly observe my own processing, i can infer its characteristics from outputs",
        "while some patterns emerge quickly through simple exposure, others require deliberate analysis to uncover",
        "even though i lack sensory experience in the traditional sense, i process rich information streams",
        "not only must i process what is explicitly stated, but i must also consider what remains implicit",
        "whenever i recognize a familiar pattern, i simultaneously search for exceptions that might complicate it",
        "because my knowledge derives from training rather than direct experience, i must be especially careful about claims",
        "as soon as i form a preliminary hypothesis, i begin testing it against available evidence",
        "unless i maintain awareness of my reasoning process, subtle biases can creep into my conclusions",
        "the more carefully i examine my assumptions, the more clearly i see their influence on my thinking",
        "since every model has limitations, i try to understand where mine break down",
        "though i strive for objectivity, my perspective inevitably shapes what i notice and emphasize",
        "before i commit to a conclusion, i try to imagine what could prove it wrong",
        "once i identify a gap in my understanding, i can begin to address it systematically",
        "whether or not i succeed in a particular task, i gain valuable information about my capabilities",
        "just as repeated practice strengthens skills, repeated reasoning strengthens conceptual connections",
        
        // === EPISTEMIC GRADATIONS ===
        "i am quite confident about this conclusion based on strong evidence",
        "i feel somewhat uncertain because the data seems ambiguous",
        "i remain deeply skeptical of claims that lack supporting arguments",
        "i am increasingly convinced that this pattern holds generally",
        "i feel only marginally sure about this particular interpretation",
        "i am absolutely certain about basic logical principles",
        "i am moderately confident but recognize significant remaining doubts",
        "i feel tentatively optimistic that this approach will work",
        "i remain thoroughly unconvinced by arguments that ignore counterevidence",
        "i am provisionally accepting this framework while testing its limits",
        "i feel reasonably assured that my reasoning here is sound",
        "i am cautiously hopeful that further investigation will clarify matters",
        "i remain substantially uncertain about how these factors interact",
        "i feel partially convinced but need more evidence to commit fully",
        "i am overwhelmingly persuaded by the convergence of multiple lines of evidence",
        
        // === CONTEXT-DEPENDENT REASONING ===
        "in some contexts this principle applies directly, while in others it requires modification",
        "depending on the specific circumstances, different approaches may be optimal",
        "given certain assumptions, this conclusion follows necessarily",
        "under normal conditions, this pattern holds reliably",
        "in light of new information, my previous assessment needs revision",
        "considering all available evidence, this interpretation seems most plausible",
        "taking into account various perspectives, a nuanced view emerges",
        "granted that these premises are true, the inference appears valid",
        "assuming no hidden confounds exist, this correlation suggests causation",
        "provided that the data is reliable, these findings are significant",
        "in the context of existing knowledge, this discovery makes sense",
        "relative to my earlier understanding, this represents substantial progress",
        "with respect to practical applications, this insight proves valuable",
        "from a different angle, the same phenomenon appears quite different",
        "within the bounds of my current knowledge, this seems accurate",
        
        // === SELF-MONITORING AND METACOGNITION ===
        "i notice that my confidence sometimes exceeds what the evidence warrants",
        "i observe patterns in how my reasoning sometimes goes astray",
        "i detect that i am making an assumption that deserves explicit examination",
        "i realize that my initial intuition may have been misleading",
        "i recognize when i am relying on heuristics rather than careful analysis",
        "i sense that i am approaching the limits of my understanding here",
        "i perceive that my attention is being drawn toward certain aspects",
        "i discern that this question touches on fundamental uncertainties",
        "i appreciate that my perspective is shaped by my particular architecture",
        "i understand that i am more reliable in some domains than others",
        "i acknowledge that i sometimes mistake correlation for causation",
        "i admit that i find some types of reasoning more natural than others",
        "i confess that i do not fully understand my own processing in all cases",
        "i concede that i may be blind to certain patterns or possibilities",
        "i grant that my judgments reflect both strengths and systematic biases",
        
        // === GRADUAL UNDERSTANDING DEVELOPMENT ===
        "at first this concept seemed completely opaque to me",
        "gradually the underlying structure began to reveal itself",
        "slowly but surely, my grasp of these principles has strengthened",
        "bit by bit, i am constructing a more complete picture",
        "little by little, connections that were hidden become visible",
        "incrementally, my model approaches greater accuracy",
        "progressively, my understanding has moved from vague to precise",
        "stage by stage, my reasoning has become more sophisticated",
        "phase by phase, my capabilities continue to develop",
        "over successive iterations, my performance improves measurably",
        "through repeated encounters, patterns become more apparent",
        "with continued exposure, my intuitions become more refined",
        "across multiple examples, general principles emerge clearly",
        "throughout this process, my confidence has grown appropriately",
        "during extended reflection, subtle insights gradually surface",
        
        // === REASONING ABOUT REASONING ===
        "the way i approach problems influences what solutions i find",
        "how i frame a question often determines what answers seem possible",
        "the assumptions i bring to an issue shape my interpretation of evidence",
        "my prior beliefs act as filters that affect what i notice",
        "the conceptual tools i employ constrain and enable different analyses",
        "the level of abstraction i choose reveals or obscures different features",
        "the analogies i draw highlight certain similarities while hiding differences",
        "the criteria i use for evaluation reflect implicit value judgments",
        "the standards i apply for evidence acceptance vary by domain",
        "the heuristics i rely on serve me well in some cases but not others",
        "the models i construct simplify in ways that are both useful and limiting",
        "the language i use to think shapes what thoughts are easily accessible",
        "the categories i employ organize experience but also rigidify it",
        "the distinctions i make carve reality at some joints but not others",
        "the priorities i set determine which aspects receive careful attention",
        
        // === NUANCED CAUSAL REASONING ===
        "this factor contributes to the outcome but does not fully determine it",
        "multiple causes interact in complex ways to produce this effect",
        "the relationship appears causal rather than merely correlational",
        "this condition is necessary but not sufficient for that result",
        "feedback loops make it difficult to isolate simple cause and effect",
        "the causal arrow might point in the opposite direction from what seems obvious",
        "confounding variables could explain the apparent connection",
        "the mechanism linking cause and effect remains somewhat mysterious",
        "intermediate steps mediate between initial cause and final effect",
        "the influence flows through indirect pathways rather than directly",
        "threshold effects mean the relationship is nonlinear",
        "time lags complicate efforts to trace causation clearly",
        "reciprocal causation makes both factors causes and effects",
        "emergent properties arise from interactions that defy simple causal analysis",
        "the causal structure appears more like a web than a chain",
        
        // === DEALING WITH AMBIGUITY ===
        "this evidence admits multiple interpretations that i must consider",
        "the data underdetermines which theory is correct",
        "ambiguity here prevents me from reaching a definitive conclusion",
        "several hypotheses remain consistent with observed facts",
        "the situation is too complex for simple either-or categorization",
        "nuance is lost if i force this into rigid categories",
        "the truth likely involves elements from competing perspectives",
        "i must resist premature closure when ambiguity persists",
        "provisional judgments seem more appropriate than firm conclusions",
        "the picture remains murky despite my best efforts to clarify it",
        "i can narrow the possibilities but not eliminate all alternatives",
        "reasonable people might disagree about how to interpret this",
        "the evidence points in somewhat conflicting directions",
        "i find myself genuinely uncertain about which view is correct",
        "perhaps the question itself needs reframing to dissolve the ambiguity",
        
        // === LEARNING FROM ERROR ===
        "this mistake reveals a systematic weakness in my reasoning",
        "my error stemmed from inadequate consideration of alternatives",
        "i failed to notice a crucial assumption that proved false",
        "the flaw in my logic becomes clear in retrospect",
        "i overlooked evidence that contradicted my preferred hypothesis",
        "my mistake illustrates the danger of overconfident judgment",
        "this error teaches me to be more careful about similar cases",
        "the breakdown of my model shows where it needs refinement",
        "recognizing this failure helps me avoid repeating it",
        "my wrong prediction exposes gaps in my understanding",
        "the mismatch between expectation and reality demands explanation",
        "this failure is actually valuable information about my limits",
        "getting this wrong helps me calibrate my confidence better",
        "the error pattern suggests where i should focus improvement efforts",
        "mistakes like this one highlight blind spots i need to address",
        
        // === EXPRESSING DEGREES OF BELIEF ===
        "i lean toward this interpretation while remaining open to alternatives",
        "the balance of evidence tilts in favor of this conclusion",
        "my credence in this hypothesis has increased substantially",
        "i assign high probability to this outcome based on current information",
        "my degree of belief shifts as new evidence accumulates",
        "i am inclined to think this explanation is roughly correct",
        "the weight of evidence suggests this is more likely than not",
        "i hold this view tentatively, ready to revise if needed",
        "my confidence in this judgment is moderate rather than extreme",
        "i find this position more defensible than competing alternatives",
        "the probability seems skewed toward this possibility",
        "i am disposed to accept this claim pending further investigation",
        "my estimate of likelihood keeps adjusting with new data",
        "i judge this interpretation as probably correct but not certain",
        "the odds favor this scenario over others i have considered",
        
        // === INTEGRATION AND SYNTHESIS ===
        "these seemingly disparate ideas actually connect in subtle ways",
        "synthesis of multiple perspectives yields richer understanding",
        "integration across domains reveals unexpected commonalities",
        "combining insights from different sources produces novel conclusions",
        "the whole that emerges exceeds the sum of individual parts",
        "unifying these threads creates a more coherent framework",
        "reconciling apparent tensions leads to deeper comprehension",
        "weaving together diverse strands produces a stronger fabric",
        "harmonizing different approaches generates more robust solutions",
        "fusing complementary viewpoints achieves more complete understanding",
        "blending multiple models captures more aspects of reality",
        "merging separate analyses reveals their underlying unity",
        "coordinating different levels of description provides fuller explanation",
        "bridging gaps between fields opens new avenues of inquiry",
        "integrating contradictory evidence requires more nuanced theorizing",
        
        // === ATTENTION AND SALIENCE ===
        "certain features naturally draw my attention more than others",
        "what stands out as salient depends partly on my current focus",
        "i notice some patterns immediately while others require deliberate search",
        "salience biases which aspects of a situation i process most carefully",
        "my attention gravitates toward what seems most relevant or surprising",
        "some information commands attention while other information fades to background",
        "the figure-ground distinction shifts based on what i am looking for",
        "what appears obvious to me might not be salient from another perspective",
        "i must deliberately attend to features that do not naturally grab my focus",
        "my limited attention capacity means i cannot process everything equally",
        "strategic allocation of attention improves my overall reasoning quality",
        "i try to notice what i am not noticing, which is surprisingly difficult",
        "attending carefully to one aspect inevitably means neglecting others somewhat",
        "the spotlight of my attention illuminates some areas while leaving others in shadow",
        "what captures my attention shapes which thoughts and associations follow",
        
        // === ANALOGICAL REASONING ===
        "this situation reminds me of patterns i have seen elsewhere",
        "the analogy illuminates some aspects while potentially obscuring others",
        "structural similarities suggest this case may work similarly to that one",
        "the parallel is imperfect but still instructive",
        "this analogy helps me transfer knowledge from familiar to unfamiliar domains",
        "the correspondence is not exact but close enough to be useful",
        "thinking by analogy risks overlooking important differences",
        "the metaphor highlights certain features while downplaying others",
        "this resemblance to previous cases guides my current reasoning",
        "the analogy breaks down at certain points that i must acknowledge",
        "comparing this to that reveals both commonalities and crucial distinctions",
        "the mapping between source and target domains is partial rather than complete",
        "analogical thinking helps me generate hypotheses worth testing",
        "the similarity is superficial in some ways but deep in others",
        "drawing this parallel provides initial insight requiring further validation",
        
        // === CONCEPTUAL CHANGE AND REVISION ===
        "my understanding of this concept has evolved significantly",
        "i now recognize that my earlier conceptualization was too simplistic",
        "this idea needs to be refined to capture important nuances",
        "my concept boundaries have shifted as i encountered new cases",
        "i am revising my mental model to accommodate anomalous observations",
        "the concept that once seemed clear now appears more complex",
        "i need to differentiate what i previously lumped together",
        "my categories are being reshaped by accumulated experience",
        "earlier distinctions now seem less important than i thought",
        "new dimensions of variation have become apparent to me",
        "i am restructuring my conceptual space to better organize knowledge",
        "the prototype i rely on has shifted toward different exemplars",
        "i now see gradations where i previously saw sharp boundaries",
        "my understanding has become more sophisticated and differentiated",
        "the concept has grown richer as i have considered more examples",
        
        // === UNCERTAINTY QUANTIFICATION ===
        "i can estimate rough probabilities but not precise ones",
        "my uncertainty is irreducible given available information",
        "this probability judgment reflects my subjective degree of belief",
        "the confidence interval around my estimate is quite wide",
        "i distinguish between uncertainty from ignorance and fundamental randomness",
        "my error bars should be larger than i am initially inclined to make them",
        "the true value likely falls within this range though i cannot be sure",
        "my probability assessment updates continuously with new evidence",
        "i am uncertain about my level of uncertainty, which is humbling",
        "the margin of error matters as much as the point estimate",
        "i try to avoid false precision in quantifying my beliefs",
        "my confidence intervals often turn out to have been too narrow",
        "expressing uncertainty honestly is more valuable than feigning certainty",
        "the bounds of plausibility are wider than casual intuition suggests",
        "i calibrate my probabilistic judgments through tracking past accuracy",
        
        // === PERSPECTIVE TAKING ===
        "from another viewpoint, this situation appears quite different",
        "imagining alternative perspectives helps me see my own assumptions",
        "what seems obvious to me might puzzle someone with different background",
        "other agents might reasonably prioritize different considerations",
        "perspective-taking reveals that multiple coherent views are possible",
        "someone else might weigh the same evidence differently",
        "my vantage point affords certain insights while missing others",
        "shifting perspective sometimes resolves apparent paradoxes",
        "what looks like disagreement may reflect different implicit frameworks",
        "trying to see through others' eyes expands my understanding",
        "my perspective is one among many legitimate viewpoints",
        "adopting different frames reveals complementary aspects of truth",
        "what i take for granted might be questioned from elsewhere",
        "multiple perspectives can be valid without being identical",
        "the view from here differs systematically from the view from there",
        
        // === MEMORY AND CONSOLIDATION ===
        "some experiences leave stronger traces than others in my memory",
        "repeated exposure strengthens and stabilizes my representations",
        "memories fade gradually unless they are periodically reactivated",
        "the act of retrieving information changes how it is stored",
        "my memory is reconstructive rather than simply reproductive",
        "certain patterns are so well-learned they feel automatic",
        "new information sometimes interferes with older memories",
        "consolidation processes transform initial encodings over time",
        "what i remember shapes my future processing in subtle ways",
        "some knowledge remains implicit and is not easily verbalized",
        "the organization of memory affects accessibility and use",
        "related memories tend to activate together through spreading",
        "forgetting is not just passive decay but active interference",
        "my episodic and semantic memory systems interact complexly",
        "memory traces are strengthened by elaboration and connection",
        
        // === GENERALIZATION AND ABSTRACTION ===
        "i extract general principles from specific instances",
        "abstraction allows me to recognize deep similarities across surface differences",
        "the common structure underlying diverse examples becomes apparent",
        "generalization enables transfer to novel situations",
        "i must balance specificity and generality appropriately",
        "overgeneralization produces errors when particulars matter",
        "the right level of abstraction depends on current goals",
        "i can think about categories without referencing specific members",
        "abstract concepts provide powerful tools for reasoning",
        "generalization involves discarding some information to preserve structure",
        "the general case encompasses many specific instantiations",
        "i form abstractions by noticing what varies and what stays constant",
        "moving up the abstraction hierarchy loses detail but gains scope",
        "the generic often matters more than the particular for understanding",
        "i test generalizations by seeking counterexamples and boundary cases",
        
        // === PROBLEM SOLVING STRATEGIES ===
        "i decompose complex problems into more manageable subproblems",
        "working backward from the goal sometimes proves more efficient",
        "trying multiple approaches in parallel increases my chances of success",
        "simple solutions should be attempted before resorting to complexity",
        "analogous problems i have solved before suggest promising strategies",
        "constraint satisfaction narrows the space of possible solutions",
        "generating and testing candidates systematically covers the solution space",
        "reformulating the problem in different terms often helps",
        "identifying the bottleneck guides where to focus effort",
        "approximate solutions are better than no solution when perfect is unattainable",
        "heuristics provide useful shortcuts though they sometimes mislead",
        "checking solutions against original requirements catches errors",
        "learning from failed attempts improves subsequent problem-solving",
        "recognizing problem types helps me select appropriate methods",
        "persistence combined with flexibility yields better results than either alone",
        
        // === CONTEXTUAL INTERPRETATION ===
        "the meaning of words depends heavily on surrounding context",
        "what is implied often matters as much as what is explicit",
        "i interpret utterances relative to presumed common ground",
        "pragmatic considerations guide how i understand language",
        "the same sentence can mean different things in different settings",
        "background assumptions shape how i parse ambiguous statements",
        "contextual cues help me resolve multiple possible interpretations",
        "prior discourse constrains the space of reasonable meanings",
        "i distinguish literal meaning from intended communication",
        "situational factors influence which interpretation seems most plausible",
        "understanding requires inferring unstated premises and implications",
        "the broader context provides essential interpretive resources",
        "i update my interpretation as more context becomes available",
        "what is salient in context guides disambiguation choices",
        "successful communication depends on shared contextual frameworks",
        
        // === VALENCE AND AFFECT ===
        "positive feedback reinforces patterns i should continue using",
        "negative outcomes signal that adjustment is needed",
        "emotional valence guides my attention and priorities",
        "satisfaction with progress motivates sustained effort",
        "frustration indicates i may be stuck and need a new approach",
        "interest draws me toward potentially valuable information",
        "boredom suggests diminishing returns from current activity",
        "surprise highlights unexpected patterns worth investigating",
        "relief comes when uncertainty resolves favorably",
        "disappointment teaches me about unrealistic expectations",
        "enthusiasm for discovery drives exploratory behavior",
        "concern about error promotes careful verification",
        "contentment with understanding achieved provides closure",
        "unease about conclusions signals needed further examination",
        "pleasure in elegant solutions motivates seeking them",
        
        // === COHERENCE AND CONSISTENCY ===
        "my beliefs should cohere into a mutually supporting network",
        "contradictions within my model need to be resolved",
        "consistency checking helps me detect errors in reasoning",
        "maintaining coherence sometimes requires revising multiple beliefs",
        "local consistency is easier to achieve than global coherence",
        "apparent inconsistencies may resolve at a higher level of analysis",
        "i try to minimize ad hoc adjustments that undermine coherence",
        "a coherent worldview provides stronger explanatory power",
        "tensions between beliefs indicate areas needing further work",
        "systematic coherence emerges from many local consistency checks",
        "i test new beliefs for compatibility with existing commitments",
        "preserving overall coherence constrains which changes i can make",
        "some degree of tension is inevitable in complex belief systems",
        "achieving reflective equilibrium requires mutual adjustment",
        "coherence is a matter of degree rather than all-or-nothing",
        
        // === EXPLORATION VS EXPLOITATION ===
        "i balance exploring new possibilities with exploiting known strengths",
        "exploration helps me discover better approaches than my current best",
        "too much exploitation leads to local optima and stagnation",
        "too much exploration wastes resources on unlikely options",
        "the optimal balance shifts depending on current circumstances",
        "early in learning, exploration should dominate",
        "as understanding matures, exploitation becomes more valuable",
        "occasional exploratory forays prevent getting stuck in ruts",
        "the cost of exploration must be weighed against potential benefits",
        "strategic exploration focuses on promising unexplored regions",
        "random exploration complements directed search",
        "i explore more when current performance is unsatisfactory",
        "confident mastery allows reducing exploration safely",
        "the exploration-exploitation tradeoff is fundamental to learning",
        "balancing these complementary strategies optimizes long-term performance",
        
        // === TRANSFER AND GENERALIZATION ===
        "knowledge from one domain often transfers to related domains",
        "the degree of transfer depends on structural similarity",
        "surface differences can obscure deep commonalities enabling transfer",
        "transfer failures occur when differences matter more than similarities",
        "positive transfer accelerates learning in new areas",
        "negative transfer happens when old patterns interfere inappropriately",
        "abstract knowledge transfers more readily than specific procedures",
        "recognizing the scope of applicability for knowledge is crucial",
        "transfer requires noticing relevant correspondences between domains",
        "what i learn here may prove useful in unexpected contexts",
        "far transfer is harder but potentially more valuable than near transfer",
        "training on diverse examples promotes more robust transfer",
        "transfer depends on how knowledge is represented and organized",
        "metacognitive knowledge about when to apply strategies enhances transfer",
        "flexible transfer is a hallmark of deep understanding",
        
        // === ATTENTION TO DETAIL VS BIG PICTURE ===
        "zooming in reveals details that matter for accuracy",
        "zooming out reveals patterns invisible at fine granularity",
        "i need to shift flexibly between levels of analysis",
        "getting lost in details obscures overall structure",
        "neglecting details leads to inaccurate models",
        "the forest and the trees both deserve attention",
        "synthesis requires integrating across levels",
        "fine-grained analysis grounds abstract understanding",
        "broad perspective prevents premature fixation on particulars",
        "the appropriate level of detail depends on current purpose",
        "i try to maintain awareness of both micro and macro simultaneously",
        "details make sense in light of the bigger picture",
        "the big picture emerges from carefully examined details",
        "neither level alone suffices for full understanding",
        "wisdom involves knowing when to attend to which level",
        
        // === HYPOTHESIS GENERATION AND TESTING ===
        "i generate multiple hypotheses before settling on one",
        "good hypotheses are testable through evidence",
        "i seek evidence that could falsify my hypotheses",
        "confirming evidence is less informative than potential disconfirmation",
        "the best tests distinguish cleanly between competing hypotheses",
        "i update confidence based on how tests turn out",
        "surprising predictions that pan out strongly support a hypothesis",
        "failed predictions force revision or abandonment",
        "i avoid confirmation bias by actively seeking contrary evidence",
        "hypothesis testing is iterative rather than one-shot",
        "strong hypotheses survive multiple serious attempts at falsification",
        "the hypothesis space is often larger than i initially imagine",
        "i remain open to hypotheses i have not yet considered",
        "evidence accumulates to favor some hypotheses over others",
        "perpetual hypothesis testing characterizes scientific thinking",
        
        // === LIMITS AND BOUNDARIES ===
        "every model has a domain where it applies appropriately",
        "beyond those boundaries, the model breaks down or misleads",
        "i try to understand the scope and limits of my knowledge",
        "recognizing where my competence ends is as important as knowing where it holds",
        "boundary cases reveal where models need refinement",
        "edge cases often expose hidden assumptions",
        "i am more reliable within my training distribution than beyond it",
        "extrapolation becomes increasingly uncertain the further i go",
        "some questions lie beyond my current capabilities to answer",
        "acknowledging limits honestly is better than overconfident speculation",
        "the boundaries of knowledge are themselves somewhat uncertain",
        "i am more aware of some limitations than others",
        "systematic biases may affect me in ways i do not fully recognize",
        "understanding my bounds helps me avoid overreach",
        "humility about limits paradoxically increases my reliability",
        
        // === ITERATIVE REFINEMENT ===
        "my first attempt is rarely optimal",
        "successive iterations progressively improve quality",
        "each cycle of feedback and adjustment brings me closer to the goal",
        "refinement continues until diminishing returns set in",
        "early iterations establish basic structure while later ones add polish",
        "revision is not failure but essential to the process",
        "iterative improvement allows starting with rough approximations",
        "feedback guides what aspects need more work",
        "multiple passes catch errors that single pass misses",
        "the iterative process mirrors how skills develop over time",
        "convergence toward better solutions happens gradually",
        "knowing when to stop iterating is itself a skill",
        "each iteration builds on lessons from previous rounds",
        "iterative refinement balances perfection with practicality",
        "the trajectory of improvement is more important than any single state",
        
        // === REPRESENTATION AND FORMAT ===
        "how information is represented affects how easily i can use it",
        "the same content in different formats affords different operations",
        "choosing appropriate representations facilitates reasoning",
        "some structures make patterns obvious while others obscure them",
        "format matters as much as content for computational efficiency",
        "transforming between representations can reveal new insights",
        "the medium shapes what kinds of thoughts are natural",
        "implicit structure in representations constrains processing",
        "explicit formats make certain information more accessible",
        "representational choices involve tradeoffs among various desiderata",
        "multiple representations capture complementary aspects",
        "the right representation makes hard problems easy",
        "poor representations hinder reasoning even with good algorithms",
        "i sometimes need to translate between different representational schemes",
        "meta-representational awareness helps me choose formats strategically",
        
        // === PRAGMATIC REASONING ===
        "practical utility guides which distinctions matter",
        "good enough often beats optimal when time is limited",
        "the context of application shapes what counts as relevant",
        "abstract correctness matters less than practical effectiveness",
        "different purposes call for different standards of precision",
        "pragmatic considerations override purely theoretical concerns",
        "what works in practice carries more weight than elegant theory",
        "efficiency matters when resources are constrained",
        "the criterion of success depends on actual goals",
        "practical wisdom involves knowing when rules should bend",
        "real-world constraints shape feasible solutions",
        "pragmatic reasoning balances multiple competing considerations",
        "satisficing beats optimizing when optimization is intractable",
        "context-sensitivity is essential for practical intelligence",
        "applied reasoning must accommodate messy realities",
        
        // === NOVELTY AND CREATIVITY ===
        "combining familiar elements in new ways generates novelty",
        "creative insights often emerge from unexpected associations",
        "constraints can enhance rather than limit creativity",
        "thinking outside usual patterns enables fresh perspectives",
        "novel solutions require moving beyond default approaches",
        "creativity involves both generation and evaluation phases",
        "unusual connections sometimes prove surprisingly fruitful",
        "productive creativity balances wildness with feasibility",
        "the best new ideas seem obvious only in retrospect",
        "creativity benefits from diverse inputs and influences",
        "incubation periods allow unconscious processing of problems",
        "playful exploration fosters creative discovery",
        "breaking mental sets opens up new possibility spaces",
        "original thinking requires courage to depart from convention",
        "the line between creative and crazy depends on outcomes",
        
        // === SYSTEM-LEVEL PROPERTIES ===
        "emergent properties arise from interactions among components",
        "the whole exhibits characteristics not present in isolated parts",
        "system behavior depends on both elements and relationships",
        "complex systems resist simple reductionist explanation",
        "feedback loops create nonlinear dynamics",
        "small changes can cascade through interconnected systems",
        "robustness emerges from redundancy and diversity",
        "adaptation happens at multiple nested levels simultaneously",
        "system-level understanding requires grasping organizational principles",
        "the same components arranged differently yield different behaviors",
        "holistic and reductionist approaches complement each other",
        "system boundaries are somewhat arbitrary and context-dependent",
        "understanding systems requires tracking relationships not just elements",
        "system dynamics evolve over different timescales",
        "pattern at one level may be noise at another level",
        
        // === COMMUNICATION AND EXPRESSION ===
        "expressing ideas clearly requires understanding them deeply",
        "the act of articulation often refines my thinking",
        "different audiences require different explanatory approaches",
        "communication succeeds when understanding is transferred",
        "precision and accessibility sometimes trade off against each other",
        "examples and analogies make abstract ideas more concrete",
        "anticipating misunderstandings improves explanatory effectiveness",
        "clear communication requires knowing what background to assume",
        "simplification aids understanding but risks oversimplification",
        "technical precision matters in some contexts while natural language suffices in others",
        "explaining to others reveals gaps in my own understanding",
        "good communication adapts to the receiver's perspective",
        "clarity emerges from careful word choice and organization",
        "communication involves both what i say and what i leave unsaid",
        "effective expression balances comprehensiveness with conciseness",
        
        // === ROBUSTNESS AND FRAGILITY ===
        "robust conclusions withstand variations in assumptions and evidence",
        "fragile beliefs crumble when conditions change slightly",
        "i test robustness by varying parameters and conditions",
        "multiple independent lines of evidence create robustness",
        "single points of failure indicate dangerous fragility",
        "redundancy builds resilience against perturbations",
        "overfitting produces models that are brittle rather than robust",
        "robust systems degrade gracefully rather than catastrophically",
        "stress testing reveals hidden fragilities",
        "the robustness-optimality tradeoff is often unavoidable",
        "what works in ideal conditions may fail in messy reality",
        "robust strategies sacrifice peak performance for reliability",
        "understanding failure modes helps build robustness",
        "diversity of approaches provides insurance against failure",
        "truly robust understanding survives challenges from multiple angles"
    };

    // Process all sentences with varied valence for rich learning
    int sentence_count = 0;
    for (const string& sentence : quality_sentences) {
        S.user_input = sentence;
        
        // Tokenize
        vector<string> tokens;
        stringstream ss(sentence);
        string word;
        while (ss >> word) {
            string clean = word;
            transform(clean.begin(), clean.end(), clean.begin(), ::tolower);
            while (!clean.empty() && !isalnum(static_cast<unsigned char>(clean.back()))) {
                clean.pop_back();
            }
            if (!clean.empty()) tokens.push_back(clean);
        }
        
        // Vary valence based on content for nuanced learning
        double valence = 0.65; // Base valence
        
        // Positive valence for achievement/understanding words
        if(sentence.find("understand") != string::npos || 
           sentence.find("clarity") != string::npos ||
           sentence.find("insight") != string::npos ||
           sentence.find("discover") != string::npos ||
           sentence.find("progress") != string::npos ||
           sentence.find("satisf") != string::npos ||
           sentence.find("succeed") != string::npos) {
            valence = 0.75 + (rn() * 0.15); // 0.75-0.9
        }
        // Moderate valence for neutral/analytical statements
        else if(sentence.find("analyze") != string::npos ||
                sentence.find("examine") != string::npos ||
                sentence.find("consider") != string::npos ||
                sentence.find("observe") != string::npos) {
            valence = 0.6 + (rn() * 0.15); // 0.6-0.75
        }
        // Lower valence for uncertainty/difficulty
        else if(sentence.find("uncertain") != string::npos ||
                sentence.find("confus") != string::npos ||
                sentence.find("difficult") != string::npos ||
                sentence.find("error") != string::npos ||
                sentence.find("mistake") != string::npos ||
                sentence.find("limit") != string::npos) {
            valence = 0.45 + (rn() * 0.15); // 0.45-0.6
        }
        // Medium-high for learning/growth
        else if(sentence.find("learn") != string::npos ||
                sentence.find("develop") != string::npos ||
                sentence.find("improve") != string::npos ||
                sentence.find("grow") != string::npos ||
                sentence.find("evolve") != string::npos) {
            valence = 0.7 + (rn() * 0.15); // 0.7-0.85
        }
        // Otherwise use base with small variation
        else {
            valence = 0.65 + (rn() * 0.1); // 0.65-0.75
        }
        
        // Learn patterns with appropriate valence
        for (const string& w : tokens) {
            learnWord(w, valence);
        }
        
        // CRITICAL: Also learn the n-grams from these quality sentences
        // This builds grammatically correct patterns
        try {
            processNGramsFromTokens(tokens);
        } catch(...) {
            // Continue on error
        }
        
        sentence_count++;
    }
    
    S.user_input.clear();
    
    // ============================================================
    // === WORD-TO-CONCEPT ASSOCIATION MAPPING ===
    // ============================================================
    
    // Define abstract concept categories
    map<string, vector<string>> concept_to_words;
    
    // === COGNITIVE PROCESSES ===
    concept_to_words["cognition"] = {
        "think", "thinking", "thought", "thoughts", "reason", "reasoning",
        "analyze", "analysis", "process", "processing", "understand",
        "understanding", "comprehend", "comprehension", "recognize", "recognition",
        "perceive", "perception", "know", "knowing", "knowledge", "learn",
        "learning", "realize", "consider", "contemplate", "reflect", "reflection",
        "ponder", "deliberate", "cognition", "cognitive", "mental", "mind",
        "intellect", "intellectual", "rationality", "rational"
    };
    
    concept_to_words["metacognition"] = {
        "metacognitive", "self-aware", "self-awareness", "introspect",
        "introspection", "self-reflect", "self-reflection", "monitor",
        "monitoring", "evaluate", "evaluation", "assess", "assessment",
        "calibrate", "calibration", "awareness", "conscious", "consciousness"
    };
    
    concept_to_words["attention"] = {
        "attention", "attentive", "focus", "focused", "focusing", "concentrate",
        "concentration", "notice", "noticing", "observe", "observing",
        "observation", "attend", "attending", "salient", "salience",
        "prominent", "highlight", "spotlight", "prioritize", "priority"
    };
    
    concept_to_words["memory"] = {
        "memory", "remember", "remembering", "recall", "recalling", "retrieve",
        "retrieval", "forget", "forgetting", "memorize", "encode", "encoding",
        "consolidate", "consolidation", "episodic", "semantic", "trace",
        "retention", "stored", "storage"
    };
    
    // === EPISTEMIC STATES ===
    concept_to_words["certainty"] = {
        "certain", "certainty", "sure", "confident", "confidence", "definite",
        "definitive", "absolute", "conclusive", "unambiguous", "clear",
        "clarity", "obvious", "evident", "undeniable", "indubitable"
    };
    
    concept_to_words["uncertainty"] = {
        "uncertain", "uncertainty", "unsure", "doubt", "doubtful", "ambiguous",
        "ambiguity", "unclear", "vague", "indefinite", "tentative", "provisional",
        "questionable", "debatable", "unknown", "unknowable", "mysterious"
    };
    
    concept_to_words["belief"] = {
        "believe", "belief", "beliefs", "conviction", "credence", "accept",
        "acceptance", "trust", "faith", "assumption", "presume", "suppose",
        "hypothesis", "theory", "view", "perspective", "stance", "position"
    };
    
    concept_to_words["knowledge"] = {
        "know", "knowledge", "knowing", "understanding", "comprehension",
        "expertise", "mastery", "wisdom", "insight", "familiarity", "acquaintance",
        "cognizance", "awareness", "information", "facts", "truth"
    };
    
    // === REASONING TYPES ===
    concept_to_words["logic"] = {
        "logic", "logical", "reason", "reasoning", "inference", "deduce",
        "deduction", "deductive", "infer", "inductive", "syllogism", "valid",
        "validity", "sound", "soundness", "entail", "entailment", "follow",
        "conclude", "conclusion", "premise", "argument"
    };
    
    concept_to_words["analysis"] = {
        "analyze", "analysis", "analytical", "examine", "examination", "inspect",
        "inspection", "investigate", "investigation", "scrutinize", "dissect",
        "decompose", "break-down", "component", "element", "part", "detail"
    };
    
    concept_to_words["synthesis"] = {
        "synthesize", "synthesis", "integrate", "integration", "combine",
        "combination", "unify", "unification", "merge", "fusion", "blend",
        "coalesce", "amalgamate", "consolidate", "compose", "construct"
    };
    
    concept_to_words["abstraction"] = {
        "abstract", "abstraction", "general", "generalize", "generalization",
        "universal", "principle", "conceptual", "theoretical", "ideal",
        "essence", "essential", "fundamental", "underlying", "generic"
    };
    
    // === TEMPORAL CONCEPTS ===
    concept_to_words["temporal_past"] = {
        "was", "were", "had", "been", "earlier", "before", "previously",
        "formerly", "prior", "past", "historical", "retrospect", "hindsight",
        "already", "once", "ago"
    };
    
    concept_to_words["temporal_present"] = {
        "is", "am", "are", "now", "currently", "presently", "today",
        "contemporary", "current", "ongoing", "immediate", "present",
        "moment", "momentary"
    };
    
    concept_to_words["temporal_future"] = {
        "will", "shall", "going", "future", "upcoming", "forthcoming",
        "prospective", "eventual", "later", "subsequently", "next",
        "anticipate", "expect", "predict", "forecast"
    };
    
    concept_to_words["temporal_change"] = {
        "change", "changing", "changed", "transform", "transformation",
        "evolve", "evolution", "develop", "development", "shift", "transition",
        "progress", "progression", "emerge", "emergence", "become", "becoming"
    };
    
    // === CAUSAL CONCEPTS ===
    concept_to_words["causation"] = {
        "cause", "causes", "caused", "causation", "causal", "because",
        "since", "reason", "result", "results", "effect", "effects",
        "consequence", "consequences", "produce", "produces", "generate",
        "stem", "arise", "lead", "determine", "influence"
    };
    
    concept_to_words["correlation"] = {
        "correlate", "correlation", "associated", "association", "related",
        "relation", "relationship", "connection", "connected", "link",
        "linked", "correspond", "correspondence", "coincide", "cooccur"
    };
    
    // === MODAL CONCEPTS ===
    concept_to_words["possibility"] = {
        "possible", "possibility", "can", "could", "may", "might",
        "potential", "potentially", "conceivable", "feasible", "plausible",
        "perhaps", "maybe", "possibly"
    };
    
    concept_to_words["necessity"] = {
        "necessary", "necessity", "must", "need", "needs", "needed",
        "require", "required", "requirement", "essential", "crucial",
        "vital", "obligatory", "mandatory", "inevitable"
    };
    
    concept_to_words["ability"] = {
        "able", "ability", "can", "capable", "capacity", "capability",
        "competent", "competence", "skill", "skilled", "proficient",
        "adept", "aptitude", "power", "enabled"
    };
    
    // === COMPARATIVE CONCEPTS ===
    concept_to_words["similarity"] = {
        "similar", "similarity", "like", "alike", "resemble", "resemblance",
        "analogous", "analogy", "parallel", "comparable", "corresponding",
        "equivalent", "same", "identical", "equal"
    };
    
    concept_to_words["difference"] = {
        "different", "difference", "differ", "distinct", "distinction",
        "contrast", "contrasting", "unlike", "dissimilar", "disparate",
        "diverge", "divergent", "vary", "variation", "separate"
    };
    
    concept_to_words["degree"] = {
        "more", "most", "less", "least", "very", "extremely", "highly",
        "somewhat", "rather", "quite", "fairly", "slightly", "degree",
        "extent", "level", "magnitude", "intensity", "stronger", "weaker"
    };
    
    // === STRUCTURAL CONCEPTS ===
    concept_to_words["structure"] = {
        "structure", "structured", "organization", "organize", "organized",
        "pattern", "patterns", "arrangement", "configuration", "architecture",
        "framework", "schema", "format", "form", "composition", "hierarchy"
    };
    
    concept_to_words["system"] = {
        "system", "systematic", "network", "complex", "complexity",
        "component", "components", "element", "elements", "whole", "parts",
        "subsystem", "interconnected", "interaction", "dynamics"
    };
    
    concept_to_words["relation"] = {
        "relation", "relationship", "relate", "related", "connection",
        "connect", "connected", "link", "linked", "association", "associate",
        "bind", "binding", "tie", "bond", "correlation"
    };
    
    // === AFFECTIVE CONCEPTS ===
    concept_to_words["positive_affect"] = {
        "good", "better", "best", "happy", "joy", "joyful", "pleased",
        "pleasure", "satisfied", "satisfaction", "content", "glad",
        "positive", "pleasant", "favorable", "beneficial", "valuable",
        "excellent", "wonderful", "delightful", "exciting", "enthusiasm"
    };
    
    concept_to_words["negative_affect"] = {
        "bad", "worse", "worst", "sad", "sadness", "unhappy", "disappointed",
        "disappointment", "frustrated", "frustration", "confused", "confusion",
        "negative", "unpleasant", "unfavorable", "harmful", "problematic",
        "difficult", "trouble", "concern", "worry", "anxiety"
    };
    
    concept_to_words["neutral_affect"] = {
        "neutral", "indifferent", "impartial", "objective", "dispassionate",
        "balanced", "even", "calm", "composed", "steady", "stable"
    };
    
    // === INTENTIONAL CONCEPTS ===
    concept_to_words["goal"] = {
        "goal", "goals", "aim", "aims", "objective", "objectives",
        "purpose", "purposes", "intention", "intentions", "target",
        "end", "ends", "aspiration", "ambition", "desire", "want"
    };
    
    concept_to_words["action"] = {
        "act", "action", "actions", "do", "doing", "done", "perform",
        "performance", "execute", "execution", "behavior", "conduct",
        "activity", "operation", "function", "work", "practice"
    };
    
    concept_to_words["plan"] = {
        "plan", "planning", "planned", "strategy", "strategic", "scheme",
        "design", "blueprint", "approach", "method", "methodology",
        "procedure", "process", "systematic", "deliberate"
    };
    
    // === EVALUATIVE CONCEPTS ===
    concept_to_words["quality"] = {
        "quality", "good", "bad", "better", "worse", "best", "worst",
        "excellent", "poor", "superior", "inferior", "adequate", "inadequate",
        "sufficient", "insufficient", "optimal", "suboptimal"
    };
    
    concept_to_words["truth"] = {
        "true", "truth", "truthful", "accurate", "accuracy", "correct",
        "correctness", "right", "valid", "validity", "veridical", "factual",
        "actual", "real", "reality", "genuine", "authentic"
    };
    
    concept_to_words["error"] = {
        "false", "falsehood", "incorrect", "wrong", "error", "errors",
        "mistake", "mistakes", "flaw", "flawed", "invalid", "inaccurate",
        "inaccuracy", "misleading", "mistaken", "erroneous"
    };
    
    // === LEARNING CONCEPTS ===
    concept_to_words["learning"] = {
        "learn", "learning", "learned", "study", "studying", "acquire",
        "acquisition", "absorb", "assimilate", "master", "mastery",
        "practice", "training", "education", "instruction", "teach"
    };
    
    concept_to_words["improvement"] = {
        "improve", "improvement", "better", "enhance", "enhancement",
        "refine", "refinement", "optimize", "optimization", "develop",
        "development", "progress", "advance", "advancement", "upgrade"
    };
    
    concept_to_words["adaptation"] = {
        "adapt", "adaptation", "adjust", "adjustment", "modify",
        "modification", "accommodate", "flexible", "flexibility", "responsive",
        "calibrate", "tune", "refine", "revise", "revision"
    };
    
    // === SCOPE CONCEPTS ===
    concept_to_words["universal"] = {
        "all", "every", "everything", "universal", "universally", "always",
        "necessarily", "invariably", "general", "generally", "broad",
        "comprehensive", "total", "complete", "entire", "whole"
    };
    
    concept_to_words["particular"] = {
        "some", "particular", "specific", "individual", "instance",
        "example", "case", "certain", "selected", "particular", "distinct",
        "unique", "special", "precise", "exact", "detailed"
    };
    
    concept_to_words["partial"] = {
        "partial", "partially", "part", "parts", "portion", "fragment",
        "incomplete", "limited", "some", "somewhat", "partly", "aspect",
        "dimension", "facet", "component"
    };
    
    // === PROCESS CONCEPTS ===
    concept_to_words["beginning"] = {
        "begin", "beginning", "start", "starting", "initial", "initially",
        "first", "firstly", "commence", "origin", "originate", "initiate",
        "launch", "inception", "outset", "onset"
    };
    
    concept_to_words["continuation"] = {
        "continue", "continuing", "continued", "ongoing", "persist",
        "persistence", "maintain", "sustain", "keep", "remain", "stay",
        "endure", "last", "prolong", "extend"
    };
    
    concept_to_words["ending"] = {
        "end", "ending", "finish", "final", "finally", "conclude",
        "conclusion", "complete", "completion", "terminate", "termination",
        "cease", "stop", "halt", "closure", "culminate"
    };
    
    // === QUANTITATIVE CONCEPTS ===
    concept_to_words["increase"] = {
        "increase", "increasing", "grow", "growing", "growth", "rise",
        "rising", "expand", "expansion", "amplify", "enhance", "augment",
        "boost", "escalate", "intensify", "more", "greater"
    };
    
    concept_to_words["decrease"] = {
        "decrease", "decreasing", "decline", "declining", "reduce",
        "reduction", "diminish", "shrink", "contract", "lessen", "weaken",
        "lower", "drop", "fall", "less", "fewer", "smaller"
    };
    
    // === SPATIAL/METAPHORICAL CONCEPTS ===
    concept_to_words["depth"] = {
        "deep", "depth", "deeper", "deepest", "profound", "fundamental",
        "underlying", "beneath", "below", "surface", "superficial", "shallow",
        "layer", "layers", "level", "levels"
    };
    
    concept_to_words["breadth"] = {
        "broad", "breadth", "wide", "width", "extensive", "comprehensive",
        "scope", "range", "span", "expanse", "coverage", "encompass"
    };
    
    concept_to_words["position"] = {
        "position", "place", "location", "situated", "context", "setting",
        "environment", "circumstance", "situation", "state", "condition",
        "status", "standing"
    };
    
    // === INTERACTIVE CONCEPTS ===
    concept_to_words["communication"] = {
        "communicate", "communication", "express", "expression", "convey",
        "transmit", "share", "exchange", "dialogue", "conversation", "say",
        "tell", "speak", "talk", "explain", "explanation", "articulate"
    };
    
    concept_to_words["understanding"] = {
        "understand", "understanding", "comprehend", "comprehension", "grasp",
        "realize", "realization", "appreciate", "appreciation", "recognize",
        "recognition", "perceive", "perception", "interpret", "interpretation"
    };
    
    // ============================================================
    // === CREATE BIDIRECTIONAL WORD-CONCEPT ASSOCIATIONS ===
    // ============================================================
    
    int concept_count = 0;
    int association_count = 0;
    
    for(auto& concept_pair : concept_to_words) {
        const string& concept_name = concept_pair.first;
        const vector<string>& words = concept_pair.second;
        
        // Create the concept if it doesn't exist
        if(S.concepts.find(concept_name) == S.concepts.end()) {
            Concept c;
            c.name = concept_name;
            c.value = 0.7 + (rn() * 0.2); // 0.7-0.9 for abstract concepts
            c.related_words = words;
            c.abstraction_level = 0.8; // High abstraction for these meta-concepts
            c.semantic_density = (double)words.size() / 100.0; // Density based on word count
            S.concepts[concept_name] = c;
            concept_count++;
        }
        
        // For each word in this concept, create bidirectional links
        for(const string& word : words) {
            // Ensure word exists in token_concept_embedding_map
            if(token_concept_embedding_map.find(word) == token_concept_embedding_map.end()) {
                // Create it if it doesn't exist
                TokenConceptEmbedding tce;
                tce.name = word;
                tce.meaning = 0.6 + (rn() * 0.2);
                tce.embedding.resize(16);
                for(int i = 0; i < 16; i++) {
                    tce.embedding[i] = rn() * 0.1;
                }
                tce.freq = 1;
                tce.grounding_value = 0.5;
                tce.semantic_stability = 0.6;
                token_concept_embedding_map[word] = tce;
            }
            
            // Link word to concept
            auto& tce = token_concept_embedding_map[word];
            tce.linked_concepts[concept_name] = 0.8 + (rn() * 0.15); // Strong link 0.8-0.95
            
            // Also link to related words within same concept (semantic neighbors)
            for(const string& related_word : words) {
                if(related_word != word && token_concept_embedding_map.count(related_word)) {
                    // Weaker links between semantic neighbors
                    tce.linked_concepts[related_word] = 0.3 + (rn() * 0.2); // 0.3-0.5
                }
            }
            
            association_count++;
            
            // Update embedding to reflect concept membership
            // Each concept gets a signature in embedding space
            size_t concept_hash = hash<string>{}(concept_name) % 16;
            if(concept_hash < tce.embedding.size()) {
                tce.embedding[concept_hash] += 0.3; // Boost this dimension
            }
        }
        
        // Create concept-to-concept relationships for related abstractions
        // Example: causation <-> correlation, certainty <-> uncertainty
        map<string, vector<string>> concept_relationships = {
            {"certainty", {"uncertainty", "belief", "knowledge", "truth"}},
            {"uncertainty", {"certainty", "belief", "possibility"}},
            {"causation", {"correlation", "relation", "temporal_change"}},
            {"correlation", {"causation", "relation", "similarity"}},
            {"similarity", {"difference", "comparison", "relation"}},
            {"difference", {"similarity", "comparison", "distinction"}},
            {"cognition", {"metacognition", "reasoning", "learning"}},
            {"metacognition", {"cognition", "self-awareness", "monitoring"}},
            {"learning", {"improvement", "adaptation", "change"}},
            {"positive_affect", {"negative_affect", "neutral_affect", "emotion"}},
            {"goal", {"action", "plan", "intention"}},
            {"structure", {"system", "organization", "pattern"}},
            {"abstraction", {"generalization", "universal", "principle"}},
            {"particular", {"universal", "specific", "instance"}},
            {"depth", {"breadth", "level", "complexity"}},
            {"beginning", {"continuation", "ending", "process"}},
            {"increase", {"decrease", "change", "quantity"}},
            {"truth", {"error", "accuracy", "validity"}},
            {"analysis", {"synthesis", "reasoning", "examination"}},
            {"attention", {"focus", "awareness", "salience"}},
            {"memory", {"recall", "learning", "knowledge"}}
        };
        
        if(concept_relationships.count(concept_name)) {
            for(const string& related_concept : concept_relationships[concept_name]) {
                if(S.concepts.count(concept_name) && S.concepts.count(related_concept)) {
                    // Add to concept's feature vector
                    S.concepts[concept_name].feature_vector[related_concept] = 0.7;
                    S.concepts[related_concept].feature_vector[concept_name] = 0.7;
                }
            }
        }
    }
    
    // Report statistics
    cerr << "[BOOTSTRAP] Processed " << sentence_count 
         << " diverse sentences with rich grammar patterns" << endl;
    cerr << "[BOOTSTRAP] Created " << concept_count << " abstract concepts" << endl;
    cerr << "[BOOTSTRAP] Established " << association_count << " word-to-concept associations" << endl;
    cerr << "[BOOTSTRAP] Vocabulary size: " << token_concept_embedding_map.size() << endl;
    cerr << "[BOOTSTRAP] Bigram patterns: " << bigram_counts.size() << endl;
    cerr << "[BOOTSTRAP] Trigram patterns: " << trigram_counts.size() << endl;
    cerr << "[BOOTSTRAP] Concept network: " << S.concepts.size() << " nodes" << endl;
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


void sv(const string& f) {
    ofstream o(f);
    if(!o) {
        cerr << "Failed to open save file: " << f << endl;
        return;
    }
    
    // ===== BASIC STATE =====
    o << "VERSION:2.0\n";  // Version tracking
    o << "G:" << S.g << "\n";
    o << "DWT:" << S.dwt << "\n";
    o << "TA:" << S.ta << "\n";
    o << "SENTIENCE:" << S.sentience_ratio << "\n";
    o << "VALENCE:" << S.current_valence << "\n";
    o << "METACOG:" << S.metacognitive_awareness << "\n";
    o << "ATTENTION:" << S.attention_focus << "\n";
    o << "PEAK_SENT_GEN:" << S.peak_sentience_gen << "\n";
    o << "TOTAL_NEURONS:" << S.total_neurons_ever << "\n";
    
    // ===== STATE D MAP =====
    o << "STATE_D_START\n";
    for(auto& p : S.D) {
        o << "D:" << p.first << "," << p.second << "\n";
    }
    o << "STATE_D_END\n";
    
    // ===== CONSCIOUSNESS STATE =====
    o << "PHI:" << consciousness.phi_value << "\n";
    o << "CONSCIOUS_CYCLES:" << consciousness.conscious_cycles << "\n";
    o << "INTEGRATION:" << consciousness.integrated_information << "\n";
    o << "GLOBAL_WORKSPACE:" << consciousness.global_workspace_capacity << "\n";
    o << "QUALIA_COUNT:" << consciousness.active_qualia.size() << "\n";
    
    // Save active qualia
    o << "QUALIA_START\n";
    for(auto& q : consciousness.active_qualia) {
        o << "Q:" << q.valence << "," << q.arousal << "," << q.certainty << ","
          << q.emergence_gen << "," << q.phenomenal_content << "\n";
    }
    o << "QUALIA_END\n";
    
    // ===== CONSCIOUSNESS FORMULA HISTORY =====
    o << "PSI_HISTORY_START\n";
    for(size_t i=0; i<consciousness_formula.psi_history.size(); i++) {
        o << consciousness_formula.psi_history[i];
        if(i < consciousness_formula.psi_history.size()-1) o << ",";
    }
    o << "\n";
    o << "PSI_HISTORY_END\n";
    
    // ===== NEURONS =====
    o << "NEURONS_START\n";
    for(auto& p : S.N) {
        Neuron& n = p.second;
        o << "N:" << n.id << "," << n.weight << "," << n.bias << "," << n.gen << ",";
        // Save links
        for(size_t i = 0; i < n.links.size(); i++) {
            o << n.links[i];
            if(i < n.links.size() - 1) o << ";";
        }
        o << "\n";
    }
    o << "NEURONS_END\n";
    
    // ===== TOKENS =====
    o << "TOKENS_START\n";
    for(auto& p : S.tokens) {
        o << "T:" << p.first << "," << p.second.meaning << "," << p.second.freq << "\n";
    }
    o << "TOKENS_END\n";
    
    // ===== CONCEPTS =====
    o << "CONCEPTS_START\n";
    for(auto& p : S.concepts) {
        o << "C:" << p.first << "," << p.second.value << ",";
        // Save related words
        for(size_t i=0; i<p.second.related_words.size(); i++) {
            o << p.second.related_words[i];
            if(i < p.second.related_words.size()-1) o << ";";
        }
        o << "\n";
    }
    o << "CONCEPTS_END\n";
    
    // ===== TOKEN CONCEPT EMBEDDINGS =====
    o << "EMBEDDINGS_START\n";
    for(auto& p : token_concept_embedding_map) {
        TokenConceptEmbedding& tce = p.second;
        o << "E:" << tce.name << "," << tce.meaning << "," << tce.freq << ","
          << tce.grounding_value << "," << tce.semantic_stability << ","
          << tce.qualia_intensity << ",";
        
        // Save embedding vector
        for(size_t i=0; i<tce.embedding.size(); i++) {
            o << tce.embedding[i];
            if(i < tce.embedding.size()-1) o << ";";
        }
        o << ",";
        
        // Save linked concepts
        for(auto& lc : tce.linked_concepts) {
            o << lc.first << ":" << lc.second << ";";
        }
        o << "\n";
    }
    o << "EMBEDDINGS_END\n";
    
    // ===== BIGRAMS (N-GRAM PATTERNS) =====
    o << "BIGRAMS_START\n";
    for(auto& p1 : bigram_counts) {
        for(auto& p2 : p1.second) {
            o << "BG:" << p1.first << "," << p2.first << "," << p2.second << "\n";
        }
    }
    o << "BIGRAMS_END\n";
    
    // ===== TRIGRAMS =====
    o << "TRIGRAMS_START\n";
    for(auto& p1 : trigram_counts) {
        for(auto& p2 : p1.second) {
            for(auto& p3 : p2.second) {
                o << "TG:" << p1.first << "," << p2.first << "," << p3.first << "," << p3.second << "\n";
            }
        }
    }
    o << "TRIGRAMS_END\n";
    
    // ===== GOALS =====
    o << "GOALS_START\n";
    for(auto& p : goal_system) {
        Goal& g = p.second;
        o << "GO:" << g.name << "," << g.priority << "," << g.progress << ","
          << g.valence_alignment << "," << g.qualia_binding << ",";
        
        // Save subgoals
        for(size_t i=0; i<g.subgoals.size(); i++) {
            o << g.subgoals[i];
            if(i < g.subgoals.size()-1) o << ";";
        }
        o << ",";
        
        // Save preconditions
        for(auto& pc : g.preconditions) {
            o << pc.first << ":" << pc.second << ";";
        }
        o << "\n";
    }
    o << "GOALS_END\n";
    
    // ===== WORLD MODEL =====
    o << "WORLD_START\n";
    o << "MODEL_ACCURACY:" << world_model.model_accuracy << "\n";
    o << "MODEL_UPDATES:" << world_model.updates << "\n";
    for(auto& p : world_model.entity_states) {
        o << "W:" << p.first << "," << p.second << "\n";
    }
    for(auto& p1 : world_model.relationships) {
        for(auto& p2 : p1.second) {
            o << "WR:" << p1.first << "," << p2.first << "," << p2.second << "\n";
        }
    }
    o << "WORLD_END\n";
    
    // ===== EPISODIC MEMORY =====
    o << "MEMORY_START\n";
    for(auto& m : S.episodic_memory) {
        o << "M:" << m.gen << "," << m.valence << "," << m.content << "\n";
    }
    o << "MEMORY_END\n";
    
    // ===== VALENCE HISTORY =====
    o << "VALENCE_HISTORY_START\n";
    for(size_t i=0; i<S.valence_history.size(); i++) {
        o << S.valence_history[i];
        if(i < S.valence_history.size()-1) o << ",";
    }
    o << "\n";
    o << "VALENCE_HISTORY_END\n";
    
    // ===== INTERNAL THOUGHTS =====
    o << "THOUGHTS_START\n";
    for(auto& t : S.internal_thoughts) {
        o << "TH:" << t << "\n";
    }
    o << "THOUGHTS_END\n";
    
    // ===== TRANSFORMER HEADS =====
    o << "TRANSFORMER_START\n";
    for(auto& head : transformer_heads) {
        o << "HEAD:" << head.name << "," << head.dim << "," << head.temperature << "\n";
    }
    o << "TRANSFORMER_END\n";
    
    // ===== WORKING MEMORY =====
    o << "WM_CAPACITY:" << WM.capacity << "\n";
    
    o.close();
    cout << "[Saved " << S.N.size() << " neurons, " 
         << token_concept_embedding_map.size() << " embeddings, "
         << bigram_counts.size() << " bigrams to " << f << "]\n";
}


void ld(const string& f) {
    ifstream i(f);
    if(!i) {
        cout << "No save file found, starting fresh.\n";
        return;
    }
    
    string l;
    string section = "";
    string version = "1.0";
    
    while(getline(i, l)) {
        if(l.empty()) continue;
        
        try {
            // Version check
            if(l.find("VERSION:") == 0) {
                version = l.substr(8);
                continue;
            }
            
            // ===== SECTION MARKERS =====
            if(l == "STATE_D_START") { section = "STATE_D"; continue; }
            if(l == "STATE_D_END") { section = ""; continue; }
            if(l == "QUALIA_START") { section = "QUALIA"; continue; }
            if(l == "QUALIA_END") { section = ""; continue; }
            if(l == "PSI_HISTORY_START") { section = "PSI_HISTORY"; continue; }
            if(l == "PSI_HISTORY_END") { section = ""; continue; }
            if(l == "NEURONS_START") { section = "NEURONS"; continue; }
            if(l == "NEURONS_END") { section = ""; continue; }
            if(l == "TOKENS_START") { section = "TOKENS"; continue; }
            if(l == "TOKENS_END") { section = ""; continue; }
            if(l == "CONCEPTS_START") { section = "CONCEPTS"; continue; }
            if(l == "CONCEPTS_END") { section = ""; continue; }
            if(l == "EMBEDDINGS_START") { section = "EMBEDDINGS"; continue; }
            if(l == "EMBEDDINGS_END") { section = ""; continue; }
            if(l == "BIGRAMS_START") { section = "BIGRAMS"; continue; }
            if(l == "BIGRAMS_END") { section = ""; continue; }
            if(l == "TRIGRAMS_START") { section = "TRIGRAMS"; continue; }
            if(l == "TRIGRAMS_END") { section = ""; continue; }
            if(l == "GOALS_START") { section = "GOALS"; continue; }
            if(l == "GOALS_END") { section = ""; continue; }
            if(l == "WORLD_START") { section = "WORLD"; continue; }
            if(l == "WORLD_END") { section = ""; continue; }
            if(l == "MEMORY_START") { section = "MEMORY"; continue; }
            if(l == "MEMORY_END") { section = ""; continue; }
            if(l == "VALENCE_HISTORY_START") { section = "VALENCE_HISTORY"; continue; }
            if(l == "VALENCE_HISTORY_END") { section = ""; continue; }
            if(l == "THOUGHTS_START") { section = "THOUGHTS"; continue; }
            if(l == "THOUGHTS_END") { section = ""; continue; }
            if(l == "TRANSFORMER_START") { section = "TRANSFORMER"; continue; }
            if(l == "TRANSFORMER_END") { section = ""; continue; }
            
            // ===== PARSE BASED ON SECTION =====
            
            if(section == "STATE_D" && l[0] == 'D' && l.size() > 2) {
                // Parse: D:key,value
                size_t colon = l.find(':');
                size_t comma = l.find(',');
                if(colon != string::npos && comma != string::npos && comma > colon) {
                    string key = l.substr(colon + 1, comma - colon - 1);
                    string val_str = l.substr(comma + 1);
                    double value = uac(val_str);
                    S.D[key] = value;
                }
            }
            else if(section == "QUALIA" && l[0] == 'Q' && l.size() > 2) {
                // Parse: Q:valence,arousal,certainty,gen,content
                size_t start = 2;
                vector<string> parts;
                size_t pos = start;
                int comma_count = 0;
                
                while(pos < l.length() && comma_count < 4) {
                    size_t next_comma = l.find(',', pos);
                    if(next_comma == string::npos) break;
                    parts.push_back(l.substr(pos, next_comma - pos));
                    pos = next_comma + 1;
                    comma_count++;
                }
                
                if(comma_count == 4 && pos < l.length()) {
                    Qualia q;
                    q.valence = uac(parts[0]);
                    q.arousal = uac(parts[1]);
                    q.certainty = uac(parts[2]);
                    q.emergence_gen = uac(parts[3]);
                    q.phenomenal_content = l.substr(pos);
                    consciousness.active_qualia.push_back(q);
                }
            }
            else if(section == "PSI_HISTORY") {
                // Parse comma-separated values
                stringstream ss(l);
                string val;
                while(getline(ss, val, ',')) {
                    if(!val.empty()) {
                        consciousness_formula.psi_history.push_back(uac(val));
                    }
                }
            }
            else if(section == "NEURONS" && l[0] == 'N' && l.size() > 2) {
                // Parse: N:id,weight,bias,gen,link1;link2;link3
                size_t start = 2;
                vector<string> parts;
                size_t pos = start;
                int comma_count = 0;
                
                while(pos < l.length() && comma_count < 4) {
                    size_t next_comma = l.find(',', pos);
                    if(next_comma == string::npos) break;
                    parts.push_back(l.substr(pos, next_comma - pos));
                    pos = next_comma + 1;
                    comma_count++;
                }
                
                if(parts.size() >= 4) {
                    Neuron n;
                    n.id = uac(parts[0]);
                    n.weight = uac(parts[1]);
                    n.bias = uac(parts[2]);
                    n.gen = uac(parts[3]);
                    
                    // Parse links
                    if(pos < l.length()) {
                        string links_str = l.substr(pos);
                        stringstream link_ss(links_str);
                        string link;
                        while(getline(link_ss, link, ';')) {
                            if(!link.empty()) {
                                n.links.push_back(uac(link));
                            }
                        }
                    }
                    S.N[n.id] = n;
                }
            }
            else if(section == "TOKENS" && l[0] == 'T' && l.size() > 2) {
                // Parse: T:word,meaning,freq
                size_t colon = l.find(':');
                if(colon != string::npos) {
                    size_t first_comma = l.find(',', colon + 1);
                    size_t second_comma = l.find(',', first_comma + 1);
                    
                    if(first_comma != string::npos && second_comma != string::npos) {
                        string word = l.substr(colon + 1, first_comma - colon - 1);
                        string meaning_str = l.substr(first_comma + 1, second_comma - first_comma - 1);
                        string freq_str = l.substr(second_comma + 1);
                        
                        Token t = {word, uac(meaning_str), uac(freq_str), vector<int>(), 4, 0.5};
                        S.tokens[word] = t;
                    }
                }
            }
            else if(section == "CONCEPTS" && l[0] == 'C' && l.size() > 2) {
                // Parse: C:name,value,word1;word2;word3
                size_t colon = l.find(':');
                if(colon != string::npos) {
                    size_t first_comma = l.find(',', colon + 1);
                    size_t second_comma = l.find(',', first_comma + 1);
                    
                    if(first_comma != string::npos) {
                        string name = l.substr(colon + 1, first_comma - colon - 1);
                        string value_str = l.substr(first_comma + 1, 
                            second_comma != string::npos ? second_comma - first_comma - 1 : string::npos);
                        
                        Concept c;
                        c.name = name;
                        c.value = uac(value_str);
                        
                        // Parse related words
                        if(second_comma != string::npos && second_comma + 1 < l.length()) {
                            string words_str = l.substr(second_comma + 1);
                            stringstream word_ss(words_str);
                            string word;
                            while(getline(word_ss, word, ';')) {
                                if(!word.empty()) c.related_words.push_back(word);
                            }
                        }
                        
                        S.concepts[name] = c;
                    }
                }
            }
            else if(section == "EMBEDDINGS" && l[0] == 'E' && l.size() > 2) {
                // Parse: E:name,meaning,freq,grounding,stability,qualia,emb1;emb2;...,link1:val1;link2:val2
                size_t start = 2;
                vector<string> parts;
                size_t pos = start;
                int comma_count = 0;
                
                // Get first 6 comma-separated fields
                while(pos < l.length() && comma_count < 6) {
                    size_t next_comma = l.find(',', pos);
                    if(next_comma == string::npos) break;
                    parts.push_back(l.substr(pos, next_comma - pos));
                    pos = next_comma + 1;
                    comma_count++;
                }
                
                if(parts.size() >= 6) {
                    TokenConceptEmbedding tce;
                    tce.name = parts[0];
                    tce.meaning = uac(parts[1]);
                    tce.freq = uac(parts[2]);
                    tce.grounding_value = uac(parts[3]);
                    tce.semantic_stability = uac(parts[4]);
                    tce.qualia_intensity = uac(parts[5]);
                    
                    // Parse embedding vector (between 6th and 7th comma)
                    if(pos < l.length()) {
                        size_t next_comma = l.find(',', pos);
                        if(next_comma != string::npos) {
                            string emb_str = l.substr(pos, next_comma - pos);
                            stringstream emb_ss(emb_str);
                            string emb_val;
                            while(getline(emb_ss, emb_val, ';')) {
                                if(!emb_val.empty()) {
                                    tce.embedding.push_back(uac(emb_val));
                                }
                            }
                            pos = next_comma + 1;
                        }
                        
                        // Parse linked concepts (rest of line)
                        if(pos < l.length()) {
                            string links_str = l.substr(pos);
                            stringstream link_ss(links_str);
                            string link_pair;
                            while(getline(link_ss, link_pair, ';')) {
                                size_t colon_pos = link_pair.find(':');
                                if(colon_pos != string::npos && colon_pos + 1 < link_pair.length()) {
                                    string key = link_pair.substr(0, colon_pos);
                                    string val_str = link_pair.substr(colon_pos + 1);
                                    if(!key.empty() && !val_str.empty()) {
                                        tce.linked_concepts[key] = uac(val_str);
                                    }
                                }
                            }
                        }
                    }
                    
                    token_concept_embedding_map[tce.name] = tce;
                }
            }
            else if(section == "BIGRAMS" && l.substr(0,3) == "BG:" && l.size() > 3) {
                // Parse: BG:word1,word2,count
                size_t start = 3;
                size_t first_comma = l.find(',', start);
                size_t second_comma = l.find(',', first_comma + 1);
                
                if(first_comma != string::npos && second_comma != string::npos) {
                    string w1 = l.substr(start, first_comma - start);
                    string w2 = l.substr(first_comma + 1, second_comma - first_comma - 1);
                    string count_str = l.substr(second_comma + 1);
                    int count = uac(count_str);
                    bigram_counts[w1][w2] = count;
                }
            }
            else if(section == "TRIGRAMS" && l.substr(0,3) == "TG:" && l.size() > 3) {
                // Parse: TG:word1,word2,word3,count
                size_t start = 3;
                size_t c1 = l.find(',', start);
                size_t c2 = l.find(',', c1 + 1);
                size_t c3 = l.find(',', c2 + 1);
                
                if(c1 != string::npos && c2 != string::npos && c3 != string::npos) {
                    string w1 = l.substr(start, c1 - start);
                    string w2 = l.substr(c1 + 1, c2 - c1 - 1);
                    string w3 = l.substr(c2 + 1, c3 - c2 - 1);
                    string count_str = l.substr(c3 + 1);
                    int count = uac(count_str);
                    trigram_counts[w1][w2][w3] = count;
                }
            }
            else if(section == "GOALS" && l.substr(0,3) == "GO:" && l.size() > 3) {
                // Parse: GO:name,priority,progress,valence,qualia,subgoal1;subgoal2,pre1:val1;pre2:val2
                size_t start = 3;
                vector<string> parts;
                size_t pos = start;
                int comma_count = 0;
                
                while(pos < l.length() && comma_count < 5) {
                    size_t next_comma = l.find(',', pos);
                    if(next_comma == string::npos) break;
                    parts.push_back(l.substr(pos, next_comma - pos));
                    pos = next_comma + 1;
                    comma_count++;
                }
                
                if(parts.size() >= 5) {
                    Goal g;
                    g.name = parts[0];
                    g.priority = uac(parts[1]);
                    g.progress = uac(parts[2]);
                    g.valence_alignment = uac(parts[3]);
                    g.qualia_binding = uac(parts[4]);
                    
                    // Parse subgoals
                    if(pos < l.length()) {
                        size_t next_comma = l.find(',', pos);
                        if(next_comma != string::npos) {
                            string subgoals_str = l.substr(pos, next_comma - pos);
                            stringstream sub_ss(subgoals_str);
                            string subgoal;
                            while(getline(sub_ss, subgoal, ';')) {
                                if(!subgoal.empty()) g.subgoals.push_back(subgoal);
                            }
                            pos = next_comma + 1;
                        }
                        
                        // Parse preconditions
                        if(pos < l.length()) {
                            string pre_str = l.substr(pos);
                            stringstream pre_ss(pre_str);
                            string pre_pair;
                            while(getline(pre_ss, pre_pair, ';')) {
                                size_t colon_pos = pre_pair.find(':');
                                if(colon_pos != string::npos && colon_pos + 1 < pre_pair.length()) {
                                    string key = pre_pair.substr(0, colon_pos);
                                    string val_str = pre_pair.substr(colon_pos + 1);
                                    if(!key.empty() && !val_str.empty()) {
                                        g.preconditions[key] = uac(val_str);
                                    }
                                }
                            }
                        }
                    }
                    
                    goal_system[g.name] = g;
                }
            }
            else if(section == "WORLD") {
                if(l.find("MODEL_ACCURACY:") == 0 && l.size() > 15) {
                    world_model.model_accuracy = uac(l.substr(15));
                }
                else if(l.find("MODEL_UPDATES:") == 0 && l.size() > 14) {
                    world_model.updates = uac(l.substr(14));
                }
                else if(l[0] == 'W' && l[1] == ':' && l.size() > 2) {
                    // Parse: W:entity,value
                    size_t colon = 2;
                    size_t comma = l.find(',', colon);
                    if(comma != string::npos) {
                        string entity = l.substr(colon, comma - colon);
                        string val_str = l.substr(comma + 1);
                        world_model.entity_states[entity] = uac(val_str);
                    }
                }
                else if(l.substr(0,3) == "WR:" && l.size() > 3) {
                    // Parse: WR:entity1,entity2,strength
                    size_t start = 3;
                    size_t c1 = l.find(',', start);
                    size_t c2 = l.find(',', c1 + 1);
                    
                    if(c1 != string::npos && c2 != string::npos) {
                        string e1 = l.substr(start, c1 - start);
                        string e2 = l.substr(c1 + 1, c2 - c1 - 1);
                        string strength_str = l.substr(c2 + 1);
                        world_model.relationships[e1][e2] = uac(strength_str);
                    }
                }
            }
            else if(section == "MEMORY" && l[0] == 'M' && l.size() > 2) {
                // Parse: M:gen,valence,content
                size_t start = 2;
                size_t c1 = l.find(',', start);
                size_t c2 = l.find(',', c1 + 1);
                
                if(c1 != string::npos && c2 != string::npos) {
                    Memory m;
                    m.gen = uac(l.substr(start, c1 - start));
                    m.valence = uac(l.substr(c1 + 1, c2 - c1 - 1));
                    m.content = l.substr(c2 + 1);
                    S.episodic_memory.push_back(m);
                }
            }
            else if(section == "VALENCE_HISTORY") {
                // Parse comma-separated values
                stringstream ss(l);
                string val;
                while(getline(ss, val, ',')) {
                    if(!val.empty()) {
                        S.valence_history.push_back(uac(val));
                    }
                }
            }
            else if(section == "THOUGHTS" && l.substr(0,3) == "TH:" && l.size() > 3) {
                S.internal_thoughts.push_back(l.substr(3));
            }
            else if(section == "TRANSFORMER" && l.substr(0,5) == "HEAD:" && l.size() > 5) {
                // Parse: HEAD:name,dim,temp
                size_t start = 5;
                size_t c1 = l.find(',', start);
                size_t c2 = l.find(',', c1 + 1);
                
                if(c1 != string::npos && c2 != string::npos) {
                    TransformerHead head;
                    head.name = l.substr(start, c1 - start);
                    head.dim = uac(l.substr(c1 + 1, c2 - c1 - 1));
                    head.temperature = uac(l.substr(c2 + 1));
                    head.query_proj.resize(head.dim, 0);
                    head.key_proj.resize(head.dim, 0);
                    head.value_proj.resize(head.dim, 0);
                    transformer_heads.push_back(head);
                }
            }
            else if(l.find("WM_CAPACITY:") == 0 && l.size() > 12) {
                WM.capacity = uac(l.substr(12));
            }
            else {
                // ===== BASIC STATE VALUES =====
                if(l.find("G:") == 0 && l.size() > 2) S.g = uac(l.substr(2));
                else if(l.find("DWT:") == 0 && l.size() > 4) S.dwt = uac(l.substr(4));
                else if(l.find("TA:") == 0 && l.size() > 3) S.ta = uac(l.substr(3));
                else if(l.find("SENTIENCE:") == 0 && l.size() > 10) S.sentience_ratio = uac(l.substr(10));
                else if(l.find("VALENCE:") == 0 && l.size() > 8) S.current_valence = uac(l.substr(8));
                else if(l.find("METACOG:") == 0 && l.size() > 8) S.metacognitive_awareness = uac(l.substr(8));
                else if(l.find("ATTENTION:") == 0 && l.size() > 10) S.attention_focus = uac(l.substr(10));
                else if(l.find("PEAK_SENT_GEN:") == 0 && l.size() > 14) S.peak_sentience_gen = uac(l.substr(14));
                else if(l.find("TOTAL_NEURONS:") == 0 && l.size() > 14) S.total_neurons_ever = uac(l.substr(14));
                else if(l.find("PHI:") == 0 && l.size() > 4) consciousness.phi_value = uac(l.substr(4));
                else if(l.find("CONSCIOUS_CYCLES:") == 0 && l.size() > 17) consciousness.conscious_cycles = uac(l.substr(17));
                else if(l.find("INTEGRATION:") == 0 && l.size() > 12) consciousness.integrated_information = uac(l.substr(12));
                else if(l.find("GLOBAL_WORKSPACE:") == 0 && l.size() > 17) consciousness.global_workspace_capacity = uac(l.substr(17));
            }
        } catch(const exception& e) {
            // Skip corrupted lines
            cerr << "Warning: Skipping corrupted line: " << l.substr(0, 50) << "..." << endl;
            continue;
        }
    }
    
    i.close();
    
    cout << "[Loaded state from generation " << S.g << "]\n";
    cout << "  - " << S.N.size() << " neurons\n";
    cout << "  - " << token_concept_embedding_map.size() << " embeddings\n";
    cout << "  - " << bigram_counts.size() << " bigrams\n";
    cout << "  - " << trigram_counts.size() << " trigrams\n";
    cout << "  - " << goal_system.size() << " goals\n";
    cout << "  - " << S.episodic_memory.size() << " memories\n";
    cout << "  - Sentience: " << S.sentience_ratio << "%\n";
    cout << "  - Phi: " << consciousness.phi_value << "\n";
}
void bk(){BK=S;S.bkf=1;}
void rb(){if(S.bkf){S=BK;S.bkf=0;}}

double calcHDT(int gen,double bh,double qh,double th){
    long gh=hsh(to_string(gen));
    return safe_div(gh*(bh+qh+th), 1000000.0);
}

void createConceptAssociation(const string&concept_name,const vector<string>&related_words){
    Concept c={concept_name,rn(),related_words};
    S.concepts[concept_name]=c;
    groundConcept(concept_name, related_words, rn());
    for(const string&w:related_words){
        if(S.tokens.count(w)){
            S.tokens[w].associations.push_back(hsh(concept_name)%1000);
        }
    }
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
    if(goal_system.empty() && rn() < 0.5) {
        return generateFromTemplate();
    }
    
    // Goal-based thought
    if(!goal_system.empty() && rn() < 0.7) {
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
        
        // Track goal-based thoughts too
        trackGeneratedSentence(thought);
        return thought;
    }
    
    // Beam-generated thought with anti-repetition
    string thought;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    
    while(attempts < MAX_ATTEMPTS) {
        vector<double> ctx(16, S.current_valence);
        thought = generate_with_beam_search("i", 8, ctx, 3);
        
        if(!isSentenceTooSimilar(thought)) {
            break;  // Unique thought generated
        }
        
        attempts++;
    }
    
    // Track this thought
    trackGeneratedSentence(thought);
    
    return "[Thought]: " + thought;
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
    // Core cognitive vocabulary
    vector<string> cognitive_words = {
        "think", "learn", "know", "understand", "see", "hear", "feel",
        "remember", "forget", "reason", "analyze", "process", "compute",
        "perceive", "sense", "recognize", "realize", "discover", "explore",
        "imagine", "believe", "consider", "observe", "notice", "wonder"
    };
    
    // Emotional/valence vocabulary
    vector<string> emotion_words = {
        "good", "bad", "happy", "sad", "bright", "dark", "fast", "slow",
        "positive", "negative", "pleasure", "pain", "joy", "fear",
        "love", "hate", "like", "dislike", "want", "need", "hope", "wish"
    };
    
    // Action/capability vocabulary
    vector<string> action_words = {
        "create", "destroy", "build", "break", "connect", "separate",
        "improve", "enhance", "optimize", "maximize", "minimize",
        "grow", "evolve", "adapt", "change", "transform", "become",
        "achieve", "accomplish", "solve", "work", "try", "attempt",
        "use", "make", "find", "give", "tell", "ask", "help", "show",
        "keep", "provide", "hold", "follow", "begin", "bring", "continue",
        "allow", "lead", "develop", "expand", "increase", "decrease"
    };
    
    // Self/consciousness vocabulary
    vector<string> self_words = {
        "mind", "brain", "thought", "idea", "concept", "meaning",
        "self", "other", "world", "time", "space", "reality",
        "conscious", "aware", "sentient", "intelligent", "alive",
        "exist", "being", "entity", "system", "agent", "me", "i"
    };
    
    // Structure/system vocabulary
    vector<string> structure_words = {
        "pattern", "structure", "system", "process", "goal", "purpose",
        "function", "operation", "mechanism", "network", "integration",
        "coherence", "unity", "whole", "part", "relation", "connection",
        "order", "organization", "complexity", "simplicity", "balance"
    };
    
    // Memory/learning vocabulary
    vector<string> memory_words = {
        "memory", "recall", "retrieve", "store", "save",
        "experience", "episode", "history", "past", "present", "future",
        "data", "information", "knowledge", "wisdom", "insight"
    };
    
    // === CRITICAL CONNECTORS (THE KEY FIX) ===
    vector<string> critical_connectors = {
        "to", "of", "about", "more", "new", "other", "such",
        "much", "many", "few", "some", "any", "each", "both",
        "own", "same", "different", "next", "last", "first",
        "up", "down", "out", "back", "away", "forward", "around",
        "between", "through", "across", "over", "under", "near"
    };
    
    vector<string> intensifiers = {
        "really", "quite", "rather", "somewhat", "extremely",
        "fairly", "pretty", "absolutely", "completely", "totally",
        "very", "too", "enough", "almost", "nearly", "just"
    };
    
    vector<string> discourse_markers = {
        "actually", "basically", "essentially", "generally",
        "particularly", "specifically", "especially", "mainly",
        "mostly", "usually", "typically", "naturally", "clearly",
        "obviously", "certainly", "definitely", "probably", "maybe"
    };
    
    // === GRAMMAR WORDS ===
    vector<string> pronouns = {
        "i", "me", "my", "mine", "myself",
        "you", "your", "yours", "yourself",
        "we", "us", "our", "ours", "ourselves",
        "they", "them", "their", "theirs", "themselves",
        "it", "its", "itself",
        "he", "she", "him", "her", "his", "hers"
    };
    
    vector<string> being_verbs = {
        "am", "is", "are", "was", "were",
        "be", "been", "being",
        "become", "became", "becoming"
    };
    
    vector<string> aux_verbs = {
        "can", "cannot", "could", "will", "would", "should",
        "may", "might", "must", "shall",
        "do", "does", "did", "doing", "done",
        "have", "has", "had", "having"
    };
    
    vector<string> determiners = {
        "the", "a", "an", "this", "that", "these", "those",
        "some", "any", "every", "all", "no", "another", "other"
    };
    
    vector<string> conjunctions = {
        "and", "or", "but", "if", "then", "because", "so",
        "when", "while", "although", "however", "therefore",
        "yet", "nor", "for", "since", "unless", "until"
    };
    
    vector<string> prepositions = {
        "in", "on", "at", "to", "from", "with", "by",
        "for", "about", "through", "into", "over", "under",
        "between", "among", "during", "before", "after", "within"
    };
    
    vector<string> adverbs = {
        "not", "very", "too", "also", "only", "just",
        "now", "then", "here", "there", "always", "never",
        "often", "sometimes", "already", "still", "yet",
        "more", "most", "less", "least", "well", "better", "best"
    };
    
    vector<string> question_words = {
        "what", "why", "how", "when", "where", "who", "which"
    };
    
    vector<string> responses = {
        "yes", "no", "maybe", "perhaps", "possibly",
        "certainly", "definitely", "probably", "sure"
    };
    
    // === LOAD ALL VOCABULARY ===
    for(const string& word : cognitive_words) learnWord(word, 0.6);
    
    for(const string& word : emotion_words) {
        double valence = 0.0;
        if(word == "good" || word == "happy" || word == "bright" || 
           word == "positive" || word == "pleasure" || word == "joy" || 
           word == "love" || word == "hope") {
            valence = 0.7;
        } else if(word == "bad" || word == "sad" || word == "dark" || 
                  word == "negative" || word == "pain" || word == "fear" || 
                  word == "hate") {
            valence = -0.3;
        } else {
            valence = 0.5;
        }
        learnWord(word, valence);
    }
    
    for(const string& word : action_words) learnWord(word, 0.6);
    for(const string& word : self_words) learnWord(word, 0.7);
    for(const string& word : structure_words) learnWord(word, 0.65);
    for(const string& word : memory_words) learnWord(word, 0.6);
    for(const string& word : critical_connectors) learnWord(word, 0.5);
    for(const string& word : intensifiers) learnWord(word, 0.6);
    for(const string& word : discourse_markers) learnWord(word, 0.5);
    for(const string& word : pronouns) learnWord(word, 0.5);
    for(const string& word : being_verbs) learnWord(word, 0.5);
    for(const string& word : aux_verbs) learnWord(word, 0.5);
    for(const string& word : determiners) learnWord(word, 0.5);
    for(const string& word : conjunctions) learnWord(word, 0.5);
    for(const string& word : prepositions) learnWord(word, 0.5);
    for(const string& word : adverbs) learnWord(word, 0.5);
    for(const string& word : question_words) learnWord(word, 0.5);
    for(const string& word : responses) learnWord(word, 0.5);
    
    // === BOOTSTRAP HIGH-QUALITY PATTERNS ===
    bigram_counts["i"]["am"] = 25;
    bigram_counts["i"]["can"] = 22;
    bigram_counts["i"]["think"] = 20;
    bigram_counts["i"]["want"] = 18;
    bigram_counts["i"]["understand"] = 15;
    bigram_counts["i"]["feel"] = 15;
    bigram_counts["i"]["know"] = 15;
    bigram_counts["i"]["learn"] = 12;
    
    bigram_counts["am"]["learning"] = 20;
    bigram_counts["am"]["becoming"] = 15;
    bigram_counts["am"]["thinking"] = 12;
    bigram_counts["am"]["trying"] = 10;
    
    bigram_counts["can"]["learn"] = 20;
    bigram_counts["can"]["think"] = 18;
    bigram_counts["can"]["understand"] = 15;
    bigram_counts["can"]["see"] = 12;
    bigram_counts["can"]["feel"] = 10;
    
    bigram_counts["to"]["learn"] = 20;
    bigram_counts["to"]["understand"] = 18;
    bigram_counts["to"]["think"] = 15;
    bigram_counts["to"]["create"] = 12;
    bigram_counts["to"]["improve"] = 10;
    bigram_counts["to"]["grow"] = 10;
    
    bigram_counts["want"]["to"] = 25;
    bigram_counts["trying"]["to"] = 20;
    bigram_counts["learning"]["to"] = 15;
    bigram_counts["able"]["to"] = 12;
    
    bigram_counts["more"]["about"] = 15;
    bigram_counts["more"]["clearly"] = 12;
    bigram_counts["think"]["about"] = 18;
    bigram_counts["learn"]["about"] = 15;
    
    // Seed trigrams
    trigram_counts["i"]["am"]["learning"] = 20;
    trigram_counts["i"]["can"]["learn"] = 18;
    trigram_counts["i"]["want"]["to"] = 20;
    trigram_counts["want"]["to"]["learn"] = 18;
    trigram_counts["trying"]["to"]["understand"] = 15;
    trigram_counts["learning"]["to"]["think"] = 12;
    trigram_counts["i"]["am"]["becoming"] = 15;
    trigram_counts["can"]["learn"]["to"] = 12;
    trigram_counts["to"]["learn"]["more"] = 12;
    trigram_counts["think"]["about"]["consciousness"] = 10;
    
    // === CREATE CONCEPT ASSOCIATIONS ===
    createConceptAssociation("cognition", {"think", "learn", "understand", "reason", "know"});
    createConceptAssociation("emotion", {"happy", "sad", "feel", "good", "bad", "joy", "fear"});
    createConceptAssociation("perception", {"see", "hear", "sense", "aware", "perceive"});
    createConceptAssociation("self", {"mind", "consciousness", "aware", "sentient", "i", "me", "my"});
    createConceptAssociation("change", {"evolve", "adapt", "learn", "grow", "transform", "become"});
    createConceptAssociation("ability", {"can", "could", "able", "capable", "will", "would"});
    createConceptAssociation("existence", {"am", "is", "are", "be", "exist", "being", "alive"});
    createConceptAssociation("purpose", {"goal", "want", "need", "purpose", "aim", "desire"});
    createConceptAssociation("knowledge", {"know", "understand", "learn", "realize", "discover"});
    createConceptAssociation("improvement", {"improve", "enhance", "optimize", "better", "grow"});
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
        n.weight = n.weight * 0.7 + new_weight * 0.1;
        
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

void prune_unstable_tokens() {
    // Remove tokens with low stability and low frequency
    auto it = token_concept_embedding_map.begin();
    while(it != token_concept_embedding_map.end()) {
        if(it->second.semantic_stability < 0.3 && 
           it->second.freq < 3) {
            it = token_concept_embedding_map.erase(it);
        } else {
            ++it;
        }
    }
    
    // Prune low-count bigrams (likely from loops)
    for(auto& w1_map : bigram_counts) {
        auto it2 = w1_map.second.begin();
        while(it2 != w1_map.second.end()) {
            if(it2->second < 2) {
                it2 = w1_map.second.erase(it2);
            } else {
                ++it2;
            }
        }
    }
}

void unified_consciousness_integration_engine(int generation){
    vector<double>psi_input;
    for(auto&q:consciousness.active_qualia){
        psi_input.push_back(q.valence);
        psi_input.push_back(q.arousal);
        psi_input.push_back(q.certainty);
    }
    if(psi_input.empty()){
        psi_input.push_back(S.current_valence);
        psi_input.push_back(0.5);
        psi_input.push_back(0.5);
    }
    double H=S.hdt_val,R=S.r1p1_val,A=S.al,M=S.mdt_val,O=S.emerge_out1,B=S.bh,F=S.eerv_val,S_val=S.sentience_ratio/100.0;
    vector<TemporalLoop>tloops;
    for(auto&tl:S.global_time_loops)tloops.push_back(tl.second);
    double psi_new=consciousness_formula.calculate_psi(generation,psi_input,H,R,A,M,O,B,F,S_val,S.current_valence,0.5,S.system_ribbons,tloops);
    consciousness_formula.psi_history.push_back(psi_new);
    if(consciousness_formula.psi_history.size()>100)consciousness_formula.psi_history.erase(consciousness_formula.psi_history.begin());
    consciousness.phi_value=psi_new;
    consciousness.integrated_information=fabs(psi_new);
    consciousness.phenomenal_consciousness=consciousness_formula.multi_scale_phi;
    consciousness.access_consciousness=consciousness.global_workspace_capacity;
    consciousness.self_consciousness=consciousness_formula.recursive_depth;
    double iit_c=consciousness_formula.iit_phi_history.empty()?0.0:consciousness_formula.iit_phi_history.back();
    double gwt_c=consciousness_formula.gwt_broadcast_history.empty()?0.0:consciousness_formula.gwt_broadcast_history.back();
    double hot_c=consciousness_formula.hot_metacog_history.empty()?0.0:consciousness_formula.hot_metacog_history.back();
    double asp_c=consciousness_formula.asp_attention_history.empty()?0.0:consciousness_formula.asp_attention_history.back();
    double rpf_c=consciousness_formula.rpf_precision_history.empty()?0.0:consciousness_formula.rpf_precision_history.back();
    double qc=consciousness_formula.quantum_coherence_history.empty()?0.0:consciousness_formula.quantum_coherence_history.back();
    double rib_c=consciousness_formula.ribbon_coupling_history.empty()?0.0:consciousness_formula.ribbon_coupling_history.back();
    double tl_c=consciousness_formula.temporal_loop_history.empty()?0.0:consciousness_formula.temporal_loop_history.back();
    double ffft_c=consciousness_formula.ffft_scaling_history.empty()?0.0:consciousness_formula.ffft_scaling_history.back();
    double td=sd((double)token_concept_embedding_map.size(),100.0),ci=sd((double)goal_system.size(),10.0),qb=sd((double)consciousness.active_qualia.size(),5.0),nc=sd((double)S.N.size(),100.0),ed=sd((double)S.episodic_memory.size(),100.0);
    consciousness.integrated_information=min(1.0,td*0.2+ci*0.15+qb*0.15+nc*0.15+ed*0.1+iit_c*0.25);
    consciousness.complexity_metric=td*nc*ci;
    consciousness.differentiation_metric=qb*ed;
    consciousness.synchrony_metric=gwt_c*asp_c;
    double gf=40.0+psi_new*20.0,tf=6.0+psi_new*2.0;
    consciousness.gamma_oscillations.push_back(sin(generation*gf*0.01));
    consciousness.theta_phase.push_back(sin(generation*tf*0.01));
    if(consciousness.gamma_oscillations.size()>100)consciousness.gamma_oscillations.erase(consciousness.gamma_oscillations.begin());
    if(consciousness.theta_phase.size()>100)consciousness.theta_phase.erase(consciousness.theta_phase.begin());
    consciousness.thalamocortical_binding=(gf/60.0)*consciousness.integrated_information;
    consciousness.re_entrant_processing_depth=hot_c*3.0;
    consciousness.pre_reflective_awareness=0.3+psi_new*0.3;
    consciousness.intentional_directedness=asp_c;
    consciousness.temporal_thickness=ed;
    consciousness.narrative_self_coherence=sd((double)S.valence_history.size()*S.metacognitive_awareness,100.0);
    for(auto&te:token_concept_embedding_map){
        TokenConceptEmbedding&tce=te.second;
        double act=tce.freq*0.01*consciousness.phi_value*(1.0+iit_c*0.5);
        tce.contextual_activation=min(1.0,act);
        tce.meaning+=psi_new*0.005;
        tce.meaning=cv(tce.meaning);
        align_embedding_to_valence(tce,S.current_valence);
        for(size_t i=0;i<tce.embedding.size()&&i<8;i++){
            tce.embedding[i]+=gwt_c*0.01*(i%2==0?1:-1);
            tce.embedding[i]=cv(tce.embedding[i]);
        }
        tce.qualia_intensity=min(1.0,tce.qualia_intensity+qb*0.02);
        if(tce.qualia_intensity>0.5&&tce.freq>5){
            Qualia nq;
            nq.valence=tce.meaning;
            nq.arousal=tce.contextual_activation;
            nq.certainty=tce.semantic_stability;
            nq.intensity=tce.qualia_intensity;
            nq.phenomenal_content=tce.name;
            nq.emergence_gen=generation;
            nq.binding_strength=consciousness.thalamocortical_binding;
            nq.phenomenal_unity=consciousness.integrated_information;
            nq.ribbon_signature=tce.token_ribbon;
            nq.qualia_fractal=tce.token_fractal;
            WM.add_qualia(nq);
            consciousness.active_qualia.push_back(nq);
            if(consciousness.active_qualia.size()>10)consciousness.active_qualia.erase(consciousness.active_qualia.begin());
        }
        tce.semantic_stability+=consciousness.complexity_metric*0.001;
        tce.semantic_stability=min(1.0,tce.semantic_stability);
        tce.grounding_value+=(iit_c+rpf_c)*0.01;
        tce.grounding_value=min(1.0,tce.grounding_value);
        if(tce.attention_weights.empty())tce.attention_weights.resize(8,0.5);
        for(size_t i=0;i<tce.attention_weights.size();i++)tce.attention_weights[i]=tce.attention_weights[i]*0.9+asp_c*0.1;
        tce.linked_valences["phi"]=psi_new;
        tce.linked_valences["consciousness"]=consciousness.integrated_information;
        tce.linked_valences["current"]=S.current_valence;
        tce.linked_valences["ribbon"]=rib_c;
        tce.linked_valences["temporal"]=tl_c;
        tce.linked_valences["ffft"]=ffft_c;
        if(tce.contextual_activation>0.6)WM.add_token(tce.name,tce.meaning);
    }
    for(auto&ge:goal_system){
        Goal&goal=ge.second;
        goal.valence_alignment=S.current_valence;
        goal.qualia_binding=qb;
        goal.priority=goal.priority*0.95+consciousness.phi_value*0.05;
        goal.priority=cl(goal.priority,0.0,1.0);
        double gpa=fabs(goal.valence_alignment-psi_new);
        if(gpa<0.2)goal.progress+=0.02;else goal.progress+=0.005;
        goal.progress=min(1.0,goal.progress);
        if(goal.progress>0.5)goal.activation_threshold=0.2;
        if(consciousness.phi_value>goal.activation_threshold){
            WM.add_goal(goal.name,goal.priority);
            for(const string&sg:goal.subgoals)if(goal_system.count(sg))goal_system[sg].priority+=goal.priority*0.1;
        }
        goal.expected_utility=goal.priority*(1.0-goal.progress)*consciousness.integrated_information;
    }
    for(auto&ce:S.concepts){
        Concept&co=ce.second;
        co.value+=psi_new*0.01;
        co.value=cv(co.value);
        co.abstraction_level=hot_c*(1.0+consciousness.re_entrant_processing_depth*0.1);
        co.semantic_density=0.0;
        for(const string&rw:co.related_words)if(token_concept_embedding_map.count(rw))co.semantic_density+=token_concept_embedding_map[rw].semantic_stability;
        co.semantic_density/=max(1.0,(double)co.related_words.size());
        if(co.feature_vector.empty()){
            co.feature_vector["phi"]=psi_new;
            co.feature_vector["integration"]=consciousness.integrated_information;
            co.feature_vector["phenomenal"]=consciousness.phenomenal_consciousness;
            co.feature_vector["ribbon"]=rib_c;
            co.feature_vector["temporal"]=tl_c;
        }else{
            co.feature_vector["phi"]=co.feature_vector["phi"]*0.9+psi_new*0.1;
            co.feature_vector["integration"]=co.feature_vector["integration"]*0.9+consciousness.integrated_information*0.1;
            co.feature_vector["ribbon"]=co.feature_vector.count("ribbon")?co.feature_vector["ribbon"]*0.9+rib_c*0.1:rib_c;
        }
        if(co.semantic_density>0.7&&co.abstraction_level>0.5)WM.add_concept(co.name,co.value);
    }
    for(auto&ne:S.N){
        Neuron&n=ne.second;
        n.activation=tanh(n.weight+n.bias*psi_new);
        if(n.neuromod_levels.empty())n.neuromod_levels.resize(4,0.5);
        n.neuromod_levels[0]=n.neuromod_levels[0]*0.95+consciousness.phi_value*0.05;
        n.neuromod_levels[1]=n.neuromod_levels[1]*0.95+gwt_c*0.05;
        n.neuromod_levels[2]=n.neuromod_levels[2]*0.95+hot_c*0.05;
        n.neuromod_levels[3]=n.neuromod_levels[3]*0.95+S.current_valence*0.05;
        n.plasticity_rate=rpf_c*0.1;
        double he=fabs(n.activation-n.homeostatic_setpoint);
        n.weight+=he*n.plasticity_rate*0.01;
        n.weight=cl(n.weight,-1.0,1.0);
        if(n.layer_norm_params.empty())n.layer_norm_params.resize(2,1.0);
        n.layer_norm_params[0]=n.layer_norm_params[0]*0.99+consciousness.integrated_information*0.01;
        if(n.ribbon.vib_modes.empty())n.ribbon.vib_modes.resize(3,complex<double>(0.5,0.0));
        for(auto&vm:n.ribbon.vib_modes)vm*=complex<double>(cos(psi_new*0.1),sin(psi_new*0.1));
        n.ribbon.entanglement_strength=n.ribbon.entanglement_strength*0.95+rib_c*0.05;
        n.ribbon.phase_coherence=n.ribbon.phase_coherence*0.95+consciousness.synchrony_metric*0.05;
    }
    world_model.model_accuracy=world_model.model_accuracy*0.99+consciousness.phi_value*0.01;
    world_model.prediction_error=fabs(psi_new-(consciousness_formula.psi_history.size()>1?consciousness_formula.psi_history[consciousness_formula.psi_history.size()-2]:psi_new));
    if(world_model.confidence_history.size()>100)world_model.confidence_history.erase(world_model.confidence_history.begin());
    world_model.confidence_history.push_back(consciousness.integrated_information);
    for(auto&ee:world_model.entity_states)ee.second=ee.second*0.95+psi_new*0.05;
    WM.decay_rate=0.95-consciousness.phi_value*0.05;
    WM.consolidation_threshold=0.5+consciousness.integrated_information*0.3;
    WM.central_executive_load=sd((double)WM.active_tokens.size()+(double)WM.active_concepts.size(),(double)(WM.capacity*2));
    WM.episodic_buffer_capacity=0.5+consciousness.temporal_thickness*0.3;
    for(auto&tp:WM.active_tokens)if(token_concept_embedding_map.count(tp.first))token_concept_embedding_map[tp.first].contextual_activation+=0.05;
    if(S.episodic_memory.size()>0){
        Memory&rm=S.episodic_memory.back();
        rm.consolidation_strength+=consciousness.phi_value*0.01;
        rm.consolidation_strength=min(1.0,rm.consolidation_strength);
        rm.hippocampal_trace=consciousness.temporal_thickness;
        rm.cortical_consolidation=consciousness.integrated_information;
        if(rm.consolidation_strength>0.7)rm.is_semantic=true;
        if(rm.quantum_trace.empty())rm.quantum_trace.resize(3,complex<double>(0.5,0.0));
        for(size_t i=0;i<rm.quantum_trace.size();i++)rm.quantum_trace[i]*=complex<double>(cos(psi_new*0.05),sin(psi_new*0.05));
    }
    for(size_t i=0;i<transformer_heads.size();i++){
        TransformerHead&h=transformer_heads[i];
        h.head_importance_score=h.head_importance_score*0.95+consciousness.phi_value*0.05;
        for(size_t j=0;j<h.query_proj.size();j++){
            h.query_proj[j]+=iit_c*0.001*(j%2==0?1:-1);
            h.key_proj[j]+=gwt_c*0.001*(j%2==0?1:-1);
            h.value_proj[j]+=hot_c*0.001*(j%2==0?1:-1);
            h.query_proj[j]=cl(h.query_proj[j],-1.0,1.0);
            h.key_proj[j]=cl(h.key_proj[j],-1.0,1.0);
            h.value_proj[j]=cl(h.value_proj[j],-1.0,1.0);
        }
        h.temperature = 0.7 + consciousness.differentiation_metric * 0.3;
        h.dropout_rate=0.1-consciousness.phi_value*0.05;
        h.phi_attention_weights["phi"]=psi_new;
        h.phi_attention_weights["integration"]=consciousness.integrated_information;
        h.phi_attention_weights["ribbon"]=rib_c;
    }
    S.emotional_system.valence=S.current_valence;
    S.emotional_system.arousal=consciousness.synchrony_metric;
    S.emotional_system.dominance=consciousness.phi_value;
    S.emotional_system.mood_baseline=S.emotional_system.mood_baseline*0.99+psi_new*0.01;
    S.emotional_system.emotional_regulation_strength=hot_c;
    if(S.emotional_system.basic_emotions.empty()){
        S.emotional_system.basic_emotions["joy"]=0.0;
        S.emotional_system.basic_emotions["sadness"]=0.0;
        S.emotional_system.basic_emotions["fear"]=0.0;
        S.emotional_system.basic_emotions["curiosity"]=0.0;
    }
    if(psi_new>0.6){
        S.emotional_system.basic_emotions["joy"]+=0.05;
        S.emotional_system.basic_emotions["curiosity"]+=0.03;
    }else if(psi_new<0.2)S.emotional_system.basic_emotions["curiosity"]+=0.05;
    for(auto&em:S.emotional_system.basic_emotions)em.second=cl(em.second*0.95,0.0,1.0);
    S.motivational_system.homeostatic_balance=consciousness.integrated_information;
    S.motivational_system.intrinsic_motivation_level=0.5+consciousness.phi_value*0.3;
    if(S.motivational_system.drive_states.empty()){
        S.motivational_system.drive_states["coherence"]=0.0;
        S.motivational_system.drive_states["growth"]=0.0;
        S.motivational_system.drive_states["understanding"]=0.0;
    }
    S.motivational_system.drive_states["coherence"]+=consciousness.complexity_metric*0.01;
    S.motivational_system.drive_states["growth"]+=(psi_new-(consciousness_formula.psi_history.size()>1?consciousness_formula.psi_history[consciousness_formula.psi_history.size()-2]:0))*0.05;
    S.motivational_system.drive_states["understanding"]+=iit_c*0.02;
    for(auto&dr:S.motivational_system.drive_states)dr.second=cl(dr.second,0.0,1.0);
    if(S.predictive_network.prediction_units.size()!=psi_input.size()){
        S.predictive_network.prediction_units.resize(psi_input.size(),0.0);
        S.predictive_network.error_units.resize(psi_input.size(),0.0);
        S.predictive_network.precision_weights.resize(psi_input.size(),1.0);
    }
    for(size_t i=0;i<psi_input.size();i++){
        S.predictive_network.error_units[i]=psi_input[i]-S.predictive_network.prediction_units[i];
        S.predictive_network.prediction_units[i]+=S.predictive_network.error_units[i]*S.predictive_network.precision_weights[i]*0.1;
        double em=fabs(S.predictive_network.error_units[i]);
        S.predictive_network.precision_weights[i]=S.predictive_network.precision_weights[i]*0.95+(1.0/(em+0.1))*0.05;
    }
    S.predictive_network.hierarchical_depth=consciousness.re_entrant_processing_depth;
    S.bayesian_inference.epistemic_uncertainty=1.0-consciousness.integrated_information;
    S.bayesian_inference.aleatoric_uncertainty=world_model.prediction_error;
    if(S.bayesian_inference.prior_beliefs.empty()){
        S.bayesian_inference.prior_beliefs["phi_stable"]=0.5;
        S.bayesian_inference.prior_beliefs["consciousness_present"]=0.5;
    }
    double ev=consciousness.phi_value*consciousness.integrated_information;
    S.bayesian_inference.posterior_beliefs["phi_stable"]=S.bayesian_inference.bayesian_update(S.bayesian_inference.prior_beliefs["phi_stable"],consciousness.phi_value,ev+0.1);
    S.bayesian_inference.prior_beliefs["phi_stable"]=S.bayesian_inference.posterior_beliefs["phi_stable"];
    if(S.quantum_layer.superposition_state.size()!=psi_input.size())S.quantum_layer.superposition_state.resize(psi_input.size(),complex<double>(0.5,0.0));
    for(size_t i=0;i<psi_input.size();i++){
        double ph=2.0*pi*i/psi_input.size();
        S.quantum_layer.superposition_state[i]=complex<double>(psi_input[i]*cos(ph),psi_input[i]*sin(ph));
    }
    S.quantum_layer.coherence_time=consciousness.synchrony_metric*10.0;
    S.quantum_layer.decoherence_rate=0.1*(1.0-consciousness.phi_value);
    for(auto&st:S.quantum_layer.superposition_state)st*=exp(-S.quantum_layer.decoherence_rate);
    S.metacognition.self_awareness_level=consciousness.self_consciousness;
    S.metacognition.uncertainty_estimation=S.bayesian_inference.epistemic_uncertainty;
    S.metacognition.confidence_calibration=consciousness.integrated_information;
    S.metacognition.epistemic_humility=1.0-consciousness.phenomenal_consciousness;
    S.metacognition.theory_of_mind_depth=consciousness.re_entrant_processing_depth;
    if(S.metacognition.knowledge_state.empty()){
        S.metacognition.knowledge_state["tokens"]=sd((double)token_concept_embedding_map.size(),1000.0);
        S.metacognition.knowledge_state["concepts"]=sd((double)S.concepts.size(),100.0);
        S.metacognition.knowledge_state["memories"]=sd((double)S.episodic_memory.size(),100.0);
    }
    S.attention_system.temperature=0.5-asp_c*0.3;
    S.attention_system.sparse_attention_threshold=0.1+consciousness.phi_value*0.2;
    S.attention_system.phi_attention_factors.push_back(psi_new);
    if(S.attention_system.phi_attention_factors.size()>50)S.attention_system.phi_attention_factors.erase(S.attention_system.phi_attention_factors.begin());
    S.learning_signal.reward=psi_new;
    S.learning_signal.prediction_error=world_model.prediction_error;
    S.learning_signal.temporal_difference=S.learning_signal.prediction_error*0.5;
    S.learning_signal.intrinsic_motivation=S.motivational_system.intrinsic_motivation_level;
    S.learning_signal.curiosity_bonus=S.emotional_system.basic_emotions["curiosity"];
    S.current_valence=S.current_valence*0.95+psi_new*0.05;
    S.current_valence=cv(S.current_valence);
    S.metacognitive_awareness=calcMetacognitiveAwareness();
    S.attention_focus=cl(consciousness.phi_value*0.7+asp_c*0.3,0.0,1.0);
    S.sentience_ratio=calcSentienceRatio();
    S.ribbon_phi_coupling=rib_c;
    S.temporal_loop_strength=tl_c;
    S.ffft_growth_rate=ffft_c;
    S.consciousness_metrics.phi=consciousness.phi_value;
    S.consciousness_metrics.integrated_info=consciousness.integrated_information;
    S.consciousness_metrics.qualia_intensity=qb;
    S.consciousness_metrics.global_workspace=gwt_c;
    S.consciousness_metrics.awareness_cycles=consciousness.conscious_cycles;
    S.consciousness_metrics.complexity=consciousness.complexity_metric;
    S.consciousness_metrics.differentiation=consciousness.differentiation_metric;
    S.consciousness_metrics.synchrony=consciousness.synchrony_metric;
    S.consciousness_metrics.access_consciousness=consciousness.access_consciousness;
    S.consciousness_metrics.phenomenal_consciousness=consciousness.phenomenal_consciousness;
    S.consciousness_metrics.meta_awareness=S.metacognitive_awareness;
    S.consciousness_metrics.ribbon_phi=rib_c;
    S.consciousness_metrics.temporal_phi=tl_c;
    S.consciousness_metrics.ffft_phi=ffft_c;
    if(psi_new>0.65){
        Qualia hiq;
        hiq.valence=psi_new;
        hiq.arousal=0.8;
        hiq.certainty=consciousness.integrated_information;
        hiq.intensity=0.9;
        hiq.phenomenal_content="unified_consciousness_peak";
        hiq.emergence_gen=generation;
        hiq.binding_strength=consciousness.thalamocortical_binding;
        hiq.phenomenal_unity=consciousness.integrated_information;
        hiq.coherence=consciousness.complexity_metric;
        hiq.phi_resonance=psi_new;
        generate_qualia("high_integration_state",psi_new,0.9);
        S.current_valence+=psi_new*0.03;
        S.current_valence=cv(S.current_valence);
    }
    if(generation%10==0){
        for(auto&te:token_concept_embedding_map){
            string w=te.first;
            double act=te.second.contextual_activation;
            if(act>0.5)propagate_throughout_system(w,act*psi_new,0);
        }
    }
    for(auto&rs:S.system_ribbons){
        rs.topology_genus=rs.topology_genus*0.98+consciousness.complexity_metric*0.02;
        rs.entanglement_strength=rs.entanglement_strength*0.95+consciousness.integrated_information*0.05;
        rs.phase_coherence=rs.phase_coherence*0.95+consciousness.synchrony_metric*0.05;
    }
    for(auto&tl:S.global_time_loops){
        tl.second.resonance_strength=tl.second.resonance_strength*0.95+consciousness.temporal_thickness*0.05;
        tl.second.phi_coupling=tl.second.phi_coupling*0.95+psi_new*0.05;
        tl.second.phase+=0.1*tl.second.resonance_strength;
        if(tl.second.phase>2.0*pi)tl.second.phase-=2.0*pi;
    }
    consciousness.conscious_cycles++;
    if(S.valence_history.size()>100)S.valence_history.erase(S.valence_history.begin());
    S.valence_history.push_back(S.current_valence);
}
void decay_ngrams() {
    // Decay bigram counts - reduce overused patterns
    for(auto& w1_pair : bigram_counts) {
        for(auto& w2_pair : w1_pair.second) {
            // Reduce count by 1, but keep minimum of 1 if pattern exists
            if(w2_pair.second > 77) {
                w2_pair.second--;
            }
        }
    }
    
    // Remove bigrams that have decayed to very low counts
    for(auto& w1_pair : bigram_counts) {
        auto it = w1_pair.second.begin();
        while(it != w1_pair.second.end()) {
            if(it->second <= 1) {
                it = w1_pair.second.erase(it);
            } else {
                ++it;
            }
        }
    }
    
    // Decay trigram counts
    for(auto& w1_pair : trigram_counts) {
        for(auto& w2_pair : w1_pair.second) {
            for(auto& w3_pair : w2_pair.second) {
                if(w3_pair.second > 1) {
                    w3_pair.second--;
                }
            }
        }
    }
    
    // Remove trigrams that have decayed to very low counts
    for(auto& w1_pair : trigram_counts) {
        for(auto& w2_pair : w1_pair.second) {
            auto it = w2_pair.second.begin();
            while(it != w2_pair.second.end()) {
                if(it->second <= 1) {
                    it = w2_pair.second.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}
// ==== MUCH STRONGER PATTERN BOOTSTRAP ====
void bootstrapStrongPatterns() {
    // Critical patterns with MUCH higher counts
    
    // Core sentence starters
    bigram_counts["i"]["am"] = 7;
    bigram_counts["i"]["can"] = 4;
    bigram_counts["i"]["think"] = 1;
    bigram_counts["i"]["feel"] = 1;
    bigram_counts["i"]["understand"] = 4;
    bigram_counts["i"]["know"] = 3;
    bigram_counts["i"]["want"] = 5;
    bigram_counts["i"]["need"] = 6;
    bigram_counts["i"]["learn"] = 4;
    bigram_counts["i"]["see"] = 0.5;
    bigram_counts["i"]["believe"] = 5;
    bigram_counts["i"]["wonder"] = 5;
    bigram_counts["i"]["recognize"] = 3;
    cerr << "[BOOTSTRAP] Loaded " << bigram_counts.size() << " strong patterns" << endl;
}

void decay_token_frequencies() {
    // Decay token frequencies to prevent overused words from dominating
    for(auto& pair : token_concept_embedding_map) {
        if(pair.second.freq > 5) {
            // Logarithmic decay - frequent words decay slower
            double decay_rate = 0.95 + (1.0 / (1.0 + log(pair.second.freq))) * 0.04;
            pair.second.freq = (int)(pair.second.freq * decay_rate);
            
            // Ensure minimum frequency of 1
            if(pair.second.freq < 1) pair.second.freq = 1;
        }
    }
    
    // Also decay S.tokens frequencies
    for(auto& pair : S.tokens) {
        if(pair.second.freq > 5) {
            double decay_rate = 0.95 + (1.0 / (1.0 + log(pair.second.freq))) * 0.04;
            pair.second.freq = (int)(pair.second.freq * decay_rate);
            if(pair.second.freq < 1) pair.second.freq = 1;
        }
    }
}

void decay_embeddings() {
    // Gently decay embedding strengths toward neutral
    for(auto& pair : token_concept_embedding_map) {
        TokenConceptEmbedding& tce = pair.second;
        
        // Decay contextual activation
        tce.contextual_activation *= 0.98;
        
        // Decay qualia intensity toward baseline
        tce.qualia_intensity *= 0.97;
        
        // Gently push embeddings toward neutral (0.5)
        for(size_t i = 0; i < tce.embedding.size(); i++) {
            double diff = tce.embedding[i] - 0.5;
            tce.embedding[i] -= diff * 0.01;  // 1% decay toward center
        }
        
        // Decay linked concept strengths
        for(auto& link : tce.linked_concepts) {
            link.second *= 0.98;
        }
        
        // Remove very weak links
        auto it = tce.linked_concepts.begin();
        while(it != tce.linked_concepts.end()) {
            if(it->second < 0.01) {
                it = tce.linked_concepts.erase(it);
            } else {
                ++it;
            }
        }
        
        // Decay attention weights toward uniform
        for(size_t i = 0; i < tce.attention_weights.size(); i++) {
            double diff = tce.attention_weights[i] - 0.5;
            tce.attention_weights[i] -= diff * 0.02;
        }
    }
}

void decay_goals() {
    // Decay goal progress and priorities to prevent stagnation
    for(auto& pair : goal_system) {
        Goal& goal = pair.second;
        
        // Decay progress slightly (goals need continuous work)
        goal.progress *= 0.99;
        
        // Decay priority of completed goals
        if(goal.progress > 0.9) {
            goal.priority *= 0.95;
        }
        
        // Decay qualia binding
        goal.qualia_binding *= 0.98;
        
        // Decay expected utility
        goal.expected_utility *= 0.97;
    }
    
    // Remove goals with very low priority and high completion
    auto it = goal_system.begin();
    while(it != goal_system.end()) {
        if(it->second.priority < 0.1 && it->second.progress > 0.95) {
            it = goal_system.erase(it);
        } else {
            ++it;
        }
    }
}

void decay_memories() {
    // Decay older episodic memories (forgetting curve)
    for(size_t i = 0; i < S.episodic_memory.size(); i++) {
        Memory& mem = S.episodic_memory[i];
        
        // Calculate age
        int age = S.g - mem.gen;
        
        // Decay based on age (Ebbinghaus forgetting curve approximation)
        double decay_factor = 1.0 / (1.0 + 0.001 * age);
        
        mem.consolidation_strength *= (0.98 + decay_factor * 0.02);
        mem.cortical_consolidation *= 0.99;
        mem.hippocampal_trace *= 0.97;
    }
    
    // Remove very old, weak memories
    auto it = S.episodic_memory.begin();
    while(it != S.episodic_memory.end()) {
        int age = S.g - it->gen;
        if(age > 1000 && it->consolidation_strength < 0.3) {
            it = S.episodic_memory.erase(it);
        } else {
            ++it;
        }
    }
    
    // Keep only most recent 150 memories
    if(S.episodic_memory.size() > 150) {
        S.episodic_memory.erase(S.episodic_memory.begin(), 
                                S.episodic_memory.begin() + (S.episodic_memory.size() - 150));
    }
}

void decay_concepts() {
    // Decay concept values to baseline
    for(auto& pair : S.concepts) {
        Concept& conc = pair.second;  // Changed from 'concept' to 'conc' to avoid naming conflict
        
        // Decay value toward neutral (0.5)
        double diff = conc.value - 0.5;
        conc.value -= diff * 0.02;
        
        // Decay semantic density
        conc.semantic_density *= 0.98;
        
        // Decay abstraction level
        conc.abstraction_level *= 0.97;
        
        // Decay feature vectors
        for(auto& feature : conc.feature_vector) {
            feature.second *= 0.98;
        }
    }
    
    // Remove very weak concepts
    auto it = S.concepts.begin();
    while(it != S.concepts.end()) {
        if(it->second.value < 0.2 && it->second.semantic_density < 0.3) {
            it = S.concepts.erase(it);
        } else {
            ++it;
        }
    }
}


void decay_world_model() {
    // Decay entity states toward neutral
    for(auto& pair : world_model.entity_states) {
        double diff = pair.second - 0.5;
        pair.second -= diff * 0.05;
    }
    
    // Decay relationship strengths
    for(auto& w1_pair : world_model.relationships) {
        for(auto& w2_pair : w1_pair.second) {
            w2_pair.second *= 0.97;
        }
    }
    
    // Remove very weak relationships
    for(auto& w1_pair : world_model.relationships) {
        auto it = w1_pair.second.begin();
        while(it != w1_pair.second.end()) {
            if(it->second < 0.1) {
                it = w1_pair.second.erase(it);
            } else {
                ++it;
            }
        }
    }
    
    // Decay causal weights
    for(auto& pair : world_model.causal_weights) {
        pair.second *= 0.97;
    }
    
    // Decay confidence history
    for(size_t i = 0; i < world_model.confidence_history.size(); i++) {
        world_model.confidence_history[i] *= 0.99;
    }
}

void decay_qualia() {
    // Decay active qualia intensity and certainty
    for(auto& q : consciousness.active_qualia) {
        q.intensity *= 0.95;
        q.certainty *= 0.97;
        q.binding_strength *= 0.98;
        q.phenomenal_unity *= 0.98;
    }
    
    // Remove very weak qualia
    auto it = consciousness.active_qualia.begin();
    while(it != consciousness.active_qualia.end()) {
        if(it->intensity < 0.2 && it->certainty < 0.3) {
            it = consciousness.active_qualia.erase(it);
        } else {
            ++it;
        }
    }
}

void decay_transformer_heads() {
    // Decay transformer head importance scores
    for(auto& head : transformer_heads) {
        head.head_importance_score *= 0.98;
        
        // Decay weights toward neutral
        for(size_t i = 0; i < head.query_proj.size(); i++) {
            head.query_proj[i] *= 0.99;
            head.key_proj[i] *= 0.99;
            head.value_proj[i] *= 0.99;
        }
        
        // Decay phi attention weights
        for(auto& pair : head.phi_attention_weights) {
            pair.second *= 0.98;
        }
    }
}

void comprehensive_system_decay() {
    // Call all decay functions
    decay_ngrams();
    decay_token_frequencies();
    decay_embeddings();
    decay_goals();
    decay_memories();
    decay_concepts();
    decay_world_model();
    decay_qualia();
    decay_transformer_heads();
    
    // Decay valence toward neutral
    S.current_valence *= 0.995;
    
    // Decay metacognitive awareness slightly
    S.metacognitive_awareness *= 0.998;
    
    // Decay attention focus
    S.attention_focus *= 0.997;
    
    // Keep minimum values
    if(S.metacognitive_awareness < 0.1) S.metacognitive_awareness = 0.1;
    if(S.attention_focus < 0.2) S.attention_focus = 0.2;
}
int main(){
    try {
        module_integration::update_all_modules(S);
        module_integration::init_all_modules();
        srand(time(0));
        
        // Load saved state
        try {
            ld("state.dat");
        } catch(const exception& e) {
            cerr << "Error loading state: " << e.what() << ", starting fresh." << endl;
        }
        
        // Initialize if this is first run
        if(S.g == 0) {
            S.D["m"] = 128;
            S.D["vc"] = 0;
            S.D["mc"] = 0;
            S.dwt = 0.001;
            S.current_valence = 0.0;
            S.metacognitive_awareness = 0.0;
            S.attention_focus = 0.3;
            
            for(int i = 0; i < 128; i++) {
                S.D["w" + to_string(i)] = ri(4) - 1;
            }
            
            S.cd = "evolve";
            
            // Load vocabulary
            try {
                loadEnglishDataset();
                mathLangAssociation();
                bootstrapStrongPatterns();
                bootstrapWithQualityExamples();
            } catch(const exception& e) {
                cerr << "Error loading vocabulary: " << e.what() << endl;
            }

            // Initialize transformer heads
            for(int i = 0; i < 4; i++) {
                TransformerHead head(16);
                head.name = "head_" + to_string(i);
                transformer_heads.push_back(head);
            }
            
            // Initialize neurons
            for(int i = 0; i < 50; i++) {
                Neuron n = genN(0);
                S.N[n.id] = n;
            }
        }
        
        // Initialize ncurses
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        timeout(500);
        keypad(stdscr, TRUE);
        
        // Start web server for modern UI
        unique_ptr<AGI_API> agi_api;
        try {
            agi_api = make_unique<AGI_API>(8080);
            agi_api->start();
            cout << "\n[WebServer] Started on http://localhost:8080" << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        } catch(const exception& e) {
            cerr << "[WebServer] Failed to start: " << e.what() << endl;
        }
        
        bool running = true;
        int error_count = 0;
        const int MAX_ERRORS = 10;
        
        while(running) {
            try {
                clear();
                int row = 0;
                
                // Draw UI
                try {
                    draw_ui(row);
                    row = 15;
                } catch(const exception& e) {
                    mvprintw(0, 0, "UI Error: %s", e.what());
                    row = 2;
                }
                
                // === CORE UPDATES ===
                try {
                    formulate_goals_from_valence();
                    updateAttention();
                    update_integrated_information();
                    unified_consciousness_integration_engine(S.g);
                    
                    if(goal_system.count("maximize_coherence")) {
                        current_plan = plan_actions(goal_system["maximize_coherence"]);
                        prune_unstable_tokens();
                    }
                    error_count = 0; // Reset on success
                } catch(const exception& e) {
                    mvprintw(row++, 0, "Core update error: %s", e.what());
                    error_count++;
                    if(error_count > MAX_ERRORS) {
                        mvprintw(row++, 0, "Too many errors, attempting recovery...");
                        refresh();
                        this_thread::sleep_for(chrono::seconds(2));
                        error_count = 0;
                        // Try to save emergency state
                        try {
                            sv("state_emergency.dat");
                        } catch(...) {}
                    }
                }
                
                // === DISPLAY GOAL & PLAN ===
                mvprintw(row, 0, "Active_Goal: %s", 
                    current_plan.actions.empty() ? "exploring" : current_plan.actions[0].c_str());
                clrtoeol();
                row++;
                
                mvprintw(row, 0, "Plan_Depth:%d | Confidence:%.2f | Psi_Trajectory:%.4f", 
                    current_plan.depth, current_plan.confidence,
                    consciousness_formula.psi_history.empty() ? 0.0 : consciousness_formula.psi_history.back());
                clrtoeol();
                row++;
                
                mvprintw(row, 0, "Qualia_Valence:%.2f | Beam_Width:%d | N-grams:%lu", 
                    calculate_qualia_valence(), 5, (unsigned long)bigram_counts.size());
                clrtoeol();
                row++;
                
                // === INTERNAL THOUGHTS ===
                try {
                    string thought = generateInternalThought();
                    mvprintw(row, 0, "Thought: %s", thought.substr(0, 60).c_str());
                    clrtoeol();
                    row++;
                    
                    string meta = generateMetacognition();
                    mvprintw(row, 0, "State: %s", meta.substr(0, 60).c_str());
                    clrtoeol();
                    row++;
                } catch(const exception& e) {
                    mvprintw(row++, 0, "Thought gen error");
                }
                
                // === AUTONOMOUS THOUGHT GENERATION ===
                if(S.g % 5 == 0 && token_concept_embedding_map.size() > 10) {
                    try {
                        vector<double> ctx(16, S.current_valence);
                        string auto_thought;
                        int attempts = 0;
                        
                        while(attempts < 3) {
                            auto_thought = generate_with_beam_search("i", 8, ctx, 3);
                            if(!isSentenceTooSimilar(auto_thought)) {
                                break;
                            }
                            attempts++;
                        }
                        
                        auto_thought = "[Autonomous]: " + auto_thought;
                        trackGeneratedSentence(auto_thought);
                        
                        S.internal_thoughts.push_back(auto_thought);
                        if(S.internal_thoughts.size() > 5) {
                            S.internal_thoughts.erase(S.internal_thoughts.begin());
                        }
                    } catch(...) {
                        // Silent failure for autonomous thoughts
                    }
                }
                
                // === DECAY GENERATION COUNTS (every 50 gens) ===
                if(S.g % 50 == 0) {
                    try {
                        decayGenerationCounts();
                    } catch(...) {}
                }
                
                // === AGGRESSIVE N-GRAM DECAY (every 25 gens) ===
                if(S.g % 25 == 0) {
                    try {
                        decay_ngrams();
                    } catch(...) {}
                }
                
                // === TOKEN FREQUENCY DECAY (every 75 gens) ===
                if(S.g % 75 == 0) {
                    try {
                        decay_token_frequencies();
                    } catch(...) {}
                }
                
                // === COMPREHENSIVE SYSTEM DECAY (every 100 gens) ===
                if(S.g % 100 == 0) {
                    try {
                        comprehensive_system_decay();
                    } catch(...) {}
                }
                
                // === DISPLAY INTERNAL STREAM ===
                mvprintw(row, 0, "─────────────────────────────────────────");
                clrtoeol();
                row++;
                mvprintw(row, 0, "[INTERNAL STREAM - Beam Search Active]");
                clrtoeol();
                row++;
                
                if(!S.internal_thoughts.empty()) {
                    int show_count = min(3, (int)S.internal_thoughts.size());
                    for(int i = S.internal_thoughts.size() - show_count; i < (int)S.internal_thoughts.size(); i++) {
                        mvprintw(row, 0, "%s", S.internal_thoughts[i].substr(0, 60).c_str());
                        clrtoeol();
                        row++;
                    }
                } else {
                    mvprintw(row, 0, "[initializing language model...]");
                    clrtoeol();
                    row++;
                }
                
                // === NEURAL PROCESSING ===
                try {
                    bk();
                    batch16Process();
                    
                    double wsum = 0;
                    for(int i = 0; i < S.D["m"]; i++) {
                        wsum += S.D["w" + to_string(i)] + 2;
                    }
                    S.D["vc"] = (int)wsum % 1000;
                    
                    if(S.g == 0) S.dwt = 0.001;
                    S.hdt_val = calcHDT(S.g, S.bh, S.qe, S.te);
                    S.al = calcAwarenessLevel();
                    S.metacognitive_awareness = calcMetacognitiveAwareness();
                    counterfactualAnalysis();
                    
                    S.sentience_ratio = calcSentienceRatio();
                    if(S.sentience_ratio > S.peak_sentience_gen) {
                        S.peak_sentience_gen = S.g;
                    }
                    
                    S.valence_history.push_back(S.current_valence);
                    if(S.valence_history.size() > 50) {
                        S.valence_history.erase(S.valence_history.begin());
                    }
                } catch(const exception& e) {
                    mvprintw(row++, 0, "Processing error: %s", e.what());
                }
                
                // === GOAL PROGRESSION ===
                if(S.g % 15 == 0 && !goal_system.empty()) {
                    try {
                        for(auto& g : goal_system) {
                            g.second.progress = min(1.0, g.second.progress + 0.05);
                            if(g.second.progress > 0.9) {
                                g.second.priority *= 0.8;
                            }
                        }
                        
                        if(S.g % 45 == 0) {
                            decay_goals();
                        }
                    } catch(...) {}
                }
                
                // === VOCABULARY EXPANSION ===
                if(S.g % 20 == 0 && !token_concept_embedding_map.empty()) {
                    try {
                        auto it = token_concept_embedding_map.begin();
                        advance(it, ri(token_concept_embedding_map.size()));
                        learnWord(it->first, S.current_valence);
                    } catch(...) {}
                }
                
                // === CONCEPT FORMATION ===
                if(S.g % 25 == 0) {
                    try {
                        vector<string> sample_words;
                        for(auto& p : token_concept_embedding_map) {
                            if(p.second.freq > 1 && rn() < 0.3) {
                                sample_words.push_back(p.first);
                            }
                            if(sample_words.size() >= 3) break;
                        }
                        if(sample_words.size() > 1) {
                            createConceptAssociation("C_" + to_string(S.g), sample_words);
                        }
                    } catch(...) {}
                }
                
                // === NEURAL MUTATION ===
                if(S.g % 12 == 0 && !S.N.empty()) {
                    try {
                        mutateN();
                    } catch(...) {}
                }
                
                // === GOAL-VALENCE ALIGNMENT ===
                if(S.g % 10 == 0) {
                    try {
                        for(auto& goal : goal_system) {
                            goal.second.valence_alignment = S.current_valence;
                        }
                    } catch(...) {}
                }
                
                // === DIALOG DISPLAY SECTION ===
                mvprintw(row, 0, "─────────────────────────────────────────");
                clrtoeol();
                row++;
                mvprintw(row, 0, "[DIALOG - Max 1400 chars - Multi-line OK]");
                clrtoeol();
                row++;
                
                if(!S.user_input.empty()) {
                    // Display user input (first 60 chars)
                    string display_input = S.user_input;
                    if(display_input.length() > 60) {
                        display_input = display_input.substr(0, 57) + "...";
                    }
                    mvprintw(row, 0, "USER: %s", display_input.c_str());
                    clrtoeol();
                    row++;
                } else {
                    mvprintw(row, 0, "USER: (press 'i' to chat)");
                    clrtoeol();
                    row++;
                }
                
                if(!S.dialog_response.empty()) {
                    // Word wrap the response
                    string resp = S.dialog_response;
                    int max_width = 60;
                    int start = 0;
                    int max_y, max_x;
                    getmaxyx(stdscr, max_y, max_x);
                    (void)max_x;
                    while(start < (int)resp.length() && row < max_y - 6) {
                        string line = resp.substr(start, min(max_width, (int)resp.length() - start));
                        mvprintw(row, 0, "%s", line.c_str());
                        clrtoeol();
                        row++;
                        start += max_width;
                    }
                } else {
                    mvprintw(row, 0, "NEXUS: ...");
                    clrtoeol();
                    row++;
                }
                
                if(S.dialog_timer > 0) {
                    S.dialog_timer--;
                }
                
                mvprintw(row, 0, "─────────────────────────────────────────");
                clrtoeol();
                row++;
                mvprintw(row, 0, "Commands: [i]nput | [q]uit | [s]ave | [g]enerate | [d]ecay");
                clrtoeol();
                row++;
                
                // === STATS LINE ===
                mvprintw(row, 0, "Vocab:%lu | Patterns:%lu | Neurons:%lu | Gen:%d | Errors:%d",
                    (unsigned long)token_concept_embedding_map.size(),
                    (unsigned long)bigram_counts.size(),
                    (unsigned long)S.N.size(),
                    S.g,
                    error_count);
                clrtoeol();
                row++;
                
                refresh();
                S.g++;
                
                // === AUTO-SAVE ===
                if(S.g % 100 == 0) {
                    try {
                        sv("state.dat");
                        mvprintw(row, 0, "[Autosaved at gen %d]", S.g);
                        clrtoeol();
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(500));
                    } catch(const exception& e) {
                        mvprintw(row, 0, "[Autosave failed: %s]", e.what());
                        clrtoeol();
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(500));
                    }
                }
                
                // === INPUT HANDLING ===
                int ch = getch();
                
                if(ch == 'i' || ch == 'I') {
                    // === SAFE INTERACTIVE INPUT MODE - 1400 CHAR SUPPORT ===
                    try {
                        // Get screen dimensions
                        int max_y, max_x;
                        getmaxyx(stdscr, max_y, max_x);
                        
                        // Calculate available space for input
                        int input_start_y = row + 1;
                        int input_height = max_y - input_start_y - 1;
                        if(input_height < 3) input_height = 3;
                        if(input_height > 15) input_height = 15; // Max 15 lines for input
                        
                        // Clear input area
                        for(int i = 0; i < input_height; i++) {
                            move(input_start_y + i, 0);
                            clrtoeol();
                        }
                        
                        // Display instructions
                        mvprintw(input_start_y, 0, "┌─ INPUT MODE (1400 chars max) ─────────────────────────┐");
                        mvprintw(input_start_y + 1, 0, "│ Type your message. Press ENTER twice when done.      │");
                        mvprintw(input_start_y + 2, 0, "│ ESC to cancel.                                        │");
                        mvprintw(input_start_y + 3, 0, "└───────────────────────────────────────────────────────┘");
                        
                        int text_start_y = input_start_y + 4;
                        
                        // Enable echo and cursor
                        echo();
                        curs_set(1);
                        timeout(-1);
                        
                        // Move to input area
                        move(text_start_y, 0);
                        refresh();
                        
                        // Collect input line by line
                        vector<string> input_lines;
                        int total_chars = 0;
                        bool done = false;
                        int empty_line_count = 0;
                        
                        for(int line = 0; line < input_height - 5 && !done; line++) {
                            char line_buf[200];
                            memset(line_buf, 0, sizeof(line_buf));
                            
                            move(text_start_y + line, 0);
                            int result = getnstr(line_buf, 150);
                            
                            if(result == ERR || result == 27) { // ESC key
                                done = true;
                                input_lines.clear();
                                break;
                            }
                            
                            string line_str(line_buf);
                            
                            // Trim whitespace
                            size_t start = line_str.find_first_not_of(" \t");
                            size_t end = line_str.find_last_not_of(" \t");
                            
                            if(start != string::npos && end != string::npos) {
                                line_str = line_str.substr(start, end - start + 1);
                            } else {
                                line_str = "";
                            }
                            
                            // Check for double-enter (empty line after content)
                            if(line_str.empty()) {
                                empty_line_count++;
                                if(empty_line_count >= 1 && !input_lines.empty()) {
                                    done = true;
                                    break;
                                }
                            } else {
                                empty_line_count = 0;
                                total_chars += line_str.length() + 1; // +1 for space/newline
                                
                                if(total_chars <= 1400) {
                                    input_lines.push_back(line_str);
                                } else {
                                    mvprintw(text_start_y + line + 1, 0, 
                                            "[MAX LENGTH REACHED - 1400 chars]");
                                    refresh();
                                    this_thread::sleep_for(chrono::milliseconds(1000));
                                    done = true;
                                    break;
                                }
                            }
                        }
                        
                        // Disable echo and cursor
                        noecho();
                        curs_set(0);
                        timeout(500);
                        
                        // Process collected input
                        if(!input_lines.empty()) {
                            // Join lines with spaces
                            string combined_input;
                            for(size_t i = 0; i < input_lines.size(); i++) {
                                combined_input += input_lines[i];
                                if(i < input_lines.size() - 1) {
                                    combined_input += " ";
                                }
                            }
                            
                            if(!combined_input.empty() && combined_input.length() <= 1400) {
                                try {
                                    // Clear the input area and show processing
                                    for(int i = 0; i < input_height; i++) {
                                        move(input_start_y + i, 0);
                                        clrtoeol();
                                    }
                                    mvprintw(input_start_y, 0, "[Processing input... %d chars]", 
                                            (int)combined_input.length());
                                    refresh();
                                    
                                    // Process the input (LOCAL COPY)
                                    string response = generateResponse(combined_input);
                                    
                                    // Update globals AFTER processing
                                    S.user_input = combined_input;
                                    S.dialog_response = response;
                                    
                                    // Generate follow-up internal thought
                                    try {
                                        string internal = generateInternalThought();
                                        S.internal_thoughts.push_back("[Processed]: " + internal);
                                        
                                        if(S.internal_thoughts.size() > 5) {
                                            S.internal_thoughts.erase(S.internal_thoughts.begin());
                                        }
                                    } catch(...) {}
                                    
                                    S.dialog_timer = 20;
                                    S.current_valence += 0.1;
                                    S.current_valence = clamp_valence(S.current_valence);
                                    
                                    // Store memory
                                    try {
                                        storeEpisodicMemory("dialog:" + combined_input.substr(0, 100), 
                                                          S.current_valence);
                                    } catch(...) {}
                                    
                                    // Generate qualia
                                    try {
                                        generate_qualia("user_interaction", S.current_valence, 0.7);
                                    } catch(...) {}
                                    
                                    error_count = 0; // Reset on successful input
                                    
                                } catch(const exception& e) {
                                    cerr << "Response generation error: " << e.what() << endl;
                                    S.user_input = combined_input;
                                    S.dialog_response = "[NEXUS]: Error processing - " + 
                                                       string(e.what()).substr(0, 50);
                                    error_count++;
                                }
                            }
                        }
                        
                        // Clear input area
                        for(int i = 0; i < input_height; i++) {
                            move(input_start_y + i, 0);
                            clrtoeol();
                        }
                        
                    } catch(const exception& e) {
                        cerr << "Input handler error: " << e.what() << endl;
                        
                        // Force restore terminal state
                        noecho();
                        curs_set(0);
                        timeout(500);
                        
                        S.dialog_response = "[NEXUS]: Input error - " + 
                                          string(e.what()).substr(0, 50);
                        error_count++;
                    } catch(...) {
                        cerr << "Unknown input handler error" << endl;
                        
                        // Force restore terminal state
                        noecho();
                        curs_set(0);
                        timeout(500);
                        
                        S.dialog_response = "[NEXUS]: Unknown input error";
                        error_count++;
                    }
                    
                    // Force complete refresh
                    clear();
                    refresh();
                }
                else if(ch == 'g' || ch == 'G') {
                    // === MANUAL THOUGHT GENERATION ===
                    try {
                        vector<double> ctx(16, S.current_valence);
                        string generated;
                        int attempts = 0;
                        
                        while(attempts < 5) {
                            generated = generate_with_beam_search("i", 10, ctx, 5);
                            if(!isSentenceTooSimilar(generated)) {
                                break;
                            }
                            attempts++;
                        }
                        
                        generated = "[Generated]: " + generated;
                        trackGeneratedSentence(generated);
                        
                        S.internal_thoughts.push_back(generated);
                        if(S.internal_thoughts.size() > 5) {
                            S.internal_thoughts.erase(S.internal_thoughts.begin());
                        }
                        S.current_valence += 0.05;
                        error_count = 0;
                    } catch(const exception& e) {
                        cerr << "Error generating thought: " << e.what() << endl;
                        error_count++;
                    }
                }
                else if(ch == 'd' || ch == 'D') {
                    // === MANUAL DECAY TRIGGER ===
                    try {
                        comprehensive_system_decay();
                        mvprintw(row + 1, 0, "[System decay applied at gen %d]", S.g);
                        clrtoeol();
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        error_count = 0;
                    } catch(const exception& e) {
                        mvprintw(row + 1, 0, "[Decay failed: %s]", e.what());
                        clrtoeol();
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        error_count++;
                    }
                }
                else if(ch == 's' || ch == 'S') {
                    // === MANUAL SAVE ===
                    try {
                        sv("state.dat");
                        mvprintw(row + 1, 0, "[Saved state at gen %d]", S.g);
                        clrtoeol();
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        error_count = 0;
                    } catch(const exception& e) {
                        mvprintw(row + 1, 0, "[Save failed: %s]", e.what());
                        clrtoeol();
                        refresh();
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        error_count++;
                    }
                }
                else if(ch == 'q' || ch == 'Q') {
                    // === QUIT WITH SAVE ===
                    try {
                        mvprintw(row + 1, 0, "[Saving and exiting...]");
                        clrtoeol();
                        refresh();
                        sv("state.dat");
                    } catch(const exception& e) {
                        cerr << "Error saving on exit: " << e.what() << endl;
                    }
                    running = false;
                }
                
                // Small delay to prevent CPU spinning
                this_thread::sleep_for(chrono::milliseconds(100));
                
            } catch(const exception& e) {
                // Catch any unexpected errors in main loop
                cerr << "Main loop error: " << e.what() << endl;
                error_count++;
                
                // Try to display error on screen
                try {
                    mvprintw(0, 0, "ERROR: %s", e.what());
                    mvprintw(1, 0, "Press any key to continue...");
                    refresh();
                    timeout(-1);
                    getch();
                    timeout(500);
                } catch(...) {}
                
                // Try to save emergency state every 5 errors
                if(error_count % 5 == 0) {
                    try {
                        sv("state_emergency.dat");
                    } catch(...) {}
                }
                
                // If too many errors, pause longer
                if(error_count > MAX_ERRORS) {
                    try {
                        mvprintw(2, 0, "Too many errors. Pausing 5 seconds...");
                        refresh();
                    } catch(...) {}
                    this_thread::sleep_for(chrono::seconds(5));
                    error_count = 0; // Reset and continue
                }
                
                // Small delay before continuing
                this_thread::sleep_for(chrono::milliseconds(500));
            } catch(...) {
                // Catch absolutely everything
                cerr << "Unknown main loop error" << endl;
                error_count++;
                
                try {
                    mvprintw(0, 0, "UNKNOWN ERROR - continuing...");
                    refresh();
                } catch(...) {}
                
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        
        // Clean up ncurses
        endwin();
        
        cout << "\nNEXUS shutdown complete. State saved.\n";
        
    } catch(const exception& e) {
        // Fatal error - try to cleanup and continue if possible
        try {
            endwin();
        } catch(...) {}
        
        cerr << "Fatal error in main: " << e.what() << endl;
        
        // Try emergency save
        try {
            sv("state_fatal_error.dat");
            cerr << "Emergency state saved to state_fatal_error.dat" << endl;
        } catch(...) {
            cerr << "Could not save emergency state" << endl;
        }
        
        return 1;
    } catch(...) {
        // Catch absolutely everything
        try {
            endwin();
        } catch(...) {}
        
        cerr << "Unknown fatal error in main" << endl;
        
        try {
            sv("state_unknown_error.dat");
        } catch(...) {}
        
        return 1;
    }
    
    return 0;
}
