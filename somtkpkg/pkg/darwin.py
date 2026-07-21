#!/usr/bin/env python3
from sys import argv as a
from xml.etree import ElementTree as ET

tree = ET.parse(a[1])
text = ET.Element('title')
text.text = a[2]
tree.getroot().append(text)
tree.write(a[1])
