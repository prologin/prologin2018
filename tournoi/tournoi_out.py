#!/usr/bin/python

import django
import os
import sys
import time
from collections import defaultdict

if len(sys.argv) < 2:
    print('Usage: {} tournament_id'.format(sys.argv[0]))
    sys.exit(1)

os.environ['DJANGO_SETTINGS_MODULE'] = 'prologin.concours.settings'
django.setup()

from django.contrib.auth.models import User
from prologin.concours.stechec.models import Tournament, Match, MatchPlayer, Champion, TournamentPlayer, Map

from tournoi_common import get_champions

chs = get_champions()

tid = int(sys.argv[1])

tournoi = Tournament.objects.get(id=tid)
matches = Match.objects.filter(tournament=tournoi)
chs = {c for m in matches for c in m.players.all()}

score = defaultdict(int)
indice = defaultdict(int)
matrix = defaultdict(list)
match_ids = defaultdict(list)
for m in matches:
    c1, c2 = tuple(MatchPlayer.objects.filter(match=m))
    matrix[(c1.champion.id, c2.champion.id)].append(c1.score)
    matrix[(c2.champion.id, c1.champion.id)].append(c2.score)

    match_ids[(c1.champion.id, c2.champion.id)].append(m.id)
    match_ids[(c2.champion.id, c1.champion.id)].append(m.id)

    # Indices
    indice[c1.champion.id] += c1.score
    indice[c2.champion.id] += c2.score

    # Victories
    if c1.score > c2.score:
        score[c1.champion.id] += 2
    elif c2.score > c1.score:
        score[c2.champion.id] += 2
    else:
        score[c1.champion.id] += 1
        score[c2.champion.id] += 1

print('''<!DOCTYPE html>
<head>
  <link rel="stylesheet" href="style.css">
  <title>Prologin 2018 : {}</title>
</head>
<body>'''.format(tournoi.name))

print('<h1>{}</h1>'.format(tournoi.name))
print('<h2>Classement</h2>')

print('<table>')
print('<thead><td>#</td><td>Victoires</td><td>Nom</td><td>Login</td><td>Nom</td></thead>')
l = list(chs)
l.sort(key=lambda x: -score.get(x.pk, 0))
for i, c in enumerate(l, 1):
    print('<tr>')
    print('<td>{}</td>'.format(i))
    print('<td>{}</td>'.format(score.get(c.pk, 0) // 2))
    print('<td><strong><a href="http://concours/champions/{}/sources/">{}</a></strong></td>'.format(c.id, c.name))
    print('<td>{}</td><td>{}</td>'.format(c.author.username, c.author.get_full_name()))
    print('</tr>')
print('</table>')

for i, c1 in enumerate(l, 1):
    print('<h2>{}. {} (de {})</h2>'.format(i, c1.name, c1.author.username))

    print('<table>')
    print('<thead>')
    print('<td>VS</td>')
    for i in range(len(matrix[c1.pk, l[0].pk])):
        print('<td>Match {}</td>'.format(i + 1))
    print('<td>Total</td>')
    print('</thead>')

    for i, c2 in enumerate(l, 1):
        print('<tr><td><strong>{}</strong>'.format(i))

        for j in range(len(matrix[c1.pk, c2.pk])):
            if c1.pk == c2.pk:
                print('<td>X</td>')
            else:
                cssclass = 'lost' if matrix[c1.pk, c2.pk][j] < matrix[c2.pk, c1.pk][j] else 'won'
                print('<td class="{}"><a href="http://concours/matches/{}">{}</a></td>'.format(cssclass, match_ids[c1.pk, c2.pk][j], matrix[c1.pk, c2.pk][j]))
        print('<td><strong>{}</strong></td>'.format(sum(matrix[c1.pk, c2.pk])))
        print('</tr>')
    print('</table>')

print('</body></html>')
