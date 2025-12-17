# Build and Development Instructions for NexusAGI

## Quick Build

### For Linux:
```bash
make linux
```

### For Windows:
```bash
make windows
```

### Both platforms:
```bash
make both
```

### Complete setup with UI:
```bash
make complete-setup
make both
```

## Run the System

### Linux:
```bash
./output/Nexus
```

### Windows:
```bash
./output/Nexus.exe
```

## Verify Web UI

After starting the system, open: **http://localhost:8080**

## Project Structure

- `src/main.cpp` - Main AGI loop with integrated web server
- `src/web_server.h/.cpp` - HTTP server
- `src/agi_api.h/.cpp` - REST API endpoints
- `src/enhanced_reasoning.h/.cpp` - Concept graph reasoning
- `src/memory_system.h/.cpp` - Episodic and semantic memory
- `src/consciousness_coherence.h/.cpp` - Consciousness calculations
- `src/goal_planning.h/.cpp` - Goal formulation and planning
- `makefile` - Build system with all source files

## New Files Added

All new functionality is in the `src/` directory:
- Web server and API: `web_server.*`, `agi_api.*`
- Reasoning: `enhanced_reasoning.*`
- Memory: `memory_system.*`
- Consciousness: `consciousness_coherence.*`
- Goal planning: `goal_planning.*`

## Compilation Notes

- All new modules are C++ compatible
- Web server uses socket APIs (cross-platform)
- No external dependencies required beyond what's already in the project
- All files follow existing code conventions
- Includes are properly managed to avoid circular dependencies

## Testing

After build, the system will:
1. Start the ncurses terminal interface (or terminal UI)
2. Initialize and start web server on port 8080
3. Print "WebServer started on http://localhost:8080"
4. Accept connections on both terminal and web

Navigate to http://localhost:8080 in any modern browser to access the modern UI.

## Key Endpoints

- `http://localhost:8080/` - Web UI (HTML)
- `http://localhost:8080/api/chat` - Chat endpoint (POST)
- `http://localhost:8080/api/status` - System status
- `http://localhost:8080/api/consciousness` - Consciousness metrics
- `http://localhost:8080/api/thoughts` - Internal thoughts
- `http://localhost:8080/api/memory` - Memory status
- `http://localhost:8080/api/goals` - Active goals
- `http://localhost:8080/api/valence` - Valence history

## Development Workflow

1. **Make changes to source**
2. **Run make** to rebuild
3. **Test via terminal** for console output
4. **Test via web UI** for modern interface
