% global metrics

% body
numeric g.b.ul, g.b.ll, g.b.h;
g.b.ul := 6cm;
g.b.ll := 4cm;
g.b.h := 5cm;
numeric g.b.size;
g.b.size := 5cm;

% armour
numeric g.s.size;
g.s.size = 2.5cm;
numeric g.s.h;  % thickness
g.s.h = g.s.size / 10;

% arm 1
numeric g.a.u.len, g.a.u.w, g.a.u.a;
g.a.u.len := 4cm;
g.a.u.w := 2cm;
g.a.u.a = 0;

numeric g.a.u.l.size;
numeric g.a.u.r.size;
g.a.u.l.size = g.a.u.r.size = g.a.u.len;

% arm 2
numeric g.a.l.len, g.a.l.w, g.a.l.a;
g.a.l.len := 4cm;
g.a.l.w := g.a.u.w;
g.a.l.a := 5;

numeric g.a.l.l.size;
numeric g.a.l.r.size;
g.a.l.l.size = g.a.l.r.size = g.a.l.len;

% leg 1
numeric g.l.u.len, g.l.u.d, g.l.u.w, g.l.u.a;
g.l.u.d := 2cm;
g.l.u.len := 5cm;
g.l.u.w := 2cm;
g.l.u.a := 10;

numeric g.l.u.l.size;
numeric g.l.u.r.size;
g.l.u.l.size = g.l.u.r.size = g.l.u.len;

% leg 2
numeric g.l.l.len, g.l.l.w, g.l.l.a;
g.l.l.len := 7cm;
g.l.l.w := g.l.u.w;
g.l.l.a := 5;

numeric g.l.l.l.size;
numeric g.l.l.r.size;
g.l.l.l.size = g.l.l.r.size = g.l.l.len;

% foot

% links
numeric g.link.a.s.d;
g.link.a.s.d := g.s.size / 2;
