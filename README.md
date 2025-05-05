# Borderlands Witch
A library allowing Borderlands PythonSDK mods to read and write raw memory (including executable memory) at runtime.

To get started, [download the latest release](https://github.com/mopioid/Borderlands-Witch/releases). The `witch` folder inside the release's zip can simply be added to your project, and then imported with a relative import:

```python
from . import witch
```

Witch provides two functions, `memory_range` and `sigscan`, [described in its stubs file](https://github.com/mopioid/Borderlands-Witch/blob/main/witch.pyi) (`__init__.pyi`).
