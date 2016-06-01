def fig_part (suffix c) =
  beginfig(100 + c.idx);
    transform t;
    t := identity scaled c.scale;
    draw_path_list_with(c.ps, t, );
    draw_path_list_with(c.qs, t, dashed evenly);
    draw_frame(identity);
    drawarrow origin -- -c.origin transformed t withcolor blue;
    draw_all_labels(c, t);
  endfig;
enddef;

g.s.l.scale := 4;
g.s.r.scale := 4;
g.c.scale := 4;
map_f(fig_part);

beginfig(100);
  transform t;
  t := identity scaled 2;
  draw_path_list_with(g.h.ps, abs_trans(g.h) transformed t, );
  draw_path_list_with(g.c.ps, abs_trans(g.c) transformed t, );
endfig;
