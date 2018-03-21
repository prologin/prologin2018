#! /usr/bin/env python

def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
            src/action_deplacer.cc
            src/action_glisser.cc
            src/api.cc
            src/entry.cc
            src/game_state.cc
            src/interface.cc
            src/map.cc
            src/player_info.cc
            src/rules.cc
        ''',
        defines = ['MODULE_COLOR=ANSI_COL_BROWN', 'MODULE_NAME="rules"'],
        target = 'prologin2018',
        use = ['stechec2'],
    )

    bld.install_files('${PREFIX}/share/stechec2/prologin2018', [
        'prologin2018.yml',
    ])
