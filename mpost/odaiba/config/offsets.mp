% center
% - origin: local frame origin

% body
g.w.origin := (0, g.w.h / 2);
g.b.origin := (0, -g.b.h / 2);

% head
g.h.origin := (0, -g.h.size / 2);

% corn
g.c.origin := origin;

% armour
g.s.l.origin := (g.s.size / 2, g.s.size / 2);

g.s.r.origin := ymirror g.s.l.origin;

% arm
g.a.u.l.origin := (0, g.a.u.len / 2);

g.a.u.r.origin := ymirror g.a.u.l.origin;

% arm 2
g.a.l.l.origin := (0, g.a.l.len / 2);

g.a.l.r.origin := ymirror g.a.l.l.origin;

% leg 1
g.l.u.l.origin := (0, g.l.u.len / 2);

g.l.u.r.origin := ymirror g.l.u.l.origin;

% leg 2
g.l.l.l.origin := (0, g.l.l.len / 2);

g.l.l.r.origin := ymirror g.l.l.l.origin;
