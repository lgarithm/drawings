% outputformat := "png";
outputtemplate := "%j-%02c.%o";

nf := 24;
dr := 360 / nf;

def frame(expr j) =
    draw_filled_main(n, t, rr, r, R);
    if j mod 3 = 0:
      draw_filled_face_i;
    else:
      if j mod 3 = 1:
        draw_filled_face_ii;
      else:
	draw_filled_face_iii;
      fi;
    fi;
enddef;

for j:=1 upto nf:
    beginfig(j);
        th0 := th0 + dr;
        frame(j);
    endfig;
endfor;
