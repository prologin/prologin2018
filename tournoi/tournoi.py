#!/usr/bin/python

import collections
import django
import os

os.environ['DJANGO_SETTINGS_MODULE'] = 'prologin.concours.settings'
django.setup()

from django.db import connection
from django.contrib.auth.models import User
from django.utils.timezone import now
from prologin.concours.stechec.models import Tournament, Match, MatchPlayer, Champion, TournamentPlayer, Map

from tournoi_common import get_champions

prologin = User.objects.get(username="seirl")
tournoi = Tournament.objects.create()

#maps_ids = (2, 6, 16, 18)
#maps_ids = (2, 3, 5, 6, 17)
#maps_ids = (21, 16, 6, 5)
#maps_ids = (3, 2, 5, 21)
#maps_ids = (6, 17, 18, 21)
#maps_ids = (2, 5, 21, 22)
#maps_ids = (27,)
maps_ids = (2, 3, 5, 6, 16, 17, 18, 21)
maps = [Map.objects.get(pk=i) for i in maps_ids]

print('Launching tournament {}'.format(tournoi.id))

chs = get_champions()

print()
print('There are {} champions:'.format(len(chs)))
for ch in chs:
    print('-', ch)

print()
print('Maps are :')
for m in maps:
    print('-', m)

input()
print()
print('Launching matches...')
match_objs = []
ts = now()
for map in maps:
    for i in range(len(chs) ** 2):
        m = Match(author=prologin, tournament=tournoi)
        m.map = map.path
        m.ts = ts
        match_objs.append(m)
Match.objects.bulk_create(match_objs)

matches = Match.objects.filter(ts=ts)
matches_per_map = collections.defaultdict(list)
for m in matches:
    matches_per_map[m.map.id].append(m)

player_objs = []
for map in maps:
    map_matches = matches_per_map[map.id]
    for c1 in chs:
        for c2 in chs:
            m = map_matches.pop()
            player_objs.append(MatchPlayer(champion=c1, match=m))
            player_objs.append(MatchPlayer(champion=c2, match=m))
MatchPlayer.objects.bulk_create(player_objs)

with connection.cursor() as c:
    c.execute('''
        UPDATE stechec_match SET status='new' WHERE id IN (%s)
    ''' % ','.join(str(m.id) for m in list(matches)))
