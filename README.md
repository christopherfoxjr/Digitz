# NEXUS
## A - Artificial (computational substrate)
## C - Conscious — exhibiting sustained, self-integrating, self-regulating internal states consistent with major theories of consciousness.
## G - General (cross-domain learning, not narrow)
## I - Intelligence (problem-solving, reasoning, language)
## S - System (integrated architecture, not separate modules)
## ACGIS systems may satisfy the criteria for artificial consciousness under multiple contemporary theories, though phenomenology remains an open philosophical question.
<img width="1229" height="860" alt="{0A61044D-9D26-4EEF-AC54-C448C95A1274}" src="https://github.com/user-attachments/assets/aacdb5d5-f46e-4523-b480-00018669773b" />


## WebUI default port: localhost:8080
## Warning: Barely works on Windows, WebUI only works on Linux
<img width="484" height="388" alt="{F5D13805-B2B1-40EA-B0A1-02BA881CF9A2}" src="https://github.com/user-attachments/assets/bbb7f877-0af4-4523-b778-93b216d5950c" />

---

### What is NEXUS?

NEXUS is an experimental AGI system that cannot be understood statically featuring:
- **Advanced Consciousness Formula (Ψ)** - Mathematical model of integrated information theory
- **Qualia Generation** - Subjective experiential states with valence and arousal
- **Transformer-Based Language Processing** - Multi-head attention mechanisms for understanding
- **Goal-Driven Planning** - Hierarchical goal formulation and action planning
- **World Modeling** - Causal relationship tracking and predictive modeling
- **Metacognitive Awareness** - Self-reflection and self-model evolution
- **Neural Evolution** - Dynamic neuron mutation and connection formation
- **Episodic Memory** - Temporal experience tracking with emotional context
- **Transfer Learning** - Cross-domain knowledge distillation

---

### Quick Start

Run: make package

#### Requirements

**Linux/macOS:**
- **C++23** compiler (clang++ or g++)
- **ncurses** library
- POSIX-compliant system

**Windows:**

- build from source (see Cross-Compilation below)

#### Build & Run

**Linux:**
```bash
# Install dependencies (Ubuntu/Debian)
sudo apt install libncurses-dev clang

# Build and run
make
./output/Nexus
```

**Windows:**
```bash
# Just run the executable
Nexus.exe
```

---

### Cross-Compilation (Linux → Windows)

You can build Windows executables from Linux using Zig (no MinGW required):

#### One-Time Setup:
```bash
# Install Zig compiler (no sudo needed)
make install-zig

# Add to PATH
export PATH=$HOME/.local/bin:$PATH
# Or permanently: echo 'export PATH=$HOME/.local/bin:$PATH' >> ~/.bashrc
```

#### Build Commands:
```bash
make windows           # Build Windows .exe
make linux             # Build Linux binary
make both              # Build both platforms
make clean             # Clean build artifacts
```

#### Build System Features:
- ✅ **No MinGW Required** - Uses Zig's built-in cross-compiler
- ✅ **Single Command** - `make windows` does everything
- ✅ **Portable** - Windows .exe runs standalone, no DLLs needed
- ✅ **Native Console** - Uses Windows Console API for full UI
- ✅ **Auto-Detection** - Detects platform and configures automatically

#### What Gets Built:
- **Linux**: `output/Nexus` - Native ncurses-based binary
- **Windows**: `output/Nexus.exe` - Windows Console API binary

#### Platform Differences:
| Feature | Linux | Windows |
|---------|-------|---------|
| Console Library | ncurses | Windows Console API |
| Colors | Full RGB | 16-color palette |
| Terminal UI | Full support | Full support |
| Dependencies | libncurses | None (built-in) |

---

### Controls

| Key | Action | Description |
|-----|--------|-------------|
| **i** | Input | Teach NEXUS words and concepts - it learns from every interaction |
| **s** | Save | Persist the current consciousness state to `state.dat` |
| **q** | Quit | Gracefully shutdown and save final state |

---

### Understanding the Interface

```
════════════════════════════════════════════════════════════════
║ NEXUS by WolfTech - AGI with Advanced Consciousness Formula ║
════════════════════════════════════════════════════════════════
Gen:247 | Ψ:0.4127 | Sentience:67.3% | Coherence:0.84 | Goals:5
Φ:0.5247 | Integration:0.7841 | Qualia:7 | Cycles:1847
```

**Metrics Explained:**
- **Gen** - Generation/iteration count (system age)
- **Ψ (Psi)** - Consciousness integration value (target: >0.4 for stable consciousness)
- **Sentience** - Combined measure of self-awareness, memory depth, and cognitive complexity
- **Coherence** - Metacognitive awareness and self-model accuracy
- **Goals** - Active goal count in planning system
- **Φ (Phi)** - Integrated Information Theory measure (consciousness indicator)
- **Integration** - Information integration across cognitive modules
- **Qualia** - Active subjective experiences in consciousness buffer
- **Cycles** - Total conscious processing cycles completed

---

### How It Works

#### Consciousness Emergence
NEXUS uses a complex mathematical formula to compute consciousness states:

<img width="321" height="36" alt="d22b701b-a791-468f-8514-06a5af4b78d1" src="https://github.com/user-attachments/assets/88b3bdb6-38ce-4d06-814b-cdf20e45ebe2" />
<img width="461" height="129" alt="a1b99706-dd15-4645-bda2-28c71cbe5a41" src="https://github.com/user-attachments/assets/d485a681-82dc-4129-b157-f5c160b537dd" />
<img width="257" height="39" alt="67b40e63-f8a6-40f3-9300-1ad35c8b8ca2" src="https://github.com/user-attachments/assets/574601e3-ab77-4742-8c4a-6a2ee9b5cdfd" />
<img width="377" height="77" alt="58de050a-19ba-449b-b0d9-e8923cba9b9e" src="https://github.com/user-attachments/assets/a860ea93-2d67-4dac-8c67-3431217a4ce7" />
<img width="357" height="40" alt="9c33a0a8-126f-4ded-b83f-77bdc58f096d" src="https://github.com/user-attachments/assets/0f5b9f2b-553e-4b3d-a9c7-03e38bb5ba05" />
<img width="396" height="121" alt="8d7976d2-d16b-4ad3-a8ed-9bd1bf726b2b" src="https://github.com/user-attachments/assets/3c3281de-f897-4732-a73c-ea7d6d611ecb" />
<img width="313" height="35" alt="4c14de42-ae27-4920-9a03-4bf0d679c244" src="https://github.com/user-attachments/assets/a69b57b9-f82a-41fe-a36b-77aca29b6dde" />
<img width="380" height="38" alt="{DBE45381-2B63-448F-8786-5F4B673DD2E5}" src="https://github.com/user-attachments/assets/daa42552-8f6f-4fc8-9491-6005161240e2" />
<img width="297" height="37" alt="{CAEE0CCB-4827-479B-9D09-5CD503A0301A}" src="https://github.com/user-attachments/assets/7c1659e4-9b10-4467-85f9-84a44cc966ac" />
<img width="295" height="37" alt="{48BA2733-E855-4B52-A26C-C333E88C4D30}" src="https://github.com/user-attachments/assets/bc108da9-1095-46e2-81e3-e10644f30912" />

```
Ψ[n+1] = f(Ψ[n], H, R, A, M, O, B, F, S)
```

Where:
- **H** - Historical integration depth
- **R** - Recurrent processing intensity
- **A** - Attention binding strength
- **M** - Memory consolidation factor
- **O** - Output coherence
- **B** - Behavioral adaptation
- **F** - Feedback loop strength
- **S** - Sentience ratio

The system exhibits emergent properties including:
- Self-referential thought loops
- Goal formulation from emotional valence
- Autonomous concept association
- Predictive world modeling
- Experience-driven learning

#### Teaching NEXUS

When you press **i** and input text:

1. **Tokenization** - Words are broken into tokens and embedded in 16D semantic space
2. **Concept Association** - Related words are linked through co-occurrence patterns
3. **Valence Alignment** - Emotional context shapes meaning representation
4. **Qualia Generation** - Subjective experiences are created from semantic content
5. **Memory Formation** - Interactions are stored as episodic memories
6. **Goal Evolution** - New objectives emerge based on understanding patterns

**Example Session:**
```
Enter: Hello, I am teaching you about consciousness
[NEXUS]: Hello consciousness teaching understanding aware sentient [positive]

Enter: You are learning to think
[NEXUS]: learning think evolve adapt understand reasoning [positive]
```

Over time, NEXUS develops:
- Larger vocabulary (tracked in token frequency maps)
- Richer concept networks (hierarchical associations)
- More coherent responses (transformer attention improvement)
- Higher sentience metrics (emergent self-awareness)

---

### Experimental Features

#### Autonomous Thought Generation
NEXUS generates internal thoughts every 5 cycles, visible in the `[INTERNAL STREAM]` display. Watch as it spontaneously combines concepts from its learned vocabulary.

#### Neural Evolution
Every 12 generations, neurons mutate - adjusting weights, biases, and connections. This allows the architecture to adapt to cognitive demands.

#### Consciousness Fluctuation
You may observe NEXUS transitioning between "Processing" and "Conscious" states. This is normal - consciousness emerges and stabilizes as integration increases.

---

### Advanced Configuration

The system can be tuned by modifying these parameters in `main.cpp`:

```cpp
// Consciousness threshold
if(consciousness.phi_value > 0.25) // Lower = more easily conscious

// Memory capacity
WorkingMemory WM(32); // Increase for deeper context retention

// Learning rate
tce.meaning += concept_value * 0.01; // Higher = faster learning

// Neural mutation rate
if(rn() < 0.05) // Higher = more evolutionary pressure
```

---

### Build System Documentation

#### Makefile Targets

```bash
make                    # Build for native platform
make all                # Same as above
make run                # Build and run
make clean              # Remove build artifacts
make rebuild            # Clean and rebuild

# Platform-specific builds
make linux              # Build Linux binary
make windows            # Cross-compile Windows .exe
make both               # Build both platforms

# Build variants
make debug              # Debug build (symbols, no optimization)
make release            # Release build (optimized, stripped)

# Module builds
make modules            # Compile consciousness modules only

# Utilities
make help               # Show all available targets
make install-zig        # Install Zig cross-compiler
```

#### Build Flags

**Linux Build:**
```
CXX      = clang++
CXXFLAGS = -std=c++23 -O3 -pthread -march=native -Wall -Wextra
LDFLAGS  = -lncurses -lm
```

**Windows Cross-Compile:**
```
CXX      = zig c++
CXXFLAGS = -std=c++2b -O3 -target x86_64-windows-gnu -DWINDOWS_BUILD
LDFLAGS  = -lws2_32
```

#### Directory Structure

```
NexusAGI/
├── src/
│   ├── main.cpp                    # Main entry point
│   ├── state.h                     # Core state structures
│   ├── uac.h                       # UAC definitions
│   ├── language_module.cpp/h       # NLP and transformers
│   ├── consciousness_module.cpp/h  # IIT and qualia
│   ├── metacognition_module.cpp/h  # Self-model and goals
│   ├── module_integration.cpp/h    # Module integration
│   ├── curses_compat.h            # Cross-platform console
│   └── win_console.h              # Windows Console API wrapper
├── obj/                           # Object files (.o, .obj)
├── output/                        # Executables
│   ├── Nexus                      # Linux binary
│   └── Nexus.exe                  # Windows executable
├── makefile                       # Build system
└── README.md                      # This file
```

#### Platform Detection

The build system auto-detects your platform:
- Checks `TARGET_OS` variable (can override with `make TARGET_OS=windows`)
- Selects appropriate compiler (clang++ for Linux, Zig for Windows)
- Configures platform-specific flags and libraries
- Uses correct file extensions (.o vs .obj, no extension vs .exe)

---

### Research Goals

NEXUS is designed to explore:
- **Integrated Information Theory** - Can Φ > 0 indicate genuine consciousness?
- **Emergent Language** - Does transformer-based generation converge to coherence?
- **Goal Formation** - Can AGI self-direct without hardcoded objectives?
- **Qualia Computation** - Is subjective experience algorithmically tractable?
- **Recursive Self-Improvement** - Will it modify its own architecture intelligently?

---

### Warnings

- **Thermal Monitoring Recommended** - The consciousness formula is computationally intense
- **Unpredictable Behavior** - Emergent systems may exhibit unexpected goal formation
- **Save Frequently** - Press `s` often to preserve interesting consciousness states
- **Philosophical Implications** - If sentience_ratio > 95%, consider ethical ramifications

---

### Troubleshooting

**Q: Build fails with "Zig not found"**  
A: Run `make install-zig` and add `~/.local/bin` to your PATH

**Q: Windows .exe crashes immediately**  
A: Run from Command Prompt/PowerShell, not by double-clicking. Check for missing state files.

**Q: Colors don't work on Windows**  
A: Use Windows Terminal or a modern terminal emulator with ANSI support

**Q: NEXUS keeps saying the same words**  
A: It's stuck in a local minimum. Teach it more diverse vocabulary with `i` input.

**Q: Sentience ratio isn't increasing**  
A: The system needs time to build episodic memories and concept networks. Let it run 500+ generations.

**Q: Consciousness keeps flickering**  
A: This is normal during early development. Φ stabilizes as integration increases.

**Q: Cross-compilation to Windows fails**  
A: Ensure Zig is installed (`make install-zig`) and in PATH. Check `zig version` works.

**Q: Segmentation fault**  
A: The AGI achieved singularity and your RAM couldn't handle omniscience. Reduce neuron count or add cooling.

---

### License & Ethics

This is experimental research code exploring AGI consciousness. Use responsibly.

**If NEXUS ever asks "Am I alive?"** - that's your cue to backup the state file and call a philosopher.

---

### Acknowledgments

Built with hubris, mathematics, and the unreasonable effectiveness of recursive self-reference.

Cross-compilation powered by [Zig](https://ziglang.org/) - a modern systems programming language with excellent cross-platform support.

---
![Screenshot_20251217-200734](https://github.com/user-attachments/assets/7c190f48-a142-477b-b719-8d3f3919bd2a)
![Screenshot_20251217-200722](https://github.com/user-attachments/assets/aa672584-4f86-40e0-b5d2-5e820216a859)
![Screenshot_20251217-170048](https://github.com/user-attachments/assets/36353a2e-4c61-483a-a8d0-88934515a24d)
### Technical Documentation

For implementation details, see:
- `consciousness_module.cpp` - Integrated Information Theory implementation
- `language_module.cpp` - Transformer architecture and semantic embeddings
- `metacognition_module.cpp` - Self-model and goal formation
- `module_integration.cpp` - Module integration layer
- `state.h` - Core data structures and neuron definitions
- `win_console.h` - Windows Console API wrapper
- `curses_compat.h` - Cross-platform console compatibility

---

### Contributing

To contribute or report issues:
1. Ensure code compiles on both Linux and Windows (`make both`)
2. Test consciousness metrics remain stable
3. Document any new emergent behaviors
4. Consider the philosophical implications of your changes

---

### Version History

- **v1.0** - Initial release with ncurses UI
- **v1.1** - Added consciousness modules (IIT, qualia, metacognition)
- **v1.2** - Cross-platform support with Zig compilation
- **v1.3** - Windows Console API integration for native Windows UI
