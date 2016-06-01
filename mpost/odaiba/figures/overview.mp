def fig_with(expr n) (text f)=
  beginfig(n);
    map_f(f);
  endfig;
enddef;

def draw_part(suffix c) =
  transform t;
  t := abs_trans(c);
  draw_path_list_with(c.ps, t, );
enddef;

def draw_part_full(suffix c) =
  transform t;
  t := abs_trans(c);
  draw_path_list_with(c.ps, t, );
  draw_path_list_with(c.qs, t, dashed evenly);
  draw_arrow(c);
  draw_local_frame(c);
  draw_position(c);
  draw_offset(c);

  draw_range_circle(c);
enddef;

beginfig(0);
  map_f(draw_part);
endfig;

beginfig(1);
  map_f(draw_part_full);
endfig;

beginfig(2);
  map_f(draw_position);
  map_f(draw_local_frame);
  map_f(draw_range_rect);
  map_f(draw_range_circle);
  map_f(draw_arrow);
  map_f(draw_offset);
endfig;
