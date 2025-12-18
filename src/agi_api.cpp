#include "agi_api.h"
#include "module_integration.h"
#include <sstream>
#include <iomanip>
#include <cmath>

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
    server_->register_route("POST", "/api/save", [this](const HttpRequest& req) { return handle_save(req); });
    server_->register_route("POST", "/api/load", [this](const HttpRequest& req) { return handle_load(req); });
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

std::string AGI_API::filter_markers(const std::string& text) {
    std::string result = text;
    
    // Filter out [positive] markers
    size_t pos = 0;
    while ((pos = result.find("[positive]", pos)) != std::string::npos) {
        result.erase(pos, 10);
    }
    
    // Filter out [negative] markers
    pos = 0;
    while ((pos = result.find("[negative]", pos)) != std::string::npos) {
        result.erase(pos, 10);
    }
    
    return result;
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
        
        // Filter out [positive] and [negative] markers
        response = filter_markers(response);
        
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
            background: #ffffff;
            color: #1a1a1a;
            height: 100vh;
            display: flex;
            flex-direction: column;
        }
        
        header {
            background: #ffffff;
            border-bottom: 1px solid #e5e5e5;
            padding: 16px 24px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        h1 {
            font-size: 20px;
            font-weight: 600;
            color: #1a1a1a;
            letter-spacing: -0.3px;
        }
        
        .header-right {
            display: flex;
            align-items: center;
            gap: 16px;
        }
        
        .history-btn {
            padding: 8px 16px;
            background: #f3f4f6;
            border: 1px solid #e5e5e5;
            border-radius: 8px;
            font-size: 14px;
            cursor: pointer;
            transition: all 0.2s;
            color: #1a1a1a;
        }
        
        .history-btn:hover {
            background: #e5e7eb;
        }
        
        .status-indicator {
            display: flex;
            align-items: center;
            gap: 8px;
            font-size: 13px;
            color: #1a1a1a;
        }
        
        .status-dot {
            width: 8px;
            height: 8px;
            border-radius: 50%;
            background: #10b981;
            animation: pulse 2s ease-in-out infinite;
        }
        
        @keyframes pulse {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.5; }
        }
        
        .main-container {
            flex: 1;
            display: flex;
            overflow: hidden;
        }
        
        .sidebar {
            width: 280px;
            background: #f9fafb;
            border-right: 1px solid #e5e5e5;
            display: none;
            flex-direction: column;
        }
        
        .sidebar.active {
            display: flex;
        }
        
        .sidebar-header {
            padding: 16px;
            border-bottom: 1px solid #e5e5e5;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .sidebar-title {
            font-size: 16px;
            font-weight: 600;
        }
        
        .close-sidebar {
            padding: 4px 8px;
            background: transparent;
            border: none;
            cursor: pointer;
            font-size: 18px;
            color: #666;
        }
        
        .close-sidebar:hover {
            color: #1a1a1a;
        }
        
        .sidebar-content {
            flex: 1;
            overflow-y: auto;
            padding: 8px;
        }
        
        .new-chat-btn {
            width: 100%;
            padding: 12px;
            background: #1a1a1a;
            color: #ffffff;
            border: none;
            border-radius: 8px;
            font-size: 14px;
            font-weight: 500;
            cursor: pointer;
            margin-bottom: 8px;
        }
        
        .new-chat-btn:hover {
            background: #333;
        }
        
        .session-item {
            padding: 12px;
            background: #ffffff;
            border: 1px solid #e5e5e5;
            border-radius: 8px;
            margin-bottom: 8px;
            cursor: pointer;
            transition: all 0.2s;
            position: relative;
        }
        
        .session-item:hover {
            background: #f3f4f6;
        }
        
        .session-item.active {
            background: #e5e7eb;
            border-color: #1a1a1a;
        }
        
        .session-title {
            font-size: 14px;
            font-weight: 500;
            margin-bottom: 4px;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }
        
        .session-date {
            font-size: 12px;
            color: #666;
        }
        
        .delete-session {
            position: absolute;
            top: 8px;
            right: 8px;
            padding: 4px 8px;
            background: #ef4444;
            color: #ffffff;
            border: none;
            border-radius: 4px;
            font-size: 11px;
            cursor: pointer;
            opacity: 0;
            transition: opacity 0.2s;
        }
        
        .session-item:hover .delete-session {
            opacity: 1;
        }
        
        .delete-session:hover {
            background: #dc2626;
        }
        
        .chat-container {
            flex: 1;
            display: flex;
            flex-direction: column;
            max-width: 800px;
            width: 100%;
            margin: 0 auto;
            padding: 0 24px;
        }
        
        .messages {
            flex: 1;
            overflow-y: auto;
            padding: 24px 0;
            display: flex;
            flex-direction: column;
            gap: 24px;
        }
        
        .message {
            display: flex;
            gap: 12px;
            animation: fadeIn 0.3s ease-out;
        }
        
        @keyframes fadeIn {
            from {
                opacity: 0;
                transform: translateY(10px);
            }
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }
        
        .message-avatar {
            width: 32px;
            height: 32px;
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 16px;
            flex-shrink: 0;
        }
        
        .message.user .message-avatar {
            background: #f3f4f6;
        }
        
        .message.ai .message-avatar {
            background: #1a1a1a;
            color: #ffffff;
        }
        
        .message-content {
            flex: 1;
            padding-top: 4px;
        }
        
        .message-text {
            font-size: 15px;
            line-height: 1.6;
            color: #1a1a1a;
            word-wrap: break-word;
        }
        
        .message-meta {
            font-size: 12px;
            color: #666;
            margin-top: 6px;
        }
        
        .input-container {
            padding: 24px 0;
            border-top: 1px solid #e5e5e5;
        }
        
        .input-wrapper {
            display: flex;
            gap: 12px;
            align-items: flex-end;
        }
        
        .input-field {
            flex: 1;
            padding: 12px 16px;
            border: 1px solid #e5e5e5;
            border-radius: 12px;
            font-size: 15px;
            font-family: inherit;
            resize: none;
            max-height: 120px;
            transition: border-color 0.2s;
        }
        
        .input-field:focus {
            outline: none;
            border-color: #1a1a1a;
        }
        
        .send-button {
            padding: 12px 24px;
            background: #1a1a1a;
            color: #ffffff;
            border: none;
            border-radius: 12px;
            font-size: 15px;
            font-weight: 500;
            cursor: pointer;
            transition: all 0.2s;
            white-space: nowrap;
        }
        
        .send-button:hover {
            background: #333;
        }
        
        .send-button:active {
            transform: scale(0.98);
        }
        
        .send-button:disabled {
            background: #e5e5e5;
            color: #666;
            cursor: not-allowed;
        }
        
        .typing-indicator {
            display: none;
            align-items: center;
            gap: 4px;
            padding: 12px 16px;
            color: #666;
            font-size: 14px;
        }
        
        .typing-indicator.active {
            display: flex;
        }
        
        .typing-dot {
            width: 6px;
            height: 6px;
            border-radius: 50%;
            background: #666;
            animation: typing 1.4s ease-in-out infinite;
        }
        
        .typing-dot:nth-child(2) { animation-delay: 0.2s; }
        .typing-dot:nth-child(3) { animation-delay: 0.4s; }
        
        @keyframes typing {
            0%, 60%, 100% { transform: translateY(0); }
            30% { transform: translateY(-8px); }
        }
        
        ::-webkit-scrollbar {
            width: 8px;
        }
        
        ::-webkit-scrollbar-track {
            background: transparent;
        }
        
        ::-webkit-scrollbar-thumb {
            background: #e5e5e5;
            border-radius: 4px;
        }
        
        ::-webkit-scrollbar-thumb:hover {
            background: #d4d4d4;
        }
        
        .empty-state {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            color: #666;
            gap: 16px;
            padding: 48px;
        }
        
        .empty-state-icon {
            font-size: 64px;
            font-weight: 700;
            color: #9ca3af;
        }
        
        .empty-state-text {
            font-size: 16px;
            font-weight: 600;
            color: #374151;
            text-align: center;
        }
    </style>
</head>
<body>
    <header>
        <h1>Nexus</h1>
        <div class="header-right">
            <button class="history-btn" id="history-btn">History</button>
            <div class="status-indicator">
                <div class="status-dot"></div>
                <span>WolfTech Innovations</span>
            </div>
        </div>
    </header>
    
    <div class="main-container">
        <div class="sidebar" id="sidebar">
            <div class="sidebar-header">
                <div class="sidebar-title">Chat History</div>
                <button class="close-sidebar" id="close-sidebar">×</button>
            </div>
            <div class="sidebar-content">
                <button class="new-chat-btn" id="new-chat-btn">New Chat</button>
                <div id="sessions-list"></div>
            </div>
        </div>
        
        <div class="chat-container">
            <div class="messages" id="messages">
                <div class="empty-state">
                    <div class="empty-state-icon">N</div>
                    <div class="empty-state-text">Start a conversation with Nexus</div>
                </div>
            </div>
            
            <div class="input-container">
                <div class="typing-indicator" id="typing-indicator">
                    <span>Nexus is thinking</span>
                    <div class="typing-dot"></div>
                    <div class="typing-dot"></div>
                    <div class="typing-dot"></div>
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
        let isSending = false;
        let currentSessionId = null;
        let sessions = {};
        
        // Load sessions from localStorage
        function loadSessions() {
            const stored = localStorage.getItem('nexus_sessions');
            if (stored) {
                sessions = JSON.parse(stored);
            }
        }
        
        // Save sessions to localStorage
        function saveSessions() {
            localStorage.setItem('nexus_sessions', JSON.stringify(sessions));
        }
        
        // Create a new session
        function createNewSession() {
            const sessionId = 'session_' + Date.now();
            sessions[sessionId] = {
                id: sessionId,
                title: 'New Chat',
                date: new Date().toISOString(),
                messages: []
            };
            currentSessionId = sessionId;
            saveSessions();
            clearChat();
            renderSessionsList();
            return sessionId;
        }
        
        // Load a session
        function loadSession(sessionId) {
            if (!sessions[sessionId]) return;
            
            currentSessionId = sessionId;
            const session = sessions[sessionId];
            
            clearChat();
            
            // Restore messages
            session.messages.forEach(msg => {
                addMessageToChat(msg.role, msg.text, msg.metadata, false);
            });
            
            renderSessionsList();
        }
        
        // Delete a session
        function deleteSession(sessionId, event) {
            event.stopPropagation();
            
            if (confirm('Delete this chat session?')) {
                delete sessions[sessionId];
                saveSessions();
                
                if (currentSessionId === sessionId) {
                    createNewSession();
                } else {
                    renderSessionsList();
                }
            }
        }
        
        // Render sessions list
        function renderSessionsList() {
            const container = document.getElementById('sessions-list');
            container.innerHTML = '';
            
            const sessionArray = Object.values(sessions).sort((a, b) => 
                new Date(b.date) - new Date(a.date)
            );
            
            sessionArray.forEach(session => {
                const div = document.createElement('div');
                div.className = 'session-item' + (session.id === currentSessionId ? ' active' : '');
                div.onclick = () => loadSession(session.id);
                
                const title = document.createElement('div');
                title.className = 'session-title';
                title.textContent = session.title;
                
                const date = document.createElement('div');
                date.className = 'session-date';
                date.textContent = new Date(session.date).toLocaleDateString();
                
                const deleteBtn = document.createElement('button');
                deleteBtn.className = 'delete-session';
                deleteBtn.textContent = 'Delete';
                deleteBtn.onclick = (e) => deleteSession(session.id, e);
                
                div.appendChild(title);
                div.appendChild(date);
                div.appendChild(deleteBtn);
                container.appendChild(div);
            });
        }
        
        // Clear chat display
        function clearChat() {
            document.getElementById('messages').innerHTML = `
                <div class="empty-state">
                    <div class="empty-state-icon">N</div>
                    <div class="empty-state-text">Start a conversation with Nexus</div>
                </div>
            `;
        }
        
        // Save current message to session
        function saveMessageToSession(role, text, metadata) {
            if (!currentSessionId || !sessions[currentSessionId]) return;
            
            const session = sessions[currentSessionId];
            session.messages.push({ role, text, metadata });
            
            // Update title with first user message
            if (role === 'user' && session.messages.length === 1) {
                session.title = text.substring(0, 50) + (text.length > 50 ? '...' : '');
            }
            
            saveSessions();
            renderSessionsList();
        }
        
        // Auto-resize textarea
        const input = document.getElementById('user-input');
        input.addEventListener('input', function() {
            this.style.height = 'auto';
            this.style.height = Math.min(this.scrollHeight, 120) + 'px';
        });
        
        // Toggle sidebar
        document.getElementById('history-btn').addEventListener('click', () => {
            document.getElementById('sidebar').classList.toggle('active');
        });
        
        document.getElementById('close-sidebar').addEventListener('click', () => {
            document.getElementById('sidebar').classList.remove('active');
        });
        
        // New chat button
        document.getElementById('new-chat-btn').addEventListener('click', () => {
            createNewSession();
            document.getElementById('sidebar').classList.remove('active');
        });
        
        // Autosave on page unload
        window.addEventListener('beforeunload', function(e) {
            saveSessions();
            navigator.sendBeacon(API_BASE + '/save');
        });
        
        // Autosave periodically (every 2 minutes)
        setInterval(async function() {
            try {
                await fetch(API_BASE + '/save', { method: 'POST' });
            } catch (e) {
                console.error('Autosave failed:', e);
            }
        }, 120000);
        
        async function sendMessage() {
            if (isSending) return;
            
            const message = input.value.trim();
            if (!message) return;
            
            // Create session if none exists
            if (!currentSessionId) {
                createNewSession();
            }
            
            isSending = true;
            
            // Clear empty state if first message
            const messagesContainer = document.getElementById('messages');
            if (messagesContainer.querySelector('.empty-state')) {
                messagesContainer.innerHTML = '';
            }
            
            // Add user message
            addMessageToChat('user', message);
            saveMessageToSession('user', message);
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
                    saveMessageToSession('ai', data.response, data);
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
        
        function addMessageToChat(role, text, metadata, scroll = true) {
            const container = document.getElementById('messages');
            
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
                meta.textContent = `Valence: ${metadata.valence.toFixed(2)} • Generation: ${metadata.generation}`;
                content.appendChild(meta);
            }
            
            msgDiv.appendChild(avatar);
            msgDiv.appendChild(content);
            container.appendChild(msgDiv);
            
            // Smooth scroll to bottom
            if (scroll) {
                container.scrollTo({
                    top: container.scrollHeight,
                    behavior: 'smooth'
                });
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
        
        // Initialize
        loadSessions();
        
        // Load last session or create new one
        const sessionArray = Object.values(sessions).sort((a, b) => 
            new Date(b.date) - new Date(a.date)
        );
        
        if (sessionArray.length > 0) {
            loadSession(sessionArray[0].id);
        } else {
            createNewSession();
        }
        
        renderSessionsList();
        
        // Focus input on load
        input.focus();
    </script>
</body>
</html>)html";
    
    return resp;
}
