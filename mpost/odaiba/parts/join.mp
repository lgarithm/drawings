% prefix: g.a.j.l
def def_part_cc(suffix cc) =
  begingroup;
    % parameters:
    numeric r, l, l';
    r := 1cm;
    l := 1.2 g.a.u.w;
    l' := .8 g.a.u.w;
    l'' := 1.4 g.a.u.w;

    % controls:
    pair a, b, c, d;
    a := (-l' / 2, r / 2);
    b := (-l / 2, r / 2);
    c := xmirror(b);
    d := xmirror(a);
    e := (-l'' / 2, 0);

    pair a', b', c', d';
    a' := ymirror a;
    b' := ymirror b;
    c' := ymirror c;
    d' := ymirror d;
    e' := ymirror e;

    % layer: path
    add_to_list(cc.ps, a -- b -- c -- d);
    add_to_list(cc.ps, a' -- b' -- c' -- d');
    % layer: vpath
    add_to_list(cc.qs, e -- e');
    % layer: label
    add_self_label_to(cc, a);
    add_self_label_to(cc, b);
    add_self_label_to(cc, c);
    add_self_label_to(cc, d);
    add_self_label_to(cc, e);
    add_self_label_to(cc, a');
    add_self_label_to(cc, b');
    add_self_label_to(cc, c');
    add_self_label_to(cc, d');
    add_self_label_to(cc, e');
  endgroup;
enddef;

def_part_cc(g.a.j.l);


% prefix: g.a.j.r
def def_part_cc(suffix cc) =
  begingroup;
% layer: path
    append_to_list(cc.ps, g.a.j.l.ps, ymirror);
% layer: vpath
    append_to_list(cc.qs, g.a.j.l.qs, ymirror);
  endgroup;
enddef;

def_part_cc(g.a.j.r);



% prefix: g.l.j.l
def def_part_cc(suffix cc) =
  begingroup;
% parameters:
    numeric r, l, l';
    r := 1cm;
    l := 1.2 g.l.u.w;
    l' := .8 g.l.u.w;
    l'' := 1.4 g.l.u.w;

% controls:
    pair a, b, c, d;
    a := (-l' / 2, r / 2);
    b := (-l / 2, r / 2);
    c := xmirror(b);
    d := xmirror(a);
    e := (-l'' / 2, 0);

    pair a', b', c', d';
    a' := ymirror(a);
    b' := ymirror(b);
    c' := ymirror(c);
    d' := ymirror(d);
    e' := ymirror(e);

% layer: path
    add_to_list(cc.ps, a -- b -- c -- d);
    add_to_list(cc.ps, a' -- b' -- c' -- d');
% layer: vpath
    add_to_list(cc.qs, e -- e');
% layer: label
    add_self_label_to(cc, a);
    add_self_label_to(cc, b);
    add_self_label_to(cc, c);
    add_self_label_to(cc, d);
    add_self_label_to(cc, e);
    add_self_label_to(cc, a');
    add_self_label_to(cc, b');
    add_self_label_to(cc, c');
    add_self_label_to(cc, d');
    add_self_label_to(cc, e');
  endgroup;
enddef;

def_part_cc(g.l.j.l);


% prefix: g.l.j.r
def def_part_cc(suffix cc) =
  begingroup;
    % layer: path
    append_to_list(cc.ps, g.l.j.l.ps, ymirror);
    % layer: vpath
    append_to_list(cc.qs, g.l.j.l.qs, ymirror);
  endgroup;
enddef;

def_part_cc(g.l.j.r);
