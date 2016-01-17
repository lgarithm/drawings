def frame(expr j) =
    if j mod 2 = 0:
        draw_main(n, t);
        draw_face_i;
    else:
        draw_main(n, t);
    fi;
enddef;

for j:=1 upto 16:
    beginfig(j);
        frame(j);
    endfig;
endfor;
