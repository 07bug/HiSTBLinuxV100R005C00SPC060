# -*- Mode: Python -*-
# vi:si:et:sw=4:sts=4:ts=4

"""
Insert includes for the element-*-details.xml files into the related docbook
files.
"""

from __future__ import print_function, unicode_literals

import codecs
import glob
import os
import sys

import xml.dom.minidom

def patch(related, details):
    try:
        doc = xml.dom.minidom.parse(related)
    except IOError:
        return

    # find the insertion point
    elem = None
    for e in doc.childNodes:
        if e.nodeType == e.ELEMENT_NODE and e.localName == 'refentry':
            elem = e
            break
    if elem == None:
        return

    elem2 = None
    for e in elem.childNodes:
        if e.nodeType == e.ELEMENT_NODE and e.localName == 'refsect1':
            id = e.getAttributeNode('id')
            role = e.getAttributeNode('role')
            if id and id.nodeValue.endswith('.description') and role and role.nodeValue == 'desc':
                elem2 = e
                break
    if elem2 == None:
        return

    # insert include
    include = doc.createElement('include')
    include.setAttribute('xmlns', 'http://www.w3.org/2003/XInclude')
    include.setAttribute('href', details)
    fallback = doc.createElement('fallback')
    fallback.setAttribute('xmlns', 'http://www.w3.org/2003/XInclude')
    include.appendChild(fallback)
    elem2.appendChild(include)

    # store patched file
    result = codecs.open(related, mode="w", encoding="utf-8")
    #result = open(related, "wb")
    doc.writexml(result)
    result.close()

def main():
    if not len(sys.argv) == 2:
        sys.stderr.write('Please specify the xml/ dir')
        sys.exit(1)

    xmldir = sys.argv[1]

    # parse all *-details.xml files and patch includes into the corresponding
    # xml files
    for details in glob.glob("%s/element-*-details.xml" % xmldir):
        patch (details.replace("-details", ""), os.path.basename(details))

main()
