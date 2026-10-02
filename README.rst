Qore Markdown module
====================

Copyright 2026 Qore Technologies, s.r.o.

The module converts Markdown documents to HTML using Sundown 1.16.0.
Tables, fenced code blocks, automatic links, strikethrough and superscripts
are enabled. Raw HTML is preserved; applications accepting untrusted input
must apply their own HTML policy to the result.

Example::

    %modern
    %requires markdown
    string html = markdown_convert("# Invoice summary\n\n**Paid** in full.\n");
    printf("%s", html);

Build with the installed Qore SDK and CMake 3.16 or newer::

    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
    cmake --build build
    QORE_MODULE_DIR="$PWD/build" qore -b --enable-debug test/markdown.qtest -v
    cmake --build build --target docs

Match CMAKE_INSTALL_PREFIX to the installed qore executable. Use build-debug
with CMAKE_BUILD_TYPE=Debug for memory diagnostics. Generated API metadata is
installed with the native module. Doxygen is optional outside documentation
packaging. Tests cover empty and malformed input, rendering extensions,
escaping, Unicode, reference isolation, and concurrent conversions.

The wrapper is licensed under LGPL 2.1 or later (COPYING.LGPL); bundled Sundown
uses ISC (COPYING.Sundown), with the Houdini MIT notice retained in
COPYING.Houdini. Bundled source files match Sundown commit
37728fb2d7137ff7c37d0a474cb827a8d6d846d8, apart from the documented ANSI C
parameter declarations in its generated HTML-block lookup table.
