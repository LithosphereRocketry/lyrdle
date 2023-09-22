from azapi import AZlyrics
import os

cachepath = "cache"
aliasfile = "cache/aliases.txt"
if not os.path.exists(cachepath):
    os.makedirs(cachepath)

aliases = {}
if os.path.isfile(aliasfile):
    with open(aliasfile, 'r') as af:
        for l in af.read().split("\n"):
            if l:
                fake, real = l.split(':')
                fakeartist, fakesong = fake.split('~')
                realartist, realsong = real.split('~')
                aliases[(fakeartist, fakesong)] = (realartist, realsong)
else:
    open(aliasfile, 'w')

api = AZlyrics()

def recordAlias(fa, fs, ra, rs):
    aliases[(fa, fs)] = (ra, rs)
    with open(aliasfile, 'a') as af:
        af.write(fa+"~"+fs+":"+ra+"~"+rs+"\n")

def toCachePath(artist, song):
    if (artist, song) in aliases:
        artist, song = aliases[(artist, song)]
    # This should be really unlikely to conflict for any reasonable song title
    # if it does idk cry about it
    return cachepath+"/lyrics_"+artist+"_"+song+".txt"

def fetch_api(artist, song):
    api.artist = artist
    api.title = song
    lyrics = api.getLyrics()
    return (api.artist, api.title, lyrics)

def fetch(artist, song):
    if not os.path.isfile(toCachePath(artist, song)):
        print("Song not cached, downloading...")
        true_artist, true_song, lyrics = fetch_api(artist, song)
        if true_artist != artist or true_song != song:
            recordAlias(artist, song, true_artist, true_song)
        with open(toCachePath(true_artist, true_song), 'w') as f:
            for lyr in lyrics:
                f.write(lyr)
        return lyrics
    else:
        with open(toCachePath(artist, song), 'r') as f:
            return f.read()