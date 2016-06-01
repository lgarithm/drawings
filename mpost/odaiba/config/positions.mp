% positions
% - pos: absolute position of center
% - ag: rotate angle

% body
g.w.pos := (0, g.w.h / 2);
g.b.pos := (0, g.w.h + g.b.h / 2);

% head
g.h.pos := (0, g.w.h + g.b.h + g.h.size / 2);

% corn
g.c.pos := (0, g.w.h + g.b.h + g.h.size + g.c.size / 2);

% armour
g.s.l.pos := origin
  shifted (0, g.w.h)
  shifted (-g.b.ul / 2, g.b.h)
  shifted (-g.s.size / 2, - g.s.size / 2);

g.s.r.pos := ymirror g.s.l.pos;

% arm 1
g.a.u.l.ag := -10;
g.a.u.l.pos := g.s.l.pos
  shifted ((g.a.u.len / 2 + g.link.a.s.d) * dir(-90 + g.a.u.l.ag));

g.a.u.r.pos := ymirror g.a.u.l.pos;
g.a.u.r.ag := -g.a.u.l.ag;

% arm 2
g.a.l.l.ag := g.a.u.l.ag;
g.a.l.l.pos := -up scaled (g.a.u.len + 1cm + g.a.l.len / 2)
  transformed abs_trans(g.a.u.l);

g.a.l.r.ag := -g.a.l.l.ag;
g.a.l.r.pos := ymirror g.a.l.l.pos;

% arm join
g.a.j.l.ag := g.a.u.l.ag;
g.a.j.l.pos := -up scaled (g.a.u.len + 1cm / 2)
  transformed abs_trans(g.a.u.l);

g.a.j.r.ag := g.a.u.r.ag;
g.a.j.r.pos := ymirror(g.a.j.l.pos);

% leg 1
g.l.u.l.ag := -10;
g.l.u.l.pos := (-(g.l.u.w + g.l.u.d) / 2, 0)
  shifted ((g.l.u.len / 2) * dir(-90 + g.l.u.l.ag));

g.l.u.r.ag := -g.l.u.l.ag;
g.l.u.r.pos := ymirror g.l.u.l.pos;

% leg 2
g.l.l.l.pos := -up scaled (g.l.u.len + 1cm + g.l.l.len / 2)
  transformed abs_trans(g.l.u.l);
g.l.l.l.ag := g.l.u.l.ag;

g.l.l.r.pos := ymirror g.l.l.l.pos;
g.l.l.r.ag := -g.l.l.l.ag;

% leg join
g.l.j.l.ag := g.l.u.l.ag;
g.l.j.l.pos := -up scaled (g.l.u.len + 1cm / 2)
  transformed abs_trans(g.l.u.l);

g.l.j.r.ag := g.l.u.r.ag;
g.l.j.r.pos := ymirror(g.l.j.l.pos);
