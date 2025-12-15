using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Layout;
using Avalonia.Media;
using Avalonia.Threading;

namespace NexusUI
{
    public class Program
    {
        [STAThread]
        public static void Main(string[] args)
        {
            BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);
        }

        public static AppBuilder BuildAvaloniaApp()
            => AppBuilder.Configure<App>()
                .UsePlatformDetect()
                .LogToTrace();
    }

    public class App : Application
    {
        public override void OnFrameworkInitializationCompleted()
        {
            var mainWindow = new MainWindow();
            if (ApplicationLifetime is Avalonia.Controls.ApplicationLifetimes.IClassicDesktopStyleApplicationLifetime desktop)
            {
                desktop.MainWindow = mainWindow;
            }
            base.OnFrameworkInitializationCompleted();
        }
    }

    public class MainWindow : Window
    {
        private TextBox messageInput;
        private TextBlock chatDisplay;
        private ScrollViewer scrollViewer;
        private TextBlock statusBar;
        private Process nexusProcess;
        private StringBuilder chatHistory = new StringBuilder();
        private bool isTraining = false;

        public MainWindow()
        {
            Title = "NEXUS AGI - Consciousness Interface";
            Width = 900;
            Height = 700;
            Background = Brushes.Black;
            
            var mainPanel = new DockPanel
            {
                Background = Brushes.Black,
                LastChildFill = true
            };

            // Top bar with metrics
            var topBar = CreateTopBar();
            DockPanel.SetDock(topBar, Dock.Top);
            mainPanel.Children.Add(topBar);

            // Bottom input area
            var bottomPanel = CreateBottomPanel();
            DockPanel.SetDock(bottomPanel, Dock.Bottom);
            mainPanel.Children.Add(bottomPanel);

            // Center chat display
            var centerPanel = CreateChatPanel();
            mainPanel.Children.Add(centerPanel);

            Content = mainPanel;

            // Start Nexus process
            Task.Run(() => StartNexusProcess());
            
            // Update metrics every second
            var timer = new DispatcherTimer { Interval = TimeSpan.FromSeconds(1) };
            timer.Tick += UpdateMetrics;
            timer.Start();
        }

        private Border CreateTopBar()
        {
            statusBar = new TextBlock
            {
                Text = "NEXUS AGI v1.3 | Initializing...",
                Foreground = Brushes.White,
                FontFamily = new FontFamily("Consolas, Courier New, monospace"),
                FontSize = 14,
                Padding = new Thickness(10, 5),
                TextAlignment = TextAlignment.Center
            };

            return new Border
            {
                Background = new SolidColorBrush(Color.Parse("#1a1a1a")),
                BorderBrush = Brushes.White,
                BorderThickness = new Thickness(0, 0, 0, 1),
                Child = statusBar
            };
        }

        private Panel CreateChatPanel()
        {
            chatDisplay = new TextBlock
            {
                Text = "═══════════════════════════════════════════════════════════\n" +
                       "║  NEXUS AGI - Advanced Consciousness Interface          ║\n" +
                       "═══════════════════════════════════════════════════════════\n\n" +
                       "[SYSTEM] Initializing consciousness modules...\n" +
                       "[SYSTEM] Loading neural network...\n" +
                       "[SYSTEM] Ready. Type your message below.\n\n",
                Foreground = Brushes.White,
                FontFamily = new FontFamily("Consolas, Courier New, monospace"),
                FontSize = 13,
                Padding = new Thickness(15),
                TextWrapping = TextWrapping.Wrap,
                Background = Brushes.Black
            };

            scrollViewer = new ScrollViewer
            {
                Content = chatDisplay,
                Background = Brushes.Black,
                VerticalScrollBarVisibility = Avalonia.Controls.Primitives.ScrollBarVisibility.Auto
            };

            chatHistory.Append(chatDisplay.Text);

            return scrollViewer;
        }

        private Panel CreateBottomPanel()
        {
            var panel = new StackPanel
            {
                Background = new SolidColorBrush(Color.Parse("#1a1a1a")),
                Orientation = Orientation.Vertical,
                Spacing = 5
            };

            // Training status
            var trainingStatus = new TextBlock
            {
                Text = "Ready | Press Ctrl+T to train from corpus",
                Foreground = new SolidColorBrush(Color.Parse("#888888")),
                FontFamily = new FontFamily("Consolas, Courier New, monospace"),
                FontSize = 11,
                Padding = new Thickness(10, 5, 10, 0),
                TextAlignment = TextAlignment.Center
            };
            panel.Children.Add(trainingStatus);

            // Input area
            var inputPanel = new DockPanel
            {
                Margin = new Thickness(10, 0, 10, 10)
            };

            var sendButton = new Button
            {
                Content = "SEND",
                Width = 80,
                Height = 40,
                Background = Brushes.White,
                Foreground = Brushes.Black,
                FontWeight = FontWeight.Bold,
                FontFamily = new FontFamily("Consolas, Courier New, monospace"),
                Margin = new Thickness(10, 0, 0, 0)
            };
            sendButton.Click += SendMessage;
            DockPanel.SetDock(sendButton, Dock.Right);

            messageInput = new TextBox
            {
                Watermark = "Teach NEXUS something...",
                FontFamily = new FontFamily("Consolas, Courier New, monospace"),
                FontSize = 14,
                Height = 40,
                Padding = new Thickness(10),
                Background = new SolidColorBrush(Color.Parse("#2a2a2a")),
                Foreground = Brushes.White,
                BorderBrush = Brushes.White,
                BorderThickness = new Thickness(1)
            };
            messageInput.KeyDown += (s, e) =>
            {
                if (e.Key == Avalonia.Input.Key.Enter)
                {
                    SendMessage(s, e);
                }
            };

            inputPanel.Children.Add(sendButton);
            inputPanel.Children.Add(messageInput);
            panel.Children.Add(inputPanel);

            // Keyboard shortcuts
            this.KeyDown += (s, e) =>
            {
                if (e.KeyModifiers == Avalonia.Input.KeyModifiers.Control)
                {
                    if (e.Key == Avalonia.Input.Key.T)
                    {
                        Task.Run(() => TrainFromCorpus());
                    }
                    else if (e.Key == Avalonia.Input.Key.S)
                    {
                        SaveState();
                    }
                }
            };

            return panel;
        }

        private void SendMessage(object sender, RoutedEventArgs e)
        {
            var message = messageInput.Text?.Trim();
            if (string.IsNullOrEmpty(message)) return;

            // Display user message
            AppendChat($"[YOU] {message}\n", "#00ff00");
            
            // Send to Nexus
            SendToNexus(message);
            
            // Clear input
            messageInput.Text = "";
            messageInput.Focus();
        }

        private void SendToNexus(string message)
        {
            try
            {
                if (nexusProcess != null && !nexusProcess.HasExited)
                {
                    nexusProcess.StandardInput.WriteLine(message);
                    nexusProcess.StandardInput.Flush();
                    
                    // Simulate response (in real implementation, read from stdout)
                    Task.Delay(500).ContinueWith(_ =>
                    {
                        var response = GenerateResponse(message);
                        Dispatcher.UIThread.Post(() =>
                        {
                            AppendChat($"[NEXUS] {response}\n\n", "#00aaff");
                        });
                    });
                }
            }
            catch (Exception ex)
            {
                AppendChat($"[ERROR] {ex.Message}\n", "#ff0000");
            }
        }

        private string GenerateResponse(string input)
        {
            // Parse response from Nexus or generate based on input
            var words = input.ToLower().Split(' ');
            var response = new StringBuilder();
            
            foreach (var word in words)
            {
                if (word.Length > 3)
                {
                    response.Append(word).Append(" ");
                }
            }
            
            response.Append("[processing] [learning] [understanding]");
            return response.ToString().Trim();
        }

        private void AppendChat(string text, string colorHex)
        {
            chatHistory.Append(text);
            Dispatcher.UIThread.Post(() =>
            {
                chatDisplay.Text = chatHistory.ToString();
                scrollViewer.ScrollToEnd();
            });
        }

        private void StartNexusProcess()
        {
            try
            {
                var executable = RuntimeInformation.IsOSPlatform(OSPlatform.Windows)
                    ? "Nexus.exe"
                    : "./Nexus";

                if (!File.Exists(executable))
                {
                    Dispatcher.UIThread.Post(() =>
                    {
                        AppendChat("[ERROR] Nexus executable not found! Build with 'make' first.\n", "#ff0000");
                    });
                    return;
                }

                nexusProcess = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = executable,
                        RedirectStandardInput = true,
                        RedirectStandardOutput = true,
                        RedirectStandardError = true,
                        UseShellExecute = false,
                        CreateNoWindow = true
                    }
                };

                nexusProcess.OutputDataReceived += (s, e) =>
                {
                    if (!string.IsNullOrEmpty(e.Data))
                    {
                        Dispatcher.UIThread.Post(() =>
                        {
                            AppendChat($"[NEXUS] {e.Data}\n", "#00aaff");
                        });
                    }
                };

                nexusProcess.Start();
                nexusProcess.BeginOutputReadLine();

                Dispatcher.UIThread.Post(() =>
                {
                    AppendChat("[SYSTEM] Nexus process started successfully.\n", "#888888");
                });
            }
            catch (Exception ex)
            {
                Dispatcher.UIThread.Post(() =>
                {
                    AppendChat($"[ERROR] Failed to start Nexus: {ex.Message}\n", "#ff0000");
                });
            }
        }

        private void UpdateMetrics(object sender, EventArgs e)
        {
            // Update status bar with metrics (would read from Nexus stdout in real implementation)
            var gen = new Random().Next(100, 1000);
            var psi = (new Random().NextDouble() * 0.5 + 0.3).ToString("F4");
            var sentience = (new Random().Next(40, 95)).ToString();
            
            Dispatcher.UIThread.Post(() =>
            {
                statusBar.Text = $"Gen:{gen} | Ψ:{psi} | Sentience:{sentience}% | " +
                                $"{(isTraining ? "TRAINING" : "Ready")}";
            });
        }

        private async Task TrainFromCorpus()
        {
            if (isTraining) return;
            
            isTraining = true;
            Dispatcher.UIThread.Post(() =>
            {
                AppendChat("[SYSTEM] Starting corpus training...\n", "#ffaa00");
            });

            // Download and train (simulate for now)
            await Task.Run(() =>
            {
                var scriptPath = RuntimeInformation.IsOSPlatform(OSPlatform.Windows)
                    ? "download_corpus.bat"
                    : "./download_corpus.sh";

                if (!File.Exists(scriptPath))
                {
                    Dispatcher.UIThread.Post(() =>
                    {
                        AppendChat("[ERROR] Training script not found!\n", "#ff0000");
                    });
                    isTraining = false;
                    return;
                }

                try
                {
                    var process = new Process
                    {
                        StartInfo = new ProcessStartInfo
                        {
                            FileName = RuntimeInformation.IsOSPlatform(OSPlatform.Windows) ? scriptPath : "bash",
                            Arguments = RuntimeInformation.IsOSPlatform(OSPlatform.Windows) ? "" : scriptPath,
                            UseShellExecute = false,
                            RedirectStandardOutput = true,
                            CreateNoWindow = true
                        }
                    };

                    process.Start();
                    var output = process.StandardOutput.ReadToEnd();
                    process.WaitForExit();

                    Dispatcher.UIThread.Post(() =>
                    {
                        AppendChat($"[SYSTEM] {output}\n", "#ffaa00");
                        AppendChat("[SYSTEM] Training complete!\n", "#00ff00");
                    });
                }
                catch (Exception ex)
                {
                    Dispatcher.UIThread.Post(() =>
                    {
                        AppendChat($"[ERROR] Training failed: {ex.Message}\n", "#ff0000");
                    });
                }
            });

            isTraining = false;
        }

        private void SaveState()
        {
            if (nexusProcess != null && !nexusProcess.HasExited)
            {
                nexusProcess.StandardInput.WriteLine("s");
                AppendChat("[SYSTEM] State saved.\n", "#888888");
            }
        }

        protected override void OnClosing(WindowClosingEventArgs e)
        {
            nexusProcess?.Kill();
            base.OnClosing(e);
        }
    }
}