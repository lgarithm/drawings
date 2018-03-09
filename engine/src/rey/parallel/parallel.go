package parallel

func Multi(m int, n int, f func(int, int)) {
	if m <= 0 {
		return
	}
	todo := make(chan int, n)
	for j := 0; j < n; j++ {
		todo <- j
	}
	done := make(chan int, n)
	for k := 0; k < m; k++ {
		go func(k int) {
			for {
				select {
				case j := <-todo:
					f(j, k)
					done <- j
					break
				default:
					return
				}
			}
		}(k)
	}
	for j := 0; j < n; j++ {
		<-done
	}
}
