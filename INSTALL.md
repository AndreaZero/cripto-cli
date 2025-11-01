# Installation Guide

## Installazione Globale del Comando `crypto`

Per rendere il comando `crypto` eseguibile da qualsiasi directory del terminale, hai diverse opzioni:

### Opzione 1: Installazione con Make (Consigliata)

Questa è la soluzione più semplice e pulita:

```bash
make
sudo make install
```

Questo comando copierà l'eseguibile in `/usr/local/bin/crypto`, rendendolo disponibile globalmente.

Per disinstallare:
```bash
sudo make uninstall
```

### Opzione 2: Aggiungere bin/ al PATH

Se preferisci non installare globalmente, puoi aggiungere la directory `bin/` al tuo PATH:

**Per Bash/Zsh:**
Aggiungi questa riga al tuo `~/.bashrc` o `~/.zshrc`:
```bash
export PATH="$PATH:/percorso/completo/a/crypto-cli/bin"
```

Poi ricarica la shell:
```bash
source ~/.bashrc  # o source ~/.zshrc
```

**Per Fish:**
Aggiungi questa riga al tuo `~/.config/fish/config.fish`:
```fish
set -gx PATH $PATH /percorso/completo/a/crypto-cli/bin
```

### Opzione 3: Creare un Alias

Aggiungi un alias al tuo `~/.bashrc` o `~/.zshrc`:

```bash
alias crypto='/percorso/completo/a/crypto-cli/bin/crypto'
```

Poi ricarica la shell:
```bash
source ~/.bashrc  # o source ~/.zshrc
```

## Verifica Installazione

Dopo l'installazione, verifica che funzioni:

```bash
which crypto
crypto --version
crypto btc
```

Se vedi il path e il comando funziona, l'installazione è riuscita!

## Nota per Windows (WSL)

Su WSL, l'installazione con `make install` funziona esattamente come su Linux. Se usi PowerShell di Windows, potresti dover aggiungere il percorso manualmente al PATH di Windows.

