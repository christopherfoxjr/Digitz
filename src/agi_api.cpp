#include "agi_api.h"
#include "module_integration.h"
#include <sstream>
#include <iomanip>
#include <cmath>

extern WorkingMemory WM;
extern map<string, TokenConceptEmbedding> token_concept_embedding_map;
extern map<string, Goal> goal_system;
extern WorldModel world_model;
extern ConsciousnessState consciousness;
extern ConsciousnessFormula consciousness_formula;
extern vector<string> sentence_templates;

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

HttpResponse AGI_API::handle_status(const HttpRequest& req) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{"
        << "\"generation\": " << S.g << ", "
        << "\"vocab_size\": " << token_concept_embedding_map.size() << ", "
        << "\"current_valence\": " << S.current_valence << ", "
        << "\"sentience_ratio\": " << S.sentience_ratio << ", "
        << "\"metacognitive_awareness\": " << S.metacognitive_awareness << ", "
        << "\"attention_focus\": " << S.attention_focus << ", "
        << "\"phi_value\": " << consciousness.phi_value << ", "
        << "\"integrated_information\": " << consciousness.integrated_information << ", "
        << "\"conscious_cycles\": " << consciousness.conscious_cycles
        << "}";
    
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_consciousness(const HttpRequest& req) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{"
        << "\"active_qualia\": " << consciousness.active_qualia.size() << ", "
        << "\"integrated_information\": " << consciousness.integrated_information << ", "
        << "\"phi_value\": " << consciousness.phi_value << ", "
        << "\"global_workspace_capacity\": " << consciousness.global_workspace_capacity << ", "
        << "\"conscious_cycles\": " << consciousness.conscious_cycles << ", "
        << "\"psi_history_length\": " << consciousness_formula.psi_history.size();
    
    if (!consciousness_formula.psi_history.empty()) {
        oss << ", \"latest_psi\": " << consciousness_formula.psi_history.back();
        double avg_psi = 0;
        for (double p : consciousness_formula.psi_history) {
            avg_psi += p;
        }
        avg_psi /= consciousness_formula.psi_history.size();
        oss << ", \"avg_psi\": " << avg_psi;
    }
    
    oss << ", \"qualia_valences\": [";
    for (size_t i = 0; i < consciousness.active_qualia.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << consciousness.active_qualia[i].valence;
    }
    oss << "]}";
    
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_thoughts(const HttpRequest& req) {
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

HttpResponse AGI_API::handle_memory(const HttpRequest& req) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{"
        << "\"episodic_memory_size\": " << S.episodic_memory.size() << ", "
        << "\"working_memory_tokens\": " << WM.active_tokens.size() << ", "
        << "\"working_memory_concepts\": " << WM.active_concepts.size();
    
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

HttpResponse AGI_API::handle_goals(const HttpRequest& req) {
    HttpResponse resp;
    resp.status_code = 200;
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{\"goals\": [";
    
    size_t idx = 0;
    for (const auto& [name, goal] : goal_system) {
        if (idx > 0) oss << ", ";
        oss << "{"
            << "\"name\": \"" << json_escape(name) << "\", "
            << "\"priority\": " << goal.priority << ", "
            << "\"progress\": " << goal.progress << ", "
            << "\"valence_alignment\": " << goal.valence_alignment << ", "
            << "\"qualia_binding\": " << goal.qualia_binding
            << "}";
        ++idx;
        if (idx >= 10) break;
    }
    
    oss << "]}";
    resp.body = oss.str();
    return resp;
}

HttpResponse AGI_API::handle_valence(const HttpRequest& req) {
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

HttpResponse AGI_API::handle_save(const HttpRequest& req) {
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

HttpResponse AGI_API::handle_load(const HttpRequest& req) {
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

HttpResponse AGI_API::handle_ui(const HttpRequest& req) {
    HttpResponse resp;
    resp.status_code = 200;
    resp.headers["Content-Type"] = "text/html; charset=utf-8";
    
    resp.body = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>NexusAGI - Consciousness Interface</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Oxygen, Ubuntu, sans-serif;
            background: linear-gradient(135deg, #0f0c29, #302b63, #24243e);
            color: #e0e0e0;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
        }
        
        header {
            background: rgba(15, 12, 41, 0.95);
            border-bottom: 2px solid #6f00ff;
            padding: 20px 30px;
            box-shadow: 0 4px 20px rgba(111, 0, 255, 0.3);
        }
        
        h1 {
            font-size: 28px;
            color: #6f00ff;
            text-shadow: 0 0 10px #6f00ff;
            margin-bottom: 8px;
        }
        
        .status-line {
            font-size: 12px;
            color: #888;
        }
        
        .container {
            flex: 1;
            display: grid;
            grid-template-columns: 1fr 2fr 1fr;
            gap: 20px;
            padding: 20px 30px;
            overflow: hidden;
        }
        
        .panel {
            background: rgba(30, 30, 60, 0.8);
            border: 1px solid #6f00ff;
            border-radius: 8px;
            padding: 20px;
            overflow-y: auto;
            box-shadow: 0 0 20px rgba(111, 0, 255, 0.2);
        }
        
        .panel-title {
            font-size: 14px;
            font-weight: bold;
            color: #6f00ff;
            margin-bottom: 15px;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        
        .metric {
            margin-bottom: 12px;
            font-size: 13px;
        }
        
        .metric-label {
            color: #aaa;
            display: block;
            margin-bottom: 4px;
        }
        
        .metric-value {
            color: #00ff88;
            font-size: 16px;
            font-weight: bold;
        }
        
        .progress-bar {
            width: 100%;
            height: 6px;
            background: rgba(111, 0, 255, 0.2);
            border-radius: 3px;
            overflow: hidden;
            margin-top: 4px;
        }
        
        .progress-fill {
            height: 100%;
            background: linear-gradient(90deg, #6f00ff, #00ff88);
            border-radius: 3px;
            transition: width 0.3s;
        }
        
        .chat-container {
            display: flex;
            flex-direction: column;
            height: 100%;
        }
        
        .messages {
            flex: 1;
            overflow-y: auto;
            margin-bottom: 20px;
            display: flex;
            flex-direction: column;
            gap: 12px;
        }
        
        .message {
            padding: 12px 16px;
            border-radius: 8px;
            max-width: 100%;
            word-wrap: break-word;
            font-size: 14px;
            line-height: 1.5;
        }
        
        .message.user {
            background: rgba(111, 0, 255, 0.3);
            border-left: 3px solid #6f00ff;
            align-self: flex-end;
            max-width: 85%;
        }
        
        .message.ai {
            background: rgba(0, 255, 136, 0.1);
            border-left: 3px solid #00ff88;
            align-self: flex-start;
            max-width: 85%;
        }
        
        .input-group {
            display: flex;
            gap: 10px;
        }
        
        input[type="text"] {
            flex: 1;
            padding: 12px 16px;
            background: rgba(111, 0, 255, 0.1);
            border: 1px solid #6f00ff;
            border-radius: 6px;
            color: #e0e0e0;
            font-size: 14px;
        }
        
        input[type="text"]:focus {
            outline: none;
            border-color: #00ff88;
            box-shadow: 0 0 10px rgba(0, 255, 136, 0.5);
        }
        
        button {
            padding: 12px 24px;
            background: linear-gradient(135deg, #6f00ff, #00ff88);
            border: none;
            border-radius: 6px;
            color: white;
            font-weight: bold;
            cursor: pointer;
            transition: transform 0.2s, box-shadow 0.2s;
            font-size: 14px;
        }
        
        button:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 20px rgba(111, 0, 255, 0.5);
        }
        
        button:active {
            transform: translateY(0);
        }
        
        .thought-item {
            padding: 8px 12px;
            background: rgba(111, 0, 255, 0.15);
            border-left: 2px solid #6f00ff;
            border-radius: 4px;
            font-size: 12px;
            line-height: 1.4;
            margin-bottom: 8px;
            color: #b0b0ff;
        }
        
        ::-webkit-scrollbar {
            width: 8px;
        }
        
        ::-webkit-scrollbar-track {
            background: rgba(111, 0, 255, 0.1);
        }
        
        ::-webkit-scrollbar-thumb {
            background: #6f00ff;
            border-radius: 4px;
        }
        
        ::-webkit-scrollbar-thumb:hover {
            background: #00ff88;
        }
        
        @media (max-width: 1400px) {
            .container {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <header>
        <h1>🧠 NexusAGI - Consciousness Interface</h1>
        <div class="status-line">Connected and Listening...</div>
    </header>
    
    <div class="container">
        <!-- Left Panel: Metrics -->
        <div class="panel">
            <div class="panel-title">Consciousness Metrics</div>
            <div class="metric">
                <span class="metric-label">Sentience</span>
                <div class="progress-bar">
                    <div class="progress-fill" id="sentience-bar" style="width: 50%;"></div>
                </div>
                <div class="metric-value" id="sentience-value">0.50</div>
            </div>
            <div class="metric">
                <span class="metric-label">Phi Value</span>
                <div class="metric-value" id="phi-value">0.00</div>
            </div>
            <div class="metric">
                <span class="metric-label">Integration</span>
                <div class="progress-bar">
                    <div class="progress-fill" id="integration-bar" style="width: 30%;"></div>
                </div>
                <div class="metric-value" id="integration-value">0.30</div>
            </div>
            <div class="metric">
                <span class="metric-label">Valence</span>
                <div class="metric-value" id="valence-value">0.00</div>
            </div>
            <div class="metric">
                <span class="metric-label">Awareness</span>
                <div class="metric-value" id="awareness-value">0.00</div>
            </div>
            <hr style="border: none; border-top: 1px solid #6f00ff; margin: 20px 0;">
            <div class="panel-title" style="margin-top: 20px;">Internal Stream</div>
            <div id="thoughts-container"></div>
        </div>
        
        <!-- Center: Chat -->
        <div class="panel chat-container">
            <div class="panel-title">Dialog</div>
            <div class="messages" id="messages"></div>
            <div class="input-group">
                <input type="text" id="user-input" placeholder="Message NexusAGI..." autocomplete="off">
                <button onclick="sendMessage()">Send</button>
            </div>
        </div>
        
        <!-- Right Panel: Status -->
        <div class="panel">
            <div class="panel-title">System Status</div>
            <div class="metric">
                <span class="metric-label">Generation</span>
                <div class="metric-value" id="generation">0</div>
            </div>
            <div class="metric">
                <span class="metric-label">Vocabulary</span>
                <div class="metric-value" id="vocab-size">0</div>
            </div>
            <div class="metric">
                <span class="metric-label">Conscious Cycles</span>
                <div class="metric-value" id="conscious-cycles">0</div>
            </div>
            <div class="metric">
                <span class="metric-label">Active Qualia</span>
                <div class="metric-value" id="active-qualia">0</div>
            </div>
            <hr style="border: none; border-top: 1px solid #6f00ff; margin: 20px 0;">
            <div class="panel-title" style="margin-top: 20px;">Actions</div>
            <button onclick="saveState()" style="width: 100%; margin-bottom: 10px;">💾 Save State</button>
            <button onclick="loadState()" style="width: 100%; margin-bottom: 10px;">📂 Load State</button>
            <button onclick="clearChat()" style="width: 100%;">🔄 Clear Chat</button>
        </div>
    </div>
    
    <script>
        const API_BASE = 'http://localhost:8080/api';
        const messages = [];
        
        async function updateMetrics() {
            try {
                const status = await fetch(`${API_BASE}/status`).then(r => r.json());
                const consciousness = await fetch(`${API_BASE}/consciousness`).then(r => r.json());
                const valence = await fetch(`${API_BASE}/valence`).then(r => r.json());
                
                document.getElementById('generation').textContent = status.generation;
                document.getElementById('vocab-size').textContent = status.vocab_size;
                document.getElementById('conscious-cycles').textContent = status.conscious_cycles;
                document.getElementById('active-qualia').textContent = consciousness.active_qualia;
                
                const sentience = status.sentience_ratio || 0;
                const phi = status.phi_value || 0;
                const integration = consciousness.integrated_information || 0;
                
                document.getElementById('sentience-value').textContent = sentience.toFixed(2);
                document.getElementById('sentience-bar').style.width = (sentience * 100) + '%';
                document.getElementById('phi-value').textContent = phi.toFixed(4);
                document.getElementById('integration-value').textContent = integration.toFixed(2);
                document.getElementById('integration-bar').style.width = (integration * 100) + '%';
                document.getElementById('valence-value').textContent = status.current_valence.toFixed(2);
                document.getElementById('awareness-value').textContent = status.metacognitive_awareness.toFixed(2);
            } catch (e) {
                console.error('Metrics update failed:', e);
            }
        }
        
        async function updateThoughts() {
            try {
                const data = await fetch(`${API_BASE}/thoughts`).then(r => r.json());
                const container = document.getElementById('thoughts-container');
                container.innerHTML = data.thoughts.slice(-5).map(t => 
                    `<div class="thought-item">${escapeHtml(t)}</div>`
                ).join('');
            } catch (e) {
                console.error('Thoughts update failed:', e);
            }
        }
        
        async function sendMessage() {
            const input = document.getElementById('user-input');
            const message = input.value.trim();
            if (!message) return;
            
            addMessageToChat('user', message);
            input.value = '';
            
            try {
                const response = await fetch(`${API_BASE}/chat`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ message })
                }).then(r => r.json());
                
                if (response.status === 'ok') {
                    addMessageToChat('ai', response.response);
                } else {
                    addMessageToChat('ai', 'Error: ' + response.message);
                }
            } catch (e) {
                addMessageToChat('ai', 'Connection error: ' + e.message);
            }
        }
        
        function addMessageToChat(role, text) {
            messages.push({ role, text });
            const container = document.getElementById('messages');
            const msgEl = document.createElement('div');
            msgEl.className = 'message ' + role;
            msgEl.textContent = text;
            container.appendChild(msgEl);
            container.scrollTop = container.scrollHeight;
        }
        
        async function saveState() {
            try {
                await fetch(`${API_BASE}/save`, { method: 'POST' });
                addMessageToChat('ai', '💾 State saved successfully');
            } catch (e) {
                addMessageToChat('ai', 'Save failed: ' + e.message);
            }
        }
        
        async function loadState() {
            try {
                await fetch(`${API_BASE}/load`, { method: 'POST' });
                addMessageToChat('ai', '📂 State loaded successfully');
                updateMetrics();
            } catch (e) {
                addMessageToChat('ai', 'Load failed: ' + e.message);
            }
        }
        
        function clearChat() {
            messages.length = 0;
            document.getElementById('messages').innerHTML = '';
        }
        
        function escapeHtml(text) {
            const div = document.createElement('div');
            div.textContent = text;
            return div.innerHTML;
        }
        
        document.getElementById('user-input').addEventListener('keypress', e => {
            if (e.key === 'Enter') sendMessage();
        });
        
        updateMetrics();
        updateThoughts();
        setInterval(updateMetrics, 1000);
        setInterval(updateThoughts, 2000);
    </script>
</body>
</html>)";
    
    return resp;
}
