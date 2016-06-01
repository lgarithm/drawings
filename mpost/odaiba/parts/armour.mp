% prefix: g.s.l
def def_part_cc(suffix cc) =
  begingroup;
    numeric cc.th[];
    cc.th[1] := 80;
    cc.th[2] := 70;
    cc.th[3] := 60;
    cc.th[4] := 60;
    cc.th[5] := 70;
    cc.th[6] := 80;
    cc.th[7] := 80;

    pair P, Q, R;
    P := origin shifted (g.s.size * dir(180 - 10));
    Q := P shifted (g.s.size * dir(-90 + 15));
    R := Q shifted (.6 * g.s.size * dir(-10));

    pair a, b, c, d, e, f, g;
    a := .2 [origin, P];
    b := .8 [origin, P];
    c := .1 [P, Q];
    d := Q;
    e := .9 [Q, R];
    f := .2 [R, origin];
    g := .9 [R, origin];

    numeric s.l.tmp.d[];
    for i := 1 upto 7:
      s.l.tmp.d[i] := g.s.h / tand(cc.th[i]);
    endfor;

    pair mv[];
    mv[1] := unit(b - a) rotated 90 scaled s.l.tmp.d[1];
    mv[2] := unit(c - b) rotated 90 scaled s.l.tmp.d[2];
    mv[3] := unit(d - c) rotated 90 scaled s.l.tmp.d[3];
    mv[4] := unit(e - d) rotated 90 scaled s.l.tmp.d[4];
    mv[5] := unit(f - e) rotated 90 scaled s.l.tmp.d[5];
    mv[6] := unit(g - f) rotated 90 scaled s.l.tmp.d[6];
    mv[7] := unit(a - g) rotated 90 scaled s.l.tmp.d[7];

    pair aa, bb, cc, dd, ee, ff, gg;
    aa = whatever [g + mv[7], a + mv[7]] = whatever [a + mv[1], b + mv[1]];
    bb = whatever [a + mv[1], b + mv[1]] = whatever [b + mv[2], c + mv[2]];
    cc = whatever [b + mv[2], c + mv[2]] = whatever [c + mv[3], d + mv[3]];
    dd = whatever [c + mv[3], d + mv[3]] = whatever [d + mv[4], e + mv[4]];
    ee = whatever [d + mv[4], e + mv[4]] = whatever [e + mv[5], f + mv[5]];
    ff = whatever [e + mv[5], f + mv[5]] = whatever [f + mv[6], g + mv[6]];
    gg = whatever [f + mv[6], g + mv[6]] = whatever [g + mv[7], a + mv[7]];

    % layer: path
    add_to_list(cc.ps, a -- b -- c -- d -- e -- f -- g -- cycle);
    add_to_list(cc.ps, aa -- bb -- cc -- dd -- ee -- ff -- gg -- cycle);
    % layer: vpath

    % layer: label
    add_self_label_to(cc, a);
    add_self_label_to(cc, b);
    add_self_label_to(cc, c);
    add_self_label_to(cc, d);
    add_self_label_to(cc, e);
    add_self_label_to(cc, f);
    add_self_label_to(cc, g);
  endgroup;
enddef;

def_part_cc(g.s.l);

% prefix: g.s.r
def def_part_cc(suffix cc) =
  begingroup;
    % layer: path
    append_to_list(cc.ps, g.s.l.ps, ymirror);
    % layer: vpath
    append_to_list(cc.qs, g.s.l.qs, ymirror);
  endgroup;
enddef;

def_part_cc(g.s.r);
