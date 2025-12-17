#pragma once
#ifndef MEMORY_SYSTEM_H
#define MEMORY_SYSTEM_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

struct LongTermMemory {
    std::string id;
    std::string content;
    std::vector<std::string> tags;
    double valence;
    double importance;
    time_t creation_time;
    time_t last_accessed;
    int access_count;
};

struct SemanticMemory {
    std::string concept;
    std::string definition;
    std::vector<std::string> examples;
    double confidence;
    double grounding_value;
};

class MemorySystem {
public:
    MemorySystem();
    ~MemorySystem();
    
    void initialize();
    
    void store_episodic_memory(const std::string& content, double valence, const std::vector<std::string>& tags);
    
    void store_semantic_memory(const std::string& concept, const std::string& definition, 
                               const std::vector<std::string>& examples, double confidence);
    
    std::vector<LongTermMemory> retrieve_by_tags(const std::vector<std::string>& tags);
    
    std::vector<LongTermMemory> retrieve_by_valence_range(double min_val, double max_val);
    
    SemanticMemory retrieve_semantic(const std::string& concept);
    
    void update_memory_importance(const std::string& memory_id, double importance_delta);
    
    void consolidate_memories();
    
    void save_to_disk(const std::string& filename);
    
    void load_from_disk(const std::string& filename);
    
    int get_total_memories() const { return long_term_memories_.size(); }
    
    int get_semantic_knowledge_count() const { return semantic_memory_.size(); }
    
private:
    std::vector<LongTermMemory> long_term_memories_;
    std::map<std::string, SemanticMemory> semantic_memory_;
    
    std::string generate_memory_id();
    
    void prune_old_memories();
    
    std::vector<std::string> extract_concepts(const std::string& content);
};

#endif // MEMORY_SYSTEM_H
