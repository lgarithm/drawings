% prefix: g.c
def def_part_g_c(suffix cc) =
  begingroup;
    % parameters:
    numeric cc.size;
    cc.size := 1cm;

    pair o;
    o := (0, -cc.size / 2);

    pair o';
    o' := o scaled .6;

    pair a, b, c, d, e;
    a := dir(-90 - 360 / 5) scaled g.c.size / 2;
    c := dir(-90 - 360 / 5 * 2) scaled g.c.size / 2;
    b = whatever [a, c];
    b - o' + o = whatever [o, a];
    d := 4[o, a];
    e := .5[b, c];

    pair a', b', c', d', e';
    a' := ymirror a;
    b' := ymirror b;
    c' := ymirror c;
    d' := ymirror d;
    e' := ymirror e;

    % layer: path
    add_to_list(cc.ps, o' -- b -- c -- c' -- b' -- cycle);
    add_to_list(cc.ps, a -- d -- e);
    add_to_list(cc.ps, a' -- d' -- e');
    add_to_list(cc.ps, o -- a -- b);
    add_to_list(cc.ps, o -- a' -- b');
    add_to_list(cc.ps, o -- o');
    % layer: vpath

    % layer: label
    add_self_label_to(cc, a);
    add_self_label_to(cc, b);
    add_self_label_to(cc, c);
    add_self_label_to(cc, d);
    add_self_label_to(cc, e);
    add_self_label_to(cc, o);
    add_self_label_to(cc, a');
    add_self_label_to(cc, b');
    add_self_label_to(cc, c');
    add_self_label_to(cc, d');
    add_self_label_to(cc, e');
    add_self_label_to(cc, o');
  endgroup;
enddef;
