#!/usr/bin/python

# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Antoine Pietri

import collections
import django
import os
import sys
import tarfile
import tempfile
import time

if len(sys.argv) < 2:
    sys.exit('Usage: {} tournament_id'.format(sys.argv[0]))

os.environ['DJANGO_SETTINGS_MODULE'] = 'prologin.concours.settings'
django.setup()

from prologin.concours.stechec.models import Tournament, Match, MatchPlayer, Champion, TournamentPlayer, Map

tournoi = Tournament.objects.get(id=int(sys.argv[1]))
chs = Champion.objects.filter(matches__tournament=tournoi).distinct()

langs = []
cnt = collections.Counter()

for c in chs:
    lang = c.get_lang_code()
    cnt[lang] += 1
    # Do something like this to merge with the final hall of fame:
    # while read l; do echo $l $(grep $l lang_stats | cut -d$'\t' -f2 ); done < HallOfFame
    print('{}\t({})'.format(c.author.get_full_name(), lang.replace('cxx', 'c++').title()))
    

print(cnt)
