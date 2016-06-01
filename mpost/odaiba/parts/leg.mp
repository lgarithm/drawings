% prefix: g.l

% prefix: g.l.u.l
def def_part_cc(suffix cc) =
  begingroup;
    numeric w, l;
    w := g.l.u.w;
    l := g.l.u.len;
    pair a, b, c, d, e;
    a := (-w / 2, 0);
    b := a - (0, l);
    c := b shifted (w / 10 * right);
    d := c shifted (l * .4 * up);
    e = whatever [origin, right] = whatever [c, d];

    pair a', b', c', d', e';
    a' := ymirror a;
    b' := ymirror b;
    c' := ymirror c;
    d' := ymirror d;
    e' := ymirror e;

    % layer: path
    add_to_list(cc.ps, a -- b -- c -- d -- d' -- c' -- b' -- a' -- cycle);
    % layer: vpath
    add_to_list(cc.qs, d -- e);
    add_to_list(cc.qs, d' -- e');

    % leyer: label
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

def_part_cc(g.l.u.l);


% prefix: g.l.u.r
def def_part_cc(suffix cc) =
  begingroup;
% layer: path
    append_to_list(cc.ps, g.l.u.l.ps, ymirror);
% layer: vpath
    append_to_list(cc.qs, g.l.u.l.qs, ymirror);
  endgroup;
enddef;

def_part_cc(g.l.u.r);

% prefix: g.l.l.l
def def_part_cc(suffix cc) =
  begingroup;
    numeric w, l;
    w := g.l.l.w;
    l := g.l.l.len;
    pair a, b, c, d, e;
    a := (-w / 2, -l);
    b := (-w / 2, 0);
    c := b shifted (w / 10 * right);
    d := c shifted (l * .4 * -up);
    e := c shifted (l * -up);

    pair a', b', c', d', e';
    a' := ymirror a;
    b' := ymirror b;
    c' := ymirror c;
    d' := ymirror d;
    e' := ymirror e;

    % layer: path
    add_to_list(cc.ps, a -- b -- c -- d -- d' -- c' -- b' -- a' -- cycle);
    % layer: vpath
    add_to_list(cc.qs, d -- e);
    add_to_list(cc.qs, d' -- e');
    % leyer: label
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

def_part_cc(g.l.l.l);


% prefix: g.l.l.r
def def_part_cc(suffix cc) =
  begingroup;
    % layer: path
    append_to_list(cc.ps, g.l.l.l.ps, ymirror);
    % layer: vpath
    append_to_list(cc.qs, g.l.l.l.qs, ymirror);
  endgroup;
enddef;

def_part_cc(g.l.l.r);
