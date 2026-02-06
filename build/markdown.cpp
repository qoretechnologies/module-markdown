/*
  markdown.qpp

  Qore Programming Language

  Copyright 2012-2013 Qore Technologies

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <qore/Qore.h>
#include "markdown.h"
#include "html.h"

static QoreNamespace MarkdownNS("Markdown");

void init_markdown_functions(QoreNamespace& ns);

static void markdown_module_init(QoreModuleInitContext& ctx, ExceptionSink& xsink) {
    init_markdown_functions(MarkdownNS);
}

static void markdown_module_ns_init(QoreNamespace* rns, QoreNamespace* qns, ExceptionSink& xsink) {
    qns->addNamespace(MarkdownNS.copy());
}

void markdown_module_delete() {
   // nothing to do here in this case
}

extern "C" DLLEXPORT void markdown_qore_module_desc(QoreModuleInfo& mod_info) {
    mod_info.name = "markdown";
    mod_info.version = PACKAGE_VERSION;
    mod_info.desc = "Markdwon parser module";
    mod_info.author = "Petr Vanek";
    mod_info.url = "http://qore.org";
    mod_info.api_major = QORE_MODULE_API_MAJOR;
    mod_info.api_minor = QORE_MODULE_API_MINOR;
    mod_info.init = markdown_module_init;
    mod_info.ns_init = markdown_module_ns_init;
    mod_info.del = markdown_module_delete;
    mod_info.license = QL_LGPL;
    mod_info.license_str = "LGPL";
}
# 64 "/home/david/src/qore/git/module-markdown/src/markdown.qpp"
# 69 "/home/david/src/qore/git/module-markdown/src/markdown.qpp"
# 76 "/home/david/src/qore/git/module-markdown/src/markdown.qpp"
// string markdown_convert(string input) {}
static QoreValue f_markdown_convert_Vs(const QoreListNode* args, RuntimeConfig& runtime_cfg, ExceptionSink* xsink) {
    const QoreStringNode* input = HARD_QORE_VALUE_STRING(args, 0);
# 79 "/home/david/src/qore/git/module-markdown/src/markdown.qpp"
    unsigned int extensions = MKDEXT_NO_INTRA_EMPHASIS|MKDEXT_TABLES|MKDEXT_FENCED_CODE|MKDEXT_AUTOLINK|MKDEXT_STRIKETHROUGH|MKDEXT_SUPERSCRIPT|MKDEXT_LAX_SPACING;
    sd_callbacks callbacks;
    html_renderopt options;

    sdhtml_renderer(&callbacks, &options, 0);
    //sdhtml_toc_renderer(&callbacks, &options);

    buf *ob = bufnew(64);
    sd_markdown* md = sd_markdown_new(extensions, 16, &callbacks, &options);
	sd_markdown_render(ob, (const uint8_t*)input->getBuffer(), input->size(), md);
    // sdhtml_smartypants(ob, ib->data, ib->size);
	sd_markdown_free(md);

    QoreStringNode* ret = new QoreStringNode((const char*)ob->data, ob->size);

    bufrelease(ob);

    return ret;
}

// string markdown_version() {}
static QoreValue f_markdown_version(const QoreListNode* args, RuntimeConfig& runtime_cfg, ExceptionSink* xsink) {
# 72 "/home/david/src/qore/git/module-markdown/src/markdown.qpp"
    return new QoreStringNode(SUNDOWN_VERSION);
}


DLLLOCAL void init_markdown_functions(QoreNamespace& ns) {
    // string markdown_convert(string input) {}
    ns.addBuiltinVariant("markdown_convert", (q_func_t)f_markdown_convert_Vs, QCF_RET_VALUE_ONLY, QDOM_DEFAULT, stringTypeInfo, 1, stringTypeInfo, QORE_PARAM_NO_ARG, "input");
    // string markdown_version() {}
    ns.addBuiltinVariant("markdown_version", (q_func_t)f_markdown_version, QCF_RET_VALUE_ONLY, QDOM_DEFAULT, stringTypeInfo);

}
