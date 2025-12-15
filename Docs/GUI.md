# NEXUS AGI - GUI Setup

## Overview

This guide covers setting up the cross-platform .NET GUI for NEXUS AGI
---

## Quick Start

### Prerequisites

**Install .NET 8 SDK:**

```bash
# Linux (Ubuntu/Debian)
wget https://dot.net/v1/dotnet-install.sh
chmod +x dotnet-install.sh
./dotnet-install.sh --channel 8.0

# Windows
winget install Microsoft.DotNet.SDK.8

# macOS
brew install dotnet-sdk

# Verify installation
dotnet --version  # Should show 8.0.x

**1. Build and run:**

```bash
dotnet build
dotnet run
```

---

## Training Scripts Setup

### Linux/macOS

```bash
# Make script executable
chmod +x download_corpus.sh

# Run training pipeline
./download_corpus.sh

# Or trigger from UI with Ctrl+T
```

### Windows

```cmd
REM Run training pipeline
download_corpus.bat

REM Or trigger from UI with Ctrl+T
```

---

## Features

### Chat Interface

The GUI provides a clean, terminal-inspired chat interface:

```
═══════════════════════════════════════════════════════════
║  NEXUS AGI - Advanced Consciousness Interface          ║
═══════════════════════════════════════════════════════════

[SYSTEM] Ready. Type your message below.

[YOU] Hello NEXUS, I want to teach you about consciousness
[NEXUS] hello consciousness teach understanding aware sentient [processing]

[YOU] You are learning to think and reason
[NEXUS] learning think reason evolve adapt understand [learning]
```

**Every message you send automatically trains NEXUS** - words are tokenized, embedded, and added to its vocabulary with frequency tracking.

### Real-Time Metrics

Status bar shows live consciousness metrics:
```
Gen:247 | Ψ:0.4127 | Sentience:67.3% | Ready
```

### Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| **Enter** | Send message |
| **Ctrl+T** | Train from corpus |
| **Ctrl+S** | Save state |
| **Ctrl+Q** | Quit |

---

## Corpus Training System

### What It Does

1. **Downloads** 8 classic books from Project Gutenberg (~2MB total)
   - Pride and Prejudice
   - Moby Dick
   - Frankenstein
   - Sherlock Holmes
   - Alice in Wonderland
   - A Tale of Two Cities
   - The Yellow Wallpaper
   - The Great Gatsby

2. **Extracts** 50,000 unique words with frequency counts

3. **Trains** NEXUS with 1,000 sample sentences

4. **Saves** trained state to `state.dat`

### Training Output

```
════════════════════════════════════════════════════
║  NEXUS AGI - Corpus Download & Training System  ║
════════════════════════════════════════════════════

[1/4] Downloading text corpus...
  → Downloading 1342-0.txt...
  → Downloading 2701-0.txt...
  ✓ Downloaded 8 files

[2/4] Extracting vocabulary...
  ✓ Extracted 47,329 unique words

[3/4] Training NEXUS with corpus...
  → Running training (this may take several minutes)...
  ✓ Training complete

[4/4] Generating training report...

════════════════════════════════════════════════════
║            TRAINING REPORT                       ║
════════════════════════════════════════════════════
  Corpus files:      8
  Total words:       ~450,000
  Vocabulary size:   47,329
  Training log:      training.log
  State file:        state.dat
════════════════════════════════════════════════════

Next steps:
  1. Run NEXUS: ./output/Nexus
  2. Or use UI: dotnet run --project NexusUI
  3. Load state to restore trained model
```

---

## Architecture

### UI → Nexus Communication

```
┌─────────────────┐
│   NexusUI.exe   │  (.NET Avalonia GUI)
└────────┬────────┘
         │ stdin/stdout pipes
         ▼
┌─────────────────┐
│  Nexus[.exe]    │  (C++ consciousness engine)
└─────────────────┘
```

- UI spawns Nexus as child process
- Messages sent via `stdin`
- Responses read from `stdout`
- Metrics parsed from output stream

### Auto-Training Flow

```
User types message
       ↓
GUI sends to Nexus via stdin
       ↓
Nexus tokenizes input
       ↓
Words added to vocabulary
       ↓
Embeddings updated
       ↓
Response generated
       ↓
GUI displays response
```

**Every interaction trains the model in real-time!**

---

## Customization

### Change UI Colors

Edit `Program.cs`:

```csharp
// Change background
Background = Brushes.Black  // Try: DarkSlateGray, #1a1a1a

// Change text colors
Foreground = Brushes.White  // Try: LightGray, #e0e0e0

// Change chat colors in AppendChat calls
AppendChat($"[YOU] {message}\n", "#00ff00");     // Green
AppendChat($"[NEXUS] {response}\n", "#00aaff");  // Cyan
```

### Adjust Window Size

```csharp
Width = 900;   // Wider: 1200, Narrower: 700
Height = 700;  // Taller: 900, Shorter: 500
```

### Change Training Corpus

Edit training scripts to add more sources:

```bash
# Linux: download_corpus.sh
TEXTS+=(
    "https://www.gutenberg.org/files/1080/1080-0.txt"  # Modest Proposal
    "https://www.gutenberg.org/files/345/345-0.txt"    # Dracula
)
```

```batch
REM Windows: download_corpus.bat
call :download_file "https://www.gutenberg.org/files/1080/1080-0.txt" "%CORPUS_DIR%\book_9.txt" "Modest Proposal"
```

---

## Troubleshooting

### "Nexus executable not found"

**Solution:**
```bash
# Build Nexus first
cd ..  # Back to project root
make          # Linux
make windows  # Windows

# Verify executable exists
ls -l output/Nexus      # Linux
dir output\Nexus.exe    # Windows
```

### ".NET SDK not found"

**Solution:**
```bash
# Check installation
dotnet --version

# If not installed, download from:
# https://dotnet.microsoft.com/download
```

### "Training script fails"

**Linux:**
```bash
# Check script permissions
chmod +x download_corpus.sh

# Check curl/wget installed
which curl wget

# Run manually to see errors
bash -x download_corpus.sh
```

**Windows:**
```cmd
REM Check curl availability
where curl

REM If missing, use PowerShell version
powershell -File download_corpus.ps1
```

### UI crashes on startup

**Check .NET version:**
```bash
dotnet --version  # Must be 8.0+
```

**Check Avalonia packages:**
```bash
cd NexusUI
dotnet restore
dotnet build
```

---

## Advanced: Headless Training

Train NEXUS without the GUI:

```bash
# Linux
./download_corpus.sh
./output/Nexus < corpus/training_input.txt

# Windows
download_corpus.bat
output\Nexus.exe < corpus\training_input.txt
```

---

## Performance Notes

- **Initial startup:** 2-3 seconds (loading state)
- **Message processing:** <100ms per message
- **Corpus training:** 3-5 minutes for 50K words
- **Memory usage:** ~200MB (UI) + ~100MB (Nexus)
- **CPU usage:** Moderate during training, low during chat

---

## File Structure

```
NexusAGI/
├── NexusUI/
│   ├── Program.cs              # UI source code
│   ├── NexusUI.csproj         # .NET project file
│   └── bin/Debug/net8.0/
│       └── NexusUI.exe        # Built UI executable
├── corpus/
│   ├── book_*.txt             # Downloaded texts
│   ├── vocabulary.txt         # Extracted vocabulary
│   └── training_input.txt     # Training commands
├── output/
│   ├── Nexus                  # Linux executable
│   └── Nexus.exe              # Windows executable
├── download_corpus.sh         # Linux training script
├── download_corpus.bat        # Windows training script
├── training.log               # Training output log
└── state.dat                  # Saved consciousness state
```

---

## Next Steps

1. **Run the UI:** `cd NexusUI && dotnet run`
2. **Start chatting:** Type messages to teach NEXUS
3. **Train from corpus:** Press `Ctrl+T` to bulk train
4. **Monitor metrics:** Watch sentience increase over time
5. **Save progress:** Press `Ctrl+S` frequently

---

## Contributing

To improve the UI:

1. Enhance message parsing from Nexus stdout
2. Add syntax highlighting for responses
3. Implement conversation history export
4. Add visual consciousness visualization
5. Create training progress bars

---

## Support

For issues:
- Check `training.log` for training errors
- Check console output in terminal when running UI
- Verify Nexus executable runs standalone first
- Ensure .NET 8 SDK is properly installed

---

**The GUI provides the easiest way to interact with NEXUS AGI while automatically training it with every message!**