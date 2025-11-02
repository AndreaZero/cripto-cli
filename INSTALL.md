# Installation Guide

## Global Installation of the `crypto` Command

To make the `crypto` command executable from any terminal directory, you have several options:

### Option 1: Installation with Make (Recommended)

This is the simplest and cleanest solution:

```bash
make
sudo make install
```

This command will copy the executable to `/usr/local/bin/crypto`, making it available globally.

To uninstall:
```bash
sudo make uninstall
```

### Option 2: Add bin/ to PATH

If you prefer not to install globally, you can add the `bin/` directory to your PATH:

**For Bash/Zsh:**
Add this line to your `~/.bashrc` or `~/.zshrc`:
```bash
export PATH="$PATH:/full/path/to/crypto-cli/bin"
```

Then reload the shell:
```bash
source ~/.bashrc  # or source ~/.zshrc
```

**For Fish:**
Add this line to your `~/.config/fish/config.fish`:
```fish
set -gx PATH $PATH /full/path/to/crypto-cli/bin
```

### Option 3: Create an Alias

Add an alias to your `~/.bashrc` or `~/.zshrc`:

```bash
alias crypto='/full/path/to/crypto-cli/bin/crypto'
```

Then reload the shell:
```bash
source ~/.bashrc  # or source ~/.zshrc
```

## Verify Installation

After installation, verify that it works:

```bash
which crypto
crypto --version
crypto btc
```

If you see the path and the command works, the installation was successful!

## Note for Windows (WSL)

On WSL, installation with `make install` works exactly the same as on Linux. If you use Windows PowerShell, you may need to manually add the path to Windows PATH.
