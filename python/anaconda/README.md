# Sample Project

## Initial Setup

### Prerequisites

Make sure you have [Anaconda](https://www.anaconda.com/download) or [Miniconda](https://docs.conda.io/en/latest/miniconda.html) installed.

### Creating the Conda Environment

```bash
conda env create -f environment.yml
```

### Activating the Environment

```bash
conda activate sample-project
```

### Updating the Environment

If `environment.yml` changes, sync your environment with:

```bash
conda env update -f environment.yml --prune
```

### Deactivating the Environment

```bash
conda deactivate
```

## Troubleshooting

### Windows: `conda` not recognized in PowerShell / VS Code

If you see `conda : The term 'conda' is not recognized...` when running from VS Code or PowerShell, follow these steps:

**1. Initialize conda for PowerShell**

Open **Anaconda Prompt** (not PowerShell) and run:

```bash
conda init powershell
```

Then restart VS Code completely.

**2. Allow PowerShell to run scripts**

Open PowerShell **as Administrator** and run:

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

**Alternative: use Command Prompt instead of PowerShell**

If you'd rather not change PowerShell settings, switch VS Code's default terminal to Command Prompt:

1. Open the Command Palette (`Ctrl+Shift+P`)
2. Search for **Terminal: Select Default Profile**
3. Choose **Command Prompt**

`conda` works in Command Prompt without any extra configuration.