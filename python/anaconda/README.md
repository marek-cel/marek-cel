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