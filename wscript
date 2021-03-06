#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (c) 2012-2020 Association Prologin <association@prologin.org>

import glob
import os.path

from wafgenerator import generator_player_install


def options(opt):
    pass


def configure(cfg):
    pass


def build(bld):
    bld.shlib(
        source='''
            src/action_deplacer.cc
            src/action_glisser.cc
            src/action_pousser.cc
            src/action_debug_afficher_drapeau.cc
            src/api.cc
            src/entry.cc
            src/game_state.cc
            src/interface.cc
            src/map.cc
            src/player_info.cc
            src/rules.cc
            src/dumper.cc
        ''',
        defines=['MODULE_COLOR=ANSI_COL_BROWN', 'MODULE_NAME="rules"'],
        target='prologin2018',
        use=['stechec2'],
    )

    abs_pattern = os.path.join(bld.path.abspath(), 'src/tests/test-*.cc')
    for test_src in glob.glob(abs_pattern):

        test_name = os.path.split(test_src)[-1]
        test_name = test_name[len("test-"):-(len(".cc"))]

        # Waf requires a relative path for the source
        src_relpath = os.path.relpath(test_src, bld.path.abspath())

        bld.program(
            features='gtest',
            source=src_relpath,
            target='prologin2018-test-{}'.format(test_name),
            use=['prologin2018', 'stechec2-utils'],
            includes=['.'],
            defines=['MODULE_COLOR=ANSI_COL_PURPLE',
                     'MODULE_NAME="prologin2018"'],
        )

    bld.install_files('${PREFIX}/share/stechec2/prologin2018', [
        'prologin2018.yml',
    ])

    generator_player_install(bld, 'prologin2018')
