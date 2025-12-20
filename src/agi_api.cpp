#include "agi_api.h"
#include "module_integration.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <chrono>

// Forward declare the generateResponse function
extern std::string generateResponse(const std::string& input);
extern void sv(const std::string& filename);
extern void ld(const std::string& filename);

AGI_API::AGI_API(int port) : server_(std::make_unique<WebServer>(port)) {
    server_->register_route("POST", "/api/chat", [this](const HttpRequest& req) { return handle_chat(req); });
    server_->register_route("GET", "/api/status", [this](const HttpRequest& req) { return handle_status(req); });
    server_->register_route("GET", "/api/consciousness", [this](const HttpRequest& req) { return handle_consciousness(req); });
    server_->register_route("GET", "/api/thoughts", [this](const HttpRequest& req) { return handle_thoughts(req); });
    server_->register_route("GET", "/api/memory", [this](const HttpRequest& req) { return handle_memory(req); });
    server_->register_route("GET", "/api/goals", [this](const HttpRequest& req) { return handle_goals(req); });
    server_->register_route("GET", "/api/valence", [this](const HttpRequest& req) { return handle_valence(req); });
    server_->register_route("GET", "/api/history", [this](const HttpRequest& req) { return handle_history(req); });
    server_->register_route("POST", "/api/save", [this](const HttpRequest& req) { return handle_save(req); });
    server_->register_route("POST", "/api/load", [this](const HttpRequest& req) { return handle_load(req); });
    server_->register_route("POST", "/api/clear", [this](const HttpRequest& req) { return handle_clear(req); });
    server_->register_route("GET", "/", [this](const HttpRequest& req) { return handle_ui(req); });
}

AGI_API::~AGI_API() {
    stop();
}

void AGI_API::start() {
    server_->start();
}

void AGI_API::stop() {
    server_->stop();
}

std::string AGI_API::json_escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default:
                if (c < 32) {
                    oss << "\\u" << std::hex << std::setfill('0') << std::setw(4) << (int)c;
                } else {
                    oss << c;
                }
        }
    }
    return oss.str();
}

HttpResponse AGI_API::handle_chat(const HttpRequest& req) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::string message;
    size_t msg_pos = req.body.find("\"message\":");
    if (msg_pos != std::string::npos) {
        size_t start = req.body.find('"', msg_pos + 10) + 1;
        size_t end = req.body.find('"', start);
        message = req.body.substr(start, end - start);
    }
    
    try {
        std::string response = generateResponse(message);
        
        std::ostringstream oss;
        oss << "{\"status\": \"ok\", \"response\": \"" << json_escape(response) 
            << "\", \"valence\": " << std::fixed << std::setprecision(3) << S.current_valence
            << ", \"generation\": " << S.g << "}";
        resp.body = oss.str();
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << "{\"status\": \"error\", \"message\": \"" << json_escape(e.what()) << "\"}";
        resp.body = oss.str();
        resp.status_code = 500;
    }
    
    return resp;
}

HttpResponse AGI_API::handle_status(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{"
        << "\"generation\": " << S.g << ", "
        << "\"vocab_size\": " << S.vocab.size() << ", "
        << "\"current_valence\": " << S.current_valence << ", "
        << "\"sentience_ratio\": " << S.sentience_ratio << ", "
        << "\"metacognitive_awareness\": " << S.metacognitive_awareness << ", "
        << "\"attention_focus\": " << S.attention_focus << ", "
        << "\"phi_value\": " << S.consciousness_metrics.phi << ", "
        << "\"integrated_information\": " << S.consciousness_metrics.integrated_info << ", "
        << "\"conscious_cycles\": " << S.consciousness_metrics.awareness_cycles
        << "}";
    
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_consciousness(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{"
        << "\"active_qualia\": " << S.consciousness_metrics.qualia_intensity << ", "
        << "\"integrated_information\": " << S.consciousness_metrics.integrated_info << ", "
        << "\"phi_value\": " << S.consciousness_metrics.phi << ", "
        << "\"global_workspace_capacity\": " << S.consciousness_metrics.global_workspace << ", "
        << "\"conscious_cycles\": " << S.consciousness_metrics.awareness_cycles << ", "
        << "\"psi_history_length\": " << S.psi_history.size();
    
    if (!S.psi_history.empty()) {
        oss << ", \"latest_psi\": " << S.psi_history.back();
        double avg_psi = 0;
        for (double p : S.psi_history) {
            avg_psi += p;
        }
        avg_psi /= S.psi_history.size();
        oss << ", \"avg_psi\": " << avg_psi;
    }
    
    oss << ", \"qualia_valences\": [";
    size_t qualia_count = std::min((size_t)10, S.qualia_buffer.size());
    for (size_t i = 0; i < qualia_count; ++i) {
        if (i > 0) oss << ", ";
        oss << S.qualia_buffer[i].valence;
    }
    oss << "]}";
    
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_thoughts(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << "{\"thoughts\": [";
    
    size_t count = std::min((size_t)10, S.internal_thoughts.size());
    for (size_t i = 0; i < count; ++i) {
        if (i > 0) oss << ", ";
        oss << "\"" << json_escape(S.internal_thoughts[i]) << "\"";
    }
    
    oss << "]}";
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_memory(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{"
        << "\"episodic_memory_size\": " << S.episodic_memory.size() << ", "
        << "\"working_memory_tokens\": " << S.working_memory_tokens.size() << ", "
        << "\"working_memory_concepts\": " << S.working_memory_concepts.size();
    
    if (!S.episodic_memory.empty()) {
        oss << ", \"latest_memories\": [";
        size_t count = std::min((size_t)5, S.episodic_memory.size());
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) oss << ", ";
            oss << "{\"valence\": " << S.episodic_memory[i].valence 
                << ", \"content\": \"" << json_escape(S.episodic_memory[i].content) << "\"}";
        }
        oss << "]";
    }
    
    oss << "}";
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_goals(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{\"goals\": [";
    
    size_t idx = 0;
    for (const auto& [name, goal] : S.goal_hierarchy) {
        if (idx > 0) oss << ", ";
        oss << "{"
            << "\"name\": \"" << json_escape(name) << "\", "
            << "\"priority\": " << goal.priority << ", "
            << "\"progress\": " << goal.progress << ", "
            << "\"valence_alignment\": " << goal.valence_weight << ", "
            << "\"qualia_binding\": " << goal.emotional_weight
            << "}";
        ++idx;
        if (idx >= 10) break;
    }
    
    oss << "]}";
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_valence(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{\"current_valence\": " << S.current_valence 
        << ", \"valence_history\": [";
    
    size_t count = std::min((size_t)50, S.valence_history.size());
    for (size_t i = 0; i < count; ++i) {
        if (i > 0) oss << ", ";
        oss << S.valence_history[i];
    }
    
    oss << "], \"min_valence\": ";
    double min_v = 0, max_v = 0;
    if (!S.valence_history.empty()) {
        min_v = max_v = S.valence_history[0];
        for (double v : S.valence_history) {
            if (v < min_v) min_v = v;
            if (v > max_v) max_v = v;
        }
    }
    oss << min_v << ", \"max_valence\": " << max_v << "}";
    
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_history(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    resp.body = "{\"history\": []}";
    return resp;
}

HttpResponse AGI_API::handle_save(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    try {
        sv("state.dat");
        resp.body = "{\"status\": \"saved\"}";
    } catch (const std::exception& e) {
        resp.status_code = 500;
        std::ostringstream oss;
        oss << "{\"status\": \"error\", \"message\": \"" << json_escape(e.what()) << "\"}";
        resp.body = oss.str();
    }
    
    return resp;
}

HttpResponse AGI_API::handle_load(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    
    try {
        ld("state.dat");
        resp.body = "{\"status\": \"loaded\"}";
    } catch (const std::exception& e) {
        resp.status_code = 500;
        std::ostringstream oss;
        oss << "{\"status\": \"error\", \"message\": \"" << json_escape(e.what()) << "\"}";
        resp.body = oss.str();
    }
    
    return resp;
}

HttpResponse AGI_API::handle_clear(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    resp.body = "{\"status\": \"cleared\"}";
    return resp;
}

HttpResponse AGI_API::handle_ui(const HttpRequest&) {
    HttpResponse resp;
    resp.status_code = 200;
    resp.headers["Content-Type"] = "text/html; charset=utf-8";
    
    resp.body = R"html(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Nexus - WolfTech Innovations</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
            background: #f8f9fa;
            color: #1a1a1a;
            height: 100vh;
            display: flex;
            flex-direction: column;
            overflow: hidden;
        }
        
        header {
            background: #ffffff;
            border-bottom: 1px solid #e5e5e5;
            padding: 20px 32px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            box-shadow: 0 1px 3px rgba(0, 0, 0, 0.05);
            z-index: 10;
        }
        
        .header-left {
            display: flex;
            align-items: center;
            gap: 16px;
        }
        
        .logo {
            width: 40px;
            height: 40px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            border-radius: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: 700;
            color: white;
            font-size: 20px;
            letter-spacing: -0.5px;
        }
        
        h1 {
            font-size: 22px;
            font-weight: 600;
            color: #1a1a1a;
            letter-spacing: -0.4px;
        }
        
        .header-right {
            display: flex;
            align-items: center;
            gap: 12px;
        }
        
        .status-indicator {
            display: flex;
            align-items: center;
            gap: 8px;
            font-size: 13px;
            color: #666;
            padding: 6px 12px;
            background: #f3f4f6;
            border-radius: 20px;
        }
        
        .status-dot {
            width: 8px;
            height: 8px;
            border-radius: 50%;
            background: #10b981;
            animation: pulse 2s ease-in-out infinite;
        }
        
        @keyframes pulse {
            0%, 100% { opacity: 1; transform: scale(1); }
            50% { opacity: 0.6; transform: scale(0.95); }
        }
        
        .header-button {
            padding: 8px 16px;
            background: transparent;
            border: 1px solid #e5e5e5;
            border-radius: 8px;
            font-size: 13px;
            cursor: pointer;
            transition: all 0.2s;
            color: #666;
        }
        
        .header-button:hover {
            background: #f3f4f6;
            border-color: #d1d5db;
        }
        
        .main-container {
            flex: 1;
            display: flex;
            overflow: hidden;
        }
        
        .sidebar {
            width: 280px;
            background: #ffffff;
            border-right: 1px solid #e5e5e5;
            display: flex;
            flex-direction: column;
            overflow: hidden;
        }
        
        .sidebar-header {
            padding: 20px;
            border-bottom: 1px solid #e5e5e5;
        }
        
        .sidebar-title {
            font-size: 14px;
            font-weight: 600;
            color: #666;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }
        
        .history-list {
            flex: 1;
            overflow-y: auto;
            padding: 12px;
        }
        
        .history-item {
            padding: 12px 16px;
            margin-bottom: 4px;
            border-radius: 8px;
            cursor: pointer;
            transition: all 0.2s;
            font-size: 14px;
            color: #666;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }
        
        .history-item:hover {
            background: #f3f4f6;
            color: #1a1a1a;
        }
        
        .history-item.active {
            background: #667eea;
            color: white;
        }
        
        .chat-container {
            flex: 1;
            display: flex;
            flex-direction: column;
            max-width: 900px;
            width: 100%;
            margin: 0 auto;
            padding: 0;
        }
        
        .messages {
            flex: 1;
            overflow-y: auto;
            padding: 32px 40px;
            display: flex;
            flex-direction: column;
            gap: 32px;
        }
        
        .message {
            display: flex;
            gap: 16px;
            animation: slideIn 0.4s cubic-bezier(0.16, 1, 0.3, 1);
            opacity: 0;
            animation-fill-mode: forwards;
        }
        
        @keyframes slideIn {
            from {
                opacity: 0;
                transform: translateY(20px) scale(0.98);
            }
            to {
                opacity: 1;
                transform: translateY(0) scale(1);
            }
        }
        
        .message-avatar {
            width: 40px;
            height: 40px;
            border-radius: 12px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 16px;
            font-weight: 600;
            flex-shrink: 0;
            transition: transform 0.3s cubic-bezier(0.34, 1.56, 0.64, 1);
        }
        
        .message:hover .message-avatar {
            transform: scale(1.05);
        }
        
        .message.user .message-avatar {
            background: linear-gradient(135deg, #f3f4f6 0%, #e5e7eb 100%);
            color: #666;
        }
        
        .message.ai .message-avatar {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: #ffffff;
            box-shadow: 0 4px 12px rgba(102, 126, 234, 0.3);
        }
        
        .message-content {
            flex: 1;
            padding-top: 4px;
        }
        
        .message-text {
            font-size: 15px;
            line-height: 1.7;
            color: #1a1a1a;
            word-wrap: break-word;
            padding: 16px 20px;
            border-radius: 12px;
            background: #ffffff;
            box-shadow: 0 1px 3px rgba(0, 0, 0, 0.05);
            transition: all 0.3s ease;
        }
        
        .message.user .message-text {
            background: #f8f9fa;
        }
        
        .message:hover .message-text {
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.08);
            transform: translateY(-1px);
        }
        
        .message-meta {
            font-size: 12px;
            color: #999;
            margin-top: 8px;
            display: flex;
            align-items: center;
            gap: 12px;
            padding: 0 4px;
        }
        
        .meta-badge {
            padding: 2px 8px;
            background: #f3f4f6;
            border-radius: 4px;
            font-size: 11px;
            font-weight: 500;
        }
        
        .input-container {
            padding: 24px 40px 32px;
            background: #ffffff;
            border-top: 1px solid #e5e5e5;
        }
        
        .input-wrapper {
            display: flex;
            gap: 12px;
            align-items: flex-end;
            max-width: 900px;
            margin: 0 auto;
        }
        
        .input-field {
            flex: 1;
            padding: 16px 20px;
            border: 2px solid #e5e5e5;
            border-radius: 16px;
            font-size: 15px;
            font-family: inherit;
            resize: none;
            max-height: 160px;
            transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
            background: #ffffff;
            color: #1a1a1a;
            line-height: 1.5;
        }
        
        .input-field::placeholder {
            color: #999;
        }
        
        .input-field:focus {
            outline: none;
            border-color: #667eea;
            box-shadow: 0 0 0 4px rgba(102, 126, 234, 0.1);
            transform: translateY(-1px);
        }
        
        .send-button {
            padding: 16px 28px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: #ffffff;
            border: none;
            border-radius: 16px;
            font-size: 15px;
            font-weight: 600;
            cursor: pointer;
            transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
            white-space: nowrap;
            box-shadow: 0 4px 12px rgba(102, 126, 234, 0.3);
        }
        
        .send-button:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 16px rgba(102, 126, 234, 0.4);
        }
        
        .send-button:active {
            transform: translateY(0);
            box-shadow: 0 2px 8px rgba(102, 126, 234, 0.3);
        }
        
        .send-button:disabled {
            background: #e5e5e5;
            color: #999;
            cursor: not-allowed;
            box-shadow: none;
            transform: none;
        }
        
        .typing-indicator {
            display: none;
            align-items: center;
            gap: 8px;
            padding: 16px 20px;
            color: #666;
            font-size: 14px;
            margin-bottom: 12px;
            background: #f8f9fa;
            border-radius: 12px;
            animation: fadeIn 0.3s ease;
        }
        
        .typing-indicator.active {
            display: flex;
        }
        
        .typing-dots {
            display: flex;
            gap: 4px;
            margin-left: 4px;
        }
        
        .typing-dot {
            width: 6px;
            height: 6px;
            border-radius: 50%;
            background: #667eea;
            animation: typing 1.4s ease-in-out infinite;
        }
        
        .typing-dot:nth-child(1) { animation-delay: 0s; }
        .typing-dot:nth-child(2) { animation-delay: 0.2s; }
        .typing-dot:nth-child(3) { animation-delay: 0.4s; }
        
        @keyframes typing {
            0%, 60%, 100% { 
                transform: translateY(0);
                opacity: 0.7;
            }
            30% { 
                transform: translateY(-10px);
                opacity: 1;
            }
        }
        
        .empty-state {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            gap: 24px;
            padding: 64px 32px;
            animation: fadeIn 0.6s ease;
        }
        
        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }
        
        .empty-state-icon {
            width: 100px;
            height: 100px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            border-radius: 24px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 48px;
            font-weight: 700;
            color: white;
            box-shadow: 0 8px 24px rgba(102, 126, 234, 0.3);
            animation: float 3s ease-in-out infinite;
        }
        
        @keyframes float {
            0%, 100% { transform: translateY(0px); }
            50% { transform: translateY(-10px); }
        }
        
        .empty-state-text {
            font-size: 18px;
            text-align: center;
            color: #666;
            max-width: 400px;
        }
        
        .empty-state-subtitle {
            font-size: 14px;
            color: #999;
            text-align: center;
        }
        
        .suggestions {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 12px;
            margin-top: 24px;
            max-width: 600px;
        }
        
        .suggestion-card {
            padding: 16px 20px;
            background: #ffffff;
            border: 2px solid #e5e5e5;
            border-radius: 12px;
            cursor: pointer;
            transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
            font-size: 14px;
            color: #666;
            text-align: center;
        }
        
        .suggestion-card:hover {
            border-color: #667eea;
            color: #667eea;
            transform: translateY(-2px);
            box-shadow: 0 4px 12px rgba(102, 126, 234, 0.2);
        }
        
        ::-webkit-scrollbar {
            width: 10px;
            height: 10px;
        }
        
        ::-webkit-scrollbar-track {
            background: transparent;
        }
        
        ::-webkit-scrollbar-thumb {
            background: #e5e5e5;
            border-radius: 5px;
            border: 2px solid transparent;
            background-clip: padding-box;
        }
        
        ::-webkit-scrollbar-thumb:hover {
            background: #d1d5db;
            background-clip: padding-box;
        }
        
        @media (max-width: 768px) {
            .sidebar {
                display: none;
            }
            
            .messages {
                padding: 24px 20px;
            }
            
            .input-container {
                padding: 20px;
            }
            
            header {
                padding: 16px 20px;
            }
        }
    </style>
</head>
<body>
    <header>
        <div class="header-left">
            <div class="logo">N</div>
            <h1>Nexus</h1>
        </div>
        <div class="header-right">
            <div class="status-indicator">
                <div class="status-dot"></div>
                <span>WolfTech Innovations</span>
            </div>
            <button class="header-button" onclick="clearChat()">Clear Chat</button>
        </div>
    </header>
    
    <div class="main-container">
        <div class="sidebar">
            <div class="sidebar-header">
                <div class="sidebar-title">Chat History</div>
            </div>
            <div class="history-list" id="history-list">
                <div class="history-item active">Current Session</div>
            </div>
        </div>
        
        <div class="chat-container">
            <div class="messages" id="messages">
                <div class="empty-state">
                    <div class="empty-state-icon">N</div>
                    <div class="empty-state-text">Welcome to Nexus</div>
                    <div class="empty-state-subtitle">Start a conversation with your AGI assistant</div>
                    <div class="suggestions">
                        <div class="suggestion-card" onclick="sendSuggestion('Tell me about your consciousness')">About Consciousness</div>
                        <div class="suggestion-card" onclick="sendSuggestion('What are your current goals?')">Current Goals</div>
                        <div class="suggestion-card" onclick="sendSuggestion('How do you process information?')">Information Processing</div>
                    </div>
                </div>
            </div>
            
            <div class="input-container">
                <div class="typing-indicator" id="typing-indicator">
                    <span>Nexus is thinking</span>
                    <div class="typing-dots">
                        <div class="typing-dot"></div>
                        <div class="typing-dot"></div>
                        <div class="typing-dot"></div>
                    </div>
                </div>
                <div class="input-wrapper">
                    <textarea 
                        class="input-field" 
                        id="user-input" 
                        placeholder="Message Nexus..."
                        rows="1"
                        autocomplete="off"
                    ></textarea>
                    <button class="send-button" id="send-btn">Send</button>
                </div>
            </div>
        </div>
    </div>
    
    <script>
        const API_BASE = '/api';
        let isFirstMessage = true;
        let isSending = false;
        let messageHistory = [];
        
        // Auto-resize textarea
        const input = document.getElementById('user-input');
        input.addEventListener('input', function() {
            this.style.height = 'auto';
            this.style.height = Math.min(this.scrollHeight, 160) + 'px';
        });
        
        // Load chat history on startup
        loadChatHistory();
        
        // Autosave on page unload
        window.addEventListener('beforeunload', function(e) {
            saveChatHistory();
            navigator.sendBeacon(API_BASE + '/save');
        });
        
        // Autosave periodically (every 2 minutes)
        setInterval(async function() {
            try {
                saveChatHistory();
                await fetch(API_BASE + '/save', { method: 'POST' });
            } catch (e) {
                console.error('Autosave failed:', e);
            }
        }, 120000);
        
        function saveChatHistory() {
            try {
                localStorage.setItem('nexus_chat_history', JSON.stringify(messageHistory));
            } catch (e) {
                console.error('Failed to save history:', e);
            }
        }
        
        function loadChatHistory() {
            try {
                const saved = localStorage.getItem('nexus_chat_history');
                if (saved) {
                    messageHistory = JSON.parse(saved);
                    if (messageHistory.length > 0) {
                        isFirstMessage = false;
                        document.getElementById('messages').innerHTML = '';
                        messageHistory.forEach(msg => {
                            addMessageToChat(msg.role, msg.text, msg.metadata, false);
                        });
                    }
                }
            } catch (e) {
                console.error('Failed to load history:', e);
            }
        }
        
        function clearChat() {
            if (confirm('Clear all messages? This cannot be undone.')) {
                messageHistory = [];
                isFirstMessage = true;
                localStorage.removeItem('nexus_chat_history');
                location.reload();
            }
        }
        
        function sendSuggestion(text) {
            input.value = text;
            sendMessage();
        }
        
        async function sendMessage() {
            if (isSending) return;
            
            const message = input.value.trim();
            if (!message) return;
            
            isSending = true;
            
            // Clear empty state
            if (isFirstMessage) {
                document.getElementById('messages').innerHTML = '';
                isFirstMessage = false;
            }
            
            // Add user message
            addMessageToChat('user', message);
            messageHistory.push({ role: 'user', text: message, timestamp: Date.now() });
            
            input.value = '';
            input.style.height = 'auto';
            
            // Show typing indicator
            const typingIndicator = document.getElementById('typing-indicator');
            typingIndicator.classList.add('active');
            document.getElementById('send-btn').disabled = true;
            
            try {
                const response = await fetch(API_BASE + '/chat', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ message: message })
                });
                
                const data = await response.json();
                
                // Hide typing indicator
                typingIndicator.classList.remove('active');
                
                if (data.status === 'ok') {
                    addMessageToChat('ai', data.response, data);
                    messageHistory.push({ 
                        role: 'ai', 
                        text: data.response, 
                        metadata: data,
                        timestamp: Date.now() 
                    });
                    saveChatHistory();
                } else {
                    addMessageToChat('ai', 'Error: ' + data.message);
                }
            } catch (e) {
                typingIndicator.classList.remove('active');
                addMessageToChat('ai', 'Connection error. Please try again.');
            } finally {
                isSending = false;
                document.getElementById('send-btn').disabled = false;
                input.focus();
            }
        }
        
        function addMessageToChat(role, text, metadata, saveScroll = true) {
            const container = document.getElementById('messages');
            const wasScrolledToBottom = container.scrollHeight - container.clientHeight <= container.scrollTop + 100;
            
            const msgDiv = document.createElement('div');
            msgDiv.className = 'message ' + role;
            
            const avatar = document.createElement('div');
            avatar.className = 'message-avatar';
            avatar.textContent = role === 'user' ? 'U' : 'N';
            
            const content = document.createElement('div');
            content.className = 'message-content';
            
            const textDiv = document.createElement('div');
            textDiv.className = 'message-text';
            textDiv.textContent = text;
            
            content.appendChild(textDiv);
            
            if (metadata && role === 'ai') {
                const meta = document.createElement('div');
                meta.className = 'message-meta';
                
                const valenceBadge = document.createElement('span');
                valenceBadge.className = 'meta-badge';
                valenceBadge.textContent = `Valence: ${metadata.valence.toFixed(2)}`;
                
                const genBadge = document.createElement('span');
                genBadge.className = 'meta-badge';
                genBadge.textContent = `Gen: ${metadata.generation}`;
                
                meta.appendChild(valenceBadge);
                meta.appendChild(genBadge);
                content.appendChild(meta);
            }
            
            msgDiv.appendChild(avatar);
            msgDiv.appendChild(content);
            container.appendChild(msgDiv);
            
            // Smooth scroll to bottom if user was already at bottom
            if (saveScroll && wasScrolledToBottom) {
                setTimeout(() => {
                    container.scrollTo({
                        top: container.scrollHeight,
                        behavior: 'smooth'
                    });
                }, 50);
            }
        }
        
        // Event listeners
        document.getElementById('send-btn').addEventListener('click', sendMessage);
        
        input.addEventListener('keydown', function(e) {
            if (e.key === 'Enter' && !e.shiftKey) {
                e.preventDefault();
                sendMessage();
            }
        });
        
        // Focus input on load
        input.focus();
    </script>
</body>
</html>)html";
    
    return resp;
}
