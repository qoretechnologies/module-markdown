# Copyright (C) 2026 Qore Technologies, s.r.o.
# SPDX-License-Identifier: MIT
# Use the pinned source epoch for RPM headers and installed file timestamps.
%global source_date_epoch_from_changelog 1
%global use_source_date_epoch_as_buildtime 1
%if v"%{rpmversion}" >= v"4.20"
%global build_mtime_policy clamp_to_source_date_epoch
%else
%global clamp_mtime_to_source_date_epoch 1
%endif
%bcond_without tests
%bcond_without docs
Name: qore-markdown-module
Version: 1.0.0
Release: 1%{?dist}
Summary: Markdown-to-HTML conversion for Qore
License: LGPL-2.1-or-later AND ISC AND MIT
URL: https://github.com/qoretechnologies/module-markdown
Source0: %{name}-%{version}.tar.xz
BuildRequires: cmake >= 3.16
BuildRequires: make
BuildRequires: gcc-c++
BuildRequires: gcc
%if %{with tests}
BuildRequires: python3 >= 3.11
%endif
Provides: bundled(sundown) = 1.16.0
Provides: bundled(houdini)
BuildRequires: qore-devel >= 3.0.0~
BuildRequires: qore-rpm-macros >= 3.0.0~
%if %{with docs}
BuildRequires: doxygen
%if 0%{?suse_version}
BuildRequires: util-linux
%else
BuildRequires: util-linux-core
%endif
%endif

%description
Native Qore module for converting Markdown documents to HTML using Sundown.
Supports tables, fenced code, automatic links, strikethrough and superscripts.
Raw HTML is preserved; applications control the policy for untrusted input.

%if %{with docs}
%package doc
Summary: Markdown module reference documentation
BuildArch: noarch
%description doc
API reference and examples for Qore's Markdown module.
%endif

%prep
%autosetup
%build
%{?set_build_flags}
. %{_rpmconfigdir}/qore/module-env.sh
qore_set_source_prefix_maps "%{qore_debug_source_dir}"
cmake -S . -B build -G 'Unix Makefiles' \
  -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE=-DNDEBUG \
  -DCMAKE_C_FLAGS_RELEASE=-DNDEBUG \
  -DCMAKE_INSTALL_PREFIX=%{_prefix} -DCMAKE_INSTALL_LIBDIR=%{_lib} \
  -DCMAKE_SKIP_RPATH=ON -DCMAKE_IGNORE_PREFIX_PATH=/usr/local \
  -DQore_DIR=%{_libdir}/cmake/Qore -DQORE_EXECUTABLE=/usr/bin/qore \
  -DQORE_QPP_EXECUTABLE=/usr/bin/qpp \
  -DCMAKE_DISABLE_FIND_PACKAGE_Doxygen=%{!?with_docs:ON}%{?with_docs:OFF}
cmake --build build -- %{?_smp_mflags}
%if %{with docs}
printf '\nWARN_AS_ERROR = FAIL_ON_WARNINGS\n' >> build/Doxyfile
cmake --build build --target docs -- %{?_smp_mflags}
%endif
%install
DESTDIR=%{buildroot} cmake --install build
chmod 755 %{buildroot}%{_libdir}/qore-modules/markdown-api-*.qmod
%if %{with docs}
install -d %{buildroot}%{_docdir}/%{name}-doc
cp -a build/docs/markdown/html %{buildroot}%{_docdir}/%{name}-doc/
hardlink -t -O %{buildroot}%{_docdir}/%{name}-doc
%endif
%check
%if %{with tests}
. %{_rpmconfigdir}/qore/module-env.sh
/usr/bin/qore -b --enable-debug -l "$PWD/build/markdown-api-$(/usr/bin/qore --latest-module-api).qmod" test/markdown.qtest -v
python3 -B -W error -m unittest discover -s test -p test_uninstall.py -v
%endif
%files
%license COPYING.LGPL COPYING.Sundown COPYING.Houdini
%doc README.rst
%{_libdir}/qore-modules/markdown-api-*.qmod
%dir %{_datadir}/qore/metadata/markdown
%{_datadir}/qore/metadata/markdown/*.meta.json
%if %{with docs}
%files doc
%license COPYING.LGPL COPYING.Sundown COPYING.Houdini
%doc %{_docdir}/%{name}-doc/
%endif
%changelog
* Fri Oct 02 2026 David Nichols <david@qore.org> - 1.0.0-1
- Build from a clean source archive with the packaged Qore SDK and ABI dependency generator.
- Include API metadata, documentation, bundled-library notices, and offline conversion checks.
