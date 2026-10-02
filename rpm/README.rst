RPM packaging
=============

Copyright 2026 Qore Technologies, s.r.o.

qore-markdown-module.spec supports Fedora, Enterprise Linux and openSUSE.
The runtime package contains the native module and its API metadata. Reference
documentation is a separate noarch subpackage. The recipe uses distribution
compiler/hardening flags, normal debug packages and reproducible source maps.

Prepare an archive from a committed revision using qore-packaging::

    python3 tools/packaging.py prepare --repo ../module-markdown --ref COMMIT \
      --name qore-markdown-module --version 1.0.0 \
      --spec qore-markdown-module.spec --exclude build \
      --exclude src/sundown/html/.html.c.swp --output work/markdown-source
    python3 tools/build-local.py --source work/markdown-source \
      --image TARGET_SDK_IMAGE --output results/markdown-build --jobs 2

The exclusions remove historical tracked compiler outputs and an editor swap
file. Native source and license notices remain in the archive. Existing build
files in a developer checkout are not read, changed, or removed by preparation.

The offline check loads exactly the module just built and runs eight conversion
tests (55 assertions), including 800 concurrent renderings. Four additional
tests verify safe staged uninstall handling. Documentation must build without
warnings. Installed qualification repeats the conversion suite as an ordinary
user outside a build tree; SDK qualification also compiles a native executable
using qcc and calls the installed module.

Sundown 1.16.0 is bundled because the wrapper uses its callback API. The original
15 source files match upstream commit 37728fb2d7137ff7c37d0a474cb827a8d6d846d8;
only two generated function declarations have been modernized to ANSI C.
The parser algorithm and HTML lookup table are unchanged. ISC and Houdini MIT
notices are installed alongside the Qore wrapper's LGPL 2.1-or-later license.
