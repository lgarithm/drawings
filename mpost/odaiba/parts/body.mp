% prefix: g.b
def def_part_g_b(suffix cc) =
  begingroup;
    % parameters:
    numeric g.b.ha, g.b.hb, g.b.hc;
    g.b.ha := 3cm;
    g.b.hb := 1cm;
    g.b.hc := 1cm;

    % layer: vpath
    add_to_list(cc.qs, origin
        -- (-g.b.ll / 2, 0)
        -- (-g.b.ul / 2, g.b.h)
        -- (g.b.ul / 2, g.b.h)
        -- (g.b.ll / 2, 0)
        -- cycle);

    pair a, b, c, d, e, f, g;
    a := (-g.b.ul / 2, g.b.h);
    b := (-g.b.ul / 2, g.b.h - g.b.ha / 2);
    c := (-g.b.ul / 2, g.b.h - g.b.ha);
    d := (-g.b.ul / 2 * .8, g.b.hb + g.b.hc);
    e := (-g.b.ul / 2 * .7, g.b.hc);
    f := (-g.b.ul / 2 * .6, g.b.hc);
    g := (-g.b.ul / 2 * .65, 0);

    pair a', b', c', d', e', f', g';
    a' := ymirror a;
    b' := ymirror b;
    c' := ymirror c;
    d' := ymirror d;
    e' := ymirror e;
    f' := ymirror f;
    g' := ymirror g;

    % layer: path
    add_to_list(cc.ps, a -- b -- c -- c' -- b' -- a' -- cycle);
    add_to_list(cc.ps, d -- e -- e' -- d');
    add_to_list(cc.ps, f -- g -- g' -- f');

    % layer: label
    add_self_label_to(cc, a);
    add_self_label_to(cc, b);
    add_self_label_to(cc, c);
    add_self_label_to(cc, d);
    add_self_label_to(cc, e);
    add_self_label_to(cc, f);
    add_self_label_to(cc, g);
    add_self_label_to(cc, a');
    add_self_label_to(cc, b');
    add_self_label_to(cc, c');
    add_self_label_to(cc, d');
    add_self_label_to(cc, e');
    add_self_label_to(cc, f');
    add_self_label_to(cc, g');
  endgroup;
enddef;

% prefix: g.w
def def_part_g_w(suffix cc) =
  begingroup;
    % parameters:
    numeric cc.w, cc.h, cc.hh, cc.sisze;
    cc.w := 6cm;
    cc.hh := 2cm;
    cc.h := 2.5cm;
    cc.size := 2.5cm;

    % control points:
    pair a, b, c;
    a := (-cc.w / 2 * .8, 0);
    b := (-cc.w / 2, -cc.hh);
    c := (-(g.l.u.d - .6cm) / 2, -cc.h);

    pair d, e, f, g;
    % d :=

    pair a', b', c';
    a' := ymirror a;
    b' := ymirror b;
    c' := ymirror c;

    pair d', e', f', g';

    % layer: path
    add_to_list(cc.ps, origin -- a -- b -- c -- c' -- b' -- a' -- cycle);
    % layer: vpath

    % layer: label
    add_self_label_to(cc, a);
    add_self_label_to(cc, b);
    add_self_label_to(cc, c);
    add_self_label_to(cc, a');
    add_self_label_to(cc, b');
    add_self_label_to(cc, c');
  endgroup;
enddef;
