#!/usr/bin/env python

import yaml

output = ""
with open('../prologin2018.yml', 'r') as content:
    data = yaml.load(content)
    for constant in data['constant']:
        output += "\nconst {} = {}\n".format(constant['cst_name'],
                                             constant['cst_val'])

with open('godot/scripts/Constants.gd', 'w') as content:
    content.write("# SPDX-License-Identifier: GPL-2.0-or-later\n")
    content.write("# Copyright 2018 Sacha Delanoue\n\n")
    content.write("# This file has been generated, you should not edit it\n\n")
    content.write("extends Node\n")
    content.write(output)
