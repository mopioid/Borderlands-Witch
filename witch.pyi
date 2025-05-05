from typing import overload

def memory_range(start: int, size: int, unlock: bool = False) -> memoryview:
    """
    Expose a range of raw memory for reading and optionally writing.

    Args:
        start:
            The address in memory to expose. No safety checks are performed to
            ensure this is a valid address readable by the current application.
        size:
            The length of memory to expose. No safety checks are performed to
            ensure the resulting range is readable by the current application.
        unlock:
            If `True`, the range of memory is unlocked for writing before being
            returned, if it was not already.
    Returns:
        A `memoryview` instance representing the range of memory.
    """
    ...

@overload
def sigscan(pattern: str) -> int | None:
    """
    Scan the executable memory for a byte string matching the specified
    pattern.

    Args:
        pattern:
            The pattern string to scan for. Byte values are specified as pairs
            of hexadecimal digits. Spaces are ignored. All other characters are
            treated as wildcards.
    Returns:
        The address of the first matching byte string, or `None` if no matches
        are found.
    """
    ...

@overload
def sigscan(pattern: str, *, start: int, size: int) -> int | None:
    """
    Scan the provided memory range for a byte string matching the specified
    pattern.

    Args:
        pattern:
            The pattern string to scan for. Byte values are specified as pairs
            of hexadecimal digits. Spaces are ignored. All other characters are
            treated as wildcards.
        start:
            The address to begin the scan at. No safety checks are performed to
            ensure this is a valid address readable by the current application.
        size:
            The length of memory to expose. No safety checks are performed to
            ensure the resulting range is readable by the current application.
    Returns:
        The address of the first matching byte string, or `None` if no matches
        are found.
    """
    ...

@overload
def sigscan(bytes: bytes, mask: bytes | None = None) -> int | None:
    """
    Scan the provided memory range for a matching byte string.

    Args:
        bytes:
            The byte string to scan for.
        mask:
            If specified, a byte string of the same length of `bytes`, used to
            mask memory bytes with logical ANDs when comparing them against the
            values specified in `bytes`.
    Returns:
        The address of the first matching byte string, or `None` if no matches
        are found.
    """
    ...

@overload
def sigscan(
    bytes: bytes, mask: bytes | None = None, *, start: int, size: int
) -> int | None:
    """
    Scan the provided memory range for a byte string matching the specified
    pattern.

    Args:
        bytes:
            The byte string to scan for.
        mask:
            If specified, a byte string of the same length of `bytes`, used to
            mask memory bytes with logical ANDs when comparing them against the
            values specified in `bytes`.
        size:
            The length of memory to expose. No safety checks are performed to
            ensure the resulting range is readable by the current application.
    Returns:
        The address of the first matching byte string, or `None` if no matches
        are found.
    """
    ...
