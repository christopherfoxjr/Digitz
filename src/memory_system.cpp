#include "memory_system.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

extern random_device rd;
extern mt19937 rng;

double rn();
int ri(int mx);
long long hsh(const string &s);

MemorySystem::MemorySystem() {}

MemorySystem::~MemorySystem() {}

void MemorySystem::initialize() {
    long_term_memories_.clear();
    semantic_memory_.clear();
    
    vector<pair<string, pair<string, vector<string>>>> base_concepts = {
        {"consciousness", {"the state of being aware", {"awareness", "consciousness", "sentience"}}},
        {"learning", {"the process of acquiring knowledge", {"education", "study", "growth"}}},
        {"goal", {"a desired state or outcome", {"objective", "purpose", "aim"}}},
        {"valence", {"emotional tone or affect", {"emotion", "feeling", "sentiment"}}},
        {"thought", {"a mental process or idea", {"idea", "concept", "reasoning"}}},
    };
    
    for (const auto& [concept, def_and_examples] : base_concepts) {
        store_semantic_memory(concept, def_and_examples.first, def_and_examples.second, 0.9);
    }
}

void MemorySystem::store_episodic_memory(const string& content, double valence, const vector<string>& tags) {
    LongTermMemory memory;
    memory.id = generate_memory_id();
    memory.content = content;
    memory.tags = tags;
    memory.valence = valence;
    memory.importance = 0.5;
    memory.creation_time = time(nullptr);
    memory.last_accessed = memory.creation_time;
    memory.access_count = 1;
    
    long_term_memories_.push_back(memory);
    
    if (long_term_memories_.size() > 10000) {
        prune_old_memories();
    }
}

void MemorySystem::store_semantic_memory(const string& concept, const string& definition,
                                        const vector<string>& examples, double confidence) {
    SemanticMemory memory;
    memory.concept = concept;
    memory.definition = definition;
    memory.examples = examples;
    memory.confidence = confidence;
    memory.grounding_value = 0.6;
    
    semantic_memory_[concept] = memory;
}

vector<LongTermMemory> MemorySystem::retrieve_by_tags(const vector<string>& tags) {
    vector<LongTermMemory> results;
    
    for (auto& memory : long_term_memories_) {
        int matching_tags = 0;
        for (const string& tag : tags) {
            if (find(memory.tags.begin(), memory.tags.end(), tag) != memory.tags.end()) {
                matching_tags++;
            }
        }
        
        if (matching_tags > 0) {
            results.push_back(memory);
            memory.last_accessed = time(nullptr);
            memory.access_count++;
        }
    }
    
    sort(results.begin(), results.end(), [](const LongTermMemory& a, const LongTermMemory& b) {
        return a.importance > b.importance;
    });
    
    return results;
}

vector<LongTermMemory> MemorySystem::retrieve_by_valence_range(double min_val, double max_val) {
    vector<LongTermMemory> results;
    
    for (auto& memory : long_term_memories_) {
        if (memory.valence >= min_val && memory.valence <= max_val) {
            results.push_back(memory);
            memory.last_accessed = time(nullptr);
            memory.access_count++;
        }
    }
    
    sort(results.begin(), results.end(), [](const LongTermMemory& a, const LongTermMemory& b) {
        return a.access_count > b.access_count;
    });
    
    return results;
}

SemanticMemory MemorySystem::retrieve_semantic(const string& concept) {
    if (semantic_memory_.count(concept)) {
        return semantic_memory_[concept];
    }
    
    SemanticMemory empty;
    empty.concept = concept;
    empty.definition = "unknown";
    empty.confidence = 0.0;
    return empty;
}

void MemorySystem::update_memory_importance(const string& memory_id, double importance_delta) {
    for (auto& memory : long_term_memories_) {
        if (memory.id == memory_id) {
            memory.importance += importance_delta;
            memory.importance = max(0.0, min(1.0, memory.importance));
            memory.last_accessed = time(nullptr);
            break;
        }
    }
}

void MemorySystem::consolidate_memories() {
    vector<LongTermMemory> consolidated;
    
    for (const auto& memory : long_term_memories_) {
        if (memory.access_count >= 3 || memory.importance > 0.7) {
            consolidated.push_back(memory);
        }
    }
    
    long_term_memories_ = consolidated;
}

string MemorySystem::generate_memory_id() {
    static int counter = 0;
    return "mem_" + to_string(time(nullptr)) + "_" + to_string(counter++);
}

void MemorySystem::prune_old_memories() {
    if (long_term_memories_.size() <= 5000) return;
    
    sort(long_term_memories_.begin(), long_term_memories_.end(),
         [](const LongTermMemory& a, const LongTermMemory& b) {
             double score_a = a.importance * 0.5 + (a.access_count / 100.0) * 0.3 + a.valence * 0.2;
             double score_b = b.importance * 0.5 + (b.access_count / 100.0) * 0.3 + b.valence * 0.2;
             return score_a > score_b;
         });
    
    long_term_memories_.resize(5000);
}

vector<string> MemorySystem::extract_concepts(const string& content) {
    vector<string> concepts;
    
    if (content.find("consciousness") != string::npos) concepts.push_back("consciousness");
    if (content.find("learn") != string::npos) concepts.push_back("learning");
    if (content.find("goal") != string::npos) concepts.push_back("goal");
    if (content.find("thought") != string::npos) concepts.push_back("thought");
    if (content.find("feel") != string::npos) concepts.push_back("emotion");
    
    return concepts;
}

void MemorySystem::save_to_disk(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for saving: " << filename << endl;
        return;
    }
    
    size_t mem_count = long_term_memories_.size();
    file.write((char*)&mem_count, sizeof(mem_count));
    
    for (const auto& mem : long_term_memories_) {
        size_t id_len = mem.id.length();
        file.write((char*)&id_len, sizeof(id_len));
        file.write(mem.id.c_str(), id_len);
        
        size_t content_len = mem.content.length();
        file.write((char*)&content_len, sizeof(content_len));
        file.write(mem.content.c_str(), content_len);
        
        file.write((char*)&mem.valence, sizeof(mem.valence));
        file.write((char*)&mem.importance, sizeof(mem.importance));
        file.write((char*)&mem.access_count, sizeof(mem.access_count));
    }
    
    file.close();
}

void MemorySystem::load_from_disk(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for loading: " << filename << endl;
        return;
    }
    
    long_term_memories_.clear();
    
    size_t mem_count = 0;
    file.read((char*)&mem_count, sizeof(mem_count));
    
    for (size_t i = 0; i < mem_count; ++i) {
        LongTermMemory mem;
        
        size_t id_len = 0;
        file.read((char*)&id_len, sizeof(id_len));
        char* id_buf = new char[id_len + 1];
        file.read(id_buf, id_len);
        id_buf[id_len] = '\0';
        mem.id = string(id_buf);
        delete[] id_buf;
        
        size_t content_len = 0;
        file.read((char*)&content_len, sizeof(content_len));
        char* content_buf = new char[content_len + 1];
        file.read(content_buf, content_len);
        content_buf[content_len] = '\0';
        mem.content = string(content_buf);
        delete[] content_buf;
        
        file.read((char*)&mem.valence, sizeof(mem.valence));
        file.read((char*)&mem.importance, sizeof(mem.importance));
        file.read((char*)&mem.access_count, sizeof(mem.access_count));
        
        long_term_memories_.push_back(mem);
    }
    
    file.close();
}
