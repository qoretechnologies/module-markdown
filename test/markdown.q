#!/usr/bin/env qore
%modern
%requires markdown

printf("VERSION: %n\n", markdown_version());

string doc = new ReadOnlyFile("test.md").read(-1);
string html = markdown_convert(doc);
printf("%s\n", html);
