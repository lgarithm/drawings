% prefix: g.h
def def_part_cc(suffix cc) =
  begingroup;
    pair a, b, c, d;
    a := (-g.h.size / 2, 0);
    b := 1.5 [origin, a];
    c := origin rotatedaround(b, 90);
    d := (-g.h.size / 2, g.h.size);

    pair a', b', c', d';
    a' := ymirror a;
    b' := ymirror b;
    c' := ymirror c;
    d' := ymirror d;

    % layer: path
    add_to_list(cc.ps, a -- d -- d' -- a' -- cycle);
    add_to_list(cc.ps, a -- b -- c .. d .. d' .. c' -- b' -- a' -- cycle);
    add_to_list(cc.ps, d .. (0, 1.5 g.h.size) .. d');
    % layer: vpath

    % layer: label
    add_self_label_to(cc, a);
    add_self_label_to(cc, b);
    add_self_label_to(cc, c);
    add_self_label_to(cc, d);
    add_self_label_to(cc, a');
    add_self_label_to(cc, b');
    add_self_label_to(cc, c');
    add_self_label_to(cc, d');
  endgroup;
enddef;

def_part_cc(g.h);
