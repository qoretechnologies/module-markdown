# Markdown SDK compatibility and conversion audit

Copyright 2026 Qore Technologies, s.r.o.

Scope: current CMake/SDK support, documentation and licenses, two generated C parameter declarations, deterministic conversion and uninstall tests. Existing tracked build/ files in the user checkout are excluded from this change.

Validation is recorded under qore-packaging/results/markdown-native-2-*, markdown-native-3-*, markdown-uninstall-tests-1.log and markdown-staged-install-uninstall-1.json. The clean source copy excludes tracked build outputs and the editor swap file.

|!Check|!Status|!Evidence
|1. Entry exists in `doxygen/lang/120_modules.dox.tmpl` (for modules in the Qore repo; N/A for external module repos)|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|2. Entry exists in `doxygen/lang/900_release_notes.dox.tmpl` (for modules in the Qore repo; external modules have release notes in their .qm)|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|3. `qore_user_module()` or `qore_external_user_module()` call in `CMakeLists.txt`|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|4. Module added to QMOD list in `CMakeLists.txt`|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|5. `.qm` file has `@section <lowercasemodname>intro` as first doc section — must be all lowercase (e.g., `avrodataproviderintro`, not `AvroDataProviderintro`)|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|6. `%modern` in `.qm` file — no redundant `%new-style`, `%require-types`, `%strict-args`, `%enable-all-warnings`|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|7. No parse directives (`%requires`, `%modern`, `%new-style`) in separated `.qc` files (check OUTSIDE of `@code` blocks only)|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|8. No `%include` usage (deprecated for modules)|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|9. Copyright 2026 on all new files|Pass|New project code, tests, documentation and build helpers carry 2026 copyright. Upstream license notices remain intact.
|10. Directory layout: `.qm` inside `qlib/<ModuleName>/` directory (not at `qlib/<ModuleName>.qm` for multi-file modules)|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|11. No second `.qm` for the same module at `qlib/<ModuleName>.qm`|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|12. `ns=Qore::XX` matches the QoreNamespace constructor path|N/A|No new .qm module or QPP class; registration, module layout and class namespace checks do not apply.
|13. `%modern` directive present|Pass|test/markdown.qtest uses %modern.
|14. Executable permission set (`chmod +x`)|Pass|test/markdown.qtest is executable.
|15. Uses %prepend-module-path  before %requires for in-repo modules (Qore and Qore modules only; not Qorus)|Pass|The tested binary module is selected with QORE_MODULE_DIR; QUnit belongs to the installed Qore SDK. No local Qore source module is imported.
|16. External module dependencies use `%try-module` — except modules delivered with the project itself (Qore ex: DataProvider, ConnectionProvider, QUnit, etc.) which use hard `%requires`|Pass|markdown is delivered by this repository and uses hard %requires. QUnit is part of Qore and also uses hard %requires.
|17. No filesystem operations (fopen, open, creat, unlink, remove, rename, mkdir, rmdir, stat, chmod) without sandbox checks|Pass|The changed native header performs no filesystem access. The staged CMake uninstall validates paths before removal and preserves symlink targets.
|18. No network operations (connect, bind, socket, getaddrinfo, gethostbyname) without sandbox checks|Pass|No network operations in changed code or conversion fixtures.
|19. If filesystem/network ops exist, verify `QoreSandboxManagerHelper` usage|N/A|No native filesystem/network entry point is added.
|20. No `File::`, `Dir::`, `Socket::`, `HTTPClient::` usage without justification|N/A|No Qore implementation uses filesystem or network APIs; fixtures only render in-memory text.
|21. All `for`/`while` loops that could iterate >100 times have `qore_check_cancel()` checks|Pass|Native changes are two parameter declarations only; the generated lookup algorithm is unchanged. Qore test loops use the interpreter cancellation points.
|22. Uses `qore_check_cancel()` (NOT deprecated `qore_check_io_interrupt()`)|Pass|No deprecated cancellation API introduced.
|23. Check frequency: every 100 iterations for tight loops, every 10 for expensive iterations|N/A|No native loop implementation changed; only two function declarations were modernized.
|24. No blocking operations without cancellation support|Pass|Concurrent tests synchronize through a bounded Queue wait; no sleeps or polling. Worker exceptions return through the same queue.
|25. Every action has `display_name`, `short_desc` (plain text, <80 chars), `desc` (markdown)|N/A|No DataProvider, action, application, description schema or factory changes.
|26. Every action has `options` populated via `getActionOptionFromFields()` — without this, the action shows an empty, unusable form|N/A|No DataProvider, action, application, description schema or factory changes.
|27. Every action has `output_type` set to a typed data type constant (e.g., `MyResponseDataType`) — not omitted|N/A|No DataProvider, action, application, description schema or factory changes.
|28. DPAT_API actions: provider has `"supports_request": True` and implements `doRequestImpl()`|N/A|No DataProvider, action, application, description schema or factory changes.
|29. DPAT_FIND actions: every option exists in `SearchOptions`, `getRecordTypeImpl()` returns `*hash<string, AbstractDataField>`|N/A|No DataProvider, action, application, description schema or factory changes.
|30. Scheme-based apps (with `"scheme"` in registerApp): actions use `"path"` and do NOT use `"cls"` — having both `scheme` and `cls` causes a runtime error|N/A|No DataProvider, action, application, description schema or factory changes.
|31. Single-key hash slices use trailing comma: `Fields{"key",}` (without trailing comma, `Fields{"key"}` returns the value, not a hash)|N/A|No DataProvider, action, application, description schema or factory changes.
|32. Typed data type classes exist for request and response types — inherit `HashDataType`, have `const Fields` hash, call `addQoreFields(Fields)` in constructor, export public constant at bottom (e.g., `public const MyDataType = new MyDataType();`)|N/A|No DataProvider, action, application, description schema or factory changes.
|33. Request/input types use `public` Fields (enables `ClassName::Fields` in action registration)|N/A|No DataProvider, action, application, description schema or factory changes.
|34. Response/output types use `private` Fields|N/A|No DataProvider, action, application, description schema or factory changes.
|35. Each field in data types has `display_name`, `type`, and `desc` (markdown-formatted)|N/A|No DataProvider, action, application, description schema or factory changes.
|36. Input fields have `example_value` where useful (string fields, endpoint URIs, SQL queries, etc.)|N/A|No DataProvider, action, application, description schema or factory changes.
|37. Fields with finite allowed values use `allowed_values` with `AllowedValueInfo` containing both `value` and `display_name` (Title Case, human-readable) — never bare values, never described only in text|N/A|No DataProvider, action, application, description schema or factory changes.
|38. Password/secret fields have `"sensitive": True`|N/A|No DataProvider, action, application, description schema or factory changes.
|39. `groups` uses `AppGroup` enum values from `qlib/DataProvider/AppGroup.qc`|N/A|No DataProvider, action, application, description schema or factory changes.
|40. App `logo` stored as separate file, loaded at module level in `Priv` namespace|N/A|No DataProvider, action, application, description schema or factory changes.
|41. App `desc` uses markdown: bullet list of capabilities, links to project website, business-language explanation of value|N/A|No DataProvider, action, application, description schema or factory changes.
|42. `display_name` is user-friendly ("Apache Avro" not "avro")|N/A|No DataProvider, action, application, description schema or factory changes.
|43. `short_desc` is plain text, under 80 chars, single sentence — no markdown|N/A|No DataProvider, action, application, description schema or factory changes.
|44. `desc` uses markdown: backticks for code/field refs (`` `field_name` ``, `` `True` ``, `` `pdf` ``), `\n\n` for paragraphs, `- ` bullet lists for enumerations, `bold` for caveats|N/A|No DataProvider, action, application, description schema or factory changes.
|45. Descriptions use plain business language relating to common challenges — not just technical "what" but "why" and "when to use"|N/A|No DataProvider, action, application, description schema or factory changes.
|46. No bare `True`/`False`/`NOTHING` — must be backtick-wrapped in `desc`|N/A|No DataProvider, action, application, description schema or factory changes.
|47. No bare field/option names in prose — must use backticks|N/A|No DataProvider, action, application, description schema or factory changes.
|48. Long descriptions (>500 chars) use bold section headers and bullet lists|N/A|No DataProvider, action, application, description schema or factory changes.
|49. Factory registration in Qore repo: every factory name registered in `qlib/DataProvider/DataProvider.qc` → `FactoryMap` (without this, module loads but doesn't appear in Qorus apps)|N/A|No DataProvider, action, application, description schema or factory changes.
|50. `getRecordTypeImpl()` signature: must be `private *hash<string, AbstractDataField> getRecordTypeImpl(*hash<auto> search_options)` — NOT returning `*AbstractDataProviderType`|N/A|No DataProvider, action, application, description schema or factory changes.
|51. Dependency JARs committed (for JNI modules): JAR files in `qlib/*/jar/` may be gitignored — use `git add -f` to ensure they're tracked, otherwise CI compilation fails|N/A|No JNI or JAR dependency.
|52. JAR install rules in CMakeLists.txt for all dependency JARs|N/A|No JNI or JAR dependency.
|53. No workarounds: No TODOs, FIXMEs, stubs, or partially-implemented features|Pass|The CMake minimum, external-module macro, missing documentation footer and uninstall helper are corrected directly. K&R declarations are replaced with equivalent ANSI C declarations; no diagnostics disabled.
|54. Exception safety: C++ uses `ReferenceHolder` for Qore allocations, `std::unique_ptr` for C++ allocations, `*xsink` checked after every fallible operation|Pass|No native allocation/ownership implementation changed. Uninstall validates the complete manifest before deleting files; Python test staging is cleaned up on failure.
|55. Thread safety: All mutable shared state protected by `std::lock_guard<std::mutex>` or documented as immutable-after-construction|Pass|The native lookup implementation remains unchanged. Concurrent rendering tests use private per-call Sundown state and queue-based result collection, with 800 verified conversions.
|56. Type safety: Strongly-typed `code<return(args)>` instead of untyped `code`; `static_cast` instead of C casts; typed hashdecls for results; enums where appropriate|Pass|ANSI parameter types preserve the existing const char pointer and unsigned-int length. Qore fixtures use typed methods and hash<string, bool>.
|57. Performance: No O(n²) where O(n) is possible; no unnecessary copies; coordinate descent uses incremental residuals not full matrix multiply|Pass|No parser algorithm or hash table changes. Tests verify generated HTML and reference isolation.
|58. Error handling: All inputs validated (dimensions, empty data, unfitted models); C++ I/O handles EAGAIN/EINTR if applicable|Pass|Coverage includes empty input, unterminated markup, missing references, Unicode/BOM, escaping, duplicate worker results, missing manifests, relative paths, directories, spaces and symlinks.
|59. Documentation: Doxygen `@param`, `@return`, `@throw` on all public methods; `@par Example` with realistic business scenarios; `@note` for important caveats|Pass|README, generated API main page, example, license notices and release notes added. All 15 bundled Sundown files match a pinned upstream commit before the documented declaration-only change.
|60. QPP flags: `[flags=CONSTANT]` on methods that never throw; `[flags=RET_VALUE_ONLY]` on methods that throw but have no side effects|N/A|No QPP method or flag changes.
|61. Security: No user-controlled format strings; no buffer overflows; bounds checking on array indices; no credentials in code|Pass|No credentials or external services. Staged uninstall uses CMake file operations without shell filename interpolation; raw HTML preservation is explicitly documented.
|62. Correctness: Algorithms verified against reference implementations; edge cases tested (empty data, single sample, all-zero features)|Pass|Debug/Release builds and eight conversion tests (55 assertions) pass without diagnostics; four uninstall tests and actual staged install/uninstall pass; Doxygen succeeds; Valgrind reports zero errors and zero definite/indirect/possible lost bytes.

19 Pass, 43 N/A, 0 Fail.
